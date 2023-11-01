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

UpdatePhysicalOperator::UpdatePhysicalOperator(Table *table, const char * field_name, Value value)
{
  table_ = table;
  char *tmp = (char *)malloc(sizeof(char) * (strlen(field_name) + 1));
  strcpy(tmp, field_name);
  field_name_ = tmp;

  value_ = value;
}

UpdatePhysicalOperator::~UpdatePhysicalOperator() {
  if (field_name_ != nullptr) {
    delete field_name_;
  }
}

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

    RowTuple *row_tuple = static_cast<RowTuple *>(tuple);
    Record &record = row_tuple->record();
    if (*field_name_ == 0) {
      rc = RC::EMPTY;
      return rc;
    }
    int index;
    const FieldMeta* feildmeta = table_->table_meta().field(field_name_,index);
    if (feildmeta == nullptr)
    {
      rc = RC::EMPTY;
      return rc;
    }
    int offset = feildmeta->offset();
    rc = trx_->update_record(table_, record, feildmeta, index, value_);
//    rc = trx_->update_record(table_, record, value_, offset);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to delete record: %s", strrc(rc));
      return rc;
    }

////    删除旧记录
//    rc = trx_->delete_record(table_, record);
//    if (rc != RC::SUCCESS) {
//      LOG_WARN("failed to delete record: %s", strrc(rc));
//      return rc;
//    }
//    auto to_update_field_meta = table_->table_meta().field(field_name_);
////    修改记录
//    rc = row_tuple->set_cell(to_update_field_meta,&value_);
//    if (rc != RC::SUCCESS) {
//      LOG_WARN("failed to update record: %s", strrc(rc));
//      return rc;
//    }
//    // 添加新记录
//    rc = trx_->insert_record(table_,row_tuple->record());
//    if (rc != RC::SUCCESS) {
//      LOG_WARN("failed to insert record: %s", strrc(rc));
//      return rc;
//    }
  }


  return RC::RECORD_EOF;
}

RC UpdatePhysicalOperator::close()
{
  return RC::SUCCESS;
}
