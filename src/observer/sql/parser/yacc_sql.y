
%{

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>

#include "common/log/log.h"
#include "common/lang/string.h"
#include "sql/parser/parse_defs.h"
#include "sql/parser/yacc_sql.hpp"
#include "sql/parser/lex_sql.h"
#include "sql/expr/expression.h"

using namespace std;

string token_name(const char *sql_string, YYLTYPE *llocp)
{
  return string(sql_string + llocp->first_column, llocp->last_column - llocp->first_column + 1);
}

int yyerror(YYLTYPE *llocp, const char *sql_string, ParsedSqlResult *sql_result, yyscan_t scanner, const char *msg)
{
  std::unique_ptr<ParsedSqlNode> error_sql_node = std::make_unique<ParsedSqlNode>(SCF_ERROR);
  error_sql_node->error.error_msg = msg;
  error_sql_node->error.line = llocp->first_line;
  error_sql_node->error.column = llocp->first_column;
  sql_result->add_sql_node(std::move(error_sql_node));
  return 0;
}

ArithmeticExpr *create_arithmetic_expression(ArithmeticExpr::Type type,
                                             Expression *left,
                                             Expression *right,
                                             const char *sql_string,
                                             YYLTYPE *llocp)
{
  ArithmeticExpr *expr = new ArithmeticExpr(type, left, right);
  expr->set_name(token_name(sql_string, llocp));
  return expr;
}

%}

%define api.pure full
%define parse.error verbose
/** 启用位置标识 **/
%locations
%lex-param { yyscan_t scanner }
/** 这些定义了在yyparse函数中的参数 **/
%parse-param { const char * sql_string }
%parse-param { ParsedSqlResult * sql_result }
%parse-param { void * scanner }

//标识tokens
%token  SEMICOLON
        CREATE
        DROP
        TABLE
        TABLES
        INDEX
        CALC
        SELECT
        DESC
        ASC
        SHOW
        SYNC
        INSERT
        DELETE
        UPDATE
        LBRACE
        RBRACE
        COMMA
        TRX_BEGIN
        TRX_COMMIT
        TRX_ROLLBACK
        INT_T
        STRING_T
        FLOAT_T
        DATE_T
        TEXT_T
        HELP
        EXIT
        DOT //QUOTE
        INTO
        VALUES
        FROM
        WHERE
        AND
        SET
        INNER
        JOIN
        ON
        LOAD
        DATA
        INFILE
        EXPLAIN
        EQ
        LT
        GT
        LE
        GE
        NE
        IS
        IN_T
        EXISTS_T
        NULL_T
        // like已经在词法解析之中解析出
        LIKE_C
        NOT
        COUNT
        SUM
        MAX
        MIN
        AVG
        ORDER
        BY
        UNIQUE

/** union 中定义各种数据类型，真实生成的代码也是union类型，所以不能有非POD类型的数据 **/
%union {
  ParsedSqlNode *                   sql_node;
  ConditionSqlNode *                condition;
  Value *                           value;
  enum CompOp                       comp;
  RelAttrSqlNode *                  rel_attr;
  RelAttrSqlNode *                  agg_func;
  std::vector<AttrInfoSqlNode> *    attr_infos;
  AttrInfoSqlNode *                 attr_info;
  Expression *                      expression;
  std::vector<Expression *> *       expression_list;
  std::vector<Value> *              value_list;
  std::vector<ConditionSqlNode> *   condition_list;
  std::vector<RelAttrSqlNode> *     rel_attr_list;
  std::vector<std::string> *        relation_list;
  std::vector<RelWithConditions> *  join_relation_list;
  std::vector<OrderByItem> *        order_by_item_list;
  std::vector<UpdateSetSqlNode>*    update_set_list;
  OrderByItem *                     order_by_item;
  OrderByType                       order_type;
  char *                            string;
  int                               number;
  float                             floats;
  bool                              bools;
}

%token <number> NUMBER
%token <floats> FLOAT
%token <string> ID
%token <string> SSS
//非终结符

