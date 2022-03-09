/* original parser id follows */
/* yysccsid[] = "@(#)yaccpar	1.9 (Berkeley) 02/21/93" */
/* (use YYMAJOR/YYMINOR for ifdefs dependent on parser version) */

#define YYBYACC 1
#define YYMAJOR 2
#define YYMINOR 0
#define YYPATCH 20260126

#define YYEMPTY        (-1)
#define yyclearin      (yychar = YYEMPTY)
#define yyerrok        (yyerrflag = 0)
#define YYRECOVERING() (yyerrflag != 0)
#define YYENOMEM       (-2)
#define YYEOF          0
#undef YYBTYACC
#define YYBTYACC 0
#define YYDEBUGSTR YYPREFIX "debug"

#ifndef yyparse
#define yyparse    glcpp_parser_parse
#endif /* yyparse */

#ifndef yylex
#define yylex      glcpp_parser_lex
#endif /* yylex */

#ifndef yyerror
#define yyerror    glcpp_parser_error
#endif /* yyerror */

#ifndef yychar
#define yychar     glcpp_parser_char
#endif /* yychar */

#ifndef yyval
#define yyval      glcpp_parser_val
#endif /* yyval */

#ifndef yylval
#define yylval     glcpp_parser_lval
#endif /* yylval */

#ifndef yydebug
#define yydebug    glcpp_parser_debug
#endif /* yydebug */

#ifndef yynerrs
#define yynerrs    glcpp_parser_nerrs
#endif /* yynerrs */

#ifndef yyerrflag
#define yyerrflag  glcpp_parser_errflag
#endif /* yyerrflag */

#ifndef yylhs
#define yylhs      glcpp_parser_lhs
#endif /* yylhs */

#ifndef yylen
#define yylen      glcpp_parser_len
#endif /* yylen */

#ifndef yydefred
#define yydefred   glcpp_parser_defred
#endif /* yydefred */

#ifndef yystos
#define yystos     glcpp_parser_stos
#endif /* yystos */

#ifndef yydgoto
#define yydgoto    glcpp_parser_dgoto
#endif /* yydgoto */

#ifndef yysindex
#define yysindex   glcpp_parser_sindex
#endif /* yysindex */

#ifndef yyrindex
#define yyrindex   glcpp_parser_rindex
#endif /* yyrindex */

#ifndef yygindex
#define yygindex   glcpp_parser_gindex
#endif /* yygindex */

#ifndef yytable
#define yytable    glcpp_parser_table
#endif /* yytable */

#ifndef yycheck
#define yycheck    glcpp_parser_check
#endif /* yycheck */

#ifndef yyname
#define yyname     glcpp_parser_name
#endif /* yyname */

#ifndef yyrule
#define yyrule     glcpp_parser_rule
#endif /* yyrule */

#ifndef yyloc
#define yyloc      glcpp_parser_loc
#endif /* yyloc */

#ifndef yylloc
#define yylloc     glcpp_parser_lloc
#endif /* yylloc */

#if YYBTYACC

#ifndef yycindex
#define yycindex   glcpp_parser_cindex
#endif /* yycindex */

#ifndef yyctable
#define yyctable   glcpp_parser_ctable
#endif /* yyctable */

#endif /* YYBTYACC */

#define YYPREFIX "glcpp_parser_"

#define YYPURE 1

#line 2 "../mesa/src/compiler/glsl/glcpp/glcpp-parse.y"
/*
 * Copyright © 2010 Intel Corporation
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <inttypes.h>

#include "glcpp.h"
#include "main/mtypes.h"
#include "util/strndup.h"

const char *
_mesa_lookup_shader_include(struct gl_context *ctx, char *path,
                            bool error_check);

size_t
_mesa_get_shader_include_cursor(struct gl_shared_state *shared);

void
_mesa_set_shader_include_cursor(struct gl_shared_state *shared, size_t cursor);

static void
yyerror(YYLTYPE *locp, glcpp_parser_t *parser, const char *error);

static void
_define_object_macro(glcpp_parser_t *parser,
                     YYLTYPE *loc,
                     const char *macro,
                     token_list_t *replacements);

static void
_define_function_macro(glcpp_parser_t *parser,
                       YYLTYPE *loc,
                       const char *macro,
                       string_list_t *parameters,
                       token_list_t *replacements);

static string_list_t *
_string_list_create(glcpp_parser_t *parser);

static void
_string_list_append_item(glcpp_parser_t *parser, string_list_t *list,
                         const char *str);

static int
_string_list_contains(string_list_t *list, const char *member, int *index);

static const char *
_string_list_has_duplicate(string_list_t *list);

static int
_string_list_length(string_list_t *list);

static int
_string_list_equal(string_list_t *a, string_list_t *b);

static argument_list_t *
_argument_list_create(glcpp_parser_t *parser);

static void
_argument_list_append(glcpp_parser_t *parser, argument_list_t *list,
                      token_list_t *argument);

static int
_argument_list_length(argument_list_t *list);

static token_list_t *
_argument_list_member_at(argument_list_t *list, int index);

static token_t *
_token_create_str(glcpp_parser_t *parser, int type, char *str);

static token_t *
_token_create_ival(glcpp_parser_t *parser, int type, int ival);

static token_list_t *
_token_list_create(glcpp_parser_t *parser);

static void
_token_list_append(glcpp_parser_t *parser, token_list_t *list, token_t *token);

static void
_token_list_append_list(token_list_t *list, token_list_t *tail);

static int
_token_list_equal_ignoring_space(token_list_t *a, token_list_t *b);

static void
_parser_active_list_push(glcpp_parser_t *parser, const char *identifier,
                         token_node_t *marker);

static void
_parser_active_list_pop(glcpp_parser_t *parser);

static int
_parser_active_list_contains(glcpp_parser_t *parser, const char *identifier);

typedef enum {
   EXPANSION_MODE_IGNORE_DEFINED,
   EXPANSION_MODE_EVALUATE_DEFINED
} expansion_mode_t;

/* Expand list, and begin lexing from the result (after first
 * prefixing a token of type 'head_token_type').
 */
static void
_glcpp_parser_expand_and_lex_from(glcpp_parser_t *parser, int head_token_type,
                                  token_list_t *list, expansion_mode_t mode);

/* Perform macro expansion in-place on the given list. */
static void
_glcpp_parser_expand_token_list(glcpp_parser_t *parser, token_list_t *list,
                                expansion_mode_t mode);

static void
_glcpp_parser_print_expanded_token_list(glcpp_parser_t *parser,
                                        token_list_t *list);

static void
_glcpp_parser_skip_stack_push_if(glcpp_parser_t *parser, YYLTYPE *loc,
                                 int condition);

static void
_glcpp_parser_skip_stack_change_if(glcpp_parser_t *parser, YYLTYPE *loc,
                                   const char *type, int condition);

static void
_glcpp_parser_skip_stack_pop(glcpp_parser_t *parser, YYLTYPE *loc);

static void
_glcpp_parser_handle_version_declaration(glcpp_parser_t *parser, intmax_t version,
                                         const char *ident, bool explicitly_set);

static int
glcpp_parser_lex(YYSTYPE *yylval, YYLTYPE *yylloc, glcpp_parser_t *parser);

static void
glcpp_parser_lex_from(glcpp_parser_t *parser, token_list_t *list);

struct define_include {
   glcpp_parser_t *parser;
   YYLTYPE *loc;
};

static void
glcpp_parser_copy_defines(const void *key, void *data, void *closure);

static void
add_builtin_define(glcpp_parser_t *parser, const char *name, int value);

#line 302 "compiler/glsl/glcpp/glcpp-parse.c"

#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
/* Default: YYLTYPE is the text position type. */
typedef struct YYLTYPE
{
    int first_line;
    int first_column;
    int last_line;
    int last_column;
    unsigned source;
} YYLTYPE;
#define YYLTYPE_IS_DECLARED 1
#endif
#define YYRHSLOC(rhs, k) ((rhs)[k])

/* compatibility with bison */
#ifdef YYPARSE_PARAM
/* compatibility with FreeBSD */
# ifdef YYPARSE_PARAM_TYPE
#  define YYPARSE_DECL() yyparse(YYPARSE_PARAM_TYPE YYPARSE_PARAM)
# else
#  define YYPARSE_DECL() yyparse(void *YYPARSE_PARAM)
# endif
#else
# define YYPARSE_DECL() yyparse(glcpp_parser_t *parser)
#endif

/* Parameters sent to lex. */
#ifdef YYLEX_PARAM
# ifdef YYLEX_PARAM_TYPE
#  define YYLEX_DECL() yylex(YYSTYPE *yylval, YYLTYPE *yylloc, YYLEX_PARAM_TYPE YYLEX_PARAM)
# else
#  define YYLEX_DECL() yylex(YYSTYPE *yylval, YYLTYPE *yylloc, void * YYLEX_PARAM)
# endif
# define YYLEX yylex(&yylval, &yylloc, YYLEX_PARAM)
#else
# define YYLEX_DECL() yylex(YYSTYPE *yylval, YYLTYPE *yylloc, glcpp_parser_t *parser)
# define YYLEX yylex(&yylval, &yylloc, parser)
#endif

/* Parameters sent to yyerror. */
#ifndef YYERROR_DECL
#define YYERROR_DECL() yyerror(YYLTYPE *loc, glcpp_parser_t *parser, const char *s)
#endif
#ifndef YYERROR_CALL
#define YYERROR_CALL(msg) yyerror(&yylloc, parser, msg)
#endif

extern int YYPARSE_DECL();

