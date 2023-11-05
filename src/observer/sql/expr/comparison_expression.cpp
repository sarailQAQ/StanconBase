//
// Created by weizhi on 23-11-3.
//

#include "comparison_expression.h"

using namespace std;

ComparisonExpr::ComparisonExpr(CompOp comp, unique_ptr<Expression> left, unique_ptr<Expression> right)
{
  comp_ = comp;
  //  类型相同不用转
  if(left->value_type() == right->value_type()){
    left_ = std::move(left);
    right_ = std::move(right);
    return;
  }

  // 子查询暂时不转
  if(left->type() == ExprType::SUB_QUERY || right->type() == ExprType::SUB_QUERY){
    left_ = std::move(left);
    right_ = std::move(right);
    return;
  }

  // int、char、日期 遇到浮点 都转浮点
  if(left->value_type() == AttrType::FLOATS){
    left_ = std::move(left);
    right_ = std::unique_ptr<Expression>(new CastExpr(std::move(right),AttrType::FLOATS));
    return;
  }
  if(right->value_type() == AttrType::FLOATS){
    left_ = std::unique_ptr<Expression>(new CastExpr(std::move(left),AttrType::FLOATS));
    right_ = std::move(right);
    return;
  }

  // 不是浮点 有整形就转整形
  if(left->value_type() == AttrType::INTS){
    left_ = std::move(left);
    right_ = std::unique_ptr<Expression>(new CastExpr(std::move(right),AttrType::INTS));
    return;
  }
  if(right->value_type() == AttrType::INTS){
    left_ = std::unique_ptr<Expression>(new CastExpr(std::move(left),AttrType::INTS));
    right_ = std::move(right);
    return;
  }


  // 匹配不上转换规则，也不转
  left_ = std::move(left);
  right_ = std::move(right);

}

ComparisonExpr::~ComparisonExpr()
{}

RC ComparisonExpr::compare_value(const Value &left, const Value &right, bool &result) const
{
  // 如果存在null参与比较，同时比较符不是is null  也不是 is not null 则直接判断为false
  if((comp_ != IS_NULL && comp_ != NOT_NULL) && (left.attr_type() == NULLS || right.attr_type() == NULLS)){
    result = false;
    return  RC::SUCCESS;
  }

  RC rc = RC::SUCCESS;
  int cmp_result = left.compare(right);
  result = false;
  switch (comp_) {
    case EQUAL_TO: {
      result = (0 == cmp_result);
    } break;
    case LESS_EQUAL: {
      result = (cmp_result <= 0);
    } break;
    case NOT_EQUAL: {
      result = (cmp_result != 0);
    } break;
    case LESS_THAN: {
      result = (cmp_result < 0);
    } break;
    case GREAT_EQUAL: {
      result = (cmp_result >= 0);
    } break;
    case GREAT_THAN: {
      result = (cmp_result > 0);
    } break;
    //实现LIKE值比较
    //在LIKE中只有左值匹配右值 'ta%' LIKE 't' -> TURE
    case LIKE: {
      result = left.like(right);
    } break;
    case NOT_LIKE: {
      result = !left.like(right);
    } break;
    case IS_NULL: {
      AttrType left_type = left.attr_type();
      AttrType right_type = right.attr_type();
      result = left_type == right_type && left_type == NULLS;
    } break;
    case NOT_NULL: {
      AttrType left_type = left.attr_type();
      AttrType right_type = right.attr_type();
      result = (left_type == NULLS || right_type == NULLS) && (left_type != NULLS || right_type != NULLS);
    } break;
    default: {
      LOG_WARN("unsupported comparison. %d", comp_);
      rc = RC::INTERNAL;
    } break;
  }

  return rc;
}

RC ComparisonExpr::try_get_value(Value &cell) const
{
  if (left_->type() == ExprType::VALUE && right_->type() == ExprType::VALUE) {
    ValueExpr *left_value_expr = static_cast<ValueExpr *>(left_.get());
    ValueExpr *right_value_expr = static_cast<ValueExpr *>(right_.get());
    const Value &left_cell = left_value_expr->get_value();
    const Value &right_cell = right_value_expr->get_value();

    bool value = false;
    RC rc = compare_value(left_cell, right_cell, value);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to compare tuple cells. rc=%s", strrc(rc));
    } else {
      cell.set_boolean(value);
    }
    return rc;
  }

  return RC::INVALID_ARGUMENT;
}

