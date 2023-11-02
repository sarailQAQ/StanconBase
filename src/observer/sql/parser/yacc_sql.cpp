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
  YYSYMBOL_NUMBER = 64,                    /* NUMBER  */
  YYSYMBOL_FLOAT = 65,                     /* FLOAT  */
  YYSYMBOL_ID = 66,                        /* ID  */
  YYSYMBOL_SSS = 67,                       /* SSS  */
  YYSYMBOL_68_ = 68,                       /* '+'  */
  YYSYMBOL_69_ = 69,                       /* '-'  */
  YYSYMBOL_70_ = 70,                       /* '*'  */
  YYSYMBOL_71_ = 71,                       /* '/'  */
  YYSYMBOL_UMINUS = 72,                    /* UMINUS  */
  YYSYMBOL_73_1_ = 73,                     /* '1'  */
  YYSYMBOL_YYACCEPT = 74,                  /* $accept  */
  YYSYMBOL_commands = 75,                  /* commands  */
  YYSYMBOL_command_wrapper = 76,           /* command_wrapper  */
  YYSYMBOL_exit_stmt = 77,                 /* exit_stmt  */
  YYSYMBOL_help_stmt = 78,                 /* help_stmt  */
  YYSYMBOL_sync_stmt = 79,                 /* sync_stmt  */
  YYSYMBOL_begin_stmt = 80,                /* begin_stmt  */
  YYSYMBOL_commit_stmt = 81,               /* commit_stmt  */
  YYSYMBOL_rollback_stmt = 82,             /* rollback_stmt  */
  YYSYMBOL_drop_table_stmt = 83,           /* drop_table_stmt  */
  YYSYMBOL_show_tables_stmt = 84,          /* show_tables_stmt  */
  YYSYMBOL_desc_table_stmt = 85,           /* desc_table_stmt  */
  YYSYMBOL_create_table_stmt = 86,         /* create_table_stmt  */
  YYSYMBOL_create_index_stmt = 87,         /* create_index_stmt  */
  YYSYMBOL_drop_index_stmt = 88,           /* drop_index_stmt  */
  YYSYMBOL_show_index_stmt = 89,           /* show_index_stmt  */
  YYSYMBOL_attr_def_list = 90,             /* attr_def_list  */
  YYSYMBOL_attr_def = 91,                  /* attr_def  */
  YYSYMBOL_nullable = 92,                  /* nullable  */
  YYSYMBOL_number = 93,                    /* number  */
  YYSYMBOL_type = 94,                      /* type  */
  YYSYMBOL_insert_stmt = 95,               /* insert_stmt  */
  YYSYMBOL_value_list = 96,                /* value_list  */
  YYSYMBOL_value = 97,                     /* value  */
  YYSYMBOL_delete_stmt = 98,               /* delete_stmt  */
  YYSYMBOL_update_stmt = 99,               /* update_stmt  */
  YYSYMBOL_select_stmt = 100,              /* select_stmt  */
  YYSYMBOL_calc_stmt = 101,                /* calc_stmt  */
  YYSYMBOL_expression_list = 102,          /* expression_list  */
  YYSYMBOL_expression = 103,               /* expression  */
  YYSYMBOL_select_attr = 104,              /* select_attr  */
  YYSYMBOL_agg_func = 105,                 /* agg_func  */
  YYSYMBOL_order_by = 106,                 /* order_by  */
  YYSYMBOL_order_by_item_list = 107,       /* order_by_item_list  */
  YYSYMBOL_order_by_item = 108,            /* order_by_item  */
  YYSYMBOL_order_type = 109,               /* order_type  */
  YYSYMBOL_agg_func_list = 110,            /* agg_func_list  */
  YYSYMBOL_rel_attr = 111,                 /* rel_attr  */
  YYSYMBOL_attr_list = 112,                /* attr_list  */
  YYSYMBOL_rel_list = 113,                 /* rel_list  */
  YYSYMBOL_where = 114,                    /* where  */
  YYSYMBOL_condition_list = 115,           /* condition_list  */
  YYSYMBOL_condition = 116,                /* condition  */
  YYSYMBOL_sub_comp_op = 117,              /* sub_comp_op  */
  YYSYMBOL_comp_op = 118,                  /* comp_op  */
  YYSYMBOL_in = 119,                       /* in  */
  YYSYMBOL_exists = 120,                   /* exists  */
  YYSYMBOL_load_data_stmt = 121,           /* load_data_stmt  */
  YYSYMBOL_explain_stmt = 122,             /* explain_stmt  */
  YYSYMBOL_set_variable_stmt = 123,        /* set_variable_stmt  */
  YYSYMBOL_opt_semicolon = 124             /* opt_semicolon  */
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
typedef yytype_uint8 yy_state_t;

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
#define YYFINAL  74
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   245

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  74
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  51
/* YYNRULES -- Number of rules.  */
#define YYNRULES  139
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  255

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   323


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
       2,     2,    70,    68,     2,    69,     2,    71,     2,    73,
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
      65,    66,    67,    72
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   209,   209,   217,   218,   219,   220,   221,   222,   223,
     224,   225,   226,   227,   228,   229,   230,   231,   232,   233,
     234,   235,   236,   237,   241,   247,   252,   258,   264,   270,
     276,   283,   289,   296,   315,   332,   343,   353,   356,   369,
     378,   394,   397,   400,   405,   408,   409,   410,   411,   412,
     415,   431,   434,   445,   449,   453,   458,   466,   478,   493,
     537,   547,   552,   563,   566,   569,   572,   575,   579,   582,
     590,   597,   606,   618,   625,   632,   636,   640,   644,   648,
     656,   659,   667,   670,   675,   682,   692,   695,   698,   705,
     708,   720,   726,   731,   742,   745,   759,   762,   775,   789,
     792,   798,   801,   806,   813,   828,   843,   855,   867,   877,
     889,   901,   913,   929,   930,   931,   932,   933,   934,   935,
     936,   940,   941,   942,   943,   944,   945,   946,   947,   948,
     949,   952,   953,   956,   957,   961,   974,   982,   992,   993
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
  "AVG", "ORDER", "BY", "NUMBER", "FLOAT", "ID", "SSS", "'+'", "'-'",
  "'*'", "'/'", "UMINUS", "'1'", "$accept", "commands", "command_wrapper",
  "exit_stmt", "help_stmt", "sync_stmt", "begin_stmt", "commit_stmt",
  "rollback_stmt", "drop_table_stmt", "show_tables_stmt",
  "desc_table_stmt", "create_table_stmt", "create_index_stmt",
  "drop_index_stmt", "show_index_stmt", "attr_def_list", "attr_def",
  "nullable", "number", "type", "insert_stmt", "value_list", "value",
  "delete_stmt", "update_stmt", "select_stmt", "calc_stmt",
  "expression_list", "expression", "select_attr", "agg_func", "order_by",
  "order_by_item_list", "order_by_item", "order_type", "agg_func_list",
  "rel_attr", "attr_list", "rel_list", "where", "condition_list",
  "condition", "sub_comp_op", "comp_op", "in", "exists", "load_data_stmt",
  "explain_stmt", "set_variable_stmt", "opt_semicolon", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-214)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-119)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      97,    33,    53,    -1,    85,   -44,    44,  -214,    -3,     6,
     -20,  -214,  -214,  -214,  -214,  -214,    -6,    58,    97,   103,
     101,  -214,  -214,  -214,  -214,  -214,  -214,  -214,  -214,  -214,
    -214,  -214,  -214,  -214,  -214,  -214,  -214,  -214,  -214,  -214,
    -214,  -214,    39,    49,    50,    56,    -1,  -214,  -214,  -214,
    -214,    -1,  -214,  -214,     8,   105,   106,   107,   110,   111,
      99,  -214,    98,   113,   115,  -214,  -214,   102,    71,    73,
     112,    95,   104,  -214,  -214,  -214,  -214,   130,   114,  -214,
     121,   -13,  -214,    -1,    -1,    -1,    -1,    -1,   -54,    84,
      84,    84,    84,   -56,    86,    38,  -214,    84,  -214,    87,
     129,   137,   116,   -33,   109,   118,   120,   122,  -214,  -214,
       3,     3,  -214,  -214,   154,   158,   159,   160,   162,   166,
     168,  -214,  -214,   -15,   113,   115,  -214,   171,   -29,  -214,
     145,  -214,   161,   132,   172,   173,  -214,  -214,  -214,  -214,
    -214,  -214,  -214,  -214,   128,   156,   137,  -214,  -214,   -33,
    -214,   143,   119,   119,  -214,   163,   179,   -33,   192,  -214,
    -214,  -214,  -214,  -214,    -7,   118,   181,    84,   -15,   135,
     140,   183,  -214,   186,   187,   188,   189,   190,   191,   155,
    -214,  -214,    17,   194,    16,   195,   196,    16,   197,   -29,
     200,   137,   150,   153,  -214,   164,  -214,   172,  -214,   115,
    -214,   180,   165,  -214,   -33,   202,  -214,  -214,  -214,   200,
    -214,  -214,   -33,   200,  -214,  -214,   -33,  -214,   203,  -214,
    -214,  -214,   205,  -214,  -214,   206,   -29,    84,   183,  -214,
     207,   183,   208,   183,  -214,    11,  -214,   -15,  -214,   199,
      79,  -214,  -214,   210,  -214,   211,  -214,  -214,    84,  -214,
    -214,  -214,  -214,  -214,  -214
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,    26,     0,     0,
       0,    27,    28,    29,    25,    24,     0,     0,     0,     0,
     138,    23,    22,    15,    16,    17,    18,     9,    10,    11,
       8,    12,    13,    14,     5,     7,     6,     4,     3,    19,
      20,    21,     0,     0,     0,     0,     0,    56,    53,    54,
      55,     0,    69,    60,    61,     0,     0,     0,     0,     0,
      92,    70,     0,    89,    94,    32,    31,     0,     0,     0,
       0,     0,     0,   136,     1,   139,     2,     0,     0,    30,
       0,     0,    68,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    72,     0,    71,     0,
       0,    99,     0,     0,     0,     0,     0,     0,    67,    62,
      63,    64,    65,    66,     0,     0,     0,     0,     0,     0,
       0,    93,    91,    96,    89,    94,    36,     0,   101,    57,
       0,   137,     0,     0,    37,     0,    35,    73,    74,    75,
      76,    78,    77,    79,     0,     0,    99,    90,    95,     0,
     133,     0,     0,     0,   100,   102,     0,     0,     0,    45,
      46,    47,    48,    49,    41,     0,     0,     0,    96,     0,
      80,    51,   134,   121,   122,   123,   124,   125,   126,   129,
     119,   127,     0,     0,     0,     0,     0,     0,     0,   101,
       0,    99,     0,     0,    42,     0,    40,    37,    33,    94,
      98,     0,     0,    59,     0,     0,   130,   120,   128,     0,
     110,   112,     0,     0,   109,   111,     0,   103,     0,    58,
     135,    44,     0,    43,    38,     0,   101,    82,    51,    50,
       0,    51,     0,    51,   108,    41,    34,    96,    81,    83,
      86,    52,   107,     0,   106,     0,    39,    97,    82,    88,
      87,    85,   104,   105,    84
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -214,  -214,   213,  -214,  -214,  -214,  -214,  -214,  -214,  -214,
    -214,  -214,  -214,  -214,  -214,  -214,    35,    68,     0,  -214,
    -214,  -214,  -213,   -95,  -214,  -214,  -183,  -214,   151,   -42,
    -214,   141,  -214,   -11,  -214,  -214,   117,    -4,  -124,  -166,
    -143,  -176,  -214,    89,    90,    92,  -214,  -214,  -214,  -214,
    -214
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,   166,   134,   196,   222,
     164,    34,   205,    52,    35,    36,    37,    38,    53,    54,
      62,    63,   203,   238,   239,   251,    96,   153,    98,   146,
     129,   154,   155,   183,   184,   185,   156,    39,    40,    41,
      76
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      64,   148,   200,   170,    81,   144,   108,   218,   131,    82,
     121,   193,    60,   217,   122,   241,   114,    46,   243,   115,
     245,    47,    65,   145,   150,    47,   230,   151,    83,    68,
     232,    48,    49,   152,    50,    48,    49,    60,    50,    42,
      69,    43,   110,   111,   112,   113,    70,   194,   219,   195,
     237,    66,    67,    47,   171,    84,    85,    86,    87,    44,
      71,    45,   191,    48,    49,   194,    50,   195,    51,   207,
      47,   247,   208,    86,    87,   225,    84,    85,    86,    87,
      48,    49,    60,    50,   116,   117,   118,   119,   120,   210,
     249,   250,   214,   125,   152,    55,    56,    57,    58,    59,
      72,     1,     2,    74,    75,    77,     3,     4,     5,   228,
       6,     7,     8,     9,    10,    78,    79,   231,    11,    12,
      13,   233,    80,    88,    89,    90,    14,    15,    91,    92,
      93,   152,    94,    95,    16,    97,    99,   100,    17,   101,
     103,    18,    55,    56,    57,    58,    59,   104,   105,   102,
      60,    60,   123,   126,   106,    61,   159,   160,   161,   162,
     163,   107,   127,   199,   173,   174,   175,   176,   177,   178,
     179,   180,   128,   137,   181,   182,   132,   138,   139,   140,
     211,   141,   130,   215,   133,   142,   135,   143,   136,   149,
     157,   167,   165,   158,   168,   169,   172,   190,   192,   189,
     198,   201,   202,   204,  -113,  -114,  -115,  -116,  -117,  -118,
       4,   206,   209,   212,   213,   216,   220,   221,   223,   248,
     226,   229,   234,   240,   235,   236,   242,   244,   227,   252,
     253,    73,   224,   197,   109,   246,   124,   254,     0,     0,
       0,   147,   186,   187,   240,   188
};