#define DEFINED 257
#define ELIF_EXPANDED 258
#define HASH_TOKEN 259
#define DEFINE_TOKEN 260
#define FUNC_IDENTIFIER 261
#define OBJ_IDENTIFIER 262
#define ELIF 263
#define ELSE 264
#define ENDIF 265
#define ERROR_TOKEN 266
#define IF 267
#define IFDEF 268
#define IFNDEF 269
#define LINE 270
#define PRAGMA 271
#define UNDEF 272
#define VERSION_TOKEN 273
#define GARBAGE 274
#define IDENTIFIER 275
#define IF_EXPANDED 276
#define INTEGER 277
#define INTEGER_STRING 278
#define LINE_EXPANDED 279
#define NEWLINE 280
#define OTHER 281
#define PLACEHOLDER 282
#define SPACE 283
#define PLUS_PLUS 284
#define MINUS_MINUS 285
#define PATH 286
#define INCLUDE 287
#define PASTE 288
#define OR 289
#define AND 290
#define EQUAL 291
#define NOT_EQUAL 292
#define LESS_OR_EQUAL 293
#define GREATER_OR_EQUAL 294
#define LEFT_SHIFT 295
#define RIGHT_SHIFT 296
#define UNARY 297
#define YYERRCODE 256
typedef int YYINT;
static const YYINT glcpp_parser_lhs[] = {                -1,
    0,    0,   10,   10,   10,   10,   12,   12,   12,   12,
   12,   13,   13,   13,   11,   11,   11,   14,   14,   14,
   14,   14,   14,   14,   14,   14,   17,   14,   18,   14,
   14,   14,   14,   14,   15,   15,   15,    2,    2,    3,
    4,    4,    4,    4,    4,    4,    4,    4,    4,    4,
    4,    4,    4,    4,    4,    4,    4,    4,    4,    4,
    4,    4,    4,    4,    4,    5,    5,    9,    9,    8,
    8,   16,   16,    7,    7,    6,    6,    6,    6,    6,
    6,    6,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,
};
static const YYINT glcpp_parser_len[] = {                 2,
    0,    2,    1,    2,    1,    1,    3,    3,    3,    4,
    4,    3,    5,    6,    1,    1,    4,    3,    4,    3,
    4,    3,    5,    5,    4,    3,    0,    4,    0,    4,
    4,    5,    2,    3,    3,    3,    4,    1,    1,    1,
    1,    1,    3,    3,    3,    3,    3,    3,    3,    3,
    3,    3,    3,    3,    3,    3,    3,    3,    3,    3,
    2,    2,    2,    2,    3,    1,    3,    1,    2,    0,
    1,    0,    1,    1,    2,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,
};
static const YYINT glcpp_parser_defred[] = {              1,
    0,   80,    0,    0,   76,    0,   77,    0,   68,   81,
    0,  114,  115,   78,  113,  109,  108,  107,  106,   90,
  104,  105,  100,  101,  102,  103,   98,   99,   92,   93,
   91,   96,   97,   85,   86,   95,   94,  111,   83,   84,
   87,   88,   89,  110,  112,   79,   74,    0,    5,    2,
    3,    6,   15,   16,   42,   39,   38,    0,    0,    0,
    0,    0,   41,    0,    0,    0,   27,   29,    0,    0,
    0,    0,    0,    0,    0,    0,    0,   33,    0,    0,
    0,    4,   69,   82,   75,   64,   63,    0,   61,   62,
    8,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,   36,   18,   26,    0,    0,    0,   35,   22,    0,
    0,    0,    0,   34,    0,   40,    0,    0,   20,    7,
    9,    0,    0,   65,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,   60,
   59,   58,    0,    0,    0,   25,   28,   30,   21,    0,
    0,    0,   17,   19,    0,   31,   37,   11,   10,   66,
    0,    0,   12,   23,   24,   32,    0,    0,    0,   13,
    0,   67,   14,
};
#if defined(YYDESTRUCT_CALL) || defined(YYSTYPE_TOSTRING)
static const YYINT glcpp_parser_stos[] = {                0,
  299,  257,  258,  259,  275,  276,  278,  279,  280,  281,
  283,  284,  285,  286,  288,  289,  290,  124,   94,   38,
  291,  292,   60,   62,  293,  294,  295,  296,   43,   45,
   42,   47,   37,   40,   41,   33,  126,   44,   91,   93,
  123,  125,   46,   59,   61,  300,  305,  306,  308,  309,
  310,  311,  313,  314,  275,  277,  278,   43,   45,   40,
   33,  126,  301,  303,  260,  263,  264,  265,  266,  267,
  268,  269,  270,  271,  272,  273,  274,  280,  287,  303,
  301,  310,  280,  283,  305,  303,  303,  303,  303,  303,
  280,  289,  290,  124,   94,   38,  291,  292,   60,   62,
  293,  294,  295,  296,   43,   45,   42,   47,   37,  261,
  262,  280,  312,  280,  306,  316,  317,  280,  280,  306,
  275,  275,  306,  280,  275,  278,  302,  306,  280,  280,
  280,  286,  301,   41,  303,  303,  303,  303,  303,  303,
  303,  303,  303,  303,  303,  303,  303,  303,  303,  303,
  303,  303,   40,  306,  307,  280,  280,  280,  280,  306,
  315,  315,  280,  280,  275,  280,  280,  280,  280,  275,
   41,  304,  280,  280,  280,  280,  307,   41,   44,  280,
  307,  275,  280,
};
#endif /* YYDESTRUCT_CALL || YYSTYPE_TOSTRING */
static const YYINT glcpp_parser_dgoto[] = {               1,
   46,   63,  127,   64,  172,   47,  154,  155,   49,   50,
   51,   52,  113,   53,   54,  161,  116,  117,
};
static const YYINT glcpp_parser_sindex[] = {              0,
  -33,    0,  300, 1099,    0,  300,    0, -215,    0,    0,
 -253,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    7,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  300,  300,  300,
  300,  300,    0,  840, -245,   66,    0,    0, -262,  106,
 -243, -241,  813, -258, -239, -236,  813,    0, -234,  871,
 -192,    0,    0,    0,    0,    0,    0,  882,    0,    0,
    0,  300,  300,  300,  300,  300,  300,  300,  300,  300,
  300,  300,  300,  300,  300,  300,  300,  300,  300,   17,
  813,    0,    0,    0,  370, -225, -216,    0,    0,  410,
  813,  813,  469,    0, -210,    0, -256,  509,    0,    0,
    0, -206, -205,    0,  908,  947,   35,  437,  915,  141,
  141,  -22,  -22,  -22,  -22,   -4,   -4,  127,  127,    0,
    0,    0,  -39,  813, -201,    0,    0,    0,    0,  813,
 -199, -197,    0,    0, -193,    0,    0,    0,    0,    0,
  813,   15,    0,    0,    0,    0, -191,  813, -179,    0,
 -178,    0,    0,
};
static const YYINT glcpp_parser_rindex[] = {              0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  773,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
 -175,    0,    0,    0,    0,    0,    0,    0,    0,    0,
 -165, -165,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  -40,   24,   30,  -10,  294,  334,
 1044, 1214, 1231, 1237, 1254,  547, 1174,  955,  990,    0,
    0,    0,    0, -164,    0,    0,    0,    0,    0, -163,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
 -175,    0,    0,    0,    0,    0,    0, -175,    0,    0,
    0,    0,    0,
};
#if YYBTYACC
static const YYINT glcpp_parser_cindex[] = {              0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,
};
#endif
static const YYINT glcpp_parser_gindex[] = {              0,
    0,   -5,    0,  615,    0,  161,  144, -141,    0,    0,
  107,    0,    0,    0,    0,   -3,    0,    0,
};
#define YYTABLESIZE 1548
static const YYINT glcpp_parser_table[] = {              36,
   43,  171,   81,   33,   20,    4,   34,   35,   31,   29,
   38,   30,   43,   32,  109,  110,  111,  118,  165,  107,
  105,  124,  106,  166,  108,   44,   23,   45,   24,  177,
   46,  121,  109,  122,  112,  125,  181,  107,  105,   36,
  106,  126,  108,   33,   20,  129,   34,   35,   31,   29,
   38,   30,   43,   32,  157,  178,  153,   39,  179,   40,
   19,   56,   57,  158,   44,   44,   23,   45,   24,  164,
   45,  109,   96,  168,  169,  133,  107,  105,  173,  106,
  174,  108,  175,   46,   56,   57,  176,  131,  180,   41,
   18,   42,   37,  132,   99,  182,  100,   39,   36,   40,
   19,  183,   33,   20,   70,   34,   35,   31,   29,   38,
   30,   43,   32,   46,   72,   71,   73,   82,  162,    0,
    0,    0,    0,    0,   44,   23,   45,   24,   95,   41,
   18,   42,   37,    0,    0,    0,    0,    0,   36,    0,
    0,    0,   33,   20,   48,   34,   35,   31,   29,   38,
   30,   43,   32,   45,    0,    0,   39,    0,   40,   19,
    0,    0,    0,  109,   44,   23,   45,   24,  107,    0,
    0,    0,    0,  108,    0,    0,    0,  109,    0,    0,
    0,    0,  107,  105,    0,  106,    0,  108,   41,   18,
   42,   37,    0,    0,    0,    0,   39,    0,   40,   19,
   99,    0,  100,    0,    0,    0,    0,    0,   85,  115,
    0,    0,    0,  120,    0,    0,  123,    0,    0,    0,
  128,    0,    0,    2,    3,    4,    0,    0,   41,   18,
   42,   37,    0,    0,    0,  170,    0,    0,    0,   43,
    0,    5,    6,    0,    7,    8,    9,   10,   43,   11,
   12,   13,   14,    0,   15,   16,   17,   21,   22,   25,
   26,   27,   28,    2,  160,  160,    0,    0,    0,   46,
    0,    0,  103,  104,    0,   85,    0,    0,   46,   46,
   85,    5,    0,   85,    7,    0,   83,   10,   85,   84,
   12,   13,   14,    0,   15,   16,   17,   21,   22,   25,
   26,   27,   28,   44,    0,    0,    0,    0,    0,   45,
    0,    0,   44,   44,   85,    0,    0,    0,   45,   45,
   85,    0,    2,    0,    0,   97,   98,  101,  102,  103,
  104,   47,   61,    0,   47,    0,    0,    0,    0,   60,
    5,    0,   58,    7,   59,  114,   10,    0,   84,   12,
   13,   14,    0,   15,   16,   17,   21,   22,   25,   26,
   27,   28,    2,    0,    0,    0,    0,    0,    0,    0,
    0,   49,    0,    0,   49,    0,    0,    0,    0,    0,
    5,    0,    0,    7,    0,  119,   10,   47,   84,   12,
   13,   14,    0,   15,   16,   17,   21,   22,   25,   26,
   27,   28,   36,    0,    0,    0,   33,   20,    0,   34,
   35,   31,   29,   38,   30,   43,   32,   47,    0,    0,
    0,    0,    0,    0,    0,   62,    0,   49,   44,   23,
   45,   24,    0,  101,  102,  103,  104,    0,    0,    0,
    0,    0,   36,    0,    0,    0,   33,   20,    0,   34,
   35,   31,   29,   38,   30,   43,   32,   49,    0,    0,
   39,    0,   40,   19,    0,    0,    0,    0,   44,   23,
   45,   24,    0,  109,   96,    0,    0,    0,  107,  105,
    0,  106,    0,  108,    0,    0,    0,    0,    0,    0,
    0,    0,   41,   18,   42,   37,   99,    0,  100,    0,
   39,   36,   40,   19,    0,   33,   20,    0,   34,   35,
   31,   29,   38,   30,   43,   32,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,   44,   23,   45,
   24,    0,   41,   18,   42,   37,    0,    0,    0,    0,
    0,   36,    0,    0,    0,   33,   20,    0,   34,   35,
   31,   29,   38,   30,   43,   32,    0,    0,    0,   39,
    0,   40,   19,    0,    0,    0,    0,   44,   23,   45,
   24,    0,    0,   47,   55,    0,   56,   57,    0,    0,
    0,    0,   47,   47,   55,    0,    0,   55,    0,    0,
    0,   41,   18,   42,   37,    0,    0,    0,    0,   39,
    0,   40,   19,    0,    0,    0,   55,    0,   55,    0,
    0,    0,    0,   49,    0,    0,    0,    0,    0,    0,
   80,    0,   49,   49,   49,   49,    2,    0,    0,    0,
    0,   41,   18,   42,   37,    0,    0,    0,    0,    0,
   55,    0,    0,    0,    5,    0,    0,    7,    0,  156,
   10,    0,   84,   12,   13,   14,    0,   15,   16,   17,
   21,   22,   25,   26,   27,   28,    2,    0,    0,    0,
   55,    0,   86,   87,   88,   89,   90,    0,    0,    0,
    0,    0,    0,    0,    5,    0,    0,    7,    0,  159,
   10,    0,   84,   12,   13,   14,    0,   15,   16,   17,
   21,   22,   25,   26,   27,   28,  135,  136,  137,  138,
  139,  140,  141,  142,  143,  144,  145,  146,  147,  148,
  149,  150,  151,  152,    0,    2,    0,   97,   98,  101,
  102,  103,  104,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    5,    0,    0,    7,    0,  163,   10,
    0,   84,   12,   13,   14,    0,   15,   16,   17,   21,
   22,   25,   26,   27,   28,    2,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    5,    0,    0,    7,    0,  167,   10,
    0,   84,   12,   13,   14,    0,   15,   16,   17,   21,
   22,   25,   26,   27,   28,   82,    0,    0,    0,   82,
   82,    0,   82,   82,   82,   82,   82,   82,   82,   82,
    0,    0,    0,    0,    0,    0,   55,    0,    0,    0,
    0,   82,   82,   82,   82,   55,   55,   55,   55,   55,
   55,   55,   55,    0,    0,   36,    0,    0,    0,   33,
   20,    0,   34,   35,   31,   29,   38,   30,   43,   32,
    0,    0,    0,   82,    0,   82,   82,    0,    0,    0,
    0,   44,   23,   45,   24,    0,  109,   96,    0,    0,
    0,  107,  105,    0,  106,    0,  108,    0,    0,    0,
    0,    0,    0,    0,    0,   82,   82,   82,   82,   99,
    0,  100,    0,   39,    0,   40,   19,  109,   96,    0,
    0,    0,  107,  105,    0,  106,    0,  108,  109,   96,
    0,    0,  134,  107,  105,    0,  106,    0,  108,    0,
   99,    0,  100,   95,    0,   41,   18,   42,   37,    0,
    0,   99,    0,  100,  109,   96,    0,    0,    0,  107,
  105,  109,  106,    0,  108,    0,  107,  105,    0,  106,
    0,  108,    0,   94,   95,    0,    0,   99,    0,  100,
    0,    0,    0,    0,   99,   95,  100,    0,    0,    0,
    0,    0,    0,  109,   96,    0,    0,    0,  107,  105,
    0,  106,   57,  108,   94,   57,    0,   57,    0,   57,
    0,   95,    0,    0,    0,   94,   99,    0,  100,    0,
    0,    0,    0,    0,   57,    0,   57,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,   56,    0,   82,
   56,   94,   56,    0,   56,    0,    0,    0,    0,    0,
   95,    0,    0,    0,    0,    0,    0,   82,   57,   56,
   82,   56,   82,   82,    0,   82,   82,   82,   82,    0,
   82,   82,   82,   82,   82,   82,   82,   82,   82,    2,
   94,    0,    0,    0,    0,    0,    0,    0,   57,    0,
    0,   48,    0,   56,   48,    0,    0,    5,    0,    0,
    7,    0,    0,   10,    0,   84,   12,   13,   14,    0,
   15,   16,   17,   21,   22,   25,   26,   27,   28,    0,
    0,    0,    0,   56,    0,    0,    0,    0,    0,   91,
    0,    0,    0,    0,    0,    0,    0,    0,   92,   93,
   97,   98,  101,  102,  103,  104,    0,   48,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  130,    0,    0,    0,    0,    0,    0,    0,    0,   92,
   93,   97,   98,  101,  102,  103,  104,   48,    0,    0,
   92,   93,   97,   98,  101,  102,  103,  104,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,   93,   97,   98,
  101,  102,  103,  104,    0,   97,   98,  101,  102,  103,
  104,   54,    0,    0,   54,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,   54,   57,   54,    0,   97,   98,  101,
  102,  103,  104,   57,   57,   57,   57,   57,   57,   57,
   57,   53,    0,    0,   53,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,   54,   52,   56,
    0,   52,    0,   53,   51,   53,    0,   51,   56,   56,
   56,   56,   56,   56,   56,   56,    0,    0,    0,    0,
   52,   50,   52,    0,   50,    0,   51,   54,   51,    0,
    0,    0,    0,    0,    0,    0,    0,   53,    0,    0,
    0,    0,    0,   50,    0,   50,    0,    0,    0,    0,
    0,    0,    0,   48,   52,    0,    0,    0,    0,    0,
   51,    0,   48,   48,   48,   48,    0,   53,    0,    0,
    0,    0,    0,    0,    0,    0,    0,   50,    0,    0,
    0,    0,    0,    0,   52,    0,    0,    0,   65,    0,
   51,   66,   67,   68,   69,   70,   71,   72,   73,   74,
   75,   76,   77,    0,    0,    0,    0,   50,   78,    0,
    0,    0,    0,    0,    0,   79,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,   54,    0,    0,    0,    0,    0,    0,
    0,    0,   54,   54,   54,   54,   54,   54,   54,   54,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,   53,    0,    0,    0,    0,    0,    0,
    0,    0,   53,   53,   53,   53,   53,   53,    0,    0,
   52,    0,    0,    0,    0,    0,   51,    0,    0,   52,
   52,   52,   52,   52,   52,   51,   51,   51,   51,   51,
   51,    0,    0,   50,    0,    0,    0,    0,    0,    0,
    0,    0,   50,   50,   50,   50,   50,   50,
};
static const YYINT glcpp_parser_check[] = {              33,
   41,   41,    8,   37,   38,  259,   40,   41,   42,   43,
   44,   45,   46,   47,   37,  261,  262,  280,  275,   42,
   43,  280,   45,  280,   47,   59,   60,   61,   62,  171,
   41,  275,   37,  275,  280,  275,  178,   42,   43,   33,
   45,  278,   47,   37,   38,  280,   40,   41,   42,   43,
   44,   45,   46,   47,  280,   41,   40,   91,   44,   93,
   94,  277,  278,  280,   41,   59,   60,   61,   62,  280,
   41,   37,   38,  280,  280,   81,   42,   43,  280,   45,
  280,   47,  280,   94,  277,  278,  280,  280,  280,  123,
  124,  125,  126,  286,   60,  275,   62,   91,   33,   93,
   94,  280,   37,   38,  280,   40,   41,   42,   43,   44,
   45,   46,   47,  124,  280,  280,  280,   11,  122,   -1,
   -1,   -1,   -1,   -1,   59,   60,   61,   62,   94,  123,
  124,  125,  126,   -1,   -1,   -1,   -1,   -1,   33,   -1,
   -1,   -1,   37,   38,    1,   40,   41,   42,   43,   44,
   45,   46,   47,  124,   -1,   -1,   91,   -1,   93,   94,
   -1,   -1,   -1,   37,   59,   60,   61,   62,   42,   -1,
   -1,   -1,   -1,   47,   -1,   -1,   -1,   37,   -1,   -1,
   -1,   -1,   42,   43,   -1,   45,   -1,   47,  123,  124,
  125,  126,   -1,   -1,   -1,   -1,   91,   -1,   93,   94,
   60,   -1,   62,   -1,   -1,   -1,   -1,   -1,   48,   66,
   -1,   -1,   -1,   70,   -1,   -1,   73,   -1,   -1,   -1,
   77,   -1,   -1,  257,  258,  259,   -1,   -1,  123,  124,
  125,  126,   -1,   -1,   -1,  275,   -1,   -1,   -1,  280,
   -1,  275,  276,   -1,  278,  279,  280,  281,  289,  283,
  284,  285,  286,   -1,  288,  289,  290,  291,  292,  293,
  294,  295,  296,  257,  121,  122,   -1,   -1,   -1,  280,
   -1,   -1,  295,  296,   -1,  115,   -1,   -1,  289,  290,
  120,  275,   -1,  123,  278,   -1,  280,  281,  128,  283,
  284,  285,  286,   -1,  288,  289,  290,  291,  292,  293,
  294,  295,  296,  280,   -1,   -1,   -1,   -1,   -1,  280,
   -1,   -1,  289,  290,  154,   -1,   -1,   -1,  289,  290,
  160,   -1,  257,   -1,   -1,  291,  292,  293,  294,  295,
  296,   38,   33,   -1,   41,   -1,   -1,   -1,   -1,   40,
  275,   -1,   43,  278,   45,  280,  281,   -1,  283,  284,
  285,  286,   -1,  288,  289,  290,  291,  292,  293,  294,
  295,  296,  257,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   38,   -1,   -1,   41,   -1,   -1,   -1,   -1,   -1,
  275,   -1,   -1,  278,   -1,  280,  281,   94,  283,  284,
  285,  286,   -1,  288,  289,  290,  291,  292,  293,  294,
  295,  296,   33,   -1,   -1,   -1,   37,   38,   -1,   40,
   41,   42,   43,   44,   45,   46,   47,  124,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  126,   -1,   94,   59,   60,
   61,   62,   -1,  293,  294,  295,  296,   -1,   -1,   -1,
   -1,   -1,   33,   -1,   -1,   -1,   37,   38,   -1,   40,
   41,   42,   43,   44,   45,   46,   47,  124,   -1,   -1,
   91,   -1,   93,   94,   -1,   -1,   -1,   -1,   59,   60,
   61,   62,   -1,   37,   38,   -1,   -1,   -1,   42,   43,
   -1,   45,   -1,   47,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  123,  124,  125,  126,   60,   -1,   62,   -1,
   91,   33,   93,   94,   -1,   37,   38,   -1,   40,   41,
   42,   43,   44,   45,   46,   47,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   59,   60,   61,
   62,   -1,  123,  124,  125,  126,   -1,   -1,   -1,   -1,
   -1,   33,   -1,   -1,   -1,   37,   38,   -1,   40,   41,
   42,   43,   44,   45,   46,   47,   -1,   -1,   -1,   91,
   -1,   93,   94,   -1,   -1,   -1,   -1,   59,   60,   61,
   62,   -1,   -1,  280,  275,   -1,  277,  278,   -1,   -1,
   -1,   -1,  289,  290,   38,   -1,   -1,   41,   -1,   -1,
   -1,  123,  124,  125,  126,   -1,   -1,   -1,   -1,   91,
   -1,   93,   94,   -1,   -1,   -1,   60,   -1,   62,   -1,
   -1,   -1,   -1,  280,   -1,   -1,   -1,   -1,   -1,   -1,
    6,   -1,  289,  290,  291,  292,  257,   -1,   -1,   -1,
   -1,  123,  124,  125,  126,   -1,   -1,   -1,   -1,   -1,
   94,   -1,   -1,   -1,  275,   -1,   -1,  278,   -1,  280,
  281,   -1,  283,  284,  285,  286,   -1,  288,  289,  290,
  291,  292,  293,  294,  295,  296,  257,   -1,   -1,   -1,
  124,   -1,   58,   59,   60,   61,   62,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  275,   -1,   -1,  278,   -1,  280,
  281,   -1,  283,  284,  285,  286,   -1,  288,  289,  290,
  291,  292,  293,  294,  295,  296,   92,   93,   94,   95,
   96,   97,   98,   99,  100,  101,  102,  103,  104,  105,
  106,  107,  108,  109,   -1,  257,   -1,  291,  292,  293,
  294,  295,  296,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  275,   -1,   -1,  278,   -1,  280,  281,
   -1,  283,  284,  285,  286,   -1,  288,  289,  290,  291,
  292,  293,  294,  295,  296,  257,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  275,   -1,   -1,  278,   -1,  280,  281,
   -1,  283,  284,  285,  286,   -1,  288,  289,  290,  291,
  292,  293,  294,  295,  296,   33,   -1,   -1,   -1,   37,
   38,   -1,   40,   41,   42,   43,   44,   45,   46,   47,
   -1,   -1,   -1,   -1,   -1,   -1,  280,   -1,   -1,   -1,
   -1,   59,   60,   61,   62,  289,  290,  291,  292,  293,
  294,  295,  296,   -1,   -1,   33,   -1,   -1,   -1,   37,
   38,   -1,   40,   41,   42,   43,   44,   45,   46,   47,
   -1,   -1,   -1,   91,   -1,   93,   94,   -1,   -1,   -1,
   -1,   59,   60,   61,   62,   -1,   37,   38,   -1,   -1,
   -1,   42,   43,   -1,   45,   -1,   47,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  123,  124,  125,  126,   60,
   -1,   62,   -1,   91,   -1,   93,   94,   37,   38,   -1,
   -1,   -1,   42,   43,   -1,   45,   -1,   47,   37,   38,
   -1,   -1,   41,   42,   43,   -1,   45,   -1,   47,   -1,
   60,   -1,   62,   94,   -1,  123,  124,  125,  126,   -1,
   -1,   60,   -1,   62,   37,   38,   -1,   -1,   -1,   42,
   43,   37,   45,   -1,   47,   -1,   42,   43,   -1,   45,
   -1,   47,   -1,  124,   94,   -1,   -1,   60,   -1,   62,
   -1,   -1,   -1,   -1,   60,   94,   62,   -1,   -1,   -1,
   -1,   -1,   -1,   37,   38,   -1,   -1,   -1,   42,   43,
   -1,   45,   38,   47,  124,   41,   -1,   43,   -1,   45,
   -1,   94,   -1,   -1,   -1,  124,   60,   -1,   62,   -1,
   -1,   -1,   -1,   -1,   60,   -1,   62,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   38,   -1,  257,
   41,  124,   43,   -1,   45,   -1,   -1,   -1,   -1,   -1,
   94,   -1,   -1,   -1,   -1,   -1,   -1,  275,   94,   60,
  278,   62,  280,  281,   -1,  283,  284,  285,  286,   -1,
  288,  289,  290,  291,  292,  293,  294,  295,  296,  257,
  124,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  124,   -1,
   -1,   38,   -1,   94,   41,   -1,   -1,  275,   -1,   -1,
  278,   -1,   -1,  281,   -1,  283,  284,  285,  286,   -1,
  288,  289,  290,  291,  292,  293,  294,  295,  296,   -1,
   -1,   -1,   -1,  124,   -1,   -1,   -1,   -1,   -1,  280,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  289,  290,
  291,  292,  293,  294,  295,  296,   -1,   94,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  280,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  289,
  290,  291,  292,  293,  294,  295,  296,  124,   -1,   -1,
  289,  290,  291,  292,  293,  294,  295,  296,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  290,  291,  292,
  293,  294,  295,  296,   -1,  291,  292,  293,  294,  295,
  296,   38,   -1,   -1,   41,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   60,  280,   62,   -1,  291,  292,  293,
  294,  295,  296,  289,  290,  291,  292,  293,  294,  295,
  296,   38,   -1,   -1,   41,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   94,   38,  280,
   -1,   41,   -1,   60,   38,   62,   -1,   41,  289,  290,
  291,  292,  293,  294,  295,  296,   -1,   -1,   -1,   -1,
   60,   38,   62,   -1,   41,   -1,   60,  124,   62,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   94,   -1,   -1,
   -1,   -1,   -1,   60,   -1,   62,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  280,   94,   -1,   -1,   -1,   -1,   -1,
   94,   -1,  289,  290,  291,  292,   -1,  124,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   94,   -1,   -1,
   -1,   -1,   -1,   -1,  124,   -1,   -1,   -1,  260,   -1,
  124,  263,  264,  265,  266,  267,  268,  269,  270,  271,
  272,  273,  274,   -1,   -1,   -1,   -1,  124,  280,   -1,
   -1,   -1,   -1,   -1,   -1,  287,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  280,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  289,  290,  291,  292,  293,  294,  295,  296,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  280,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  289,  290,  291,  292,  293,  294,   -1,   -1,
  280,   -1,   -1,   -1,   -1,   -1,  280,   -1,   -1,  289,
  290,  291,  292,  293,  294,  289,  290,  291,  292,  293,
  294,   -1,   -1,  280,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  289,  290,  291,  292,  293,  294,
};
#if YYBTYACC
static const YYINT glcpp_parser_ctable[] = {             -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,
};
#endif
#define YYFINAL 1
#ifndef YYDEBUG
#define YYDEBUG 1
#endif
#define YYMAXTOKEN 297
#define YYUNDFTOKEN 318
#define YYTRANSLATE(a) ((a) > YYMAXTOKEN ? YYUNDFTOKEN : (a))
#if YYDEBUG
#ifndef NULL
#define NULL (void*)0
#endif
static const char *const glcpp_parser_name[] = {

"$end",NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,
NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,
NULL,NULL,"'!'",NULL,NULL,NULL,"'%'","'&'",NULL,"'('","')'","'*'","'+'","','",
"'-'","'.'","'/'",NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"';'",
"'<'","'='","'>'",NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,
NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,
"'['",NULL,"']'","'^'",NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,
NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,
NULL,"'{'","'|'","'}'","'~'",NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,
NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,
NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,
NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,
NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,
NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,
NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,
NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,
NULL,NULL,NULL,NULL,NULL,NULL,NULL,"error","DEFINED","ELIF_EXPANDED",
"HASH_TOKEN","DEFINE_TOKEN","FUNC_IDENTIFIER","OBJ_IDENTIFIER","ELIF","ELSE",
"ENDIF","ERROR_TOKEN","IF","IFDEF","IFNDEF","LINE","PRAGMA","UNDEF",
"VERSION_TOKEN","GARBAGE","IDENTIFIER","IF_EXPANDED","INTEGER","INTEGER_STRING",
"LINE_EXPANDED","NEWLINE","OTHER","PLACEHOLDER","SPACE","PLUS_PLUS",
"MINUS_MINUS","PATH","INCLUDE","PASTE","OR","AND","EQUAL","NOT_EQUAL",
"LESS_OR_EQUAL","GREATER_OR_EQUAL","LEFT_SHIFT","RIGHT_SHIFT","UNARY","$accept",
"input","operator","integer_constant","version_constant","expression",
"identifier_list","preprocessing_token","pp_tokens","replacement_list",
"text_line","line","control_line","expanded_line","define",
"control_line_success","control_line_error","junk","$$1","$$2","illegal-symbol",
};
static const char *const glcpp_parser_rule[] = {
"$accept : input",
"input :",
"input : input line",
"line : control_line",
"line : SPACE control_line",
"line : text_line",
"line : expanded_line",
"expanded_line : IF_EXPANDED expression NEWLINE",
"expanded_line : ELIF_EXPANDED expression NEWLINE",
"expanded_line : LINE_EXPANDED integer_constant NEWLINE",
"expanded_line : LINE_EXPANDED integer_constant integer_constant NEWLINE",
"expanded_line : LINE_EXPANDED integer_constant PATH NEWLINE",
"define : OBJ_IDENTIFIER replacement_list NEWLINE",
"define : FUNC_IDENTIFIER '(' ')' replacement_list NEWLINE",
"define : FUNC_IDENTIFIER '(' identifier_list ')' replacement_list NEWLINE",
"control_line : control_line_success",
"control_line : control_line_error",
"control_line : HASH_TOKEN LINE pp_tokens NEWLINE",
"control_line_success : HASH_TOKEN DEFINE_TOKEN define",
"control_line_success : HASH_TOKEN UNDEF IDENTIFIER NEWLINE",
"control_line_success : HASH_TOKEN INCLUDE NEWLINE",
"control_line_success : HASH_TOKEN IF pp_tokens NEWLINE",
"control_line_success : HASH_TOKEN IF NEWLINE",
"control_line_success : HASH_TOKEN IFDEF IDENTIFIER junk NEWLINE",
"control_line_success : HASH_TOKEN IFNDEF IDENTIFIER junk NEWLINE",
"control_line_success : HASH_TOKEN ELIF pp_tokens NEWLINE",
"control_line_success : HASH_TOKEN ELIF NEWLINE",
"$$1 :",
"control_line_success : HASH_TOKEN ELSE $$1 NEWLINE",
"$$2 :",
"control_line_success : HASH_TOKEN ENDIF $$2 NEWLINE",
"control_line_success : HASH_TOKEN VERSION_TOKEN version_constant NEWLINE",
"control_line_success : HASH_TOKEN VERSION_TOKEN version_constant IDENTIFIER NEWLINE",
"control_line_success : HASH_TOKEN NEWLINE",
"control_line_success : HASH_TOKEN PRAGMA NEWLINE",
"control_line_error : HASH_TOKEN ERROR_TOKEN NEWLINE",
"control_line_error : HASH_TOKEN DEFINE_TOKEN NEWLINE",
"control_line_error : HASH_TOKEN GARBAGE pp_tokens NEWLINE",
"integer_constant : INTEGER_STRING",
"integer_constant : INTEGER",
"version_constant : INTEGER_STRING",
"expression : integer_constant",
"expression : IDENTIFIER",
"expression : expression OR expression",
"expression : expression AND expression",
"expression : expression '|' expression",
"expression : expression '^' expression",
"expression : expression '&' expression",
"expression : expression NOT_EQUAL expression",
"expression : expression EQUAL expression",
"expression : expression GREATER_OR_EQUAL expression",
"expression : expression LESS_OR_EQUAL expression",
"expression : expression '>' expression",
"expression : expression '<' expression",
"expression : expression RIGHT_SHIFT expression",
"expression : expression LEFT_SHIFT expression",
"expression : expression '-' expression",
"expression : expression '+' expression",
"expression : expression '%' expression",
"expression : expression '/' expression",
"expression : expression '*' expression",
"expression : '!' expression",
"expression : '~' expression",
"expression : '-' expression",
"expression : '+' expression",
"expression : '(' expression ')'",
"identifier_list : IDENTIFIER",
"identifier_list : identifier_list ',' IDENTIFIER",
"text_line : NEWLINE",
"text_line : pp_tokens NEWLINE",
"replacement_list :",
"replacement_list : pp_tokens",
"junk :",
"junk : pp_tokens",
"pp_tokens : preprocessing_token",
"pp_tokens : pp_tokens preprocessing_token",
"preprocessing_token : IDENTIFIER",
"preprocessing_token : INTEGER_STRING",
"preprocessing_token : PATH",
"preprocessing_token : operator",
"preprocessing_token : DEFINED",
"preprocessing_token : OTHER",
"preprocessing_token : SPACE",
"operator : '['",
"operator : ']'",
"operator : '('",
"operator : ')'",
"operator : '{'",
"operator : '}'",
"operator : '.'",
"operator : '&'",
"operator : '*'",
"operator : '+'",
"operator : '-'",
"operator : '~'",
"operator : '!'",
"operator : '/'",
"operator : '%'",
"operator : LEFT_SHIFT",
"operator : RIGHT_SHIFT",
"operator : '<'",
"operator : '>'",
"operator : LESS_OR_EQUAL",
"operator : GREATER_OR_EQUAL",
"operator : EQUAL",
"operator : NOT_EQUAL",
"operator : '^'",
"operator : '|'",
"operator : AND",
"operator : OR",
"operator : ';'",
"operator : ','",
"operator : '='",
"operator : PASTE",
"operator : PLUS_PLUS",
"operator : MINUS_MINUS",

};
#endif

