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
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "task6_parser.y"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

extern int yylex();
extern FILE *yyin;

int line_num = 1;
int temp_count = 0;
int label_count = 1;

typedef struct {
    char op[20], arg1[50], arg2[50], result[50];
    int is_dead;
} Quadruple;

Quadruple tac[1000];
int tac_count = 0;

typedef struct {
    char var[50];
    int value;
    int is_const;
    int is_used;
} VarInfo;

VarInfo var_table[200];
int var_count = 0;

typedef struct {
    int false_pos;
    int end_pos;
    char false_label[20];
    char end_label[20];
} PatchInfo;

PatchInfo stack[100];
int sp = -1;

void yyerror(const char *s);
char* new_temp();
char* new_label();
void gen(char *op, char *arg1, char *arg2, char *result);
void print_tac(const char *title);
void print_quadruples();

// Optimization functions
void constant_propagation();
void constant_folding();
void enhanced_constant_folding();
void dead_code_elimination();
void eliminate_unreachable_code();
int find_var(const char *name);
void update_var(const char *name, int value, int is_const);
int is_constant(const char *str);
int evaluate_expr(const char *op, int val1, int val2);
void mark_used_vars();

#line 132 "task6_parser.c"

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

#include "task6_parser.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_NUM = 3,                        /* NUM  */
  YYSYMBOL_FLOAT_NUM = 4,                  /* FLOAT_NUM  */
  YYSYMBOL_ID = 5,                         /* ID  */
  YYSYMBOL_INT = 6,                        /* INT  */
  YYSYMBOL_FLOAT = 7,                      /* FLOAT  */
  YYSYMBOL_CHAR = 8,                       /* CHAR  */
  YYSYMBOL_DOUBLE = 9,                     /* DOUBLE  */
  YYSYMBOL_VOID = 10,                      /* VOID  */
  YYSYMBOL_IF = 11,                        /* IF  */
  YYSYMBOL_ELSE = 12,                      /* ELSE  */
  YYSYMBOL_WHILE = 13,                     /* WHILE  */
  YYSYMBOL_FOR = 14,                       /* FOR  */
  YYSYMBOL_RETURN = 15,                    /* RETURN  */
  YYSYMBOL_PLUS = 16,                      /* PLUS  */
  YYSYMBOL_MINUS = 17,                     /* MINUS  */
  YYSYMBOL_MUL = 18,                       /* MUL  */
  YYSYMBOL_DIV = 19,                       /* DIV  */
  YYSYMBOL_ASSIGN = 20,                    /* ASSIGN  */
  YYSYMBOL_LT = 21,                        /* LT  */
  YYSYMBOL_GT = 22,                        /* GT  */
  YYSYMBOL_LE = 23,                        /* LE  */
  YYSYMBOL_GE = 24,                        /* GE  */
  YYSYMBOL_EQ = 25,                        /* EQ  */
  YYSYMBOL_NE = 26,                        /* NE  */
  YYSYMBOL_LBRACE = 27,                    /* LBRACE  */
  YYSYMBOL_RBRACE = 28,                    /* RBRACE  */
  YYSYMBOL_LPAREN = 29,                    /* LPAREN  */
  YYSYMBOL_RPAREN = 30,                    /* RPAREN  */
  YYSYMBOL_LBRACKET = 31,                  /* LBRACKET  */
  YYSYMBOL_RBRACKET = 32,                  /* RBRACKET  */
  YYSYMBOL_SEMI = 33,                      /* SEMI  */
  YYSYMBOL_COMMA = 34,                     /* COMMA  */
  YYSYMBOL_YYACCEPT = 35,                  /* $accept  */
  YYSYMBOL_program = 36,                   /* program  */
  YYSYMBOL_function_list = 37,             /* function_list  */
  YYSYMBOL_function = 38,                  /* function  */
  YYSYMBOL_param_list = 39,                /* param_list  */
  YYSYMBOL_type_spec = 40,                 /* type_spec  */
  YYSYMBOL_stmt_list = 41,                 /* stmt_list  */
  YYSYMBOL_stmt = 42,                      /* stmt  */
  YYSYMBOL_declaration = 43,               /* declaration  */
  YYSYMBOL_assignment = 44,                /* assignment  */
  YYSYMBOL_if_stmt = 45,                   /* if_stmt  */
  YYSYMBOL_46_1 = 46,                      /* $@1  */
  YYSYMBOL_47_2 = 47,                      /* $@2  */
  YYSYMBOL_else_part = 48,                 /* else_part  */
  YYSYMBOL_while_stmt = 49,                /* while_stmt  */
  YYSYMBOL_50_3 = 50,                      /* $@3  */
  YYSYMBOL_51_4 = 51,                      /* $@4  */
  YYSYMBOL_return_stmt = 52,               /* return_stmt  */
  YYSYMBOL_condition = 53,                 /* condition  */
  YYSYMBOL_relop = 54,                     /* relop  */
  YYSYMBOL_expr = 55,                      /* expr  */
  YYSYMBOL_term = 56,                      /* term  */
  YYSYMBOL_factor = 57                     /* factor  */
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
typedef yytype_int8 yy_state_t;

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

