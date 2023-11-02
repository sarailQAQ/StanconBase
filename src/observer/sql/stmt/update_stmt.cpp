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
// Created by Wangyunlai on 2022/5/22.
//

#include "sql/stmt/update_stmt.h"

#include <utility>
#include "sql/stmt/filter_stmt.h"
#include "common/log/log.h"
#include "storage/db/db.h"
#include "storage/table/table.h"
#include "common/date.h"

UpdateStmt::UpdateStmt(Table *table, std::vector<std::string> field_names, std::vector<Value> value, FilterStmt *filter_stmt)
    : table_(table), field_names_(std::move(field_names)),
      values_(std::move(value)), filter_stmt_(filter_stmt)
{}

RC UpdateStmt::create(Db *db, const UpdateSqlNode &update, Stmt *&stmt)
{
  const char *table_name = update.relation_name.c_str();
  if (nullptr == db || nullptr == table_name || update.update_set.names.empty()
      || update.update_set.values.size() != update.update_set.names.size()) {
    LOG_WARN("invalid argument for update. db=%p, table_name=%p",
        db, table_name);
    return RC::INVALID_ARGUMENT;
  }

  // check whether the table exists
  Table *table = db->find_table(table_name);
  if (nullptr == table) {
    LOG_WARN("no such table. db=%s, table_name=%s", db->name(), table_name);
    return RC::SCHEMA_TABLE_NOT_EXIST;
  }

  std::vector<std::string> field_names;
  std::vector<Value> values;

  //  字段校验
  for (int i = 0; i < update.update_set.names.size(); i++) {
    auto& attribute_name = update.update_set.names[i];
    auto& value = update.update_set.values[i];
    Value update_value(value);

    const TableMeta &table_meta    = table->table_meta();
    auto field_meta    = table_meta.field(attribute_name.c_str());

    // 字段不存在
    if(field_meta == nullptr) {
      LOG_WARN("no such table field. db=%s, table_name=%s, field_names=%s", db->name(), table_name,attribute_name.c_str());
      return RC::SCHEMA_FIELD_NOT_EXIST;
    }

    // 日期类型特判
    if (field_meta->type() == AttrType::DATES && value.attr_type() == AttrType::CHARS) {
      int date_num = -1;
      RC  rc = string_to_date(value.data(), date_num);
      if (rc != RC::SUCCESS) {
        LOG_WARN("date type parse err. table=%s, field=%s, field type=%d, value_type=%d",
          table_name, field_meta->name(), field_meta->type(), value.attr_type());
        return rc;
      }
      update_value = Value(date_num);
      update_value.set_type(AttrType::DATES);
    }

    // TEXT类型特殊判断
    if(field_meta->type() ==  AttrType::TEXTS && value.attr_type() == AttrType::CHARS){
      update_value.set_text(update_value.data());
      update_value.set_type(AttrType::TEXTS);
    }

    // null 特判
    if(!field_meta->is_nullable() && update_value.attr_type() == AttrType::NULLS){
      LOG_WARN("field can not be set null");
      return RC::SCHEMA_FIELD_NOT_NULL;
    }

    if (update_value.attr_type() != NULLS && field_meta->type() != update_value.attr_type()) {
      LOG_WARN("field type mismatch. table=%s, field=%s, field type=%d, value_type=%d",
          table_name, field_meta->name(), field_meta->type(), value.attr_type());
      return RC::SCHEMA_FIELD_TYPE_MISMATCH;
    }

    field_names.emplace_back(field_meta->name());
    values.push_back(update_value);
  }

  // filter stmt
  std::unordered_map<std::string, Table *> table_map;
  table_map.insert(std::pair<std::string, Table *>(std::string(table_name), table));
  FilterStmt *filter_stmt = nullptr;
  RC rc = FilterStmt::create(
      db, table, &table_map, update.conditions.data(), static_cast<int>(update.conditions.size()), filter_stmt);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to create filter statement. rc=%d:%s", rc, strrc(rc));
    return rc;
  }

  // 只支持一个字段更新
  stmt = new UpdateStmt(table, field_names, values,  filter_stmt);
  return RC::SUCCESS;
}