#if YYDEBUG
int      yydebug;
#endif

#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
#ifndef YYLLOC_DEFAULT
#define YYLLOC_DEFAULT(loc, rhs, n) \
do \
{ \
    if (n == 0) \
    { \
        (loc).first_line   = YYRHSLOC(rhs, 0).last_line; \
        (loc).first_column = YYRHSLOC(rhs, 0).last_column; \
        (loc).last_line    = YYRHSLOC(rhs, 0).last_line; \
        (loc).last_column  = YYRHSLOC(rhs, 0).last_column; \
    } \
    else \
    { \
        (loc).first_line   = YYRHSLOC(rhs, 1).first_line; \
        (loc).first_column = YYRHSLOC(rhs, 1).first_column; \
        (loc).last_line    = YYRHSLOC(rhs, n).last_line; \
        (loc).last_column  = YYRHSLOC(rhs, n).last_column; \
    } \
} while (0)
#endif /* YYLLOC_DEFAULT */
#endif /* defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED) */
#if YYBTYACC

#ifndef YYLVQUEUEGROWTH
#define YYLVQUEUEGROWTH 32
#endif
#endif /* YYBTYACC */

/* define the initial stack-sizes */
#ifdef YYSTACKSIZE
#undef YYMAXDEPTH
#define YYMAXDEPTH  YYSTACKSIZE
#else
#ifdef YYMAXDEPTH
#define YYSTACKSIZE YYMAXDEPTH
#else
#define YYSTACKSIZE 10000
#define YYMAXDEPTH  10000
#endif
#endif

#ifndef YYINITSTACKSIZE
#define YYINITSTACKSIZE 200
#endif

typedef struct {
    unsigned stacksize;
    YYINT    *s_base;
    YYINT    *s_mark;
    YYINT    *s_last;
    YYSTYPE  *l_base;
    YYSTYPE  *l_mark;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
    YYLTYPE  *p_base;
    YYLTYPE  *p_mark;
#endif
} YYSTACKDATA;
#if YYBTYACC

struct YYParseState_s
{
    struct YYParseState_s *save;    /* Previously saved parser state */
    YYSTACKDATA            yystack; /* saved parser stack */
    int                    state;   /* saved parser state */
    int                    errflag; /* saved error recovery status */
    int                    lexeme;  /* saved index of the conflict lexeme in the lexical queue */
    YYINT                  ctry;    /* saved index in yyctable[] for this conflict */
};
typedef struct YYParseState_s YYParseState;
#endif /* YYBTYACC */
#line 871 "../mesa/src/compiler/glsl/glcpp/glcpp-parse.y"

string_list_t *
_string_list_create(glcpp_parser_t *parser)
{
   string_list_t *list;

   list = linear_alloc_child(parser->linalloc, sizeof(string_list_t));
   list->head = NULL;
   list->tail = NULL;

   return list;
}

void
_string_list_append_item(glcpp_parser_t *parser, string_list_t *list,
                         const char *str)
{
   string_node_t *node;

   node = linear_alloc_child(parser->linalloc, sizeof(string_node_t));
   node->str = linear_strdup(parser->linalloc, str);

   node->next = NULL;

   if (list->head == NULL) {
      list->head = node;
   } else {
      list->tail->next = node;
   }

   list->tail = node;
}

int
_string_list_contains(string_list_t *list, const char *member, int *index)
{
   string_node_t *node;
   int i;

   if (list == NULL)
      return 0;

   for (i = 0, node = list->head; node; i++, node = node->next) {
      if (strcmp (node->str, member) == 0) {
         if (index)
            *index = i;
         return 1;
      }
   }

   return 0;
}

/* Return duplicate string in list (if any), NULL otherwise. */
const char *
_string_list_has_duplicate(string_list_t *list)
{
   string_node_t *node, *dup;

   if (list == NULL)
      return NULL;

   for (node = list->head; node; node = node->next) {
      for (dup = node->next; dup; dup = dup->next) {
         if (strcmp (node->str, dup->str) == 0)
            return node->str;
      }
   }

   return NULL;
}

int
_string_list_length(string_list_t *list)
{
   int length = 0;
   string_node_t *node;

   if (list == NULL)
      return 0;

   for (node = list->head; node; node = node->next)
      length++;

   return length;
}

int
_string_list_equal(string_list_t *a, string_list_t *b)
{
   string_node_t *node_a, *node_b;

   if (a == NULL && b == NULL)
      return 1;

   if (a == NULL || b == NULL)
      return 0;

   for (node_a = a->head, node_b = b->head;
        node_a && node_b;
        node_a = node_a->next, node_b = node_b->next)
   {
      if (strcmp (node_a->str, node_b->str))
         return 0;
   }

   /* Catch the case of lists being different lengths, (which
    * would cause the loop above to terminate after the shorter
    * list). */
   return node_a == node_b;
}

argument_list_t *
_argument_list_create(glcpp_parser_t *parser)
{
   argument_list_t *list;

   list = linear_alloc_child(parser->linalloc, sizeof(argument_list_t));
   list->head = NULL;
   list->tail = NULL;

   return list;
}

void
_argument_list_append(glcpp_parser_t *parser,
                      argument_list_t *list, token_list_t *argument)
{
   argument_node_t *node;

   node = linear_alloc_child(parser->linalloc, sizeof(argument_node_t));
   node->argument = argument;

   node->next = NULL;

   if (list->head == NULL) {
      list->head = node;
   } else {
      list->tail->next = node;
   }

   list->tail = node;
}

int
_argument_list_length(argument_list_t *list)
{
   int length = 0;
   argument_node_t *node;

   if (list == NULL)
      return 0;

   for (node = list->head; node; node = node->next)
      length++;

   return length;
}

token_list_t *
_argument_list_member_at(argument_list_t *list, int index)
{
   argument_node_t *node;
   int i;

   if (list == NULL)
      return NULL;

   node = list->head;
   for (i = 0; i < index; i++) {
      node = node->next;
      if (node == NULL)
         break;
   }

   if (node)
      return node->argument;

   return NULL;
}

token_t *
_token_create_str(glcpp_parser_t *parser, int type, char *str)
{
   token_t *token;

   token = linear_alloc_child(parser->linalloc, sizeof(token_t));
   token->type = type;
   token->value.str = str;
   token->expanding = false;

   return token;
}

token_t *
_token_create_ival(glcpp_parser_t *parser, int type, int ival)
{
   token_t *token;

   token = linear_alloc_child(parser->linalloc, sizeof(token_t));
   token->type = type;
   token->value.ival = ival;
   token->expanding = false;

   return token;
}

token_list_t *
_token_list_create(glcpp_parser_t *parser)
{
   token_list_t *list;

   list = linear_alloc_child(parser->linalloc, sizeof(token_list_t));
   list->head = NULL;
   list->tail = NULL;
   list->non_space_tail = NULL;

   return list;
}

void
_token_list_append(glcpp_parser_t *parser, token_list_t *list, token_t *token)
{
   token_node_t *node;

   node = linear_alloc_child(parser->linalloc, sizeof(token_node_t));
   node->token = token;
   node->next = NULL;

   if (list->head == NULL) {
      list->head = node;
   } else {
      list->tail->next = node;
   }

   list->tail = node;
   if (token->type != SPACE)
      list->non_space_tail = node;
}

void
_token_list_append_list(token_list_t *list, token_list_t *tail)
{
   if (tail == NULL || tail->head == NULL)
      return;

   if (list->head == NULL) {
      list->head = tail->head;
   } else {
      list->tail->next = tail->head;
   }

   list->tail = tail->tail;
   list->non_space_tail = tail->non_space_tail;
}

static token_list_t *
_token_list_copy(glcpp_parser_t *parser, token_list_t *other)
{
   token_list_t *copy;
   token_node_t *node;

   if (other == NULL)
      return NULL;

   copy = _token_list_create (parser);
   for (node = other->head; node; node = node->next) {
      token_t *new_token = linear_alloc_child(parser->linalloc, sizeof(token_t));
      *new_token = *node->token;
      _token_list_append (parser, copy, new_token);
   }

   return copy;
}

static void
_token_list_trim_trailing_space(token_list_t *list)
{
   if (list->non_space_tail) {
      list->non_space_tail->next = NULL;
      list->tail = list->non_space_tail;
   }
}

static int
_token_list_is_empty_ignoring_space(token_list_t *l)
{
   token_node_t *n;

   if (l == NULL)
      return 1;

   n = l->head;
   while (n != NULL && n->token->type == SPACE)
      n = n->next;

   return n == NULL;
}

int
_token_list_equal_ignoring_space(token_list_t *a, token_list_t *b)
{
   token_node_t *node_a, *node_b;

   if (a == NULL || b == NULL) {
      int a_empty = _token_list_is_empty_ignoring_space(a);
      int b_empty = _token_list_is_empty_ignoring_space(b);
      return a_empty == b_empty;
   }

   node_a = a->head;
   node_b = b->head;

   while (1)
   {
      if (node_a == NULL && node_b == NULL)
         break;

      /* Ignore trailing whitespace */
      if (node_a == NULL && node_b->token->type == SPACE) {
         while (node_b && node_b->token->type == SPACE)
            node_b = node_b->next;
      }

      if (node_a == NULL && node_b == NULL)
         break;

      if (node_b == NULL && node_a->token->type == SPACE) {
         while (node_a && node_a->token->type == SPACE)
            node_a = node_a->next;
      }

      if (node_a == NULL && node_b == NULL)
         break;

      if (node_a == NULL || node_b == NULL)
         return 0;
      /* Make sure whitespace appears in the same places in both.
       * It need not be exactly the same amount of whitespace,
       * though.
       */
      if (node_a->token->type == SPACE && node_b->token->type == SPACE) {
         while (node_a && node_a->token->type == SPACE)
            node_a = node_a->next;
         while (node_b && node_b->token->type == SPACE)
            node_b = node_b->next;
         continue;
      }

      if (node_a->token->type != node_b->token->type)
         return 0;

      switch (node_a->token->type) {
      case INTEGER:
         if (node_a->token->value.ival !=  node_b->token->value.ival) {
            return 0;
         }
         break;
      case IDENTIFIER:
      case INTEGER_STRING:
      case OTHER:
         if (strcmp(node_a->token->value.str, node_b->token->value.str)) {
            return 0;
         }
         break;
      }

      node_a = node_a->next;
      node_b = node_b->next;
   }

   return 1;
}

static void
_token_print(struct _mesa_string_buffer *out, token_t *token)
{
   if (token->type < 256) {
      _mesa_string_buffer_append_char(out, token->type);
      return;
   }

   switch (token->type) {
   case INTEGER:
      _mesa_string_buffer_printf(out, "%" PRIiMAX, token->value.ival);
      break;
   case IDENTIFIER:
   case INTEGER_STRING:
   case PATH:
   case OTHER:
      _mesa_string_buffer_append(out, token->value.str);
      break;
   case SPACE:
      _mesa_string_buffer_append_char(out, ' ');
      break;
   case LEFT_SHIFT:
      _mesa_string_buffer_append(out, "<<");
      break;
   case RIGHT_SHIFT:
      _mesa_string_buffer_append(out, ">>");
      break;
   case LESS_OR_EQUAL:
      _mesa_string_buffer_append(out, "<=");
      break;
   case GREATER_OR_EQUAL:
      _mesa_string_buffer_append(out, ">=");
      break;
   case EQUAL:
      _mesa_string_buffer_append(out, "==");
      break;
   case NOT_EQUAL:
      _mesa_string_buffer_append(out, "!=");
      break;
   case AND:
      _mesa_string_buffer_append(out, "&&");
      break;
   case OR:
      _mesa_string_buffer_append(out, "||");
      break;
   case PASTE:
      _mesa_string_buffer_append(out, "##");
      break;
   case PLUS_PLUS:
      _mesa_string_buffer_append(out, "++");
      break;
   case MINUS_MINUS:
      _mesa_string_buffer_append(out, "--");
      break;
   case DEFINED:
      _mesa_string_buffer_append(out, "defined");
      break;
   case PLACEHOLDER:
      /* Nothing to print. */
      break;
   default:
      assert(!"Error: Don't know how to print token.");

      break;
   }
}

/* Return a new token formed by pasting 'token' and 'other'. Note that this
 * function may return 'token' or 'other' directly rather than allocating
 * anything new.
 *
 * Caution: Only very cursory error-checking is performed to see if
 * the final result is a valid single token. */
static token_t *
_token_paste(glcpp_parser_t *parser, token_t *token, token_t *other)
{
   token_t *combined = NULL;

   /* Pasting a placeholder onto anything makes no change. */
   if (other->type == PLACEHOLDER)
      return token;

   /* When 'token' is a placeholder, just return 'other'. */
   if (token->type == PLACEHOLDER)
      return other;

   /* A very few single-character punctuators can be combined
    * with another to form a multi-character punctuator. */
   switch (token->type) {
   case '<':
      if (other->type == '<')
         combined = _token_create_ival (parser, LEFT_SHIFT, LEFT_SHIFT);
      else if (other->type == '=')
         combined = _token_create_ival (parser, LESS_OR_EQUAL, LESS_OR_EQUAL);
      break;
   case '>':
      if (other->type == '>')
         combined = _token_create_ival (parser, RIGHT_SHIFT, RIGHT_SHIFT);
      else if (other->type == '=')
         combined = _token_create_ival (parser, GREATER_OR_EQUAL, GREATER_OR_EQUAL);
      break;
   case '=':
      if (other->type == '=')
         combined = _token_create_ival (parser, EQUAL, EQUAL);
      break;
   case '!':
      if (other->type == '=')
         combined = _token_create_ival (parser, NOT_EQUAL, NOT_EQUAL);
      break;
   case '&':
      if (other->type == '&')
         combined = _token_create_ival (parser, AND, AND);
      break;
   case '|':
      if (other->type == '|')
         combined = _token_create_ival (parser, OR, OR);
      break;
   }

   if (combined != NULL) {
      /* Inherit the location from the first token */
      combined->location = token->location;
      return combined;
   }

   /* Two string-valued (or integer) tokens can usually just be
    * mashed together. (We also handle a string followed by an
    * integer here as well.)
    *
    * There are some exceptions here. Notably, if the first token
    * is an integer (or a string representing an integer), then
    * the second token must also be an integer or must be a
    * string representing an integer that begins with a digit.
    */
   if ((token->type == IDENTIFIER || token->type == OTHER || token->type == INTEGER_STRING || token->type == INTEGER) &&
       (other->type == IDENTIFIER || other->type == OTHER || other->type == INTEGER_STRING || other->type == INTEGER))
   {
      char *str;
      int combined_type;

      /* Check that pasting onto an integer doesn't create a
       * non-integer, (that is, only digits can be
       * pasted. */
      if (token->type == INTEGER_STRING || token->type == INTEGER) {
         switch (other->type) {
         case INTEGER_STRING:
            if (other->value.str[0] < '0' || other->value.str[0] > '9')
               goto FAIL;
            break;
         case INTEGER:
            if (other->value.ival < 0)
               goto FAIL;
            break;
         default:
            goto FAIL;
         }
      }

      if (token->type == INTEGER)
         str = linear_asprintf(parser->linalloc, "%" PRIiMAX, token->value.ival);
      else
         str = linear_strdup(parser->linalloc, token->value.str);

      if (other->type == INTEGER)
         linear_asprintf_append(parser->linalloc, &str, "%" PRIiMAX, other->value.ival);
      else
         linear_strcat(parser->linalloc, &str, other->value.str);

      /* New token is same type as original token, unless we
       * started with an integer, in which case we will be
       * creating an integer-string. */
      combined_type = token->type;
      if (combined_type == INTEGER)
         combined_type = INTEGER_STRING;

      combined = _token_create_str (parser, combined_type, str);
      combined->location = token->location;
      return combined;
   }

    FAIL:
   glcpp_error (&token->location, parser, "");
   _mesa_string_buffer_append(parser->info_log, "Pasting \"");
   _token_print(parser->info_log, token);
   _mesa_string_buffer_append(parser->info_log, "\" and \"");
   _token_print(parser->info_log, other);
   _mesa_string_buffer_append(parser->info_log, "\" does not give a valid preprocessing token.\n");

   return token;
}

static void
_token_list_print(glcpp_parser_t *parser, token_list_t *list)
{
   token_node_t *node;

   if (list == NULL)
      return;

   for (node = list->head; node; node = node->next)
      _token_print(parser->output, node->token);
}

void
yyerror(YYLTYPE *locp, glcpp_parser_t *parser, const char *error)
{
   glcpp_error(locp, parser, "%s", error);
}

static void
add_builtin_define(glcpp_parser_t *parser, const char *name, int value)
{
   token_t *tok;
   token_list_t *list;

   tok = _token_create_ival (parser, INTEGER, value);

   list = _token_list_create(parser);
   _token_list_append(parser, list, tok);
   _define_object_macro(parser, NULL, name, list);
}

/* Initial output buffer size, 4096 minus ralloc() overhead. It was selected
 * to minimize total amount of allocated memory during shader-db run.
 */
#define INITIAL_PP_OUTPUT_BUF_SIZE 4048

glcpp_parser_t *
glcpp_parser_create(struct gl_context *gl_ctx,
                    glcpp_extension_iterator extensions, void *state)
{
   glcpp_parser_t *parser;

   parser = ralloc (NULL, glcpp_parser_t);

   glcpp_lex_init_extra (parser, &parser->scanner);
   parser->defines = _mesa_hash_table_create(NULL, _mesa_hash_string,
                                             _mesa_key_string_equal);
   parser->linalloc = linear_alloc_parent(parser, 0);
   parser->active = NULL;
   parser->lexing_directive = 0;
   parser->lexing_version_directive = 0;
   parser->space_tokens = 1;
   parser->last_token_was_newline = 0;
   parser->last_token_was_space = 0;
   parser->first_non_space_token_this_line = 1;
   parser->newline_as_space = 0;
   parser->in_control_line = 0;
   parser->paren_count = 0;
   parser->commented_newlines = 0;

   parser->skip_stack = NULL;
   parser->skipping = 0;

   parser->lex_from_list = NULL;
   parser->lex_from_node = NULL;

   parser->output = _mesa_string_buffer_create(parser,
                                               INITIAL_PP_OUTPUT_BUF_SIZE);
   parser->info_log = _mesa_string_buffer_create(parser,
                                                 INITIAL_PP_OUTPUT_BUF_SIZE);
   parser->error = 0;

   parser->gl_ctx = gl_ctx;
   parser->extensions = extensions;
   parser->extension_list = &gl_ctx->Extensions;
   parser->state = state;
   parser->api = gl_ctx->API;
   parser->version = 0;
   parser->version_set = false;

   parser->has_new_line_number = 0;
   parser->new_line_number = 1;
   parser->has_new_source_number = 0;
   parser->new_source_number = 0;

   parser->is_gles = false;

   return parser;
}

void
glcpp_parser_destroy(glcpp_parser_t *parser)
{
   glcpp_lex_destroy (parser->scanner);
   _mesa_hash_table_destroy(parser->defines, NULL);
   ralloc_free (parser);
}

typedef enum function_status
{
   FUNCTION_STATUS_SUCCESS,
   FUNCTION_NOT_A_FUNCTION,
   FUNCTION_UNBALANCED_PARENTHESES
} function_status_t;

/* Find a set of function-like macro arguments by looking for a
 * balanced set of parentheses.
 *
 * When called, 'node' should be the opening-parenthesis token, (or
 * perhaps preceeding SPACE tokens). Upon successful return *last will
 * be the last consumed node, (corresponding to the closing right
 * parenthesis).
 *
 * Return values:
 *
 *   FUNCTION_STATUS_SUCCESS:
 *
 *      Successfully parsed a set of function arguments.
 *
 *   FUNCTION_NOT_A_FUNCTION:
 *
 *      Macro name not followed by a '('. This is not an error, but
 *      simply that the macro name should be treated as a non-macro.
 *
 *   FUNCTION_UNBALANCED_PARENTHESES
 *
 *      Macro name is not followed by a balanced set of parentheses.
 */