static const yytype_int16 yycheck[] =
{
       4,   125,   168,   146,    46,    20,    19,   190,   103,    51,
      66,    18,    66,   189,    70,   228,    70,    18,   231,    73,
     233,    54,    66,    38,    53,    54,   209,    56,    20,    32,
     213,    64,    65,   128,    67,    64,    65,    66,    67,     6,
      34,     8,    84,    85,    86,    87,    66,    54,   191,    56,
     226,     7,     8,    54,   149,    68,    69,    70,    71,     6,
      66,     8,   157,    64,    65,    54,    67,    56,    69,    52,
      54,   237,    55,    70,    71,   199,    68,    69,    70,    71,
      64,    65,    66,    67,    88,    89,    90,    91,    92,   184,
      11,    12,   187,    97,   189,    57,    58,    59,    60,    61,
      42,     4,     5,     0,     3,    66,     9,    10,    11,   204,
      13,    14,    15,    16,    17,    66,    66,   212,    21,    22,
      23,   216,    66,    18,    18,    18,    29,    30,    18,    18,
      31,   226,    34,    20,    37,    20,    34,    66,    41,    66,
      45,    44,    57,    58,    59,    60,    61,    43,    18,    37,
      66,    66,    66,    66,    40,    70,    24,    25,    26,    27,
      28,    40,    33,   167,    45,    46,    47,    48,    49,    50,
      51,    52,    35,    19,    55,    56,    67,    19,    19,    19,
     184,    19,    66,   187,    66,    19,    66,    19,    66,    18,
      45,    18,    20,    32,    66,    39,    53,    18,     6,    36,
      19,    66,    62,    20,    18,    18,    18,    18,    18,    18,
      10,    56,    18,    18,    18,    18,    66,    64,    54,    20,
      40,    19,    19,   227,    19,    19,    19,    19,    63,    19,
      19,    18,   197,   165,    83,   235,    95,   248,    -1,    -1,
      -1,   124,   153,   153,   248,   153
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     4,     5,     9,    10,    11,    13,    14,    15,    16,
      17,    21,    22,    23,    29,    30,    37,    41,    44,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,    95,    98,    99,   100,   101,   121,
     122,   123,     6,     8,     6,     8,    18,    54,    64,    65,
      67,    69,    97,   102,   103,    57,    58,    59,    60,    61,
      66,    70,   104,   105,   111,    66,     7,     8,    32,    34,
      66,    66,    42,    76,     0,     3,   124,    66,    66,    66,
      66,   103,   103,    20,    68,    69,    70,    71,    18,    18,
      18,    18,    18,    31,    34,    20,   110,    20,   112,    34,
      66,    66,    37,    45,    43,    18,    40,    40,    19,   102,
     103,   103,   103,   103,    70,    73,   111,   111,   111,   111,
     111,    66,    70,    66,   105,   111,    66,    33,    35,   114,
      66,    97,    67,    66,    91,    66,    66,    19,    19,    19,
      19,    19,    19,    19,    20,    38,   113,   110,   112,    18,
      53,    56,    97,   111,   115,   116,   120,    45,    32,    24,
      25,    26,    27,    28,    94,    20,    90,    18,    66,    39,
     114,    97,    53,    45,    46,    47,    48,    49,    50,    51,
      52,    55,    56,   117,   118,   119,   117,   118,   119,    36,
      18,    97,     6,    18,    54,    56,    92,    91,    19,   111,
     113,    66,    62,   106,    20,    96,    56,    52,    55,    18,
      97,   111,    18,    18,    97,   111,    18,   115,   100,   114,
      66,    64,    93,    54,    90,   112,    40,    63,    97,    19,
     100,    97,   100,    97,    19,    19,    19,   115,   107,   108,
     111,    96,    19,    96,    19,    96,    92,   113,    20,    11,
      12,   109,    19,    19,   107
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    74,    75,    76,    76,    76,    76,    76,    76,    76,
      76,    76,    76,    76,    76,    76,    76,    76,    76,    76,
      76,    76,    76,    76,    77,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    90,    90,    91,
      91,    92,    92,    92,    93,    94,    94,    94,    94,    94,
      95,    96,    96,    97,    97,    97,    97,    98,    99,   100,
     101,   102,   102,   103,   103,   103,   103,   103,   103,   103,
     104,   104,   104,   105,   105,   105,   105,   105,   105,   105,
     106,   106,   107,   107,   107,   108,   109,   109,   109,   110,
     110,   111,   111,   111,   112,   112,   113,   113,   113,   114,
     114,   115,   115,   115,   116,   116,   116,   116,   116,   116,
     116,   116,   116,   117,   117,   117,   117,   117,   117,   117,
     117,   118,   118,   118,   118,   118,   118,   118,   118,   118,
     118,   119,   119,   120,   120,   121,   122,   123,   124,   124
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     2,     2,     7,     9,     5,     4,     0,     3,     6,
       3,     0,     1,     2,     1,     1,     1,     1,     1,     1,
       8,     0,     3,     1,     1,     1,     1,     4,     7,     7,
       2,     1,     3,     3,     3,     3,     3,     3,     2,     1,
       1,     2,     2,     4,     4,     4,     4,     4,     4,     4,
       0,     3,     0,     1,     3,     2,     0,     1,     1,     0,
       3,     3,     1,     3,     0,     3,     0,     6,     3,     0,
       2,     0,     1,     3,     6,     6,     5,     5,     4,     3,
       3,     3,     3,     1,     1,     1,     1,     1,     1,     1,
       2,     1,     1,     1,     1,     1,     1,     1,     2,     1,
       2,     1,     2,     1,     2,     7,     2,     4,     0,     1
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
#line 210 "./src/observer/sql/parser/yacc_sql.y"
  {
    std::unique_ptr<ParsedSqlNode> sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[-1].sql_node));
    sql_result->add_sql_node(std::move(sql_node));
  }
