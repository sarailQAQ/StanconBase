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
// Created by WangYunlai on 2022/07/01.
//

#include "common/log/log.h"
#include "sql/operator/project_physical_operator.h"
#include "storage/record/record.h"
#include "storage/table/table.h"

RC ProjectPhysicalOperator::open(Trx *trx)
{
  if (children_.empty()) {
    return RC::SUCCESS;
  }

  PhysicalOperator *child = children_[0].get();
  RC                rc    = child->open(trx);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to open child operator: %s", strrc(rc));
    return rc;
  }

  has_agg_func_ = false;
  for (const auto &spece : tuple_.speces()) {
    if (spece->agg_func() != AggFunc::A_NULL) {
      has_agg_func_ = true;
      break;
    }
  }
  return RC::SUCCESS;
}

RC ProjectPhysicalOperator::next()
{
  if (children_.empty()) {
    return RC::RECORD_EOF;
  }
  return children_[0]->next();
}

RC ProjectPhysicalOperator::close()
{
  if (!children_.empty()) {
    children_[0]->close();
  }
  return RC::SUCCESS;
}
Tuple *ProjectPhysicalOperator::current_tuple()
{
  RC rc = RC::SUCCESS;
  // 不存在聚合函数
  if (!has_agg_func_) {
    tuple_.set_tuple(children_[0]->current_tuple());
    return &tuple_;
  }
  auto               cur_tuple = children_[0]->current_tuple();
  auto               speces = tuple_.speces();
  std::vector<Value> values;        // 各个值（根据函数类型更新）
  std::vector<int>   values_count;  // 各个值的计数器
  Value              tmp;
  // 初始化第一行
  for (size_t i = 0; i < tuple_.cell_num(); i++) {
    cur_tuple->find_cell(*speces[i], tmp);
    values.emplace_back(tmp);
    if (tmp.attr_type() != AttrType::NULLS) {
      values_count.emplace_back(1);
    }
  }
  // 读取出所有行
  while ((rc = next()) == RC::SUCCESS) {
    cur_tuple = children_[0]->current_tuple();

    for (size_t i = 0; i < tuple_.cell_num(); i++) {
      cur_tuple->find_cell(*speces[i], tmp);
      // 字段为NULL 不参与 聚合计算
      if (tmp.attr_type() == AttrType::NULLS) {
        continue;
      }
      values_count[i]++;
      switch (speces[i]->agg_func()) {
        case AggFunc::A_COUNT: break; // 直接用计数器
        case AggFunc::A_AVG: // AVG 和 SUM 都是求和
        case AggFunc::A_SUM: {
          if(tmp.attr_type() == AttrType::FLOATS){
            values[i].set_float(values[i].get_float() + tmp.get_float()) ;
          } else{
            values[i].set_int(values[i].get_int() + tmp.get_int()) ;
          }
        } break;
        case AggFunc::A_MAX: {
          if (values[i].compare(tmp) < 0) {
            values[i] = tmp;
          }
        } break;
        case AggFunc::A_MIN: {
          if (values[i].compare(tmp) > 0) {
            values[i] = tmp;
          }
        } break;
      }
    }
  }
  // 特殊处理 count 和 vag
  for (size_t i = 0; i < tuple_.cell_num(); i++) {
    if (speces[i]->agg_func() == AggFunc::A_COUNT) {
      values[i] = Value(values_count[i]);
    }
    if (speces[i]->agg_func() == AggFunc::A_AVG) {
      values[i].set_float(values[i].get_float() / values_count[i]);
    }
  }

  // 封装数据
  ValueListTuple *value_list = new ValueListTuple;
  value_list->set_cells(values);
  tuple_.set_tuple(value_list);
  return &tuple_;
}

void ProjectPhysicalOperator::add_projection(const Field &field)
{
  // 对单表来说，展示的(alias) 字段总是字段名称，
  // 对多表查询来说，展示的alias 需要带表名字
  TupleCellSpec *spec = new TupleCellSpec(field.table_name(), field.meta()->name(), field.meta()->name(),field.agg_func());
  tuple_.add_cell_spec(spec);
}