static function_status_t
_arguments_parse(glcpp_parser_t *parser,
                 argument_list_t *arguments, token_node_t *node,
                 token_node_t **last)
{
   token_list_t *argument;
   int paren_count;

   node = node->next;

   /* Ignore whitespace before first parenthesis. */
   while (node && node->token->type == SPACE)
      node = node->next;

   if (node == NULL || node->token->type != '(')
      return FUNCTION_NOT_A_FUNCTION;

   node = node->next;

   argument = _token_list_create (parser);
   _argument_list_append (parser, arguments, argument);

   for (paren_count = 1; node; node = node->next) {
      if (node->token->type == '(') {
         paren_count++;
      } else if (node->token->type == ')') {
         paren_count--;
         if (paren_count == 0)
            break;
      }

      if (node->token->type == ',' && paren_count == 1) {
         _token_list_trim_trailing_space (argument);
         argument = _token_list_create (parser);
         _argument_list_append (parser, arguments, argument);
      } else {
         if (argument->head == NULL) {
            /* Don't treat initial whitespace as part of the argument. */
            if (node->token->type == SPACE)
               continue;
         }
         _token_list_append(parser, argument, node->token);
      }
   }

   if (paren_count)
      return FUNCTION_UNBALANCED_PARENTHESES;

   *last = node;

   return FUNCTION_STATUS_SUCCESS;
}

static token_list_t *
_token_list_create_with_one_ival(glcpp_parser_t *parser, int type, int ival)
{
   token_list_t *list;
   token_t *node;

   list = _token_list_create(parser);
   node = _token_create_ival(parser, type, ival);
   _token_list_append(parser, list, node);

   return list;
}

static token_list_t *
_token_list_create_with_one_space(glcpp_parser_t *parser)
{
   return _token_list_create_with_one_ival(parser, SPACE, SPACE);
}

static token_list_t *
_token_list_create_with_one_integer(glcpp_parser_t *parser, int ival)
{
   return _token_list_create_with_one_ival(parser, INTEGER, ival);
}

/* Evaluate a DEFINED token node (based on subsequent tokens in the list).
 *
 * Note: This function must only be called when "node" is a DEFINED token,
 * (and will abort with an assertion failure otherwise).
 *
 * If "node" is followed, (ignoring any SPACE tokens), by an IDENTIFIER token
 * (optionally preceded and followed by '(' and ')' tokens) then the following
 * occurs:
 *
 *   If the identifier is a defined macro, this function returns 1.
 *
 *   If the identifier is not a defined macro, this function returns 0.
 *
 *   In either case, *last will be updated to the last node in the list
 *   consumed by the evaluation, (either the token of the identifier or the
 *   token of the closing parenthesis).
 *
 * In all other cases, (such as "node is the final node of the list", or
 * "missing closing parenthesis", etc.), this function generates a
 * preprocessor error, returns -1 and *last will not be set.
 */
static int
_glcpp_parser_evaluate_defined(glcpp_parser_t *parser, token_node_t *node,
                               token_node_t **last)
{
   token_node_t *argument, *defined = node;

   assert(node->token->type == DEFINED);

   node = node->next;

   /* Ignore whitespace after DEFINED token. */
   while (node && node->token->type == SPACE)
      node = node->next;

   if (node == NULL)
      goto FAIL;

   if (node->token->type == IDENTIFIER || node->token->type == OTHER) {
      argument = node;
   } else if (node->token->type == '(') {
      node = node->next;

      /* Ignore whitespace after '(' token. */
      while (node && node->token->type == SPACE)
         node = node->next;

      if (node == NULL || (node->token->type != IDENTIFIER &&
                           node->token->type != OTHER)) {
         goto FAIL;
      }

      argument = node;

      node = node->next;

      /* Ignore whitespace after identifier, before ')' token. */
      while (node && node->token->type == SPACE)
         node = node->next;

      if (node == NULL || node->token->type != ')')
         goto FAIL;
   } else {
      goto FAIL;
   }

   *last = node;

   return _mesa_hash_table_search(parser->defines,
                                  argument->token->value.str) ? 1 : 0;

FAIL:
   glcpp_error (&defined->token->location, parser,
                "\"defined\" not followed by an identifier");
   return -1;
}

/* Evaluate all DEFINED nodes in a given list, modifying the list in place.
 */
static void
_glcpp_parser_evaluate_defined_in_list(glcpp_parser_t *parser,
                                       token_list_t *list)
{
   token_node_t *node, *node_prev, *replacement, *last = NULL;
   int value;

   if (list == NULL)
      return;

   node_prev = NULL;
   node = list->head;

   while (node) {

      if (node->token->type != DEFINED)
         goto NEXT;

      value = _glcpp_parser_evaluate_defined (parser, node, &last);
      if (value == -1)
         goto NEXT;

      replacement = linear_alloc_child(parser->linalloc, sizeof(token_node_t));
      replacement->token = _token_create_ival (parser, INTEGER, value);

      /* Splice replacement node into list, replacing from "node"
       * through "last". */
      if (node_prev)
         node_prev->next = replacement;
      else
         list->head = replacement;
      replacement->next = last->next;
      if (last == list->tail)
         list->tail = replacement;

      node = replacement;

   NEXT:
      node_prev = node;
      node = node->next;
   }
}

/* Perform macro expansion on 'list', placing the resulting tokens
 * into a new list which is initialized with a first token of type
 * 'head_token_type'. Then begin lexing from the resulting list,
 * (return to the current lexing source when this list is exhausted).
 *
 * See the documentation of _glcpp_parser_expand_token_list for a description
 * of the "mode" parameter.
 */
static void
_glcpp_parser_expand_and_lex_from(glcpp_parser_t *parser, int head_token_type,
                                  token_list_t *list, expansion_mode_t mode)
{
   token_list_t *expanded;
   token_t *token;

   expanded = _token_list_create (parser);
   token = _token_create_ival (parser, head_token_type, head_token_type);
   _token_list_append (parser, expanded, token);
   _glcpp_parser_expand_token_list (parser, list, mode);
   _token_list_append_list (expanded, list);
   glcpp_parser_lex_from (parser, expanded);
}

static void
_glcpp_parser_apply_pastes(glcpp_parser_t *parser, token_list_t *list)
{
   token_node_t *node;

   node = list->head;
   while (node) {
      token_node_t *next_non_space;

      /* Look ahead for a PASTE token, skipping space. */
      next_non_space = node->next;
      while (next_non_space && next_non_space->token->type == SPACE)
         next_non_space = next_non_space->next;

      if (next_non_space == NULL)
         break;

      if (next_non_space->token->type != PASTE) {
         node = next_non_space;
         continue;
      }

      /* Now find the next non-space token after the PASTE. */
      next_non_space = next_non_space->next;
      while (next_non_space && next_non_space->token->type == SPACE)
         next_non_space = next_non_space->next;

      if (next_non_space == NULL) {
         yyerror(&node->token->location, parser, "'##' cannot appear at either end of a macro expansion\n");
         return;
      }

      node->token = _token_paste(parser, node->token, next_non_space->token);
      node->next = next_non_space->next;
      if (next_non_space == list->tail)
         list->tail = node;
   }

   list->non_space_tail = list->tail;
}

/* This is a helper function that's essentially part of the
 * implementation of _glcpp_parser_expand_node. It shouldn't be called
 * except for by that function.
 *
 * Returns NULL if node is a simple token with no expansion, (that is,
 * although 'node' corresponds to an identifier defined as a
 * function-like macro, it is not followed with a parenthesized
 * argument list).
 *
 * Compute the complete expansion of node (which is a function-like
 * macro) and subsequent nodes which are arguments.
 *
 * Returns the token list that results from the expansion and sets
 * *last to the last node in the list that was consumed by the
 * expansion. Specifically, *last will be set as follows: as the
 * token of the closing right parenthesis.
 *
 * See the documentation of _glcpp_parser_expand_token_list for a description
 * of the "mode" parameter.
 */
static token_list_t *
_glcpp_parser_expand_function(glcpp_parser_t *parser, token_node_t *node,
                              token_node_t **last, expansion_mode_t mode)
{
   struct hash_entry *entry;
   macro_t *macro;
   const char *identifier;
   argument_list_t *arguments;
   function_status_t status;
   token_list_t *substituted;
   int parameter_index;

   identifier = node->token->value.str;

   entry = _mesa_hash_table_search(parser->defines, identifier);
   macro = entry ? entry->data : NULL;

   assert(macro->is_function);

   arguments = _argument_list_create(parser);
   status = _arguments_parse(parser, arguments, node, last);

   switch (status) {
   case FUNCTION_STATUS_SUCCESS:
      break;
   case FUNCTION_NOT_A_FUNCTION:
      return NULL;
   case FUNCTION_UNBALANCED_PARENTHESES:
      glcpp_error(&node->token->location, parser, "Macro %s call has unbalanced parentheses\n", identifier);
      return NULL;
   }

   /* Replace a macro defined as empty with a SPACE token. */
   if (macro->replacements == NULL) {
      return _token_list_create_with_one_space(parser);
   }

   if (!((_argument_list_length (arguments) ==
          _string_list_length (macro->parameters)) ||
         (_string_list_length (macro->parameters) == 0 &&
          _argument_list_length (arguments) == 1 &&
          arguments->head->argument->head == NULL))) {
      glcpp_error(&node->token->location, parser,
                  "Error: macro %s invoked with %d arguments (expected %d)\n",
                  identifier, _argument_list_length (arguments),
                  _string_list_length(macro->parameters));
      return NULL;
   }

   /* Perform argument substitution on the replacement list. */
   substituted = _token_list_create(parser);

   for (node = macro->replacements->head; node; node = node->next) {
      if (node->token->type == IDENTIFIER &&
          _string_list_contains(macro->parameters, node->token->value.str,
                                &parameter_index)) {
         token_list_t *argument;
         argument = _argument_list_member_at(arguments, parameter_index);
         /* Before substituting, we expand the argument tokens, or append a
          * placeholder token for an empty argument. */
         if (argument->head) {
            token_list_t *expanded_argument;
            expanded_argument = _token_list_copy(parser, argument);
            _glcpp_parser_expand_token_list(parser, expanded_argument, mode);
            _token_list_append_list(substituted, expanded_argument);
         } else {
            token_t *new_token;

            new_token = _token_create_ival(parser, PLACEHOLDER,
                                           PLACEHOLDER);
            _token_list_append(parser, substituted, new_token);
         }
      } else {
         _token_list_append(parser, substituted, node->token);
      }
   }

   /* After argument substitution, and before further expansion
    * below, implement token pasting. */

   _token_list_trim_trailing_space(substituted);

   _glcpp_parser_apply_pastes(parser, substituted);

   return substituted;
}

/* Compute the complete expansion of node, (and subsequent nodes after
 * 'node' in the case that 'node' is a function-like macro and
 * subsequent nodes are arguments).
 *
 * Returns NULL if node is a simple token with no expansion.
 *
 * Otherwise, returns the token list that results from the expansion
 * and sets *last to the last node in the list that was consumed by
 * the expansion. Specifically, *last will be set as follows:
 *
 *   As 'node' in the case of object-like macro expansion.
 *
 *   As the token of the closing right parenthesis in the case of
 *   function-like macro expansion.
 *
 * See the documentation of _glcpp_parser_expand_token_list for a description
 * of the "mode" parameter.
 */
static token_list_t *
_glcpp_parser_expand_node(glcpp_parser_t *parser, token_node_t *node,
                          token_node_t **last, expansion_mode_t mode,
                          int line)
{
   token_t *token = node->token;
   const char *identifier;
   struct hash_entry *entry;
   macro_t *macro;

   /* If token is already being expanded return to avoid an infinite loop */
   if (token->expanding)
      return NULL;

   /* We only expand identifiers */
   if (token->type != IDENTIFIER) {
      return NULL;
   }

   *last = node;
   identifier = token->value.str;

   /* Special handling for __LINE__ and __FILE__, (not through
    * the hash table). */
   if (*identifier == '_') {
      if (strcmp(identifier, "__LINE__") == 0)
         return _token_list_create_with_one_integer(parser, line);

      if (strcmp(identifier, "__FILE__") == 0)
         return _token_list_create_with_one_integer(parser,
                                                    node->token->location.source);
   }

   /* Look up this identifier in the hash table. */
   entry = _mesa_hash_table_search(parser->defines, identifier);
   macro = entry ? entry->data : NULL;

   /* Not a macro, so no expansion needed. */
   if (macro == NULL)
      return NULL;

   /* Finally, don't expand this macro if we're already actively
    * expanding it, (to avoid infinite recursion). */
   if (_parser_active_list_contains (parser, identifier)) {
      /* We change the `expanding` bool to true to prevent any
       * future expansion of this unexpanded token. */
      char *str;
      token_list_t *expansion;
      token_t *final;

      str = linear_strdup(parser->linalloc, token->value.str);
      final = _token_create_str(parser, token->type, str);
      final->expanding = true;
      expansion = _token_list_create(parser);
      _token_list_append(parser, expansion, final);
      return expansion;
   }

   if (! macro->is_function) {
      token_list_t *replacement;

      /* Replace a macro defined as empty with a SPACE token. */
      if (macro->replacements == NULL)
         return _token_list_create_with_one_space(parser);

      replacement = _token_list_copy(parser, macro->replacements);
      _glcpp_parser_apply_pastes(parser, replacement);
      return replacement;
   }

   return _glcpp_parser_expand_function(parser, node, last, mode);
}

/* Push a new identifier onto the parser's active list.
 *
 * Here, 'marker' is the token node that appears in the list after the
 * expansion of 'identifier'. That is, when the list iterator begins
 * examining 'marker', then it is time to pop this node from the
 * active stack.
 */
static void
_parser_active_list_push(glcpp_parser_t *parser, const char *identifier,
                         token_node_t *marker)
{
   active_list_t *node;

   node = linear_alloc_child(parser->linalloc, sizeof(active_list_t));
   node->identifier = linear_strdup(parser->linalloc, identifier);
   node->marker = marker;
   node->next = parser->active;

   parser->active = node;
}

static void
_parser_active_list_pop(glcpp_parser_t *parser)
{
   active_list_t *node = parser->active;

   if (node == NULL) {
      parser->active = NULL;
      return;
   }

   node = parser->active->next;
   parser->active = node;
}

static int
_parser_active_list_contains(glcpp_parser_t *parser, const char *identifier)
{
   active_list_t *node;

   if (parser->active == NULL)
      return 0;

   for (node = parser->active; node; node = node->next)
      if (strcmp(node->identifier, identifier) == 0)
         return 1;

   return 0;
}

/* Walk over the token list replacing nodes with their expansion.
 * Whenever nodes are expanded the walking will walk over the new
 * nodes, continuing to expand as necessary. The results are placed in
 * 'list' itself.
 *
 * The "mode" argument controls the handling of any DEFINED tokens that
 * result from expansion as follows:
 *
 *   EXPANSION_MODE_IGNORE_DEFINED: Any resulting DEFINED tokens will be
 *      left in the final list, unevaluated. This is the correct mode
 *      for expanding any list in any context other than a
 *      preprocessor conditional, (#if or #elif).
 *
 *   EXPANSION_MODE_EVALUATE_DEFINED: Any resulting DEFINED tokens will be
 *      evaluated to 0 or 1 tokens depending on whether the following
 *      token is the name of a defined macro. If the DEFINED token is
 *      not followed by an (optionally parenthesized) identifier, then
 *      an error will be generated. This the correct mode for
 *      expanding any list in the context of a preprocessor
 *      conditional, (#if or #elif).
 */
static void
_glcpp_parser_expand_token_list(glcpp_parser_t *parser, token_list_t *list,
                                expansion_mode_t mode)
{
   token_node_t *node_prev;
   token_node_t *node, *last = NULL;
   token_list_t *expansion;
   active_list_t *active_initial = parser->active;
   int line;

   if (list == NULL)
      return;

   _token_list_trim_trailing_space (list);

   line = list->tail->token->location.last_line;

   node_prev = NULL;
   node = list->head;

   if (mode == EXPANSION_MODE_EVALUATE_DEFINED)
      _glcpp_parser_evaluate_defined_in_list (parser, list);

   while (node) {

      while (parser->active && parser->active->marker == node)
         _parser_active_list_pop (parser);

      expansion = _glcpp_parser_expand_node (parser, node, &last, mode, line);
      if (expansion) {
         token_node_t *n;

         if (mode == EXPANSION_MODE_EVALUATE_DEFINED) {
            _glcpp_parser_evaluate_defined_in_list (parser, expansion);
         }

         for (n = node; n != last->next; n = n->next)
            while (parser->active && parser->active->marker == n) {
               _parser_active_list_pop (parser);
            }

         _parser_active_list_push(parser, node->token->value.str, last->next);

         /* Splice expansion into list, supporting a simple deletion if the
          * expansion is empty.
          */
         if (expansion->head) {
            if (node_prev)
               node_prev->next = expansion->head;
            else
               list->head = expansion->head;
            expansion->tail->next = last->next;
            if (last == list->tail)
               list->tail = expansion->tail;
         } else {
            if (node_prev)
               node_prev->next = last->next;
            else
               list->head = last->next;
            if (last == list->tail)
               list->tail = NULL;
         }
      } else {
         node_prev = node;
      }
      node = node_prev ? node_prev->next : list->head;
   }

   /* Remove any lingering effects of this invocation on the
    * active list. That is, pop until the list looks like it did
    * at the beginning of this function. */
   while (parser->active && parser->active != active_initial)
      _parser_active_list_pop (parser);

   list->non_space_tail = list->tail;
}

void
_glcpp_parser_print_expanded_token_list(glcpp_parser_t *parser,
                                        token_list_t *list)
{
   if (list == NULL)
      return;

   _glcpp_parser_expand_token_list (parser, list, EXPANSION_MODE_IGNORE_DEFINED);

   _token_list_trim_trailing_space (list);

   _token_list_print (parser, list);
}

static void
_check_for_reserved_macro_name(glcpp_parser_t *parser, YYLTYPE *loc,
                               const char *identifier)
{
   /* Section 3.3 (Preprocessor) of the GLSL 1.30 spec (and later) and
    * the GLSL ES spec (all versions) say:
    *
    *     "All macro names containing two consecutive underscores ( __ )
    *     are reserved for future use as predefined macro names. All
    *     macro names prefixed with "GL_" ("GL" followed by a single
    *     underscore) are also reserved."
    *
    * The intention is that names containing __ are reserved for internal
    * use by the implementation, and names prefixed with GL_ are reserved
    * for use by Khronos.  Since every extension adds a name prefixed
    * with GL_ (i.e., the name of the extension), that should be an
    * error.  Names simply containing __ are dangerous to use, but should
    * be allowed.
    *
    * A future version of the GLSL specification will clarify this.
    */
   if (strstr(identifier, "__")) {
      glcpp_warning(loc, parser, "Macro names containing \"__\" are reserved "
                    "for use by the implementation.\n");
   }
   if (strncmp(identifier, "GL_", 3) == 0) {
      glcpp_error (loc, parser, "Macro names starting with \"GL_\" are reserved.\n");
   }
   if (strcmp(identifier, "defined") == 0) {
      glcpp_error (loc, parser, "\"defined\" cannot be used as a macro name");
   }
}

static int
_macro_equal(macro_t *a, macro_t *b)
{
   if (a->is_function != b->is_function)
      return 0;

   if (a->is_function) {
      if (! _string_list_equal (a->parameters, b->parameters))
         return 0;
   }

   return _token_list_equal_ignoring_space(a->replacements, b->replacements);
}

void
_define_object_macro(glcpp_parser_t *parser, YYLTYPE *loc,
                     const char *identifier, token_list_t *replacements)
{
   macro_t *macro, *previous;
   struct hash_entry *entry;

   /* We define pre-defined macros before we've started parsing the actual
    * file. So if there's no location defined yet, that's what were doing and
    * we don't want to generate an error for using the reserved names. */
   if (loc != NULL)
      _check_for_reserved_macro_name(parser, loc, identifier);

   macro = linear_alloc_child(parser->linalloc, sizeof(macro_t));

   macro->is_function = 0;
   macro->parameters = NULL;
   macro->identifier = linear_strdup(parser->linalloc, identifier);
   macro->replacements = replacements;

   entry = _mesa_hash_table_search(parser->defines, identifier);
   previous = entry ? entry->data : NULL;
   if (previous) {
      if (_macro_equal (macro, previous)) {
         return;
      }
      glcpp_error (loc, parser, "Redefinition of macro %s\n",  identifier);
   }

   _mesa_hash_table_insert (parser->defines, identifier, macro);
}

void
_define_function_macro(glcpp_parser_t *parser, YYLTYPE *loc,
                       const char *identifier, string_list_t *parameters,
                       token_list_t *replacements)
{
   macro_t *macro, *previous;
   struct hash_entry *entry;
   const char *dup;

   _check_for_reserved_macro_name(parser, loc, identifier);

        /* Check for any duplicate parameter names. */
   if ((dup = _string_list_has_duplicate (parameters)) != NULL) {
      glcpp_error (loc, parser, "Duplicate macro parameter \"%s\"", dup);
   }

   macro = linear_alloc_child(parser->linalloc, sizeof(macro_t));

   macro->is_function = 1;
   macro->parameters = parameters;
   macro->identifier = linear_strdup(parser->linalloc, identifier);
   macro->replacements = replacements;

   entry = _mesa_hash_table_search(parser->defines, identifier);
   previous = entry ? entry->data : NULL;
   if (previous) {
      if (_macro_equal (macro, previous)) {
         return;
      }
      glcpp_error (loc, parser, "Redefinition of macro %s\n", identifier);
   }

   _mesa_hash_table_insert(parser->defines, identifier, macro);
}

