//
// Created by weizhi on 23-11-3.
//

#include "expression.h"
#include "sql/operator/project_physical_operator.h"
/**
 * @brief 子查询表达式,子查询依赖算子，为了避免循环依赖，就把子查询表达式独立出来了
 * @ingroup Expression
 */
class SubQueryExpr : public Expression
{
public:
  SubQueryExpr( ProjectPhysicalOperator *sub_opt):sub_opt_(sub_opt){}

  virtual ~SubQueryExpr() = default;

  ExprType type() const override { return ExprType::SUB_QUERY; }

  AttrType value_type() const override { return AttrType::NULLS; }

  RC get_value(const Tuple &tuple, Value &value) const override;
  RC get_value(Trx *trx, const Tuple &tuple, Value &value);

  // 如果子查询是一个数值列表，则直接在这里返回
  RC try_get_value(Value &value) const override;

  void reset(){ cur_index_ =0;}
  void set_cached(){cached_=true;}

private:
  // 子查询算子
  ProjectPhysicalOperator *sub_opt_;
  bool cached_ = false; // 子查询是否已经执行完毕
  int                      cur_index_ = 0;
  std::vector<Value> values_;
};