#line 1814 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 24: /* exit_stmt: EXIT  */
#line 241 "./src/observer/sql/parser/yacc_sql.y"
         {
      (void)yynerrs;  // 这么写为了消除yynerrs未使用的告警。如果你有更好的方法欢迎提PR
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXIT);
    }
#line 1823 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 25: /* help_stmt: HELP  */
#line 247 "./src/observer/sql/parser/yacc_sql.y"
         {
      (yyval.sql_node) = new ParsedSqlNode(SCF_HELP);
    }
#line 1831 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 26: /* sync_stmt: SYNC  */
#line 252 "./src/observer/sql/parser/yacc_sql.y"
         {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SYNC);
    }
#line 1839 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 27: /* begin_stmt: TRX_BEGIN  */
#line 258 "./src/observer/sql/parser/yacc_sql.y"
               {
      (yyval.sql_node) = new ParsedSqlNode(SCF_BEGIN);
    }
#line 1847 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 28: /* commit_stmt: TRX_COMMIT  */
#line 264 "./src/observer/sql/parser/yacc_sql.y"
               {
      (yyval.sql_node) = new ParsedSqlNode(SCF_COMMIT);
    }
#line 1855 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 29: /* rollback_stmt: TRX_ROLLBACK  */
#line 270 "./src/observer/sql/parser/yacc_sql.y"
                  {
      (yyval.sql_node) = new ParsedSqlNode(SCF_ROLLBACK);
    }