RC ComparisonExpr::get_value(const Tuple &tuple, Value &value) const
{
  Value left_value;
  Value right_value;

  RC rc = left_->get_value(tuple, left_value);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to get value of left expression. rc=%s", strrc(rc));
    return rc;
  }
  rc = right_->get_value(tuple, right_value);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to get value of right expression. rc=%s", strrc(rc));
    return rc;
  }

  bool bool_value = false;
  rc = compare_value(left_value, right_value, bool_value);
  if (rc == RC::SUCCESS) {
    value.set_boolean(bool_value);
  }
  return rc;
}

RC ComparisonExpr::get_value(Trx *trx, const Tuple &tuple, Value &value)
{
  RC    rc = RC::SUCCESS;
  Value left_value;
  Value right_value;

  // 1. (not) exists
  if (comp_ == EXISTS || comp_ == NOT_EXISTS) {
    ASSERT(right_->type() == ExprType::SUB_QUERY, "right exp must be SUB_QUERY");
    rc = right_->get_value(trx, tuple, right_value);
    if (rc != RC::SUCCESS && rc != RC::RECORD_EOF) {
      LOG_WARN("failed to get value of right expression. rc=%s", strrc(rc));
      return rc;
    }
    // 如果comp_是存在，则取到值返回true，如果是不存在则相反
    value.set_boolean(comp_ == EXISTS ? rc == RC::SUCCESS : rc == RC::RECORD_EOF);
    static_cast<SubQueryExpr *>(right_.get())->reset();  // 重置子查询
    return RC::SUCCESS;
  }

  // 2. (not) in
  if (comp_ == IN || comp_ == NOT_IN) {
    ASSERT(left_->type() == ExprType::VALUE ||left_->type() == ExprType::FIELD , "left exp must be value or field");
    ASSERT(right_->type() == ExprType::SUB_QUERY, "right exp must be SUB_QUERY");
    rc = left_->get_value(trx, tuple, left_value);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to get value of left expression. rc=%s", strrc(rc));
      return rc;
    }
    bool in = false;
    while ((rc = right_->get_value(trx, tuple, right_value)) == RC::SUCCESS) {
      if(left_value.compare(right_value) == 0){
        in = true;
        break;
      }
    }

    // 如果子查询有多个表达式直接返回错误,（目前的逻辑要在子查询执行完毕后判断）
    if(static_cast<SubQueryExpr *>(left_.get())->has_multi_res()){
      LOG_WARN("not support multi field for sub-query");
      return RC::INVALID_ARGUMENT;
    }

    value.set_boolean(comp_ == IN ? in : !in);
    if (left_->type() == ExprType::SUB_QUERY) {
      static_cast<SubQueryExpr *>(left_.get())->reset();  // 重置子查询
    }
    static_cast<SubQueryExpr *>(right_.get())->reset();  // 重置子查询,下次查询就可以从头开始
    return RC::SUCCESS;
  }

  // 3. other comp
  rc = left_->get_value(trx, tuple, left_value);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to get value of left expression. rc=%s", strrc(rc));
    return rc;
  }
  rc = right_->get_value(trx, tuple, right_value);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to get value of right expression. rc=%s", strrc(rc));
    return rc;
  }

  bool bool_value = false;
  rc              = compare_value(left_value, right_value, bool_value);
  if (rc == RC::SUCCESS) {
    value.set_boolean(bool_value);
  }
  if (left_->type() == ExprType::SUB_QUERY) {
    static_cast<SubQueryExpr *>(left_.get())->reset();  // 重置子查询
  }
  if (right_->type() == ExprType::SUB_QUERY) {
    static_cast<SubQueryExpr *>(right_.get())->reset();  // 重置子查询
  }
  return rc;
}