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
// Created by Wangyunlai on 2022/07/05.
//

#pragma once

#include <utility>

#include "storage/table/table.h"
#include "storage/field/field_meta.h"

/**
 * @brief 字段
 *
 */
class Field
{
public:
  Field() = default;
  Field(const Table *table, const FieldMeta *field, std::string alias = "", AggFunc agg_func = AggFunc::A_NULL)
      : table_(table), field_(field), agg_func_(agg_func), alias_(std::move(alias))
  {}
  Field(const Field &) = default;

  const Table     *table() const { return table_; }
  const FieldMeta *meta() const { return field_; }

  AttrType attr_type() const { return field_->type(); }

  const AggFunc agg_func() const { return agg_func_; }

  const char *table_name() const { return table_->name(); }
  const char *field_name() const { return field_->name(); }
  const char *alias() const { return alias_.c_str(); }

  void set_table(const Table *table) { this->table_ = table; }
  void set_field(const FieldMeta *field) { this->field_ = field; }

  void set_int(Record &record, int value);
  int  get_int(const Record &record);

  const char *get_data(const Record &record);

protected:
  const Table     *table_    = nullptr;
  const FieldMeta *field_    = nullptr;
  AggFunc          agg_func_ = AggFunc::A_NULL;
  std::string      alias_;
};

class OrderField : public Field
{
public:
  OrderField();
  OrderField(const Table *table, const FieldMeta *field, OrderByType order_type)
      : Field(table, field), order_type_(order_type)
  {}
  OrderByType order_type() { return order_type_; }
  OrderByType order_type_ = OrderByType::SORT_ASC;
};
