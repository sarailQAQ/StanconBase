/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 2

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 2 "./src/observer/sql/parser/yacc_sql.y"


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


#line 115 "./src/observer/sql/parser/yacc_sql.cpp"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "yacc_sql.hpp"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_SEMICOLON = 3,                  /* SEMICOLON  */
  YYSYMBOL_CREATE = 4,                     /* CREATE  */
  YYSYMBOL_DROP = 5,                       /* DROP  */
  YYSYMBOL_TABLE = 6,                      /* TABLE  */
  YYSYMBOL_TABLES = 7,                     /* TABLES  */
  YYSYMBOL_INDEX = 8,                      /* INDEX  */
  YYSYMBOL_CALC = 9,                       /* CALC  */
  YYSYMBOL_SELECT = 10,                    /* SELECT  */
  YYSYMBOL_DESC = 11,                      /* DESC  */
  YYSYMBOL_ASC = 12,                       /* ASC  */
  YYSYMBOL_SHOW = 13,                      /* SHOW  */
  YYSYMBOL_SYNC = 14,                      /* SYNC  */
  YYSYMBOL_INSERT = 15,                    /* INSERT  */
  YYSYMBOL_DELETE = 16,                    /* DELETE  */
  YYSYMBOL_UPDATE = 17,                    /* UPDATE  */
  YYSYMBOL_LBRACE = 18,                    /* LBRACE  */
  YYSYMBOL_RBRACE = 19,                    /* RBRACE  */
  YYSYMBOL_COMMA = 20,                     /* COMMA  */
  YYSYMBOL_TRX_BEGIN = 21,                 /* TRX_BEGIN  */
  YYSYMBOL_TRX_COMMIT = 22,                /* TRX_COMMIT  */
  YYSYMBOL_TRX_ROLLBACK = 23,              /* TRX_ROLLBACK  */
  YYSYMBOL_INT_T = 24,                     /* INT_T  */
  YYSYMBOL_STRING_T = 25,                  /* STRING_T  */
  YYSYMBOL_FLOAT_T = 26,                   /* FLOAT_T  */
  YYSYMBOL_DATE_T = 27,                    /* DATE_T  */
  YYSYMBOL_TEXT_T = 28,                    /* TEXT_T  */
  YYSYMBOL_HELP = 29,                      /* HELP  */
  YYSYMBOL_EXIT = 30,                      /* EXIT  */
  YYSYMBOL_DOT = 31,                       /* DOT  */
  YYSYMBOL_INTO = 32,                      /* INTO  */
  YYSYMBOL_VALUES = 33,                    /* VALUES  */
  YYSYMBOL_FROM = 34,                      /* FROM  */
  YYSYMBOL_WHERE = 35,                     /* WHERE  */
  YYSYMBOL_AND = 36,                       /* AND  */
  YYSYMBOL_SET = 37,                       /* SET  */
  YYSYMBOL_INNER = 38,                     /* INNER  */
  YYSYMBOL_JOIN = 39,                      /* JOIN  */
  YYSYMBOL_ON = 40,                        /* ON  */
  YYSYMBOL_LOAD = 41,                      /* LOAD  */
  YYSYMBOL_DATA = 42,                      /* DATA  */
  YYSYMBOL_INFILE = 43,                    /* INFILE  */
  YYSYMBOL_EXPLAIN = 44,                   /* EXPLAIN  */
  YYSYMBOL_EQ = 45,                        /* EQ  */
  YYSYMBOL_LT = 46,                        /* LT  */
  YYSYMBOL_GT = 47,                        /* GT  */
  YYSYMBOL_LE = 48,                        /* LE  */
  YYSYMBOL_GE = 49,                        /* GE  */
  YYSYMBOL_NE = 50,                        /* NE  */
  YYSYMBOL_IS = 51,                        /* IS  */
  YYSYMBOL_IN_T = 52,                      /* IN_T  */
  YYSYMBOL_EXISTS_T = 53,                  /* EXISTS_T  */
  YYSYMBOL_NULL_T = 54,                    /* NULL_T  */
  YYSYMBOL_LIKE_C = 55,                    /* LIKE_C  */
  YYSYMBOL_NOT = 56,                       /* NOT  */
  YYSYMBOL_COUNT = 57,                     /* COUNT  */
  YYSYMBOL_SUM = 58,                       /* SUM  */
  YYSYMBOL_MAX = 59,                       /* MAX  */
  YYSYMBOL_MIN = 60,                       /* MIN  */
  YYSYMBOL_AVG = 61,                       /* AVG  */
  YYSYMBOL_ORDER = 62,                     /* ORDER  */
  YYSYMBOL_BY = 63,                        /* BY  */
  YYSYMBOL_UNIQUE = 64,                    /* UNIQUE  */
  YYSYMBOL_NUMBER = 65,                    /* NUMBER  */
  YYSYMBOL_FLOAT = 66,                     /* FLOAT  */
  YYSYMBOL_ID = 67,                        /* ID  */
  YYSYMBOL_SSS = 68,                       /* SSS  */
  YYSYMBOL_69_ = 69,                       /* '+'  */
  YYSYMBOL_70_ = 70,                       /* '-'  */
  YYSYMBOL_71_ = 71,                       /* '*'  */
  YYSYMBOL_72_ = 72,                       /* '/'  */
  YYSYMBOL_UMINUS = 73,                    /* UMINUS  */
  YYSYMBOL_74_1_ = 74,                     /* '1'  */
  YYSYMBOL_YYACCEPT = 75,                  /* $accept  */
  YYSYMBOL_commands = 76,                  /* commands  */
  YYSYMBOL_command_wrapper = 77,           /* command_wrapper  */
  YYSYMBOL_exit_stmt = 78,                 /* exit_stmt  */
  YYSYMBOL_help_stmt = 79,                 /* help_stmt  */
  YYSYMBOL_sync_stmt = 80,                 /* sync_stmt  */
  YYSYMBOL_begin_stmt = 81,                /* begin_stmt  */
  YYSYMBOL_commit_stmt = 82,               /* commit_stmt  */
  YYSYMBOL_rollback_stmt = 83,             /* rollback_stmt  */
  YYSYMBOL_drop_table_stmt = 84,           /* drop_table_stmt  */
  YYSYMBOL_show_tables_stmt = 85,          /* show_tables_stmt  */
  YYSYMBOL_desc_table_stmt = 86,           /* desc_table_stmt  */
  YYSYMBOL_create_table_stmt = 87,         /* create_table_stmt  */
  YYSYMBOL_create_index_stmt = 88,         /* create_index_stmt  */
  YYSYMBOL_drop_index_stmt = 89,           /* drop_index_stmt  */
  YYSYMBOL_show_index_stmt = 90,           /* show_index_stmt  */
  YYSYMBOL_attr_def_list = 91,             /* attr_def_list  */
  YYSYMBOL_attr_def = 92,                  /* attr_def  */
  YYSYMBOL_nullable = 93,                  /* nullable  */
  YYSYMBOL_number = 94,                    /* number  */
  YYSYMBOL_type = 95,                      /* type  */
  YYSYMBOL_insert_stmt = 96,               /* insert_stmt  */
  YYSYMBOL_value_list = 97,                /* value_list  */
  YYSYMBOL_value = 98,                     /* value  */
  YYSYMBOL_delete_stmt = 99,               /* delete_stmt  */
  YYSYMBOL_update_stmt = 100,              /* update_stmt  */
  YYSYMBOL_select_stmt = 101,              /* select_stmt  */
  YYSYMBOL_calc_stmt = 102,                /* calc_stmt  */
  YYSYMBOL_expression_list = 103,          /* expression_list  */
  YYSYMBOL_expression = 104,               /* expression  */
  YYSYMBOL_select_attr = 105,              /* select_attr  */
  YYSYMBOL_agg_func = 106,                 /* agg_func  */
  YYSYMBOL_order_by = 107,                 /* order_by  */
  YYSYMBOL_order_by_item_list = 108,       /* order_by_item_list  */
  YYSYMBOL_order_by_item = 109,            /* order_by_item  */
  YYSYMBOL_order_type = 110,               /* order_type  */
  YYSYMBOL_agg_func_list = 111,            /* agg_func_list  */
  YYSYMBOL_rel_attr = 112,                 /* rel_attr  */
  YYSYMBOL_attr_list = 113,                /* attr_list  */
  YYSYMBOL_rel_list = 114,                 /* rel_list  */
  YYSYMBOL_where = 115,                    /* where  */
  YYSYMBOL_condition_list = 116,           /* condition_list  */
  YYSYMBOL_condition = 117,                /* condition  */
  YYSYMBOL_sub_comp_op = 118,              /* sub_comp_op  */
  YYSYMBOL_comp_op = 119,                  /* comp_op  */
  YYSYMBOL_exists = 120,                   /* exists  */
  YYSYMBOL_load_data_stmt = 121,           /* load_data_stmt  */
  YYSYMBOL_explain_stmt = 122,             /* explain_stmt  */
  YYSYMBOL_update_set = 123,               /* update_set  */
  YYSYMBOL_update_set_list = 124,          /* update_set_list  */
  YYSYMBOL_set_variable_stmt = 125,        /* set_variable_stmt  */
  YYSYMBOL_opt_semicolon = 126             /* opt_semicolon  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int16 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if 1

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* 1 */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE) \
             + YYSIZEOF (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  75
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   278

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  75
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  52
/* YYNRULES -- Number of rules.  */
#define YYNRULES  143
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  277

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   324


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,    71,    69,     2,    70,     2,    72,     2,    74,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    73
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   212,   212,   220,   221,   222,   223,   224,   225,   226,
     227,   228,   229,   230,   231,   232,   233,   234,   235,   236,
     237,   238,   239,   240,   244,   250,   255,   261,   267,   273,
     279,   286,   292,   299,   318,   333,   351,   362,   372,   375,
     388,   397,   413,   416,   419,   424,   427,   428,   429,   430,
     431,   434,   450,   453,   464,   468,   472,   477,   485,   497,
     511,   555,   565,   570,   581,   584,   587,   590,   593,   597,
     600,   608,   615,   624,   636,   643,   650,   654,   658,   662,
     666,   674,   677,   685,   688,   693,   700,   710,   713,   716,
     723,   726,   738,   744,   749,   760,   763,   777,   780,   793,
     807,   810,   816,   819,   824,   831,   846,   861,   872,   883,
     894,   905,   914,   926,   938,   950,   966,   967,   968,   969,
     970,   971,   972,   973,   977,   978,   979,   980,   981,   982,
     983,   984,   985,   986,   990,   991,   995,  1008,  1016,  1027,
    1033,  1041,  1051,  1052
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if 1
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "SEMICOLON", "CREATE",
  "DROP", "TABLE", "TABLES", "INDEX", "CALC", "SELECT", "DESC", "ASC",
  "SHOW", "SYNC", "INSERT", "DELETE", "UPDATE", "LBRACE", "RBRACE",
  "COMMA", "TRX_BEGIN", "TRX_COMMIT", "TRX_ROLLBACK", "INT_T", "STRING_T",
  "FLOAT_T", "DATE_T", "TEXT_T", "HELP", "EXIT", "DOT", "INTO", "VALUES",
  "FROM", "WHERE", "AND", "SET", "INNER", "JOIN", "ON", "LOAD", "DATA",
  "INFILE", "EXPLAIN", "EQ", "LT", "GT", "LE", "GE", "NE", "IS", "IN_T",
  "EXISTS_T", "NULL_T", "LIKE_C", "NOT", "COUNT", "SUM", "MAX", "MIN",
  "AVG", "ORDER", "BY", "UNIQUE", "NUMBER", "FLOAT", "ID", "SSS", "'+'",
  "'-'", "'*'", "'/'", "UMINUS", "'1'", "$accept", "commands",
  "command_wrapper", "exit_stmt", "help_stmt", "sync_stmt", "begin_stmt",
  "commit_stmt", "rollback_stmt", "drop_table_stmt", "show_tables_stmt",
  "desc_table_stmt", "create_table_stmt", "create_index_stmt",
  "drop_index_stmt", "show_index_stmt", "attr_def_list", "attr_def",
  "nullable", "number", "type", "insert_stmt", "value_list", "value",
  "delete_stmt", "update_stmt", "select_stmt", "calc_stmt",
  "expression_list", "expression", "select_attr", "agg_func", "order_by",
  "order_by_item_list", "order_by_item", "order_type", "agg_func_list",
  "rel_attr", "attr_list", "rel_list", "where", "condition_list",
  "condition", "sub_comp_op", "comp_op", "exists", "load_data_stmt",
  "explain_stmt", "update_set", "update_set_list", "set_variable_stmt",
  "opt_semicolon", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-188)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-122)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     136,     1,    31,    14,   -17,   -29,    11,  -188,    13,    27,
      18,  -188,  -188,  -188,  -188,  -188,    36,    29,   136,    78,
     102,  -188,  -188,  -188,  -188,  -188,  -188,  -188,  -188,  -188,
    -188,  -188,  -188,  -188,  -188,  -188,  -188,  -188,  -188,  -188,
    -188,  -188,    39,    40,   100,    43,    47,    14,  -188,  -188,
    -188,  -188,    14,  -188,  -188,     4,    98,   101,   104,   105,
     110,    87,  -188,    95,   111,   113,  -188,  -188,    96,    54,
      67,   107,    94,    99,  -188,  -188,  -188,  -188,   130,   114,
      89,  -188,   115,   -13,  -188,    14,    14,    14,    14,    14,
     -51,   108,   108,   108,   108,   -50,   109,   103,  -188,   108,
    -188,   112,   141,   146,   116,   -40,   117,   119,   120,   138,
     121,  -188,  -188,    26,    26,  -188,  -188,   163,   165,   170,
     171,   173,   183,   184,  -188,  -188,    -7,   111,   113,  -188,
     195,    59,  -188,   172,  -188,    -5,  -188,   187,   143,   196,
     197,   153,  -188,  -188,  -188,  -188,  -188,  -188,  -188,  -188,
     154,   185,   146,  -188,  -188,   -40,   212,  -188,   174,   149,
     149,  -188,   189,   205,   -40,   116,  -188,   220,  -188,  -188,
    -188,  -188,  -188,    -8,   119,   209,   108,   211,    -7,   164,
     168,   214,   213,  -188,   217,   218,   219,   221,   222,   223,
     182,  -188,  -188,    15,   224,   -32,   226,   -32,    59,   212,
    -188,  -188,   178,   181,  -188,   193,  -188,   196,  -188,   113,
     108,  -188,   208,   186,  -188,   -40,   231,   162,  -188,  -188,
    -188,    -2,  -188,  -188,    -2,  -188,  -188,  -188,   232,  -188,
    -188,   233,  -188,  -188,   234,   113,    59,   108,   214,  -188,
    -188,  -188,  -188,  -188,  -188,  -188,   202,   -32,   214,   236,
     214,   237,  -188,    -1,  -188,   238,    -7,  -188,   239,    88,
    -188,  -188,  -188,   241,  -188,   242,  -188,  -188,  -188,  -188,
     108,  -188,  -188,  -188,  -188,  -188,  -188
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,    26,     0,     0,
       0,    27,    28,    29,    25,    24,     0,     0,     0,     0,
     142,    23,    22,    15,    16,    17,    18,     9,    10,    11,
       8,    12,    13,    14,     5,     7,     6,     4,     3,    19,
      20,    21,     0,     0,     0,     0,     0,     0,    57,    54,
      55,    56,     0,    70,    61,    62,     0,     0,     0,     0,
       0,    93,    71,     0,    90,    95,    32,    31,     0,     0,
       0,     0,     0,     0,   137,     1,   143,     2,     0,     0,
       0,    30,     0,     0,    69,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    73,     0,
      72,     0,     0,   100,     0,     0,     0,     0,     0,     0,
       0,    68,    63,    64,    65,    66,    67,     0,     0,     0,
       0,     0,     0,     0,    94,    92,    97,    90,    95,    37,
       0,   102,    58,     0,   139,   100,   141,     0,     0,    38,
       0,     0,    36,    74,    75,    76,    77,    79,    78,    80,
       0,     0,   100,    91,    96,     0,     0,   134,     0,     0,
       0,   101,   103,     0,     0,     0,    59,     0,    46,    47,
      48,    49,    50,    42,     0,     0,     0,     0,    97,     0,
      81,    52,     0,   135,   124,   125,   126,   127,   128,   129,
     132,   122,   130,     0,     0,     0,     0,     0,   102,     0,
     138,   140,     0,     0,    43,     0,    41,    38,    33,    95,
       0,    99,     0,     0,    60,     0,     0,     0,   133,   123,
     131,     0,   113,   115,     0,   112,   114,   104,     0,   136,
      45,     0,    44,    39,     0,    95,   102,    83,    52,    51,
     116,   117,   118,   119,   120,   121,     0,     0,    52,     0,
      52,     0,   111,    42,    34,     0,    97,    82,    84,    87,
      53,   109,   110,     0,   108,     0,   107,    40,    35,    98,
      83,    89,    88,    86,   105,   106,    85
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -188,  -188,   240,  -188,  -188,  -188,  -188,  -188,  -188,  -188,
    -188,  -188,  -188,  -188,  -188,  -188,    55,    90,    10,  -188,
    -188,  -188,  -146,  -104,  -188,  -188,  -152,  -188,   180,    49,
    -188,   175,  -188,    -3,  -188,  -188,   142,    -4,  -126,  -175,
    -123,  -187,  -188,  -155,   118,  -188,  -188,  -188,   106,  -188,
    -188,  -188
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,   175,   139,   206,   231,
     173,    34,   216,    53,    35,    36,    37,    38,    54,    55,
      63,    64,   214,   257,   258,   273,    98,   160,   100,   152,
     132,   161,   162,   194,   195,   163,    39,    40,   134,   135,
      41,    77
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      65,   136,   154,   211,   182,   196,   111,    42,     4,    43,
     203,   227,   166,   150,    48,   165,    61,   124,    67,    68,
     117,   125,    48,   118,    85,    49,    50,   159,    51,   180,
     131,   151,    47,    49,    50,    61,    51,    45,    66,    46,
      56,    57,    58,    59,    60,    69,   204,   228,   205,   256,
      61,   181,    48,   204,    62,   205,    86,    87,    88,    89,
     200,    70,   247,    49,    50,    44,    51,   219,    48,   249,
     220,    73,   251,    86,    87,    88,    89,   156,    75,    49,
      50,   269,    51,   234,    52,    71,   119,   120,   121,   122,
     123,   222,   260,   225,   159,   128,    83,    88,    89,   271,
     272,    84,   263,    72,   265,    76,    78,    79,    80,   255,
      81,   238,   157,    48,    82,   158,    90,   248,    95,    91,
     250,   102,    92,    93,    49,    50,    61,    51,    94,    96,
     101,    97,   159,    99,   103,   113,   114,   115,   116,   105,
       1,     2,   106,   261,   104,     3,     4,     5,   107,     6,
       7,     8,     9,    10,   108,   110,   109,    11,    12,    13,
      56,    57,    58,    59,    60,    14,    15,   168,   169,   170,
     171,   172,   209,    16,   130,    61,   126,    17,   141,   129,
      18,   131,   143,   133,   144,   137,   138,   140,   142,   145,
     146,   223,   147,   226,   184,   185,   186,   187,   188,   189,
     190,   191,   148,   149,   192,   193,   235,   240,   241,   242,
     243,   244,   245,   155,   191,   176,   174,   164,   246,   167,
     177,   178,     4,   199,   179,   198,   202,   183,   208,   210,
     213,   212,   217,   259,   215,  -116,  -117,  -118,   218,  -119,
    -120,  -121,   221,   262,   224,   229,   230,   232,   236,   237,
     239,   252,   253,   254,   219,   264,   266,   268,    74,   270,
     274,   275,   233,   267,   207,   112,   259,   276,     0,   153,
       0,   201,   127,     0,     0,     0,     0,     0,   197
};

