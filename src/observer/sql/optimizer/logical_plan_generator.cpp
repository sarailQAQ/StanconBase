/* Copyright (c) 2023 OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

//
// Created by Wangyunlai on 2023/08/16.
//

#include "sql/optimizer/logical_plan_generator.h"
#include "optimize_stage.h"
#include "event/sql_event.h"

#include "sql/operator/logical_operator.h"
#include "sql/operator/calc_logical_operator.h"
#include "sql/operator/project_logical_operator.h"
#include "sql/operator/predicate_logical_operator.h"
#include "sql/operator/table_get_logical_operator.h"
#include "sql/operator/update_logical_operator.h"
#include "sql/operator/insert_logical_operator.h"
#include "sql/operator/delete_logical_operator.h"
#include "sql/operator/join_logical_operator.h"
#include "sql/operator/explain_logical_operator.h"

#include "sql/stmt/stmt.h"
#include "sql/stmt/calc_stmt.h"
#include "sql/stmt/select_stmt.h"
#include "sql/stmt/update_stmt.h"
#include "sql/stmt/filter_stmt.h"
#include "sql/stmt/insert_stmt.h"
#include "sql/stmt/delete_stmt.h"
#include "sql/stmt/explain_stmt.h"
#include "sql/operator/order_by_logical_operator.h"
#include "sql/expr/comparison_expression.h"
#include "sql/expr/expression.h"


using namespace std;

RC LogicalPlanGenerator::create(Stmt *stmt, unique_ptr<LogicalOperator> &logical_operator)
{
  RC rc = RC::SUCCESS;
  switch (stmt->type()) {
    case StmtType::CALC: {
      CalcStmt *calc_stmt = static_cast<CalcStmt *>(stmt);
      rc                  = create_plan(calc_stmt, logical_operator);
    } break;

    case StmtType::SELECT: {
      SelectStmt *select_stmt = static_cast<SelectStmt *>(stmt);
      rc                      = create_plan(select_stmt, logical_operator);
    } break;

    case StmtType::INSERT: {
      InsertStmt *insert_stmt = static_cast<InsertStmt *>(stmt);
      rc                      = create_plan(insert_stmt, logical_operator);
    } break;

    case StmtType::DELETE: {
      DeleteStmt *delete_stmt = static_cast<DeleteStmt *>(stmt);
      rc                      = create_plan(delete_stmt, logical_operator);
    } break;

    case StmtType::UPDATE: {
      UpdateStmt *update_stmt = static_cast<UpdateStmt *>(stmt);
      rc                      = create_plan(update_stmt, logical_operator);
    } break;

    case StmtType::EXPLAIN: {
      ExplainStmt *explain_stmt = static_cast<ExplainStmt *>(stmt);
      rc                        = create_plan(explain_stmt, logical_operator);
    } break;
    default: {
      rc = RC::UNIMPLENMENT;
    }
  }
  return rc;
}

RC LogicalPlanGenerator::create_plan(CalcStmt *calc_stmt, std::unique_ptr<LogicalOperator> &logical_operator)
{
  logical_operator.reset(new CalcLogicalOperator(std::move(calc_stmt->expressions())));
  return RC::SUCCESS;
}

RC LogicalPlanGenerator::create_plan(UpdateStmt *update_stmt, unique_ptr<LogicalOperator> &logical_operator)
{
  Table             *table       = update_stmt->table();
  FilterStmt        *filter_stmt = update_stmt->filter_stmt();
  std::vector<Field> fields;
  for (int i = table->table_meta().sys_field_num(); i < table->table_meta().field_num(); i++) {
    const FieldMeta *field_meta = table->table_meta().field(i);
    fields.push_back(Field(table, field_meta));
  }
  unique_ptr<LogicalOperator> table_get_oper(new TableGetLogicalOperator(table, fields, false /*readonly*/));

  unique_ptr<LogicalOperator> predicate_oper;
  RC                          rc = create_plan(filter_stmt, predicate_oper);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  unique_ptr<LogicalOperator> update_oper(
      new UpdateLogicalOperator(table, update_stmt->field_name(), update_stmt->value()));

  if (predicate_oper) {
    predicate_oper->add_child(std::move(table_get_oper));
    update_oper->add_child(std::move(predicate_oper));
  } else {
    update_oper->add_child(std::move(table_get_oper));
  }

  logical_operator = std::move(update_oper);
  return rc;
}