#line 1863 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 30: /* drop_table_stmt: DROP TABLE ID  */
#line 276 "./src/observer/sql/parser/yacc_sql.y"
                  {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DROP_TABLE);
      (yyval.sql_node)->drop_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 1873 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 31: /* show_tables_stmt: SHOW TABLES  */
#line 283 "./src/observer/sql/parser/yacc_sql.y"
                {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SHOW_TABLES);
    }
#line 1881 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 32: /* desc_table_stmt: DESC ID  */
#line 289 "./src/observer/sql/parser/yacc_sql.y"
             {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DESC_TABLE);
      (yyval.sql_node)->desc_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 1891 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 33: /* create_table_stmt: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE  */
#line 297 "./src/observer/sql/parser/yacc_sql.y"
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
#line 1911 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 34: /* create_index_stmt: CREATE INDEX ID ON ID LBRACE rel_attr attr_list RBRACE  */
#line 316 "./src/observer/sql/parser/yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CREATE_INDEX);
      CreateIndexSqlNode &create_index = (yyval.sql_node)->create_index;
      create_index.index_name = (yyvsp[-6].string);
      create_index.relation_name = (yyvsp[-4].string);
      create_index.attribute_names.push_back(*(yyvsp[-2].rel_attr));
      if ((yyvsp[-1].rel_attr_list) != nullptr) {
        create_index.attribute_names.insert(create_index.attribute_names.end(), (yyvsp[-1].rel_attr_list)->begin(), (yyvsp[-1].rel_attr_list)->end());
      }
      free((yyvsp[-6].string));
      free((yyvsp[-4].string));
      free((yyvsp[-2].rel_attr));
    }
#line 1929 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 35: /* drop_index_stmt: DROP INDEX ID ON ID  */
#line 333 "./src/observer/sql/parser/yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DROP_INDEX);
      (yyval.sql_node)->drop_index.index_name = (yyvsp[-2].string);
      (yyval.sql_node)->drop_index.relation_name = (yyvsp[0].string);
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 1941 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 36: /* show_index_stmt: SHOW INDEX FROM ID  */
#line 344 "./src/observer/sql/parser/yacc_sql.y"
    {
        (yyval.sql_node) = new ParsedSqlNode(SCF_SHOW_INDEX);
        (yyval.sql_node)->show_index.relation_name = (yyvsp[0].string);
        free((yyvsp[0].string));
    }
#line 1951 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 37: /* attr_def_list: %empty  */
#line 353 "./src/observer/sql/parser/yacc_sql.y"
    {
      (yyval.attr_infos) = nullptr;
    }
#line 1959 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 38: /* attr_def_list: COMMA attr_def attr_def_list  */
#line 357 "./src/observer/sql/parser/yacc_sql.y"
    {
      if ((yyvsp[0].attr_infos) != nullptr) {
        (yyval.attr_infos) = (yyvsp[0].attr_infos);
      } else {
        (yyval.attr_infos) = new std::vector<AttrInfoSqlNode>;
      }
      (yyval.attr_infos)->emplace_back(*(yyvsp[-1].attr_info));
      delete (yyvsp[-1].attr_info);
    }
#line 1973 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 39: /* attr_def: ID type LBRACE number RBRACE nullable  */
#line 370 "./src/observer/sql/parser/yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-4].number);
      (yyval.attr_info)->name = (yyvsp[-5].string);
      (yyval.attr_info)->length = (yyvsp[-2].number);
      (yyval.attr_info)->is_nullable = (yyvsp[0].bools);
      free((yyvsp[-5].string));
    }
#line 1986 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 40: /* attr_def: ID type nullable  */
#line 379 "./src/observer/sql/parser/yacc_sql.y"
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
#line 2003 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 41: /* nullable: %empty  */
#line 394 "./src/observer/sql/parser/yacc_sql.y"
    {
        (yyval.bools) = false;
    }
#line 2011 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 42: /* nullable: NULL_T  */
#line 397 "./src/observer/sql/parser/yacc_sql.y"
             {
        (yyval.bools) = true;
    }
#line 2019 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 43: /* nullable: NOT NULL_T  */
#line 400 "./src/observer/sql/parser/yacc_sql.y"
                 {
        (yyval.bools) = false;
    }
#line 2027 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 44: /* number: NUMBER  */
#line 405 "./src/observer/sql/parser/yacc_sql.y"
           {(yyval.number) = (yyvsp[0].number);}
#line 2033 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 45: /* type: INT_T  */
#line 408 "./src/observer/sql/parser/yacc_sql.y"
               { (yyval.number)=INTS; }
#line 2039 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 46: /* type: STRING_T  */
#line 409 "./src/observer/sql/parser/yacc_sql.y"
               { (yyval.number)=CHARS; }
#line 2045 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 47: /* type: FLOAT_T  */
#line 410 "./src/observer/sql/parser/yacc_sql.y"
               { (yyval.number)=FLOATS; }
#line 2051 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 48: /* type: DATE_T  */
#line 411 "./src/observer/sql/parser/yacc_sql.y"
              { (yyval.number)=DATES; }
#line 2057 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 49: /* type: TEXT_T  */
#line 412 "./src/observer/sql/parser/yacc_sql.y"
              { (yyval.number)=TEXTS; }
#line 2063 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 50: /* insert_stmt: INSERT INTO ID VALUES LBRACE value value_list RBRACE  */
#line 416 "./src/observer/sql/parser/yacc_sql.y"
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
#line 2079 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 51: /* value_list: %empty  */
#line 431 "./src/observer/sql/parser/yacc_sql.y"
    {
      (yyval.value_list) = nullptr;
    }