static const yytype_int16 yycheck[] =
{
       4,   105,   128,   178,   156,   160,    19,     6,    10,     8,
      18,   198,   135,    20,    54,    20,    67,    67,     7,     8,
      71,    71,    54,    74,    20,    65,    66,   131,    68,   152,
      35,    38,    18,    65,    66,    67,    68,     6,    67,     8,
      57,    58,    59,    60,    61,    32,    54,   199,    56,   236,
      67,   155,    54,    54,    71,    56,    69,    70,    71,    72,
     164,    34,   217,    65,    66,    64,    68,    52,    54,   221,
      55,    42,   224,    69,    70,    71,    72,    18,     0,    65,
      66,   256,    68,   209,    70,    67,    90,    91,    92,    93,
      94,   195,   238,   197,   198,    99,    47,    71,    72,    11,
      12,    52,   248,    67,   250,     3,    67,    67,     8,   235,
      67,   215,    53,    54,    67,    56,    18,   221,    31,    18,
     224,    67,    18,    18,    65,    66,    67,    68,    18,    34,
      34,    20,   236,    20,    67,    86,    87,    88,    89,    45,
       4,     5,    43,   247,    37,     9,    10,    11,    18,    13,
      14,    15,    16,    17,    40,    40,    67,    21,    22,    23,
      57,    58,    59,    60,    61,    29,    30,    24,    25,    26,
      27,    28,   176,    37,    33,    67,    67,    41,    40,    67,
      44,    35,    19,    67,    19,    68,    67,    67,    67,    19,
      19,   195,    19,   197,    45,    46,    47,    48,    49,    50,
      51,    52,    19,    19,    55,    56,   210,    45,    46,    47,
      48,    49,    50,    18,    52,    18,    20,    45,    56,    32,
      67,    67,    10,    18,    39,    36,     6,    53,    19,    18,
      62,    67,    19,   237,    20,    18,    18,    18,    56,    18,
      18,    18,    18,   247,    18,    67,    65,    54,    40,    63,
      19,    19,    19,    19,    52,    19,    19,    19,    18,    20,
      19,    19,   207,   253,   174,    85,   270,   270,    -1,   127,
      -1,   165,    97,    -1,    -1,    -1,    -1,    -1,   160
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     4,     5,     9,    10,    11,    13,    14,    15,    16,
      17,    21,    22,    23,    29,    30,    37,    41,    44,    76,
      77,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    89,    90,    96,    99,   100,   101,   102,   121,
     122,   125,     6,     8,    64,     6,     8,    18,    54,    65,
      66,    68,    70,    98,   103,   104,    57,    58,    59,    60,
      61,    67,    71,   105,   106,   112,    67,     7,     8,    32,
      34,    67,    67,    42,    77,     0,     3,   126,    67,    67,
       8,    67,    67,   104,   104,    20,    69,    70,    71,    72,
      18,    18,    18,    18,    18,    31,    34,    20,   111,    20,
     113,    34,    67,    67,    37,    45,    43,    18,    40,    67,
      40,    19,   103,   104,   104,   104,   104,    71,    74,   112,
     112,   112,   112,   112,    67,    71,    67,   106,   112,    67,
      33,    35,   115,    67,   123,   124,    98,    68,    67,    92,
      67,    40,    67,    19,    19,    19,    19,    19,    19,    19,
      20,    38,   114,   111,   113,    18,    18,    53,    56,    98,
     112,   116,   117,   120,    45,    20,   115,    32,    24,    25,
      26,    27,    28,    95,    20,    91,    18,    67,    67,    39,
     115,    98,   101,    53,    45,    46,    47,    48,    49,    50,
      51,    52,    55,    56,   118,   119,   118,   119,    36,    18,
      98,   123,     6,    18,    54,    56,    93,    92,    19,   112,
      18,   114,    67,    62,   107,    20,    97,    19,    56,    52,
      55,    18,    98,   112,    18,    98,   112,   116,   101,    67,
      65,    94,    54,    91,   113,   112,    40,    63,    98,    19,
      45,    46,    47,    48,    49,    50,    56,   118,    98,   101,
      98,   101,    19,    19,    19,   113,   116,   108,   109,   112,
      97,    98,   112,    97,    19,    97,    19,    93,    19,   114,
      20,    11,    12,   110,    19,    19,   108
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    75,    76,    77,    77,    77,    77,    77,    77,    77,
      77,    77,    77,    77,    77,    77,    77,    77,    77,    77,
      77,    77,    77,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    88,    89,    90,    91,    91,
      92,    92,    93,    93,    93,    94,    95,    95,    95,    95,
      95,    96,    97,    97,    98,    98,    98,    98,    99,   100,
     101,   102,   103,   103,   104,   104,   104,   104,   104,   104,
     104,   105,   105,   105,   106,   106,   106,   106,   106,   106,
     106,   107,   107,   108,   108,   108,   109,   110,   110,   110,
     111,   111,   112,   112,   112,   113,   113,   114,   114,   114,
     115,   115,   116,   116,   116,   117,   117,   117,   117,   117,
     117,   117,   117,   117,   117,   117,   118,   118,   118,   118,
     118,   118,   118,   118,   119,   119,   119,   119,   119,   119,
     119,   119,   119,   119,   120,   120,   121,   122,   123,   124,
     124,   125,   126,   126
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     2,     2,     7,     9,    10,     5,     4,     0,     3,
       6,     3,     0,     1,     2,     1,     1,     1,     1,     1,
       1,     8,     0,     3,     1,     1,     1,     1,     4,     5,
       7,     2,     1,     3,     3,     3,     3,     3,     3,     2,
       1,     1,     2,     2,     4,     4,     4,     4,     4,     4,
       4,     0,     3,     0,     1,     3,     2,     0,     1,     1,
       0,     3,     3,     1,     3,     0,     3,     0,     6,     3,
       0,     2,     0,     1,     3,     6,     6,     5,     5,     5,
       5,     4,     3,     3,     3,     3,     1,     1,     1,     1,
       1,     1,     1,     2,     1,     1,     1,     1,     1,     1,
       1,     2,     1,     2,     1,     2,     7,     2,     3,     1,
       3,     4,     0,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (&yylloc, sql_string, sql_result, scanner, YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF

/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)


/* YYLOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

# ifndef YYLOCATION_PRINT

#  if defined YY_LOCATION_PRINT

   /* Temporary convenience wrapper in case some people defined the
      undocumented and private YY_LOCATION_PRINT macros.  */
#   define YYLOCATION_PRINT(File, Loc)  YY_LOCATION_PRINT(File, *(Loc))

#  elif defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static int
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  int res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
}