#if !defined yyoverflow

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
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

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
#define YYFINAL  10
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   157

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  35
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  23
/* YYNRULES -- Number of rules.  */
#define YYNRULES  54
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  113

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   289


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
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    85,    85,    86,    86,    87,    87,    88,    88,    89,
      89,    89,    89,    89,    90,    90,    91,    91,    91,    91,
      91,    94,    95,    96,    97,   101,   102,   109,   115,   109,
     127,   127,   130,   135,   130,   146,   146,   148,   151,   151,
     152,   152,   153,   153,   156,   157,   158,   162,   163,   164,
     168,   169,   170,   171,   172
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "NUM", "FLOAT_NUM",
  "ID", "INT", "FLOAT", "CHAR", "DOUBLE", "VOID", "IF", "ELSE", "WHILE",
  "FOR", "RETURN", "PLUS", "MINUS", "MUL", "DIV", "ASSIGN", "LT", "GT",
  "LE", "GE", "EQ", "NE", "LBRACE", "RBRACE", "LPAREN", "RPAREN",
  "LBRACKET", "RBRACKET", "SEMI", "COMMA", "$accept", "program",
  "function_list", "function", "param_list", "type_spec", "stmt_list",
  "stmt", "declaration", "assignment", "if_stmt", "$@1", "$@2",
  "else_part", "while_stmt", "$@3", "$@4", "return_stmt", "condition",
  "relop", "expr", "term", "factor", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-27)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     122,   -27,   -27,   -27,   -27,   -27,    29,   122,   -27,    34,
     -27,   -27,    33,    14,    43,     7,    53,   -27,    50,   122,
     -27,    46,   -27,    92,   -14,    70,   -27,    -1,   -27,    96,
     -27,   -27,   -27,   -27,   -27,   -27,    58,   -27,     4,     4,
       4,    82,   -27,   -27,    72,     4,   -27,     9,    -8,   -27,
     -15,   -27,   100,    -2,   111,   123,     4,     4,    19,     4,
       4,   -27,     4,     4,     4,   112,   -27,   -27,   114,   -27,
     -27,   -27,   -27,   -27,   -27,   -27,     4,   113,   106,   -27,
      -8,    -8,   -27,   -27,   102,    94,     4,   109,    31,   -27,
     -27,   -27,    12,   104,   -27,   115,   147,   -27,   -27,    74,
     -27,   119,   -27,    85,   120,   140,   -27,   -27,   127,   -27,
     -27,    99,   -27
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     9,    10,    11,    12,    13,     0,     2,     4,     0,
       1,     3,     0,     0,     0,     0,     0,    15,     0,     0,
       8,     0,    15,     0,     0,     0,    32,     0,     5,     0,
      14,    16,    17,    18,    19,    20,     0,     7,     0,     0,
       0,     0,    52,    53,    51,     0,    36,     0,    46,    49,
       0,     6,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    35,     0,     0,     0,     0,    21,    25,     0,    27,
      38,    39,    40,    41,    42,    43,     0,     0,     0,    50,
      44,    45,    47,    48,     0,     0,     0,     0,    37,    33,
      54,    24,     0,     0,    15,     0,     0,    22,    26,     0,
      15,     0,    28,     0,     0,    31,    34,    23,     0,    29,
      15,     0,    30
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -27,   -27,   -27,   148,   -27,    27,   -22,   -27,   -27,   -27,
     -27,   -27,   -27,   -27,   -27,   -27,   -27,   -27,   101,   -27,
     -26,    16,    62
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     6,     7,     8,    15,    29,    21,    30,    31,    32,
      33,    87,   105,   109,    34,    41,    95,    35,    54,    76,
      55,    48,    49
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      36,    47,    42,    43,    44,    64,    38,    42,    43,    44,
      62,    63,    52,    53,    59,    60,    65,    39,    66,    58,
       1,     2,     3,     4,     5,    59,    60,     9,    45,    10,
      68,    78,    46,    45,     9,    59,    60,    18,    84,    12,
      16,    19,    61,    96,    14,    97,    23,    59,    60,    79,
      88,    24,     1,     2,     3,     4,     5,    25,    20,    26,
      93,    27,    13,    24,     1,     2,     3,     4,     5,    25,
      17,    26,    99,    27,    28,    80,    81,    22,   103,    24,
       1,     2,     3,     4,     5,    25,    51,    26,   111,    27,
      24,     1,     2,     3,     4,     5,    25,    37,    26,    40,
      27,    50,   102,    57,    24,     1,     2,     3,     4,     5,
      25,    56,    26,   106,    27,    85,    59,    60,    59,    60,
      59,    60,    59,    60,    82,    83,    92,   112,     1,     2,
       3,     4,     5,    67,    86,    91,    94,    98,    90,    59,
      60,    69,   100,    89,    70,    71,    72,    73,    74,    75,
     101,   104,   108,   107,   110,    11,     0,    77
};