/** type 定义了各种解析后的结果输出的是什么类型。类型对应了 union 中的定义的成员变量名称 **/
%type <number>              type
%type <bools>               nullable
%type <condition>           condition
%type <value>               value
%type <number>              number
%type <comp>                sub_comp_op
%type <comp>                comp_op
%type <comp>                exists
%type <rel_attr>            rel_attr
%type <order_by_item_list>  order_by_item_list
%type <order_by_item_list>  order_by
%type <order_type>          order_type
%type <order_by_item>       order_by_item
%type <agg_func>            agg_func
%type <attr_infos>          attr_def_list
%type <attr_info>           attr_def
%type <value_list>          value_list
%type <condition_list>      where
%type <condition_list>      condition_list
%type <rel_attr_list>       select_attr
%type <rel_attr_list>       agg_func_list
%type <join_relation_list>  rel_list
%type <rel_attr_list>       attr_list
%type <expression>          expression
%type <expression_list>     expression_list
%type <sql_node>            calc_stmt
%type <sql_node>            select_stmt
%type <sql_node>            insert_stmt
%type <sql_node>            update_stmt
%type <sql_node>            update_set
%type <update_set_list>            update_set_list
%type <sql_node>            delete_stmt
%type <sql_node>            create_table_stmt
%type <sql_node>            drop_table_stmt
%type <sql_node>            show_tables_stmt
%type <sql_node>            desc_table_stmt
%type <sql_node>            create_index_stmt
%type <sql_node>            drop_index_stmt
%type <sql_node>            show_index_stmt
%type <sql_node>            sync_stmt
%type <sql_node>            begin_stmt
%type <sql_node>            commit_stmt
%type <sql_node>            rollback_stmt
%type <sql_node>            load_data_stmt
%type <sql_node>            explain_stmt
%type <sql_node>            set_variable_stmt
%type <sql_node>            help_stmt
%type <sql_node>            exit_stmt
%type <sql_node>            command_wrapper
// commands should be a list but I use a single command instead
%type <sql_node>            commands

%left '+' '-'
%left '*' '/'
%nonassoc UMINUS
%%

commands: command_wrapper opt_semicolon  //commands or sqls. parser starts here.
  {
    std::unique_ptr<ParsedSqlNode> sql_node = std::unique_ptr<ParsedSqlNode>($1);
    sql_result->add_sql_node(std::move(sql_node));
  }
  ;

command_wrapper:
    calc_stmt
  | select_stmt
  | insert_stmt
  | update_stmt
  | delete_stmt
  | create_table_stmt
  | drop_table_stmt
  | show_tables_stmt
  | desc_table_stmt
  | create_index_stmt
  | drop_index_stmt
  | show_index_stmt
  | sync_stmt
  | begin_stmt
  | commit_stmt
  | rollback_stmt
  | load_data_stmt
  | explain_stmt
  | set_variable_stmt
  | help_stmt
  | exit_stmt
    ;

exit_stmt:
    EXIT {
      (void)yynerrs;  // 这么写为了消除yynerrs未使用的告警。如果你有更好的方法欢迎提PR
      $$ = new ParsedSqlNode(SCF_EXIT);
    };

help_stmt:
    HELP {
      $$ = new ParsedSqlNode(SCF_HELP);
    };

sync_stmt:
    SYNC {
      $$ = new ParsedSqlNode(SCF_SYNC);
    }
    ;

begin_stmt:
    TRX_BEGIN  {
      $$ = new ParsedSqlNode(SCF_BEGIN);
    }
    ;

commit_stmt:
    TRX_COMMIT {
      $$ = new ParsedSqlNode(SCF_COMMIT);
    }
    ;

rollback_stmt:
    TRX_ROLLBACK  {
      $$ = new ParsedSqlNode(SCF_ROLLBACK);
    }
    ;

drop_table_stmt:    /*drop table 语句的语法解析树*/
    DROP TABLE ID {
      $$ = new ParsedSqlNode(SCF_DROP_TABLE);
      $$->drop_table.relation_name = $3;
      free($3);
    };

show_tables_stmt:
    SHOW TABLES {
      $$ = new ParsedSqlNode(SCF_SHOW_TABLES);
    }
    ;

desc_table_stmt:
    DESC ID  {
      $$ = new ParsedSqlNode(SCF_DESC_TABLE);
      $$->desc_table.relation_name = $2;
      free($2);
    }
    ;