static int
glcpp_parser_lex(YYSTYPE *yylval, YYLTYPE *yylloc, glcpp_parser_t *parser)
{
   token_node_t *node;
   int ret;

   if (parser->lex_from_list == NULL) {
      ret = glcpp_lex(yylval, yylloc, parser->scanner);

      /* XXX: This ugly block of code exists for the sole
       * purpose of converting a NEWLINE token into a SPACE
       * token, but only in the case where we have seen a
       * function-like macro name, but have not yet seen its
       * closing parenthesis.
       *
       * There's perhaps a more compact way to do this with
       * mid-rule actions in the grammar.
       *
       * I'm definitely not pleased with the complexity of
       * this code here.
       */
      if (parser->newline_as_space) {
         if (ret == '(') {
            parser->paren_count++;
         } else if (ret == ')') {
            parser->paren_count--;
            if (parser->paren_count == 0)
               parser->newline_as_space = 0;
         } else if (ret == NEWLINE) {
            ret = SPACE;
         } else if (ret != SPACE) {
            if (parser->paren_count == 0)
               parser->newline_as_space = 0;
         }
      } else if (parser->in_control_line) {
         if (ret == NEWLINE)
            parser->in_control_line = 0;
      }
      else if (ret == DEFINE_TOKEN || ret == UNDEF || ret == IF ||
               ret == IFDEF || ret == IFNDEF || ret == ELIF || ret == ELSE ||
               ret == ENDIF || ret == HASH_TOKEN) {
         parser->in_control_line = 1;
      } else if (ret == IDENTIFIER) {
         struct hash_entry *entry = _mesa_hash_table_search(parser->defines,
                                                            yylval->str);
         macro_t *macro = entry ? entry->data : NULL;
         if (macro && macro->is_function) {
            parser->newline_as_space = 1;
            parser->paren_count = 0;
         }
      }

      return ret;
   }

   node = parser->lex_from_node;

   if (node == NULL) {
      parser->lex_from_list = NULL;
      return NEWLINE;
   }

   *yylval = node->token->value;
   ret = node->token->type;

   parser->lex_from_node = node->next;

   return ret;
}

static void
glcpp_parser_lex_from(glcpp_parser_t *parser, token_list_t *list)
{
   token_node_t *node;

   assert (parser->lex_from_list == NULL);

   /* Copy list, eliminating any space tokens. */
   parser->lex_from_list = _token_list_create (parser);

   for (node = list->head; node; node = node->next) {
      if (node->token->type == SPACE)
         continue;
      _token_list_append (parser,  parser->lex_from_list, node->token);
   }

   parser->lex_from_node = parser->lex_from_list->head;

   /* It's possible the list consisted of nothing but whitespace. */
   if (parser->lex_from_node == NULL) {
      parser->lex_from_list = NULL;
   }
}

static void
_glcpp_parser_skip_stack_push_if(glcpp_parser_t *parser, YYLTYPE *loc,
                                 int condition)
{
   skip_type_t current = SKIP_NO_SKIP;
   skip_node_t *node;

   if (parser->skip_stack)
      current = parser->skip_stack->type;

   node = linear_alloc_child(parser->linalloc, sizeof(skip_node_t));
   node->loc = *loc;

   if (current == SKIP_NO_SKIP) {
      if (condition)
         node->type = SKIP_NO_SKIP;
      else
         node->type = SKIP_TO_ELSE;
   } else {
      node->type = SKIP_TO_ENDIF;
   }

   node->has_else = false;
   node->next = parser->skip_stack;
   parser->skip_stack = node;
}

static void
_glcpp_parser_skip_stack_change_if(glcpp_parser_t *parser, YYLTYPE *loc,
                                   const char *type, int condition)
{
   if (parser->skip_stack == NULL) {
      glcpp_error (loc, parser, "#%s without #if\n", type);
      return;
   }

   if (parser->skip_stack->type == SKIP_TO_ELSE) {
      if (condition)
         parser->skip_stack->type = SKIP_NO_SKIP;
   } else {
      parser->skip_stack->type = SKIP_TO_ENDIF;
   }
}

static void
_glcpp_parser_skip_stack_pop(glcpp_parser_t *parser, YYLTYPE *loc)
{
   skip_node_t *node;

   if (parser->skip_stack == NULL) {
      glcpp_error (loc, parser, "#endif without #if\n");
      return;
   }

   node = parser->skip_stack;
   parser->skip_stack = node->next;
}

static void
_glcpp_parser_handle_version_declaration(glcpp_parser_t *parser, intmax_t version,
                                         const char *identifier,
                                         bool explicitly_set)
{
   if (parser->version_set)
      return;

   parser->version = version;
   parser->version_set = true;

   add_builtin_define (parser, "__VERSION__", version);

   parser->is_gles = (version == 100) ||
                     (identifier && (strcmp(identifier, "es") == 0));
   bool is_compat = version >= 150 && identifier &&
                    strcmp(identifier, "compatibility") == 0;

   /* Add pre-defined macros. */
   if (parser->is_gles)
      add_builtin_define(parser, "GL_ES", 1);
   else if (is_compat)
      add_builtin_define(parser, "GL_compatibility_profile", 1);
   else if (version >= 150)
      add_builtin_define(parser, "GL_core_profile", 1);

   /* Currently, all ES2/ES3 implementations support highp in the
    * fragment shader, so we always define this macro in ES2/ES3.
    * If we ever get a driver that doesn't support highp, we'll
    * need to add a flag to the gl_context and check that here.
    */
   if (version >= 130 || parser->is_gles)
      add_builtin_define (parser, "GL_FRAGMENT_PRECISION_HIGH", 1);

   /* Add all the extension macros available in this context */
   if (parser->extensions)
      parser->extensions(parser->state, add_builtin_define, parser,
                         version, parser->is_gles);

   if (parser->extension_list) {
      /* If MESA_shader_integer_functions is supported, then the building
       * blocks required for the 64x64 => 64 multiply exist.  Add defines for
       * those functions so that they can be tested.
       */
      if (parser->extension_list->MESA_shader_integer_functions) {
         add_builtin_define(parser, "__have_builtin_builtin_udiv64", 1);
         add_builtin_define(parser, "__have_builtin_builtin_umod64", 1);
         add_builtin_define(parser, "__have_builtin_builtin_idiv64", 1);
         add_builtin_define(parser, "__have_builtin_builtin_imod64", 1);
      }
   }

   if (explicitly_set) {
      _mesa_string_buffer_printf(parser->output,
                                 "#version %" PRIiMAX "%s%s", version,
                                 identifier ? " " : "",
                                 identifier ? identifier : "");
   }
}

/* GLSL version if no version is explicitly specified. */
#define IMPLICIT_GLSL_VERSION 110

/* GLSL ES version if no version is explicitly specified. */
#define IMPLICIT_GLSL_ES_VERSION 100

void
glcpp_parser_resolve_implicit_version(glcpp_parser_t *parser)
{
   int language_version = parser->api == API_OPENGLES2 ?
                          IMPLICIT_GLSL_ES_VERSION : IMPLICIT_GLSL_VERSION;

   _glcpp_parser_handle_version_declaration(parser, language_version,
                                            NULL, false);
}

static void
glcpp_parser_copy_defines(const void *key, void *data, void *closure)
{
   struct define_include *di = (struct define_include *) closure;
   macro_t *macro = (macro_t *) data;

   /* If we hit an error on a previous pass, just return */
   if (di->parser->error)
      return;

   const char *identifier =  macro->identifier;
   struct hash_entry *entry = _mesa_hash_table_search(di->parser->defines,
                                                      identifier);

   macro_t *previous = entry ? entry->data : NULL;
   if (previous) {
      if (_macro_equal(macro, previous)) {
         return;
      }
      glcpp_error(di->loc, di->parser, "Redefinition of macro %s\n",
                  identifier);
   }

   _mesa_hash_table_insert(di->parser->defines, identifier, macro);
}
#line 2937 "compiler/glsl/glcpp/glcpp-parse.c"

/* For use in generated program */
#define yydepth (int)(yystack.s_mark - yystack.s_base)
#if YYBTYACC
#define yytrial (yyps->save)
#endif /* YYBTYACC */

#if YYDEBUG
#include <stdio.h>	/* needed for printf */
#endif

#include <stdlib.h>	/* needed for malloc, etc */
#include <string.h>	/* needed for memset */

/* allocate initial stack or double stack size, up to YYMAXDEPTH */
static int yygrowstack(YYSTACKDATA *data)
{
    int i;
    unsigned newsize;
    YYINT *newss;
    YYSTYPE *newvs;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
    YYLTYPE *newps;
#endif

    if ((newsize = data->stacksize) == 0)
        newsize = YYINITSTACKSIZE;
    else if (newsize >= YYMAXDEPTH)
        return YYENOMEM;
    else if ((newsize *= 2) > YYMAXDEPTH)
        newsize = YYMAXDEPTH;

    i = (int) (data->s_mark - data->s_base);
    newss = (YYINT *)realloc(data->s_base, newsize * sizeof(*newss));
    if (newss == NULL)
        return YYENOMEM;

    data->s_base = newss;
    data->s_mark = newss + i;

    newvs = (YYSTYPE *)realloc(data->l_base, newsize * sizeof(*newvs));
    if (newvs == NULL)
        return YYENOMEM;

    data->l_base = newvs;
    data->l_mark = newvs + i;

#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
    newps = (YYLTYPE *)realloc(data->p_base, newsize * sizeof(*newps));
    if (newps == NULL)
        return YYENOMEM;

    data->p_base = newps;
    data->p_mark = newps + i;
#endif

    data->stacksize = newsize;
    data->s_last = data->s_base + newsize - 1;

#if YYDEBUG
    if (yydebug)
        fprintf(stderr, "%sdebug: stack size increased to %d\n", YYPREFIX, newsize);
#endif
    return 0;
}

#if YYPURE || defined(YY_NO_LEAKS)
static void yyfreestack(YYSTACKDATA *data)
{
    free(data->s_base);
    free(data->l_base);
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
    free(data->p_base);
#endif
    memset(data, 0, sizeof(*data));
}
#else
#define yyfreestack(data) /* nothing */
#endif /* YYPURE || defined(YY_NO_LEAKS) */
#if YYBTYACC

static YYParseState *
yyNewState(unsigned size)
{
    YYParseState *p = (YYParseState *) malloc(sizeof(YYParseState));
    if (p == NULL) return NULL;

    p->yystack.stacksize = size;
    if (size == 0)
    {
        p->yystack.s_base = NULL;
        p->yystack.l_base = NULL;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
        p->yystack.p_base = NULL;
#endif
        return p;
    }
    p->yystack.s_base    = (YYINT *) malloc(size * sizeof(YYINT));
    if (p->yystack.s_base == NULL) return NULL;
    p->yystack.l_base    = (YYSTYPE *) malloc(size * sizeof(YYSTYPE));
    if (p->yystack.l_base == NULL) return NULL;
    memset(p->yystack.l_base, 0, size * sizeof(YYSTYPE));
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
    p->yystack.p_base    = (YYLTYPE *) malloc(size * sizeof(YYLTYPE));
    if (p->yystack.p_base == NULL) return NULL;
    memset(p->yystack.p_base, 0, size * sizeof(YYLTYPE));
#endif

    return p;
}

static void
yyFreeState(YYParseState *p)
{
    yyfreestack(&p->yystack);
    free(p);
}
#endif /* YYBTYACC */

#define YYABORT  goto yyabort
#define YYREJECT goto yyabort
#define YYACCEPT goto yyaccept
#define YYERROR  goto yyerrlab
#if YYBTYACC
#define YYVALID        do { if (yyps->save)            goto yyvalid; } while(0)
#define YYVALID_NESTED do { if (yyps->save && \
                                yyps->save->save == 0) goto yyvalid; } while(0)
#endif /* YYBTYACC */

int
YYPARSE_DECL()
{
    int      yyerrflag;
    int      yychar;
    YYSTYPE  yyval;
    YYSTYPE  yylval;
    int      yynerrs;

#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
    YYLTYPE  yyloc; /* position returned by actions */
    YYLTYPE  yylloc; /* position from the lexer */
#endif

    /* variables for the parser stack */
    YYSTACKDATA yystack;
#if YYBTYACC

    /* Current parser state */
    static YYParseState *yyps = NULL;

    /* yypath != NULL: do the full parse, starting at *yypath parser state. */
    static YYParseState *yypath = NULL;

    /* Base of the lexical value queue */
    static YYSTYPE *yylvals = NULL;

    /* Current position at lexical value queue */
    static YYSTYPE *yylvp = NULL;

    /* End position of lexical value queue */
    static YYSTYPE *yylve = NULL;

    /* The last allocated position at the lexical value queue */
    static YYSTYPE *yylvlim = NULL;

#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
    /* Base of the lexical position queue */
    static YYLTYPE *yylpsns = NULL;

    /* Current position at lexical position queue */
    static YYLTYPE *yylpp = NULL;

    /* End position of lexical position queue */
    static YYLTYPE *yylpe = NULL;

    /* The last allocated position at the lexical position queue */
    static YYLTYPE *yylplim = NULL;
#endif

    /* Current position at lexical token queue */
    static YYINT  *yylexp = NULL;

    static YYINT  *yylexemes = NULL;
#endif /* YYBTYACC */
    int yym, yyn, yystate, yyresult;
#if YYBTYACC
    int yynewerrflag;
    YYParseState *yyerrctx = NULL;
#endif /* YYBTYACC */
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
    YYLTYPE  yyerror_loc_range[3]; /* position of error start/end (0 unused) */
#endif
#if YYDEBUG
    const char *yys;

    if ((yys = getenv("YYDEBUG")) != NULL)
    {
        yyn = *yys;
        if (yyn >= '0' && yyn <= '9')
            yydebug = yyn - '0';
    }
    if (yydebug)
        fprintf(stderr, "%sdebug[<# of symbols on state stack>]\n", YYPREFIX);
#endif
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
    memset(yyerror_loc_range, 0, sizeof(yyerror_loc_range));
#endif

    yyerrflag = 0;
    yychar = 0;
    memset(&yyval,  0, sizeof(yyval));
    memset(&yylval, 0, sizeof(yylval));
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
    memset(&yyloc,  0, sizeof(yyloc));
    memset(&yylloc, 0, sizeof(yylloc));
#endif

#line 180 "../mesa/src/compiler/glsl/glcpp/glcpp-parse.y"
	{
   yyloc.first_line = 1;
   yyloc.first_column = 1;
   yyloc.last_line = 1;
   yyloc.last_column = 1;
   yyloc.source = 0;
}
#if YYBTYACC
    yyps = yyNewState(0); if (yyps == NULL) goto yyenomem;
    yyps->save = NULL;
#endif /* YYBTYACC */
    yym = 0;
    /* yyn is set below */
    yynerrs = 0;
    yyerrflag = 0;
    yychar = YYEMPTY;
    yystate = 0;

#if YYPURE
    memset(&yystack, 0, sizeof(yystack));
#endif

    if (yystack.s_base == NULL && yygrowstack(&yystack) == YYENOMEM) goto yyoverflow;
    yystack.s_mark = yystack.s_base;
    yystack.l_mark = yystack.l_base;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
    yystack.p_mark = yystack.p_base;
#endif
    yystate = 0;
    *yystack.s_mark = 0;

yyloop:
    if ((yyn = yydefred[yystate]) != 0) goto yyreduce;
    if (yychar < 0)
    {
#if YYBTYACC
        do {
        if (yylvp < yylve)
        {
            /* we're currently re-reading tokens */
            yylval = *yylvp++;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
            yylloc = *yylpp++;
#endif
            yychar = *yylexp++;
            break;
        }
        if (yyps->save)
        {
            /* in trial mode; save scanner results for future parse attempts */
            if (yylvp == yylvlim)
            {   /* Enlarge lexical value queue */
                size_t p = (size_t) (yylvp - yylvals);
                size_t s = (size_t) (yylvlim - yylvals);

                s += YYLVQUEUEGROWTH;
                if ((yylexemes = (YYINT *)realloc(yylexemes, s * sizeof(YYINT))) == NULL) goto yyenomem;
                if ((yylvals   = (YYSTYPE *)realloc(yylvals, s * sizeof(YYSTYPE))) == NULL) goto yyenomem;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
                if ((yylpsns   = (YYLTYPE *)realloc(yylpsns, s * sizeof(YYLTYPE))) == NULL) goto yyenomem;
#endif
                yylvp   = yylve = yylvals + p;
                yylvlim = yylvals + s;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
                yylpp   = yylpe = yylpsns + p;
                yylplim = yylpsns + s;
#endif
                yylexp  = yylexemes + p;
            }
            *yylexp = (YYINT) YYLEX;
            *yylvp++ = yylval;
            yylve++;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
            *yylpp++ = yylloc;
            yylpe++;
#endif
            yychar = *yylexp++;
            break;
        }
        /* normal operation, no conflict encountered */
#endif /* YYBTYACC */
        yychar = YYLEX;
#if YYBTYACC
        } while (0);
#endif /* YYBTYACC */
        if (yychar < 0) yychar = YYEOF;
#if YYDEBUG
        if (yydebug)
        {
            if ((yys = yyname[YYTRANSLATE(yychar)]) == NULL) yys = yyname[YYUNDFTOKEN];
            fprintf(stderr, "%s[%d]: state %d, reading token %d (%s)",
                            YYDEBUGSTR, yydepth, yystate, yychar, yys);
#ifdef YYSTYPE_TOSTRING
#if YYBTYACC
            if (!yytrial)
#endif /* YYBTYACC */
                fprintf(stderr, " <%s>", YYSTYPE_TOSTRING(yychar, yylval));
#endif
            fputc('\n', stderr);
        }
#endif
    }
#if YYBTYACC

    /* Do we have a conflict? */
    if (((yyn = yycindex[yystate]) != 0) && (yyn += yychar) >= 0 &&
        yyn <= YYTABLESIZE && yycheck[yyn] == (YYINT) yychar)
    {
        YYINT ctry;

        if (yypath)
        {
            YYParseState *save;
#if YYDEBUG
            if (yydebug)
                fprintf(stderr, "%s[%d]: CONFLICT in state %d: following successful trial parse\n",
                                YYDEBUGSTR, yydepth, yystate);
#endif
            /* Switch to the next conflict context */
            save = yypath;
            yypath = save->save;
            save->save = NULL;
            ctry = save->ctry;
            if (save->state != yystate) YYABORT;
            yyFreeState(save);

        }
        else
        {

            /* Unresolved conflict - start/continue trial parse */
            YYParseState *save;
#if YYDEBUG
            if (yydebug)
            {
                fprintf(stderr, "%s[%d]: CONFLICT in state %d. ", YYDEBUGSTR, yydepth, yystate);
                if (yyps->save)
                    fputs("ALREADY in conflict, continuing trial parse.\n", stderr);
                else
                    fputs("Starting trial parse.\n", stderr);
            }
#endif
            save                  = yyNewState((unsigned)(yystack.s_mark - yystack.s_base + 1));
            if (save == NULL) goto yyenomem;
            save->save            = yyps->save;
            save->state           = yystate;
            save->errflag         = yyerrflag;
            save->yystack.s_mark  = save->yystack.s_base + (yystack.s_mark - yystack.s_base);
            memcpy (save->yystack.s_base, yystack.s_base, (size_t) (yystack.s_mark - yystack.s_base + 1) * sizeof(YYINT));
            save->yystack.l_mark  = save->yystack.l_base + (yystack.l_mark - yystack.l_base);
            memcpy (save->yystack.l_base, yystack.l_base, (size_t) (yystack.l_mark - yystack.l_base + 1) * sizeof(YYSTYPE));
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
            save->yystack.p_mark  = save->yystack.p_base + (yystack.p_mark - yystack.p_base);
            memcpy (save->yystack.p_base, yystack.p_base, (size_t) (yystack.p_mark - yystack.p_base + 1) * sizeof(YYLTYPE));
#endif
            ctry                  = yytable[yyn];
            if (yyctable[ctry] == -1)
            {
#if YYDEBUG
                if (yydebug && yychar >= YYEOF)
                    fprintf(stderr, "%s[%d]: backtracking 1 token\n", YYDEBUGSTR, yydepth);
#endif
                ctry++;
            }
            save->ctry = ctry;
            if (yyps->save == NULL)
            {
                /* If this is a first conflict in the stack, start saving lexemes */
                if (!yylexemes)
                {
                    yylexemes = (YYINT *) malloc((YYLVQUEUEGROWTH) * sizeof(YYINT));
                    if (yylexemes == NULL) goto yyenomem;
                    yylvals   = (YYSTYPE *) malloc((YYLVQUEUEGROWTH) * sizeof(YYSTYPE));
                    if (yylvals == NULL) goto yyenomem;
                    yylvlim   = yylvals + YYLVQUEUEGROWTH;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
                    yylpsns   = (YYLTYPE *) malloc((YYLVQUEUEGROWTH) * sizeof(YYLTYPE));
                    if (yylpsns == NULL) goto yyenomem;
                    yylplim   = yylpsns + YYLVQUEUEGROWTH;
#endif
                }
                if (yylvp == yylve)
                {
                    yylvp  = yylve = yylvals;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
                    yylpp  = yylpe = yylpsns;
#endif
                    yylexp = yylexemes;
                    if (yychar >= YYEOF)
                    {
                        *yylve++ = yylval;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
                        *yylpe++ = yylloc;
#endif
                        *yylexp  = (YYINT) yychar;
                        yychar   = YYEMPTY;
                    }
                }
            }
            if (yychar >= YYEOF)
            {
                yylvp--;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
                yylpp--;
#endif
                yylexp--;
                yychar = YYEMPTY;
            }
            save->lexeme = (int) (yylvp - yylvals);
            yyps->save   = save;
        }
        if (yytable[yyn] == ctry)
        {
#if YYDEBUG
            if (yydebug)
                fprintf(stderr, "%s[%d]: state %d, shifting to state %d\n",
                                YYDEBUGSTR, yydepth, yystate, yyctable[ctry]);
#endif
            if (yychar < 0)
            {
                yylvp++;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
                yylpp++;
#endif
                yylexp++;
            }
            if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM)
                goto yyoverflow;
            yystate = yyctable[ctry];
            *++yystack.s_mark = (YYINT) yystate;
            *++yystack.l_mark = yylval;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
            *++yystack.p_mark = yylloc;
#endif
            yychar  = YYEMPTY;
            if (yyerrflag > 0) --yyerrflag;
            goto yyloop;
        }
        else
        {
            yyn = yyctable[ctry];
            goto yyreduce;
        }
    } /* End of code dealing with conflicts */
