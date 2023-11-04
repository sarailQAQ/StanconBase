//
// Created by weizhi on 23-11-3.
//

#include "sub_query_expression.h"

RC SubQueryExpr::get_value(Trx *trx, const Tuple &tuple, Value &value)
{
  RC rc = RC::SUCCESS;
  // 第一次执行缓存记录
  if (!cached_) {
    sub_opt_->open(trx);
    while ((rc = sub_opt_->next()) != RC::RECORD_EOF) {
      auto  tmp_tuple = sub_opt_->current_tuple();
      Value tmp_value;
      tmp_tuple->cell_at(0, tmp_value);  // 只要第一个
      values_.emplace_back(tmp_value);
    }
    sub_opt_->close();
    cached_ = true;
    reset();

    if(rc != RC::RECORD_EOF){
      LOG_WARN("failed to get value of SubQueryExpr. rc=%s", strrc(rc));
      return rc;
    }
  }

  if (cur_index_ < values_.size()) {
    value = values_[cur_index_++];
    return RC::SUCCESS;
  }
  reset();
  return RC::RECORD_EOF;
}


RC       SubQueryExpr::try_get_value(Value &value) const { return RC::UNIMPLENMENT; }
