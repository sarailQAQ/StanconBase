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
// Created by Weizhi on 2023/10/25.
//

#pragma once

#include "sql/operator/logical_operator.h"

/**
 * @brief 逻辑算子，用于执行order by语句
 * @ingroup LogicalOperator
 */
class OrderByLogicalOperator : public LogicalOperator
{
public:
  OrderByLogicalOperator(std::vector<std::unique_ptr<Expression>> expressions, std::vector<OrderByType> order_by_types)
  {
    order_by_types_ = std::move(order_by_types);
    expressions_    = std::move(expressions);
  }
  ~OrderByLogicalOperator() {};

  LogicalOperatorType type() const override { return LogicalOperatorType::ORDER_BY; }

  std::vector<OrderByType> &order_by_types() { return order_by_types_; }

private:
  std::vector<OrderByType> order_by_types_;  // 对应表达式的排序方式，升序还是降序
  // expressions_ 里面存 orderby by 的 Field表达式 table.col
};