#endif /* YYBTYACC */
    if (((yyn = yysindex[yystate]) != 0) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == (YYINT) yychar)
    {
#if YYDEBUG
        if (yydebug)
            fprintf(stderr, "%s[%d]: state %d, shifting to state %d\n",
                            YYDEBUGSTR, yydepth, yystate, yytable[yyn]);
#endif
        if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM) goto yyoverflow;
        yystate = yytable[yyn];
        *++yystack.s_mark = yytable[yyn];
        *++yystack.l_mark = yylval;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
        *++yystack.p_mark = yylloc;
#endif
        yychar = YYEMPTY;
        if (yyerrflag > 0)  --yyerrflag;
        goto yyloop;
    }
    if (((yyn = yyrindex[yystate]) != 0) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == (YYINT) yychar)
    {
        yyn = yytable[yyn];
        goto yyreduce;
    }
    if (yyerrflag != 0) goto yyinrecovery;
#if YYBTYACC

    yynewerrflag = 1;
    goto yyerrhandler;
    goto yyerrlab; /* redundant goto avoids 'unused label' warning */

yyerrlab:
    /* explicit YYERROR from an action -- pop the rhs of the rule reduced
     * before looking for error recovery */
    yystack.s_mark -= yym;
    yystate = *yystack.s_mark;
    yystack.l_mark -= yym;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
    yystack.p_mark -= yym;
#endif

    yynewerrflag = 0;
yyerrhandler:
    while (yyps->save)
    {
        int ctry;
        YYParseState *save = yyps->save;
#if YYDEBUG
        if (yydebug)
            fprintf(stderr, "%s[%d]: ERROR in state %d, CONFLICT BACKTRACKING to state %d, %d tokens\n",
                            YYDEBUGSTR, yydepth, yystate, yyps->save->state,
                    (int)(yylvp - yylvals - yyps->save->lexeme));
#endif
        /* Memorize most forward-looking error state in case it's really an error. */
        if (yyerrctx == NULL || yyerrctx->lexeme < yylvp - yylvals)
        {
            /* Free old saved error context state */
            if (yyerrctx) yyFreeState(yyerrctx);
            /* Create and fill out new saved error context state */
            yyerrctx                 = yyNewState((unsigned)(yystack.s_mark - yystack.s_base + 1));
            if (yyerrctx == NULL) goto yyenomem;
            yyerrctx->save           = yyps->save;
            yyerrctx->state          = yystate;
            yyerrctx->errflag        = yyerrflag;
            yyerrctx->yystack.s_mark = yyerrctx->yystack.s_base + (yystack.s_mark - yystack.s_base);
            memcpy (yyerrctx->yystack.s_base, yystack.s_base, (size_t) (yystack.s_mark - yystack.s_base + 1) * sizeof(YYINT));
            yyerrctx->yystack.l_mark = yyerrctx->yystack.l_base + (yystack.l_mark - yystack.l_base);
            memcpy (yyerrctx->yystack.l_base, yystack.l_base, (size_t) (yystack.l_mark - yystack.l_base + 1) * sizeof(YYSTYPE));
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
            yyerrctx->yystack.p_mark = yyerrctx->yystack.p_base + (yystack.p_mark - yystack.p_base);
            memcpy (yyerrctx->yystack.p_base, yystack.p_base, (size_t) (yystack.p_mark - yystack.p_base + 1) * sizeof(YYLTYPE));
#endif
            yyerrctx->lexeme         = (int) (yylvp - yylvals);
        }
        yylvp          = yylvals   + save->lexeme;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
        yylpp          = yylpsns   + save->lexeme;
#endif
        yylexp         = yylexemes + save->lexeme;
        yychar         = YYEMPTY;
        yystack.s_mark = yystack.s_base + (save->yystack.s_mark - save->yystack.s_base);
        memcpy (yystack.s_base, save->yystack.s_base, (size_t) (yystack.s_mark - yystack.s_base + 1) * sizeof(YYINT));
        yystack.l_mark = yystack.l_base + (save->yystack.l_mark - save->yystack.l_base);
        memcpy (yystack.l_base, save->yystack.l_base, (size_t) (yystack.l_mark - yystack.l_base + 1) * sizeof(YYSTYPE));
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
        yystack.p_mark = yystack.p_base + (save->yystack.p_mark - save->yystack.p_base);
        memcpy (yystack.p_base, save->yystack.p_base, (size_t) (yystack.p_mark - yystack.p_base + 1) * sizeof(YYLTYPE));
#endif
        ctry           = ++save->ctry;
        yystate        = save->state;
        /* We tried shift, try reduce now */
        if ((yyn = yyctable[ctry]) >= 0) goto yyreduce;
        yyps->save     = save->save;
        save->save     = NULL;
        yyFreeState(save);

        /* Nothing left on the stack -- error */
        if (!yyps->save)
        {
#if YYDEBUG
            if (yydebug)
                fprintf(stderr, "%sdebug[%d,trial]: trial parse FAILED, entering ERROR mode\n",
                                YYPREFIX, yydepth);
#endif
            /* Restore state as it was in the most forward-advanced error */
            yylvp          = yylvals   + yyerrctx->lexeme;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
            yylpp          = yylpsns   + yyerrctx->lexeme;
#endif
            yylexp         = yylexemes + yyerrctx->lexeme;
            yychar         = yylexp[-1];
            yylval         = yylvp[-1];
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
            yylloc         = yylpp[-1];
#endif
            yystack.s_mark = yystack.s_base + (yyerrctx->yystack.s_mark - yyerrctx->yystack.s_base);
            memcpy (yystack.s_base, yyerrctx->yystack.s_base, (size_t) (yystack.s_mark - yystack.s_base + 1) * sizeof(YYINT));
            yystack.l_mark = yystack.l_base + (yyerrctx->yystack.l_mark - yyerrctx->yystack.l_base);
            memcpy (yystack.l_base, yyerrctx->yystack.l_base, (size_t) (yystack.l_mark - yystack.l_base + 1) * sizeof(YYSTYPE));
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
            yystack.p_mark = yystack.p_base + (yyerrctx->yystack.p_mark - yyerrctx->yystack.p_base);
            memcpy (yystack.p_base, yyerrctx->yystack.p_base, (size_t) (yystack.p_mark - yystack.p_base + 1) * sizeof(YYLTYPE));
#endif
            yystate        = yyerrctx->state;
            yyFreeState(yyerrctx);
            yyerrctx       = NULL;
        }
        yynewerrflag = 1;
    }
    if (yynewerrflag == 0) goto yyinrecovery;
#endif /* YYBTYACC */

    YYERROR_CALL("syntax error");
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
    yyerror_loc_range[1] = yylloc; /* lookahead position is error start position */
#endif

#if !YYBTYACC
    goto yyerrlab; /* redundant goto avoids 'unused label' warning */
yyerrlab:
#endif
    ++yynerrs;

yyinrecovery:
    if (yyerrflag < 3)
    {
        yyerrflag = 3;
        for (;;)
        {
            if (((yyn = yysindex[*yystack.s_mark]) != 0) && (yyn += YYERRCODE) >= 0 &&
                    yyn <= YYTABLESIZE && yycheck[yyn] == (YYINT) YYERRCODE)
            {
#if YYDEBUG
                if (yydebug)
                    fprintf(stderr, "%s[%d]: state %d, error recovery shifting to state %d\n",
                                    YYDEBUGSTR, yydepth, *yystack.s_mark, yytable[yyn]);
#endif
                if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM) goto yyoverflow;
                yystate = yytable[yyn];
                *++yystack.s_mark = yytable[yyn];
                *++yystack.l_mark = yylval;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
                /* lookahead position is error end position */
                yyerror_loc_range[2] = yylloc;
                YYLLOC_DEFAULT(yyloc, yyerror_loc_range, 2); /* position of error span */
                *++yystack.p_mark = yyloc;
#endif
                goto yyloop;
            }
            else
            {
#if YYDEBUG
                if (yydebug)
                    fprintf(stderr, "%s[%d]: error recovery discarding state %d\n",
                                    YYDEBUGSTR, yydepth, *yystack.s_mark);
#endif
                if (yystack.s_mark <= yystack.s_base) goto yyabort;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
                /* the current TOS position is the error start position */
                yyerror_loc_range[1] = *yystack.p_mark;
#endif
#if defined(YYDESTRUCT_CALL)
#if YYBTYACC
                if (!yytrial)
#endif /* YYBTYACC */
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
                    YYDESTRUCT_CALL("error: discarding state",
                                    yystos[*yystack.s_mark], yystack.l_mark, yystack.p_mark);
#else
                    YYDESTRUCT_CALL("error: discarding state",
                                    yystos[*yystack.s_mark], yystack.l_mark);
#endif /* defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED) */
#endif /* defined(YYDESTRUCT_CALL) */
                --yystack.s_mark;
                --yystack.l_mark;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
                --yystack.p_mark;
#endif
            }
        }
    }
    else
    {
        if (yychar == YYEOF) goto yyabort;
#if YYDEBUG
        if (yydebug)
        {
            if ((yys = yyname[YYTRANSLATE(yychar)]) == NULL) yys = yyname[YYUNDFTOKEN];
            fprintf(stderr, "%s[%d]: state %d, error recovery discarding token %d (%s)\n",
                            YYDEBUGSTR, yydepth, yystate, yychar, yys);
        }
#endif
#if defined(YYDESTRUCT_CALL)
#if YYBTYACC
        if (!yytrial)
#endif /* YYBTYACC */
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
            YYDESTRUCT_CALL("error: discarding token", yychar, &yylval, &yylloc);
#else
            YYDESTRUCT_CALL("error: discarding token", yychar, &yylval);
#endif /* defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED) */
#endif /* defined(YYDESTRUCT_CALL) */
        yychar = YYEMPTY;
        goto yyloop;
    }

yyreduce:
    yym = yylen[yyn];
#if YYDEBUG
    if (yydebug)
    {
        fprintf(stderr, "%s[%d]: state %d, reducing by rule %d (%s)",
                        YYDEBUGSTR, yydepth, yystate, yyn, yyrule[yyn]);
#ifdef YYSTYPE_TOSTRING
#if YYBTYACC
        if (!yytrial)
#endif /* YYBTYACC */
            if (yym > 0)
            {
                int i;
                fputc('<', stderr);
                for (i = yym; i > 0; i--)
                {
                    if (i != yym) fputs(", ", stderr);
                    fputs(YYSTYPE_TOSTRING(yystos[yystack.s_mark[1-i]],
                                           yystack.l_mark[1-i]), stderr);
                }
                fputc('>', stderr);
            }
#endif
        fputc('\n', stderr);
    }
#endif
    if (yym > 0)
        yyval = yystack.l_mark[1-yym];
    else
        memset(&yyval, 0, sizeof yyval);
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)

    /* Perform position reduction */
    memset(&yyloc, 0, sizeof(yyloc));
#if YYBTYACC
    if (!yytrial)
#endif /* YYBTYACC */
    {
        YYLLOC_DEFAULT(yyloc, &yystack.p_mark[-yym], yym);
        /* just in case YYERROR is invoked within the action, save
           the start of the rhs as the error start position */
        yyerror_loc_range[1] = yystack.p_mark[1-yym];
    }