static const yytype_int8 yycheck[] =
{
      22,    27,     3,     4,     5,    20,    20,     3,     4,     5,
      18,    19,    38,    39,    16,    17,    31,    31,    33,    45,
       6,     7,     8,     9,    10,    16,    17,     0,    29,     0,
      32,    57,    33,    29,     7,    16,    17,    30,    64,     5,
      13,    34,    33,    31,    30,    33,    19,    16,    17,    30,
      76,     5,     6,     7,     8,     9,    10,    11,     5,    13,
      86,    15,    29,     5,     6,     7,     8,     9,    10,    11,
      27,    13,    94,    15,    28,    59,    60,    27,   100,     5,
       6,     7,     8,     9,    10,    11,    28,    13,   110,    15,
       5,     6,     7,     8,     9,    10,    11,     5,    13,    29,
      15,     5,    28,    31,     5,     6,     7,     8,     9,    10,
      11,    29,    13,    28,    15,     3,    16,    17,    16,    17,
      16,    17,    16,    17,    62,    63,    32,    28,     6,     7,
       8,     9,    10,    33,    20,    33,    27,    33,    32,    16,
      17,    30,    27,    30,    21,    22,    23,    24,    25,    26,
       3,    32,    12,    33,    27,     7,    -1,    56
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     6,     7,     8,     9,    10,    36,    37,    38,    40,
       0,    38,     5,    29,    30,    39,    40,    27,    30,    34,
       5,    41,    27,    40,     5,    11,    13,    15,    28,    40,
      42,    43,    44,    45,    49,    52,    41,     5,    20,    31,
      29,    50,     3,     4,     5,    29,    33,    55,    56,    57,
       5,    28,    55,    55,    53,    55,    29,    31,    55,    16,
      17,    33,    18,    19,    20,    31,    33,    33,    32,    30,
      21,    22,    23,    24,    25,    26,    54,    53,    55,    30,
      56,    56,    57,    57,    55,     3,    20,    46,    55,    30,
      32,    33,    32,    55,    27,    51,    31,    33,    33,    41,
      27,     3,    28,    41,    32,    47,    28,    33,    12,    48,
      27,    41,    28
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    35,    36,    37,    37,    38,    38,    39,    39,    40,
      40,    40,    40,    40,    41,    41,    42,    42,    42,    42,
      42,    43,    43,    43,    43,    44,    44,    46,    47,    45,
      48,    48,    50,    51,    49,    52,    52,    53,    54,    54,
      54,    54,    54,    54,    55,    55,    55,    56,    56,    56,
      57,    57,    57,    57,    57
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     1,     7,     8,     4,     2,     1,
       1,     1,     1,     1,     2,     0,     1,     1,     1,     1,
       1,     3,     6,     9,     5,     4,     7,     0,     0,    10,
       4,     0,     0,     0,     9,     3,     2,     3,     1,     1,
       1,     1,     1,     1,     3,     3,     1,     3,     3,     1,
       3,     1,     1,     1,     4
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
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


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




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
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
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
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
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
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






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
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

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

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

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
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
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

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
      yychar = yylex ();
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


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 24: /* declaration: type_spec ID ASSIGN expr SEMI  */
#line 97 "task6_parser.y"
                                    { gen("=", (yyvsp[-1].str), "", (yyvsp[-3].str)); }
#line 1254 "task6_parser.c"
    break;

  case 25: /* assignment: ID ASSIGN expr SEMI  */
#line 101 "task6_parser.y"
                        { gen("=", (yyvsp[-1].str), "", (yyvsp[-3].str)); }
#line 1260 "task6_parser.c"
    break;

  case 26: /* assignment: ID LBRACKET expr RBRACKET ASSIGN expr SEMI  */
#line 102 "task6_parser.y"
                                                 {
        char tmp[100]; sprintf(tmp, "%s[%s]", (yyvsp[-6].str), (yyvsp[-4].str));
        gen("=", (yyvsp[-1].str), "", tmp);
    }
#line 1269 "task6_parser.c"
    break;

  case 27: /* $@1: %empty  */
#line 109 "task6_parser.y"
                               {
        char *Lfalse = new_label();
        gen("ifFalse", (yyvsp[-1].str), "", Lfalse);
        sp++;
        stack[sp].false_pos = tac_count - 1;
        strcpy(stack[sp].false_label, Lfalse);
    }
#line 1281 "task6_parser.c"
    break;

  case 28: /* $@2: %empty  */
#line 115 "task6_parser.y"
                              {
        char *Lend = new_label();
        gen("goto", "", "", Lend);
        stack[sp].end_pos = tac_count - 1;
        strcpy(stack[sp].end_label, Lend);
        gen("Label", "", "", stack[sp].false_label);
    }
#line 1293 "task6_parser.c"
    break;

  case 29: /* if_stmt: IF LPAREN condition RPAREN $@1 LBRACE stmt_list RBRACE $@2 else_part  */
#line 121 "task6_parser.y"
                {
        gen("Label", "", "", stack[sp].end_label);
        sp--;
    }
#line 1302 "task6_parser.c"
    break;

  case 32: /* $@3: %empty  */
#line 130 "task6_parser.y"
          {
        char *Lstart = new_label();
        gen("Label", "", "", Lstart);
        sp++;
        strcpy(stack[sp].false_label, Lstart);
    }
#line 1313 "task6_parser.c"
    break;

  case 33: /* $@4: %empty  */
#line 135 "task6_parser.y"
                              {
        char *Lend = new_label();
        gen("ifFalse", (yyvsp[-1].str), "", Lend);
        strcpy(stack[sp].end_label, Lend);
    }
#line 1323 "task6_parser.c"
    break;

  case 34: /* while_stmt: WHILE $@3 LPAREN condition RPAREN $@4 LBRACE stmt_list RBRACE  */
#line 139 "task6_parser.y"
                              {
        gen("goto", "", "", stack[sp].false_label);
        gen("Label", "", "", stack[sp].end_label);
        sp--;
    }
#line 1333 "task6_parser.c"
    break;

  case 35: /* return_stmt: RETURN expr SEMI  */
#line 146 "task6_parser.y"
                              { gen("return", (yyvsp[-1].str), "", ""); }
#line 1339 "task6_parser.c"
    break;

  case 36: /* return_stmt: RETURN SEMI  */
#line 146 "task6_parser.y"
                                                                           { gen("return", "", "", ""); }
#line 1345 "task6_parser.c"
    break;

  case 37: /* condition: expr relop expr  */
#line 148 "task6_parser.y"
                           { char *tmp = new_temp(); gen((yyvsp[-1].str), (yyvsp[-2].str), (yyvsp[0].str), tmp); (yyval.str) = tmp; }
#line 1351 "task6_parser.c"
    break;

  case 38: /* relop: LT  */
#line 151 "task6_parser.y"
       { (yyval.str) = strdup("<"); }
#line 1357 "task6_parser.c"
    break;

  case 39: /* relop: GT  */
#line 151 "task6_parser.y"
                                  { (yyval.str) = strdup(">"); }
#line 1363 "task6_parser.c"
    break;

  case 40: /* relop: LE  */
#line 152 "task6_parser.y"
         { (yyval.str) = strdup("<="); }
#line 1369 "task6_parser.c"
    break;

  case 41: /* relop: GE  */
#line 152 "task6_parser.y"
                                     { (yyval.str) = strdup(">="); }
#line 1375 "task6_parser.c"
    break;

  case 42: /* relop: EQ  */
#line 153 "task6_parser.y"
         { (yyval.str) = strdup("=="); }
#line 1381 "task6_parser.c"
    break;

  case 43: /* relop: NE  */
#line 153 "task6_parser.y"
                                     { (yyval.str) = strdup("!="); }
#line 1387 "task6_parser.c"
    break;

  case 44: /* expr: expr PLUS term  */
#line 156 "task6_parser.y"
                   { char *tmp = new_temp(); gen("+", (yyvsp[-2].str), (yyvsp[0].str), tmp); (yyval.str) = tmp; }
#line 1393 "task6_parser.c"
    break;

  case 45: /* expr: expr MINUS term  */
#line 157 "task6_parser.y"
                      { char *tmp = new_temp(); gen("-", (yyvsp[-2].str), (yyvsp[0].str), tmp); (yyval.str) = tmp; }
#line 1399 "task6_parser.c"
    break;

  case 46: /* expr: term  */
#line 158 "task6_parser.y"
           { (yyval.str) = (yyvsp[0].str); }
#line 1405 "task6_parser.c"
    break;

  case 47: /* term: term MUL factor  */
#line 162 "task6_parser.y"
                    { char *tmp = new_temp(); gen("*", (yyvsp[-2].str), (yyvsp[0].str), tmp); (yyval.str) = tmp; }
#line 1411 "task6_parser.c"
    break;

  case 48: /* term: term DIV factor  */
#line 163 "task6_parser.y"
                      { char *tmp = new_temp(); gen("/", (yyvsp[-2].str), (yyvsp[0].str), tmp); (yyval.str) = tmp; }
#line 1417 "task6_parser.c"
    break;

  case 49: /* term: factor  */
#line 164 "task6_parser.y"
             { (yyval.str) = (yyvsp[0].str); }
#line 1423 "task6_parser.c"
    break;

  case 50: /* factor: LPAREN expr RPAREN  */
#line 168 "task6_parser.y"
                       { (yyval.str) = (yyvsp[-1].str); }
#line 1429 "task6_parser.c"
    break;

  case 51: /* factor: ID  */
#line 169 "task6_parser.y"
         { (yyval.str) = (yyvsp[0].str); }
#line 1435 "task6_parser.c"
    break;

  case 52: /* factor: NUM  */
#line 170 "task6_parser.y"
          { char *buf = (char*)malloc(16); sprintf(buf, "%d", (yyvsp[0].num)); (yyval.str) = buf; }
#line 1441 "task6_parser.c"
    break;

  case 53: /* factor: FLOAT_NUM  */
#line 171 "task6_parser.y"
                { char *buf = (char*)malloc(16); sprintf(buf, "%.2f", (yyvsp[0].fnum)); (yyval.str) = buf; }
#line 1447 "task6_parser.c"
    break;

  case 54: /* factor: ID LBRACKET expr RBRACKET  */
#line 172 "task6_parser.y"
                                { char *buf = (char*)malloc(64); sprintf(buf, "%s[%s]", (yyvsp[-3].str), (yyvsp[-1].str)); (yyval.str) = buf; }
#line 1453 "task6_parser.c"
    break;


#line 1457 "task6_parser.c"

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
      yyerror (YY_("syntax error"));
    }

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
                      yytoken, &yylval);
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


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


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
  yyerror (YY_("memory exhausted"));
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
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 175 "task6_parser.y"


