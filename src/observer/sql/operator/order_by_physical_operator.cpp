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
// Created by Weizhi on 2023/10/25.
//

#include "common/log/log.h"
#include "sql/operator/order_by_physical_operator.h"
#include "storage/record/record.h"
#include "sql/stmt/filter_stmt.h"
#include "storage/field/field.h"

OrderByPhysicalOperator::OrderByPhysicalOperator(
    std::vector<std::unique_ptr<Expression>> expressions, std::vector<OrderByType> order_by_types)
    : expressions_(std::move(expressions)), order_by_types_(std::move(order_by_types))
{}

RC OrderByPhysicalOperator::open(Trx *trx)
{
  RC rc = RC::SUCCESS;
  trx_  = trx;

  rc = children_[0]->open(trx);
  if (rc != RC::SUCCESS) {
    LOG_WARN("order by 子算子开启失败");
    return rc;
  }
  while (RC::SUCCESS == (children_[0]->next())) {
    auto temp = children_[0]->current_tuple();
    tuple_cache_.emplace_back(std::move(temp->clone()));
  }
  rc                   = children_[0]->close();
  auto &expressions    = expressions_;
  auto &order_by_types = order_by_types_;
  // 开始基于各个比较字段排序
  // 自定义比较逻辑
  auto compareTuple = [&expressions, order_by_types](const Tuple *tuple1, const Tuple *tuple2) {
    Value left;
    Value right;
    for (int i = 0; i < order_by_types.size(); i++) {
      auto &sort_expr = expressions[i];
      sort_expr->get_value(*tuple1, left);
      sort_expr->get_value(*tuple2, right);
      auto res = left.compare(right);
      if (res == 0) {
        continue;
      }
      return order_by_types[i] == OrderByType::SORT_ASC ? res < 0 : res > 0;
    }
    return false;
  };

  std::sort(tuple_cache_.begin(), tuple_cache_.end(), compareTuple);

  if (rc != RC::SUCCESS) {
    LOG_WARN("order by 子算子关闭失败");
    return rc;
  }
  return rc;
}

RC OrderByPhysicalOperator::next()
{
  if (current_index_ == tuple_cache_.size()) {
    return RC::RECORD_EOF;
  }
  tuple_ = static_cast<ProjectTuple *>(tuple_cache_[current_index_++]);

  return RC::SUCCESS;
}

RC OrderByPhysicalOperator::close() { return RC::SUCCESS; }

Tuple *OrderByPhysicalOperator::current_tuple() { return tuple_; }
