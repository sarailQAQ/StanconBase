/* Copyright (c) 2021OceanBase and/or its affiliates. All rights reserved.
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

#include "sql/stmt/insert_stmt.h"
#include "common/log/log.h"
#include "storage/db/db.h"
#include "storage/table/table.h"
#include "common/date.h"

InsertStmt::InsertStmt(Table *table, const Value *values, int value_amount)
    : table_(table), values_(values), value_amount_(value_amount)
{}

RC InsertStmt::create(Db *db, InsertSqlNode &inserts, Stmt *&stmt)
{
  const char *table_name = inserts.relation_name.c_str();
  if (nullptr == db || nullptr == table_name || inserts.values.empty()) {
    LOG_WARN("invalid argument. db=%p, table_name=%p, value_num=%d",
        db, table_name, static_cast<int>(inserts.values.size()));
    return RC::INVALID_ARGUMENT;
  }

  // check whether the table exists
  Table *table = db->find_table(table_name);
  if (nullptr == table) {
    LOG_WARN("no such table. db=%s, table_name=%s", db->name(), table_name);
    return RC::SCHEMA_TABLE_NOT_EXIST;
  }

  // check the fields number
//  const Value *values = inserts.values.data(); // const类型无法修改，所以不用
  const int value_num = static_cast<int>(inserts.values.size());
  const TableMeta &table_meta = table->table_meta();
  const int field_num = table_meta.field_num() - table_meta.sys_field_num();
  if (field_num != value_num) {
    LOG_WARN("schema mismatch. value num=%d, field num in schema=%d", value_num, field_num);
    return RC::SCHEMA_FIELD_MISSING;
  }

  // check fields type
  const int sys_field_num = table_meta.sys_field_num();
  for (int i = 0; i < value_num; i++) {
    const FieldMeta *field_meta = table_meta.field(i + sys_field_num);
    const AttrType field_type = field_meta->type();
    const AttrType value_type = inserts.values[i].attr_type();

    // 校验null
    if(value_type == AttrType::NULLS){
      if(field_meta->is_nullable()){
        continue;
      }
      LOG_ERROR("Unacceptable operation: put NULL into a NOT NULL field");
      return RC::SCHEMA_FIELD_NOT_NULL;
    }

    // 日期类型特判
    if(field_type == AttrType::DATES && value_type == AttrType::CHARS){
      int date_num = -1;
      RC rc = string_to_date(inserts.values[i].data(),date_num);
      if(rc != RC::SUCCESS){
        LOG_WARN("date type parse err. table=%s, field=%s, field type=%d, value_type=%d",
          table_name, field_meta->name(), field_type, value_type);
        return rc;
      }
      auto new_date = Value(date_num);
      new_date.set_type(AttrType::DATES);
      inserts.values[i] = new_date;
      continue;
    }
    //TEXT类型特判
    if(field_type == AttrType::TEXTS && value_type == AttrType::CHARS)
    {
      auto new_text = Value();
      new_text.set_type(AttrType::TEXTS);
      new_text.set_text(inserts.values.data()[i].data());
      inserts.values[i] = new_text;
      continue;
    }
    if (field_type != value_type) {  // TODO try to convert the value type to field type
      LOG_WARN("field type mismatch. table=%s, field=%s, field type=%d, value_type=%d",
          table_name, field_meta->name(), field_type, value_type);
      return RC::SCHEMA_FIELD_TYPE_MISMATCH;
    }
  }

  // everything alright
  stmt = new InsertStmt(table, inserts.values.data(), value_num);
  return RC::SUCCESS;
}