void yyerror(const char *s) { fprintf(stderr, "Error at line %d: %s\n", line_num, s); }

char* new_temp() { char *t = (char*)malloc(10); sprintf(t, "t%d", temp_count++); return t; }
char* new_label() { char *l = (char*)malloc(10); sprintf(l, "L%d", label_count++); return l; }

void gen(char *op, char *arg1, char *arg2, char *result) {
    strcpy(tac[tac_count].op, op);
    strcpy(tac[tac_count].arg1, arg1 ? arg1 : "");
    strcpy(tac[tac_count].arg2, arg2 ? arg2 : "");
    strcpy(tac[tac_count].result, result ? result : "");
    tac[tac_count].is_dead = 0;
    tac_count++;
}

int find_var(const char *name) {
    for (int i = 0; i < var_count; i++) {
        if (strcmp(var_table[i].var, name) == 0) return i;
    }
    return -1;
}

void update_var(const char *name, int value, int is_const) {
    int idx = find_var(name);
    if (idx == -1) {
        strcpy(var_table[var_count].var, name);
        var_table[var_count].value = value;
        var_table[var_count].is_const = is_const;
        var_table[var_count].is_used = 0;
        var_count++;
    } else {
        var_table[idx].value = value;
        var_table[idx].is_const = is_const;
    }
}

