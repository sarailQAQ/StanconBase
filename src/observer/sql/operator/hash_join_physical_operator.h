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
// Created by Weizhi on 2023/10/20.
//

#pragma once

#include "sql/parser/parse.h"
#include "sql/operator/physical_operator.h"
#include <unordered_map>

/**
 * @brief 哈希连接 物理算子
 * @details
 * @ingroup HashJoinPhysicalOperator
 */
class HashJoinPhysicalOperator : public PhysicalOperator
{
public:
  HashJoinPhysicalOperator();
  virtual ~HashJoinPhysicalOperator() = default;

  PhysicalOperatorType type() const override
  {
    return PhysicalOperatorType::HASH_JOIN;
  }

  RC open(Trx *trx) override;
  RC next() override;
  RC close() override;
  Tuple *current_tuple() override;

private:
  RC left_next();   //! 左表遍历下一条数据
  RC right_next();  //! 右表遍历下一条数据，如果上一轮结束了就重新开始新的一轮

private:
  Trx *trx_ = nullptr;


  //! 左表右表的真实对象是在PhysicalOperator::children_中，这里是为了写的时候更简单
  PhysicalOperator *left_ = nullptr;
  PhysicalOperator *right_ = nullptr;
  Tuple *left_tuple_ = nullptr;
  Tuple *right_tuple_ = nullptr;
  JoinedTuple joined_tuple_;  //! 当前关联的左右两个tuple
  bool round_done_ = true;    //! 右表遍历的一轮是否结束
  bool right_closed_ = true;  //! 右表算子是否已经关闭
};