#   define YYLOCATION_PRINT  yy_location_print_

    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT(File, Loc)  YYLOCATION_PRINT(File, &(Loc))

#  else

#   define YYLOCATION_PRINT(File, Loc) ((void) 0)
    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT  YYLOCATION_PRINT

#  endif
# endif /* !defined YYLOCATION_PRINT */


# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value, Location, sql_string, sql_result, scanner); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, const char * sql_string, ParsedSqlResult * sql_result, void * scanner)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  YY_USE (yylocationp);
  YY_USE (sql_string);
  YY_USE (sql_result);
  YY_USE (scanner);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, const char * sql_string, ParsedSqlResult * sql_result, void * scanner)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  YYLOCATION_PRINT (yyo, yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yykind, yyvaluep, yylocationp, sql_string, sql_result, scanner);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp,
                 int yyrule, const char * sql_string, ParsedSqlResult * sql_result, void * scanner)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)],
                       &(yylsp[(yyi + 1) - (yynrhs)]), sql_string, sql_result, scanner);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule, sql_string, sql_result, scanner); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


/* Context of a parse error.  */
typedef struct
{
  yy_state_t *yyssp;
  yysymbol_kind_t yytoken;
  YYLTYPE *yylloc;
} yypcontext_t;

/* Put in YYARG at most YYARGN of the expected tokens given the
   current YYCTX, and return the number of tokens stored in YYARG.  If
   YYARG is null, return the number of expected tokens (guaranteed to
   be less than YYNTOKENS).  Return YYENOMEM on memory exhaustion.
   Return 0 if there are more than YYARGN expected tokens, yet fill
   YYARG up to YYARGN. */
