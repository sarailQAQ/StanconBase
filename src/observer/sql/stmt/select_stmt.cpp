/* Copyright (c) 2021 OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

//
// Created by Wangyunlai on 2022/6/6.
//

#include "sql/stmt/select_stmt.h"
#include "sql/stmt/filter_stmt.h"
#include "common/log/log.h"
#include "common/lang/string.h"
#include "storage/db/db.h"
#include "storage/table/table.h"

SelectStmt::~SelectStmt()
{
  if (nullptr != filter_stmt_) {
    delete filter_stmt_;
    filter_stmt_ = nullptr;
  }
}

static void wildcard_fields(Table *table, std::vector<Field> &field_metas)
{
  const TableMeta &table_meta = table->table_meta();
  const int        field_num  = table_meta.field_num();
  for (int i = table_meta.sys_field_num(); i < field_num; i++) {
    field_metas.push_back(Field(table, table_meta.field(i)));
  }
}

RC SelectStmt::create(Db *db, const SelectSqlNode &select_sql, Stmt *&stmt)
{
  if (nullptr == db) {
    LOG_WARN("invalid argument. db is null");
    return RC::INVALID_ARGUMENT;
  }

  // collect tables in `from` statement
  std::vector<Table *>                     tables;
  std::unordered_map<std::string, Table *> table_map;
  //  校验每个表，并存在table_map里
  for (size_t i = 0; i < select_sql.relations.size(); i++) {
    const char *table_name = select_sql.relations[i].c_str();
    if (nullptr == table_name) {
      LOG_WARN("invalid argument. relation name is null. index=%d", i);
      return RC::INVALID_ARGUMENT;
    }

    Table *table = db->find_table(table_name);
    if (nullptr == table) {
      LOG_WARN("no such table. db=%s, table_name=%s", db->name(), table_name);
      return RC::SCHEMA_TABLE_NOT_EXIST;
    }

    tables.push_back(table);
    table_map.insert(std::pair<std::string, Table *>(table_name, table));
  }

  // collect query fields in `select` statement
  std::vector<Field> query_fields;
  std::vector<Field> agg_fields_;
  //  校验每一个需要查出来的字段（属性）
  for (int i = static_cast<int>(select_sql.attributes.size()) - 1; i >= 0; i--) {
    const RelAttrSqlNode &relation_attr = select_sql.attributes[i];
    // is_blank 检查一个以NULL中止的C字符串是否为空白（空格字符）
    //  有聚合函数
    if (relation_attr.agg_func != AggFunc::A_NULL) {
      Table           *table;
      const FieldMeta *field_meta;
      // 没给表名就取第一个，给了就取指定的
      if (common::is_blank(relation_attr.relation_name.c_str())) {
        if (tables.size() != 1) {
          LOG_WARN("invalid. I do not know the attr's table. attr=%s", relation_attr.attribute_name.c_str());
          return RC::SCHEMA_FIELD_MISSING;
        }
        table = tables[0];
      } else {
        table = table_map[relation_attr.relation_name];
      }

      if(table == nullptr){
        LOG_WARN("can not find table : %s", relation_attr.relation_name.c_str());
        return RC::SCHEMA_TABLE_NOT_EXIST;
      }

      // 字段不是* 就校验字段是否存在
      if (0 != strcmp(relation_attr.attribute_name.c_str(), "*")) {
        field_meta = table->table_meta().field(relation_attr.attribute_name.c_str());
        if (nullptr == field_meta) {
          LOG_WARN("no such field. field=%s.%s.%s", db->name(), table->name(), relation_attr.attribute_name.c_str());
          return RC::SCHEMA_FIELD_MISSING;
        }
      } else {
        // 字段是 * 就默认按照以第一个字段(第一个非系统字段)来聚合
        field_meta = table->table_meta().field(table->table_meta().sys_field_num());
      }

      // 校验不支持的聚合字段
      if ((relation_attr.agg_func == AggFunc::A_AVG || relation_attr.agg_func == AggFunc::A_SUM) &&
          (field_meta->type() == AttrType::CHARS || field_meta->type() == AttrType::DATES)) {
        LOG_WARN("not support func field=%s.%s.%s , func = %s", db->name(), table->name(), relation_attr.attribute_name.c_str(),relation_attr.agg_func);
        return RC::INVALID_ARGUMENT;
      }

      // 校验完成
      agg_fields_.emplace_back(Field(table, field_meta, relation_attr.alias, relation_attr.agg_func));
      continue;
    }

    if (common::is_blank(relation_attr.relation_name.c_str()) &&
        0 == strcmp(relation_attr.attribute_name.c_str(), "*")) {  // 未指定表名，且需要所有字段
      for (Table *table : tables) {
        // 将一个表中除了系统字段外的所有字段添加到一个字段元数据向量
        wildcard_fields(table, query_fields);
      }

    } else if (!common::is_blank(relation_attr.relation_name.c_str())) {  // 指定表名
      const char *table_name = relation_attr.relation_name.c_str();
      const char *field_name = relation_attr.attribute_name.c_str();

      if (0 == strcmp(table_name, "*")) {
        if (0 != strcmp(field_name, "*")) {
          LOG_WARN("invalid field name while table is *. attr=%s", field_name);
          return RC::SCHEMA_FIELD_MISSING;
        }
        // 所有表的所有字段 *.*
        for (Table *table : tables) {
          wildcard_fields(table, query_fields);
        }
      } else {  // 指定表
        auto iter = table_map.find(table_name);
        if (iter == table_map.end()) {
          LOG_WARN("no such table in from list: %s", table_name);
          return RC::SCHEMA_FIELD_MISSING;
        }

        Table *table = iter->second;
        if (0 == strcmp(field_name, "*")) {  // 指定表的所有字段
          wildcard_fields(table, query_fields);
        } else {  // 指定表，指定字段
                  // 在 fields_ 中查找指定名称的字段，并返回对应的字段元数据指针
          const FieldMeta *field_meta = table->table_meta().field(field_name);
          if (nullptr == field_meta) {
            LOG_WARN("no such field. field=%s.%s.%s", db->name(), table->name(), field_name);
            return RC::SCHEMA_FIELD_MISSING;
          }

          query_fields.push_back(Field(table, field_meta, relation_attr.alias));
        }
      }
    } else {  // 没给表名（使用from list 里唯一的表名）
      if (tables.size() != 1) {
        LOG_WARN("invalid. I do not know the attr's table. attr=%s", relation_attr.attribute_name.c_str());
        return RC::SCHEMA_FIELD_MISSING;
      }

      Table           *table      = tables[0];
      const FieldMeta *field_meta = table->table_meta().field(relation_attr.attribute_name.c_str());
      if (nullptr == field_meta) {
        LOG_WARN("no such field. field=%s.%s.%s", db->name(), table->name(), relation_attr.attribute_name.c_str());
        return RC::SCHEMA_FIELD_MISSING;
      }

      query_fields.push_back(Field(table, field_meta, relation_attr.alias));
    }
  }

  // 聚合函数不允许与普通字段同时查询
  if (!query_fields.empty() && !agg_fields_.empty()) {
    LOG_WARN("聚合函数不允许与普通字段同时查询");
    return RC::INVALID_ARGUMENT;
  }

  LOG_INFO("got %d tables in from stmt and %d fields in query stmt", tables.size(), query_fields.size());

  Table *default_table = nullptr;
  if (tables.size() == 1) {
    default_table = tables[0];
  }

  // join 连接条件
  std::vector<FilterStmt *> join_filter_stmts;
  if (!select_sql.join_conditions.empty()) {
    for (const auto &item : select_sql.join_conditions) {
      FilterStmt *filter_stmt = nullptr;
      RC          rc =
          FilterStmt::create(db, default_table, &table_map, item.data(), static_cast<int>(item.size()), filter_stmt);
      if (rc != RC::SUCCESS) {
        LOG_WARN("cannot construct filter stmt");
        return rc;
      }
      join_filter_stmts.emplace_back(filter_stmt);
    }
  }

  // create filter statement in `where` statement
  FilterStmt *filter_stmt = nullptr;
  RC          rc          = FilterStmt::create(db,
      default_table,
      &table_map,
      select_sql.conditions.data(),
      static_cast<int>(select_sql.conditions.size()),
      filter_stmt);
  if (rc != RC::SUCCESS) {
    LOG_WARN("cannot construct filter stmt");
    return rc;
  }

  // 校验排序字段
  std::vector<OrderField> order_fields;
  for (const auto &order_by_item : select_sql.order_by_items) {
    Table *table = nullptr;
    const FieldMeta *field_meta;
    // 找表
    if (common::is_blank(order_by_item.attr.relation_name.c_str())) {
      if (tables.size() != 1) {
        LOG_WARN("invalid. I do not know the attr's table. attr=%s", order_by_item.attr.attribute_name.c_str());
        return RC::SCHEMA_FIELD_MISSING;
      }
      table = tables[0];
    } else {
      table = table_map[order_by_item.attr.relation_name];
    }

    if(table == nullptr){
      LOG_WARN("can not find table : %s", order_by_item.attr.relation_name.c_str());
      return RC::SCHEMA_TABLE_NOT_EXIST;
    }

    // 找字段
    field_meta = table->table_meta().field(order_by_item.attr.attribute_name.c_str());
    if (nullptr == field_meta) {
      LOG_WARN("no such field. field=%s.%s.%s", db->name(), table->name(), order_by_item.attr.attribute_name.c_str());
      return RC::SCHEMA_FIELD_MISSING;
    }

    // 校验完成
    order_fields.emplace_back(OrderField(table, field_meta, order_by_item.order_type));
  }

  // everything alright
  SelectStmt *select_stmt = new SelectStmt();
  // TODO add expression copy
  select_stmt->tables_.swap(tables);
  // 聚合字段和非聚合字段选一个存进去
  select_stmt->query_fields_.swap(!agg_fields_.empty() ? agg_fields_ : query_fields);
  select_stmt->order_fields_.swap(order_fields);
  select_stmt->filter_stmt_       = filter_stmt;
  select_stmt->join_filter_stmts_ = join_filter_stmts;
  stmt                            = select_stmt;
  return RC::SUCCESS;
}
