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

#pragma once

#include "sql/parser/parse.h"
#include "sql/operator/physical_operator.h"

/**
 * @brief order by 物理算子
 * @details 子算子是project，先拿到所有数据，存起来排序，然后再输出
 * @ingroup PhysicalOperator
 */
class OrderByPhysicalOperator : public PhysicalOperator
{
public:
  OrderByPhysicalOperator();
  OrderByPhysicalOperator(
      std::vector<std::unique_ptr<Expression>> expressions, std::vector<OrderByType> order_by_types);
  ~OrderByPhysicalOperator() {
//    for (const auto &item : tuple_cache_){
//      delete item;
//    }
//    tuple_cache_.clear();
  }

  PhysicalOperatorType type() const override { return PhysicalOperatorType::ORDER_BY; }

  RC     open(Trx *trx) override;
  RC     next() override;
  RC     close() override;
  Tuple *current_tuple() override;

private:
  Trx                                     *trx_ = nullptr;
  std::vector<std::unique_ptr<Expression>> expressions_;     // 基于某个表达式排序
  std::vector<OrderByType>                 order_by_types_;  // 对应表达式的排序方式，升序还是降序
  std::vector<Tuple *>                     tuple_cache_;  // 数据缓存，先将数据全部载入，再进行排序
  ProjectTuple *tuple_;
  int current_index_ = 0;       // 当前next已经遍历到哪个位置
};