static int
yypcontext_expected_tokens (const yypcontext_t *yyctx,
                            yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  int yyn = yypact[+*yyctx->yyssp];
  if (!yypact_value_is_default (yyn))
    {
      /* Start YYX at -YYN if negative to avoid negative indexes in
         YYCHECK.  In other words, skip the first -YYN actions for
         this state because they are default actions.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;
      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yyx;
      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
        if (yycheck[yyx + yyn] == yyx && yyx != YYSYMBOL_YYerror
            && !yytable_value_is_error (yytable[yyx + yyn]))
          {
            if (!yyarg)
              ++yycount;
            else if (yycount == yyargn)
              return 0;
            else
              yyarg[yycount++] = YY_CAST (yysymbol_kind_t, yyx);
          }
    }
  if (yyarg && yycount == 0 && 0 < yyargn)
    yyarg[0] = YYSYMBOL_YYEMPTY;
  return yycount;
}




#ifndef yystrlen
# if defined __GLIBC__ && defined _STRING_H
#  define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
# else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
# endif
#endif

#ifndef yystpcpy
# if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#  define yystpcpy stpcpy
# else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
# endif
#endif

#ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
      char const *yyp = yystr;
      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            else
              goto append;

          append:
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
#endif


static int
yy_syntax_error_arguments (const yypcontext_t *yyctx,
                           yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yyctx->yytoken != YYSYMBOL_YYEMPTY)
    {
      int yyn;
      if (yyarg)
        yyarg[yycount] = yyctx->yytoken;
      ++yycount;
      yyn = yypcontext_expected_tokens (yyctx,
                                        yyarg ? yyarg + 1 : yyarg, yyargn - 1);
      if (yyn == YYENOMEM)
        return YYENOMEM;
      else
        yycount += yyn;
    }
  return yycount;
}

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return -1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return YYENOMEM if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                const yypcontext_t *yyctx)
{
  enum { YYARGS_MAX = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  yysymbol_kind_t yyarg[YYARGS_MAX];
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* Actual size of YYARG. */
  int yycount = yy_syntax_error_arguments (yyctx, yyarg, YYARGS_MAX);
  if (yycount == YYENOMEM)
    return YYENOMEM;

  switch (yycount)
    {
#define YYCASE_(N, S)                       \
      case N:                               \
        yyformat = S;                       \
        break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
    }

  /* Compute error message size.  Don't count the "%s"s, but reserve
     room for the terminator.  */
  yysize = yystrlen (yyformat) - 2 * yycount + 1;
  {
    int yyi;
    for (yyi = 0; yyi < yycount; ++yyi)
      {
        YYPTRDIFF_T yysize1
          = yysize + yytnamerr (YY_NULLPTR, yytname[yyarg[yyi]]);
        if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
          yysize = yysize1;
        else
          return YYENOMEM;
      }
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return -1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yytname[yyarg[yyi++]]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, YYLTYPE *yylocationp, const char * sql_string, ParsedSqlResult * sql_result, void * scanner)
{
  YY_USE (yyvaluep);
  YY_USE (yylocationp);
  YY_USE (sql_string);
  YY_USE (sql_result);
  YY_USE (scanner);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}






/*----------.
| yyparse.  |
`----------*/

int
yyparse (const char * sql_string, ParsedSqlResult * sql_result, void * scanner)
{
/* Lookahead token kind.  */
int yychar;


/* The semantic value of the lookahead symbol.  */
/* Default value used for initialization, for pacifying older GCCs
   or non-GCC compilers.  */
YY_INITIAL_VALUE (static YYSTYPE yyval_default;)
YYSTYPE yylval YY_INITIAL_VALUE (= yyval_default);

/* Location data for the lookahead symbol.  */
static YYLTYPE yyloc_default
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
YYLTYPE yylloc = yyloc_default;

    /* Number of syntax errors so far.  */
    int yynerrs = 0;

    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

    /* The location stack: array, bottom, top.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls = yylsa;
    YYLTYPE *yylsp = yyls;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

  /* The locations where the error started and ended.  */
  YYLTYPE yyerror_range[3];

  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  yylsp[0] = yylloc;
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yyls1, yysize * YYSIZEOF (*yylsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
        yyls = yyls1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex (&yylval, &yylloc, scanner);
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      yyerror_range[1] = yylloc;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END
  *++yylsp = yylloc;

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location. */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  yyerror_range[1] = yyloc;
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* commands: command_wrapper opt_semicolon  */
#line 213 "./src/observer/sql/parser/yacc_sql.y"
  {
    std::unique_ptr<ParsedSqlNode> sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[-1].sql_node));
    sql_result->add_sql_node(std::move(sql_node));
  }
#line 1832 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 24: /* exit_stmt: EXIT  */
#line 244 "./src/observer/sql/parser/yacc_sql.y"
         {
      (void)yynerrs;  // 这么写为了消除yynerrs未使用的告警。如果你有更好的方法欢迎提PR
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXIT);
    }
#line 1841 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 25: /* help_stmt: HELP  */
#line 250 "./src/observer/sql/parser/yacc_sql.y"
         {
      (yyval.sql_node) = new ParsedSqlNode(SCF_HELP);
    }
#line 1849 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 26: /* sync_stmt: SYNC  */
#line 255 "./src/observer/sql/parser/yacc_sql.y"
         {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SYNC);
    }
#line 1857 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 27: /* begin_stmt: TRX_BEGIN  */
#line 261 "./src/observer/sql/parser/yacc_sql.y"
               {
      (yyval.sql_node) = new ParsedSqlNode(SCF_BEGIN);
    }
#line 1865 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 28: /* commit_stmt: TRX_COMMIT  */
#line 267 "./src/observer/sql/parser/yacc_sql.y"
               {
      (yyval.sql_node) = new ParsedSqlNode(SCF_COMMIT);
    }
#line 1873 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 29: /* rollback_stmt: TRX_ROLLBACK  */
#line 273 "./src/observer/sql/parser/yacc_sql.y"
                  {
      (yyval.sql_node) = new ParsedSqlNode(SCF_ROLLBACK);
    }
#line 1881 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 30: /* drop_table_stmt: DROP TABLE ID  */
#line 279 "./src/observer/sql/parser/yacc_sql.y"
                  {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DROP_TABLE);
      (yyval.sql_node)->drop_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 1891 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 31: /* show_tables_stmt: SHOW TABLES  */
#line 286 "./src/observer/sql/parser/yacc_sql.y"
                {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SHOW_TABLES);
    }
#line 1899 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 32: /* desc_table_stmt: DESC ID  */
#line 292 "./src/observer/sql/parser/yacc_sql.y"
             {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DESC_TABLE);
      (yyval.sql_node)->desc_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 1909 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 33: /* create_table_stmt: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE  */
#line 300 "./src/observer/sql/parser/yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CREATE_TABLE);
      CreateTableSqlNode &create_table = (yyval.sql_node)->create_table;
      create_table.relation_name = (yyvsp[-4].string);
      free((yyvsp[-4].string));

      std::vector<AttrInfoSqlNode> *src_attrs = (yyvsp[-1].attr_infos);

      if (src_attrs != nullptr) {
        create_table.attr_infos.swap(*src_attrs);
      }
      create_table.attr_infos.emplace_back(*(yyvsp[-2].attr_info));
      std::reverse(create_table.attr_infos.begin(), create_table.attr_infos.end());
      delete (yyvsp[-2].attr_info);
    }
#line 1929 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 34: /* create_index_stmt: CREATE INDEX ID ON ID LBRACE rel_attr attr_list RBRACE  */
#line 319 "./src/observer/sql/parser/yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CREATE_INDEX);
      CreateIndexSqlNode &create_index = (yyval.sql_node)->create_index;
      create_index.index_name = (yyvsp[-6].string);
      create_index.relation_name = (yyvsp[-4].string);
      create_index.attribute_names.push_back(*(yyvsp[-2].rel_attr));
      if ((yyvsp[-1].rel_attr_list) != nullptr) {
        create_index.attribute_names.insert(create_index.attribute_names.end(), (yyvsp[-1].rel_attr_list)->begin(), (yyvsp[-1].rel_attr_list)->end());
      }
      create_index.is_unique = false;
      free((yyvsp[-6].string));
      free((yyvsp[-4].string));
      free((yyvsp[-2].rel_attr));
    }
#line 1948 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 35: /* create_index_stmt: CREATE UNIQUE INDEX ID ON ID LBRACE rel_attr attr_list RBRACE  */
#line 333 "./src/observer/sql/parser/yacc_sql.y"
                                                                    {
        (yyval.sql_node) = new ParsedSqlNode(SCF_CREATE_INDEX);
        CreateIndexSqlNode &create_index = (yyval.sql_node)->create_index;
        create_index.index_name = (yyvsp[-6].string);
        create_index.relation_name = (yyvsp[-4].string);
        create_index.attribute_names.push_back(*(yyvsp[-2].rel_attr));
        if ((yyvsp[-1].rel_attr_list) != nullptr) {
           create_index.attribute_names.insert(create_index.attribute_names.end(), (yyvsp[-1].rel_attr_list)->begin(), (yyvsp[-1].rel_attr_list)->end());
        }
        create_index.is_unique = true;
        printf("uu ok!\n");
        free((yyvsp[-6].string));
        free((yyvsp[-4].string));
        free((yyvsp[-2].rel_attr));
    }