RC LogicalPlanGenerator::create_plan(SelectStmt *select_stmt, unique_ptr<LogicalOperator> &logical_operator)
{
  // 创建表操作符
  unique_ptr<LogicalOperator> table_oper(nullptr);
  // 获取查询中的表和字段信息

  const std::vector<Table *> &tables     = select_stmt->tables();
  const std::vector<Field>   &all_fields = select_stmt->query_fields();
  // 单表table_oper 就是一个get算子，多表的话table_oper是一个join算子 其子节点分别是各个表的get算子
  int expr_index = 0;  // 一个join expr就在第一个第二个表之间，以此类推
  for (Table *table : tables) {
    std::vector<Field> fields;
    // 筛选属于当前表的字段
    for (const Field &field : all_fields) {
      if (0 == strcmp(field.table_name(), table->name())) {
        fields.push_back(field);
      }
    }
    // 创建表获取操作符
    unique_ptr<LogicalOperator> table_get_oper(new TableGetLogicalOperator(table, fields, true /*readonly*/));
    if (table_oper == nullptr) {
      // 第一张表
      // 如果是第一个表，则直接赋值给table_oper
      table_oper = std::move(table_get_oper);
    } else {
      // 带join的表
      // 如果不是第一个表，则创建连接操作符，并将之前的table_oper和当前表的操作符作为子节点
      JoinLogicalOperator *join_oper;
      if (!select_stmt->join_filter_stmts().empty()) {
        unique_ptr<ConjunctionExpr> conjunction_expr;
        create_expr(select_stmt->join_filter_stmts()[expr_index++], conjunction_expr);
        join_oper = new JoinLogicalOperator(std::move(conjunction_expr));
      } else {
        join_oper = new JoinLogicalOperator;
      }

      join_oper->add_child(std::move(table_oper));
      join_oper->add_child(std::move(table_get_oper));
      table_oper = unique_ptr<LogicalOperator>(join_oper);
    }
  }
  // 创建谓词操作符
  unique_ptr<LogicalOperator> predicate_oper;
  if (!select_stmt->filter_stmt()->filter_units().empty()) {
    RC rc = create_plan(select_stmt->filter_stmt(), predicate_oper);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to create predicate logical plan. rc=%s", strrc(rc));
      return rc;
    }
  }

  // 创建投影操作符
  unique_ptr<LogicalOperator> project_oper(new ProjectLogicalOperator(all_fields));
  if (predicate_oper) {
    if (table_oper) {
      predicate_oper->add_child(std::move(table_oper));
    }
    project_oper->add_child(std::move(predicate_oper));
  } else {
    if (table_oper) {
      project_oper->add_child(std::move(table_oper));
    }
  }

  // 排序算子
  if (!select_stmt->order_fields().empty()) {
    std::vector<OrderByType>                 order_by_types;
    std::vector<std::unique_ptr<Expression>> expressions;
    for (const auto &item : select_stmt->order_fields()) {
      order_by_types.emplace_back(item.order_type_);
      expressions.emplace_back(new FieldExpr(item));
    }
    unique_ptr<LogicalOperator> order_oper(new OrderByLogicalOperator(std::move(expressions),order_by_types));

    // 如果有排序算子，则第一层是排序(最后执行)，然后才是映射
    order_oper->add_child(std::move(project_oper));
    logical_operator.swap(order_oper);
    return RC::SUCCESS;
  }

  logical_operator.swap(project_oper);
  return RC::SUCCESS;
}