#line 2087 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 52: /* value_list: COMMA value value_list  */
#line 434 "./src/observer/sql/parser/yacc_sql.y"
                              {
      if ((yyvsp[0].value_list) != nullptr) {
        (yyval.value_list) = (yyvsp[0].value_list);
      } else {
        (yyval.value_list) = new std::vector<Value>;
      }
      (yyval.value_list)->emplace_back(*(yyvsp[-1].value));
      delete (yyvsp[-1].value);
    }
#line 2101 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 53: /* value: NUMBER  */
#line 445 "./src/observer/sql/parser/yacc_sql.y"
           {
      (yyval.value) = new Value((int)(yyvsp[0].number));
      (yyloc) = (yylsp[0]);
    }
#line 2110 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 54: /* value: FLOAT  */
#line 449 "./src/observer/sql/parser/yacc_sql.y"
           {
      (yyval.value) = new Value((float)(yyvsp[0].floats));
      (yyloc) = (yylsp[0]);
    }
#line 2119 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 55: /* value: SSS  */
#line 453 "./src/observer/sql/parser/yacc_sql.y"
         {
      char *tmp = common::substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
      (yyval.value) = new Value(tmp);
      free(tmp);
    }
#line 2129 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 56: /* value: NULL_T  */
#line 458 "./src/observer/sql/parser/yacc_sql.y"
            {
      (yyval.value) = new Value();
      (yyval.value)->set_null();
      //@$ = @1;
    }
#line 2139 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 57: /* delete_stmt: DELETE FROM ID where  */
#line 467 "./src/observer/sql/parser/yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DELETE);
      (yyval.sql_node)->deletion.relation_name = (yyvsp[-1].string);
      if ((yyvsp[0].condition_list) != nullptr) {
        (yyval.sql_node)->deletion.conditions.swap(*(yyvsp[0].condition_list));
        delete (yyvsp[0].condition_list);
      }
      free((yyvsp[-1].string));
    }
#line 2153 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 58: /* update_stmt: UPDATE ID SET ID EQ value where  */
#line 479 "./src/observer/sql/parser/yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_UPDATE);
      (yyval.sql_node)->update.relation_name = (yyvsp[-5].string);
      (yyval.sql_node)->update.attribute_name = (yyvsp[-3].string);
      (yyval.sql_node)->update.value = *(yyvsp[-1].value);
      if ((yyvsp[0].condition_list) != nullptr) {
        (yyval.sql_node)->update.conditions.swap(*(yyvsp[0].condition_list));
        delete (yyvsp[0].condition_list);
      }
      free((yyvsp[-5].string));
      free((yyvsp[-3].string));
    }
#line 2170 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 59: /* select_stmt: SELECT select_attr FROM ID rel_list where order_by  */
#line 494 "./src/observer/sql/parser/yacc_sql.y"
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
#line 2215 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 60: /* calc_stmt: CALC expression_list  */
#line 538 "./src/observer/sql/parser/yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CALC);
      std::reverse((yyvsp[0].expression_list)->begin(), (yyvsp[0].expression_list)->end());
      (yyval.sql_node)->calc.expressions.swap(*(yyvsp[0].expression_list));
      delete (yyvsp[0].expression_list);
    }
#line 2226 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 61: /* expression_list: expression  */
#line 548 "./src/observer/sql/parser/yacc_sql.y"
    {
      (yyval.expression_list) = new std::vector<Expression*>;
      (yyval.expression_list)->emplace_back((yyvsp[0].expression));
    }
#line 2235 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 62: /* expression_list: expression COMMA expression_list  */
#line 553 "./src/observer/sql/parser/yacc_sql.y"
    {
      if ((yyvsp[0].expression_list) != nullptr) {
        (yyval.expression_list) = (yyvsp[0].expression_list);
      } else {
        (yyval.expression_list) = new std::vector<Expression *>;
      }
      (yyval.expression_list)->emplace_back((yyvsp[-2].expression));
    }
#line 2248 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 63: /* expression: expression '+' expression  */
#line 563 "./src/observer/sql/parser/yacc_sql.y"
                              {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::ADD, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2256 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 64: /* expression: expression '-' expression  */
#line 566 "./src/observer/sql/parser/yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::SUB, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2264 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 65: /* expression: expression '*' expression  */
#line 569 "./src/observer/sql/parser/yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::MUL, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2272 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 66: /* expression: expression '/' expression  */
#line 572 "./src/observer/sql/parser/yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::DIV, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2280 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 67: /* expression: LBRACE expression RBRACE  */
#line 575 "./src/observer/sql/parser/yacc_sql.y"
                               {
      (yyval.expression) = (yyvsp[-1].expression);
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
    }
#line 2289 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 68: /* expression: '-' expression  */
#line 579 "./src/observer/sql/parser/yacc_sql.y"
                                  {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::NEGATIVE, (yyvsp[0].expression), nullptr, sql_string, &(yyloc));
    }
#line 2297 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 69: /* expression: value  */
#line 582 "./src/observer/sql/parser/yacc_sql.y"
            {
      (yyval.expression) = new ValueExpr(*(yyvsp[0].value));
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      delete (yyvsp[0].value);
    }
#line 2307 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 70: /* select_attr: '*'  */
#line 590 "./src/observer/sql/parser/yacc_sql.y"
        {
      (yyval.rel_attr_list) = new std::vector<RelAttrSqlNode>;
      RelAttrSqlNode attr;
      attr.relation_name  = "";
      attr.attribute_name = "*";
      (yyval.rel_attr_list)->emplace_back(attr);
    }
#line 2319 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 71: /* select_attr: rel_attr attr_list  */
#line 597 "./src/observer/sql/parser/yacc_sql.y"
                         {
      if ((yyvsp[0].rel_attr_list) != nullptr) {
        (yyval.rel_attr_list) = (yyvsp[0].rel_attr_list);
      } else {
        (yyval.rel_attr_list) = new std::vector<RelAttrSqlNode>;
      }
      (yyval.rel_attr_list)->emplace_back(*(yyvsp[-1].rel_attr));
      delete (yyvsp[-1].rel_attr);
    }
#line 2333 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 72: /* select_attr: agg_func agg_func_list  */
#line 606 "./src/observer/sql/parser/yacc_sql.y"
                             {
      if ((yyvsp[0].rel_attr_list) != nullptr) {
        (yyval.rel_attr_list) = (yyvsp[0].rel_attr_list);
      } else {
        (yyval.rel_attr_list) = new std::vector<RelAttrSqlNode>;
      }
      (yyval.rel_attr_list)->emplace_back(*(yyvsp[-1].agg_func));
      delete (yyvsp[-1].agg_func);
    }