#line 1968 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 36: /* drop_index_stmt: DROP INDEX ID ON ID  */
#line 352 "./src/observer/sql/parser/yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DROP_INDEX);
      (yyval.sql_node)->drop_index.index_name = (yyvsp[-2].string);
      (yyval.sql_node)->drop_index.relation_name = (yyvsp[0].string);
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 1980 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 37: /* show_index_stmt: SHOW INDEX FROM ID  */
#line 363 "./src/observer/sql/parser/yacc_sql.y"
    {
        (yyval.sql_node) = new ParsedSqlNode(SCF_SHOW_INDEX);
        (yyval.sql_node)->show_index.relation_name = (yyvsp[0].string);
        free((yyvsp[0].string));
    }
#line 1990 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 38: /* attr_def_list: %empty  */
#line 372 "./src/observer/sql/parser/yacc_sql.y"
    {
      (yyval.attr_infos) = nullptr;
    }
#line 1998 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 39: /* attr_def_list: COMMA attr_def attr_def_list  */
#line 376 "./src/observer/sql/parser/yacc_sql.y"
    {
      if ((yyvsp[0].attr_infos) != nullptr) {
        (yyval.attr_infos) = (yyvsp[0].attr_infos);
      } else {
        (yyval.attr_infos) = new std::vector<AttrInfoSqlNode>;
      }
      (yyval.attr_infos)->emplace_back(*(yyvsp[-1].attr_info));
      delete (yyvsp[-1].attr_info);
    }
#line 2012 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 40: /* attr_def: ID type LBRACE number RBRACE nullable  */
#line 389 "./src/observer/sql/parser/yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-4].number);
      (yyval.attr_info)->name = (yyvsp[-5].string);
      (yyval.attr_info)->length = (yyvsp[-2].number);
      (yyval.attr_info)->is_nullable = (yyvsp[0].bools);
      free((yyvsp[-5].string));
    }
#line 2025 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 41: /* attr_def: ID type nullable  */
#line 398 "./src/observer/sql/parser/yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-1].number);
      (yyval.attr_info)->name = (yyvsp[-2].string);
      if((yyval.attr_info)->type == TEXTS) {
      (yyval.attr_info)->length = 65535;
      }else{
        (yyval.attr_info)->length = 4;
      }
      (yyval.attr_info)->is_nullable = (yyvsp[0].bools);
      free((yyvsp[-2].string));
    }
#line 2042 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 42: /* nullable: %empty  */
#line 413 "./src/observer/sql/parser/yacc_sql.y"
    {
        (yyval.bools) = false;
    }
#line 2050 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 43: /* nullable: NULL_T  */
#line 416 "./src/observer/sql/parser/yacc_sql.y"
             {
        (yyval.bools) = true;
    }
#line 2058 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 44: /* nullable: NOT NULL_T  */
#line 419 "./src/observer/sql/parser/yacc_sql.y"
                 {
        (yyval.bools) = false;
    }
#line 2066 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 45: /* number: NUMBER  */
#line 424 "./src/observer/sql/parser/yacc_sql.y"
           {(yyval.number) = (yyvsp[0].number);}
#line 2072 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 46: /* type: INT_T  */
#line 427 "./src/observer/sql/parser/yacc_sql.y"
               { (yyval.number)=INTS; }
#line 2078 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 47: /* type: STRING_T  */
#line 428 "./src/observer/sql/parser/yacc_sql.y"
               { (yyval.number)=CHARS; }
#line 2084 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 48: /* type: FLOAT_T  */
#line 429 "./src/observer/sql/parser/yacc_sql.y"
               { (yyval.number)=FLOATS; }
#line 2090 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 49: /* type: DATE_T  */
#line 430 "./src/observer/sql/parser/yacc_sql.y"
              { (yyval.number)=DATES; }
#line 2096 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 50: /* type: TEXT_T  */
#line 431 "./src/observer/sql/parser/yacc_sql.y"
              { (yyval.number)=TEXTS; }
#line 2102 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 51: /* insert_stmt: INSERT INTO ID VALUES LBRACE value value_list RBRACE  */
#line 435 "./src/observer/sql/parser/yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_INSERT);
      (yyval.sql_node)->insertion.relation_name = (yyvsp[-5].string);
      if ((yyvsp[-1].value_list) != nullptr) {
        (yyval.sql_node)->insertion.values.swap(*(yyvsp[-1].value_list));
      }
      (yyval.sql_node)->insertion.values.emplace_back(*(yyvsp[-2].value));
      std::reverse((yyval.sql_node)->insertion.values.begin(), (yyval.sql_node)->insertion.values.end());
      delete (yyvsp[-2].value);
      free((yyvsp[-5].string));
    }
#line 2118 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 52: /* value_list: %empty  */
#line 450 "./src/observer/sql/parser/yacc_sql.y"
    {
      (yyval.value_list) = nullptr;
    }
#line 2126 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 53: /* value_list: COMMA value value_list  */
#line 453 "./src/observer/sql/parser/yacc_sql.y"
                              {
      if ((yyvsp[0].value_list) != nullptr) {
        (yyval.value_list) = (yyvsp[0].value_list);
      } else {
        (yyval.value_list) = new std::vector<Value>;
      }
      (yyval.value_list)->emplace_back(*(yyvsp[-1].value));
      delete (yyvsp[-1].value);
    }
#line 2140 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 54: /* value: NUMBER  */
#line 464 "./src/observer/sql/parser/yacc_sql.y"
           {
      (yyval.value) = new Value((int)(yyvsp[0].number));
      (yyloc) = (yylsp[0]);
    }
#line 2149 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 55: /* value: FLOAT  */
#line 468 "./src/observer/sql/parser/yacc_sql.y"
           {
      (yyval.value) = new Value((float)(yyvsp[0].floats));
      (yyloc) = (yylsp[0]);
    }
#line 2158 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 56: /* value: SSS  */
#line 472 "./src/observer/sql/parser/yacc_sql.y"
         {
      char *tmp = common::substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
      (yyval.value) = new Value(tmp);
      free(tmp);
    }
#line 2168 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 57: /* value: NULL_T  */
#line 477 "./src/observer/sql/parser/yacc_sql.y"
            {
      (yyval.value) = new Value();
      (yyval.value)->set_null();
      //@$ = @1;
    }
#line 2178 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 58: /* delete_stmt: DELETE FROM ID where  */
#line 486 "./src/observer/sql/parser/yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DELETE);
      (yyval.sql_node)->deletion.relation_name = (yyvsp[-1].string);
      if ((yyvsp[0].condition_list) != nullptr) {
        (yyval.sql_node)->deletion.conditions.swap(*(yyvsp[0].condition_list));
        delete (yyvsp[0].condition_list);
      }
      free((yyvsp[-1].string));
    }
#line 2192 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 59: /* update_stmt: UPDATE ID SET update_set_list where  */
#line 498 "./src/observer/sql/parser/yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_UPDATE);
      (yyval.sql_node)->update.relation_name = (yyvsp[-3].string);
      (yyval.sql_node)->update.update_set = *(yyvsp[-1].update_set_list);
      if ((yyvsp[0].condition_list) != nullptr) {
        (yyval.sql_node)->update.conditions.swap(*(yyvsp[0].condition_list));
        delete (yyvsp[0].condition_list);
      }
      free((yyvsp[-3].string));
      delete (yyvsp[-1].update_set_list);
    }
#line 2208 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 60: /* select_stmt: SELECT select_attr FROM ID rel_list where order_by  */
#line 512 "./src/observer/sql/parser/yacc_sql.y"
    {
      std::vector<std::string> relations;

      (yyval.sql_node) = new ParsedSqlNode(SCF_SELECT);
      if ((yyvsp[-5].rel_attr_list) != nullptr) {
        (yyval.sql_node)->selection.attributes.swap(*(yyvsp[-5].rel_attr_list));
        delete (yyvsp[-5].rel_attr_list);
      }
      if ((yyvsp[-2].join_relation_list) != nullptr) {

        for(auto item: *(yyvsp[-2].join_relation_list)) {
            relations.emplace_back(item.relation);
            if(!item.conditions.empty()){
                auto join_condition = new std::vector<ConditionSqlNode>;
                join_condition->insert(join_condition->end(),item.conditions.begin(), item.conditions.end());
                (yyval.sql_node)->selection.join_conditions.emplace_back(*join_condition);
                delete join_condition;
            }
        }
        std::reverse((yyval.sql_node)->selection.join_conditions.begin(), (yyval.sql_node)->selection.join_conditions.end());
        (yyval.sql_node)->selection.relations.swap(relations);
        delete (yyvsp[-2].join_relation_list);
      }
      (yyval.sql_node)->selection.relations.push_back((yyvsp[-3].string));
      std::reverse((yyval.sql_node)->selection.relations.begin(), (yyval.sql_node)->selection.relations.end());

      if ((yyvsp[-1].condition_list) != nullptr) {
        (yyval.sql_node)->selection.conditions.insert((yyval.sql_node)->selection.conditions.end(), (yyvsp[-1].condition_list)->begin(), (yyvsp[-1].condition_list)->end());
        //$$->selection.conditions.swap(*$6);
        delete (yyvsp[-1].condition_list);
      }

      if ((yyvsp[0].order_by_item_list) != nullptr) {
        // $$->selection.order_by_items.insert($$->selection.conditions.end(), $7->begin(), $7->end());
        (yyval.sql_node)->selection.order_by_items.swap(*(yyvsp[0].order_by_item_list));
        delete (yyvsp[0].order_by_item_list);
      }

      free((yyvsp[-3].string));
    }