RC LogicalPlanGenerator::create_expr(FilterStmt *filter_stmt, unique_ptr<ConjunctionExpr> &conjunction_expr)
{
  // 创建比较表达式
  std::vector<unique_ptr<Expression>> cmp_exprs;
  const std::vector<FilterUnit *>    &filter_units = filter_stmt->filter_units();
  for (const FilterUnit *filter_unit : filter_units) {
    const FilterObj &filter_obj_left  = filter_unit->left();
    const FilterObj &filter_obj_right = filter_unit->right();
    // 创建左右表达式

    // 左值暂时不支持 列表和子查询
    unique_ptr<Expression> left(filter_obj_left.type == ATTR
                                    ? static_cast<Expression *>(new FieldExpr(filter_obj_left.field))
                                    : static_cast<Expression *>(new ValueExpr(filter_obj_left.value)));

    Expression *right_expr;
    switch (filter_obj_right.type) {
      case VALUE:{
        right_expr = static_cast<Expression *>(new ValueExpr(filter_obj_right.value));
      } break;
      case ATTR:{
        right_expr = static_cast<Expression *>(new ValueExpr(filter_obj_right.value));
      } break;
      case VALUE_LIST:{
        right_expr = static_cast<Expression *>(new SubQueryExpr(filter_obj_right.value_list));
      } break;
      case SUB_QUERY:{
        // fake_event 模拟查询stmt 构造物理算子的过程
        OptimizeStage optimize_stage;
        auto fake_event = new SQLStageEvent(filter_obj_right.sub_query);
        optimize_stage.handle_request(fake_event);
        right_expr = static_cast<Expression *>(new SubQueryExpr(&fake_event->physical_operator()));
      } break;
      default:{
        LOG_WARN("not support filter_obj type");
        return RC::INVALID_ARGUMENT;
      }
    }

    unique_ptr<Expression> right(right_expr);

    ComparisonExpr *cmp_expr = new ComparisonExpr(filter_unit->comp(), std::move(left), std::move(right));
    cmp_exprs.emplace_back(cmp_expr);
  }

  unique_ptr<PredicateLogicalOperator> predicate_oper;
  if (!cmp_exprs.empty()) {
    // 如果存在比较表达式，则创建合取表达式，并将其作为谓词操作符
    conjunction_expr = unique_ptr<ConjunctionExpr>(new ConjunctionExpr(ConjunctionExpr::Type::AND, cmp_exprs));
  }
  return RC::SUCCESS;
}

RC LogicalPlanGenerator::create_plan(FilterStmt *filter_stmt, unique_ptr<LogicalOperator> &logical_operator)
{
  unique_ptr<ConjunctionExpr> conjunction_expr;
  create_expr(filter_stmt, conjunction_expr);
  if (conjunction_expr) {
    unique_ptr<PredicateLogicalOperator> predicate_oper =
        unique_ptr<PredicateLogicalOperator>(new PredicateLogicalOperator(std::move(conjunction_expr)));
    logical_operator = std::move(predicate_oper);
  }
  return RC::SUCCESS;
}

RC LogicalPlanGenerator::create_plan(InsertStmt *insert_stmt, unique_ptr<LogicalOperator> &logical_operator)
{
  Table        *table = insert_stmt->table();
  vector<Value> values(insert_stmt->values(), insert_stmt->values() + insert_stmt->value_amount());

  InsertLogicalOperator *insert_operator = new InsertLogicalOperator(table, values);
  logical_operator.reset(insert_operator);
  return RC::SUCCESS;
}

RC LogicalPlanGenerator::create_plan(DeleteStmt *delete_stmt, unique_ptr<LogicalOperator> &logical_operator)
{
  Table             *table       = delete_stmt->table();
  FilterStmt        *filter_stmt = delete_stmt->filter_stmt();
  std::vector<Field> fields;
  for (int i = table->table_meta().sys_field_num(); i < table->table_meta().field_num(); i++) {
    const FieldMeta *field_meta = table->table_meta().field(i);
    fields.push_back(Field(table, field_meta));
  }
  unique_ptr<LogicalOperator> table_get_oper(new TableGetLogicalOperator(table, fields, false /*readonly*/));

  unique_ptr<LogicalOperator> predicate_oper;
  RC                          rc = create_plan(filter_stmt, predicate_oper);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  unique_ptr<LogicalOperator> delete_oper(new DeleteLogicalOperator(table));

  if (predicate_oper) {
    predicate_oper->add_child(std::move(table_get_oper));
    delete_oper->add_child(std::move(predicate_oper));
  } else {
    delete_oper->add_child(std::move(table_get_oper));
  }

  logical_operator = std::move(delete_oper);
  return rc;
}

RC LogicalPlanGenerator::create_plan(ExplainStmt *explain_stmt, unique_ptr<LogicalOperator> &logical_operator)
{
  Stmt                       *child_stmt = explain_stmt->child();
  unique_ptr<LogicalOperator> child_oper;
  RC                          rc = create(child_stmt, child_oper);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to create explain's child operator. rc=%s", strrc(rc));
    return rc;
  }

  logical_operator = unique_ptr<LogicalOperator>(new ExplainLogicalOperator);
  logical_operator->add_child(std::move(child_oper));
  return rc;
}