#endif

    switch (yyn)
    {
case 5:
#line 228 "../mesa/src/compiler/glsl/glcpp/glcpp-parse.y"
	{
		_glcpp_parser_print_expanded_token_list (parser, yystack.l_mark[0].token_list);
		_mesa_string_buffer_append_char(parser->output, '\n');
	}
#line 3674 "compiler/glsl/glcpp/glcpp-parse.c"
break;
case 7:
#line 236 "../mesa/src/compiler/glsl/glcpp/glcpp-parse.y"
	{
		if (parser->is_gles && yystack.l_mark[-1].expression_value.undefined_macro)
			glcpp_error(& yystack.p_mark[-2], parser, "undefined macro %s in expression (illegal in GLES)", yystack.l_mark[-1].expression_value.undefined_macro);
		_glcpp_parser_skip_stack_push_if (parser, & yystack.p_mark[-2], yystack.l_mark[-1].expression_value.value);
	}
#line 3683 "compiler/glsl/glcpp/glcpp-parse.c"
break;
case 8:
#line 241 "../mesa/src/compiler/glsl/glcpp/glcpp-parse.y"
	{
		if (parser->is_gles && yystack.l_mark[-1].expression_value.undefined_macro)
			glcpp_error(& yystack.p_mark[-2], parser, "undefined macro %s in expression (illegal in GLES)", yystack.l_mark[-1].expression_value.undefined_macro);
		_glcpp_parser_skip_stack_change_if (parser, & yystack.p_mark[-2], "elif", yystack.l_mark[-1].expression_value.value);
	}
#line 3692 "compiler/glsl/glcpp/glcpp-parse.c"
break;
case 9:
#line 246 "../mesa/src/compiler/glsl/glcpp/glcpp-parse.y"
	{
		parser->has_new_line_number = 1;
		parser->new_line_number = yystack.l_mark[-1].ival;
		_mesa_string_buffer_printf(parser->output, "#line %" PRIiMAX "\n", yystack.l_mark[-1].ival);
	}
#line 3701 "compiler/glsl/glcpp/glcpp-parse.c"
break;
case 10:
#line 251 "../mesa/src/compiler/glsl/glcpp/glcpp-parse.y"
	{
		parser->has_new_line_number = 1;
		parser->new_line_number = yystack.l_mark[-2].ival;
		parser->has_new_source_number = 1;
		parser->new_source_number = yystack.l_mark[-1].ival;
		_mesa_string_buffer_printf(parser->output,
					   "#line %" PRIiMAX " %" PRIiMAX "\n",
					    yystack.l_mark[-2].ival, yystack.l_mark[-1].ival);
	}
#line 3714 "compiler/glsl/glcpp/glcpp-parse.c"
break;
case 11:
#line 260 "../mesa/src/compiler/glsl/glcpp/glcpp-parse.y"
	{
		parser->has_new_line_number = 1;
		parser->new_line_number = yystack.l_mark[-2].ival;
		_mesa_string_buffer_printf(parser->output,
					   "#line %" PRIiMAX " %s\n",
					    yystack.l_mark[-2].ival, yystack.l_mark[-1].str);
	}
#line 3725 "compiler/glsl/glcpp/glcpp-parse.c"
break;
case 12:
#line 270 "../mesa/src/compiler/glsl/glcpp/glcpp-parse.y"
	{
		_define_object_macro (parser, & yystack.p_mark[-2], yystack.l_mark[-2].str, yystack.l_mark[-1].token_list);
	}
#line 3732 "compiler/glsl/glcpp/glcpp-parse.c"
break;
case 13:
#line 273 "../mesa/src/compiler/glsl/glcpp/glcpp-parse.y"
	{
		_define_function_macro (parser, & yystack.p_mark[-4], yystack.l_mark[-4].str, NULL, yystack.l_mark[-1].token_list);
	}
#line 3739 "compiler/glsl/glcpp/glcpp-parse.c"
break;
case 14:
#line 276 "../mesa/src/compiler/glsl/glcpp/glcpp-parse.y"
	{
		_define_function_macro (parser, & yystack.p_mark[-5], yystack.l_mark[-5].str, yystack.l_mark[-3].string_list, yystack.l_mark[-1].token_list);
	}
#line 3746 "compiler/glsl/glcpp/glcpp-parse.c"
break;
case 15:
#line 282 "../mesa/src/compiler/glsl/glcpp/glcpp-parse.y"
	{
		_mesa_string_buffer_append_char(parser->output, '\n');
	}
#line 3753 "compiler/glsl/glcpp/glcpp-parse.c"
break;
case 17:
#line 286 "../mesa/src/compiler/glsl/glcpp/glcpp-parse.y"
	{

		if (parser->skip_stack == NULL ||
		    parser->skip_stack->type == SKIP_NO_SKIP)
		{
			_glcpp_parser_expand_and_lex_from (parser,
							   LINE_EXPANDED, yystack.l_mark[-1].token_list,
							   EXPANSION_MODE_IGNORE_DEFINED);
		}
	}
#line 3767 "compiler/glsl/glcpp/glcpp-parse.c"
break;
case 19:
#line 300 "../mesa/src/compiler/glsl/glcpp/glcpp-parse.y"
	{
		struct hash_entry *entry;

                /* Section 3.4 (Preprocessor) of the GLSL ES 3.00 spec says:
                 *
                 *    It is an error to undefine or to redefine a built-in
                 *    (pre-defined) macro name.
                 *
                 * The GLSL ES 1.00 spec does not contain this text, but
                 * dEQP's preprocess test in GLES2 checks for it.
                 *
                 * Section 3.3 (Preprocessor) revision 7, of the GLSL 4.50
                 * spec says:
                 *
                 *    By convention, all macro names containing two consecutive
                 *    underscores ( __ ) are reserved for use by underlying
                 *    software layers. Defining or undefining such a name
                 *    in a shader does not itself result in an error, but may
                 *    result in unintended behaviors that stem from having
                 *    multiple definitions of the same name. All macro names
                 *    prefixed with "GL_" (...) are also reseved, and defining
                 *    such a name results in a compile-time error.
                 *
                 * The code below implements the same checks as GLSLang.
                 */
		if (strncmp("GL_", yystack.l_mark[-1].str, 3) == 0)
			glcpp_error(& yystack.p_mark[-3], parser, "Built-in (pre-defined)"
				    " names beginning with GL_ cannot be undefined.");
		else if (strstr(yystack.l_mark[-1].str, "__") != NULL) {
			if (parser->is_gles
			    && parser->version >= 300
			    && (strcmp("__LINE__", yystack.l_mark[-1].str) == 0
				|| strcmp("__FILE__", yystack.l_mark[-1].str) == 0
				|| strcmp("__VERSION__", yystack.l_mark[-1].str) == 0)) {
				glcpp_error(& yystack.p_mark[-3], parser, "Built-in (pre-defined)"
					    " names cannot be undefined.");
			} else if (parser->is_gles && parser->version <= 300) {
				glcpp_error(& yystack.p_mark[-3], parser,
					    " names containing consecutive underscores"
					    " are reserved.");
			} else {
				glcpp_warning(& yystack.p_mark[-3], parser,
					      " names containing consecutive underscores"
					      " are reserved.");
			}
		}

		entry = _mesa_hash_table_search (parser->defines, yystack.l_mark[-1].str);
		if (entry) {
			_mesa_hash_table_remove (parser->defines, entry);
		}
	}
#line 3823 "compiler/glsl/glcpp/glcpp-parse.c"
break;
case 20:
#line 352 "../mesa/src/compiler/glsl/glcpp/glcpp-parse.y"
	{
		size_t include_cursor = _mesa_get_shader_include_cursor(parser->gl_ctx->Shared);

		/* Remove leading and trailing "" or <> */
		char *start = strchr(yystack.l_mark[-1].str, '"');
		if (!start) {
			_mesa_set_shader_include_cursor(parser->gl_ctx->Shared, 0);
			start = strchr(yystack.l_mark[-1].str, '<');
		}
		char *path = strndup(start + 1, strlen(start + 1) - 1);

		const char *shader =
			_mesa_lookup_shader_include(parser->gl_ctx, path, false);
		free(path);

		if (!shader)
			glcpp_error(&yystack.p_mark[-2], parser, "%s not found", yystack.l_mark[-1].str);
		else {
			/* Create a temporary parser with the same settings */
			glcpp_parser_t *tmp_parser =
				glcpp_parser_create(parser->gl_ctx, parser->extensions, parser->state);
			tmp_parser->version_set = true;
			tmp_parser->version = parser->version;

			/* Set the shader source and run the lexer */
			glcpp_lex_set_source_string(tmp_parser, shader);

			/* Copy any existing define macros to the temporary
			 * shade include parser.
			 */
			struct define_include di;
			di.parser = tmp_parser;
			di.loc = &yystack.p_mark[-2];

			hash_table_call_foreach(parser->defines,
						glcpp_parser_copy_defines,
						&di);

			/* Print out '#include' to the glsl parser. We do this
			 * so that it can do the error checking require to
			 * make sure the ARB_shading_language_include
			 * extension is enabled.
			 */
			_mesa_string_buffer_printf(parser->output, "#include\n");

			/* Parse the include string before adding to the
			 * preprocessor output.
			 */
			glcpp_parser_parse(tmp_parser);
			_mesa_string_buffer_printf(parser->info_log, "%s",
						   tmp_parser->info_log->buf);
			_mesa_string_buffer_printf(parser->output, "%s",
						   tmp_parser->output->buf);

			/* Copy any new define macros to the parent parser
			 * and steal the memory of our temp parser so we don't
			 * free these new defines before they are no longer
			 * needed.
			 */
			di.parser = parser;
			di.loc = &yystack.p_mark[-2];
			ralloc_steal(parser, tmp_parser);

			hash_table_call_foreach(tmp_parser->defines,
						glcpp_parser_copy_defines,
						&di);

			/* Destroy tmp parser memory we no longer need */
			glcpp_lex_destroy(tmp_parser->scanner);
			_mesa_hash_table_destroy(tmp_parser->defines, NULL);
		}

		_mesa_set_shader_include_cursor(parser->gl_ctx->Shared, include_cursor);
	}
#line 3901 "compiler/glsl/glcpp/glcpp-parse.c"
break;
case 21:
#line 426 "../mesa/src/compiler/glsl/glcpp/glcpp-parse.y"
	{
		/* Be careful to only evaluate the 'if' expression if
		 * we are not skipping. When we are skipping, we
		 * simply push a new 0-valued 'if' onto the skip
		 * stack.
		 *
		 * This avoids generating diagnostics for invalid
		 * expressions that are being skipped. */
		if (parser->skip_stack == NULL ||
		    parser->skip_stack->type == SKIP_NO_SKIP)
		{
			_glcpp_parser_expand_and_lex_from (parser,
							   IF_EXPANDED, yystack.l_mark[-1].token_list,
							   EXPANSION_MODE_EVALUATE_DEFINED);
		}	
		else
		{
			_glcpp_parser_skip_stack_push_if (parser, & yystack.p_mark[-3], 0);
			parser->skip_stack->type = SKIP_TO_ENDIF;
		}
	}
#line 3926 "compiler/glsl/glcpp/glcpp-parse.c"
break;
case 22:
#line 447 "../mesa/src/compiler/glsl/glcpp/glcpp-parse.y"
	{
		/* #if without an expression is only an error if we
		 *  are not skipping */
		if (parser->skip_stack == NULL ||
		    parser->skip_stack->type == SKIP_NO_SKIP)
		{
			glcpp_error(& yystack.p_mark[-2], parser, "#if with no expression");
		}	
		_glcpp_parser_skip_stack_push_if (parser, & yystack.p_mark[-2], 0);
	}
#line 3940 "compiler/glsl/glcpp/glcpp-parse.c"
break;
case 23:
#line 457 "../mesa/src/compiler/glsl/glcpp/glcpp-parse.y"
	{
		struct hash_entry *entry =
				_mesa_hash_table_search(parser->defines, yystack.l_mark[-2].str);
		macro_t *macro = entry ? entry->data : NULL;
		_glcpp_parser_skip_stack_push_if (parser, & yystack.p_mark[-4], macro != NULL);
	}
#line 3950 "compiler/glsl/glcpp/glcpp-parse.c"
break;
case 24:
#line 463 "../mesa/src/compiler/glsl/glcpp/glcpp-parse.y"
	{
		struct hash_entry *entry =
				_mesa_hash_table_search(parser->defines, yystack.l_mark[-2].str);
		macro_t *macro = entry ? entry->data : NULL;
		_glcpp_parser_skip_stack_push_if (parser, & yystack.p_mark[-2], macro == NULL);
	}
#line 3960 "compiler/glsl/glcpp/glcpp-parse.c"
break;
case 25:
#line 469 "../mesa/src/compiler/glsl/glcpp/glcpp-parse.y"
	{
		/* Be careful to only evaluate the 'elif' expression
		 * if we are not skipping. When we are skipping, we
		 * simply change to a 0-valued 'elif' on the skip
		 * stack.
		 *
		 * This avoids generating diagnostics for invalid
		 * expressions that are being skipped. */
		if (parser->skip_stack &&
		    parser->skip_stack->type == SKIP_TO_ELSE)
		{
			_glcpp_parser_expand_and_lex_from (parser,
							   ELIF_EXPANDED, yystack.l_mark[-1].token_list,
							   EXPANSION_MODE_EVALUATE_DEFINED);
		}
		else if (parser->skip_stack &&
		    parser->skip_stack->has_else)
		{
			glcpp_error(& yystack.p_mark[-3], parser, "#elif after #else");
		}
		else
		{
			_glcpp_parser_skip_stack_change_if (parser, & yystack.p_mark[-3],
							    "elif", 0);
		}
	}
#line 3990 "compiler/glsl/glcpp/glcpp-parse.c"
break;
case 26:
#line 495 "../mesa/src/compiler/glsl/glcpp/glcpp-parse.y"
	{
		/* #elif without an expression is an error unless we
		 * are skipping. */
		if (parser->skip_stack &&
		    parser->skip_stack->type == SKIP_TO_ELSE)
		{
			glcpp_error(& yystack.p_mark[-2], parser, "#elif with no expression");
		}
		else if (parser->skip_stack &&
		    parser->skip_stack->has_else)
		{
			glcpp_error(& yystack.p_mark[-2], parser, "#elif after #else");
		}
		else
		{
			_glcpp_parser_skip_stack_change_if (parser, & yystack.p_mark[-2],
							    "elif", 0);
			glcpp_warning(& yystack.p_mark[-2], parser, "ignoring illegal #elif without expression");
		}
	}
#line 4014 "compiler/glsl/glcpp/glcpp-parse.c"
break;
case 27:
#line 515 "../mesa/src/compiler/glsl/glcpp/glcpp-parse.y"
	{ parser->lexing_directive = 1; }
#line 4019 "compiler/glsl/glcpp/glcpp-parse.c"
break;
case 28:
#line 515 "../mesa/src/compiler/glsl/glcpp/glcpp-parse.y"
	{
		if (parser->skip_stack &&
		    parser->skip_stack->has_else)
		{
			glcpp_error(& yystack.p_mark[-3], parser, "multiple #else");
		}
		else
		{
			_glcpp_parser_skip_stack_change_if (parser, & yystack.p_mark[-3], "else", 1);
			if (parser->skip_stack)
				parser->skip_stack->has_else = true;
		}
	}
#line 4036 "compiler/glsl/glcpp/glcpp-parse.c"
break;
case 29:
#line 528 "../mesa/src/compiler/glsl/glcpp/glcpp-parse.y"
	{
		_glcpp_parser_skip_stack_pop (parser, & yystack.p_mark[-1]);
	}
#line 4043 "compiler/glsl/glcpp/glcpp-parse.c"
break;
case 31:
#line 531 "../mesa/src/compiler/glsl/glcpp/glcpp-parse.y"
	{
		if (parser->version_set) {
			glcpp_error(& yystack.p_mark[-3], parser, "#version must appear on the first line");
		}
		_glcpp_parser_handle_version_declaration(parser, yystack.l_mark[-1].ival, NULL, true);
	}
#line 4053 "compiler/glsl/glcpp/glcpp-parse.c"
break;
case 32:
#line 537 "../mesa/src/compiler/glsl/glcpp/glcpp-parse.y"
	{
		if (parser->version_set) {
			glcpp_error(& yystack.p_mark[-4], parser, "#version must appear on the first line");
		}
		_glcpp_parser_handle_version_declaration(parser, yystack.l_mark[-2].ival, yystack.l_mark[-1].str, true);
	}
#line 4063 "compiler/glsl/glcpp/glcpp-parse.c"
break;
case 33:
#line 543 "../mesa/src/compiler/glsl/glcpp/glcpp-parse.y"
	{
		glcpp_parser_resolve_implicit_version(parser);
	}
#line 4070 "compiler/glsl/glcpp/glcpp-parse.c"
break;
case 34:
#line 546 "../mesa/src/compiler/glsl/glcpp/glcpp-parse.y"
	{
		_mesa_string_buffer_printf(parser->output, "#%s", yystack.l_mark[-1].str);
	}
#line 4077 "compiler/glsl/glcpp/glcpp-parse.c"
break;
case 35:
#line 552 "../mesa/src/compiler/glsl/glcpp/glcpp-parse.y"
	{
		glcpp_error(& yystack.p_mark[-2], parser, "#%s", yystack.l_mark[-1].str);
	}
#line 4084 "compiler/glsl/glcpp/glcpp-parse.c"
break;
case 36:
#line 555 "../mesa/src/compiler/glsl/glcpp/glcpp-parse.y"
	{
		glcpp_error (& yystack.p_mark[-2], parser, "#define without macro name");
	}
#line 4091 "compiler/glsl/glcpp/glcpp-parse.c"
break;
case 37:
#line 558 "../mesa/src/compiler/glsl/glcpp/glcpp-parse.y"
	{
		glcpp_error (& yystack.p_mark[-3], parser, "Illegal non-directive after #");
	}
#line 4098 "compiler/glsl/glcpp/glcpp-parse.c"
break;
case 38:
#line 564 "../mesa/src/compiler/glsl/glcpp/glcpp-parse.y"
	{
		/* let strtoll detect the base */
		yyval.ival = strtoll (yystack.l_mark[0].str, NULL, 0);
	}
#line 4106 "compiler/glsl/glcpp/glcpp-parse.c"
break;
case 39:
#line 568 "../mesa/src/compiler/glsl/glcpp/glcpp-parse.y"
	{
		yyval.ival = yystack.l_mark[0].ival;
	}
#line 4113 "compiler/glsl/glcpp/glcpp-parse.c"
break;
case 40:
#line 573 "../mesa/src/compiler/glsl/glcpp/glcpp-parse.y"
	{
	   /* Both octal and hexadecimal constants begin with 0. */
	   if (yystack.l_mark[0].str[0] == '0' && yystack.l_mark[0].str[1] != '\0') {
		glcpp_error(&yystack.p_mark[0], parser, "invalid #version \"%s\" (not a decimal constant)", yystack.l_mark[0].str);
		yyval.ival = 0;
	   } else {
		yyval.ival = strtoll(yystack.l_mark[0].str, NULL, 10);
	   }
	}
#line 4126 "compiler/glsl/glcpp/glcpp-parse.c"
break;
case 41:
#line 584 "../mesa/src/compiler/glsl/glcpp/glcpp-parse.y"
	{
		yyval.expression_value.value = yystack.l_mark[0].ival;
		yyval.expression_value.undefined_macro = NULL;
	}
#line 4134 "compiler/glsl/glcpp/glcpp-parse.c"
break;
case 42:
#line 588 "../mesa/src/compiler/glsl/glcpp/glcpp-parse.y"
	{
		yyval.expression_value.value = 0;
		if (parser->is_gles)
			yyval.expression_value.undefined_macro = linear_strdup(parser->linalloc, yystack.l_mark[0].str);
		else
			yyval.expression_value.undefined_macro = NULL;
	}
#line 4145 "compiler/glsl/glcpp/glcpp-parse.c"
break;
case 43:
#line 595 "../mesa/src/compiler/glsl/glcpp/glcpp-parse.y"
	{
		yyval.expression_value.value = yystack.l_mark[-2].expression_value.value || yystack.l_mark[0].expression_value.value;

		/* Short-circuit: Only flag undefined from right side
		 * if left side evaluates to false.
		 */
		if (yystack.l_mark[-2].expression_value.undefined_macro)
			yyval.expression_value.undefined_macro = yystack.l_mark[-2].expression_value.undefined_macro;
                else if (! yystack.l_mark[-2].expression_value.value)
			yyval.expression_value.undefined_macro = yystack.l_mark[0].expression_value.undefined_macro;
	}
#line 4160 "compiler/glsl/glcpp/glcpp-parse.c"
break;
case 44:
#line 606 "../mesa/src/compiler/glsl/glcpp/glcpp-parse.y"
	{
		yyval.expression_value.value = yystack.l_mark[-2].expression_value.value && yystack.l_mark[0].expression_value.value;

		/* Short-circuit: Only flag undefined from right-side
		 * if left side evaluates to true.
		 */
		if (yystack.l_mark[-2].expression_value.undefined_macro)
			yyval.expression_value.undefined_macro = yystack.l_mark[-2].expression_value.undefined_macro;
                else if (yystack.l_mark[-2].expression_value.value)
			yyval.expression_value.undefined_macro = yystack.l_mark[0].expression_value.undefined_macro;
	}
#line 4175 "compiler/glsl/glcpp/glcpp-parse.c"
break;
case 45:
#line 617 "../mesa/src/compiler/glsl/glcpp/glcpp-parse.y"
	{
		yyval.expression_value.value = yystack.l_mark[-2].expression_value.value | yystack.l_mark[0].expression_value.value;
		if (yystack.l_mark[-2].expression_value.undefined_macro)
			yyval.expression_value.undefined_macro = yystack.l_mark[-2].expression_value.undefined_macro;
                else
			yyval.expression_value.undefined_macro = yystack.l_mark[0].expression_value.undefined_macro;
	}
#line 4186 "compiler/glsl/glcpp/glcpp-parse.c"
break;
case 46:
#line 624 "../mesa/src/compiler/glsl/glcpp/glcpp-parse.y"
	{
		yyval.expression_value.value = yystack.l_mark[-2].expression_value.value ^ yystack.l_mark[0].expression_value.value;
		if (yystack.l_mark[-2].expression_value.undefined_macro)
			yyval.expression_value.undefined_macro = yystack.l_mark[-2].expression_value.undefined_macro;
                else
			yyval.expression_value.undefined_macro = yystack.l_mark[0].expression_value.undefined_macro;
	}
#line 4197 "compiler/glsl/glcpp/glcpp-parse.c"
break;
case 47:
#line 631 "../mesa/src/compiler/glsl/glcpp/glcpp-parse.y"
	{
		yyval.expression_value.value = yystack.l_mark[-2].expression_value.value & yystack.l_mark[0].expression_value.value;
		if (yystack.l_mark[-2].expression_value.undefined_macro)
			yyval.expression_value.undefined_macro = yystack.l_mark[-2].expression_value.undefined_macro;
                else
			yyval.expression_value.undefined_macro = yystack.l_mark[0].expression_value.undefined_macro;
	}
#line 4208 "compiler/glsl/glcpp/glcpp-parse.c"
break;
case 48:
#line 638 "../mesa/src/compiler/glsl/glcpp/glcpp-parse.y"
	{
		yyval.expression_value.value = yystack.l_mark[-2].expression_value.value != yystack.l_mark[0].expression_value.value;
		if (yystack.l_mark[-2].expression_value.undefined_macro)
			yyval.expression_value.undefined_macro = yystack.l_mark[-2].expression_value.undefined_macro;
                else
			yyval.expression_value.undefined_macro = yystack.l_mark[0].expression_value.undefined_macro;
	}
#line 4219 "compiler/glsl/glcpp/glcpp-parse.c"
break;
case 49:
#line 645 "../mesa/src/compiler/glsl/glcpp/glcpp-parse.y"
	{
		yyval.expression_value.value = yystack.l_mark[-2].expression_value.value == yystack.l_mark[0].expression_value.value;
		if (yystack.l_mark[-2].expression_value.undefined_macro)
			yyval.expression_value.undefined_macro = yystack.l_mark[-2].expression_value.undefined_macro;
                else
			yyval.expression_value.undefined_macro = yystack.l_mark[0].expression_value.undefined_macro;
	}
#line 4230 "compiler/glsl/glcpp/glcpp-parse.c"
break;
case 50:
#line 652 "../mesa/src/compiler/glsl/glcpp/glcpp-parse.y"
	{
		yyval.expression_value.value = yystack.l_mark[-2].expression_value.value >= yystack.l_mark[0].expression_value.value;
		if (yystack.l_mark[-2].expression_value.undefined_macro)
			yyval.expression_value.undefined_macro = yystack.l_mark[-2].expression_value.undefined_macro;
                else
			yyval.expression_value.undefined_macro = yystack.l_mark[0].expression_value.undefined_macro;
	}
#line 4241 "compiler/glsl/glcpp/glcpp-parse.c"
break;
case 51:
#line 659 "../mesa/src/compiler/glsl/glcpp/glcpp-parse.y"
	{
		yyval.expression_value.value = yystack.l_mark[-2].expression_value.value <= yystack.l_mark[0].expression_value.value;
		if (yystack.l_mark[-2].expression_value.undefined_macro)
			yyval.expression_value.undefined_macro = yystack.l_mark[-2].expression_value.undefined_macro;
                else
			yyval.expression_value.undefined_macro = yystack.l_mark[0].expression_value.undefined_macro;
	}
#line 4252 "compiler/glsl/glcpp/glcpp-parse.c"
break;
case 52:
#line 666 "../mesa/src/compiler/glsl/glcpp/glcpp-parse.y"
	{
		yyval.expression_value.value = yystack.l_mark[-2].expression_value.value > yystack.l_mark[0].expression_value.value;
		if (yystack.l_mark[-2].expression_value.undefined_macro)
			yyval.expression_value.undefined_macro = yystack.l_mark[-2].expression_value.undefined_macro;
                else
			yyval.expression_value.undefined_macro = yystack.l_mark[0].expression_value.undefined_macro;
	}
#line 4263 "compiler/glsl/glcpp/glcpp-parse.c"
break;
case 53:
#line 673 "../mesa/src/compiler/glsl/glcpp/glcpp-parse.y"
	{
		yyval.expression_value.value = yystack.l_mark[-2].expression_value.value < yystack.l_mark[0].expression_value.value;
		if (yystack.l_mark[-2].expression_value.undefined_macro)
			yyval.expression_value.undefined_macro = yystack.l_mark[-2].expression_value.undefined_macro;
                else
			yyval.expression_value.undefined_macro = yystack.l_mark[0].expression_value.undefined_macro;
	}
#line 4274 "compiler/glsl/glcpp/glcpp-parse.c"
break;
case 54:
#line 680 "../mesa/src/compiler/glsl/glcpp/glcpp-parse.y"
	{
		yyval.expression_value.value = yystack.l_mark[-2].expression_value.value >> yystack.l_mark[0].expression_value.value;
		if (yystack.l_mark[-2].expression_value.undefined_macro)
			yyval.expression_value.undefined_macro = yystack.l_mark[-2].expression_value.undefined_macro;
                else
			yyval.expression_value.undefined_macro = yystack.l_mark[0].expression_value.undefined_macro;
	}
#line 4285 "compiler/glsl/glcpp/glcpp-parse.c"
break;
case 55:
#line 687 "../mesa/src/compiler/glsl/glcpp/glcpp-parse.y"
	{
		yyval.expression_value.value = yystack.l_mark[-2].expression_value.value << yystack.l_mark[0].expression_value.value;
		if (yystack.l_mark[-2].expression_value.undefined_macro)
			yyval.expression_value.undefined_macro = yystack.l_mark[-2].expression_value.undefined_macro;
                else
			yyval.expression_value.undefined_macro = yystack.l_mark[0].expression_value.undefined_macro;
	}
#line 4296 "compiler/glsl/glcpp/glcpp-parse.c"
break;
case 56:
#line 694 "../mesa/src/compiler/glsl/glcpp/glcpp-parse.y"
	{
		yyval.expression_value.value = yystack.l_mark[-2].expression_value.value - yystack.l_mark[0].expression_value.value;
		if (yystack.l_mark[-2].expression_value.undefined_macro)
			yyval.expression_value.undefined_macro = yystack.l_mark[-2].expression_value.undefined_macro;
                else
			yyval.expression_value.undefined_macro = yystack.l_mark[0].expression_value.undefined_macro;
	}
#line 4307 "compiler/glsl/glcpp/glcpp-parse.c"
break;
case 57:
#line 701 "../mesa/src/compiler/glsl/glcpp/glcpp-parse.y"
	{
		yyval.expression_value.value = yystack.l_mark[-2].expression_value.value + yystack.l_mark[0].expression_value.value;
		if (yystack.l_mark[-2].expression_value.undefined_macro)
			yyval.expression_value.undefined_macro = yystack.l_mark[-2].expression_value.undefined_macro;
                else
			yyval.expression_value.undefined_macro = yystack.l_mark[0].expression_value.undefined_macro;
	}
#line 4318 "compiler/glsl/glcpp/glcpp-parse.c"
break;
case 58:
#line 708 "../mesa/src/compiler/glsl/glcpp/glcpp-parse.y"
	{
		if (yystack.l_mark[0].expression_value.value == 0) {
			yyerror (& yystack.p_mark[-2], parser,
				 "zero modulus in preprocessor directive");
		} else {
			yyval.expression_value.value = yystack.l_mark[-2].expression_value.value % yystack.l_mark[0].expression_value.value;
		}
		if (yystack.l_mark[-2].expression_value.undefined_macro)
			yyval.expression_value.undefined_macro = yystack.l_mark[-2].expression_value.undefined_macro;
                else
			yyval.expression_value.undefined_macro = yystack.l_mark[0].expression_value.undefined_macro;
	}
#line 4334 "compiler/glsl/glcpp/glcpp-parse.c"
break;
case 59:
#line 720 "../mesa/src/compiler/glsl/glcpp/glcpp-parse.y"
	{
		if (yystack.l_mark[0].expression_value.value == 0) {
			yyerror (& yystack.p_mark[-2], parser,
				 "division by 0 in preprocessor directive");
		} else {
			yyval.expression_value.value = yystack.l_mark[-2].expression_value.value / yystack.l_mark[0].expression_value.value;
		}
		if (yystack.l_mark[-2].expression_value.undefined_macro)
			yyval.expression_value.undefined_macro = yystack.l_mark[-2].expression_value.undefined_macro;
                else
			yyval.expression_value.undefined_macro = yystack.l_mark[0].expression_value.undefined_macro;
	}
#line 4350 "compiler/glsl/glcpp/glcpp-parse.c"
break;
case 60:
#line 732 "../mesa/src/compiler/glsl/glcpp/glcpp-parse.y"
	{
		yyval.expression_value.value = yystack.l_mark[-2].expression_value.value * yystack.l_mark[0].expression_value.value;
		if (yystack.l_mark[-2].expression_value.undefined_macro)
			yyval.expression_value.undefined_macro = yystack.l_mark[-2].expression_value.undefined_macro;
                else
			yyval.expression_value.undefined_macro = yystack.l_mark[0].expression_value.undefined_macro;
	}
#line 4361 "compiler/glsl/glcpp/glcpp-parse.c"
break;
case 61:
#line 739 "../mesa/src/compiler/glsl/glcpp/glcpp-parse.y"
	{
		yyval.expression_value.value = ! yystack.l_mark[0].expression_value.value;
		yyval.expression_value.undefined_macro = yystack.l_mark[0].expression_value.undefined_macro;
	}
#line 4369 "compiler/glsl/glcpp/glcpp-parse.c"
break;
case 62:
#line 743 "../mesa/src/compiler/glsl/glcpp/glcpp-parse.y"
	{
		yyval.expression_value.value = ~ yystack.l_mark[0].expression_value.value;
		yyval.expression_value.undefined_macro = yystack.l_mark[0].expression_value.undefined_macro;
	}
#line 4377 "compiler/glsl/glcpp/glcpp-parse.c"
break;
case 63:
#line 747 "../mesa/src/compiler/glsl/glcpp/glcpp-parse.y"
	{
		yyval.expression_value.value = - yystack.l_mark[0].expression_value.value;
		yyval.expression_value.undefined_macro = yystack.l_mark[0].expression_value.undefined_macro;
	}
#line 4385 "compiler/glsl/glcpp/glcpp-parse.c"
break;
case 64:
#line 751 "../mesa/src/compiler/glsl/glcpp/glcpp-parse.y"
	{
		yyval.expression_value.value = + yystack.l_mark[0].expression_value.value;
		yyval.expression_value.undefined_macro = yystack.l_mark[0].expression_value.undefined_macro;
	}
#line 4393 "compiler/glsl/glcpp/glcpp-parse.c"
break;
case 65:
#line 755 "../mesa/src/compiler/glsl/glcpp/glcpp-parse.y"
	{
		yyval.expression_value = yystack.l_mark[-1].expression_value;
	}
#line 4400 "compiler/glsl/glcpp/glcpp-parse.c"
break;
case 66:
#line 761 "../mesa/src/compiler/glsl/glcpp/glcpp-parse.y"
	{
		yyval.string_list = _string_list_create (parser);
		_string_list_append_item (parser, yyval.string_list, yystack.l_mark[0].str);
	}
#line 4408 "compiler/glsl/glcpp/glcpp-parse.c"
break;
case 67:
#line 765 "../mesa/src/compiler/glsl/glcpp/glcpp-parse.y"
	{
		yyval.string_list = yystack.l_mark[-2].string_list;	
		_string_list_append_item (parser, yyval.string_list, yystack.l_mark[0].str);
	}
#line 4416 "compiler/glsl/glcpp/glcpp-parse.c"
break;
case 68:
#line 772 "../mesa/src/compiler/glsl/glcpp/glcpp-parse.y"
	{ yyval.token_list = NULL; }
#line 4421 "compiler/glsl/glcpp/glcpp-parse.c"
break;
case 70:
#line 777 "../mesa/src/compiler/glsl/glcpp/glcpp-parse.y"
	{ yyval.token_list = NULL; }
#line 4426 "compiler/glsl/glcpp/glcpp-parse.c"
break;
case 73:
#line 783 "../mesa/src/compiler/glsl/glcpp/glcpp-parse.y"
	{
		if (parser->gl_ctx->Const.AllowExtraPPTokens)
			glcpp_warning(&yystack.p_mark[0], parser, "extra tokens at end of directive");
		else
			glcpp_error(&yystack.p_mark[0], parser, "extra tokens at end of directive");
	}
#line 4436 "compiler/glsl/glcpp/glcpp-parse.c"
break;
case 74:
#line 792 "../mesa/src/compiler/glsl/glcpp/glcpp-parse.y"
	{
		parser->space_tokens = 1;
		yyval.token_list = _token_list_create (parser);
		_token_list_append (parser, yyval.token_list, yystack.l_mark[0].token);
	}
#line 4445 "compiler/glsl/glcpp/glcpp-parse.c"
break;
case 75:
#line 797 "../mesa/src/compiler/glsl/glcpp/glcpp-parse.y"
	{
		yyval.token_list = yystack.l_mark[-1].token_list;
		_token_list_append (parser, yyval.token_list, yystack.l_mark[0].token);
	}
#line 4453 "compiler/glsl/glcpp/glcpp-parse.c"
break;
case 76:
#line 804 "../mesa/src/compiler/glsl/glcpp/glcpp-parse.y"
	{
		yyval.token = _token_create_str (parser, IDENTIFIER, yystack.l_mark[0].str);
		yyval.token->location = yylloc;
	}
#line 4461 "compiler/glsl/glcpp/glcpp-parse.c"
break;
case 77:
#line 808 "../mesa/src/compiler/glsl/glcpp/glcpp-parse.y"
	{
		yyval.token = _token_create_str (parser, INTEGER_STRING, yystack.l_mark[0].str);
		yyval.token->location = yylloc;
	}
#line 4469 "compiler/glsl/glcpp/glcpp-parse.c"
break;
case 78:
#line 812 "../mesa/src/compiler/glsl/glcpp/glcpp-parse.y"
	{
		yyval.token = _token_create_str (parser, PATH, yystack.l_mark[0].str);
		yyval.token->location = yylloc;
	}
#line 4477 "compiler/glsl/glcpp/glcpp-parse.c"
break;
case 79:
#line 816 "../mesa/src/compiler/glsl/glcpp/glcpp-parse.y"
	{
		yyval.token = _token_create_ival (parser, yystack.l_mark[0].ival, yystack.l_mark[0].ival);
		yyval.token->location = yylloc;
	}
#line 4485 "compiler/glsl/glcpp/glcpp-parse.c"
break;
case 80:
#line 820 "../mesa/src/compiler/glsl/glcpp/glcpp-parse.y"
	{
		yyval.token = _token_create_ival (parser, DEFINED, DEFINED);
		yyval.token->location = yylloc;
	}
#line 4493 "compiler/glsl/glcpp/glcpp-parse.c"
break;
case 81:
#line 824 "../mesa/src/compiler/glsl/glcpp/glcpp-parse.y"
	{
		yyval.token = _token_create_str (parser, OTHER, yystack.l_mark[0].str);
		yyval.token->location = yylloc;
	}
#line 4501 "compiler/glsl/glcpp/glcpp-parse.c"
break;
case 82:
#line 828 "../mesa/src/compiler/glsl/glcpp/glcpp-parse.y"
	{
		yyval.token = _token_create_ival (parser, SPACE, SPACE);
		yyval.token->location = yylloc;
	}
#line 4509 "compiler/glsl/glcpp/glcpp-parse.c"
break;
case 83:
#line 835 "../mesa/src/compiler/glsl/glcpp/glcpp-parse.y"
	{ yyval.ival = '['; }
#line 4514 "compiler/glsl/glcpp/glcpp-parse.c"
break;
case 84:
#line 836 "../mesa/src/compiler/glsl/glcpp/glcpp-parse.y"
	{ yyval.ival = ']'; }
#line 4519 "compiler/glsl/glcpp/glcpp-parse.c"
break;
case 85:
#line 837 "../mesa/src/compiler/glsl/glcpp/glcpp-parse.y"
	{ yyval.ival = '('; }
#line 4524 "compiler/glsl/glcpp/glcpp-parse.c"
break;
case 86:
#line 838 "../mesa/src/compiler/glsl/glcpp/glcpp-parse.y"
	{ yyval.ival = ')'; }
#line 4529 "compiler/glsl/glcpp/glcpp-parse.c"
break;
case 87:
#line 839 "../mesa/src/compiler/glsl/glcpp/glcpp-parse.y"
	{ yyval.ival = '{'; }
#line 4534 "compiler/glsl/glcpp/glcpp-parse.c"
break;
case 88:
#line 840 "../mesa/src/compiler/glsl/glcpp/glcpp-parse.y"
	{ yyval.ival = '}'; }
#line 4539 "compiler/glsl/glcpp/glcpp-parse.c"
break;
case 89:
#line 841 "../mesa/src/compiler/glsl/glcpp/glcpp-parse.y"
	{ yyval.ival = '.'; }
#line 4544 "compiler/glsl/glcpp/glcpp-parse.c"
break;
case 90:
#line 842 "../mesa/src/compiler/glsl/glcpp/glcpp-parse.y"
	{ yyval.ival = '&'; }
#line 4549 "compiler/glsl/glcpp/glcpp-parse.c"
break;
case 91:
#line 843 "../mesa/src/compiler/glsl/glcpp/glcpp-parse.y"
	{ yyval.ival = '*'; }
#line 4554 "compiler/glsl/glcpp/glcpp-parse.c"
break;
case 92:
#line 844 "../mesa/src/compiler/glsl/glcpp/glcpp-parse.y"
	{ yyval.ival = '+'; }
#line 4559 "compiler/glsl/glcpp/glcpp-parse.c"
break;
case 93:
#line 845 "../mesa/src/compiler/glsl/glcpp/glcpp-parse.y"
	{ yyval.ival = '-'; }
#line 4564 "compiler/glsl/glcpp/glcpp-parse.c"
break;
case 94:
#line 846 "../mesa/src/compiler/glsl/glcpp/glcpp-parse.y"
	{ yyval.ival = '~'; }
#line 4569 "compiler/glsl/glcpp/glcpp-parse.c"
break;
case 95:
#line 847 "../mesa/src/compiler/glsl/glcpp/glcpp-parse.y"
	{ yyval.ival = '!'; }
#line 4574 "compiler/glsl/glcpp/glcpp-parse.c"
break;
case 96:
#line 848 "../mesa/src/compiler/glsl/glcpp/glcpp-parse.y"
	{ yyval.ival = '/'; }
#line 4579 "compiler/glsl/glcpp/glcpp-parse.c"
break;
case 97:
#line 849 "../mesa/src/compiler/glsl/glcpp/glcpp-parse.y"
	{ yyval.ival = '%'; }
#line 4584 "compiler/glsl/glcpp/glcpp-parse.c"
break;
case 98:
#line 850 "../mesa/src/compiler/glsl/glcpp/glcpp-parse.y"
	{ yyval.ival = LEFT_SHIFT; }
#line 4589 "compiler/glsl/glcpp/glcpp-parse.c"
break;
case 99:
#line 851 "../mesa/src/compiler/glsl/glcpp/glcpp-parse.y"
	{ yyval.ival = RIGHT_SHIFT; }
#line 4594 "compiler/glsl/glcpp/glcpp-parse.c"
break;
case 100:
#line 852 "../mesa/src/compiler/glsl/glcpp/glcpp-parse.y"
	{ yyval.ival = '<'; }
#line 4599 "compiler/glsl/glcpp/glcpp-parse.c"
break;
case 101:
#line 853 "../mesa/src/compiler/glsl/glcpp/glcpp-parse.y"
	{ yyval.ival = '>'; }
#line 4604 "compiler/glsl/glcpp/glcpp-parse.c"
break;
case 102:
#line 854 "../mesa/src/compiler/glsl/glcpp/glcpp-parse.y"
	{ yyval.ival = LESS_OR_EQUAL; }
#line 4609 "compiler/glsl/glcpp/glcpp-parse.c"
break;
case 103:
#line 855 "../mesa/src/compiler/glsl/glcpp/glcpp-parse.y"
	{ yyval.ival = GREATER_OR_EQUAL; }
#line 4614 "compiler/glsl/glcpp/glcpp-parse.c"
break;
case 104:
#line 856 "../mesa/src/compiler/glsl/glcpp/glcpp-parse.y"
	{ yyval.ival = EQUAL; }
#line 4619 "compiler/glsl/glcpp/glcpp-parse.c"
break;
case 105:
#line 857 "../mesa/src/compiler/glsl/glcpp/glcpp-parse.y"
	{ yyval.ival = NOT_EQUAL; }
#line 4624 "compiler/glsl/glcpp/glcpp-parse.c"
break;
case 106:
#line 858 "../mesa/src/compiler/glsl/glcpp/glcpp-parse.y"
	{ yyval.ival = '^'; }
#line 4629 "compiler/glsl/glcpp/glcpp-parse.c"
break;
case 107:
#line 859 "../mesa/src/compiler/glsl/glcpp/glcpp-parse.y"
	{ yyval.ival = '|'; }
#line 4634 "compiler/glsl/glcpp/glcpp-parse.c"
break;
case 108:
#line 860 "../mesa/src/compiler/glsl/glcpp/glcpp-parse.y"
	{ yyval.ival = AND; }
#line 4639 "compiler/glsl/glcpp/glcpp-parse.c"
break;
case 109:
#line 861 "../mesa/src/compiler/glsl/glcpp/glcpp-parse.y"
	{ yyval.ival = OR; }
#line 4644 "compiler/glsl/glcpp/glcpp-parse.c"
break;
case 110:
#line 862 "../mesa/src/compiler/glsl/glcpp/glcpp-parse.y"
	{ yyval.ival = ';'; }
#line 4649 "compiler/glsl/glcpp/glcpp-parse.c"
break;
case 111:
#line 863 "../mesa/src/compiler/glsl/glcpp/glcpp-parse.y"
	{ yyval.ival = ','; }
#line 4654 "compiler/glsl/glcpp/glcpp-parse.c"
break;
case 112:
#line 864 "../mesa/src/compiler/glsl/glcpp/glcpp-parse.y"
	{ yyval.ival = '='; }
#line 4659 "compiler/glsl/glcpp/glcpp-parse.c"
break;
case 113:
#line 865 "../mesa/src/compiler/glsl/glcpp/glcpp-parse.y"
	{ yyval.ival = PASTE; }
#line 4664 "compiler/glsl/glcpp/glcpp-parse.c"
break;
case 114:
#line 866 "../mesa/src/compiler/glsl/glcpp/glcpp-parse.y"
	{ yyval.ival = PLUS_PLUS; }
#line 4669 "compiler/glsl/glcpp/glcpp-parse.c"
break;
case 115:
#line 867 "../mesa/src/compiler/glsl/glcpp/glcpp-parse.y"
	{ yyval.ival = MINUS_MINUS; }
#line 4674 "compiler/glsl/glcpp/glcpp-parse.c"
break;
#line 4676 "compiler/glsl/glcpp/glcpp-parse.c"
    default:
        break;
    }
    yystack.s_mark -= yym;
    yystate = *yystack.s_mark;
    yystack.l_mark -= yym;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
    yystack.p_mark -= yym;