#line 2253 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 61: /* calc_stmt: CALC expression_list  */
#line 556 "./src/observer/sql/parser/yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CALC);
      std::reverse((yyvsp[0].expression_list)->begin(), (yyvsp[0].expression_list)->end());
      (yyval.sql_node)->calc.expressions.swap(*(yyvsp[0].expression_list));
      delete (yyvsp[0].expression_list);
    }
#line 2264 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 62: /* expression_list: expression  */
#line 566 "./src/observer/sql/parser/yacc_sql.y"
    {
      (yyval.expression_list) = new std::vector<Expression*>;
      (yyval.expression_list)->emplace_back((yyvsp[0].expression));
    }
#line 2273 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 63: /* expression_list: expression COMMA expression_list  */
#line 571 "./src/observer/sql/parser/yacc_sql.y"
    {
      if ((yyvsp[0].expression_list) != nullptr) {
        (yyval.expression_list) = (yyvsp[0].expression_list);
      } else {
        (yyval.expression_list) = new std::vector<Expression *>;
      }
      (yyval.expression_list)->emplace_back((yyvsp[-2].expression));
    }
#line 2286 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 64: /* expression: expression '+' expression  */
#line 581 "./src/observer/sql/parser/yacc_sql.y"
                              {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::ADD, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2294 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 65: /* expression: expression '-' expression  */
#line 584 "./src/observer/sql/parser/yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::SUB, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2302 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 66: /* expression: expression '*' expression  */
#line 587 "./src/observer/sql/parser/yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::MUL, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2310 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 67: /* expression: expression '/' expression  */
#line 590 "./src/observer/sql/parser/yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::DIV, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2318 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 68: /* expression: LBRACE expression RBRACE  */
#line 593 "./src/observer/sql/parser/yacc_sql.y"
                               {
      (yyval.expression) = (yyvsp[-1].expression);
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
    }
#line 2327 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 69: /* expression: '-' expression  */
#line 597 "./src/observer/sql/parser/yacc_sql.y"
                                  {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::NEGATIVE, (yyvsp[0].expression), nullptr, sql_string, &(yyloc));
    }
#line 2335 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 70: /* expression: value  */
#line 600 "./src/observer/sql/parser/yacc_sql.y"
            {
      (yyval.expression) = new ValueExpr(*(yyvsp[0].value));
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      delete (yyvsp[0].value);
    }
#line 2345 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 71: /* select_attr: '*'  */
#line 608 "./src/observer/sql/parser/yacc_sql.y"
        {
      (yyval.rel_attr_list) = new std::vector<RelAttrSqlNode>;
      RelAttrSqlNode attr;
      attr.relation_name  = "";
      attr.attribute_name = "*";
      (yyval.rel_attr_list)->emplace_back(attr);
    }
#line 2357 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 72: /* select_attr: rel_attr attr_list  */
#line 615 "./src/observer/sql/parser/yacc_sql.y"
                         {
      if ((yyvsp[0].rel_attr_list) != nullptr) {
        (yyval.rel_attr_list) = (yyvsp[0].rel_attr_list);
      } else {
        (yyval.rel_attr_list) = new std::vector<RelAttrSqlNode>;
      }
      (yyval.rel_attr_list)->emplace_back(*(yyvsp[-1].rel_attr));
      delete (yyvsp[-1].rel_attr);
    }
#line 2371 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 73: /* select_attr: agg_func agg_func_list  */
#line 624 "./src/observer/sql/parser/yacc_sql.y"
                             {
      if ((yyvsp[0].rel_attr_list) != nullptr) {
        (yyval.rel_attr_list) = (yyvsp[0].rel_attr_list);
      } else {
        (yyval.rel_attr_list) = new std::vector<RelAttrSqlNode>;
      }
      (yyval.rel_attr_list)->emplace_back(*(yyvsp[-1].agg_func));
      delete (yyvsp[-1].agg_func);
    }
#line 2385 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 74: /* agg_func: COUNT LBRACE '*' RBRACE  */
#line 636 "./src/observer/sql/parser/yacc_sql.y"
                            {
        (yyval.agg_func) = new RelAttrSqlNode;
        (yyval.agg_func)->relation_name  = "";
        (yyval.agg_func)->attribute_name = "*";
        (yyval.agg_func)->agg_func = AggFunc::A_COUNT;
        (yyval.agg_func)->alias = "COUNT(*)";
    }
#line 2397 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 75: /* agg_func: COUNT LBRACE '1' RBRACE  */
#line 643 "./src/observer/sql/parser/yacc_sql.y"
                              {
        (yyval.agg_func) = new RelAttrSqlNode;
        (yyval.agg_func)->relation_name  = "";
        (yyval.agg_func)->attribute_name = "*";
        (yyval.agg_func)->agg_func = AggFunc::A_COUNT;
        (yyval.agg_func)->alias = "COUNT(1)";
    }
#line 2409 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 76: /* agg_func: COUNT LBRACE rel_attr RBRACE  */
#line 650 "./src/observer/sql/parser/yacc_sql.y"
                                   {
        (yyvsp[-1].rel_attr)->agg_func = AggFunc::A_COUNT;
        (yyval.agg_func) = std::move((yyvsp[-1].rel_attr));
    }
#line 2418 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 77: /* agg_func: SUM LBRACE rel_attr RBRACE  */
#line 654 "./src/observer/sql/parser/yacc_sql.y"
                                 {
        (yyvsp[-1].rel_attr)->agg_func = AggFunc::A_SUM;
        (yyval.agg_func) = std::move((yyvsp[-1].rel_attr));
    }
#line 2427 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 78: /* agg_func: MIN LBRACE rel_attr RBRACE  */
#line 658 "./src/observer/sql/parser/yacc_sql.y"
                                 {
        (yyvsp[-1].rel_attr)->agg_func = AggFunc::A_MIN;
        (yyval.agg_func) = std::move((yyvsp[-1].rel_attr));
    }
#line 2436 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 79: /* agg_func: MAX LBRACE rel_attr RBRACE  */
#line 662 "./src/observer/sql/parser/yacc_sql.y"
                                 {
        (yyvsp[-1].rel_attr)->agg_func = AggFunc::A_MAX;
        (yyval.agg_func) = std::move((yyvsp[-1].rel_attr));
    }
#line 2445 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 80: /* agg_func: AVG LBRACE rel_attr RBRACE  */
#line 666 "./src/observer/sql/parser/yacc_sql.y"
                                 {
        (yyvsp[-1].rel_attr)->agg_func = AggFunc::A_AVG;
        (yyval.agg_func) = std::move((yyvsp[-1].rel_attr));
    }
#line 2454 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 81: /* order_by: %empty  */
#line 674 "./src/observer/sql/parser/yacc_sql.y"
    {
        (yyval.order_by_item_list) = nullptr;
    }
#line 2462 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 82: /* order_by: ORDER BY order_by_item_list  */
#line 677 "./src/observer/sql/parser/yacc_sql.y"
                                  {
        std::reverse((yyvsp[0].order_by_item_list)->begin(), (yyvsp[0].order_by_item_list)->end());
        (yyval.order_by_item_list) = (yyvsp[0].order_by_item_list);
    }
#line 2471 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 83: /* order_by_item_list: %empty  */
#line 685 "./src/observer/sql/parser/yacc_sql.y"
    {
        (yyval.order_by_item_list) = nullptr;
    }
#line 2479 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 84: /* order_by_item_list: order_by_item  */
#line 688 "./src/observer/sql/parser/yacc_sql.y"
                    {
        (yyval.order_by_item_list) = new std::vector<OrderByItem>;
        (yyval.order_by_item_list)->emplace_back(*(yyvsp[0].order_by_item));
        delete (yyvsp[0].order_by_item);
    }
#line 2489 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 85: /* order_by_item_list: order_by_item COMMA order_by_item_list  */
#line 693 "./src/observer/sql/parser/yacc_sql.y"
                                             {
        (yyval.order_by_item_list) = (yyvsp[0].order_by_item_list);
        (yyval.order_by_item_list)->emplace_back(*(yyvsp[-2].order_by_item));
        delete (yyvsp[-2].order_by_item);
    }
#line 2499 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 86: /* order_by_item: rel_attr order_type  */
#line 700 "./src/observer/sql/parser/yacc_sql.y"
                        {
      (yyval.order_by_item) = new OrderByItem;
      (yyval.order_by_item)->attr = *(yyvsp[-1].rel_attr);
      (yyval.order_by_item)->order_type = (yyvsp[0].order_type);
      free((yyvsp[-1].rel_attr));
    }
#line 2510 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 87: /* order_type: %empty  */
#line 710 "./src/observer/sql/parser/yacc_sql.y"
    {
        (yyval.order_type) = OrderByType::SORT_ASC;
    }
#line 2518 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 88: /* order_type: ASC  */
#line 713 "./src/observer/sql/parser/yacc_sql.y"
          {
        (yyval.order_type) = OrderByType::SORT_ASC;
    }