create_table_stmt:    /*create table 语句的语法解析树*/
    CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE
    {
      $$ = new ParsedSqlNode(SCF_CREATE_TABLE);
      CreateTableSqlNode &create_table = $$->create_table;
      create_table.relation_name = $3;
      free($3);

      std::vector<AttrInfoSqlNode> *src_attrs = $6;

      if (src_attrs != nullptr) {
        create_table.attr_infos.swap(*src_attrs);
      }
      create_table.attr_infos.emplace_back(*$5);
      std::reverse(create_table.attr_infos.begin(), create_table.attr_infos.end());
      delete $5;
    }
    ;

create_index_stmt:    /*create index 语句的语法解析树*/
    CREATE INDEX ID ON ID LBRACE rel_attr attr_list RBRACE
    {
      $$ = new ParsedSqlNode(SCF_CREATE_INDEX);
      CreateIndexSqlNode &create_index = $$->create_index;
      create_index.index_name = $3;
      create_index.relation_name = $5;
      create_index.attribute_names.push_back(*$7);
      if ($8 != nullptr) {
        create_index.attribute_names.insert(create_index.attribute_names.end(), $8->begin(), $8->end());
      }
      create_index.is_unique = false;
      free($3);
      free($5);
      free($7);
    }
    | CREATE UNIQUE INDEX ID ON ID LBRACE rel_attr attr_list RBRACE {
        $$ = new ParsedSqlNode(SCF_CREATE_INDEX);
        CreateIndexSqlNode &create_index = $$->create_index;
        create_index.index_name = $4;
        create_index.relation_name = $6;
        create_index.attribute_names.push_back(*$8);
        if ($9 != nullptr) {
           create_index.attribute_names.insert(create_index.attribute_names.end(), $9->begin(), $9->end());
        }
        create_index.is_unique = true;
        printf("uu ok!\n");
        free($4);
        free($6);
        free($8);
    }
    ;

drop_index_stmt:      /*drop index 语句的语法解析树*/
    DROP INDEX ID ON ID
    {
      $$ = new ParsedSqlNode(SCF_DROP_INDEX);
      $$->drop_index.index_name = $3;
      $$->drop_index.relation_name = $5;
      free($3);
      free($5);
    }
    ;

show_index_stmt:
    SHOW INDEX FROM ID
    {
        $$ = new ParsedSqlNode(SCF_SHOW_INDEX);
        $$->show_index.relation_name = $4;
        free($4);
    }
    ;

attr_def_list:
    /* empty */
    {
      $$ = nullptr;
    }
    | COMMA attr_def attr_def_list
    {
      if ($3 != nullptr) {
        $$ = $3;
      } else {
        $$ = new std::vector<AttrInfoSqlNode>;
      }
      $$->emplace_back(*$2);
      delete $2;
    }
    ;

attr_def:
    ID type LBRACE number RBRACE nullable
    {
      $$ = new AttrInfoSqlNode;
      $$->type = (AttrType)$2;
      $$->name = $1;
      $$->length = $4;
      $$->is_nullable = $6;
      free($1);
    }
    | ID type nullable
    {
      $$ = new AttrInfoSqlNode;
      $$->type = (AttrType)$2;
      $$->name = $1;
      if($$->type == TEXTS) {
      $$->length = 65535;
      }else{
        $$->length = 4;
      }
      $$->is_nullable = $3;
      free($1);
    }
    ;
nullable:
    /* empty */
    {
        $$ = false;
    }
    | NULL_T {
        $$ = true;
    }
    | NOT NULL_T {
        $$ = false;
    }
    ;
number:
    NUMBER {$$ = $1;}
    ;
type:
    INT_T      { $$=INTS; }
    | STRING_T { $$=CHARS; }
    | FLOAT_T  { $$=FLOATS; }
    | DATE_T  { $$=DATES; }
    | TEXT_T  { $$=TEXTS; }
    ;
insert_stmt:        /*insert   语句的语法解析树*/
    INSERT INTO ID VALUES LBRACE value value_list RBRACE
    {
      $$ = new ParsedSqlNode(SCF_INSERT);
      $$->insertion.relation_name = $3;
      if ($7 != nullptr) {
        $$->insertion.values.swap(*$7);
      }
      $$->insertion.values.emplace_back(*$6);
      std::reverse($$->insertion.values.begin(), $$->insertion.values.end());
      delete $6;
      free($3);
    }
    ;