#line 2347 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 73: /* agg_func: COUNT LBRACE '*' RBRACE  */
#line 618 "./src/observer/sql/parser/yacc_sql.y"
                            {
        (yyval.agg_func) = new RelAttrSqlNode;
        (yyval.agg_func)->relation_name  = "";
        (yyval.agg_func)->attribute_name = "*";
        (yyval.agg_func)->agg_func = AggFunc::A_COUNT;
        (yyval.agg_func)->alias = "COUNT(*)";
    }
#line 2359 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 74: /* agg_func: COUNT LBRACE '1' RBRACE  */
#line 625 "./src/observer/sql/parser/yacc_sql.y"
                              {
        (yyval.agg_func) = new RelAttrSqlNode;
        (yyval.agg_func)->relation_name  = "";
        (yyval.agg_func)->attribute_name = "*";
        (yyval.agg_func)->agg_func = AggFunc::A_COUNT;
        (yyval.agg_func)->alias = "COUNT(1)";
    }
#line 2371 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 75: /* agg_func: COUNT LBRACE rel_attr RBRACE  */
#line 632 "./src/observer/sql/parser/yacc_sql.y"
                                   {
        (yyvsp[-1].rel_attr)->agg_func = AggFunc::A_COUNT;
        (yyval.agg_func) = std::move((yyvsp[-1].rel_attr));
    }
#line 2380 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 76: /* agg_func: SUM LBRACE rel_attr RBRACE  */
#line 636 "./src/observer/sql/parser/yacc_sql.y"
                                 {
        (yyvsp[-1].rel_attr)->agg_func = AggFunc::A_SUM;
        (yyval.agg_func) = std::move((yyvsp[-1].rel_attr));
    }
#line 2389 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 77: /* agg_func: MIN LBRACE rel_attr RBRACE  */
#line 640 "./src/observer/sql/parser/yacc_sql.y"
                                 {
        (yyvsp[-1].rel_attr)->agg_func = AggFunc::A_MIN;
        (yyval.agg_func) = std::move((yyvsp[-1].rel_attr));
    }
#line 2398 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 78: /* agg_func: MAX LBRACE rel_attr RBRACE  */
#line 644 "./src/observer/sql/parser/yacc_sql.y"
                                 {
        (yyvsp[-1].rel_attr)->agg_func = AggFunc::A_MAX;
        (yyval.agg_func) = std::move((yyvsp[-1].rel_attr));
    }
#line 2407 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 79: /* agg_func: AVG LBRACE rel_attr RBRACE  */
#line 648 "./src/observer/sql/parser/yacc_sql.y"
                                 {
        (yyvsp[-1].rel_attr)->agg_func = AggFunc::A_AVG;
        (yyval.agg_func) = std::move((yyvsp[-1].rel_attr));
    }
#line 2416 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 80: /* order_by: %empty  */
#line 656 "./src/observer/sql/parser/yacc_sql.y"
    {
        (yyval.order_by_item_list) = nullptr;
    }
#line 2424 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 81: /* order_by: ORDER BY order_by_item_list  */
#line 659 "./src/observer/sql/parser/yacc_sql.y"
                                  {
        std::reverse((yyvsp[0].order_by_item_list)->begin(), (yyvsp[0].order_by_item_list)->end());
        (yyval.order_by_item_list) = (yyvsp[0].order_by_item_list);
    }
#line 2433 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 82: /* order_by_item_list: %empty  */
#line 667 "./src/observer/sql/parser/yacc_sql.y"
    {
        (yyval.order_by_item_list) = nullptr;
    }
#line 2441 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 83: /* order_by_item_list: order_by_item  */
#line 670 "./src/observer/sql/parser/yacc_sql.y"
                    {
        (yyval.order_by_item_list) = new std::vector<OrderByItem>;
        (yyval.order_by_item_list)->emplace_back(*(yyvsp[0].order_by_item));
        delete (yyvsp[0].order_by_item);
    }
#line 2451 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 84: /* order_by_item_list: order_by_item COMMA order_by_item_list  */
#line 675 "./src/observer/sql/parser/yacc_sql.y"
                                             {
        (yyval.order_by_item_list) = (yyvsp[0].order_by_item_list);
        (yyval.order_by_item_list)->emplace_back(*(yyvsp[-2].order_by_item));
        delete (yyvsp[-2].order_by_item);
    }
#line 2461 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 85: /* order_by_item: rel_attr order_type  */
#line 682 "./src/observer/sql/parser/yacc_sql.y"
                        {
      (yyval.order_by_item) = new OrderByItem;
      (yyval.order_by_item)->attr = *(yyvsp[-1].rel_attr);
      (yyval.order_by_item)->order_type = (yyvsp[0].order_type);
      free((yyvsp[-1].rel_attr));
    }
#line 2472 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 86: /* order_type: %empty  */
#line 692 "./src/observer/sql/parser/yacc_sql.y"
    {
        (yyval.order_type) = OrderByType::SORT_ASC;
    }
#line 2480 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 87: /* order_type: ASC  */
#line 695 "./src/observer/sql/parser/yacc_sql.y"
          {
        (yyval.order_type) = OrderByType::SORT_ASC;
    }
#line 2488 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 88: /* order_type: DESC  */
#line 698 "./src/observer/sql/parser/yacc_sql.y"
           {
        (yyval.order_type) = OrderByType::SORT_DESC;
    }
#line 2496 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 89: /* agg_func_list: %empty  */
#line 705 "./src/observer/sql/parser/yacc_sql.y"
    {
        (yyval.rel_attr_list) = nullptr;
    }
#line 2504 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 90: /* agg_func_list: COMMA agg_func agg_func_list  */
#line 708 "./src/observer/sql/parser/yacc_sql.y"
                                   {
        if ((yyvsp[0].rel_attr_list) != nullptr) {
            (yyval.rel_attr_list) = (yyvsp[0].rel_attr_list);
        } else {
            (yyval.rel_attr_list) = new std::vector<RelAttrSqlNode>;
        }
        (yyval.rel_attr_list)->emplace_back(*(yyvsp[-1].agg_func));
        delete (yyvsp[-1].agg_func);
    }
#line 2518 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 91: /* rel_attr: ID DOT '*'  */
#line 720 "./src/observer/sql/parser/yacc_sql.y"
               {
          (yyval.rel_attr) = new RelAttrSqlNode;
          (yyval.rel_attr)->relation_name  = (yyvsp[-2].string);
          (yyval.rel_attr)->attribute_name = "*";
          free((yyvsp[-2].string));
    }