int is_constant(const char *str) {
    if (!str || strlen(str) == 0) return 0;
    int i = 0;
    if (str[0] == '-') i = 1;
    for (; str[i]; i++) {
        if (!isdigit(str[i])) return 0;
    }
    return 1;
}

int evaluate_expr(const char *op, int val1, int val2) {
    if (strcmp(op, "+") == 0) return val1 + val2;
    if (strcmp(op, "-") == 0) return val1 - val2;
    if (strcmp(op, "*") == 0) return val1 * val2;
    if (strcmp(op, "/") == 0) return val2 != 0 ? val1 / val2 : 0;
    if (strcmp(op, ">=") == 0) return val1 >= val2;
    if (strcmp(op, "<=") == 0) return val1 <= val2;
    if (strcmp(op, ">") == 0) return val1 > val2;
    if (strcmp(op, "<") == 0) return val1 < val2;
    if (strcmp(op, "==") == 0) return val1 == val2;
    if (strcmp(op, "!=") == 0) return val1 != val2;
    return 0;
}

void constant_propagation() {
    for (int i = 0; i < tac_count; i++) {
        if (strcmp(tac[i].op, "Label") == 0 || strcmp(tac[i].op, "goto") == 0 || strcmp(tac[i].op, "ifFalse") == 0) continue;

        if (strcmp(tac[i].op, "=") == 0) {
            if (is_constant(tac[i].arg1)) {
                update_var(tac[i].result, atoi(tac[i].arg1), 1);
            } else {
                int idx = find_var(tac[i].arg1);
                if (idx != -1 && var_table[idx].is_const) {
                    sprintf(tac[i].arg1, "%d", var_table[idx].value);
                    update_var(tac[i].result, var_table[idx].value, 1);
                } else {
                    update_var(tac[i].result, 0, 0);
                }
            }
        } else if (strlen(tac[i].arg2) > 0) {
            int idx1 = find_var(tac[i].arg1);
            if (idx1 != -1 && var_table[idx1].is_const) {
                sprintf(tac[i].arg1, "%d", var_table[idx1].value);
            }
            int idx2 = find_var(tac[i].arg2);
            if (idx2 != -1 && var_table[idx2].is_const) {
                sprintf(tac[i].arg2, "%d", var_table[idx2].value);
            }
        }
    }
}