#endif
    yym = yylhs[yyn];
    if (yystate == 0 && yym == 0)
    {
#if YYDEBUG
        if (yydebug)
        {
            fprintf(stderr, "%s[%d]: after reduction, ", YYDEBUGSTR, yydepth);
#ifdef YYSTYPE_TOSTRING
#if YYBTYACC
            if (!yytrial)
#endif /* YYBTYACC */
                fprintf(stderr, "result is <%s>, ", YYSTYPE_TOSTRING(yystos[YYFINAL], yyval));
#endif
            fprintf(stderr, "shifting from state 0 to final state %d\n", YYFINAL);
        }
#endif
        yystate = YYFINAL;
        *++yystack.s_mark = YYFINAL;
        *++yystack.l_mark = yyval;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
        *++yystack.p_mark = yyloc;
#endif
        if (yychar < 0)
        {
#if YYBTYACC
            do {
            if (yylvp < yylve)
            {
                /* we're currently re-reading tokens */
                yylval = *yylvp++;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
                yylloc = *yylpp++;
#endif
                yychar = *yylexp++;
                break;
            }
            if (yyps->save)
            {
                /* in trial mode; save scanner results for future parse attempts */
                if (yylvp == yylvlim)
                {   /* Enlarge lexical value queue */
                    size_t p = (size_t) (yylvp - yylvals);
                    size_t s = (size_t) (yylvlim - yylvals);

                    s += YYLVQUEUEGROWTH;
                    if ((yylexemes = (YYINT *)realloc(yylexemes, s * sizeof(YYINT))) == NULL)
                        goto yyenomem;
                    if ((yylvals   = (YYSTYPE *)realloc(yylvals, s * sizeof(YYSTYPE))) == NULL)
                        goto yyenomem;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
                    if ((yylpsns   = (YYLTYPE *)realloc(yylpsns, s * sizeof(YYLTYPE))) == NULL)
                        goto yyenomem;
#endif
                    yylvp   = yylve = yylvals + p;
                    yylvlim = yylvals + s;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
                    yylpp   = yylpe = yylpsns + p;
                    yylplim = yylpsns + s;
#endif
                    yylexp  = yylexemes + p;
                }
                *yylexp = (YYINT) YYLEX;
                *yylvp++ = yylval;
                yylve++;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
                *yylpp++ = yylloc;
                yylpe++;
#endif
                yychar = *yylexp++;
                break;
            }
            /* normal operation, no conflict encountered */
#endif /* YYBTYACC */
            yychar = YYLEX;
#if YYBTYACC
            } while (0);
#endif /* YYBTYACC */
            if (yychar < 0) yychar = YYEOF;
#if YYDEBUG
            if (yydebug)
            {
                if ((yys = yyname[YYTRANSLATE(yychar)]) == NULL) yys = yyname[YYUNDFTOKEN];
                fprintf(stderr, "%s[%d]: state %d, reading token %d (%s)\n",
                                YYDEBUGSTR, yydepth, YYFINAL, yychar, yys);
            }
#endif
        }
        if (yychar == YYEOF) goto yyaccept;
        goto yyloop;
    }
    if (((yyn = yygindex[yym]) != 0) && (yyn += yystate) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == (YYINT) yystate)
        yystate = yytable[yyn];
    else
        yystate = yydgoto[yym];
#if YYDEBUG
    if (yydebug)
    {
        fprintf(stderr, "%s[%d]: after reduction, ", YYDEBUGSTR, yydepth);
#ifdef YYSTYPE_TOSTRING
#if YYBTYACC
        if (!yytrial)
#endif /* YYBTYACC */
            fprintf(stderr, "result is <%s>, ", YYSTYPE_TOSTRING(yystos[yystate], yyval));
#endif
        fprintf(stderr, "shifting from state %d to state %d\n", *yystack.s_mark, yystate);
    }
#endif
    if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM) goto yyoverflow;
    *++yystack.s_mark = (YYINT) yystate;
    *++yystack.l_mark = yyval;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
    *++yystack.p_mark = yyloc;
#endif
    goto yyloop;
#if YYBTYACC

    /* Reduction declares that this path is valid. Set yypath and do a full parse */
yyvalid:
    if (yypath) YYABORT;
    while (yyps->save)
    {
        YYParseState *save = yyps->save;
        yyps->save = save->save;
        save->save = yypath;
        yypath = save;
    }
#if YYDEBUG
    if (yydebug)
        fprintf(stderr, "%s[%d]: state %d, CONFLICT trial successful, backtracking to state %d, %d tokens\n",
                        YYDEBUGSTR, yydepth, yystate, yypath->state, (int)(yylvp - yylvals - yypath->lexeme));
#endif
    if (yyerrctx)
    {
        yyFreeState(yyerrctx);
        yyerrctx = NULL;
    }
    yylvp          = yylvals + yypath->lexeme;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
    yylpp          = yylpsns + yypath->lexeme;
#endif
    yylexp         = yylexemes + yypath->lexeme;
    yychar         = YYEMPTY;
    yystack.s_mark = yystack.s_base + (yypath->yystack.s_mark - yypath->yystack.s_base);
    memcpy (yystack.s_base, yypath->yystack.s_base, (size_t) (yystack.s_mark - yystack.s_base + 1) * sizeof(YYINT));
    yystack.l_mark = yystack.l_base + (yypath->yystack.l_mark - yypath->yystack.l_base);
    memcpy (yystack.l_base, yypath->yystack.l_base, (size_t) (yystack.l_mark - yystack.l_base + 1) * sizeof(YYSTYPE));
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
    yystack.p_mark = yystack.p_base + (yypath->yystack.p_mark - yypath->yystack.p_base);
    memcpy (yystack.p_base, yypath->yystack.p_base, (size_t) (yystack.p_mark - yystack.p_base + 1) * sizeof(YYLTYPE));
#endif
    yystate        = yypath->state;
    goto yyloop;
#endif /* YYBTYACC */

yyoverflow:
    YYERROR_CALL("yacc stack overflow");
#if YYBTYACC
    goto yyabort_nomem;
yyenomem:
    YYERROR_CALL("memory exhausted");
yyabort_nomem:
#endif /* YYBTYACC */
    yyresult = 2;
    goto yyreturn;

yyabort:
    yyresult = 1;
    goto yyreturn;

yyaccept:
#if YYBTYACC
    if (yyps->save) goto yyvalid;
#endif /* YYBTYACC */
    yyresult = 0;

yyreturn:
#if defined(YYDESTRUCT_CALL)
    if (yychar != YYEOF && yychar != YYEMPTY)
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
        YYDESTRUCT_CALL("cleanup: discarding token", yychar, &yylval, &yylloc);
#else
        YYDESTRUCT_CALL("cleanup: discarding token", yychar, &yylval);
#endif /* defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED) */

    {
        YYSTYPE *pv;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
        YYLTYPE *pp;

        for (pv = yystack.l_base, pp = yystack.p_base; pv <= yystack.l_mark; ++pv, ++pp)
             YYDESTRUCT_CALL("cleanup: discarding state",
                             yystos[*(yystack.s_base + (pv - yystack.l_base))], pv, pp);
#else
        for (pv = yystack.l_base; pv <= yystack.l_mark; ++pv)
             YYDESTRUCT_CALL("cleanup: discarding state",
                             yystos[*(yystack.s_base + (pv - yystack.l_base))], pv);
#endif /* defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED) */
    }
#endif /* defined(YYDESTRUCT_CALL) */

#if YYBTYACC
    if (yyerrctx)
    {
        yyFreeState(yyerrctx);
        yyerrctx = NULL;
    }
    while (yyps)
    {
        YYParseState *save = yyps;
        yyps = save->save;
        save->save = NULL;
        yyFreeState(save);
    }
    while (yypath)
    {
        YYParseState *save = yypath;
        yypath = save->save;
        save->save = NULL;
        yyFreeState(save);
    }
#endif /* YYBTYACC */
    yyfreestack(&yystack);
    return (yyresult);
}