value_list:
    /* empty */
    {
      $$ = nullptr;
    }
    | COMMA value value_list  {
      if ($3 != nullptr) {
        $$ = $3;
      } else {
        $$ = new std::vector<Value>;
      }
      $$->emplace_back(*$2);
      delete $2;
    }
    ;
value:
    NUMBER {
      $$ = new Value((int)$1);
      @$ = @1;
    }
    |FLOAT {
      $$ = new Value((float)$1);
      @$ = @1;
    }
    |SSS {
      char *tmp = common::substr($1,1,strlen($1)-2);
      $$ = new Value(tmp);
      free(tmp);
    }
    |NULL_T {
      $$ = new Value();
      $$->set_null();
      //@$ = @1;
    }
    ;

delete_stmt:    /*  delete 语句的语法解析树*/
    DELETE FROM ID where
    {
      $$ = new ParsedSqlNode(SCF_DELETE);
      $$->deletion.relation_name = $3;
      if ($4 != nullptr) {
        $$->deletion.conditions.swap(*$4);
        delete $4;
      }
      free($3);
    }
    ;
update_stmt:      /*  update 语句的语法解析树*/
    UPDATE ID SET update_set_list where
    {
      $$ = new ParsedSqlNode(SCF_UPDATE);
      $$->update.relation_name = $2;
      $$->update.update_set = *$4;
      if ($5 != nullptr) {
        $$->update.conditions.swap(*$5);
        delete $5;
      }
      free($2);
      delete $4;
    }
    ;
select_stmt:        /*  select 语句的语法解析树*/
    SELECT select_attr FROM ID rel_list where order_by
    {
      std::vector<std::string> relations;

      $$ = new ParsedSqlNode(SCF_SELECT);
      if ($2 != nullptr) {
        $$->selection.attributes.swap(*$2);
        delete $2;
      }
      if ($5 != nullptr) {

        for(auto item: *$5) {
            relations.emplace_back(item.relation);
            if(!item.conditions.empty()){
                auto join_condition = new std::vector<ConditionSqlNode>;
                join_condition->insert(join_condition->end(),item.conditions.begin(), item.conditions.end());
                $$->selection.join_conditions.emplace_back(*join_condition);
                delete join_condition;
            }
        }
        std::reverse($$->selection.join_conditions.begin(), $$->selection.join_conditions.end());
        $$->selection.relations.swap(relations);
        delete $5;
      }
      $$->selection.relations.push_back($4);
      std::reverse($$->selection.relations.begin(), $$->selection.relations.end());

      if ($6 != nullptr) {
        $$->selection.conditions.insert($$->selection.conditions.end(), $6->begin(), $6->end());
        //$$->selection.conditions.swap(*$6);
        delete $6;
      }

      if ($7 != nullptr) {
        // $$->selection.order_by_items.insert($$->selection.conditions.end(), $7->begin(), $7->end());
        $$->selection.order_by_items.swap(*$7);
        delete $7;
      }

      free($4);
    }
    ;

calc_stmt:
    CALC expression_list
    {
      $$ = new ParsedSqlNode(SCF_CALC);
      std::reverse($2->begin(), $2->end());
      $$->calc.expressions.swap(*$2);
      delete $2;
    }
    ;

expression_list:
    expression
    {
      $$ = new std::vector<Expression*>;
      $$->emplace_back($1);
    }
    | expression COMMA expression_list
    {
      if ($3 != nullptr) {
        $$ = $3;
      } else {
        $$ = new std::vector<Expression *>;
      }
      $$->emplace_back($1);
    }
    ;
expression:
    expression '+' expression {
      $$ = create_arithmetic_expression(ArithmeticExpr::Type::ADD, $1, $3, sql_string, &@$);
    }
    | expression '-' expression {
      $$ = create_arithmetic_expression(ArithmeticExpr::Type::SUB, $1, $3, sql_string, &@$);
    }
    | expression '*' expression {
      $$ = create_arithmetic_expression(ArithmeticExpr::Type::MUL, $1, $3, sql_string, &@$);
    }
    | expression '/' expression {
      $$ = create_arithmetic_expression(ArithmeticExpr::Type::DIV, $1, $3, sql_string, &@$);
    }
    | LBRACE expression RBRACE {
      $$ = $2;
      $$->set_name(token_name(sql_string, &@$));
    }
    | '-' expression %prec UMINUS {
      $$ = create_arithmetic_expression(ArithmeticExpr::Type::NEGATIVE, $2, nullptr, sql_string, &@$);
    }
    | value {
      $$ = new ValueExpr(*$1);
      $$->set_name(token_name(sql_string, &@$));
      delete $1;
    }
    ;