void constant_folding() {
    for (int i = 0; i < tac_count; i++) {
        if (strlen(tac[i].arg2) > 0 && strcmp(tac[i].op, "Label") != 0 && strcmp(tac[i].op, "goto") != 0 && strcmp(tac[i].op, "ifFalse") != 0) {
            if (is_constant(tac[i].arg1) && is_constant(tac[i].arg2)) {
                int val1 = atoi(tac[i].arg1);
                int val2 = atoi(tac[i].arg2);
                int result = evaluate_expr(tac[i].op, val1, val2);
                strcpy(tac[i].op, "=");
                sprintf(tac[i].arg1, "%d", result);
                tac[i].arg2[0] = '\0';
                update_var(tac[i].result, result, 1);
            }
        }
    }
}

void enhanced_constant_folding() {
    int changed = 1;
    int iterations = 0;
    while (changed && iterations < 5) {
        changed = 0;
        iterations++;
        
        // First propagate all known constants
        for (int i = 0; i < tac_count; i++) {
            if (strcmp(tac[i].op, "=") == 0 && is_constant(tac[i].arg1)) {
                update_var(tac[i].result, atoi(tac[i].arg1), 1);
            }
        }
        
        // Then try to fold expressions
        for (int i = 0; i < tac_count; i++) {
            if (strlen(tac[i].arg2) > 0) {
                int idx1 = find_var(tac[i].arg1);
                if (idx1 != -1 && var_table[idx1].is_const && !is_constant(tac[i].arg1)) {
                    sprintf(tac[i].arg1, "%d", var_table[idx1].value);
                    changed = 1;
                }
                int idx2 = find_var(tac[i].arg2);
                if (idx2 != -1 && var_table[idx2].is_const && !is_constant(tac[i].arg2)) {
                    sprintf(tac[i].arg2, "%d", var_table[idx2].value);
                    changed = 1;
                }
                if (is_constant(tac[i].arg1) && is_constant(tac[i].arg2)) {
                    int result = evaluate_expr(tac[i].op, atoi(tac[i].arg1), atoi(tac[i].arg2));
                    strcpy(tac[i].op, "=");
                    sprintf(tac[i].arg1, "%d", result);
                    tac[i].arg2[0] = '\0';
                    update_var(tac[i].result, result, 1);
                    changed = 1;
                }
            }
        }
    }
}