#line 2529 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 92: /* rel_attr: ID  */
#line 726 "./src/observer/sql/parser/yacc_sql.y"
         {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->attribute_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 2539 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 93: /* rel_attr: ID DOT ID  */
#line 731 "./src/observer/sql/parser/yacc_sql.y"
                {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->relation_name  = (yyvsp[-2].string);
      (yyval.rel_attr)->attribute_name = (yyvsp[0].string);
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 2551 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 94: /* attr_list: %empty  */
#line 742 "./src/observer/sql/parser/yacc_sql.y"
    {
      (yyval.rel_attr_list) = nullptr;
    }
#line 2559 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 95: /* attr_list: COMMA rel_attr attr_list  */
#line 745 "./src/observer/sql/parser/yacc_sql.y"
                               {
      if ((yyvsp[0].rel_attr_list) != nullptr) {
        (yyval.rel_attr_list) = (yyvsp[0].rel_attr_list);
      } else {
        (yyval.rel_attr_list) = new std::vector<RelAttrSqlNode>;
      }

      (yyval.rel_attr_list)->emplace_back(*(yyvsp[-1].rel_attr));
      delete (yyvsp[-1].rel_attr);
    }
#line 2574 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 96: /* rel_list: %empty  */
#line 759 "./src/observer/sql/parser/yacc_sql.y"
    {
      (yyval.join_relation_list) = nullptr;
    }
#line 2582 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 97: /* rel_list: INNER JOIN ID ON condition_list rel_list  */
#line 762 "./src/observer/sql/parser/yacc_sql.y"
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
#line 2600 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 98: /* rel_list: COMMA ID rel_list  */
#line 775 "./src/observer/sql/parser/yacc_sql.y"
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
#line 2616 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 99: /* where: %empty  */
#line 789 "./src/observer/sql/parser/yacc_sql.y"
    {
      (yyval.condition_list) = nullptr;
    }
#line 2624 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 100: /* where: WHERE condition_list  */
#line 792 "./src/observer/sql/parser/yacc_sql.y"
                           {
      (yyval.condition_list) = (yyvsp[0].condition_list);
    }
#line 2632 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 101: /* condition_list: %empty  */
#line 798 "./src/observer/sql/parser/yacc_sql.y"
    {
      (yyval.condition_list) = nullptr;
    }
#line 2640 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 102: /* condition_list: condition  */
#line 801 "./src/observer/sql/parser/yacc_sql.y"
                {
      (yyval.condition_list) = new std::vector<ConditionSqlNode>;
      (yyval.condition_list)->emplace_back(*(yyvsp[0].condition));
      delete (yyvsp[0].condition);
    }
#line 2650 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 103: /* condition_list: condition AND condition_list  */
#line 806 "./src/observer/sql/parser/yacc_sql.y"
                                   {
      (yyval.condition_list) = (yyvsp[0].condition_list);
      (yyval.condition_list)->emplace_back(*(yyvsp[-2].condition));
      delete (yyvsp[-2].condition);
    }
#line 2660 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 104: /* condition: value in LBRACE value value_list RBRACE  */
#line 814 "./src/observer/sql/parser/yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_attr = 0;
      (yyval.condition)->left_value = *(yyvsp[-5].value);
      (yyval.condition)->right_is_attr = 0;
      if ((yyvsp[-1].value_list) != nullptr) {
        (yyval.condition)->values.swap(*(yyvsp[-1].value_list));
      }
      (yyval.condition)->values.emplace_back(*(yyvsp[-2].value));
      (yyval.condition)->comp = (yyvsp[-4].comp);

      delete (yyvsp[-5].value);
      delete (yyvsp[-2].value);
    }
#line 2679 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 105: /* condition: rel_attr in LBRACE value value_list RBRACE  */
#line 829 "./src/observer/sql/parser/yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_attr = 1;
      (yyval.condition)->left_attr = *(yyvsp[-5].rel_attr);
      (yyval.condition)->right_is_attr = 0;
      if ((yyvsp[-1].value_list) != nullptr) {
        (yyval.condition)->values.swap(*(yyvsp[-1].value_list));
      }
      (yyval.condition)->values.emplace_back(*(yyvsp[-2].value));
      (yyval.condition)->comp = (yyvsp[-4].comp);

      delete (yyvsp[-5].rel_attr);
      delete (yyvsp[-2].value);
    }
#line 2698 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 106: /* condition: rel_attr sub_comp_op LBRACE select_stmt RBRACE  */
#line 844 "./src/observer/sql/parser/yacc_sql.y"
          {
            (yyval.condition) = new ConditionSqlNode;
            (yyval.condition)->left_is_attr = 1;
            (yyval.condition)->left_attr = *(yyvsp[-4].rel_attr);
            (yyval.condition)->right_is_attr = 0;
            (yyval.condition)->sub_selection = (yyvsp[-1].sql_node);
            (yyval.condition)->comp = (yyvsp[-3].comp);

            delete (yyvsp[-4].rel_attr);
            delete (yyvsp[-1].sql_node);
          }
#line 2714 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 107: /* condition: value sub_comp_op LBRACE select_stmt RBRACE  */
#line 856 "./src/observer/sql/parser/yacc_sql.y"
              {
                (yyval.condition) = new ConditionSqlNode;
                (yyval.condition)->left_is_attr = 0;
                (yyval.condition)->left_value = *(yyvsp[-4].value);
                (yyval.condition)->right_is_attr = 0;
                (yyval.condition)->sub_selection = (yyvsp[-1].sql_node);
                (yyval.condition)->comp = (yyvsp[-3].comp);

                delete (yyvsp[-4].value);
                delete (yyvsp[-1].sql_node);
              }
#line 2730 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 108: /* condition: exists LBRACE select_stmt RBRACE  */
#line 868 "./src/observer/sql/parser/yacc_sql.y"
        {
          (yyval.condition) = new ConditionSqlNode;
          (yyval.condition)->left_is_attr = 0;
          (yyval.condition)->right_is_attr = 0;
          (yyval.condition)->sub_selection = (yyvsp[-1].sql_node);
          (yyval.condition)->comp = (yyvsp[-3].comp);

          delete (yyvsp[-1].sql_node);
        }
#line 2744 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 109: /* condition: rel_attr comp_op value  */
#line 878 "./src/observer/sql/parser/yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_attr = 1;
      (yyval.condition)->left_attr = *(yyvsp[-2].rel_attr);
      (yyval.condition)->right_is_attr = 0;
      (yyval.condition)->right_value = *(yyvsp[0].value);
      (yyval.condition)->comp = (yyvsp[-1].comp);

      delete (yyvsp[-2].rel_attr);
      delete (yyvsp[0].value);
    }
#line 2760 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 110: /* condition: value comp_op value  */
#line 890 "./src/observer/sql/parser/yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_attr = 0;
      (yyval.condition)->left_value = *(yyvsp[-2].value);
      (yyval.condition)->right_is_attr = 0;
      (yyval.condition)->right_value = *(yyvsp[0].value);
      (yyval.condition)->comp = (yyvsp[-1].comp);

      delete (yyvsp[-2].value);
      delete (yyvsp[0].value);
    }
