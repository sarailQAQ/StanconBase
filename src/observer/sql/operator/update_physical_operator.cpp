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

#include <utility>
#include "sql/stmt/update_stmt.h"
#include "storage/table/table.h"
#include "storage/trx/trx.h"

using namespace std;

UpdatePhysicalOperator::UpdatePhysicalOperator(Table *table, std::vector<std::string> field_names, std::vector<Value> values)
{
  table_ = table;

  field_names_ = std::move(field_names);

  values_ = std::move(values);
}

UpdatePhysicalOperator::~UpdatePhysicalOperator() = default;

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
    if (field_names_.empty() || values_.size() != field_names_.size()) {
      rc = RC::EMPTY;
      return rc;
    }

    std::vector<int> idxs;
    std::vector<const FieldMeta*> field_metas;
    for (auto& field_name : field_names_) {
      int index;
      const FieldMeta* field_meta = table_->table_meta().field(field_name.c_str(),index);
      if (field_meta == nullptr) {
        rc = RC::EMPTY;
        return rc;
      }

      field_metas.push_back(field_meta);
      idxs.push_back(index);
    }

//    int offset = field_meta->offset();

    rc = trx_->update_record(table_, record, field_metas, idxs, values_);
//    rc = trx_->update_record(table_, record, values_, offset);
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
//    rc = row_tuple->set_cell(to_update_field_meta,&values_);
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