select_attr:
    '*' {
      $$ = new std::vector<RelAttrSqlNode>;
      RelAttrSqlNode attr;
      attr.relation_name  = "";
      attr.attribute_name = "*";
      $$->emplace_back(attr);
    }
    | rel_attr attr_list {
      if ($2 != nullptr) {
        $$ = $2;
      } else {
        $$ = new std::vector<RelAttrSqlNode>;
      }
      $$->emplace_back(*$1);
      delete $1;
    }
    | agg_func agg_func_list {
      if ($2 != nullptr) {
        $$ = $2;
      } else {
        $$ = new std::vector<RelAttrSqlNode>;
      }
      $$->emplace_back(*$1);
      delete $1;
    }
    ;

agg_func:
    COUNT LBRACE '*' RBRACE {
        $$ = new RelAttrSqlNode;
        $$->relation_name  = "";
        $$->attribute_name = "*";
        $$->agg_func = AggFunc::A_COUNT;
        $$->alias = "COUNT(*)";
    }
    | COUNT LBRACE '1' RBRACE {
        $$ = new RelAttrSqlNode;
        $$->relation_name  = "";
        $$->attribute_name = "*";
        $$->agg_func = AggFunc::A_COUNT;
        $$->alias = "COUNT(1)";
    }
    | COUNT LBRACE rel_attr RBRACE {
        $3->agg_func = AggFunc::A_COUNT;
        $$ = std::move($3);
    }
    | SUM LBRACE rel_attr RBRACE {
        $3->agg_func = AggFunc::A_SUM;
        $$ = std::move($3);
    }
    | MIN LBRACE rel_attr RBRACE {
        $3->agg_func = AggFunc::A_MIN;
        $$ = std::move($3);
    }
    | MAX LBRACE rel_attr RBRACE {
        $3->agg_func = AggFunc::A_MAX;
        $$ = std::move($3);
    }
    | AVG LBRACE rel_attr RBRACE {
        $3->agg_func = AggFunc::A_AVG;
        $$ = std::move($3);
    }
    ;

order_by:
    /* empty */
    {
        $$ = nullptr;
    }
    | ORDER BY order_by_item_list {
        std::reverse($3->begin(), $3->end());
        $$ = $3;
    }
    ;

order_by_item_list:
    /* empty */
    {
        $$ = nullptr;
    }
    | order_by_item {
        $$ = new std::vector<OrderByItem>;
        $$->emplace_back(*$1);
        delete $1;
    }
    | order_by_item COMMA order_by_item_list {
        $$ = $3;
        $$->emplace_back(*$1);
        delete $1;
    }
;
order_by_item:
    rel_attr order_type {
      $$ = new OrderByItem;
      $$->attr = *$1;
      $$->order_type = $2;
      free($1);
    }
    ;

order_type:
    /* empty */
    {
        $$ = OrderByType::SORT_ASC;
    }
    | ASC {
        $$ = OrderByType::SORT_ASC;
    }
    | DESC {
        $$ = OrderByType::SORT_DESC;
    }
    ;

agg_func_list:
    /* empty */
    {
        $$ = nullptr;
    }
    | COMMA agg_func agg_func_list {
        if ($3 != nullptr) {
            $$ = $3;
        } else {
            $$ = new std::vector<RelAttrSqlNode>;
        }
        $$->emplace_back(*$2);
        delete $2;
    }
    ;

rel_attr:
    ID DOT '*' {
          $$ = new RelAttrSqlNode;
          $$->relation_name  = $1;
          $$->attribute_name = "*";
          free($1);
    }
    | ID {
      $$ = new RelAttrSqlNode;
      $$->attribute_name = $1;
      free($1);
    }
    | ID DOT ID {
      $$ = new RelAttrSqlNode;
      $$->relation_name  = $1;
      $$->attribute_name = $3;
      free($1);
      free($3);
    }
    ;

