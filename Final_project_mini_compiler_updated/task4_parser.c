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
#line 1 "task4_parser.y"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern int yylex();
extern FILE *yyin;

int line_num = 1;
int address_counter = 1000;

// AST Node Structure
typedef struct ASTNode {
    char type[50];
    char value[50];
    struct ASTNode *left;
    struct ASTNode *right;
    struct ASTNode *next;
} ASTNode;

// Symbol Table
typedef struct {
    char name[50];
    char type[20];
    int size;
    int dimension;
    char array_spec[20];
    char lines[200];
    int address;
} Symbol;

Symbol symbol_table[100];
int symbol_count = 0;

ASTNode *root = NULL;

void yyerror(const char *s);
ASTNode* create_node(char *type, char *value, ASTNode *left, ASTNode *right);
void print_ast(ASTNode *node, char *prefix, int is_tail);
void add_symbol(char *name, char *type, int size, int dimension, char *array_spec);
void update_symbol_line(char *name);
void auto_declare_if_needed(char *name);
int lookup_symbol(char *name);
int get_type_size(char *type);
void print_symbol_table();

#line 118 "task4_parser.c"

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

#include "task4_parser.h"
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
  YYSYMBOL_param = 40,                     /* param  */
  YYSYMBOL_type = 41,                      /* type  */
  YYSYMBOL_stmt_list = 42,                 /* stmt_list  */
  YYSYMBOL_stmt = 43,                      /* stmt  */
  YYSYMBOL_declaration = 44,               /* declaration  */
  YYSYMBOL_assignment = 45,                /* assignment  */
  YYSYMBOL_if_stmt = 46,                   /* if_stmt  */
  YYSYMBOL_while_stmt = 47,                /* while_stmt  */
  YYSYMBOL_return_stmt = 48,               /* return_stmt  */
  YYSYMBOL_condition = 49,                 /* condition  */
  YYSYMBOL_relop = 50,                     /* relop  */
  YYSYMBOL_expr = 51,                      /* expr  */
  YYSYMBOL_term = 52,                      /* term  */
  YYSYMBOL_factor = 53                     /* factor  */
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
#define YYLAST   156

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  35
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  19
/* YYNRULES -- Number of rules.  */
#define YYNRULES  50
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  108

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
static const yytype_int16 yyrline[] =
{
       0,    76,    76,    83,    93,    97,   102,   110,   114,   118,
     125,   126,   127,   128,   129,   133,   142,   146,   147,   148,
     149,   150,   154,   158,   164,   170,   178,   184,   194,   197,
     206,   212,   215,   221,   227,   228,   229,   230,   231,   232,
     236,   239,   242,   246,   249,   252,   256,   257,   262,   267,
     272
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
  "function_list", "function", "param_list", "param", "type", "stmt_list",
  "stmt", "declaration", "assignment", "if_stmt", "while_stmt",
  "return_stmt", "condition", "relop", "expr", "term", "factor", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-28)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     135,   -28,   -28,   -28,   -28,   -28,    10,   135,   -28,    19,
     -28,   -28,    33,    13,    15,     4,   -28,    60,   -28,    65,
     135,   -28,    45,   -28,   -28,    -4,    67,    92,    -1,   -28,
      89,   -28,   -28,   -28,   -28,   -28,   -28,    69,     2,     2,
       2,     2,   -28,   -28,    96,     2,   -28,    -8,    17,   -28,
      86,   -28,    24,    -3,    68,   113,    98,     2,    53,     2,
       2,   -28,     2,     2,     2,   128,   -28,   -28,   112,   119,
     -28,   -28,   -28,   -28,   -28,   -28,     2,   120,    31,   -28,
      17,    17,   -28,   -28,    28,   116,     2,   -28,    51,   -28,
     -28,   -28,   -16,   107,    80,    94,   146,   -28,   -28,   138,
     -28,   121,   124,   122,   -28,   -28,   105,   -28
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,    10,    11,    12,    13,    14,     0,     2,     4,     0,
       1,     3,     0,     0,     0,     0,     8,     0,    16,     0,
       0,     9,     0,    16,     7,     0,     0,     0,     0,     6,
       0,    15,    17,    18,    19,    20,    21,     0,     0,     0,
       0,     0,    48,    49,    47,     0,    32,     0,    42,    45,
       0,     5,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    31,     0,     0,     0,     0,    22,    26,     0,     0,
      34,    35,    36,    37,    38,    39,     0,     0,     0,    46,
      40,    41,    43,    44,     0,     0,     0,    16,    33,    16,
      50,    25,     0,     0,     0,     0,     0,    23,    27,    28,
      30,     0,     0,     0,    16,    24,     0,    29
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -28,   -28,   -28,   145,   -28,   134,    26,   -23,   -28,   -28,
     -28,   -28,   -28,   -28,   115,   -28,   -27,    12,    63
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     6,     7,     8,    15,    16,    30,    22,    31,    32,
      33,    34,    35,    36,    54,    76,    55,    48,    49
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      37,    47,    42,    43,    44,    42,    43,    44,    59,    60,
      10,    52,    53,    59,    60,    96,    38,    97,    58,     1,
       2,     3,     4,     5,    12,    61,     9,    39,    45,    68,
      78,    45,    46,     9,    19,    62,    63,    84,    20,    17,
      59,    60,    18,    14,    59,    60,    17,    59,    60,    88,
      25,     1,     2,     3,     4,     5,    26,    67,    27,    93,
      28,    91,    13,    90,    94,    21,    95,    59,    60,    59,
      60,    80,    81,    29,    25,     1,     2,     3,     4,     5,
      26,   106,    27,    79,    28,    25,     1,     2,     3,     4,
       5,    26,    23,    27,    50,    28,    40,    51,    69,    25,
       1,     2,     3,     4,     5,    26,    64,    27,    99,    28,
      25,     1,     2,     3,     4,     5,    26,    65,    27,    66,
      28,    41,   100,    59,    60,    82,    83,    57,    77,    59,
      60,    85,    86,   107,    70,    71,    72,    73,    74,    75,
      98,     1,     2,     3,     4,     5,    87,    89,    92,   101,
     102,   104,    11,   103,    24,   105,    56
};