void eliminate_unreachable_code() {
    for (int i = 0; i < tac_count; i++) {
        // Look for ifFalse with constant condition
        if (strcmp(tac[i].op, "ifFalse") == 0) {
            // Check if condition is a constant
            char *cond_var = tac[i].arg1;
            int is_const = 0;
            int cond_value = 0;
            
            // Check if it's a number
            if (is_constant(cond_var)) {
                is_const = 1;
                cond_value = atoi(cond_var);
            } else {
                // Check if it's a known constant variable
                int idx = find_var(cond_var);
                if (idx != -1 && var_table[idx].is_const) {
                    is_const = 1;
                    cond_value = var_table[idx].value;
                }
            }
            
            if (is_const) {
                // If condition is true (non-zero), jump never happens
                // So the target (else branch) is unreachable
                if (cond_value != 0) {
                    // Mark ifFalse as dead
                    tac[i].is_dead = 1;
                    
                    // Get the label of the else branch
                    char *dead_label = tac[i].result;
                    int marking = 0;
                    
                    // Find and mark the entire else branch as dead
                    for (int j = i + 1; j < tac_count; j++) {
                        if (strcmp(tac[j].op, "Label") == 0) {
                            if (strcmp(tac[j].result, dead_label) == 0) {
                                // Start of else branch
                                marking = 1;
                                tac[j].is_dead = 1;
                            } else if (marking) {
                                // Hit another label (end of else) - stop
                                break;
                            }
                        } else if (marking) {
                            // Inside else branch - mark as dead
                            tac[j].is_dead = 1;
                        }
                    }
                    
                    // Also mark the goto at end of then-branch as dead if it's redundant
                    for (int j = i + 1; j < tac_count; j++) {
                        if (strcmp(tac[j].op, "goto") == 0) {
                            char *goto_target = tac[j].result;
                            // Check if next non-dead instruction is this label
                            for (int k = j + 1; k < tac_count; k++) {
                                if (!tac[k].is_dead) {
                                    if (strcmp(tac[k].op, "Label") == 0 && 
                                        strcmp(tac[k].result, goto_target) == 0) {
                                        tac[j].is_dead = 1;
                                    }
                                    break;
                                }
                            }
                            break;
                        }
                        if (strcmp(tac[j].op, "Label") == 0 && 
                            strcmp(tac[j].result, dead_label) == 0) {
                            break;
                        }
                    }
                }
            }
        }
    }
}


