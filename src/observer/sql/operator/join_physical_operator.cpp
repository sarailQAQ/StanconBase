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
// Created by WangYunlai on 2022/12/30.
//

#include "sql/operator/join_physical_operator.h"

NestedLoopJoinPhysicalOperator::NestedLoopJoinPhysicalOperator() {}
NestedLoopJoinPhysicalOperator::NestedLoopJoinPhysicalOperator(std::vector<std::unique_ptr<Expression>> exprs)
{
  // 连接条件
  if (exprs.size() != 0) {
    expression_ = std::move(exprs.front());
    ASSERT(expression_->value_type() == BOOLEANS, "join's condition should be BOOLEAN type");
  }
}

RC NestedLoopJoinPhysicalOperator::open(Trx *trx)
{
  if (children_.size() != 2) {
    LOG_WARN("nlj operator should have 2 children");
    return RC::INTERNAL;
  }

  RC rc         = RC::SUCCESS;
  left_         = children_[0].get();
  right_        = children_[1].get();
  right_closed_ = true;
  round_done_   = true;

  rc   = left_->open(trx);
  trx_ = trx;

  rc = right_->open(trx_);
  while (RC::SUCCESS == (right_->next())) {
    auto temp = right_->current_tuple();
    right_tuple_cache_.emplace_back(std::move(temp->clone()));
  }
  rc = right_->close();

  return rc;
}

RC NestedLoopJoinPhysicalOperator::next()
{
  RC rc = RC::SUCCESS;
  while (true) {
    // 右边没轮完，直接查右表下一个
    if (!round_done_) {
      rc = right_next();
      if (rc == RC::RECORD_EOF) {
        return RC::RECORD_EOF;
      }

      rc = check_expr(joined_tuple_);
      // 不满足join条件
      if (rc != RC::SUCCESS) {
        continue;
      }
      return rc;  // got one tuple from right
    }

    // 右边轮完了就左表查下一个
    rc = left_next();
    if (rc != RC::SUCCESS) {
      return rc;
    }

    rc = right_next();
    if (rc != RC::SUCCESS) {
      return rc;
    }
    rc = check_expr(joined_tuple_);
    // 不满足join条件
    if (rc != RC::SUCCESS) {
      continue;
    }
    return rc;
  }
  return rc;
}

RC NestedLoopJoinPhysicalOperator::close()
{
  RC rc = left_->close();
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to close left oper. rc=%s", strrc(rc));
  }

  return rc;
}

Tuple *NestedLoopJoinPhysicalOperator::current_tuple() { return &joined_tuple_; }

RC NestedLoopJoinPhysicalOperator::left_next()
{
  RC rc = RC::SUCCESS;
  rc    = left_->next();
  if (rc != RC::SUCCESS) {
    return rc;
  }

  left_tuple_ = left_->current_tuple();
  joined_tuple_.set_left(left_tuple_);
  return rc;
}

RC NestedLoopJoinPhysicalOperator::right_next()
{
  RC rc = RC::SUCCESS;
  if (right_tuple_cache_.empty()) {
    return RC::RECORD_EOF;
  }

  if (round_done_) {
    round_done_  = false;
    right_index_ = 0;
  }

  right_tuple_ = right_tuple_cache_[right_index_++];
  joined_tuple_.set_right(right_tuple_);

  if (right_index_ == right_tuple_cache_.size()) {
    round_done_ = true;
  }
  return rc;
}

RC NestedLoopJoinPhysicalOperator::check_expr(JoinedTuple tuple)
{
  if (!expression_) {
    return RC::SUCCESS;
  }
  RC    rc = RC::SUCCESS;
  Value value;
  // 对tuple进行过滤，过滤条件是expression_
  rc = expression_->get_value(tuple, value);
  if (rc != RC::SUCCESS) {
    return rc;
  }
  if (value.get_boolean()) {
    return rc;
  }
  return RC::RECORD_NEXT;
}
