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
// Created by Weizhi on 2023/10/16.
//

#include "sql/operator/update_physical_operator.h"
#include "sql/stmt/update_stmt.h"
#include "storage/table/table.h"
#include "storage/trx/trx.h"

using namespace std;

UpdatePhysicalOperator::UpdatePhysicalOperator(Table *table,const char * field_name, Value *value)
    : table_(table), field_name_(field_name), value_(value)
{}

RC UpdatePhysicalOperator::open(Trx *trx)
{
  if (children_.empty()) {
    return RC::SUCCESS;
  }

  std::unique_ptr<PhysicalOperator> &child = children_[0];
  RC rc = child->open(trx);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to open child operator: %s", strrc(rc));
    return rc;
  }

  trx_ = trx;

  return rc;
}

RC UpdatePhysicalOperator::next()
{
  RC rc = RC::SUCCESS;
  if (children_.empty()) {
    return RC::RECORD_EOF;
  }

  PhysicalOperator *child = children_[0].get();
  while (RC::SUCCESS == (rc = child->next())) {
    Tuple *tuple = child->current_tuple();
    if (nullptr == tuple) {
      LOG_WARN("failed to get current record: %s", strrc(rc));
      return rc;
    }
    auto to_update_field_meta = table_->table_meta().field(field_name_);


    // 提取旧数据并插入需要修改的新数据
    std::vector<Value> new_values;
    for (int i = 0; i < tuple->cell_num();i++){
      Value v;
      
      tuple->cell_at(i,v);
      new_values.emplace_back(v);
    }

    Record new_record;
    RC rc = table_->make_record(1,new_values.data(),new_record);
    RowTuple *row_tuple = static_cast<RowTuple *>(tuple);
    Record &record = row_tuple->record();


    rc = trx_->delete_record(table_, record);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to delete record: %s", strrc(rc));
      return rc;
    }
    rc = trx_->insert_record(table_,new_record);

  }


  return RC::RECORD_EOF;
}

RC UpdatePhysicalOperator::close()
{
  return RC::SUCCESS;
}