attr_list:
    /* empty */
    {
      $$ = nullptr;
    }
    | COMMA rel_attr attr_list {
      if ($3 != nullptr) {
        $$ = $3;
      } else {
        $$ = new std::vector<RelAttrSqlNode>;
      }

      $$->emplace_back(*$2);
      delete $2;
    }
    ;

rel_list:
    /* empty */
    {
      $$ = nullptr;
    }
    | INNER JOIN ID ON condition_list rel_list {
      if ($6 != nullptr) {
        $$ = $6;
      } else {
        $$ = new std::vector<RelWithConditions>;
      }
      auto tmp = new RelWithConditions;
      tmp->relation = $3;
      tmp->conditions.swap(*$5);
      $$->emplace_back(*tmp);
      free($3);
      free($5);
    }
    | COMMA ID rel_list {
      if ($3 != nullptr) {
        $$ = $3;
      } else {
        $$ = new std::vector<RelWithConditions>;
      }
      auto tmp = new RelWithConditions;
      tmp->relation = $2;
      $$->emplace_back(*tmp);
      free($2);
    }
    ;
where:
    /* empty */
    {
      $$ = nullptr;
    }
    | WHERE condition_list {
      $$ = $2;
    }
    ;
condition_list:
    /* empty */
    {
      $$ = nullptr;
    }
    | condition {
      $$ = new std::vector<ConditionSqlNode>;
      $$->emplace_back(*$1);
      delete $1;
    }
    | condition AND condition_list {
      $$ = $3;
      $$->emplace_back(*$1);
      delete $1;
    }
    ;
condition:
    value sub_comp_op LBRACE value value_list RBRACE
    {
      $$ = new ConditionSqlNode;
      $$->left_type = VALUE;
      $$->left_value = *$1;
      $$->right_type = VALUE_LIST;
      if ($5 != nullptr) {
        $$->right_values.swap(*$5);
      }
      $$->right_values.emplace_back(*$4);
      $$->comp = $2;

      delete $1;
      delete $4;
    }
    | rel_attr sub_comp_op LBRACE value value_list RBRACE
    {
      $$ = new ConditionSqlNode;
      $$->left_type = ATTR;
      $$->left_attr = *$1;
      $$->right_type = VALUE_LIST;
      if ($5 != nullptr) {
        $$->right_values.swap(*$5);
      }
      $$->right_values.emplace_back(*$4);
      $$->comp = $2;

      delete $1;
      delete $4;
    }
    | rel_attr sub_comp_op LBRACE select_stmt RBRACE
      {
        $$ = new ConditionSqlNode;
        $$->left_type = ATTR;
        $$->left_attr = *$1;
        $$->right_type = SUB_QUERY;
        $$->right_sub_selection = $4;
        $$->comp = $2;

        delete $1;
      }
    | value sub_comp_op LBRACE select_stmt RBRACE
      {
        $$ = new ConditionSqlNode;
        $$->left_type = VALUE;
        $$->left_value = *$1;
        $$->right_type = SUB_QUERY;
        $$->right_sub_selection = $4;
        $$->comp = $2;

        delete $1;
      }
     | LBRACE select_stmt RBRACE sub_comp_op value
        {
          $$ = new ConditionSqlNode;
          $$->left_type = SUB_QUERY;
          $$->left_sub_selection = $2;
          $$->right_type = VALUE;
          $$->right_value = *$5;
          $$->comp = $4;

          delete $5;
        }
    | LBRACE select_stmt RBRACE sub_comp_op rel_attr
      {
        $$ = new ConditionSqlNode;
        $$->left_type = SUB_QUERY;
        $$->left_sub_selection = $2;
        $$->right_type = ATTR;
        $$->right_attr = *$5;
        $$->comp = $4;

        delete $5;
      }
    | exists LBRACE select_stmt RBRACE
    {
      $$ = new ConditionSqlNode;
      $$->left_type = NULL_TYPE;
      $$->right_type = SUB_QUERY;
      $$->right_sub_selection = $3;
      $$->comp = $1;

    }
    | rel_attr comp_op value
    {
      $$ = new ConditionSqlNode;
      $$->left_type = ATTR;
      $$->left_attr = *$1;
      $$->right_type = VALUE;
      $$->right_value = *$3;
      $$->comp = $2;

      delete $1;
      delete $3;
    }
    | value comp_op value
    {
      $$ = new ConditionSqlNode;
      $$->left_type = VALUE;
      $$->left_value = *$1;
      $$->right_type = VALUE;
      $$->right_value = *$3;
      $$->comp = $2;

      delete $1;
      delete $3;
    }
    | rel_attr comp_op rel_attr
    {
      $$ = new ConditionSqlNode;
      $$->left_type = ATTR;
      $$->left_attr = *$1;
      $$->right_type = ATTR;
      $$->right_attr = *$3;
      $$->comp = $2;

      delete $1;
      delete $3;
    }
    | value comp_op rel_attr
    {
      $$ = new ConditionSqlNode;
      $$->left_type = VALUE;
      $$->left_value = *$1;
      $$->right_type = ATTR;
      $$->right_attr = *$3;
      $$->comp = $2;

      delete $1;
      delete $3;
    }
    ;

