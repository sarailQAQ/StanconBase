/* Copyright (c) OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

//
// Created by Weizhi on 2022/12/26.
//

#pragma once

#include "sql/operator/logical_operator.h"

/**
 * @brief 逻辑算子，用于执行update语句
 * @ingroup LogicalOperator
 */
class UpdateLogicalOperator : public LogicalOperator
{
public:
  UpdateLogicalOperator(Table *table,const char *field_name, Value value);
  ~UpdateLogicalOperator() override;

  LogicalOperatorType type() const override
  {
    return LogicalOperatorType::UPDATE;
  }
  Table *table() const
  {
    return table_;
  }
  char *field_name() const
  {
    return field_name_;
  }
  Value &value()
  {
    return value_;
  }

private:
  Table *table_ = nullptr; // 需要修改的表
  char *field_name_ = nullptr; // 需要修改的字段
  Value value_; // 修改后的值
};