void mark_used_vars() {
    for (int i = 0; i < tac_count; i++) {
        if (tac[i].is_dead) continue;
        if (strcmp(tac[i].op, "ifFalse") == 0 || strcmp(tac[i].op, "return") == 0) {
            int idx = find_var(tac[i].arg1);
            if (idx != -1) var_table[idx].is_used = 1;
        }
        if (strlen(tac[i].arg1) > 0 && !is_constant(tac[i].arg1)) {
            int idx = find_var(tac[i].arg1);
            if (idx != -1) var_table[idx].is_used = 1;
        }
        if (strlen(tac[i].arg2) > 0 && !is_constant(tac[i].arg2)) {
            int idx = find_var(tac[i].arg2);
            if (idx != -1) var_table[idx].is_used = 1;
        }
    }
}

void dead_code_elimination() {
    mark_used_vars();
    for (int i = 0; i < tac_count; i++) {
        if (tac[i].is_dead) continue;
        if ((strcmp(tac[i].op, "=") == 0 || strlen(tac[i].result) > 0) && tac[i].result[0] == 't') {
            int idx = find_var(tac[i].result);
            if (idx != -1 && !var_table[idx].is_used) {
                tac[i].is_dead = 1;
            }
        }
    }
}

void print_tac(const char *title) {
    printf("\n===============================================================\n");
    printf("           %s\n", title);
    printf("===============================================================\n\n");
    
    for (int i = 0; i < tac_count; i++) {
        // IMPORTANT: Skip dead code
        if (tac[i].is_dead) continue;
        
        if (strlen(tac[i].op) == 0) continue;
        
        if (strcmp(tac[i].op, "=") == 0)
            printf("%s = %s\n", tac[i].result, tac[i].arg1);
        else if (strcmp(tac[i].op, "Label") == 0)
            printf("%s:\n", tac[i].result);
        else if (strcmp(tac[i].op, "goto") == 0)
            printf("goto %s\n", tac[i].result);
        else if (strcmp(tac[i].op, "ifFalse") == 0)
            printf("ifFalse %s goto %s\n", tac[i].arg1, tac[i].result);
        else if (strcmp(tac[i].op, "return") == 0) {
            if (strlen(tac[i].arg1) > 0) printf("return %s\n", tac[i].arg1);
            else printf("return\n");
        } else
            printf("%s = %s %s %s\n", tac[i].result, tac[i].arg1, tac[i].op, tac[i].arg2);
    }
}


void print_quadruples() {
    printf("\n===============================================================\n");
    printf("                    QUADRUPLE FORMAT\n");
    printf("===============================================================\n\n");
    printf("%-10s %-20s %-20s %-20s\n", "Op", "Arg1", "Arg2", "Res");
    printf("---------------------------------------------------------------\n");
    for(int i = 0; i < tac_count; i++) {
        if (!tac[i].is_dead && strlen(tac[i].op) > 0) {
            printf("%-10s %-20s %-20s %-20s\n", tac[i].op, tac[i].arg1, tac[i].arg2, tac[i].result);
        }
    }
    printf("---------------------------------------------------------------\n");
    printf("===============================================================\n");
}

int main(int argc, char *argv[]) {
    FILE *input_file;
    
    printf("===============================================================\n");
    printf("   TASK 6: INTERMEDIATE CODE GENERATION + OPTIMIZATION\n");
    printf("===============================================================\n\n");
    
    if (argc > 1) {
        input_file = fopen(argv[1], "r");
        if (!input_file) {
            printf("Error: Cannot open file '%s'\n", argv[1]);
            return 1;
        }
        yyin = input_file;
        printf("Input File: %s\n", argv[1]);
    } else {
        printf("Usage: %s <input_file>\n", argv[0]);
        return 1;
    }
    
    yyparse();
    print_tac("INPUT BEFORE OPTIMIZATION");
    print_quadruples();
    
    constant_propagation();
    print_tac("AFTER CONSTANT PROPAGATION");
    
    constant_folding();
    print_tac("AFTER CONSTANT FOLDING");
    
    enhanced_constant_folding();
    print_tac("AFTER ENHANCED CONSTANT FOLDING");
    
    eliminate_unreachable_code();
    print_tac("AFTER UNREACHABLE CODE ELIMINATION");
    
    dead_code_elimination();
    print_tac("AFTER DEAD CODE ELIMINATION (FINAL)");
    
    if (argc > 1) fclose(input_file);
    return 0;
}