#line 2526 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 89: /* order_type: DESC  */
#line 716 "./src/observer/sql/parser/yacc_sql.y"
           {
        (yyval.order_type) = OrderByType::SORT_DESC;
    }
#line 2534 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 90: /* agg_func_list: %empty  */
#line 723 "./src/observer/sql/parser/yacc_sql.y"
    {
        (yyval.rel_attr_list) = nullptr;
    }
#line 2542 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 91: /* agg_func_list: COMMA agg_func agg_func_list  */
#line 726 "./src/observer/sql/parser/yacc_sql.y"
                                   {
        if ((yyvsp[0].rel_attr_list) != nullptr) {
            (yyval.rel_attr_list) = (yyvsp[0].rel_attr_list);
        } else {
            (yyval.rel_attr_list) = new std::vector<RelAttrSqlNode>;
        }
        (yyval.rel_attr_list)->emplace_back(*(yyvsp[-1].agg_func));
        delete (yyvsp[-1].agg_func);
    }
#line 2556 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 92: /* rel_attr: ID DOT '*'  */
#line 738 "./src/observer/sql/parser/yacc_sql.y"
               {
          (yyval.rel_attr) = new RelAttrSqlNode;
          (yyval.rel_attr)->relation_name  = (yyvsp[-2].string);
          (yyval.rel_attr)->attribute_name = "*";
          free((yyvsp[-2].string));
    }
#line 2567 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 93: /* rel_attr: ID  */
#line 744 "./src/observer/sql/parser/yacc_sql.y"
         {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->attribute_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 2577 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 94: /* rel_attr: ID DOT ID  */
#line 749 "./src/observer/sql/parser/yacc_sql.y"
                {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->relation_name  = (yyvsp[-2].string);
      (yyval.rel_attr)->attribute_name = (yyvsp[0].string);
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 2589 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 95: /* attr_list: %empty  */
#line 760 "./src/observer/sql/parser/yacc_sql.y"
    {
      (yyval.rel_attr_list) = nullptr;
    }
#line 2597 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 96: /* attr_list: COMMA rel_attr attr_list  */
#line 763 "./src/observer/sql/parser/yacc_sql.y"
                               {
      if ((yyvsp[0].rel_attr_list) != nullptr) {
        (yyval.rel_attr_list) = (yyvsp[0].rel_attr_list);
      } else {
        (yyval.rel_attr_list) = new std::vector<RelAttrSqlNode>;
      }

      (yyval.rel_attr_list)->emplace_back(*(yyvsp[-1].rel_attr));
      delete (yyvsp[-1].rel_attr);
    }
#line 2612 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 97: /* rel_list: %empty  */
#line 777 "./src/observer/sql/parser/yacc_sql.y"
    {
      (yyval.join_relation_list) = nullptr;
    }
#line 2620 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 98: /* rel_list: INNER JOIN ID ON condition_list rel_list  */
#line 780 "./src/observer/sql/parser/yacc_sql.y"
                                               {
      if ((yyvsp[0].join_relation_list) != nullptr) {
        (yyval.join_relation_list) = (yyvsp[0].join_relation_list);
      } else {
        (yyval.join_relation_list) = new std::vector<RelWithConditions>;
      }
      auto tmp = new RelWithConditions;
      tmp->relation = (yyvsp[-3].string);
      tmp->conditions.swap(*(yyvsp[-1].condition_list));
      (yyval.join_relation_list)->emplace_back(*tmp);
      free((yyvsp[-3].string));
      free((yyvsp[-1].condition_list));
    }
#line 2638 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 99: /* rel_list: COMMA ID rel_list  */
#line 793 "./src/observer/sql/parser/yacc_sql.y"
                        {
      if ((yyvsp[0].join_relation_list) != nullptr) {
        (yyval.join_relation_list) = (yyvsp[0].join_relation_list);
      } else {
        (yyval.join_relation_list) = new std::vector<RelWithConditions>;
      }
      auto tmp = new RelWithConditions;
      tmp->relation = (yyvsp[-1].string);
      (yyval.join_relation_list)->emplace_back(*tmp);
      free((yyvsp[-1].string));
    }
#line 2654 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 100: /* where: %empty  */
#line 807 "./src/observer/sql/parser/yacc_sql.y"
    {
      (yyval.condition_list) = nullptr;
    }
#line 2662 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 101: /* where: WHERE condition_list  */
#line 810 "./src/observer/sql/parser/yacc_sql.y"
                           {
      (yyval.condition_list) = (yyvsp[0].condition_list);
    }
#line 2670 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 102: /* condition_list: %empty  */
#line 816 "./src/observer/sql/parser/yacc_sql.y"
    {
      (yyval.condition_list) = nullptr;
    }
#line 2678 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 103: /* condition_list: condition  */
#line 819 "./src/observer/sql/parser/yacc_sql.y"
                {
      (yyval.condition_list) = new std::vector<ConditionSqlNode>;
      (yyval.condition_list)->emplace_back(*(yyvsp[0].condition));
      delete (yyvsp[0].condition);
    }
#line 2688 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 104: /* condition_list: condition AND condition_list  */
#line 824 "./src/observer/sql/parser/yacc_sql.y"
                                   {
      (yyval.condition_list) = (yyvsp[0].condition_list);
      (yyval.condition_list)->emplace_back(*(yyvsp[-2].condition));
      delete (yyvsp[-2].condition);
    }
#line 2698 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 105: /* condition: value sub_comp_op LBRACE value value_list RBRACE  */
#line 832 "./src/observer/sql/parser/yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_type = VALUE;
      (yyval.condition)->left_value = *(yyvsp[-5].value);
      (yyval.condition)->right_type = VALUE_LIST;
      if ((yyvsp[-1].value_list) != nullptr) {
        (yyval.condition)->right_values.swap(*(yyvsp[-1].value_list));
      }
      (yyval.condition)->right_values.emplace_back(*(yyvsp[-2].value));
      (yyval.condition)->comp = (yyvsp[-4].comp);

      delete (yyvsp[-5].value);
      delete (yyvsp[-2].value);
    }
#line 2717 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 106: /* condition: rel_attr sub_comp_op LBRACE value value_list RBRACE  */
#line 847 "./src/observer/sql/parser/yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_type = ATTR;
      (yyval.condition)->left_attr = *(yyvsp[-5].rel_attr);
      (yyval.condition)->right_type = VALUE_LIST;
      if ((yyvsp[-1].value_list) != nullptr) {
        (yyval.condition)->right_values.swap(*(yyvsp[-1].value_list));
      }
      (yyval.condition)->right_values.emplace_back(*(yyvsp[-2].value));
      (yyval.condition)->comp = (yyvsp[-4].comp);

      delete (yyvsp[-5].rel_attr);
      delete (yyvsp[-2].value);
    }
#line 2736 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 107: /* condition: rel_attr sub_comp_op LBRACE select_stmt RBRACE  */
#line 862 "./src/observer/sql/parser/yacc_sql.y"
      {
        (yyval.condition) = new ConditionSqlNode;
        (yyval.condition)->left_type = ATTR;
        (yyval.condition)->left_attr = *(yyvsp[-4].rel_attr);
        (yyval.condition)->right_type = SUB_QUERY;
        (yyval.condition)->right_sub_selection = (yyvsp[-1].sql_node);
        (yyval.condition)->comp = (yyvsp[-3].comp);

        delete (yyvsp[-4].rel_attr);
      }
#line 2751 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 108: /* condition: value sub_comp_op LBRACE select_stmt RBRACE  */
#line 873 "./src/observer/sql/parser/yacc_sql.y"
      {
        (yyval.condition) = new ConditionSqlNode;
        (yyval.condition)->left_type = VALUE;
        (yyval.condition)->left_value = *(yyvsp[-4].value);
        (yyval.condition)->right_type = SUB_QUERY;
        (yyval.condition)->right_sub_selection = (yyvsp[-1].sql_node);
        (yyval.condition)->comp = (yyvsp[-3].comp);

        delete (yyvsp[-4].value);
      }
#line 2766 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 109: /* condition: LBRACE select_stmt RBRACE sub_comp_op value  */
#line 884 "./src/observer/sql/parser/yacc_sql.y"
        {
          (yyval.condition) = new ConditionSqlNode;
          (yyval.condition)->left_type = SUB_QUERY;
          (yyval.condition)->left_sub_selection = (yyvsp[-3].sql_node);
          (yyval.condition)->right_type = VALUE;
          (yyval.condition)->right_value = *(yyvsp[0].value);
          (yyval.condition)->comp = (yyvsp[-1].comp);

          delete (yyvsp[0].value);
        }
#line 2781 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 110: /* condition: LBRACE select_stmt RBRACE sub_comp_op rel_attr  */
#line 895 "./src/observer/sql/parser/yacc_sql.y"
      {
        (yyval.condition) = new ConditionSqlNode;
        (yyval.condition)->left_type = SUB_QUERY;
        (yyval.condition)->left_sub_selection = (yyvsp[-3].sql_node);
        (yyval.condition)->right_type = ATTR;
        (yyval.condition)->right_attr = *(yyvsp[0].rel_attr);
        (yyval.condition)->comp = (yyvsp[-1].comp);

        delete (yyvsp[0].rel_attr);
      }
#line 2796 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 111: /* condition: exists LBRACE select_stmt RBRACE  */
#line 906 "./src/observer/sql/parser/yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_type = NULL_TYPE;
      (yyval.condition)->right_type = SUB_QUERY;
      (yyval.condition)->right_sub_selection = (yyvsp[-1].sql_node);
      (yyval.condition)->comp = (yyvsp[-3].comp);

    }