#line 2776 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 111: /* condition: rel_attr comp_op rel_attr  */
#line 902 "./src/observer/sql/parser/yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_attr = 1;
      (yyval.condition)->left_attr = *(yyvsp[-2].rel_attr);
      (yyval.condition)->right_is_attr = 1;
      (yyval.condition)->right_attr = *(yyvsp[0].rel_attr);
      (yyval.condition)->comp = (yyvsp[-1].comp);

      delete (yyvsp[-2].rel_attr);
      delete (yyvsp[0].rel_attr);
    }
#line 2792 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 112: /* condition: value comp_op rel_attr  */
#line 914 "./src/observer/sql/parser/yacc_sql.y"
    {
      (yyval.condition) = new ConditionSqlNode;
      (yyval.condition)->left_is_attr = 0;
      (yyval.condition)->left_value = *(yyvsp[-2].value);
      (yyval.condition)->right_is_attr = 1;
      (yyval.condition)->right_attr = *(yyvsp[0].rel_attr);
      (yyval.condition)->comp = (yyvsp[-1].comp);

      delete (yyvsp[-2].value);
      delete (yyvsp[0].rel_attr);
    }
#line 2808 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 113: /* sub_comp_op: EQ  */
#line 929 "./src/observer/sql/parser/yacc_sql.y"
         { (yyval.comp) = EQUAL_TO; }
#line 2814 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 114: /* sub_comp_op: LT  */
#line 930 "./src/observer/sql/parser/yacc_sql.y"
         { (yyval.comp) = LESS_THAN; }
#line 2820 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 115: /* sub_comp_op: GT  */
#line 931 "./src/observer/sql/parser/yacc_sql.y"
         { (yyval.comp) = GREAT_THAN; }
#line 2826 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 116: /* sub_comp_op: LE  */
#line 932 "./src/observer/sql/parser/yacc_sql.y"
         { (yyval.comp) = LESS_EQUAL; }
#line 2832 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 117: /* sub_comp_op: GE  */
#line 933 "./src/observer/sql/parser/yacc_sql.y"
         { (yyval.comp) = GREAT_EQUAL; }
#line 2838 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 118: /* sub_comp_op: NE  */
#line 934 "./src/observer/sql/parser/yacc_sql.y"
         { (yyval.comp) = NOT_EQUAL; }
#line 2844 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 119: /* sub_comp_op: IN_T  */
#line 935 "./src/observer/sql/parser/yacc_sql.y"
           { (yyval.comp) = IN;}
#line 2850 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 120: /* sub_comp_op: NOT IN_T  */
#line 936 "./src/observer/sql/parser/yacc_sql.y"
               {(yyval.comp) = NOT_IN;}
#line 2856 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 121: /* comp_op: EQ  */
#line 940 "./src/observer/sql/parser/yacc_sql.y"
         { (yyval.comp) = EQUAL_TO; }
#line 2862 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 122: /* comp_op: LT  */
#line 941 "./src/observer/sql/parser/yacc_sql.y"
         { (yyval.comp) = LESS_THAN; }
#line 2868 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 123: /* comp_op: GT  */
#line 942 "./src/observer/sql/parser/yacc_sql.y"
         { (yyval.comp) = GREAT_THAN; }
#line 2874 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 124: /* comp_op: LE  */
#line 943 "./src/observer/sql/parser/yacc_sql.y"
         { (yyval.comp) = LESS_EQUAL; }
#line 2880 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 125: /* comp_op: GE  */
#line 944 "./src/observer/sql/parser/yacc_sql.y"
         { (yyval.comp) = GREAT_EQUAL; }
#line 2886 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 126: /* comp_op: NE  */
#line 945 "./src/observer/sql/parser/yacc_sql.y"
         { (yyval.comp) = NOT_EQUAL; }
#line 2892 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 127: /* comp_op: LIKE_C  */
#line 946 "./src/observer/sql/parser/yacc_sql.y"
            {(yyval.comp) = LIKE;}
#line 2898 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 128: /* comp_op: NOT LIKE_C  */
#line 947 "./src/observer/sql/parser/yacc_sql.y"
                {(yyval.comp) = NOT_LIKE;}
#line 2904 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 129: /* comp_op: IS  */
#line 948 "./src/observer/sql/parser/yacc_sql.y"
         {(yyval.comp) = IS_NULL;}
#line 2910 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 130: /* comp_op: IS NOT  */
#line 949 "./src/observer/sql/parser/yacc_sql.y"
             {(yyval.comp) = NOT_NULL;}
#line 2916 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 131: /* in: IN_T  */
#line 952 "./src/observer/sql/parser/yacc_sql.y"
          {(yyval.comp) = IN;}
#line 2922 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 132: /* in: NOT IN_T  */
#line 953 "./src/observer/sql/parser/yacc_sql.y"
                {(yyval.comp) = NOT_IN;}
#line 2928 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 133: /* exists: EXISTS_T  */
#line 956 "./src/observer/sql/parser/yacc_sql.y"
               {(yyval.comp) = EXISTS;}
#line 2934 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 134: /* exists: NOT EXISTS_T  */
#line 957 "./src/observer/sql/parser/yacc_sql.y"
                   {(yyval.comp) = NOT_EXISTS;}
#line 2940 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 135: /* load_data_stmt: LOAD DATA INFILE SSS INTO TABLE ID  */
#line 962 "./src/observer/sql/parser/yacc_sql.y"
    {
      char *tmp_file_name = common::substr((yyvsp[-3].string), 1, strlen((yyvsp[-3].string)) - 2);
      
      (yyval.sql_node) = new ParsedSqlNode(SCF_LOAD_DATA);
      (yyval.sql_node)->load_data.relation_name = (yyvsp[0].string);
      (yyval.sql_node)->load_data.file_name = tmp_file_name;
      free((yyvsp[0].string));
      free(tmp_file_name);
    }
#line 2954 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 136: /* explain_stmt: EXPLAIN command_wrapper  */
#line 975 "./src/observer/sql/parser/yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXPLAIN);
      (yyval.sql_node)->explain.sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[0].sql_node));
    }
#line 2963 "./src/observer/sql/parser/yacc_sql.cpp"
    break;

  case 137: /* set_variable_stmt: SET ID EQ value  */
#line 983 "./src/observer/sql/parser/yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SET_VARIABLE);
      (yyval.sql_node)->set_variable.name  = (yyvsp[-2].string);
      (yyval.sql_node)->set_variable.value = *(yyvsp[0].value);
      free((yyvsp[-2].string));
      delete (yyvsp[0].value);
    }
#line 2975 "./src/observer/sql/parser/yacc_sql.cpp"
    break;


#line 2979 "./src/observer/sql/parser/yacc_sql.cpp"

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

#line 995 "./src/observer/sql/parser/yacc_sql.y"

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