static const yytype_int8 yycheck[] =
{
      23,    28,     3,     4,     5,     3,     4,     5,    16,    17,
       0,    38,    39,    16,    17,    31,    20,    33,    45,     6,
       7,     8,     9,    10,     5,    33,     0,    31,    29,    32,
      57,    29,    33,     7,    30,    18,    19,    64,    34,    13,
      16,    17,    27,    30,    16,    17,    20,    16,    17,    76,
       5,     6,     7,     8,     9,    10,    11,    33,    13,    86,
      15,    33,    29,    32,    87,     5,    89,    16,    17,    16,
      17,    59,    60,    28,     5,     6,     7,     8,     9,    10,
      11,   104,    13,    30,    15,     5,     6,     7,     8,     9,
      10,    11,    27,    13,     5,    15,    29,    28,    30,     5,
       6,     7,     8,     9,    10,    11,    20,    13,    28,    15,
       5,     6,     7,     8,     9,    10,    11,    31,    13,    33,
      15,    29,    28,    16,    17,    62,    63,    31,    30,    16,
      17,     3,    20,    28,    21,    22,    23,    24,    25,    26,
      33,     6,     7,     8,     9,    10,    27,    27,    32,     3,
      12,    27,     7,    32,    20,    33,    41
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     6,     7,     8,     9,    10,    36,    37,    38,    41,
       0,    38,     5,    29,    30,    39,    40,    41,    27,    30,
      34,     5,    42,    27,    40,     5,    11,    13,    15,    28,
      41,    43,    44,    45,    46,    47,    48,    42,    20,    31,
      29,    29,     3,     4,     5,    29,    33,    51,    52,    53,
       5,    28,    51,    51,    49,    51,    49,    31,    51,    16,
      17,    33,    18,    19,    20,    31,    33,    33,    32,    30,
      21,    22,    23,    24,    25,    26,    50,    30,    51,    30,
      52,    52,    53,    53,    51,     3,    20,    27,    51,    27,
      32,    33,    32,    51,    42,    42,    31,    33,    33,    28,
      28,     3,    12,    32,    27,    33,    42,    28
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    35,    36,    37,    37,    38,    38,    39,    39,    40,
      41,    41,    41,    41,    41,    42,    42,    43,    43,    43,
      43,    43,    44,    44,    44,    44,    45,    45,    46,    46,
      47,    48,    48,    49,    50,    50,    50,    50,    50,    50,
      51,    51,    51,    52,    52,    52,    53,    53,    53,    53,
      53
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     1,     8,     7,     3,     1,     2,
       1,     1,     1,     1,     1,     2,     0,     1,     1,     1,
       1,     1,     3,     6,     9,     5,     4,     7,     7,    11,
       7,     3,     2,     3,     1,     1,     1,     1,     1,     1,
       3,     3,     1,     3,     3,     1,     3,     1,     1,     1,
       4
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
  case 2: /* program: function_list  */
#line 76 "task4_parser.y"
                  { 
        root = (yyvsp[0].node); 
        (yyval.node) = (yyvsp[0].node); 
    }
#line 1233 "task4_parser.c"
    break;

  case 3: /* function_list: function_list function  */
#line 83 "task4_parser.y"
                           { 
        if((yyvsp[-1].node) != NULL) {
            ASTNode *temp = (yyvsp[-1].node);
            while(temp->next != NULL) temp = temp->next;
            temp->next = (yyvsp[0].node);
            (yyval.node) = (yyvsp[-1].node);
        } else {
            (yyval.node) = (yyvsp[0].node);
        }
    }
#line 1248 "task4_parser.c"
    break;

  case 4: /* function_list: function  */
#line 93 "task4_parser.y"
               { (yyval.node) = (yyvsp[0].node); }
#line 1254 "task4_parser.c"
    break;

  case 5: /* function: type ID LPAREN param_list RPAREN LBRACE stmt_list RBRACE  */
#line 97 "task4_parser.y"
                                                             {
        add_symbol((yyvsp[-6].str), (yyvsp[-7].str), 0, 1, "-");
        ASTNode *func = create_node("Function", (yyvsp[-6].str), (yyvsp[-4].node), (yyvsp[-1].node));
        (yyval.node) = func;
    }
#line 1264 "task4_parser.c"
    break;

  case 6: /* function: type ID LPAREN RPAREN LBRACE stmt_list RBRACE  */
#line 102 "task4_parser.y"
                                                    {
        add_symbol((yyvsp[-5].str), (yyvsp[-6].str), 0, 1, "-");
        ASTNode *func = create_node("Function", (yyvsp[-5].str), NULL, (yyvsp[-1].node));
        (yyval.node) = func;
    }
#line 1274 "task4_parser.c"
    break;

  case 7: /* param_list: param_list COMMA param  */
#line 110 "task4_parser.y"
                           {
        (yyvsp[-2].node)->next = (yyvsp[0].node);
        (yyval.node) = (yyvsp[-2].node);
    }
#line 1283 "task4_parser.c"
    break;

  case 8: /* param_list: param  */
#line 114 "task4_parser.y"
            { (yyval.node) = (yyvsp[0].node); }
#line 1289 "task4_parser.c"
    break;

  case 9: /* param: type ID  */
#line 118 "task4_parser.y"
            { 
        add_symbol((yyvsp[0].str), (yyvsp[-1].str), get_type_size((yyvsp[-1].str)), 1, "-");
        (yyval.node) = create_node("Parameter", (yyvsp[0].str), NULL, NULL);
    }
#line 1298 "task4_parser.c"
    break;

  case 10: /* type: INT  */
#line 125 "task4_parser.y"
        { (yyval.str) = strdup("int"); }
#line 1304 "task4_parser.c"
    break;

  case 11: /* type: FLOAT  */
#line 126 "task4_parser.y"
            { (yyval.str) = strdup("float"); }
#line 1310 "task4_parser.c"
    break;

  case 12: /* type: CHAR  */
#line 127 "task4_parser.y"
           { (yyval.str) = strdup("char"); }
#line 1316 "task4_parser.c"
    break;

  case 13: /* type: DOUBLE  */
#line 128 "task4_parser.y"
             { (yyval.str) = strdup("double"); }
#line 1322 "task4_parser.c"
    break;

  case 14: /* type: VOID  */
#line 129 "task4_parser.y"
           { (yyval.str) = strdup("void"); }
#line 1328 "task4_parser.c"
    break;

  case 15: /* stmt_list: stmt_list stmt  */
#line 133 "task4_parser.y"
                   {
        if((yyvsp[-1].node) == NULL) (yyval.node) = (yyvsp[0].node);
        else {
            ASTNode *temp = (yyvsp[-1].node);
            while(temp->next != NULL) temp = temp->next;
            temp->next = (yyvsp[0].node);
            (yyval.node) = (yyvsp[-1].node);
        }
    }
#line 1342 "task4_parser.c"
    break;

  case 16: /* stmt_list: %empty  */
#line 142 "task4_parser.y"
      { (yyval.node) = NULL; }
#line 1348 "task4_parser.c"
    break;

  case 17: /* stmt: declaration  */
#line 146 "task4_parser.y"
                { (yyval.node) = (yyvsp[0].node); }
#line 1354 "task4_parser.c"
    break;

  case 18: /* stmt: assignment  */
#line 147 "task4_parser.y"
                 { (yyval.node) = (yyvsp[0].node); }
#line 1360 "task4_parser.c"
    break;

  case 19: /* stmt: if_stmt  */
#line 148 "task4_parser.y"
              { (yyval.node) = (yyvsp[0].node); }
#line 1366 "task4_parser.c"
    break;

  case 20: /* stmt: while_stmt  */
#line 149 "task4_parser.y"
                 { (yyval.node) = (yyvsp[0].node); }
#line 1372 "task4_parser.c"
    break;

  case 21: /* stmt: return_stmt  */
#line 150 "task4_parser.y"
                  { (yyval.node) = (yyvsp[0].node); }
#line 1378 "task4_parser.c"
    break;

  case 22: /* declaration: type ID SEMI  */
#line 154 "task4_parser.y"
                 { 
        add_symbol((yyvsp[-1].str), (yyvsp[-2].str), get_type_size((yyvsp[-2].str)), 1, "-");
        (yyval.node) = create_node("Declaration", (yyvsp[-1].str), NULL, NULL);
    }
#line 1387 "task4_parser.c"
    break;

  case 23: /* declaration: type ID LBRACKET NUM RBRACKET SEMI  */
#line 158 "task4_parser.y"
                                         {
        char dim[20];
        sprintf(dim, "[%d]", (yyvsp[-2].num));
        add_symbol((yyvsp[-4].str), (yyvsp[-5].str), get_type_size((yyvsp[-5].str)) * (yyvsp[-2].num), 1, dim);
        (yyval.node) = create_node("Array_Declaration", (yyvsp[-4].str), NULL, NULL);
    }
#line 1398 "task4_parser.c"
    break;

  case 24: /* declaration: type ID LBRACKET NUM RBRACKET LBRACKET NUM RBRACKET SEMI  */
#line 164 "task4_parser.y"
                                                               {
        char dim[20];
        sprintf(dim, "[%d][%d]", (yyvsp[-5].num), (yyvsp[-2].num));
        add_symbol((yyvsp[-7].str), (yyvsp[-8].str), get_type_size((yyvsp[-8].str)) * (yyvsp[-5].num) * (yyvsp[-2].num), 2, dim);
        (yyval.node) = create_node("Array_Declaration", (yyvsp[-7].str), NULL, NULL);
    }
#line 1409 "task4_parser.c"
    break;

  case 25: /* declaration: type ID ASSIGN expr SEMI  */
#line 170 "task4_parser.y"
                               {
        add_symbol((yyvsp[-3].str), (yyvsp[-4].str), get_type_size((yyvsp[-4].str)), 1, "-");
        ASTNode *decl = create_node("Declaration", (yyvsp[-3].str), NULL, NULL);
        (yyval.node) = create_node("=", "", decl, (yyvsp[-1].node));
    }
#line 1419 "task4_parser.c"
    break;

  case 26: /* assignment: ID ASSIGN expr SEMI  */
#line 178 "task4_parser.y"
                        {
        auto_declare_if_needed((yyvsp[-3].str));
        update_symbol_line((yyvsp[-3].str));
        ASTNode *id_node = create_node("ID", (yyvsp[-3].str), NULL, NULL);
        (yyval.node) = create_node("=", "", id_node, (yyvsp[-1].node));
    }
#line 1430 "task4_parser.c"
    break;

  case 27: /* assignment: ID LBRACKET expr RBRACKET ASSIGN expr SEMI  */
#line 184 "task4_parser.y"
                                                 {
        auto_declare_if_needed((yyvsp[-6].str));
        update_symbol_line((yyvsp[-6].str));
        ASTNode *id_node = create_node("ID", (yyvsp[-6].str), NULL, NULL);
        ASTNode *arr = create_node("Array_Access", "", id_node, (yyvsp[-4].node));
        (yyval.node) = create_node("=", "", arr, (yyvsp[-1].node));
    }
#line 1442 "task4_parser.c"
    break;

  case 28: /* if_stmt: IF LPAREN condition RPAREN LBRACE stmt_list RBRACE  */
#line 194 "task4_parser.y"
                                                       {
        (yyval.node) = create_node("if", "", (yyvsp[-4].node), (yyvsp[-1].node));
    }
#line 1450 "task4_parser.c"
    break;

  case 29: /* if_stmt: IF LPAREN condition RPAREN LBRACE stmt_list RBRACE ELSE LBRACE stmt_list RBRACE  */
#line 197 "task4_parser.y"
                                                                                      {
        ASTNode *if_part = create_node("if", "", (yyvsp[-8].node), (yyvsp[-5].node));
        ASTNode *else_part = create_node("else", "", NULL, (yyvsp[-1].node));
        if_part->next = else_part;
        (yyval.node) = if_part;
    }
#line 1461 "task4_parser.c"
    break;

  case 30: /* while_stmt: WHILE LPAREN condition RPAREN LBRACE stmt_list RBRACE  */
#line 206 "task4_parser.y"
                                                          {
        (yyval.node) = create_node("while", "", (yyvsp[-4].node), (yyvsp[-1].node));
    }
#line 1469 "task4_parser.c"
    break;

  case 31: /* return_stmt: RETURN expr SEMI  */
#line 212 "task4_parser.y"
                     {
        (yyval.node) = create_node("return", "", (yyvsp[-1].node), NULL);
    }
#line 1477 "task4_parser.c"
    break;

  case 32: /* return_stmt: RETURN SEMI  */
#line 215 "task4_parser.y"
                  {
        (yyval.node) = create_node("return", "", NULL, NULL);
    }
#line 1485 "task4_parser.c"
    break;

  case 33: /* condition: expr relop expr  */
#line 221 "task4_parser.y"
                    {
        (yyval.node) = create_node((yyvsp[-1].node)->value, "", (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 1493 "task4_parser.c"
    break;

  case 34: /* relop: LT  */
#line 227 "task4_parser.y"
       { (yyval.node) = create_node("Relop", "<", NULL, NULL); }
#line 1499 "task4_parser.c"
    break;

  case 35: /* relop: GT  */
#line 228 "task4_parser.y"
         { (yyval.node) = create_node("Relop", ">", NULL, NULL); }
#line 1505 "task4_parser.c"
    break;

  case 36: /* relop: LE  */
#line 229 "task4_parser.y"
         { (yyval.node) = create_node("Relop", "<=", NULL, NULL); }
#line 1511 "task4_parser.c"
    break;

  case 37: /* relop: GE  */
#line 230 "task4_parser.y"
         { (yyval.node) = create_node("Relop", ">=", NULL, NULL); }
#line 1517 "task4_parser.c"
    break;

  case 38: /* relop: EQ  */
#line 231 "task4_parser.y"
         { (yyval.node) = create_node("Relop", "==", NULL, NULL); }
#line 1523 "task4_parser.c"
    break;

  case 39: /* relop: NE  */
#line 232 "task4_parser.y"
         { (yyval.node) = create_node("Relop", "!=", NULL, NULL); }
#line 1529 "task4_parser.c"
    break;

  case 40: /* expr: expr PLUS term  */
#line 236 "task4_parser.y"
                   {
        (yyval.node) = create_node("+", "", (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 1537 "task4_parser.c"
    break;

  case 41: /* expr: expr MINUS term  */
#line 239 "task4_parser.y"
                      {
        (yyval.node) = create_node("-", "", (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 1545 "task4_parser.c"
    break;

  case 42: /* expr: term  */
#line 242 "task4_parser.y"
           { (yyval.node) = (yyvsp[0].node); }
#line 1551 "task4_parser.c"
    break;

  case 43: /* term: term MUL factor  */
#line 246 "task4_parser.y"
                    {
        (yyval.node) = create_node("*", "", (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 1559 "task4_parser.c"
    break;

  case 44: /* term: term DIV factor  */
#line 249 "task4_parser.y"
                      {
        (yyval.node) = create_node("/", "", (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 1567 "task4_parser.c"
    break;

  case 45: /* term: factor  */
#line 252 "task4_parser.y"
             { (yyval.node) = (yyvsp[0].node); }
#line 1573 "task4_parser.c"
    break;

  case 46: /* factor: LPAREN expr RPAREN  */
#line 256 "task4_parser.y"
                       { (yyval.node) = (yyvsp[-1].node); }
#line 1579 "task4_parser.c"
    break;

  case 47: /* factor: ID  */
#line 257 "task4_parser.y"
         { 
        auto_declare_if_needed((yyvsp[0].str));
        update_symbol_line((yyvsp[0].str));
        (yyval.node) = create_node("ID", (yyvsp[0].str), NULL, NULL);
    }
#line 1589 "task4_parser.c"
    break;

  case 48: /* factor: NUM  */
#line 262 "task4_parser.y"
          { 
        char num_str[20];
        sprintf(num_str, "%d", (yyvsp[0].num));
        (yyval.node) = create_node("NUM", num_str, NULL, NULL);
    }
#line 1599 "task4_parser.c"
    break;

  case 49: /* factor: FLOAT_NUM  */
#line 267 "task4_parser.y"
                {
        char num_str[20];
        sprintf(num_str, "%.2f", (yyvsp[0].fnum));
        (yyval.node) = create_node("FLOAT", num_str, NULL, NULL);
    }
#line 1609 "task4_parser.c"
    break;

  case 50: /* factor: ID LBRACKET expr RBRACKET  */
#line 272 "task4_parser.y"
                                {
        auto_declare_if_needed((yyvsp[-3].str));
        update_symbol_line((yyvsp[-3].str));
        ASTNode *id_node = create_node("ID", (yyvsp[-3].str), NULL, NULL);
        (yyval.node) = create_node("Array_Access", "", id_node, (yyvsp[-1].node));
    }
#line 1620 "task4_parser.c"
    break;


#line 1624 "task4_parser.c"

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

#line 280 "task4_parser.y"


void yyerror(const char *s) {
    fprintf(stderr, "Error at line %d: %s\n", line_num, s);
}

ASTNode* create_node(char *type, char *value, ASTNode *left, ASTNode *right) {
    ASTNode *node = (ASTNode*)malloc(sizeof(ASTNode));
    strcpy(node->type, type);
    strcpy(node->value, value);
    node->left = left;
    node->right = right;
    node->next = NULL;
    return node;
}

void print_ast(ASTNode *node, char *prefix, int is_tail) {
    if(node == NULL) return;
    
    printf("%s", prefix);
    printf("%s", is_tail ? "└── " : "├── ");
    
    if(strlen(node->value) > 0) {
        printf("%s: %s\n", node->type, node->value);
    } else {
        printf("%s\n", node->type);
    }
    
    char new_prefix[200];
    strcpy(new_prefix, prefix);
    strcat(new_prefix, is_tail ? "    " : "│   ");
    
    int child_count = 0;
    if(node->left) child_count++;
    if(node->right) child_count++;
    
    if(node->left) {
        print_ast(node->left, new_prefix, (child_count == 1));
        child_count--;
    }
    
    if(node->right) {
        print_ast(node->right, new_prefix, 1);
    }
    
    if(node->next) {
        print_ast(node->next, prefix, 0);
    }
}

int get_type_size(char *type) {
    if(strcmp(type, "int") == 0) return 4;
    if(strcmp(type, "float") == 0) return 4;
    if(strcmp(type, "char") == 0) return 1;
    if(strcmp(type, "double") == 0) return 8;
    return 0;
}

int lookup_symbol(char *name) {
    for(int i = 0; i < symbol_count; i++) {
        if(strcmp(symbol_table[i].name, name) == 0) {
            return i;
        }
    }
    return -1;
}

void add_symbol(char *name, char *type, int size, int dimension, char *array_spec) {
    int idx = lookup_symbol(name);
    if(idx != -1) {
        char line_str[10];
        sprintf(line_str, "%d", line_num);
        if(strstr(symbol_table[idx].lines, line_str) == NULL) {
            strcat(symbol_table[idx].lines, ", ");
            strcat(symbol_table[idx].lines, line_str);
        }
        return;
    }
    
    strcpy(symbol_table[symbol_count].name, name);
    strcpy(symbol_table[symbol_count].type, type);
    symbol_table[symbol_count].size = size;
    symbol_table[symbol_count].dimension = dimension;
    strcpy(symbol_table[symbol_count].array_spec, array_spec);
    sprintf(symbol_table[symbol_count].lines, "%d", line_num);
    symbol_table[symbol_count].address = address_counter;
    
    address_counter += (size > 0 ? size : 4);
    symbol_count++;
}

void auto_declare_if_needed(char *name) {
    if(lookup_symbol(name) == -1) {
        add_symbol(name, "int", 4, 1, "-");
    }
}

void update_symbol_line(char *name) {
    int idx = lookup_symbol(name);
    if(idx != -1) {
        char line_str[10];
        sprintf(line_str, "%d", line_num);
        if(strstr(symbol_table[idx].lines, line_str) == NULL) {
            strcat(symbol_table[idx].lines, ", ");
            strcat(symbol_table[idx].lines, line_str);
        }
    }
}

void print_symbol_table() {
    printf("\n===============================================================\n");
    printf("                    SYMBOL TABLE\n");
    printf("===============================================================\n\n");
    
    printf("%-15s %-10s %-6s %-12s %-15s %-10s\n", 
           "NAME", "TYPE", "SIZE", "DIMENSION", "LINE", "ADDRESS");
    printf("---------------------------------------------------------------\n");
    
    for(int i = 0; i < symbol_count; i++) {
        char dim_display[50];
        
        if(strcmp(symbol_table[i].array_spec, "-") == 0) {
            sprintf(dim_display, "%d", symbol_table[i].dimension);
        } else {
            sprintf(dim_display, "%d %s", symbol_table[i].dimension, symbol_table[i].array_spec);
        }
        
        printf("%-15s %-10s %-6d %-12s %-15s %-10d\n",
               symbol_table[i].name,
               symbol_table[i].type,
               symbol_table[i].size,
               dim_display,
               symbol_table[i].lines,
               symbol_table[i].address);
    }
    
    printf("---------------------------------------------------------------\n");
    printf("Total Symbols: %d\n", symbol_count);
    printf("===============================================================\n");
}

int main(int argc, char *argv[]) {
    FILE *input_file;
    
    printf("===============================================================\n");
    printf("       TASK 4: PARSER / ABSTRACT SYNTAX TREE\n");
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
    
    print_symbol_table();
    
    printf("\n===============================================================\n");
    printf("                 ABSTRACT SYNTAX TREE\n");
    printf("===============================================================\n\n");
    
    if(root != NULL) {
        print_ast(root, "", 1);
    }
    
    printf("\n===============================================================\n");
    printf("✓ AST generated successfully!\n");
    printf("===============================================================\n");
    
    if (argc > 1) fclose(input_file);
    
    return 0;
}