#line 2809 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 112: /* condition: rel_attr comp_op value  */
#line 915 "./src/observer/sql/parser/yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_type = ATTR;
      (yyval.condition)->left_attr = *(yyvsp[-2].rel_attr);
      (yyval.condition)->right_type = VALUE;
      (yyval.condition)->right_value = *(yyvsp[0].value);
      (yyval.condition)->comp = (yyvsp[-1].comp);

      delete (yyvsp[-2].rel_attr);
      delete (yyvsp[0].value);
    }
#line 2825 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 113: /* condition: value comp_op value  */
#line 927 "./src/observer/sql/parser/yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_type = VALUE;
      (yyval.condition)->left_value = *(yyvsp[-2].value);
      (yyval.condition)->right_type = VALUE;
      (yyval.condition)->right_value = *(yyvsp[0].value);
      (yyval.condition)->comp = (yyvsp[-1].comp);

      delete (yyvsp[-2].value);
      delete (yyvsp[0].value);
    }
#line 2841 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 114: /* condition: rel_attr comp_op rel_attr  */
#line 939 "./src/observer/sql/parser/yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_type = ATTR;
      (yyval.condition)->left_attr = *(yyvsp[-2].rel_attr);
      (yyval.condition)->right_type = ATTR;
      (yyval.condition)->right_attr = *(yyvsp[0].rel_attr);
      (yyval.condition)->comp = (yyvsp[-1].comp);

      delete (yyvsp[-2].rel_attr);
      delete (yyvsp[0].rel_attr);
    }
#line 2857 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 115: /* condition: value comp_op rel_attr  */
#line 951 "./src/observer/sql/parser/yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_type = VALUE;
      (yyval.condition)->left_value = *(yyvsp[-2].value);
      (yyval.condition)->right_type = ATTR;
      (yyval.condition)->right_attr = *(yyvsp[0].rel_attr);
      (yyval.condition)->comp = (yyvsp[-1].comp);

      delete (yyvsp[-2].value);
      delete (yyvsp[0].rel_attr);
    }
#line 2873 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 116: /* sub_comp_op: EQ  */
#line 966 "./src/observer/sql/parser/yacc_sql.y"
         { (yyval.comp) = EQUAL_TO; }
#line 2879 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 117: /* sub_comp_op: LT  */
#line 967 "./src/observer/sql/parser/yacc_sql.y"
         { (yyval.comp) = LESS_THAN; }
#line 2885 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 118: /* sub_comp_op: GT  */
#line 968 "./src/observer/sql/parser/yacc_sql.y"
         { (yyval.comp) = GREAT_THAN; }
#line 2891 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 119: /* sub_comp_op: LE  */
#line 969 "./src/observer/sql/parser/yacc_sql.y"
         { (yyval.comp) = LESS_EQUAL; }
#line 2897 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 120: /* sub_comp_op: GE  */
#line 970 "./src/observer/sql/parser/yacc_sql.y"
         { (yyval.comp) = GREAT_EQUAL; }
#line 2903 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 121: /* sub_comp_op: NE  */
#line 971 "./src/observer/sql/parser/yacc_sql.y"
         { (yyval.comp) = NOT_EQUAL; }
#line 2909 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 122: /* sub_comp_op: IN_T  */
#line 972 "./src/observer/sql/parser/yacc_sql.y"
           { (yyval.comp) = IN;}
#line 2915 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 123: /* sub_comp_op: NOT IN_T  */
#line 973 "./src/observer/sql/parser/yacc_sql.y"
               {(yyval.comp) = NOT_IN;}
#line 2921 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 124: /* comp_op: EQ  */
#line 977 "./src/observer/sql/parser/yacc_sql.y"
         { (yyval.comp) = EQUAL_TO; }
#line 2927 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 125: /* comp_op: LT  */
#line 978 "./src/observer/sql/parser/yacc_sql.y"
         { (yyval.comp) = LESS_THAN; }
#line 2933 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 126: /* comp_op: GT  */
#line 979 "./src/observer/sql/parser/yacc_sql.y"
         { (yyval.comp) = GREAT_THAN; }
#line 2939 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 127: /* comp_op: LE  */
#line 980 "./src/observer/sql/parser/yacc_sql.y"
         { (yyval.comp) = LESS_EQUAL; }
#line 2945 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 128: /* comp_op: GE  */
#line 981 "./src/observer/sql/parser/yacc_sql.y"
         { (yyval.comp) = GREAT_EQUAL; }
#line 2951 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 129: /* comp_op: NE  */
#line 982 "./src/observer/sql/parser/yacc_sql.y"
         { (yyval.comp) = NOT_EQUAL; }
#line 2957 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 130: /* comp_op: LIKE_C  */
#line 983 "./src/observer/sql/parser/yacc_sql.y"
            {(yyval.comp) = LIKE;}
#line 2963 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 131: /* comp_op: NOT LIKE_C  */
#line 984 "./src/observer/sql/parser/yacc_sql.y"
                {(yyval.comp) = NOT_LIKE;}
#line 2969 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 132: /* comp_op: IS  */
#line 985 "./src/observer/sql/parser/yacc_sql.y"
         {(yyval.comp) = IS_NULL;}
#line 2975 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 133: /* comp_op: IS NOT  */
#line 986 "./src/observer/sql/parser/yacc_sql.y"
             {(yyval.comp) = NOT_NULL;}
#line 2981 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 134: /* exists: EXISTS_T  */
#line 990 "./src/observer/sql/parser/yacc_sql.y"
               {(yyval.comp) = EXISTS;}
#line 2987 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 135: /* exists: NOT EXISTS_T  */
#line 991 "./src/observer/sql/parser/yacc_sql.y"
                   {(yyval.comp) = NOT_EXISTS;}
#line 2993 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 136: /* load_data_stmt: LOAD DATA INFILE SSS INTO TABLE ID  */
#line 996 "./src/observer/sql/parser/yacc_sql.y"
    {
      char *tmp_file_name = common::substr((yyvsp[-3].string), 1, strlen((yyvsp[-3].string)) - 2);
      
      (yyval.sql_node) = new ParsedSqlNode(SCF_LOAD_DATA);
      (yyval.sql_node)->load_data.relation_name = (yyvsp[0].string);
      (yyval.sql_node)->load_data.file_name = tmp_file_name;
      free((yyvsp[0].string));
      free(tmp_file_name);
    }
#line 3007 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 137: /* explain_stmt: EXPLAIN command_wrapper  */
#line 1009 "./src/observer/sql/parser/yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXPLAIN);
      (yyval.sql_node)->explain.sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[0].sql_node));
    }
#line 3016 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 138: /* update_set: ID EQ value  */
#line 1017 "./src/observer/sql/parser/yacc_sql.y"
    {
        (yyval.sql_node) = new ParsedSqlNode(SCF_UPDATE_SET);
        (yyval.sql_node)->update_set.name  = (yyvsp[-2].string);
        (yyval.sql_node)->update_set.value = *(yyvsp[0].value);
        free((yyvsp[-2].string));
        delete (yyvsp[0].value);
    }
#line 3028 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 139: /* update_set_list: update_set  */
#line 1028 "./src/observer/sql/parser/yacc_sql.y"
    {
          (yyval.update_set_list) = new std::vector<UpdateSetSqlNode>;
          (yyval.update_set_list)->push_back((yyvsp[0].sql_node)->update_set);
          delete (yyvsp[0].sql_node);
    }
#line 3038 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 140: /* update_set_list: update_set_list COMMA update_set  */
#line 1034 "./src/observer/sql/parser/yacc_sql.y"
     {
           (yyval.update_set_list)->push_back((yyvsp[0].sql_node)->update_set);
           delete (yyvsp[0].sql_node);
     }
#line 3047 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 141: /* set_variable_stmt: SET ID EQ value  */
#line 1042 "./src/observer/sql/parser/yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SET_VARIABLE);
      (yyval.sql_node)->set_variable.name  = (yyvsp[-2].string);
      (yyval.sql_node)->set_variable.value = *(yyvsp[0].value);
      free((yyvsp[-2].string));
      delete (yyvsp[0].value);
    }
#line 3059 "./src/observer/sql/parser/yacc_sql.cpp"
    break;


#line 3063 "./src/observer/sql/parser/yacc_sql.cpp"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      {
        yypcontext_t yyctx
          = {yyssp, yytoken, &yylloc};
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == -1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *,
                             YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (yymsg)
              {
                yysyntax_error_status
                  = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
                yymsgp = yymsg;
              }
            else
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = YYENOMEM;
              }
          }
        yyerror (&yylloc, sql_string, sql_result, scanner, yymsgp);
        if (yysyntax_error_status == YYENOMEM)
          YYNOMEM;
      }
    }

  yyerror_range[1] = yylloc;
  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval, &yylloc, sql_string, sql_result, scanner);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, yylsp, sql_string, sql_result, scanner);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  ++yylsp;
  YYLLOC_DEFAULT (*yylsp, yyerror_range, 2);

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (&yylloc, sql_string, sql_result, scanner, YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc, sql_string, sql_result, scanner);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, yylsp, sql_string, sql_result, scanner);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
  return yyresult;
}

#line 1054 "./src/observer/sql/parser/yacc_sql.y"

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