/*子查询专用比较符*/
sub_comp_op:
      EQ { $$ = EQUAL_TO; }
    | LT { $$ = LESS_THAN; }
    | GT { $$ = GREAT_THAN; }
    | LE { $$ = LESS_EQUAL; }
    | GE { $$ = GREAT_EQUAL; }
    | NE { $$ = NOT_EQUAL; }
    | IN_T { $$ = IN;}
    | NOT IN_T {$$ = NOT_IN;}
    ;

comp_op:
      EQ { $$ = EQUAL_TO; }
    | LT { $$ = LESS_THAN; }
    | GT { $$ = GREAT_THAN; }
    | LE { $$ = LESS_EQUAL; }
    | GE { $$ = GREAT_EQUAL; }
    | NE { $$ = NOT_EQUAL; }
    | LIKE_C{$$ = LIKE;}
    | NOT LIKE_C{$$ = NOT_LIKE;}
    | IS {$$ = IS_NULL;}
    | IS NOT {$$ = NOT_NULL;}
    ;

exists:
      EXISTS_T {$$ = EXISTS;}
    | NOT EXISTS_T {$$ = NOT_EXISTS;}
    ;

load_data_stmt:
    LOAD DATA INFILE SSS INTO TABLE ID 
    {
      char *tmp_file_name = common::substr($4, 1, strlen($4) - 2);
      
      $$ = new ParsedSqlNode(SCF_LOAD_DATA);
      $$->load_data.relation_name = $7;
      $$->load_data.file_name = tmp_file_name;
      free($7);
      free(tmp_file_name);
    }
    ;

explain_stmt:
    EXPLAIN command_wrapper
    {
      $$ = new ParsedSqlNode(SCF_EXPLAIN);
      $$->explain.sql_node = std::unique_ptr<ParsedSqlNode>($2);
    }
    ;

update_set:
    ID EQ value
    {
        $$ = new ParsedSqlNode(SCF_UPDATE_SET);
        $$->update_set.name  = $1;
        $$->update_set.value = *$3;
        free($1);
        delete $3;
    }
    ;

update_set_list:
    update_set
    {
          $$ = new std::vector<UpdateSetSqlNode>;
          $$->push_back($1->update_set);
          delete $1;
    }
    | update_set_list COMMA update_set
     {
           $$->push_back($3->update_set);
           delete $3;
     }
     ;

set_variable_stmt:
    SET ID EQ value
    {
      $$ = new ParsedSqlNode(SCF_SET_VARIABLE);
      $$->set_variable.name  = $2;
      $$->set_variable.value = *$4;
      free($2);
      delete $4;
    }
    ;

opt_semicolon: /*empty*/
    | SEMICOLON
    ;
%%
//_____________________________________________________________________
extern void scan_string(const char *str, yyscan_t scanner);

int sql_parse(const char *s, ParsedSqlResult *sql_result) {
  yyscan_t scanner;
  yylex_init(&scanner);
  scan_string(s, scanner);
  int result = yyparse(s, sql_result, scanner);
  yylex_destroy(scanner);
  return result;
}
