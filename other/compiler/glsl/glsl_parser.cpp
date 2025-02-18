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
#define yyparse    _mesa_glsl_parse
#endif /* yyparse */

#ifndef yylex
#define yylex      _mesa_glsl_lex
#endif /* yylex */

#ifndef yyerror
#define yyerror    _mesa_glsl_error
#endif /* yyerror */

#ifndef yychar
#define yychar     _mesa_glsl_char
#endif /* yychar */

#ifndef yyval
#define yyval      _mesa_glsl_val
#endif /* yyval */

#ifndef yylval
#define yylval     _mesa_glsl_lval
#endif /* yylval */

#ifndef yydebug
#define yydebug    _mesa_glsl_debug
#endif /* yydebug */

#ifndef yynerrs
#define yynerrs    _mesa_glsl_nerrs
#endif /* yynerrs */

#ifndef yyerrflag
#define yyerrflag  _mesa_glsl_errflag
#endif /* yyerrflag */

#ifndef yylhs
#define yylhs      _mesa_glsl_lhs
#endif /* yylhs */

#ifndef yylen
#define yylen      _mesa_glsl_len
#endif /* yylen */

#ifndef yydefred
#define yydefred   _mesa_glsl_defred
#endif /* yydefred */

#ifndef yystos
#define yystos     _mesa_glsl_stos
#endif /* yystos */

#ifndef yydgoto
#define yydgoto    _mesa_glsl_dgoto
#endif /* yydgoto */

#ifndef yysindex
#define yysindex   _mesa_glsl_sindex
#endif /* yysindex */

#ifndef yyrindex
#define yyrindex   _mesa_glsl_rindex
#endif /* yyrindex */

#ifndef yygindex
#define yygindex   _mesa_glsl_gindex
#endif /* yygindex */

#ifndef yytable
#define yytable    _mesa_glsl_table
#endif /* yytable */

#ifndef yycheck
#define yycheck    _mesa_glsl_check
#endif /* yycheck */

#ifndef yyname
#define yyname     _mesa_glsl_name
#endif /* yyname */

#ifndef yyrule
#define yyrule     _mesa_glsl_rule
#endif /* yyrule */

#ifndef yyloc
#define yyloc      _mesa_glsl_loc
#endif /* yyloc */

#ifndef yylloc
#define yylloc     _mesa_glsl_lloc
#endif /* yylloc */

#if YYBTYACC

#ifndef yycindex
#define yycindex   _mesa_glsl_cindex
#endif /* yycindex */

#ifndef yyctable
#define yyctable   _mesa_glsl_ctable
#endif /* yyctable */

#endif /* YYBTYACC */

#define YYPREFIX "_mesa_glsl_"

#define YYPURE 1

#line 2 "../mesa/src/compiler/glsl/glsl_parser.yy"
/*
 * Copyright © 2008, 2009 Intel Corporation
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
#ifndef _MSC_VER
#include <strings.h>
#endif
#include <assert.h>

#include "ast.h"
#include "glsl_parser_extras.h"
#include "compiler/glsl_types.h"
#include "util/u_string.h"
#include "util/format/u_format.h"
#include "main/consts_exts.h"

#ifdef _MSC_VER
#pragma warning( disable : 4065 ) /* switch statement contains 'default' but no 'case' labels*/
#endif

#undef yyerror

static void yyerror(YYLTYPE *loc, _mesa_glsl_parse_state *st, const char *msg)
{
   _mesa_glsl_error(loc, st, "%s", msg);
}

static int
_mesa_glsl_lex(YYSTYPE *val, YYLTYPE *loc, _mesa_glsl_parse_state *state)
{
   return _mesa_glsl_lexer_lex(val, loc, state->scanner);
}

static bool match_layout_qualifier(const char *s1, const char *s2,
                                   _mesa_glsl_parse_state *state)
{
   /* From the GLSL 1.50 spec, section 4.3.8 (Layout Qualifiers):
    *
    *     "The tokens in any layout-qualifier-id-list ... are not case
    *     sensitive, unless explicitly noted otherwise."
    *
    * The text "unless explicitly noted otherwise" appears to be
    * vacuous--no desktop GLSL spec (up through GLSL 4.40) notes
    * otherwise.
    *
    * However, the GLSL ES 3.00 spec says, in section 4.3.8 (Layout
    * Qualifiers):
    *
    *     "As for other identifiers, they are case sensitive."
    *
    * So we need to do a case-sensitive or a case-insensitive match,
    * depending on whether we are compiling for GLSL ES.
    */
   if (state->es_shader)
      return strcmp(s1, s2);
   else
      return strcasecmp(s1, s2);
}
#ifdef YYSTYPE
#undef  YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
#endif
#ifndef YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
#line 101 "../mesa/src/compiler/glsl/glsl_parser.yy"
typedef union YYSTYPE {
   int n;
   int64_t n64;
   float real;
   double dreal;
   const char *identifier;

   struct ast_type_qualifier type_qualifier;

   ast_node *node;
   ast_type_specifier *type_specifier;
   ast_array_specifier *array_specifier;
   ast_fully_specified_type *fully_specified_type;
   ast_function *function;
   ast_parameter_declarator *parameter_declarator;
   ast_function_definition *function_definition;
   ast_compound_statement *compound_statement;
   ast_expression *expression;
   ast_declarator_list *declarator_list;
   ast_struct_specifier *struct_specifier;
   ast_declaration *declaration;
   ast_switch_body *switch_body;
   ast_case_label *case_label;
   ast_case_label_list *case_label_list;
   ast_case_statement *case_statement;
   ast_case_statement_list *case_statement_list;
   ast_interface_block *interface_block;
   ast_subroutine_list *subroutine_list;
   struct {
      ast_node *cond;
      ast_expression *rest;
   } for_rest_statement;

   struct {
      ast_node *then_statement;
      ast_node *else_statement;
   } selection_rest_statement;

   const glsl_type *type;
} YYSTYPE;
#endif /* !YYSTYPE_IS_DECLARED */
#line 257 "compiler/glsl/glsl_parser.cpp"

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
# define YYPARSE_DECL() yyparse(struct _mesa_glsl_parse_state *state)
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
# define YYLEX_DECL() yylex(YYSTYPE *yylval, YYLTYPE *yylloc, struct _mesa_glsl_parse_state *state)
# define YYLEX yylex(&yylval, &yylloc, state)
#endif

/* Parameters sent to yyerror. */
#ifndef YYERROR_DECL
#define YYERROR_DECL() yyerror(YYLTYPE *loc, struct _mesa_glsl_parse_state *state, const char *s)
#endif
#ifndef YYERROR_CALL
#define YYERROR_CALL(msg) yyerror(&yylloc, state, msg)
#endif

extern int YYPARSE_DECL();

#define ATTRIBUTE 257
#define CONST_TOK 258
#define BASIC_TYPE_TOK 259
#define BREAK 260
#define BUFFER 261
#define CONTINUE 262
#define DO 263
#define ELSE 264
#define FOR 265
#define IF 266
#define DEMOTE 267
#define DISCARD 268
#define RETURN 269
#define SWITCH 270
#define CASE 271
#define DEFAULT 272
#define CENTROID 273
#define IN_TOK 274
#define OUT_TOK 275
#define INOUT_TOK 276
#define UNIFORM 277
#define VARYING 278
#define SAMPLE 279
#define NOPERSPECTIVE 280
#define FLAT 281
#define SMOOTH 282
#define IMAGE1DSHADOW 283
#define IMAGE2DSHADOW 284
#define IMAGE1DARRAYSHADOW 285
#define IMAGE2DARRAYSHADOW 286
#define COHERENT 287
#define VOLATILE 288
#define RESTRICT 289
#define READONLY 290
#define WRITEONLY 291
#define SHARED 292
#define STRUCT 293
#define VOID_TOK 294
#define WHILE 295
#define IDENTIFIER 296
#define TYPE_IDENTIFIER 297
#define NEW_IDENTIFIER 298
#define FLOATCONSTANT 299
#define FLOAT16CONSTANT 300
#define DOUBLECONSTANT 301
#define INTCONSTANT 302
#define UINTCONSTANT 303
#define BOOLCONSTANT 304
#define INT64CONSTANT 305
#define UINT64CONSTANT 306
#define FIELD_SELECTION 307
#define LEFT_OP 308
#define RIGHT_OP 309
#define INC_OP 310
#define DEC_OP 311
#define LE_OP 312
#define GE_OP 313
#define EQ_OP 314
#define NE_OP 315
#define AND_OP 316
#define OR_OP 317
#define XOR_OP 318
#define MUL_ASSIGN 319
#define DIV_ASSIGN 320
#define ADD_ASSIGN 321
#define MOD_ASSIGN 322
#define LEFT_ASSIGN 323
#define RIGHT_ASSIGN 324
#define AND_ASSIGN 325
#define XOR_ASSIGN 326
#define OR_ASSIGN 327
#define SUB_ASSIGN 328
#define INVARIANT 329
#define PRECISE 330
#define LOWP 331
#define MEDIUMP 332
#define HIGHP 333
#define SUPERP 334
#define PRECISION 335
#define VERSION_TOK 336
#define EXTENSION 337
#define LINE 338
#define COLON 339
#define EOL 340
#define INTERFACE_TOK 341
#define OUTPUT 342
#define PRAGMA_DEBUG_ON 343
#define PRAGMA_DEBUG_OFF 344
#define PRAGMA_OPTIMIZE_ON 345
#define PRAGMA_OPTIMIZE_OFF 346
#define PRAGMA_WARNING_ON 347
#define PRAGMA_WARNING_OFF 348
#define PRAGMA_INVARIANT_ALL 349
#define LAYOUT_TOK 350
#define DOT_TOK 351
#define ASM 352
#define CLASS 353
#define UNION 354
#define ENUM 355
#define TYPEDEF 356
#define TEMPLATE 357
#define THIS 358
#define PACKED_TOK 359
#define GOTO 360
#define INLINE_TOK 361
#define NOINLINE 362
#define PUBLIC_TOK 363
#define STATIC 364
#define EXTERN 365
#define EXTERNAL 366
#define LONG_TOK 367
#define SHORT_TOK 368
#define HALF 369
#define FIXED_TOK 370
#define UNSIGNED 371
#define INPUT_TOK 372
#define HVEC2 373
#define HVEC3 374
#define HVEC4 375
#define FVEC2 376
#define FVEC3 377
#define FVEC4 378
#define SAMPLER3DRECT 379
#define SIZEOF 380
#define CAST 381
#define NAMESPACE 382
#define USING 383
#define RESOURCE 384
#define PATCH 385
#define SUBROUTINE 386
#define ERROR_TOK 387
#define COMMON 388
#define PARTITION 389
#define ACTIVE 390
#define FILTER 391
#define ROW_MAJOR 392
#define THEN 393
#define YYERRCODE 256
typedef int YYINT;
static const YYINT _mesa_glsl_lhs[] = {                  -1,
  107,    0,  104,  104,  104,   68,   68,   68,   68,   68,
   68,   68,  105,  105,    1,    1,    1,  108,  106,  106,
  106,    3,    3,   40,   40,   40,   40,   40,   40,   40,
   40,   40,   40,   57,   57,   57,   57,   57,   57,   56,
   63,   62,   61,   61,   59,   59,   58,   58,   60,   66,
   66,   54,   54,   54,   54,   65,   65,   65,   65,   53,
   53,   53,   53,   52,   52,   52,   51,   51,   51,   50,
   50,   50,   50,   50,   49,   49,   49,   48,   48,   47,
   47,   46,   46,   45,   45,   44,   44,   43,   43,   42,
   42,   41,   41,   64,   64,   64,   64,   64,   64,   64,
   64,   64,   64,   64,   39,   39,   55,   73,   73,   73,
   73,   25,   28,   28,   27,   27,   26,   29,   29,   29,
   30,   30,   31,   31,   31,   31,   31,   31,   32,   32,
   32,   33,   69,   69,   69,   69,   69,   70,   70,   70,
   70,   70,   70,   70,   24,   24,   12,   13,   13,   14,
   14,   14,   15,   15,   15,   17,   17,   18,   18,   11,
   11,   11,    8,    8,    8,    8,    8,    8,    8,    8,
    8,    8,    8,    8,    8,    8,    8,    8,    8,    8,
    9,    9,    9,   10,   10,   10,   10,   10,   10,   10,
   10,   10,   16,   16,   16,   16,   16,   22,   22,   22,
   22,   20,   20,   21,   21,   21,   23,   23,   23,    7,
    7,    7,   79,   79,   80,   80,   81,   83,   83,   82,
   82,   71,   71,   71,   72,   72,   74,    4,    4,    6,
    6,    6,    6,    6,    6,    6,   36,  109,   36,   37,
   37,   35,   35,    5,    5,    5,   38,   38,   86,   87,
   87,   95,   95,   88,   89,   89,   91,   91,   90,   90,
   92,   92,   93,   93,   94,   94,   94,   97,   97,   96,
   96,   98,   98,   75,   75,   75,   75,   75,   76,   67,
   67,   67,   67,   67,   34,   77,   77,   77,   78,   19,
   19,   19,   19,   19,    2,    2,    2,   84,   84,   85,
  100,  100,  101,  101,  102,  102,  103,  103,   99,   99,
   99,   99,
};
static const YYINT _mesa_glsl_len[] = {                   2,
    0,    4,    0,    3,    4,    2,    2,    2,    2,    2,
    2,    2,    0,    2,    1,    1,    1,    5,    1,    2,
    2,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    3,    1,    4,    1,    3,    2,    2,    1,
    1,    1,    2,    2,    2,    1,    2,    3,    2,    1,
    1,    1,    2,    2,    2,    1,    1,    1,    1,    1,
    3,    3,    3,    1,    3,    3,    1,    3,    3,    1,
    3,    3,    3,    3,    1,    3,    3,    1,    3,    1,
    3,    1,    3,    1,    3,    1,    3,    1,    3,    1,
    5,    1,    3,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    3,    1,    2,    2,    4,
    1,    2,    1,    1,    2,    3,    3,    2,    3,    3,
    2,    2,    0,    2,    2,    2,    2,    2,    1,    1,
    1,    1,    1,    3,    4,    6,    5,    1,    2,    3,
    5,    4,    2,    2,    1,    2,    4,    1,    3,    1,
    3,    1,    1,    1,    1,    1,    4,    1,    3,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    2,    2,    2,    2,    2,    2,    2,    2,    2,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    2,    3,    3,
    4,    1,    2,    1,    1,    1,    1,    1,    2,    1,
    1,    1,    5,    4,    1,    2,    3,    1,    3,    1,
    2,    1,    3,    4,    1,    3,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    2,    0,    4,    1,
    1,    2,    3,    1,    2,    2,    1,    2,    5,    3,
    1,    1,    4,    5,    2,    3,    3,    2,    1,    2,
    2,    2,    1,    2,    5,    7,    6,    1,    1,    1,
    0,    2,    3,    2,    2,    2,    3,    2,    2,    1,
    1,    1,    1,    1,    2,    1,    2,    2,    7,    1,
    1,    1,    1,    2,    0,    1,    2,    1,    2,    3,
    2,    3,    2,    3,    2,    3,    2,    3,    1,    1,
    1,    1,
};
static const YYINT _mesa_glsl_defred[] = {                0,
    0,    0,   13,    0,    0,   15,   16,   17,    4,    0,
    0,    0,   14,    5,    0,  185,  184,  208,    0,  181,
    0,    0,  189,    0,  186,  182,  162,  161,  160,  193,
  194,  195,  196,  197,  192,    0,  207,  206,    0,    0,
  212,  211,  210,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,  183,    0,  284,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  145,    0,  204,    0,    0,
    0,    0,    0,  280,   19,  282,    0,  133,  281,  111,
  286,  205,  283,  309,  310,  311,  312,    0,    0,    0,
    0,  191,  187,  188,  190,   22,   23,    0,    0,  143,
  173,    0,    0,    0,  144,  172,    0,    6,    7,    8,
    9,   11,   12,   10,    0,  209,    0,  179,  146,  177,
  294,  178,  174,    0,    0,    0,    0,  175,  287,  301,
  303,  305,  307,  180,    0,  288,  176,    0,    0,    0,
    0,    0,    0,    0,  108,    0,  285,    0,  129,  130,
  131,    0,    0,    0,  115,    0,    0,    0,  112,    0,
  109,   20,   21,    0,    0,    0,  215,    0,    0,  155,
  154,  153,    0,    0,  148,  152,  158,    0,  304,  306,
  308,  302,    0,   30,   29,   31,   25,   26,   32,   27,
   28,    0,    0,    0,  198,   56,   57,   58,   59,   24,
   50,   34,  107,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,   60,    0,    0,    0,    0,    0,
   42,   41,   36,    0,    0,    0,    0,    0,  117,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  247,
    0,  242,  244,    0,  229,    0,    0,  228,  231,    0,
  105,   92,    0,  227,  230,  235,  236,  232,  233,  234,
  124,  125,  127,  128,    0,    0,  121,  122,  126,  116,
    0,   18,    0,  218,    0,  214,  216,    0,  110,    0,
  147,    0,  157,    0,    0,    0,    0,   53,   54,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  199,   38,   39,    0,    0,   43,    0,   44,    0,   47,
   55,   49,  200,    0,    0,  222,  142,    0,  275,  274,
  241,  240,    0,    0,    0,  279,  278,  276,    0,    0,
    0,  237,    0,  243,  245,  246,    0,  248,   95,   96,
   98,   97,  100,  101,  102,  103,  104,   99,   94,    0,
    0,    0,    0,    0,    0,    0,  217,  213,  151,  149,
  159,    0,    0,  299,   33,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,   61,   62,   63,   37,    0,    0,   48,  201,
  225,    0,  141,    0,  268,  269,    0,    0,  277,    0,
    0,    0,    0,    0,  106,   93,  119,    0,  137,    0,
  219,  300,    0,    0,    0,   35,    0,  223,    0,  270,
    0,    0,    0,    0,    0,    0,  239,  136,    0,  289,
   91,  224,  226,    0,    0,    0,    0,  249,    0,  254,
    0,  265,    0,    0,  267,    0,    0,    0,  255,    0,
  259,    0,    0,  253,  266,  250,    0,  258,  261,  260,
  262,  256,    0,  257,
};
#if defined(YYDESTRUCT_CALL) || defined(YYSTYPE_TOSTRING)
static const YYINT _mesa_glsl_stos[] = {                  0,
  336,  395,  499,  302,  500,  296,  297,  298,  340,  396,
  337,  502,  503,  340,  396,  257,  258,  259,  261,  273,
  274,  275,  276,  277,  278,  279,  280,  281,  282,  287,
  288,  289,  290,  291,  292,  293,  294,  297,  329,  330,
  331,  332,  333,  335,  343,  344,  345,  346,  347,  348,
  349,  350,  371,  385,  386,   59,  402,  403,  404,  405,
  406,  407,  411,  412,  414,  415,  416,  418,  419,  420,
  421,  422,  423,  429,  462,  463,  464,  465,  468,  472,
  473,  474,  494,  495,  496,  497,  498,  501,  339,  123,
  396,  261,  274,  275,  277,  296,  298,  329,  330,  398,
  403,  404,  407,  411,  398,  403,  402,  340,  340,  340,
  340,  340,  340,  340,   40,  259,   40,  403,  415,  403,
  414,  403,  403,  261,  274,  275,  277,  403,  472,  495,
  496,  497,  498,  403,  407,  472,  403,  298,   91,  417,
  296,  298,  396,  398,   59,  123,  430,  258,  274,  275,
  276,  330,  402,  411,  425,  426,  427,   44,   41,   44,
   59,  462,  503,  396,  419,  475,  476,  123,  415,  292,
  359,  392,  396,  408,  409,  410,  396,  413,   59,   59,
   59,   59,  123,  299,  300,  301,  302,  303,  304,  305,
  306,  310,  311,   40,   93,   43,   45,   33,  126,  398,
  415,  435,  437,  438,  439,  440,  441,  442,  443,  444,
  445,  446,  447,  448,  449,  450,  452,  453,  454,  455,
  456,  457,  458,  460,  461,   91,   61,  417,   40,  260,
  262,  263,  265,  266,  267,  268,  269,  270,  295,   59,
  123,  125,  399,  400,  401,  415,  420,  431,  433,  434,
  436,  437,  449,  468,  469,  470,  471,  481,  483,  489,
  426,  426,  426,  426,  407,  415,  424,  428,  426,  425,
  396,  340,  396,  477,  478,  125,  476,  475,   59,   61,
   41,   44,   41,   44,  419,  479,  480,  449,  449,  434,
  317,   63,  318,  316,  124,   94,   38,  314,  315,  312,
  313,   60,   62,  308,  309,   43,   45,   42,   47,   37,
   93,  310,  311,  351,   91,   41,   44,   41,  294,  436,
  449,   40,   93,  450,  123,  436,  466,   61,   59,   59,
  401,  430,  432,   40,   40,   59,   59,   59,  434,   40,
   40,  125,  504,  125,  399,  503,   44,   59,  319,  320,
  321,  322,  323,  324,  325,  326,  327,  328,   61,  459,
  415,  396,   61,  417,  417,   44,   59,  125,  450,  409,
  396,  478,  125,  479,   41,  439,  434,  440,  441,  442,
  443,  444,  445,  445,  446,  446,  446,  446,  447,  447,
  448,  448,  449,  449,  449,  307,  434,  451,  436,   93,
  466,  467,  466,  295,  433,  469,  492,  434,   59,  434,
  419,  434,  490,  400,  436,  436,  396,  417,  466,   61,
  477,   59,  298,  397,   58,   93,   44,  125,   40,  490,
  491,  493,   41,   41,  396,   41,  125,  466,  417,   59,
  436,  125,  466,  434,   59,   41,  399,  482,  123,  484,
   61,  432,   41,  434,  432,  264,  271,  272,  125,  485,
  486,  487,  488,  466,   59,  399,  434,   58,  399,  486,
  399,  125,  487,   58,
};
#endif /* YYDESTRUCT_CALL || YYSTYPE_TOSTRING */
static const YYINT _mesa_glsl_dgoto[] = {                 2,
  273,  424,  200,  243,  244,  245,   57,   58,   59,   60,
   61,  103,  174,  175,  176,  104,   64,  178,   65,  201,
   67,  140,   68,   69,  247,   71,   72,   73,  267,  155,
  156,  157,  268,   74,  332,  248,  333,  249,  250,  202,
  251,  252,  204,  205,  206,  207,  208,  209,  210,  211,
  212,  213,  214,  253,  216,  398,  217,  218,  219,  220,
  221,  222,  223,  360,  224,  225,   75,   76,   77,   78,
  327,  402,  254,  255,  256,  257,   80,   81,   82,  166,
  167,  274,  275,  286,  287,  258,  448,  259,  450,  460,
  461,  462,  463,  260,  413,  431,  407,  432,   83,   84,
   85,   86,   87,    3,    5,   88,   12,  346,  343,
};
static const YYINT _mesa_glsl_sindex[] = {             -319,
 -259,    0,    0,   21, -287,    0,    0,    0,    0, -279,
  -15, 2141,    0,    0, -221,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  -95,    0,    0, 3427, 3427,
    0,    0,    0,   67, -201, -190, -181, -170, -150, -142,
 -136,  179,  -33,    0,  199,    0, 3491, -187, 3557, 3491,
 3491, 3621, 3557, 3491,  -40,    0,  202,    0,  178,  -36,
 1133,  226,  262,    0,    0,    0,   -2,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0, 1938,  -15, 3297,
  184,    0,    0,    0,    0,    0,    0, 3491, 3491,    0,
    0, 3491, 3491, 3491,    0,    0, -187,    0,    0,    0,
    0,    0,    0,    0,  293,    0,  -15,    0,    0,    0,
    0,    0,    0,  281,  306,  310,  314,    0,    0,    0,
    0,    0,    0,    0, 3557,    0,    0,  258, 1722,  326,
    0,    0,  -46,  386,    0,  939,    0, 1133,    0,    0,
    0, 1133, 1133, 1133,    0,  520, 1133, 1133,    0,  -15,
    0,    0,    0,   91,  -15, 2788,    0, 3297,  377,    0,
    0,    0,  382,   71,    0,    0,    0,  168,    0,    0,
    0,    0, 3297,    0,    0,    0,    0,    0,    0,    0,
    0,  455,  455,  455,    0,    0,    0,    0,    0,    0,
    0,    0,    0,  -61,  140,  144,  339,  373,  446,  -70,
  -48,   78,  285,  359,    0,  398,  -82,  194,  452, 1880,
    0,    0,    0,  455,  454, 1804, 1853,  -42,    0,  438,
  440, 1069,  461,  469,  470,  471, 1443,  488,  530,    0,
  447,    0,    0,  345,    0,    0,  512,    0,    0,   31,
    0,    0,  238,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0, -187,  -15,    0,    0,    0,    0,
   64,    0,  202,    0,   57,    0,    0, 2873,    0,  455,
    0,  293,    0,  -15,  -15,  448, 3297,    0,    0,  230,
  455,  455,  455,  455,  455,  455,  455,  455,  455,  455,
  455,  455,  455,  455,  455,  455,  455,  455,  455,  455,
    0,    0,    0,  277,  455,    0,  455,    0,    0,    0,
    0,    0,    0,  493, 1853,    0,    0, 1853,    0,    0,
    0,    0,  292, 1530,  455,    0,    0,    0,   77,  455,
 1660,    0, 1255,    0,    0,    0,  455,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  455,
  -15,  202, 1853,  106,  326,  -15,    0,    0,    0,    0,
    0,  117,  290,    0,    0,  140,   70,  144,  339,  373,
  446,  -70,  -48,  -48,   78,   78,   78,   78,  285,  285,
  359,  359,    0,    0,    0,    0,  548,  500,    0,    0,
    0,  -26,    0,  554,    0,    0, 1660,  250,    0,  261,
  -15,  548,  555,  620,    0,    0,    0,  326,    0, 1853,
    0,    0,  202,  538,  455,    0,   49,    0,  455,    0,
  540,  559, 1255,  478,  567, 1069,    0,    0,  326,    0,
    0,    0,    0,  323,  455, 1069,  365,    0,  -94,    0,
 1853,    0,  550,  548,    0, 1255,  455,  596,    0,  750,
    0, 1255,  -78,    0,    0,    0,   94,    0,    0,    0,
    0,    0, 1255,    0,
};
static const YYINT _mesa_glsl_rindex[] = {             2040,
    0,    0,    0,    0, 2241,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0, 3037,    0,
 3101, 3167,    0, 3231,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  121,  160,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0, 3361,    0,  403,    0,  556,  561,
  568,  570,  575,  695,    0,    0,   86,    0,  129,    0,
  -34,  576,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  657,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  121,  160,    0,
    0,  556,  570,  575,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0, 3037, 3101, 3167, 3231,    0,    0,    0,
    0,    0,    0,    0,  570,    0,    0,    0,    0,  256,
  318,  747,  151,    0,    0,    0,    0,  707,    0,    0,
    0,  707,  707,  707,    0,    0,  707,  707,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  364,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,   15,   39,  124,   -5,  251, 1260,  122,
  353,  646,  781, 2594,    0,    0, 2499,    0,    0,  617,
    0,    0,    0,    0,    0,    0,    0,  217,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
 1385,    0,    0,    0,    0,  539,    0,    0,    0,    0,
    0,    0, 2557,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  366,    0,    0,    0,    0,
  218,    0,  280,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  534,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  196,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  389,    0,  282,  330,    0,    0,    0,    0,    0,
    0,    0,  602,    0,    0,  669,    0,  155,  164, 1098,
 1416,  148,  679, 1131, 1942, 2712, 2790, 2797, 2665, 2705,
 2617, 2654,    0,    0,    0,    0,  571,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  607,    0,    0,    0,
    0,    7,    0,    0,    0,    0,    0,  411,    0,    0,
    0,    0,  614,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  622,    0,
    0,    0,    0,    0,  642,    0,  245,    0,    0,    0,
    0,    0,    0,  645,    0,    0,    0,    0,    0,    0,
    0,  -41,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  -21,    0,
};
#if YYBTYACC
static const YYINT _mesa_glsl_cindex[] = {                0,
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
    0,    0,    0,    0,
};
#endif
static const YYINT _mesa_glsl_gindex[] = {                0,
    2,    0,    1, -135,  346, -212,  628, 2025,  -35,    0,
    0,   23,    0,  406,    0,  -11,    0,    0,  632,  -12,
    0, -122,    0,  -87,   12,    0,    0,    0,    0,  535,
  275,    0,    0,    0,  624,    0, -402,  358, 2168,    0,
 1274, -123,    0,  407,  408,  409,  412,  415,  405,  188,
   33,   88,  183, 2983, -218,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  627,    0,    0,    0,
 -298,    0,   25,  378,    0,    0,  -30,    0,    0,  551,
 -155,  352,  436,  435,    0,    0,    0,    0,    0,    0,
  264,  263,    0,    0,  322,    0,    0,    0,    0,  663,
  671,  672,  673,    0,    0,    0,    0,    5,    0,
};
#define YYTABLESIZE 4007
static const YYINT _mesa_glsl_table[] = {                66,
   63,  292,  165,  102,  102,   10,  113,  324,  315,   13,
  277,  302,   15,  303,  227,  203,    1,  427,  328,  331,
  228,  102,  145,   70,  102,  102,  401,   90,  102,  403,
  459,  129,  136,  452,   62,   84,   79,   91,   84,  100,
  105,  160,    4,  455,  139,  119,  472,  252,  226,   11,
   63,   63,   84,   84,  102,   90,  161,   84,   90,  154,
   14,  369,  102,  102,  419,  252,  102,  102,  102,  144,
  143,   18,   90,   90,  347,   66,   63,   66,  165,   88,
  165,  198,   88,  263,   62,  135,  146,   84,  194,  348,
  164,  196,  163,  197,  169,  285,   88,   88,  428,   70,
  366,   88,  203,  264,  129,   36,   37,   90,  345,   38,
   62,  281,   79,  347,  282,  367,  173,   89,  177,   84,
  347,  438,  277,   63,  363,  202,  202,  425,  443,  202,
  102,   88,  102,  246,   63,  409,  154,  347,  108,   90,
  154,  154,  154,  266,  202,  154,  154,  102,  364,  109,
  365,  474,  464,   66,  139,   66,  203,  135,  110,   78,
  366,  271,   78,   88,   86,   78,  420,   86,  135,  111,
   66,  325,  138,  442,  199,  422,  457,  458,  265,   78,
   78,   86,   86,   53,   78,   79,   86,  138,   79,  112,
  165,   79,  457,  458,  139,   87,  226,  113,   87,  285,
    6,    7,    8,  114,   85,   79,   79,   85,  283,  139,
   79,  284,   87,   87,   78,   78,   86,   87,  115,  246,
   63,   85,   85,  331,  123,  116,   85,  312,  313,  263,
  263,  246,   63,  331,  316,  207,   45,  317,  117,  418,
   79,   79,  102,  298,  299,   78,   78,   87,   86,  264,
  264,  102,  361,  411,  135,  291,   85,  138,  123,  123,
  140,  134,  123,  300,  301,   66,  135,  362,  314,  158,
  375,   79,   79,  347,   66,  140,  134,  251,  345,   87,
    6,    7,    8,  173,  251,  371,  207,  251,   85,  251,
  433,   82,  139,  347,   82,  203,  203,  447,  359,  203,
  439,  434,  159,  251,  347,  102,  168,   18,   82,   82,
   84,   84,   84,   82,  203,  123,    6,    7,    8,  411,
  466,  246,   63,  220,  469,  135,  471,  306,  246,  307,
  246,   63,  385,  386,  387,  388,  123,  471,  220,  179,
  135,   36,   37,   82,   96,   38,   97,  184,  185,  186,
  187,  188,  189,  190,  191,   88,  135,   22,  192,  193,
    9,   15,  417,  453,  180,  135,  347,  251,  181,  251,
  251,  102,  182,  221,   82,   82,   15,  198,   15,  163,
  183,  202,  202,  202,  194,  304,  305,  196,  221,  197,
   75,  389,  390,   75,  246,  310,   75,   41,   42,   43,
  308,  246,   63,  240,  150,  309,  132,  150,   15,  132,
   75,   75,  435,  163,  163,   75,  226,  163,  164,   53,
  246,   63,  261,  246,   63,  229,  262,  263,  264,  118,
  272,  269,  118,  246,   63,  279,  135,   78,   78,   78,
   86,   86,  280,  246,   63,   75,   75,  246,   63,  246,
   63,  120,  164,  164,  120,  135,  164,  293,  135,  294,
  246,   63,  295,   79,   79,   79,  296,  241,  135,  344,
  199,   87,   87,  141,    7,  142,   75,   75,  135,   85,
   85,   85,  135,  297,  135,  383,  384,  198,  391,  392,
  311,  163,  318,  322,  194,  135,  329,  196,  330,  197,
  334,  251,  251,  251,  251,  251,  251,  251,  335,  251,
  251,  251,  251,  251,  251,  251,  251,  251,  251,  251,
  251,  251,  251,  251,  251,  251,  251,  340,  336,  337,
  164,  251,  251,  251,  251,  251,  251,  251,  251,  251,
  251,  251,  251,  251,  251,  251,  251,  251,  251,  251,
  251,  203,  203,  203,  251,  251,  349,  350,  351,  352,
  353,  354,  355,  356,  357,  358,   82,   82,   82,  341,
  145,  342,  373,  251,  251,  251,  251,  251,   50,  251,
  199,  251,  145,  396,  170,  400,  404,  423,    6,    7,
    8,  347,  426,  429,  251,  436,  440,  145,  445,  446,
  449,   16,   17,   18,  230,   19,  231,  232,  465,  233,
  234,  235,  236,  237,  238,  251,  114,   20,   21,   22,
   23,   24,   25,   26,   27,   28,   29,  451,  456,  251,
  251,   30,   31,   32,   33,   34,   35,   36,   37,  239,
   96,   38,   97,  184,  185,  186,  187,  188,  189,  190,
  191,  171,  198,  468,  192,  193,    2,   46,  298,  194,
  295,  171,  196,   40,  197,  271,   75,   75,   75,   75,
   75,  107,  296,   39,   40,   41,   42,   43,  240,   44,
  297,   11,  272,   70,  172,  273,   70,  370,  414,   70,
  121,  405,  270,  147,   52,  171,  171,  376,  153,  171,
  378,  382,  379,   70,   70,   70,  380,   70,   70,   89,
  381,  406,   89,   18,  162,   53,   76,  421,  278,   76,
  372,  374,   76,  470,  130,  473,   89,   89,  430,   54,
   55,   89,  131,  132,  133,    0,   76,   76,   70,   70,
    0,   76,  241,    0,  437,  199,    0,   36,   37,    0,
   96,   38,   97,  184,  185,  186,  187,  188,  189,  190,
  191,   89,    0,    0,  192,  193,    0,    0,    0,   70,
   70,   76,   76,  171,    0,  153,    0,    0,   18,  153,
  153,  153,  198,    0,  153,  153,   23,    0,    0,  194,
   17,    0,  196,   89,  197,    0,    0,    0,    0,    0,
    0,    0,   76,   76,    0,   17,    0,   17,  240,    0,
    0,    0,   36,   37,  165,    0,   38,    0,   67,  166,
    0,   67,    0,    0,   67,   53,  167,    0,  168,    0,
    0,    0,    0,  169,  145,  145,  145,   17,   67,   67,
   67,    0,   67,   67,    0,    0,    0,    0,  165,  165,
    0,    0,  165,  166,  166,    0,    0,  166,    0,    0,
  167,  167,  168,  168,  167,    0,  168,  169,  169,   52,
    0,  169,  241,   67,   67,  199,   16,   17,   18,  230,
   19,  231,  232,    0,  233,  234,  235,  236,  237,  238,
   53,    0,   20,   21,   22,   23,   24,   25,   26,   27,
   28,   29,    0,    0,   67,   67,   30,   31,   32,   33,
   34,   35,   36,   37,  239,   96,   38,   97,  184,  185,
  186,  187,  188,  189,  190,  191,  165,    0,    0,  192,
  193,  166,    0,    0,    0,    0,    0,    0,  167,    0,
  168,    0,    0,    0,    0,  169,    0,    0,   39,   40,
   41,   42,   43,  170,   44,    0,   11,   70,   70,   70,
   70,   70,   70,   70,    0,  123,    0,    0,    0,   52,
    0,  198,    0,    0,    0,    0,    0,    0,  194,    0,
    0,  196,    0,  197,    0,   89,    0,  170,  170,    0,
   53,  170,   76,   76,   76,   76,   76,  240,    0,  123,
  123,    0,    0,  123,   54,   55,   16,   17,   18,  230,
   19,  231,  232,    0,  233,  234,  235,  236,  237,  238,
  457,  458,   20,   21,   22,   23,   24,   25,   26,   27,
   28,   29,    0,    0,    0,    0,   30,   31,   32,   33,
   34,   35,   36,   37,  239,   96,   38,   97,  184,  185,
  186,  187,  188,  189,  190,  191,  123,    0,    0,  192,
  193,  241,    0,  242,  199,  170,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  123,   39,   40,
   41,   42,   43,    0,   44,    0,    0,    0,   67,   67,
    0,    0,   67,   67,   67,   67,   67,   67,   67,   52,
    0,  198,    0,    0,    0,    0,    0,    0,  194,    0,
    0,  196,    0,  197,    0,    0,    0,    0,    0,    0,
   53,    0,    0,    0,    0,    0,    0,  240,    0,    0,
    0,    0,    0,    0,   54,   55,    0,    0,   83,    0,
    0,   83,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,   83,   83,    0,    0,    0,
   83,    0,    0,    0,    0,    0,    0,    0,   77,    0,
    0,   77,    0,    0,   77,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,   77,   77,
   83,  146,    0,   77,  199,   16,   17,   18,  230,   19,
  231,  232,    0,  233,  234,  235,  236,  237,  238,    0,
    0,   20,   21,   22,   23,   24,   25,   26,   27,   28,
   29,   83,   83,   77,   77,   30,   31,   32,   33,   34,
   35,   36,   37,  239,   96,   38,   97,  184,  185,  186,
  187,  188,  189,  190,  191,    0,    0,    0,  192,  193,
    0,    0,    0,    0,   77,   77,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,   39,   40,   41,
   42,   43,    0,   44,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  198,   52,    0,
    0,    0,    0,    0,  194,    0,    0,  196,    0,  197,
   80,    0,    0,   80,    0,    0,    0,    0,    0,   53,
    0,    0,    0,  240,    0,    0,    0,   80,   80,    0,
    0,    0,   80,   54,   55,   16,   17,   18,  230,   19,
  231,  232,    0,  233,  234,  235,  236,  237,  238,    0,
    0,   20,   21,   22,   23,   24,   25,   26,   27,   28,
   29,    0,   80,   80,    0,   30,   31,   32,   33,   34,
   35,   36,   37,  239,   96,   38,   97,  184,  185,  186,
  187,  188,  189,  190,  191,    0,    0,  241,  192,  193,
  199,    0,    0,   80,   80,    0,    0,    0,    0,    0,
  148,    0,    0,    0,    0,    0,    0,   39,   40,   41,
   42,   43,    0,   44,    0,    0,  149,  150,  151,    0,
    0,    0,    0,   83,   83,   83,    0,  238,   52,   30,
   31,   32,   33,   34,  238,    0,    0,  238,    0,  238,
    0,    0,    0,    0,    0,    0,    0,    0,    0,   53,
    0,    0,    0,  238,   77,   77,   77,   77,   77,    0,
    0,    0,    0,   54,   55,    0,   81,    0,    0,   81,
    0,    0,  152,   41,   42,   43,    0,    0,    0,    0,
    0,    0,    0,   81,   81,  198,    0,    0,   81,    0,
    0,    0,  194,    0,    0,  196,    0,  197,    0,    0,
    0,    0,    0,  320,    0,    0,    0,    0,    0,    0,
  326,  338,    0,    0,    0,    0,    0,  238,   81,   81,
  238,   16,   17,   18,  230,   19,  231,  232,    0,  233,
  234,  235,  236,  237,  238,    0,    0,   20,   21,   22,
   23,   24,   25,   26,   27,   28,   29,    0,    0,   81,
   81,   30,   31,   32,   33,   34,   35,   36,   37,  239,
   96,   38,   97,  184,  185,  186,  187,  188,  189,  190,
  191,    0,  198,    0,  192,  193,    0,    0,  199,  194,
    0,    0,  196,    0,  197,   80,   80,   80,    0,    0,
    0,    0,    0,   39,   40,   41,   42,   43,  240,   44,
  399,    0,    0,    0,    0,    0,    0,    0,  326,    0,
    0,  326,    0,    0,   52,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  415,    0,    0,    0,    0,   53,    0,    0,    0,    0,
    0,    0,    0,  416,    0,    0,  326,    0,    0,   54,
   55,  238,  238,  238,  238,  238,  238,  238,    0,  238,
  238,  238,  238,  238,  238,  199,    0,  238,  238,  238,
  238,  238,  238,  238,  238,  238,  238,    0,    0,    0,
    0,  238,  238,  238,  238,  238,  238,  238,  238,  238,
  238,  238,  238,  238,  238,  238,  238,  238,  238,  238,
  238,    0,  198,  326,  238,  238,    0,    0,  441,  194,
  326,   18,  196,    0,  197,    0,    0,    0,    0,    0,
    0,    0,    0,  238,  238,  238,  238,  238,    0,  238,
    0,    0,    0,    0,  326,    0,    0,    0,    0,    0,
    0,   81,   81,   81,  238,   36,   37,    0,   96,   38,
   97,  184,  185,  186,  187,  188,  189,  190,  191,    0,
    0,    0,  192,  193,  198,  238,    0,    0,    0,    0,
    0,  194,    0,    0,  196,    0,  197,    0,    0,  238,
  238,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  199,   16,   17,   18,    0,
   19,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,   20,   21,   22,   23,   24,   25,   26,   27,
   28,   29,    0,   53,  195,    0,   30,   31,   32,   33,
   34,   35,   36,   37,    0,   96,   38,   97,  184,  185,
  186,  187,  188,  189,  190,  191,  198,    0,    0,  192,
  193,    0,    0,  194,    0,    0,  196,  199,  197,    0,
    0,    0,    0,    0,    0,    0,    0,    0,   39,   40,
   41,   42,   43,    0,   44,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,   52,
    0,    0,    0,    0,    0,  198,    0,    0,    0,    0,
    0,    0,  194,    0,    0,  196,  323,  197,    0,    0,
   53,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  198,    0,   54,   55,   16,   17,   18,  194,
   92,    0,  196,    0,  197,    0,    0,    0,    0,  199,
    0,    0,   20,   93,   94,   23,   95,   25,   26,   27,
   28,   29,    0,    0,    0,    0,   30,   31,   32,   33,
   34,   35,   36,   37,    0,   96,   38,   97,  184,  185,
  186,  187,  188,  189,  190,  191,    0,    0,    0,  192,
  193,    0,    0,    0,    0,  325,    0,    0,  199,   73,
   18,    0,   73,    0,    0,   73,    0,    0,   98,   99,
   41,   42,   43,    0,    0,    0,   56,    0,    0,   73,
   73,   73,    0,   73,   73,  199,    0,    0,    0,   52,
    0,    0,    0,    0,   36,   37,    0,   96,   38,   97,
  184,  185,  186,  187,  188,  189,  190,  191,    0,    0,
   53,  192,  193,    0,   73,   73,    0,    0,    0,    0,
    0,    0,    0,    0,   54,   55,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,   18,  101,  106,   73,   73,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  118,    0,  120,  122,  123,  128,  134,  137,    0,
    0,    0,   53,    0,    0,    0,   36,   37,    3,   96,
   38,   97,  184,  185,  186,  187,  188,  189,  190,  191,
    0,   18,    0,  192,  193,    0,    0,    0,    0,    0,
    0,    0,  101,  106,    0,    0,  120,  128,  134,    0,
    0,    0,    0,    0,    0,    0,    0,    0,   18,    0,
    0,    0,    0,    0,    0,   36,   37,    0,   96,   38,
   97,  184,  185,  186,  187,  188,  189,  190,  191,  128,
    0,    0,  192,  193,    0,    0,    0,    0,    0,    0,
    0,    0,   36,  319,   53,   96,   38,   97,  184,  185,
  186,  187,  188,  189,  190,  191,    0,    0,    0,  192,
  193,    0,    0,    0,   16,   17,   18,    0,   19,   56,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
   20,   21,   22,   23,   24,   25,   26,   27,   28,   29,
    0,    0,    0,   53,   30,   31,   32,   33,   34,   35,
   36,   37,    0,    0,   38,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
   53,    0,    0,   73,   73,   73,   73,   73,   73,   73,
    0,    0,    0,    0,    0,    0,   39,   40,   41,   42,
   43,    0,   44,    0,   11,    0,    0,    0,    0,    0,
   45,   46,   47,   48,   49,   50,   51,   52,    0,    0,
    0,    0,    0,    0,    0,    0,    3,    3,    3,    1,
    3,    0,    0,    0,    0,    0,    0,    0,   53,    0,
    0,    0,    3,    3,    3,    3,    3,    3,    3,    3,
    3,    3,   54,   55,    0,    0,    3,    3,    3,    3,
    3,    3,    3,    3,    0,    0,    3,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  290,    0,    0,    0,    0,    0,    0,    3,    3,
    3,    3,    3,    0,    3,    0,    3,    0,    0,    0,
    0,    0,    3,    3,    3,    3,    3,    3,    3,    3,
    0,    0,    0,    0,    0,    0,    0,   16,   17,   18,
    0,   19,    0,    0,  339,    0,    0,    0,    0,    0,
    3,    0,    0,   20,   21,   22,   23,   24,   25,   26,
   27,   28,   29,    0,    3,    3,    0,   30,   31,   32,
   33,   34,   35,   36,   37,    0,    0,   38,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  377,
    0,    0,    0,    0,    0,    0,    0,    0,    0,   39,
   40,   41,   42,   43,    0,   44,    0,    0,    0,    0,
    0,    0,  397,   45,   46,   47,   48,   49,   50,   51,
   52,    0,    0,    0,    0,    0,    0,    1,    1,    1,
    0,    1,  408,    0,    0,    0,    0,  410,  412,    0,
    0,   53,    0,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    0,    0,   54,   55,    1,    1,    1,
    1,    1,    1,    1,    1,   52,   52,    1,   51,   52,
   52,   52,   52,   52,    0,   52,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,   52,   52,   52,   52,
   52,   52,    0,    0,    0,    0,    0,    0,    0,    1,
    1,    1,    1,    1,  412,    1,    0,    0,    0,    0,
    0,    0,    0,    1,    1,    1,    1,    1,    1,    1,
    1,   52,   52,   60,   60,    0,  444,   60,   60,   60,
   60,   60,    0,   60,    0,    0,    0,    0,    0,    0,
    0,    1,  454,    0,   60,   60,   60,    0,   60,   60,
    0,    0,   52,   52,  467,    1,    1,    0,    0,    0,
    0,   64,    0,    0,   64,    0,   64,   64,   64,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,   60,
   60,   64,   64,   64,   65,   64,   64,   65,    0,   65,
   65,   65,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,   65,   65,   65,    0,   65,   65,
   60,   60,    0,    0,    0,    0,   64,   64,    0,    0,
    0,   66,    0,    0,   66,    0,   66,   66,   66,    0,
    0,    0,   68,    0,    0,   68,    0,    0,   68,   65,
   65,   66,   66,   66,    0,   66,   66,   64,   64,    0,
    0,    0,   68,   68,   68,    0,   68,   68,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
   65,   65,   69,    0,    0,   69,   66,   66,   69,   74,
    0,    0,   74,    0,    0,   74,    0,   68,   68,    0,
    0,    0,   69,   69,   69,    0,   69,   69,    0,   74,
   74,   74,    0,   74,   74,    0,    0,   66,   66,    0,
    0,    0,    0,    0,    0,    0,    0,    0,   68,   68,
    0,    0,    0,    0,    0,    0,    0,   69,   69,    0,
    0,    0,    0,    0,   74,   74,   52,   52,    0,    0,
   52,   52,   52,   52,   52,   52,   52,   52,   52,   52,
   52,   52,   52,   52,   52,   52,   52,   71,   69,   69,
   71,    0,    0,   71,   72,   74,   74,   72,    0,    0,
   72,    0,    0,    0,    0,    0,    0,   71,   71,   71,
    0,   71,   71,    0,   72,   72,   72,    0,   72,   72,
    0,    0,    0,    0,   60,   60,    0,    0,   60,   60,
   60,   60,   60,   60,   60,    0,    0,    0,    0,    0,
    0,    0,   71,   71,    0,    0,    0,    0,    0,   72,
   72,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,   64,   64,    0,    0,   64,   64,   64,   64,   64,
   64,   64,  276,   71,   71,    0,    0,    0,    0,    0,
   72,   72,    0,    0,   65,   65,    0,    0,   65,   65,
   65,   65,   65,   65,   65,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,   66,   66,    0,    0,   66,   66,   66,   66,   66,
   66,   66,   68,   68,    0,    0,   68,   68,   68,   68,
   68,   68,   68,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  368,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,   69,   69,    0,    0,   69,   69,   69,   69,
   69,   69,   69,   74,   74,   74,   74,   74,   74,   74,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,   16,   17,   18,    0,   92,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
   20,   93,   94,   23,   95,   25,   26,   27,   28,   29,
    0,    0,    0,    0,   30,   31,   32,   33,   34,   35,
   36,   37,    0,    0,   38,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,   71,   71,   71,   71,   71,   71,   71,   72,   72,
   72,   72,   72,   72,   72,    0,   98,   99,   41,   42,
   43,  215,    0,    0,    0,    0,    0,    0,    0,   16,
   17,   18,    0,   92,    0,    0,    0,   52,    0,    0,
    0,    0,    0,    0,    0,   20,   93,   94,   23,   95,
   25,   26,   27,   28,   29,    0,    0,    0,   53,   30,
   31,   32,   33,   34,   35,   36,   37,    0,    0,   38,
    0,    0,   54,   55,  288,  289,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,   98,   99,   41,   42,   43,  321,    0,  215,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,   52,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,   53,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,   54,   55,    0,
    0,    0,  215,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,  215,    0,  215,  215,  215,  215,  215,
  215,  215,  215,  215,  215,  215,  215,  215,  215,  215,
  393,  394,  395,  191,  191,  191,    0,  191,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  191,
  191,  191,  191,  191,  191,  191,  191,  191,  191,    0,
    0,    0,    0,  191,  191,  191,  191,  191,  191,  191,
  191,    0,    0,  191,  293,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  187,  187,  187,
    0,  187,    0,    0,    0,  191,  191,  191,  191,  191,
    0,    0,    0,  187,  187,  187,  187,  187,  187,  187,
  187,  187,  187,    0,    0,    0,  191,  187,  187,  187,
  187,  187,  187,  187,  187,    0,    0,  187,  290,    0,
    0,    0,    0,    0,    0,    0,    0,  191,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  191,  191,  188,  188,  188,    0,  188,    0,  187,
  187,  187,  187,  187,    0,    0,    0,    0,    0,  188,
  188,  188,  188,  188,  188,  188,  188,  188,  188,    0,
  187,    0,    0,  188,  188,  188,  188,  188,  188,  188,
  188,    0,    0,  188,  291,    0,    0,    0,    0,    0,
    0,  187,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  187,  187,  190,  190,  190,
    0,  190,    0,    0,    0,  188,  188,  188,  188,  188,
    0,    0,    0,  190,  190,  190,  190,  190,  190,  190,
  190,  190,  190,    0,    0,    0,  188,  190,  190,  190,
  190,  190,  190,  190,  190,    0,    0,  190,  292,    0,
    0,    0,    0,    0,    0,    0,    0,  188,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  188,  188,   16,   17,   18,    0,   92,    0,  190,
  190,  190,  190,  190,    0,    0,    0,    0,    0,   20,
   93,   94,   23,   95,   25,   26,   27,   28,   29,    0,
  190,    0,    0,   30,   31,   32,   33,   34,   35,   36,
   37,    0,    0,   38,    0,    0,    0,    0,    0,    0,
    0,  190,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  190,  190,  156,  156,  156,
    0,  156,    0,    0,    0,   98,   99,   41,   42,   43,
    0,    0,    0,  156,  156,  156,  156,  156,  156,  156,
  156,  156,  156,    0,    0,    0,   52,  156,  156,  156,
  156,  156,  156,  156,  156,    0,    0,  156,    0,    0,
    0,    0,    0,    0,    0,    0,    0,   53,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,   54,   55,   16,   17,    0,    0,   92,    0,  156,
  156,  156,  156,  156,    0,    0,    0,    0,    0,   20,
   93,   94,   23,   95,   25,   26,   27,   28,   29,    0,
  156,    0,    0,   30,   31,   32,   33,   34,   35,    0,
    0,    0,   96,    0,   97,    0,    0,    0,    0,    0,
    0,  156,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  156,  156,   16,   17,    0,
    0,   92,    0,    0,    0,   98,   99,   41,   42,   43,
    0,    0,    0,   20,   93,   94,   23,   95,   25,   26,
   27,   28,   29,    0,    0,    0,   52,   30,   31,   32,
   33,   34,   35,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,   54,   55,   16,   17,    0,    0,   19,    0,   98,
   99,   41,   42,   43,    0,    0,    0,    0,    0,   20,
   21,   22,   23,   24,   25,   26,   27,   28,   29,    0,
   52,    0,    0,   30,   31,   32,   33,   34,   35,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,   54,   55,   16,   17,    0,
    0,  124,    0,    0,    0,   98,   99,   41,   42,   43,
    0,    0,    0,   20,  125,  126,   23,  127,   25,   26,
   27,   28,   29,    0,    0,    0,   52,   30,   31,   32,
   33,   34,   35,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,   54,   55,    0,    0,    0,    0,    0,    0,   98,
   99,   41,   42,   43,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
   52,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,   54,   55,
};
static const YYINT _mesa_glsl_check[] = {                12,
   12,   63,   90,   39,   40,    4,   41,  226,   91,    5,
  166,   60,   11,   62,   61,  139,  336,   44,   61,  232,
  143,   57,   59,   12,   60,   61,  325,  123,   64,  328,
  125,   62,   63,  436,   12,   41,   12,   36,   44,   39,
   40,   44,  302,  446,   91,   58,  125,   41,   91,  337,
   62,   63,   58,   59,   90,   41,   59,   63,   44,   71,
  340,  280,   98,   99,  363,   59,  102,  103,  104,   69,
   69,  259,   58,   59,   44,   88,   88,   90,  166,   41,
  168,   33,   44,  125,   62,   63,  123,   93,   40,   59,
   89,   43,   88,   45,  107,  183,   58,   59,  125,   88,
   44,   63,  226,  125,  135,  293,  294,   93,  244,  297,
   88,   41,   88,   44,   44,   59,  115,  339,  117,  125,
   44,  420,  278,  135,   61,   40,   41,   58,  427,   44,
  166,   93,  168,  146,  146,   59,  148,   44,  340,  125,
  152,  153,  154,  156,   59,  157,  158,  183,  271,  340,
  273,   58,  451,  166,   91,  168,  280,  135,  340,   38,
   44,  160,   41,  125,   41,   44,   61,   44,  146,  340,
  183,  123,   44,  125,  126,   59,  271,  272,  156,   58,
   59,   58,   59,  371,   63,   38,   63,   59,   41,  340,
  278,   44,  271,  272,   44,   41,   91,  340,   44,  287,
  296,  297,  298,  340,   41,   58,   59,   44,   41,   59,
   63,   44,   58,   59,   93,   94,   93,   63,   40,  232,
  232,   58,   59,  436,  259,  259,   63,  310,  311,  271,
  272,  244,  244,  446,   41,   40,   41,   44,   40,  362,
   93,   94,  278,  314,  315,  124,  125,   93,  125,  271,
  272,  287,  265,  341,  232,  317,   93,  298,  293,  294,
   44,   44,  297,  312,  313,  278,  244,  266,  351,   44,
   41,  124,  125,   44,  287,   59,   59,   33,  414,  125,
  296,  297,  298,  282,   40,  284,   91,   43,  125,   45,
   41,   41,   91,   44,   44,   40,   41,  433,   61,   44,
  423,   41,   41,   59,   44,  341,  123,  259,   58,   59,
  316,  317,  318,   63,   59,  350,  296,  297,  298,  407,
  456,  334,  334,   44,  460,   44,  462,   43,  341,   45,
  343,  343,  300,  301,  302,  303,  371,  473,   59,   59,
   59,  293,  294,   93,  296,  297,  298,  299,  300,  301,
  302,  303,  304,  305,  306,  317,  334,   40,  310,  311,
  340,   44,  361,   41,   59,  343,   44,  123,   59,  125,
  126,  407,   59,   44,  124,  125,   59,   33,   61,  259,
  123,  296,  297,  298,   40,  308,  309,   43,   59,   45,
   38,  304,  305,   41,  407,   37,   44,  331,  332,  333,
   42,  414,  414,   59,   41,   47,   41,   44,   91,   44,
   58,   59,  411,  293,  294,   63,   91,  297,  259,  371,
  433,  433,  148,  436,  436,   40,  152,  153,  154,   41,
  340,  157,   44,  446,  446,   59,  414,  316,  317,  318,
  317,  318,   61,  456,  456,   93,   94,  460,  460,  462,
  462,   41,  293,  294,   44,  433,  297,  318,  436,  316,
  473,  473,  124,  316,  317,  318,   94,  123,  446,  125,
  126,  317,  318,  296,  297,  298,  124,  125,  456,  316,
  317,  318,  460,   38,  462,  298,  299,   33,  306,  307,
   93,  371,   41,   40,   40,  473,   59,   43,   59,   45,
   40,  257,  258,  259,  260,  261,  262,  263,   40,  265,
  266,  267,  268,  269,  270,  271,  272,  273,  274,  275,
  276,  277,  278,  279,  280,  281,  282,   40,   59,   59,
  371,  287,  288,  289,  290,  291,  292,  293,  294,  295,
  296,  297,  298,  299,  300,  301,  302,  303,  304,  305,
  306,  296,  297,  298,  310,  311,  319,  320,  321,  322,
  323,  324,  325,  326,  327,  328,  316,  317,  318,   40,
   59,  125,  125,  329,  330,  331,  332,  333,   40,  335,
  126,  337,   44,  307,  292,   93,  295,  298,  296,  297,
  298,   44,   93,   40,  350,   41,   59,   59,   59,   41,
  123,  257,  258,  259,  260,  261,  262,  263,   59,  265,
  266,  267,  268,  269,  270,  371,   41,  273,  274,  275,
  276,  277,  278,  279,  280,  281,  282,   61,  264,  385,
  386,  287,  288,  289,  290,  291,  292,  293,  294,  295,
  296,  297,  298,  299,  300,  301,  302,  303,  304,  305,
  306,  359,   33,   58,  310,  311,    0,   41,  125,   40,
   59,  259,   43,   93,   45,   59,  314,  315,  316,  317,
  318,   44,   59,  329,  330,  331,  332,  333,   59,  335,
   59,  337,   41,   38,  392,   41,   41,  282,  343,   44,
   59,  334,  158,   70,  350,  293,  294,  291,   71,  297,
  293,  297,  294,   58,   59,   60,  295,   62,   63,   41,
  296,  334,   44,  259,   88,  371,   38,  366,  168,   41,
  285,  287,   44,  460,   62,  463,   58,   59,  407,  385,
  386,   63,   62,   62,   62,   -1,   58,   59,   93,   94,
   -1,   63,  123,   -1,  125,  126,   -1,  293,  294,   -1,
  296,  297,  298,  299,  300,  301,  302,  303,  304,  305,
  306,   93,   -1,   -1,  310,  311,   -1,   -1,   -1,  124,
  125,   93,   94,  371,   -1,  148,   -1,   -1,  259,  152,
  153,  154,   33,   -1,  157,  158,   40,   -1,   -1,   40,
   44,   -1,   43,  125,   45,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  124,  125,   -1,   59,   -1,   61,   59,   -1,
   -1,   -1,  293,  294,  259,   -1,  297,   -1,   38,  259,
   -1,   41,   -1,   -1,   44,  371,  259,   -1,  259,   -1,
   -1,   -1,   -1,  259,  296,  297,  298,   91,   58,   59,
   60,   -1,   62,   63,   -1,   -1,   -1,   -1,  293,  294,
   -1,   -1,  297,  293,  294,   -1,   -1,  297,   -1,   -1,
  293,  294,  293,  294,  297,   -1,  297,  293,  294,  350,
   -1,  297,  123,   93,   94,  126,  257,  258,  259,  260,
  261,  262,  263,   -1,  265,  266,  267,  268,  269,  270,
  371,   -1,  273,  274,  275,  276,  277,  278,  279,  280,
  281,  282,   -1,   -1,  124,  125,  287,  288,  289,  290,
  291,  292,  293,  294,  295,  296,  297,  298,  299,  300,
  301,  302,  303,  304,  305,  306,  371,   -1,   -1,  310,
  311,  371,   -1,   -1,   -1,   -1,   -1,   -1,  371,   -1,
  371,   -1,   -1,   -1,   -1,  371,   -1,   -1,  329,  330,
  331,  332,  333,  259,  335,   -1,  337,  312,  313,  314,
  315,  316,  317,  318,   -1,  259,   -1,   -1,   -1,  350,
   -1,   33,   -1,   -1,   -1,   -1,   -1,   -1,   40,   -1,
   -1,   43,   -1,   45,   -1,  317,   -1,  293,  294,   -1,
  371,  297,  314,  315,  316,  317,  318,   59,   -1,  293,
  294,   -1,   -1,  297,  385,  386,  257,  258,  259,  260,
  261,  262,  263,   -1,  265,  266,  267,  268,  269,  270,
  271,  272,  273,  274,  275,  276,  277,  278,  279,  280,
  281,  282,   -1,   -1,   -1,   -1,  287,  288,  289,  290,
  291,  292,  293,  294,  295,  296,  297,  298,  299,  300,
  301,  302,  303,  304,  305,  306,  350,   -1,   -1,  310,
  311,  123,   -1,  125,  126,  371,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  371,  329,  330,
  331,  332,  333,   -1,  335,   -1,   -1,   -1,  308,  309,
   -1,   -1,  312,  313,  314,  315,  316,  317,  318,  350,
   -1,   33,   -1,   -1,   -1,   -1,   -1,   -1,   40,   -1,
   -1,   43,   -1,   45,   -1,   -1,   -1,   -1,   -1,   -1,
  371,   -1,   -1,   -1,   -1,   -1,   -1,   59,   -1,   -1,
   -1,   -1,   -1,   -1,  385,  386,   -1,   -1,   41,   -1,
   -1,   44,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   58,   59,   -1,   -1,   -1,
   63,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   38,   -1,
   -1,   41,   -1,   -1,   44,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   58,   59,
   93,  123,   -1,   63,  126,  257,  258,  259,  260,  261,
  262,  263,   -1,  265,  266,  267,  268,  269,  270,   -1,
   -1,  273,  274,  275,  276,  277,  278,  279,  280,  281,
  282,  124,  125,   93,   94,  287,  288,  289,  290,  291,
  292,  293,  294,  295,  296,  297,  298,  299,  300,  301,
  302,  303,  304,  305,  306,   -1,   -1,   -1,  310,  311,
   -1,   -1,   -1,   -1,  124,  125,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  329,  330,  331,
  332,  333,   -1,  335,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   33,  350,   -1,
   -1,   -1,   -1,   -1,   40,   -1,   -1,   43,   -1,   45,
   41,   -1,   -1,   44,   -1,   -1,   -1,   -1,   -1,  371,
   -1,   -1,   -1,   59,   -1,   -1,   -1,   58,   59,   -1,
   -1,   -1,   63,  385,  386,  257,  258,  259,  260,  261,
  262,  263,   -1,  265,  266,  267,  268,  269,  270,   -1,
   -1,  273,  274,  275,  276,  277,  278,  279,  280,  281,
  282,   -1,   93,   94,   -1,  287,  288,  289,  290,  291,
  292,  293,  294,  295,  296,  297,  298,  299,  300,  301,
  302,  303,  304,  305,  306,   -1,   -1,  123,  310,  311,
  126,   -1,   -1,  124,  125,   -1,   -1,   -1,   -1,   -1,
  258,   -1,   -1,   -1,   -1,   -1,   -1,  329,  330,  331,
  332,  333,   -1,  335,   -1,   -1,  274,  275,  276,   -1,
   -1,   -1,   -1,  316,  317,  318,   -1,   33,  350,  287,
  288,  289,  290,  291,   40,   -1,   -1,   43,   -1,   45,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  371,
   -1,   -1,   -1,   59,  314,  315,  316,  317,  318,   -1,
   -1,   -1,   -1,  385,  386,   -1,   41,   -1,   -1,   44,
   -1,   -1,  330,  331,  332,  333,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   58,   59,   33,   -1,   -1,   63,   -1,
   -1,   -1,   40,   -1,   -1,   43,   -1,   45,   -1,   -1,
   -1,   -1,   -1,  220,   -1,   -1,   -1,   -1,   -1,   -1,
  227,   59,   -1,   -1,   -1,   -1,   -1,  123,   93,   94,
  126,  257,  258,  259,  260,  261,  262,  263,   -1,  265,
  266,  267,  268,  269,  270,   -1,   -1,  273,  274,  275,
  276,  277,  278,  279,  280,  281,  282,   -1,   -1,  124,
  125,  287,  288,  289,  290,  291,  292,  293,  294,  295,
  296,  297,  298,  299,  300,  301,  302,  303,  304,  305,
  306,   -1,   33,   -1,  310,  311,   -1,   -1,  126,   40,
   -1,   -1,   43,   -1,   45,  316,  317,  318,   -1,   -1,
   -1,   -1,   -1,  329,  330,  331,  332,  333,   59,  335,
  317,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  325,   -1,
   -1,  328,   -1,   -1,  350,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  347,   -1,   -1,   -1,   -1,  371,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  360,   -1,   -1,  363,   -1,   -1,  385,
  386,  257,  258,  259,  260,  261,  262,  263,   -1,  265,
  266,  267,  268,  269,  270,  126,   -1,  273,  274,  275,
  276,  277,  278,  279,  280,  281,  282,   -1,   -1,   -1,
   -1,  287,  288,  289,  290,  291,  292,  293,  294,  295,
  296,  297,  298,  299,  300,  301,  302,  303,  304,  305,
  306,   -1,   33,  420,  310,  311,   -1,   -1,  425,   40,
  427,  259,   43,   -1,   45,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  329,  330,  331,  332,  333,   -1,  335,
   -1,   -1,   -1,   -1,  451,   -1,   -1,   -1,   -1,   -1,
   -1,  316,  317,  318,  350,  293,  294,   -1,  296,  297,
  298,  299,  300,  301,  302,  303,  304,  305,  306,   -1,
   -1,   -1,  310,  311,   33,  371,   -1,   -1,   -1,   -1,
   -1,   40,   -1,   -1,   43,   -1,   45,   -1,   -1,  385,
  386,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  126,  257,  258,  259,   -1,
  261,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  273,  274,  275,  276,  277,  278,  279,  280,
  281,  282,   -1,  371,   93,   -1,  287,  288,  289,  290,
  291,  292,  293,  294,   -1,  296,  297,  298,  299,  300,
  301,  302,  303,  304,  305,  306,   33,   -1,   -1,  310,
  311,   -1,   -1,   40,   -1,   -1,   43,  126,   45,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  329,  330,
  331,  332,  333,   -1,  335,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  350,
   -1,   -1,   -1,   -1,   -1,   33,   -1,   -1,   -1,   -1,
   -1,   -1,   40,   -1,   -1,   43,   93,   45,   -1,   -1,
  371,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   33,   -1,  385,  386,  257,  258,  259,   40,
  261,   -1,   43,   -1,   45,   -1,   -1,   -1,   -1,  126,
   -1,   -1,  273,  274,  275,  276,  277,  278,  279,  280,
  281,  282,   -1,   -1,   -1,   -1,  287,  288,  289,  290,
  291,  292,  293,  294,   -1,  296,  297,  298,  299,  300,
  301,  302,  303,  304,  305,  306,   -1,   -1,   -1,  310,
  311,   -1,   -1,   -1,   -1,  123,   -1,   -1,  126,   38,
  259,   -1,   41,   -1,   -1,   44,   -1,   -1,  329,  330,
  331,  332,  333,   -1,   -1,   -1,   59,   -1,   -1,   58,
   59,   60,   -1,   62,   63,  126,   -1,   -1,   -1,  350,
   -1,   -1,   -1,   -1,  293,  294,   -1,  296,  297,  298,
  299,  300,  301,  302,  303,  304,  305,  306,   -1,   -1,
  371,  310,  311,   -1,   93,   94,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  385,  386,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  259,   39,   40,  124,  125,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   57,   -1,   59,   60,   61,   62,   63,   64,   -1,
   -1,   -1,  371,   -1,   -1,   -1,  293,  294,   59,  296,
  297,  298,  299,  300,  301,  302,  303,  304,  305,  306,
   -1,  259,   -1,  310,  311,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   98,   99,   -1,   -1,  102,  103,  104,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  259,   -1,
   -1,   -1,   -1,   -1,   -1,  293,  294,   -1,  296,  297,
  298,  299,  300,  301,  302,  303,  304,  305,  306,  135,
   -1,   -1,  310,  311,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  293,  294,  371,  296,  297,  298,  299,  300,
  301,  302,  303,  304,  305,  306,   -1,   -1,   -1,  310,
  311,   -1,   -1,   -1,  257,  258,  259,   -1,  261,   59,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  273,  274,  275,  276,  277,  278,  279,  280,  281,  282,
   -1,   -1,   -1,  371,  287,  288,  289,  290,  291,  292,
  293,  294,   -1,   -1,  297,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  371,   -1,   -1,  312,  313,  314,  315,  316,  317,  318,
   -1,   -1,   -1,   -1,   -1,   -1,  329,  330,  331,  332,
  333,   -1,  335,   -1,  337,   -1,   -1,   -1,   -1,   -1,
  343,  344,  345,  346,  347,  348,  349,  350,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  257,  258,  259,   59,
  261,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  371,   -1,
   -1,   -1,  273,  274,  275,  276,  277,  278,  279,  280,
  281,  282,  385,  386,   -1,   -1,  287,  288,  289,  290,
  291,  292,  293,  294,   -1,   -1,  297,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  194,   -1,   -1,   -1,   -1,   -1,   -1,  329,  330,
  331,  332,  333,   -1,  335,   -1,  337,   -1,   -1,   -1,
   -1,   -1,  343,  344,  345,  346,  347,  348,  349,  350,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  257,  258,  259,
   -1,  261,   -1,   -1,  237,   -1,   -1,   -1,   -1,   -1,
  371,   -1,   -1,  273,  274,  275,  276,  277,  278,  279,
  280,  281,  282,   -1,  385,  386,   -1,  287,  288,  289,
  290,  291,  292,  293,  294,   -1,   -1,  297,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  292,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  329,
  330,  331,  332,  333,   -1,  335,   -1,   -1,   -1,   -1,
   -1,   -1,  315,  343,  344,  345,  346,  347,  348,  349,
  350,   -1,   -1,   -1,   -1,   -1,   -1,  257,  258,  259,
   -1,  261,  335,   -1,   -1,   -1,   -1,  340,  341,   -1,
   -1,  371,   -1,  273,  274,  275,  276,  277,  278,  279,
  280,  281,  282,   -1,   -1,  385,  386,  287,  288,  289,
  290,  291,  292,  293,  294,   37,   38,  297,   40,   41,
   42,   43,   44,   45,   -1,   47,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   58,   59,   60,   61,
   62,   63,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  329,
  330,  331,  332,  333,  407,  335,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  343,  344,  345,  346,  347,  348,  349,
  350,   93,   94,   37,   38,   -1,  429,   41,   42,   43,
   44,   45,   -1,   47,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  371,  445,   -1,   58,   59,   60,   -1,   62,   63,
   -1,   -1,  124,  125,  457,  385,  386,   -1,   -1,   -1,
   -1,   38,   -1,   -1,   41,   -1,   43,   44,   45,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   93,
   94,   58,   59,   60,   38,   62,   63,   41,   -1,   43,
   44,   45,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   58,   59,   60,   -1,   62,   63,
  124,  125,   -1,   -1,   -1,   -1,   93,   94,   -1,   -1,
   -1,   38,   -1,   -1,   41,   -1,   43,   44,   45,   -1,
   -1,   -1,   38,   -1,   -1,   41,   -1,   -1,   44,   93,
   94,   58,   59,   60,   -1,   62,   63,  124,  125,   -1,
   -1,   -1,   58,   59,   60,   -1,   62,   63,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  124,  125,   38,   -1,   -1,   41,   93,   94,   44,   38,
   -1,   -1,   41,   -1,   -1,   44,   -1,   93,   94,   -1,
   -1,   -1,   58,   59,   60,   -1,   62,   63,   -1,   58,
   59,   60,   -1,   62,   63,   -1,   -1,  124,  125,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  124,  125,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   93,   94,   -1,
   -1,   -1,   -1,   -1,   93,   94,  308,  309,   -1,   -1,
  312,  313,  314,  315,  316,  317,  318,  319,  320,  321,
  322,  323,  324,  325,  326,  327,  328,   38,  124,  125,
   41,   -1,   -1,   44,   38,  124,  125,   41,   -1,   -1,
   44,   -1,   -1,   -1,   -1,   -1,   -1,   58,   59,   60,
   -1,   62,   63,   -1,   58,   59,   60,   -1,   62,   63,
   -1,   -1,   -1,   -1,  308,  309,   -1,   -1,  312,  313,
  314,  315,  316,  317,  318,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   93,   94,   -1,   -1,   -1,   -1,   -1,   93,
   94,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  308,  309,   -1,   -1,  312,  313,  314,  315,  316,
  317,  318,  125,  124,  125,   -1,   -1,   -1,   -1,   -1,
  124,  125,   -1,   -1,  308,  309,   -1,   -1,  312,  313,
  314,  315,  316,  317,  318,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  308,  309,   -1,   -1,  312,  313,  314,  315,  316,
  317,  318,  308,  309,   -1,   -1,  312,  313,  314,  315,
  316,  317,  318,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  125,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  308,  309,   -1,   -1,  312,  313,  314,  315,
  316,  317,  318,  312,  313,  314,  315,  316,  317,  318,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  257,  258,  259,   -1,  261,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  273,  274,  275,  276,  277,  278,  279,  280,  281,  282,
   -1,   -1,   -1,   -1,  287,  288,  289,  290,  291,  292,
  293,  294,   -1,   -1,  297,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  312,  313,  314,  315,  316,  317,  318,  312,  313,
  314,  315,  316,  317,  318,   -1,  329,  330,  331,  332,
  333,  139,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  257,
  258,  259,   -1,  261,   -1,   -1,   -1,  350,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  273,  274,  275,  276,  277,
  278,  279,  280,  281,  282,   -1,   -1,   -1,  371,  287,
  288,  289,  290,  291,  292,  293,  294,   -1,   -1,  297,
   -1,   -1,  385,  386,  192,  193,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  329,  330,  331,  332,  333,  224,   -1,  226,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  350,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  371,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  385,  386,   -1,
   -1,   -1,  280,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  291,   -1,  293,  294,  295,  296,  297,
  298,  299,  300,  301,  302,  303,  304,  305,  306,  307,
  308,  309,  310,  257,  258,  259,   -1,  261,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  273,
  274,  275,  276,  277,  278,  279,  280,  281,  282,   -1,
   -1,   -1,   -1,  287,  288,  289,  290,  291,  292,  293,
  294,   -1,   -1,  297,  298,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  257,  258,  259,
   -1,  261,   -1,   -1,   -1,  329,  330,  331,  332,  333,
   -1,   -1,   -1,  273,  274,  275,  276,  277,  278,  279,
  280,  281,  282,   -1,   -1,   -1,  350,  287,  288,  289,
  290,  291,  292,  293,  294,   -1,   -1,  297,  298,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  371,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  385,  386,  257,  258,  259,   -1,  261,   -1,  329,
  330,  331,  332,  333,   -1,   -1,   -1,   -1,   -1,  273,
  274,  275,  276,  277,  278,  279,  280,  281,  282,   -1,
  350,   -1,   -1,  287,  288,  289,  290,  291,  292,  293,
  294,   -1,   -1,  297,  298,   -1,   -1,   -1,   -1,   -1,
   -1,  371,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  385,  386,  257,  258,  259,
   -1,  261,   -1,   -1,   -1,  329,  330,  331,  332,  333,
   -1,   -1,   -1,  273,  274,  275,  276,  277,  278,  279,
  280,  281,  282,   -1,   -1,   -1,  350,  287,  288,  289,
  290,  291,  292,  293,  294,   -1,   -1,  297,  298,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  371,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  385,  386,  257,  258,  259,   -1,  261,   -1,  329,
  330,  331,  332,  333,   -1,   -1,   -1,   -1,   -1,  273,
  274,  275,  276,  277,  278,  279,  280,  281,  282,   -1,
  350,   -1,   -1,  287,  288,  289,  290,  291,  292,  293,
  294,   -1,   -1,  297,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  371,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  385,  386,  257,  258,  259,
   -1,  261,   -1,   -1,   -1,  329,  330,  331,  332,  333,
   -1,   -1,   -1,  273,  274,  275,  276,  277,  278,  279,
  280,  281,  282,   -1,   -1,   -1,  350,  287,  288,  289,
  290,  291,  292,  293,  294,   -1,   -1,  297,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  371,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  385,  386,  257,  258,   -1,   -1,  261,   -1,  329,
  330,  331,  332,  333,   -1,   -1,   -1,   -1,   -1,  273,
  274,  275,  276,  277,  278,  279,  280,  281,  282,   -1,
  350,   -1,   -1,  287,  288,  289,  290,  291,  292,   -1,
   -1,   -1,  296,   -1,  298,   -1,   -1,   -1,   -1,   -1,
   -1,  371,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  385,  386,  257,  258,   -1,
   -1,  261,   -1,   -1,   -1,  329,  330,  331,  332,  333,
   -1,   -1,   -1,  273,  274,  275,  276,  277,  278,  279,
  280,  281,  282,   -1,   -1,   -1,  350,  287,  288,  289,
  290,  291,  292,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  385,  386,  257,  258,   -1,   -1,  261,   -1,  329,
  330,  331,  332,  333,   -1,   -1,   -1,   -1,   -1,  273,
  274,  275,  276,  277,  278,  279,  280,  281,  282,   -1,
  350,   -1,   -1,  287,  288,  289,  290,  291,  292,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  385,  386,  257,  258,   -1,
   -1,  261,   -1,   -1,   -1,  329,  330,  331,  332,  333,
   -1,   -1,   -1,  273,  274,  275,  276,  277,  278,  279,
  280,  281,  282,   -1,   -1,   -1,  350,  287,  288,  289,
  290,  291,  292,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  385,  386,   -1,   -1,   -1,   -1,   -1,   -1,  329,
  330,  331,  332,  333,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  350,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  385,  386,
};
#if YYBTYACC
static const YYINT _mesa_glsl_ctable[] = {               -1,
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
   -1,   -1,   -1,   -1,   -1,   -1,
};
#endif
#define YYFINAL 2
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 393
#define YYUNDFTOKEN 505
#define YYTRANSLATE(a) ((a) > YYMAXTOKEN ? YYUNDFTOKEN : (a))
#if YYDEBUG
#ifndef NULL
#define NULL (void*)0
#endif
static const char *const _mesa_glsl_name[] = {

"$end",NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,
NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,
NULL,NULL,"'!'",NULL,NULL,NULL,"'%'","'&'",NULL,"'('","')'","'*'","'+'","','",
"'-'",NULL,"'/'",NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,"':'","';'",
"'<'","'='","'>'","'?'",NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,
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
NULL,NULL,NULL,NULL,NULL,NULL,NULL,"error","ATTRIBUTE","CONST_TOK",
"BASIC_TYPE_TOK","BREAK","BUFFER","CONTINUE","DO","ELSE","FOR","IF","DEMOTE",
"DISCARD","RETURN","SWITCH","CASE","DEFAULT","CENTROID","IN_TOK","OUT_TOK",
"INOUT_TOK","UNIFORM","VARYING","SAMPLE","NOPERSPECTIVE","FLAT","SMOOTH",
"IMAGE1DSHADOW","IMAGE2DSHADOW","IMAGE1DARRAYSHADOW","IMAGE2DARRAYSHADOW",
"COHERENT","VOLATILE","RESTRICT","READONLY","WRITEONLY","SHARED","STRUCT",
"VOID_TOK","WHILE","IDENTIFIER","TYPE_IDENTIFIER","NEW_IDENTIFIER",
"FLOATCONSTANT","FLOAT16CONSTANT","DOUBLECONSTANT","INTCONSTANT","UINTCONSTANT",
"BOOLCONSTANT","INT64CONSTANT","UINT64CONSTANT","FIELD_SELECTION","LEFT_OP",
"RIGHT_OP","INC_OP","DEC_OP","LE_OP","GE_OP","EQ_OP","NE_OP","AND_OP","OR_OP",
"XOR_OP","MUL_ASSIGN","DIV_ASSIGN","ADD_ASSIGN","MOD_ASSIGN","LEFT_ASSIGN",
"RIGHT_ASSIGN","AND_ASSIGN","XOR_ASSIGN","OR_ASSIGN","SUB_ASSIGN","INVARIANT",
"PRECISE","LOWP","MEDIUMP","HIGHP","SUPERP","PRECISION","VERSION_TOK",
"EXTENSION","LINE","COLON","EOL","INTERFACE_TOK","OUTPUT","PRAGMA_DEBUG_ON",
"PRAGMA_DEBUG_OFF","PRAGMA_OPTIMIZE_ON","PRAGMA_OPTIMIZE_OFF",
"PRAGMA_WARNING_ON","PRAGMA_WARNING_OFF","PRAGMA_INVARIANT_ALL","LAYOUT_TOK",
"DOT_TOK","ASM","CLASS","UNION","ENUM","TYPEDEF","TEMPLATE","THIS","PACKED_TOK",
"GOTO","INLINE_TOK","NOINLINE","PUBLIC_TOK","STATIC","EXTERN","EXTERNAL",
"LONG_TOK","SHORT_TOK","HALF","FIXED_TOK","UNSIGNED","INPUT_TOK","HVEC2",
"HVEC3","HVEC4","FVEC2","FVEC3","FVEC4","SAMPLER3DRECT","SIZEOF","CAST",
"NAMESPACE","USING","RESOURCE","PATCH","SUBROUTINE","ERROR_TOK","COMMON",
"PARTITION","ACTIVE","FILTER","ROW_MAJOR","THEN","$accept","translation_unit",
"any_identifier","instance_name_opt","variable_identifier","statement",
"statement_list","simple_statement","precision_qualifier","type_qualifier",
"auxiliary_storage_qualifier","storage_qualifier","interpolation_qualifier",
"layout_qualifier","layout_qualifier_id_list","layout_qualifier_id",
"interface_block_layout_qualifier","memory_qualifier","subroutine_qualifier",
"subroutine_type_list","interface_qualifier","type_specifier",
"type_specifier_nonarray","array_specifier","basic_type_specifier_nonarray",
"fully_specified_type","function_prototype","function_header",
"function_header_with_parameters","function_declarator","parameter_declarator",
"parameter_declaration","parameter_qualifier","parameter_direction_qualifier",
"parameter_type_specifier","function_definition",
"compound_statement_no_new_scope","compound_statement","statement_no_new_scope",
"expression_statement","expression","primary_expression",
"assignment_expression","conditional_expression","logical_or_expression",
"logical_xor_expression","logical_and_expression","inclusive_or_expression",
"exclusive_or_expression","and_expression","equality_expression",
"relational_expression","shift_expression","additive_expression",
"multiplicative_expression","unary_expression","constant_expression",
"integer_expression","postfix_expression",
"function_call_header_with_parameters","function_call_header_no_parameters",
"function_call_header","function_call_generic","function_call_or_method",
"function_call","assignment_operator","unary_operator","function_identifier",
"external_declaration","pragma_statement","init_declarator_list",
"single_declaration","initializer","initializer_list","declaration",
"declaration_statement","jump_statement","demote_statement","interface_block",
"basic_interface_block","struct_specifier","struct_declaration_list",
"struct_declaration","struct_declarator","struct_declarator_list","member_list",
"member_declaration","selection_statement","selection_rest_statement",
"switch_statement","switch_body","case_label_list","case_label",
"case_statement","case_statement_list","iteration_statement","condition",
"conditionopt","for_init_statement","for_rest_statement","layout_defaults",
"layout_uniform_defaults","layout_buffer_defaults","layout_in_defaults",
"layout_out_defaults","version_statement","extension_statement_list",
"external_declaration_list","$$1","extension_statement","$$2","illegal-symbol",
};
static const char *const _mesa_glsl_rule[] = {
"$accept : translation_unit",
"$$1 :",
"translation_unit : version_statement extension_statement_list $$1 external_declaration_list",
"version_statement :",
"version_statement : VERSION_TOK INTCONSTANT EOL",
"version_statement : VERSION_TOK INTCONSTANT any_identifier EOL",
"pragma_statement : PRAGMA_DEBUG_ON EOL",
"pragma_statement : PRAGMA_DEBUG_OFF EOL",
"pragma_statement : PRAGMA_OPTIMIZE_ON EOL",
"pragma_statement : PRAGMA_OPTIMIZE_OFF EOL",
"pragma_statement : PRAGMA_INVARIANT_ALL EOL",
"pragma_statement : PRAGMA_WARNING_ON EOL",
"pragma_statement : PRAGMA_WARNING_OFF EOL",
"extension_statement_list :",
"extension_statement_list : extension_statement_list extension_statement",
"any_identifier : IDENTIFIER",
"any_identifier : TYPE_IDENTIFIER",
"any_identifier : NEW_IDENTIFIER",
"extension_statement : EXTENSION any_identifier COLON any_identifier EOL",
"external_declaration_list : external_declaration",
"external_declaration_list : external_declaration_list external_declaration",
"external_declaration_list : external_declaration_list extension_statement",
"variable_identifier : IDENTIFIER",
"variable_identifier : NEW_IDENTIFIER",
"primary_expression : variable_identifier",
"primary_expression : INTCONSTANT",
"primary_expression : UINTCONSTANT",
"primary_expression : INT64CONSTANT",
"primary_expression : UINT64CONSTANT",
"primary_expression : FLOAT16CONSTANT",
"primary_expression : FLOATCONSTANT",
"primary_expression : DOUBLECONSTANT",
"primary_expression : BOOLCONSTANT",
"primary_expression : '(' expression ')'",
"postfix_expression : primary_expression",
"postfix_expression : postfix_expression '[' integer_expression ']'",
"postfix_expression : function_call",
"postfix_expression : postfix_expression DOT_TOK FIELD_SELECTION",
"postfix_expression : postfix_expression INC_OP",
"postfix_expression : postfix_expression DEC_OP",
"integer_expression : expression",
"function_call : function_call_or_method",
"function_call_or_method : function_call_generic",
"function_call_generic : function_call_header_with_parameters ')'",
"function_call_generic : function_call_header_no_parameters ')'",
"function_call_header_no_parameters : function_call_header VOID_TOK",
"function_call_header_no_parameters : function_call_header",
"function_call_header_with_parameters : function_call_header assignment_expression",
"function_call_header_with_parameters : function_call_header_with_parameters ',' assignment_expression",
"function_call_header : function_identifier '('",
"function_identifier : type_specifier",
"function_identifier : postfix_expression",
"unary_expression : postfix_expression",
"unary_expression : INC_OP unary_expression",
"unary_expression : DEC_OP unary_expression",
"unary_expression : unary_operator unary_expression",
"unary_operator : '+'",
"unary_operator : '-'",
"unary_operator : '!'",
"unary_operator : '~'",
"multiplicative_expression : unary_expression",
"multiplicative_expression : multiplicative_expression '*' unary_expression",
"multiplicative_expression : multiplicative_expression '/' unary_expression",
"multiplicative_expression : multiplicative_expression '%' unary_expression",
"additive_expression : multiplicative_expression",
"additive_expression : additive_expression '+' multiplicative_expression",
"additive_expression : additive_expression '-' multiplicative_expression",
"shift_expression : additive_expression",
"shift_expression : shift_expression LEFT_OP additive_expression",
"shift_expression : shift_expression RIGHT_OP additive_expression",
"relational_expression : shift_expression",
"relational_expression : relational_expression '<' shift_expression",
"relational_expression : relational_expression '>' shift_expression",
"relational_expression : relational_expression LE_OP shift_expression",
"relational_expression : relational_expression GE_OP shift_expression",
"equality_expression : relational_expression",
"equality_expression : equality_expression EQ_OP relational_expression",
"equality_expression : equality_expression NE_OP relational_expression",
"and_expression : equality_expression",
"and_expression : and_expression '&' equality_expression",
"exclusive_or_expression : and_expression",
"exclusive_or_expression : exclusive_or_expression '^' and_expression",
"inclusive_or_expression : exclusive_or_expression",
"inclusive_or_expression : inclusive_or_expression '|' exclusive_or_expression",
"logical_and_expression : inclusive_or_expression",
"logical_and_expression : logical_and_expression AND_OP inclusive_or_expression",
"logical_xor_expression : logical_and_expression",
"logical_xor_expression : logical_xor_expression XOR_OP logical_and_expression",
"logical_or_expression : logical_xor_expression",
"logical_or_expression : logical_or_expression OR_OP logical_xor_expression",
"conditional_expression : logical_or_expression",
"conditional_expression : logical_or_expression '?' expression ':' assignment_expression",
"assignment_expression : conditional_expression",
"assignment_expression : unary_expression assignment_operator assignment_expression",
"assignment_operator : '='",
"assignment_operator : MUL_ASSIGN",
"assignment_operator : DIV_ASSIGN",
"assignment_operator : MOD_ASSIGN",
"assignment_operator : ADD_ASSIGN",
"assignment_operator : SUB_ASSIGN",
"assignment_operator : LEFT_ASSIGN",
"assignment_operator : RIGHT_ASSIGN",
"assignment_operator : AND_ASSIGN",
"assignment_operator : XOR_ASSIGN",
"assignment_operator : OR_ASSIGN",
"expression : assignment_expression",
"expression : expression ',' assignment_expression",
"constant_expression : conditional_expression",
"declaration : function_prototype ';'",
"declaration : init_declarator_list ';'",
"declaration : PRECISION precision_qualifier type_specifier ';'",
"declaration : interface_block",
"function_prototype : function_declarator ')'",
"function_declarator : function_header",
"function_declarator : function_header_with_parameters",
"function_header_with_parameters : function_header parameter_declaration",
"function_header_with_parameters : function_header_with_parameters ',' parameter_declaration",
"function_header : fully_specified_type variable_identifier '('",
"parameter_declarator : type_specifier any_identifier",
"parameter_declarator : layout_qualifier type_specifier any_identifier",
"parameter_declarator : type_specifier any_identifier array_specifier",
"parameter_declaration : parameter_qualifier parameter_declarator",
"parameter_declaration : parameter_qualifier parameter_type_specifier",
"parameter_qualifier :",
"parameter_qualifier : CONST_TOK parameter_qualifier",
"parameter_qualifier : PRECISE parameter_qualifier",
"parameter_qualifier : parameter_direction_qualifier parameter_qualifier",
"parameter_qualifier : precision_qualifier parameter_qualifier",
"parameter_qualifier : memory_qualifier parameter_qualifier",
"parameter_direction_qualifier : IN_TOK",
"parameter_direction_qualifier : OUT_TOK",
"parameter_direction_qualifier : INOUT_TOK",
"parameter_type_specifier : type_specifier",
"init_declarator_list : single_declaration",
"init_declarator_list : init_declarator_list ',' any_identifier",
"init_declarator_list : init_declarator_list ',' any_identifier array_specifier",
"init_declarator_list : init_declarator_list ',' any_identifier array_specifier '=' initializer",
"init_declarator_list : init_declarator_list ',' any_identifier '=' initializer",
"single_declaration : fully_specified_type",
"single_declaration : fully_specified_type any_identifier",
"single_declaration : fully_specified_type any_identifier array_specifier",
"single_declaration : fully_specified_type any_identifier array_specifier '=' initializer",
"single_declaration : fully_specified_type any_identifier '=' initializer",
"single_declaration : INVARIANT variable_identifier",
"single_declaration : PRECISE variable_identifier",
"fully_specified_type : type_specifier",
"fully_specified_type : type_qualifier type_specifier",
"layout_qualifier : LAYOUT_TOK '(' layout_qualifier_id_list ')'",
"layout_qualifier_id_list : layout_qualifier_id",
"layout_qualifier_id_list : layout_qualifier_id_list ',' layout_qualifier_id",
"layout_qualifier_id : any_identifier",
"layout_qualifier_id : any_identifier '=' constant_expression",
"layout_qualifier_id : interface_block_layout_qualifier",
"interface_block_layout_qualifier : ROW_MAJOR",
"interface_block_layout_qualifier : PACKED_TOK",
"interface_block_layout_qualifier : SHARED",
"subroutine_qualifier : SUBROUTINE",
"subroutine_qualifier : SUBROUTINE '(' subroutine_type_list ')'",
"subroutine_type_list : any_identifier",
"subroutine_type_list : subroutine_type_list ',' any_identifier",
"interpolation_qualifier : SMOOTH",
"interpolation_qualifier : FLAT",
"interpolation_qualifier : NOPERSPECTIVE",
"type_qualifier : INVARIANT",
"type_qualifier : PRECISE",
"type_qualifier : auxiliary_storage_qualifier",
"type_qualifier : storage_qualifier",
"type_qualifier : interpolation_qualifier",
"type_qualifier : layout_qualifier",
"type_qualifier : memory_qualifier",
"type_qualifier : subroutine_qualifier",
"type_qualifier : precision_qualifier",
"type_qualifier : PRECISE type_qualifier",
"type_qualifier : INVARIANT type_qualifier",
"type_qualifier : interpolation_qualifier type_qualifier",
"type_qualifier : layout_qualifier type_qualifier",
"type_qualifier : subroutine_qualifier type_qualifier",
"type_qualifier : auxiliary_storage_qualifier type_qualifier",
"type_qualifier : storage_qualifier type_qualifier",
"type_qualifier : precision_qualifier type_qualifier",
"type_qualifier : memory_qualifier type_qualifier",
"auxiliary_storage_qualifier : CENTROID",
"auxiliary_storage_qualifier : SAMPLE",
"auxiliary_storage_qualifier : PATCH",
"storage_qualifier : CONST_TOK",
"storage_qualifier : ATTRIBUTE",
"storage_qualifier : VARYING",
"storage_qualifier : IN_TOK",
"storage_qualifier : OUT_TOK",
"storage_qualifier : INOUT_TOK",
"storage_qualifier : UNIFORM",
"storage_qualifier : BUFFER",
"storage_qualifier : SHARED",
"memory_qualifier : COHERENT",
"memory_qualifier : VOLATILE",
"memory_qualifier : RESTRICT",
"memory_qualifier : READONLY",
"memory_qualifier : WRITEONLY",
"array_specifier : '[' ']'",
"array_specifier : '[' constant_expression ']'",
"array_specifier : array_specifier '[' ']'",
"array_specifier : array_specifier '[' constant_expression ']'",
"type_specifier : type_specifier_nonarray",
"type_specifier : type_specifier_nonarray array_specifier",
"type_specifier_nonarray : basic_type_specifier_nonarray",
"type_specifier_nonarray : struct_specifier",
"type_specifier_nonarray : TYPE_IDENTIFIER",
"basic_type_specifier_nonarray : VOID_TOK",
"basic_type_specifier_nonarray : BASIC_TYPE_TOK",
"basic_type_specifier_nonarray : UNSIGNED BASIC_TYPE_TOK",
"precision_qualifier : HIGHP",
"precision_qualifier : MEDIUMP",
"precision_qualifier : LOWP",
"struct_specifier : STRUCT any_identifier '{' struct_declaration_list '}'",
"struct_specifier : STRUCT '{' struct_declaration_list '}'",
"struct_declaration_list : struct_declaration",
"struct_declaration_list : struct_declaration_list struct_declaration",
"struct_declaration : fully_specified_type struct_declarator_list ';'",
"struct_declarator_list : struct_declarator",
"struct_declarator_list : struct_declarator_list ',' struct_declarator",
"struct_declarator : any_identifier",
"struct_declarator : any_identifier array_specifier",
"initializer : assignment_expression",
"initializer : '{' initializer_list '}'",
"initializer : '{' initializer_list ',' '}'",
"initializer_list : initializer",
"initializer_list : initializer_list ',' initializer",
"declaration_statement : declaration",
"statement : compound_statement",
"statement : simple_statement",
"simple_statement : declaration_statement",
"simple_statement : expression_statement",
"simple_statement : selection_statement",
"simple_statement : switch_statement",
"simple_statement : iteration_statement",
"simple_statement : jump_statement",
"simple_statement : demote_statement",
"compound_statement : '{' '}'",
"$$2 :",
"compound_statement : '{' $$2 statement_list '}'",
"statement_no_new_scope : compound_statement_no_new_scope",
"statement_no_new_scope : simple_statement",
"compound_statement_no_new_scope : '{' '}'",
"compound_statement_no_new_scope : '{' statement_list '}'",
"statement_list : statement",
"statement_list : statement_list statement",
"statement_list : statement_list extension_statement",
"expression_statement : ';'",
"expression_statement : expression ';'",
"selection_statement : IF '(' expression ')' selection_rest_statement",
"selection_rest_statement : statement ELSE statement",
"selection_rest_statement : statement",
"condition : expression",
"condition : fully_specified_type any_identifier '=' initializer",
"switch_statement : SWITCH '(' expression ')' switch_body",
"switch_body : '{' '}'",
"switch_body : '{' case_statement_list '}'",
"case_label : CASE expression ':'",
"case_label : DEFAULT ':'",
"case_label_list : case_label",
"case_label_list : case_label_list case_label",
"case_statement : case_label_list statement",
"case_statement : case_statement statement",
"case_statement_list : case_statement",
"case_statement_list : case_statement_list case_statement",
"iteration_statement : WHILE '(' condition ')' statement_no_new_scope",
"iteration_statement : DO statement_no_new_scope WHILE '(' expression ')' ';'",
"iteration_statement : FOR '(' for_init_statement for_rest_statement ')' statement_no_new_scope",
"for_init_statement : expression_statement",
"for_init_statement : declaration_statement",
"conditionopt : condition",
"conditionopt :",
"for_rest_statement : conditionopt ';'",
"for_rest_statement : conditionopt ';' expression",
"jump_statement : CONTINUE ';'",
"jump_statement : BREAK ';'",
"jump_statement : RETURN ';'",
"jump_statement : RETURN expression ';'",
"jump_statement : DISCARD ';'",
"demote_statement : DEMOTE ';'",
"external_declaration : function_definition",
"external_declaration : declaration",
"external_declaration : pragma_statement",
"external_declaration : layout_defaults",
"external_declaration : ';'",
"function_definition : function_prototype compound_statement_no_new_scope",
"interface_block : basic_interface_block",
"interface_block : layout_qualifier interface_block",
"interface_block : memory_qualifier interface_block",
"basic_interface_block : interface_qualifier NEW_IDENTIFIER '{' member_list '}' instance_name_opt ';'",
"interface_qualifier : IN_TOK",
"interface_qualifier : OUT_TOK",
"interface_qualifier : UNIFORM",
"interface_qualifier : BUFFER",
"interface_qualifier : auxiliary_storage_qualifier interface_qualifier",
"instance_name_opt :",
"instance_name_opt : NEW_IDENTIFIER",
"instance_name_opt : NEW_IDENTIFIER array_specifier",
"member_list : member_declaration",
"member_list : member_declaration member_list",
"member_declaration : fully_specified_type struct_declarator_list ';'",
"layout_uniform_defaults : layout_qualifier layout_uniform_defaults",
"layout_uniform_defaults : layout_qualifier UNIFORM ';'",
"layout_buffer_defaults : layout_qualifier layout_buffer_defaults",
"layout_buffer_defaults : layout_qualifier BUFFER ';'",
"layout_in_defaults : layout_qualifier layout_in_defaults",
"layout_in_defaults : layout_qualifier IN_TOK ';'",
"layout_out_defaults : layout_qualifier layout_out_defaults",
"layout_out_defaults : layout_qualifier OUT_TOK ';'",
"layout_defaults : layout_uniform_defaults",
"layout_defaults : layout_buffer_defaults",
"layout_defaults : layout_in_defaults",
"layout_defaults : layout_out_defaults",

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

#line 89 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
   yyloc.first_line = 1;
   yyloc.first_column = 1;
   yyloc.last_line = 1;
   yyloc.last_column = 1;
   yyloc.source = 0;
   yyloc.path = NULL;
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
case 1:
#line 295 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      _mesa_glsl_initialize_types(state);
   }
#line 3221 "compiler/glsl/glsl_parser.cpp"
break;
case 2:
#line 299 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      delete state->symbols;
      state->symbols = new(ralloc_parent(state)) glsl_symbol_table;
      if (state->es_shader) {
         if (state->stage == MESA_SHADER_FRAGMENT) {
            state->symbols->add_default_precision_qualifier("int", ast_precision_medium);
         } else {
            state->symbols->add_default_precision_qualifier("float", ast_precision_high);
            state->symbols->add_default_precision_qualifier("int", ast_precision_high);
         }
         state->symbols->add_default_precision_qualifier("sampler2D", ast_precision_low);
         state->symbols->add_default_precision_qualifier("samplerExternalOES", ast_precision_low);
         state->symbols->add_default_precision_qualifier("samplerCube", ast_precision_low);
         state->symbols->add_default_precision_qualifier("atomic_uint", ast_precision_high);
      }
      _mesa_glsl_initialize_types(state);
   }
#line 3242 "compiler/glsl/glsl_parser.cpp"
break;
case 4:
#line 321 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      state->process_version_directive(&yystack.p_mark[-1], yystack.l_mark[-1].n, NULL);
      if (state->error) {
         YYERROR;
      }
   }
#line 3252 "compiler/glsl/glsl_parser.cpp"
break;
case 5:
#line 328 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      state->process_version_directive(&yystack.p_mark[-2], yystack.l_mark[-2].n, yystack.l_mark[-1].identifier);
      if (state->error) {
         YYERROR;
      }
   }
#line 3262 "compiler/glsl/glsl_parser.cpp"
break;
case 6:
#line 337 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{ yyval.node = NULL; }
#line 3267 "compiler/glsl/glsl_parser.cpp"
break;
case 7:
#line 338 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{ yyval.node = NULL; }
#line 3272 "compiler/glsl/glsl_parser.cpp"
break;
case 8:
#line 339 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{ yyval.node = NULL; }
#line 3277 "compiler/glsl/glsl_parser.cpp"
break;
case 9:
#line 340 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{ yyval.node = NULL; }
#line 3282 "compiler/glsl/glsl_parser.cpp"
break;
case 10:
#line 342 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      /* Pragma invariant(all) cannot be used in a fragment shader.
       *
       * Page 27 of the GLSL 1.20 spec, Page 53 of the GLSL ES 3.00 spec:
       *
       *     "It is an error to use this pragma in a fragment shader."
       */
      if (state->is_version(120, 300) &&
          state->stage == MESA_SHADER_FRAGMENT) {
         _mesa_glsl_error(& yystack.p_mark[-1], state,
                          "pragma `invariant(all)' cannot be used "
                          "in a fragment shader.");
      } else if (!state->is_version(120, 100)) {
         _mesa_glsl_warning(& yystack.p_mark[-1], state,
                            "pragma `invariant(all)' not supported in %s "
                            "(GLSL ES 1.00 or GLSL 1.20 required)",
                            state->get_version_string());
      } else {
         state->all_invariant = true;
      }

      yyval.node = NULL;
   }
#line 3309 "compiler/glsl/glsl_parser.cpp"
break;
case 11:
#line 366 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      linear_ctx *mem_ctx = state->linalloc;
      yyval.node = new(mem_ctx) ast_warnings_toggle(true);
   }
#line 3317 "compiler/glsl/glsl_parser.cpp"
break;
case 12:
#line 371 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      linear_ctx *mem_ctx = state->linalloc;
      yyval.node = new(mem_ctx) ast_warnings_toggle(false);
   }
#line 3325 "compiler/glsl/glsl_parser.cpp"
break;
case 18:
#line 390 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      if (!_mesa_glsl_process_extension(yystack.l_mark[-3].identifier, & yystack.p_mark[-3], yystack.l_mark[-1].identifier, & yystack.p_mark[-1], state)) {
         YYERROR;
      }
   }
#line 3334 "compiler/glsl/glsl_parser.cpp"
break;
case 19:
#line 399 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      /* FINISHME: The NULL test is required because pragmas are set to
       * FINISHME: NULL. (See production rule for external_declaration.)
       */
      if (yystack.l_mark[0].node != NULL)
         state->translation_unit.push_tail(& yystack.l_mark[0].node->link);
   }
#line 3345 "compiler/glsl/glsl_parser.cpp"
break;
case 20:
#line 407 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      /* FINISHME: The NULL test is required because pragmas are set to
       * FINISHME: NULL. (See production rule for external_declaration.)
       */
      if (yystack.l_mark[0].node != NULL)
         state->translation_unit.push_tail(& yystack.l_mark[0].node->link);
   }
#line 3356 "compiler/glsl/glsl_parser.cpp"
break;
case 21:
#line 414 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      if (!state->allow_extension_directive_midshader) {
         _mesa_glsl_error(& yystack.p_mark[0], state,
                          "#extension directive is not allowed "
                          "in the middle of a shader");
         YYERROR;
      }
   }
#line 3368 "compiler/glsl/glsl_parser.cpp"
break;
case 24:
#line 431 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      linear_ctx *ctx = state->linalloc;
      yyval.expression = new(ctx) ast_expression(ast_identifier, NULL, NULL, NULL);
      yyval.expression->set_location(yystack.p_mark[0]);
      yyval.expression->primary_expression.identifier = yystack.l_mark[0].identifier;
   }
#line 3378 "compiler/glsl/glsl_parser.cpp"
break;
case 25:
#line 438 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      linear_ctx *ctx = state->linalloc;
      yyval.expression = new(ctx) ast_expression(ast_int_constant, NULL, NULL, NULL);
      yyval.expression->set_location(yystack.p_mark[0]);
      yyval.expression->primary_expression.int_constant = yystack.l_mark[0].n;
   }
#line 3388 "compiler/glsl/glsl_parser.cpp"
break;
case 26:
#line 445 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      linear_ctx *ctx = state->linalloc;
      yyval.expression = new(ctx) ast_expression(ast_uint_constant, NULL, NULL, NULL);
      yyval.expression->set_location(yystack.p_mark[0]);
      yyval.expression->primary_expression.uint_constant = yystack.l_mark[0].n;
   }
#line 3398 "compiler/glsl/glsl_parser.cpp"
break;
case 27:
#line 452 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      linear_ctx *ctx = state->linalloc;
      yyval.expression = new(ctx) ast_expression(ast_int64_constant, NULL, NULL, NULL);
      yyval.expression->set_location(yystack.p_mark[0]);
      yyval.expression->primary_expression.int64_constant = yystack.l_mark[0].n64;
   }
#line 3408 "compiler/glsl/glsl_parser.cpp"
break;
case 28:
#line 459 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      linear_ctx *ctx = state->linalloc;
      yyval.expression = new(ctx) ast_expression(ast_uint64_constant, NULL, NULL, NULL);
      yyval.expression->set_location(yystack.p_mark[0]);
      yyval.expression->primary_expression.uint64_constant = yystack.l_mark[0].n64;
   }
#line 3418 "compiler/glsl/glsl_parser.cpp"
break;
case 29:
#line 466 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      linear_ctx *ctx = state->linalloc;
      yyval.expression = new(ctx) ast_expression(ast_float16_constant, NULL, NULL, NULL);
      yyval.expression->set_location(yystack.p_mark[0]);
      yyval.expression->primary_expression.float16_constant = yystack.l_mark[0].real;
   }
#line 3428 "compiler/glsl/glsl_parser.cpp"
break;
case 30:
#line 473 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      linear_ctx *ctx = state->linalloc;
      yyval.expression = new(ctx) ast_expression(ast_float_constant, NULL, NULL, NULL);
      yyval.expression->set_location(yystack.p_mark[0]);
      yyval.expression->primary_expression.float_constant = yystack.l_mark[0].real;
   }
#line 3438 "compiler/glsl/glsl_parser.cpp"
break;
case 31:
#line 480 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      linear_ctx *ctx = state->linalloc;
      yyval.expression = new(ctx) ast_expression(ast_double_constant, NULL, NULL, NULL);
      yyval.expression->set_location(yystack.p_mark[0]);
      yyval.expression->primary_expression.double_constant = yystack.l_mark[0].dreal;
   }
#line 3448 "compiler/glsl/glsl_parser.cpp"
break;
case 32:
#line 487 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      linear_ctx *ctx = state->linalloc;
      yyval.expression = new(ctx) ast_expression(ast_bool_constant, NULL, NULL, NULL);
      yyval.expression->set_location(yystack.p_mark[0]);
      yyval.expression->primary_expression.bool_constant = yystack.l_mark[0].n;
   }
#line 3458 "compiler/glsl/glsl_parser.cpp"
break;
case 33:
#line 494 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      yyval.expression = yystack.l_mark[-1].expression;
   }
#line 3465 "compiler/glsl/glsl_parser.cpp"
break;
case 35:
#line 502 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      linear_ctx *ctx = state->linalloc;
      yyval.expression = new(ctx) ast_expression(ast_array_index, yystack.l_mark[-3].expression, yystack.l_mark[-1].expression, NULL);
      yyval.expression->set_location_range(yystack.p_mark[-3], yystack.p_mark[0]);
   }
#line 3474 "compiler/glsl/glsl_parser.cpp"
break;
case 36:
#line 508 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      yyval.expression = yystack.l_mark[0].expression;
   }
#line 3481 "compiler/glsl/glsl_parser.cpp"
break;
case 37:
#line 512 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      linear_ctx *ctx = state->linalloc;
      yyval.expression = new(ctx) ast_expression(ast_field_selection, yystack.l_mark[-2].expression, NULL, NULL);
      yyval.expression->set_location_range(yystack.p_mark[-2], yystack.p_mark[0]);
      yyval.expression->primary_expression.identifier = yystack.l_mark[0].identifier;
   }
#line 3491 "compiler/glsl/glsl_parser.cpp"
break;
case 38:
#line 519 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      linear_ctx *ctx = state->linalloc;
      yyval.expression = new(ctx) ast_expression(ast_post_inc, yystack.l_mark[-1].expression, NULL, NULL);
      yyval.expression->set_location_range(yystack.p_mark[-1], yystack.p_mark[0]);
   }
#line 3500 "compiler/glsl/glsl_parser.cpp"
break;
case 39:
#line 525 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      linear_ctx *ctx = state->linalloc;
      yyval.expression = new(ctx) ast_expression(ast_post_dec, yystack.l_mark[-1].expression, NULL, NULL);
      yyval.expression->set_location_range(yystack.p_mark[-1], yystack.p_mark[0]);
   }
#line 3509 "compiler/glsl/glsl_parser.cpp"
break;
case 47:
#line 556 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      yyval.expression = yystack.l_mark[-1].expression;
      yyval.expression->set_location(yystack.p_mark[-1]);
      yyval.expression->expressions.push_tail(& yystack.l_mark[0].expression->link);
   }
#line 3518 "compiler/glsl/glsl_parser.cpp"
break;
case 48:
#line 562 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      yyval.expression = yystack.l_mark[-2].expression;
      yyval.expression->set_location(yystack.p_mark[-2]);
      yyval.expression->expressions.push_tail(& yystack.l_mark[0].expression->link);
   }
#line 3527 "compiler/glsl/glsl_parser.cpp"
break;
case 50:
#line 578 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      linear_ctx *ctx = state->linalloc;
      yyval.expression = new(ctx) ast_function_expression(yystack.l_mark[0].type_specifier);
      yyval.expression->set_location(yystack.p_mark[0]);
      }
#line 3536 "compiler/glsl/glsl_parser.cpp"
break;
case 51:
#line 584 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      linear_ctx *ctx = state->linalloc;
      yyval.expression = new(ctx) ast_function_expression(yystack.l_mark[0].expression);
      yyval.expression->set_location(yystack.p_mark[0]);
      }
#line 3545 "compiler/glsl/glsl_parser.cpp"
break;
case 53:
#line 599 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      linear_ctx *ctx = state->linalloc;
      yyval.expression = new(ctx) ast_expression(ast_pre_inc, yystack.l_mark[0].expression, NULL, NULL);
      yyval.expression->set_location(yystack.p_mark[-1]);
   }
#line 3554 "compiler/glsl/glsl_parser.cpp"
break;
case 54:
#line 605 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      linear_ctx *ctx = state->linalloc;
      yyval.expression = new(ctx) ast_expression(ast_pre_dec, yystack.l_mark[0].expression, NULL, NULL);
      yyval.expression->set_location(yystack.p_mark[-1]);
   }
#line 3563 "compiler/glsl/glsl_parser.cpp"
break;
case 55:
#line 611 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      linear_ctx *ctx = state->linalloc;
      yyval.expression = new(ctx) ast_expression(yystack.l_mark[-1].n, yystack.l_mark[0].expression, NULL, NULL);
      yyval.expression->set_location_range(yystack.p_mark[-1], yystack.p_mark[0]);
   }
#line 3572 "compiler/glsl/glsl_parser.cpp"
break;
case 56:
#line 620 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{ yyval.n = ast_plus; }
#line 3577 "compiler/glsl/glsl_parser.cpp"
break;
case 57:
#line 621 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{ yyval.n = ast_neg; }
#line 3582 "compiler/glsl/glsl_parser.cpp"
break;
case 58:
#line 622 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{ yyval.n = ast_logic_not; }
#line 3587 "compiler/glsl/glsl_parser.cpp"
break;
case 59:
#line 623 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{ yyval.n = ast_bit_not; }
#line 3592 "compiler/glsl/glsl_parser.cpp"
break;
case 61:
#line 629 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      linear_ctx *ctx = state->linalloc;
      yyval.expression = new(ctx) ast_expression_bin(ast_mul, yystack.l_mark[-2].expression, yystack.l_mark[0].expression);
      yyval.expression->set_location_range(yystack.p_mark[-2], yystack.p_mark[0]);
   }
#line 3601 "compiler/glsl/glsl_parser.cpp"
break;
case 62:
#line 635 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      linear_ctx *ctx = state->linalloc;
      yyval.expression = new(ctx) ast_expression_bin(ast_div, yystack.l_mark[-2].expression, yystack.l_mark[0].expression);
      yyval.expression->set_location_range(yystack.p_mark[-2], yystack.p_mark[0]);
   }
#line 3610 "compiler/glsl/glsl_parser.cpp"
break;
case 63:
#line 641 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      linear_ctx *ctx = state->linalloc;
      yyval.expression = new(ctx) ast_expression_bin(ast_mod, yystack.l_mark[-2].expression, yystack.l_mark[0].expression);
      yyval.expression->set_location_range(yystack.p_mark[-2], yystack.p_mark[0]);
   }
#line 3619 "compiler/glsl/glsl_parser.cpp"
break;
case 65:
#line 651 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      linear_ctx *ctx = state->linalloc;
      yyval.expression = new(ctx) ast_expression_bin(ast_add, yystack.l_mark[-2].expression, yystack.l_mark[0].expression);
      yyval.expression->set_location_range(yystack.p_mark[-2], yystack.p_mark[0]);
   }
#line 3628 "compiler/glsl/glsl_parser.cpp"
break;
case 66:
#line 657 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      linear_ctx *ctx = state->linalloc;
      yyval.expression = new(ctx) ast_expression_bin(ast_sub, yystack.l_mark[-2].expression, yystack.l_mark[0].expression);
      yyval.expression->set_location_range(yystack.p_mark[-2], yystack.p_mark[0]);
   }
#line 3637 "compiler/glsl/glsl_parser.cpp"
break;
case 68:
#line 667 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      linear_ctx *ctx = state->linalloc;
      yyval.expression = new(ctx) ast_expression_bin(ast_lshift, yystack.l_mark[-2].expression, yystack.l_mark[0].expression);
      yyval.expression->set_location_range(yystack.p_mark[-2], yystack.p_mark[0]);
   }
#line 3646 "compiler/glsl/glsl_parser.cpp"
break;
case 69:
#line 673 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      linear_ctx *ctx = state->linalloc;
      yyval.expression = new(ctx) ast_expression_bin(ast_rshift, yystack.l_mark[-2].expression, yystack.l_mark[0].expression);
      yyval.expression->set_location_range(yystack.p_mark[-2], yystack.p_mark[0]);
   }
#line 3655 "compiler/glsl/glsl_parser.cpp"
break;
case 71:
#line 683 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      linear_ctx *ctx = state->linalloc;
      yyval.expression = new(ctx) ast_expression_bin(ast_less, yystack.l_mark[-2].expression, yystack.l_mark[0].expression);
      yyval.expression->set_location_range(yystack.p_mark[-2], yystack.p_mark[0]);
   }
#line 3664 "compiler/glsl/glsl_parser.cpp"
break;
case 72:
#line 689 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      linear_ctx *ctx = state->linalloc;
      yyval.expression = new(ctx) ast_expression_bin(ast_greater, yystack.l_mark[-2].expression, yystack.l_mark[0].expression);
      yyval.expression->set_location_range(yystack.p_mark[-2], yystack.p_mark[0]);
   }
#line 3673 "compiler/glsl/glsl_parser.cpp"
break;
case 73:
#line 695 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      linear_ctx *ctx = state->linalloc;
      yyval.expression = new(ctx) ast_expression_bin(ast_lequal, yystack.l_mark[-2].expression, yystack.l_mark[0].expression);
      yyval.expression->set_location_range(yystack.p_mark[-2], yystack.p_mark[0]);
   }
#line 3682 "compiler/glsl/glsl_parser.cpp"
break;
case 74:
#line 701 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      linear_ctx *ctx = state->linalloc;
      yyval.expression = new(ctx) ast_expression_bin(ast_gequal, yystack.l_mark[-2].expression, yystack.l_mark[0].expression);
      yyval.expression->set_location_range(yystack.p_mark[-2], yystack.p_mark[0]);
   }
#line 3691 "compiler/glsl/glsl_parser.cpp"
break;
case 76:
#line 711 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      linear_ctx *ctx = state->linalloc;
      yyval.expression = new(ctx) ast_expression_bin(ast_equal, yystack.l_mark[-2].expression, yystack.l_mark[0].expression);
      yyval.expression->set_location_range(yystack.p_mark[-2], yystack.p_mark[0]);
   }
#line 3700 "compiler/glsl/glsl_parser.cpp"
break;
case 77:
#line 717 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      linear_ctx *ctx = state->linalloc;
      yyval.expression = new(ctx) ast_expression_bin(ast_nequal, yystack.l_mark[-2].expression, yystack.l_mark[0].expression);
      yyval.expression->set_location_range(yystack.p_mark[-2], yystack.p_mark[0]);
   }
#line 3709 "compiler/glsl/glsl_parser.cpp"
break;
case 79:
#line 727 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      linear_ctx *ctx = state->linalloc;
      yyval.expression = new(ctx) ast_expression_bin(ast_bit_and, yystack.l_mark[-2].expression, yystack.l_mark[0].expression);
      yyval.expression->set_location_range(yystack.p_mark[-2], yystack.p_mark[0]);
   }
#line 3718 "compiler/glsl/glsl_parser.cpp"
break;
case 81:
#line 737 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      linear_ctx *ctx = state->linalloc;
      yyval.expression = new(ctx) ast_expression_bin(ast_bit_xor, yystack.l_mark[-2].expression, yystack.l_mark[0].expression);
      yyval.expression->set_location_range(yystack.p_mark[-2], yystack.p_mark[0]);
   }
#line 3727 "compiler/glsl/glsl_parser.cpp"
break;
case 83:
#line 747 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      linear_ctx *ctx = state->linalloc;
      yyval.expression = new(ctx) ast_expression_bin(ast_bit_or, yystack.l_mark[-2].expression, yystack.l_mark[0].expression);
      yyval.expression->set_location_range(yystack.p_mark[-2], yystack.p_mark[0]);
   }
#line 3736 "compiler/glsl/glsl_parser.cpp"
break;
case 85:
#line 757 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      linear_ctx *ctx = state->linalloc;
      yyval.expression = new(ctx) ast_expression_bin(ast_logic_and, yystack.l_mark[-2].expression, yystack.l_mark[0].expression);
      yyval.expression->set_location_range(yystack.p_mark[-2], yystack.p_mark[0]);
   }
#line 3745 "compiler/glsl/glsl_parser.cpp"
break;
case 87:
#line 767 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      linear_ctx *ctx = state->linalloc;
      yyval.expression = new(ctx) ast_expression_bin(ast_logic_xor, yystack.l_mark[-2].expression, yystack.l_mark[0].expression);
      yyval.expression->set_location_range(yystack.p_mark[-2], yystack.p_mark[0]);
   }
#line 3754 "compiler/glsl/glsl_parser.cpp"
break;
case 89:
#line 777 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      linear_ctx *ctx = state->linalloc;
      yyval.expression = new(ctx) ast_expression_bin(ast_logic_or, yystack.l_mark[-2].expression, yystack.l_mark[0].expression);
      yyval.expression->set_location_range(yystack.p_mark[-2], yystack.p_mark[0]);
   }
#line 3763 "compiler/glsl/glsl_parser.cpp"
break;
case 91:
#line 787 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      linear_ctx *ctx = state->linalloc;
      yyval.expression = new(ctx) ast_expression(ast_conditional, yystack.l_mark[-4].expression, yystack.l_mark[-2].expression, yystack.l_mark[0].expression);
      yyval.expression->set_location_range(yystack.p_mark[-4], yystack.p_mark[0]);
   }
#line 3772 "compiler/glsl/glsl_parser.cpp"
break;
case 93:
#line 797 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      linear_ctx *ctx = state->linalloc;
      yyval.expression = new(ctx) ast_expression(yystack.l_mark[-1].n, yystack.l_mark[-2].expression, yystack.l_mark[0].expression, NULL);
      yyval.expression->set_location_range(yystack.p_mark[-2], yystack.p_mark[0]);
   }
#line 3781 "compiler/glsl/glsl_parser.cpp"
break;
case 94:
#line 805 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{ yyval.n = ast_assign; }
#line 3786 "compiler/glsl/glsl_parser.cpp"
break;
case 95:
#line 806 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{ yyval.n = ast_mul_assign; }
#line 3791 "compiler/glsl/glsl_parser.cpp"
break;
case 96:
#line 807 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{ yyval.n = ast_div_assign; }
#line 3796 "compiler/glsl/glsl_parser.cpp"
break;
case 97:
#line 808 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{ yyval.n = ast_mod_assign; }
#line 3801 "compiler/glsl/glsl_parser.cpp"
break;
case 98:
#line 809 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{ yyval.n = ast_add_assign; }
#line 3806 "compiler/glsl/glsl_parser.cpp"
break;
case 99:
#line 810 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{ yyval.n = ast_sub_assign; }
#line 3811 "compiler/glsl/glsl_parser.cpp"
break;
case 100:
#line 811 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{ yyval.n = ast_ls_assign; }
#line 3816 "compiler/glsl/glsl_parser.cpp"
break;
case 101:
#line 812 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{ yyval.n = ast_rs_assign; }
#line 3821 "compiler/glsl/glsl_parser.cpp"
break;
case 102:
#line 813 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{ yyval.n = ast_and_assign; }
#line 3826 "compiler/glsl/glsl_parser.cpp"
break;
case 103:
#line 814 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{ yyval.n = ast_xor_assign; }
#line 3831 "compiler/glsl/glsl_parser.cpp"
break;
case 104:
#line 815 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{ yyval.n = ast_or_assign; }
#line 3836 "compiler/glsl/glsl_parser.cpp"
break;
case 105:
#line 820 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      yyval.expression = yystack.l_mark[0].expression;
   }
#line 3843 "compiler/glsl/glsl_parser.cpp"
break;
case 106:
#line 824 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      linear_ctx *ctx = state->linalloc;
      if (yystack.l_mark[-2].expression->oper != ast_sequence) {
         yyval.expression = new(ctx) ast_expression(ast_sequence, NULL, NULL, NULL);
         yyval.expression->set_location_range(yystack.p_mark[-2], yystack.p_mark[0]);
         yyval.expression->expressions.push_tail(& yystack.l_mark[-2].expression->link);
      } else {
         yyval.expression = yystack.l_mark[-2].expression;
      }

      yyval.expression->expressions.push_tail(& yystack.l_mark[0].expression->link);
   }
#line 3859 "compiler/glsl/glsl_parser.cpp"
break;
case 108:
#line 844 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      state->symbols->pop_scope();
      yyval.node = yystack.l_mark[-1].function;
   }
#line 3867 "compiler/glsl/glsl_parser.cpp"
break;
case 109:
#line 849 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      yyval.node = yystack.l_mark[-1].declarator_list;
   }
#line 3874 "compiler/glsl/glsl_parser.cpp"
break;
case 110:
#line 853 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      yystack.l_mark[-1].type_specifier->default_precision = yystack.l_mark[-2].n;
      yyval.node = yystack.l_mark[-1].type_specifier;
   }
#line 3882 "compiler/glsl/glsl_parser.cpp"
break;
case 111:
#line 858 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      ast_interface_block *block = (ast_interface_block *) yystack.l_mark[0].node;
      if (block->layout.has_layout() || block->layout.has_memory()) {
         if (!block->default_layout.merge_qualifier(& yystack.p_mark[0], state, block->layout, false)) {
            YYERROR;
         }
      }
      block->layout = block->default_layout;
      if (!block->layout.push_to_global(& yystack.p_mark[0], state)) {
         YYERROR;
      }
      yyval.node = yystack.l_mark[0].node;
   }
#line 3899 "compiler/glsl/glsl_parser.cpp"
break;
case 115:
#line 884 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      yyval.function = yystack.l_mark[-1].function;
      yyval.function->parameters.push_tail(& yystack.l_mark[0].parameter_declarator->link);
   }
#line 3907 "compiler/glsl/glsl_parser.cpp"
break;
case 116:
#line 889 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      yyval.function = yystack.l_mark[-2].function;
      yyval.function->parameters.push_tail(& yystack.l_mark[0].parameter_declarator->link);
   }
#line 3915 "compiler/glsl/glsl_parser.cpp"
break;
case 117:
#line 897 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      linear_ctx *ctx = state->linalloc;
      yyval.function = new(ctx) ast_function();
      yyval.function->set_location(yystack.p_mark[-1]);
      yyval.function->return_type = yystack.l_mark[-2].fully_specified_type;
      yyval.function->identifier = yystack.l_mark[-1].identifier;

      if (yystack.l_mark[-2].fully_specified_type->qualifier.is_subroutine_decl()) {
         /* add type for IDENTIFIER search */
         state->symbols->add_type(yystack.l_mark[-1].identifier, glsl_subroutine_type(yystack.l_mark[-1].identifier));
      } else
         state->symbols->add_function(new(state) ir_function(yystack.l_mark[-1].identifier));
      state->symbols->push_scope();
   }
#line 3933 "compiler/glsl/glsl_parser.cpp"
break;
case 118:
#line 915 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      linear_ctx *ctx = state->linalloc;
      yyval.parameter_declarator = new(ctx) ast_parameter_declarator();
      yyval.parameter_declarator->set_location_range(yystack.p_mark[-1], yystack.p_mark[0]);
      yyval.parameter_declarator->type = new(ctx) ast_fully_specified_type();
      yyval.parameter_declarator->type->set_location(yystack.p_mark[-1]);
      yyval.parameter_declarator->type->specifier = yystack.l_mark[-1].type_specifier;
      yyval.parameter_declarator->identifier = yystack.l_mark[0].identifier;
      state->symbols->add_variable(new(state) ir_variable(NULL, yystack.l_mark[0].identifier, ir_var_auto));
   }
#line 3947 "compiler/glsl/glsl_parser.cpp"
break;
case 119:
#line 926 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      _mesa_glsl_error(&yystack.p_mark[-2], state, "is is not allowed on function parameter");
      YYERROR;
   }
#line 3955 "compiler/glsl/glsl_parser.cpp"
break;
case 120:
#line 931 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      linear_ctx *ctx = state->linalloc;
      yyval.parameter_declarator = new(ctx) ast_parameter_declarator();
      yyval.parameter_declarator->set_location_range(yystack.p_mark[-2], yystack.p_mark[0]);
      yyval.parameter_declarator->type = new(ctx) ast_fully_specified_type();
      yyval.parameter_declarator->type->set_location(yystack.p_mark[-2]);
      yyval.parameter_declarator->type->specifier = yystack.l_mark[-2].type_specifier;
      yyval.parameter_declarator->identifier = yystack.l_mark[-1].identifier;
      yyval.parameter_declarator->array_specifier = yystack.l_mark[0].array_specifier;
      state->symbols->add_variable(new(state) ir_variable(NULL, yystack.l_mark[-1].identifier, ir_var_auto));
   }
#line 3970 "compiler/glsl/glsl_parser.cpp"
break;
case 121:
#line 946 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      yyval.parameter_declarator = yystack.l_mark[0].parameter_declarator;
      yyval.parameter_declarator->type->qualifier = yystack.l_mark[-1].type_qualifier;
      if (!yyval.parameter_declarator->type->qualifier.push_to_global(& yystack.p_mark[-1], state)) {
         YYERROR;
      }
   }
#line 3981 "compiler/glsl/glsl_parser.cpp"
break;
case 122:
#line 954 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      linear_ctx *ctx = state->linalloc;
      yyval.parameter_declarator = new(ctx) ast_parameter_declarator();
      yyval.parameter_declarator->set_location(yystack.p_mark[0]);
      yyval.parameter_declarator->type = new(ctx) ast_fully_specified_type();
      yyval.parameter_declarator->type->set_location_range(yystack.p_mark[-1], yystack.p_mark[0]);
      yyval.parameter_declarator->type->qualifier = yystack.l_mark[-1].type_qualifier;
      if (!yyval.parameter_declarator->type->qualifier.push_to_global(& yystack.p_mark[-1], state)) {
         YYERROR;
      }
      yyval.parameter_declarator->type->specifier = yystack.l_mark[0].type_specifier;
   }
#line 3997 "compiler/glsl/glsl_parser.cpp"
break;
case 123:
#line 970 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      memset(& yyval.type_qualifier, 0, sizeof(yyval.type_qualifier));
   }
#line 4004 "compiler/glsl/glsl_parser.cpp"
break;
case 124:
#line 974 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      if (yystack.l_mark[0].type_qualifier.flags.q.constant)
         _mesa_glsl_error(&yystack.p_mark[-1], state, "duplicate const qualifier");

      yyval.type_qualifier = yystack.l_mark[0].type_qualifier;
      yyval.type_qualifier.flags.q.constant = 1;
   }
#line 4015 "compiler/glsl/glsl_parser.cpp"
break;
case 125:
#line 982 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      if (yystack.l_mark[0].type_qualifier.flags.q.precise)
         _mesa_glsl_error(&yystack.p_mark[-1], state, "duplicate precise qualifier");

      yyval.type_qualifier = yystack.l_mark[0].type_qualifier;
      yyval.type_qualifier.flags.q.precise = 1;
   }
#line 4026 "compiler/glsl/glsl_parser.cpp"
break;
case 126:
#line 990 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      if ((yystack.l_mark[-1].type_qualifier.flags.q.in || yystack.l_mark[-1].type_qualifier.flags.q.out) && (yystack.l_mark[0].type_qualifier.flags.q.in || yystack.l_mark[0].type_qualifier.flags.q.out))
         _mesa_glsl_error(&yystack.p_mark[-1], state, "duplicate in/out/inout qualifier");

      if (!state->has_420pack_or_es31() && yystack.l_mark[0].type_qualifier.flags.q.constant)
         _mesa_glsl_error(&yystack.p_mark[-1], state, "in/out/inout must come after const "
                                      "or precise");

      yyval.type_qualifier = yystack.l_mark[-1].type_qualifier;
      yyval.type_qualifier.merge_qualifier(&yystack.p_mark[-1], state, yystack.l_mark[0].type_qualifier, false);
   }
#line 4041 "compiler/glsl/glsl_parser.cpp"
break;
case 127:
#line 1002 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      if (yystack.l_mark[0].type_qualifier.precision != ast_precision_none)
         _mesa_glsl_error(&yystack.p_mark[-1], state, "duplicate precision qualifier");

      if (!state->has_420pack_or_es31() &&
          yystack.l_mark[0].type_qualifier.flags.i != 0)
         _mesa_glsl_error(&yystack.p_mark[-1], state, "precision qualifiers must come last");

      yyval.type_qualifier = yystack.l_mark[0].type_qualifier;
      yyval.type_qualifier.precision = yystack.l_mark[-1].n;
   }
#line 4056 "compiler/glsl/glsl_parser.cpp"
break;
case 128:
#line 1014 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      yyval.type_qualifier = yystack.l_mark[-1].type_qualifier;
      yyval.type_qualifier.merge_qualifier(&yystack.p_mark[-1], state, yystack.l_mark[0].type_qualifier, false);
   }
#line 4064 "compiler/glsl/glsl_parser.cpp"
break;
case 129:
#line 1021 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      memset(& yyval.type_qualifier, 0, sizeof(yyval.type_qualifier));
      yyval.type_qualifier.flags.q.in = 1;
   }
#line 4072 "compiler/glsl/glsl_parser.cpp"
break;
case 130:
#line 1026 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      memset(& yyval.type_qualifier, 0, sizeof(yyval.type_qualifier));
      yyval.type_qualifier.flags.q.out = 1;
   }
#line 4080 "compiler/glsl/glsl_parser.cpp"
break;
case 131:
#line 1031 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      memset(& yyval.type_qualifier, 0, sizeof(yyval.type_qualifier));
      yyval.type_qualifier.flags.q.in = 1;
      yyval.type_qualifier.flags.q.out = 1;
   }
#line 4089 "compiler/glsl/glsl_parser.cpp"
break;
case 134:
#line 1045 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      linear_ctx *ctx = state->linalloc;
      ast_declaration *decl = new(ctx) ast_declaration(yystack.l_mark[0].identifier, NULL, NULL);
      decl->set_location(yystack.p_mark[0]);

      yyval.declarator_list = yystack.l_mark[-2].declarator_list;
      yyval.declarator_list->declarations.push_tail(&decl->link);
      state->symbols->add_variable(new(state) ir_variable(NULL, yystack.l_mark[0].identifier, ir_var_auto));
   }
#line 4102 "compiler/glsl/glsl_parser.cpp"
break;
case 135:
#line 1055 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      linear_ctx *ctx = state->linalloc;
      ast_declaration *decl = new(ctx) ast_declaration(yystack.l_mark[-1].identifier, yystack.l_mark[0].array_specifier, NULL);
      decl->set_location_range(yystack.p_mark[-1], yystack.p_mark[0]);

      yyval.declarator_list = yystack.l_mark[-3].declarator_list;
      yyval.declarator_list->declarations.push_tail(&decl->link);
      state->symbols->add_variable(new(state) ir_variable(NULL, yystack.l_mark[-1].identifier, ir_var_auto));
   }
#line 4115 "compiler/glsl/glsl_parser.cpp"
break;
case 136:
#line 1065 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      linear_ctx *ctx = state->linalloc;
      ast_declaration *decl = new(ctx) ast_declaration(yystack.l_mark[-3].identifier, yystack.l_mark[-2].array_specifier, yystack.l_mark[0].expression);
      decl->set_location_range(yystack.p_mark[-3], yystack.p_mark[-2]);

      yyval.declarator_list = yystack.l_mark[-5].declarator_list;
      yyval.declarator_list->declarations.push_tail(&decl->link);
      state->symbols->add_variable(new(state) ir_variable(NULL, yystack.l_mark[-3].identifier, ir_var_auto));
   }
#line 4128 "compiler/glsl/glsl_parser.cpp"
break;
case 137:
#line 1075 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      linear_ctx *ctx = state->linalloc;
      ast_declaration *decl = new(ctx) ast_declaration(yystack.l_mark[-2].identifier, NULL, yystack.l_mark[0].expression);
      decl->set_location(yystack.p_mark[-2]);

      yyval.declarator_list = yystack.l_mark[-4].declarator_list;
      yyval.declarator_list->declarations.push_tail(&decl->link);
      state->symbols->add_variable(new(state) ir_variable(NULL, yystack.l_mark[-2].identifier, ir_var_auto));
   }
#line 4141 "compiler/glsl/glsl_parser.cpp"
break;
case 138:
#line 1089 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      linear_ctx *ctx = state->linalloc;
      /* Empty declaration list is valid. */
      yyval.declarator_list = new(ctx) ast_declarator_list(yystack.l_mark[0].fully_specified_type);
      yyval.declarator_list->set_location(yystack.p_mark[0]);
   }
#line 4151 "compiler/glsl/glsl_parser.cpp"
break;
case 139:
#line 1096 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      linear_ctx *ctx = state->linalloc;
      ast_declaration *decl = new(ctx) ast_declaration(yystack.l_mark[0].identifier, NULL, NULL);
      decl->set_location(yystack.p_mark[0]);

      yyval.declarator_list = new(ctx) ast_declarator_list(yystack.l_mark[-1].fully_specified_type);
      yyval.declarator_list->set_location_range(yystack.p_mark[-1], yystack.p_mark[0]);
      yyval.declarator_list->declarations.push_tail(&decl->link);
      state->symbols->add_variable(new(state) ir_variable(NULL, yystack.l_mark[0].identifier, ir_var_auto));
   }
#line 4165 "compiler/glsl/glsl_parser.cpp"
break;
case 140:
#line 1107 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      linear_ctx *ctx = state->linalloc;
      ast_declaration *decl = new(ctx) ast_declaration(yystack.l_mark[-1].identifier, yystack.l_mark[0].array_specifier, NULL);
      decl->set_location_range(yystack.p_mark[-1], yystack.p_mark[0]);

      yyval.declarator_list = new(ctx) ast_declarator_list(yystack.l_mark[-2].fully_specified_type);
      yyval.declarator_list->set_location_range(yystack.p_mark[-2], yystack.p_mark[0]);
      yyval.declarator_list->declarations.push_tail(&decl->link);
      state->symbols->add_variable(new(state) ir_variable(NULL, yystack.l_mark[-1].identifier, ir_var_auto));
   }
#line 4179 "compiler/glsl/glsl_parser.cpp"
break;
case 141:
#line 1118 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      linear_ctx *ctx = state->linalloc;
      ast_declaration *decl = new(ctx) ast_declaration(yystack.l_mark[-3].identifier, yystack.l_mark[-2].array_specifier, yystack.l_mark[0].expression);
      decl->set_location_range(yystack.p_mark[-3], yystack.p_mark[-2]);

      yyval.declarator_list = new(ctx) ast_declarator_list(yystack.l_mark[-4].fully_specified_type);
      yyval.declarator_list->set_location_range(yystack.p_mark[-4], yystack.p_mark[-2]);
      yyval.declarator_list->declarations.push_tail(&decl->link);
      state->symbols->add_variable(new(state) ir_variable(NULL, yystack.l_mark[-3].identifier, ir_var_auto));
   }
#line 4193 "compiler/glsl/glsl_parser.cpp"
break;
case 142:
#line 1129 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      linear_ctx *ctx = state->linalloc;
      ast_declaration *decl = new(ctx) ast_declaration(yystack.l_mark[-2].identifier, NULL, yystack.l_mark[0].expression);
      decl->set_location(yystack.p_mark[-2]);

      yyval.declarator_list = new(ctx) ast_declarator_list(yystack.l_mark[-3].fully_specified_type);
      yyval.declarator_list->set_location_range(yystack.p_mark[-3], yystack.p_mark[-2]);
      yyval.declarator_list->declarations.push_tail(&decl->link);
      state->symbols->add_variable(new(state) ir_variable(NULL, yystack.l_mark[-2].identifier, ir_var_auto));
   }
#line 4207 "compiler/glsl/glsl_parser.cpp"
break;
case 143:
#line 1140 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      linear_ctx *ctx = state->linalloc;
      ast_declaration *decl = new(ctx) ast_declaration(yystack.l_mark[0].identifier, NULL, NULL);
      decl->set_location(yystack.p_mark[0]);

      yyval.declarator_list = new(ctx) ast_declarator_list(NULL);
      yyval.declarator_list->set_location_range(yystack.p_mark[-1], yystack.p_mark[0]);
      yyval.declarator_list->invariant = true;

      yyval.declarator_list->declarations.push_tail(&decl->link);
   }
#line 4222 "compiler/glsl/glsl_parser.cpp"
break;
case 144:
#line 1152 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      linear_ctx *ctx = state->linalloc;
      ast_declaration *decl = new(ctx) ast_declaration(yystack.l_mark[0].identifier, NULL, NULL);
      decl->set_location(yystack.p_mark[0]);

      yyval.declarator_list = new(ctx) ast_declarator_list(NULL);
      yyval.declarator_list->set_location_range(yystack.p_mark[-1], yystack.p_mark[0]);
      yyval.declarator_list->precise = true;

      yyval.declarator_list->declarations.push_tail(&decl->link);
   }
#line 4237 "compiler/glsl/glsl_parser.cpp"
break;
case 145:
#line 1167 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      linear_ctx *ctx = state->linalloc;
      yyval.fully_specified_type = new(ctx) ast_fully_specified_type();
      yyval.fully_specified_type->set_location(yystack.p_mark[0]);
      yyval.fully_specified_type->specifier = yystack.l_mark[0].type_specifier;
   }
#line 4247 "compiler/glsl/glsl_parser.cpp"
break;
case 146:
#line 1174 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      linear_ctx *ctx = state->linalloc;
      yyval.fully_specified_type = new(ctx) ast_fully_specified_type();
      yyval.fully_specified_type->set_location_range(yystack.p_mark[-1], yystack.p_mark[0]);
      yyval.fully_specified_type->qualifier = yystack.l_mark[-1].type_qualifier;
      if (!yyval.fully_specified_type->qualifier.push_to_global(& yystack.p_mark[-1], state)) {
         YYERROR;
      }
      yyval.fully_specified_type->specifier = yystack.l_mark[0].type_specifier;
      if (yyval.fully_specified_type->specifier->structure != NULL &&
          yyval.fully_specified_type->specifier->structure->is_declaration) {
            yyval.fully_specified_type->specifier->structure->layout = &yyval.fully_specified_type->qualifier;
      }
   }
#line 4265 "compiler/glsl/glsl_parser.cpp"
break;
case 147:
#line 1192 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      yyval.type_qualifier = yystack.l_mark[-1].type_qualifier;
   }
#line 4272 "compiler/glsl/glsl_parser.cpp"
break;
case 149:
#line 1200 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      yyval.type_qualifier = yystack.l_mark[-2].type_qualifier;
      if (!yyval.type_qualifier.merge_qualifier(& yystack.p_mark[0], state, yystack.l_mark[0].type_qualifier, true)) {
         YYERROR;
      }
   }
#line 4282 "compiler/glsl/glsl_parser.cpp"
break;
case 150:
#line 1210 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      memset(& yyval.type_qualifier, 0, sizeof(yyval.type_qualifier));

      /* Layout qualifiers for ARB_fragment_coord_conventions. */
      if (!yyval.type_qualifier.flags.i && (state->ARB_fragment_coord_conventions_enable ||
                          state->is_version(150, 0))) {
         if (match_layout_qualifier(yystack.l_mark[0].identifier, "origin_upper_left", state) == 0) {
            yyval.type_qualifier.flags.q.origin_upper_left = 1;
         } else if (match_layout_qualifier(yystack.l_mark[0].identifier, "pixel_center_integer",
                                           state) == 0) {
            yyval.type_qualifier.flags.q.pixel_center_integer = 1;
         }

         if (yyval.type_qualifier.flags.i && state->ARB_fragment_coord_conventions_warn) {
            _mesa_glsl_warning(& yystack.p_mark[0], state,
                               "GL_ARB_fragment_coord_conventions layout "
                               "identifier `%s' used", yystack.l_mark[0].identifier);
         }
      }

      /* Layout qualifiers for AMD/ARB_conservative_depth. */
      if (!yyval.type_qualifier.flags.i &&
          (state->AMD_conservative_depth_enable ||
           state->ARB_conservative_depth_enable ||
           state->EXT_conservative_depth_enable ||
           state->is_version(420, 0))) {
         if (match_layout_qualifier(yystack.l_mark[0].identifier, "depth_any", state) == 0) {
            yyval.type_qualifier.flags.q.depth_type = 1;
            yyval.type_qualifier.depth_type = ast_depth_any;
         } else if (match_layout_qualifier(yystack.l_mark[0].identifier, "depth_greater", state) == 0) {
            yyval.type_qualifier.flags.q.depth_type = 1;
            yyval.type_qualifier.depth_type = ast_depth_greater;
         } else if (match_layout_qualifier(yystack.l_mark[0].identifier, "depth_less", state) == 0) {
            yyval.type_qualifier.flags.q.depth_type = 1;
            yyval.type_qualifier.depth_type = ast_depth_less;
         } else if (match_layout_qualifier(yystack.l_mark[0].identifier, "depth_unchanged",
                                           state) == 0) {
            yyval.type_qualifier.flags.q.depth_type = 1;
            yyval.type_qualifier.depth_type = ast_depth_unchanged;
         }

         if (yyval.type_qualifier.flags.i && state->AMD_conservative_depth_warn) {
            _mesa_glsl_warning(& yystack.p_mark[0], state,
                               "GL_AMD_conservative_depth "
                               "layout qualifier `%s' is used", yystack.l_mark[0].identifier);
         }
         if (yyval.type_qualifier.flags.i && state->ARB_conservative_depth_warn) {
            _mesa_glsl_warning(& yystack.p_mark[0], state,
                               "GL_ARB_conservative_depth "
                               "layout qualifier `%s' is used", yystack.l_mark[0].identifier);
         }
         if (yyval.type_qualifier.flags.i && state->EXT_conservative_depth_warn) {
            _mesa_glsl_warning(& yystack.p_mark[0], state,
                               "GL_EXT_conservative_depth "
                               "layout qualifier `%s' is used", yystack.l_mark[0].identifier);
         }
      }

      /* See also interface_block_layout_qualifier. */
      if (!yyval.type_qualifier.flags.i && state->has_uniform_buffer_objects()) {
         if (match_layout_qualifier(yystack.l_mark[0].identifier, "std140", state) == 0) {
            yyval.type_qualifier.flags.q.std140 = 1;
         } else if (match_layout_qualifier(yystack.l_mark[0].identifier, "shared", state) == 0) {
            yyval.type_qualifier.flags.q.shared = 1;
         } else if (match_layout_qualifier(yystack.l_mark[0].identifier, "std430", state) == 0) {
            yyval.type_qualifier.flags.q.std430 = 1;
         } else if (match_layout_qualifier(yystack.l_mark[0].identifier, "column_major", state) == 0) {
            yyval.type_qualifier.flags.q.column_major = 1;
         /* "row_major" is a reserved word in GLSL 1.30+. Its token is parsed
          * below in the interface_block_layout_qualifier rule.
          *
          * It is not a reserved word in GLSL ES 3.00, so it's handled here as
          * an identifier.
          *
          * Also, this takes care of alternate capitalizations of
          * "row_major" (which is necessary because layout qualifiers
          * are case-insensitive in desktop GLSL).
          */
         } else if (match_layout_qualifier(yystack.l_mark[0].identifier, "row_major", state) == 0) {
            yyval.type_qualifier.flags.q.row_major = 1;
         /* "packed" is a reserved word in GLSL, and its token is
          * parsed below in the interface_block_layout_qualifier rule.
          * However, we must take care of alternate capitalizations of
          * "packed", because layout qualifiers are case-insensitive
          * in desktop GLSL.
          */
         } else if (match_layout_qualifier(yystack.l_mark[0].identifier, "packed", state) == 0) {
           yyval.type_qualifier.flags.q.packed = 1;
         }

         if (yyval.type_qualifier.flags.i && state->ARB_uniform_buffer_object_warn) {
            _mesa_glsl_warning(& yystack.p_mark[0], state,
                               "#version 140 / GL_ARB_uniform_buffer_object "
                               "layout qualifier `%s' is used", yystack.l_mark[0].identifier);
         }
      }

      /* Layout qualifiers for GLSL 1.50 geometry shaders. */
      if (!yyval.type_qualifier.flags.i) {
         static const struct {
            const char *s;
            GLenum e;
         } map[] = {
                 { "points", GL_POINTS },
                 { "lines", GL_LINES },
                 { "lines_adjacency", GL_LINES_ADJACENCY },
                 { "line_strip", GL_LINE_STRIP },
                 { "triangles", GL_TRIANGLES },
                 { "triangles_adjacency", GL_TRIANGLES_ADJACENCY },
                 { "triangle_strip", GL_TRIANGLE_STRIP },
         };
         for (unsigned i = 0; i < ARRAY_SIZE(map); i++) {
            if (match_layout_qualifier(yystack.l_mark[0].identifier, map[i].s, state) == 0) {
               yyval.type_qualifier.flags.q.prim_type = 1;
               yyval.type_qualifier.prim_type = map[i].e;
               break;
            }
         }

         if (yyval.type_qualifier.flags.i && !state->has_geometry_shader() &&
             !state->has_tessellation_shader()) {
            _mesa_glsl_error(& yystack.p_mark[0], state, "#version 150 layout "
                             "qualifier `%s' used", yystack.l_mark[0].identifier);
         }
      }

      /* Layout qualifiers for ARB_shader_image_load_store. */
      if (state->has_shader_image_load_store()) {
         if (!yyval.type_qualifier.flags.i) {
            static const struct {
               const char *name;
               enum pipe_format format;
               glsl_base_type base_type;
               /** Minimum desktop GLSL version required for the image
                * format.  Use 130 if already present in the original
                * ARB extension.
                */
               unsigned required_glsl;
               /** Minimum GLSL ES version required for the image format. */
               unsigned required_essl;
               /* NV_image_formats */
               bool nv_image_formats;
               bool ext_qualifiers;
            } map[] = {
               { "rgba32f", PIPE_FORMAT_R32G32B32A32_FLOAT, GLSL_TYPE_FLOAT, 130, 310, false, false },
               { "rgba16f", PIPE_FORMAT_R16G16B16A16_FLOAT, GLSL_TYPE_FLOAT, 130, 310, false, false },
               { "rg32f", PIPE_FORMAT_R32G32_FLOAT, GLSL_TYPE_FLOAT, 130, 0, true, false },
               { "rg16f", PIPE_FORMAT_R16G16_FLOAT, GLSL_TYPE_FLOAT, 130, 0, true, false },
               { "r11f_g11f_b10f", PIPE_FORMAT_R11G11B10_FLOAT, GLSL_TYPE_FLOAT, 130, 0, true, false },
               { "r32f", PIPE_FORMAT_R32_FLOAT, GLSL_TYPE_FLOAT, 130, 310, false, false },
               { "r16f", PIPE_FORMAT_R16_FLOAT, GLSL_TYPE_FLOAT, 130, 0, true, false },
               { "rgba32ui", PIPE_FORMAT_R32G32B32A32_UINT, GLSL_TYPE_UINT, 130, 310, false, false },
               { "rgba16ui", PIPE_FORMAT_R16G16B16A16_UINT, GLSL_TYPE_UINT, 130, 310, false, false },
               { "rgb10_a2ui", PIPE_FORMAT_R10G10B10A2_UINT, GLSL_TYPE_UINT, 130, 0, true, false },
               { "rgba8ui", PIPE_FORMAT_R8G8B8A8_UINT, GLSL_TYPE_UINT, 130, 310, false, false },
               { "rg32ui", PIPE_FORMAT_R32G32_UINT, GLSL_TYPE_UINT, 130, 0, true, false },
               { "rg16ui", PIPE_FORMAT_R16G16_UINT, GLSL_TYPE_UINT, 130, 0, true, false },
               { "rg8ui", PIPE_FORMAT_R8G8_UINT, GLSL_TYPE_UINT, 130, 0, true, false },
               { "r32ui", PIPE_FORMAT_R32_UINT, GLSL_TYPE_UINT, 130, 310, false, false },
               { "r16ui", PIPE_FORMAT_R16_UINT, GLSL_TYPE_UINT, 130, 0, true, false },
               { "r8ui", PIPE_FORMAT_R8_UINT, GLSL_TYPE_UINT, 130, 0, true, false },
               { "rgba32i", PIPE_FORMAT_R32G32B32A32_SINT, GLSL_TYPE_INT, 130, 310, false, false },
               { "rgba16i", PIPE_FORMAT_R16G16B16A16_SINT, GLSL_TYPE_INT, 130, 310, false, false },
               { "rgba8i", PIPE_FORMAT_R8G8B8A8_SINT, GLSL_TYPE_INT, 130, 310, false, false },
               { "rg32i", PIPE_FORMAT_R32G32_SINT, GLSL_TYPE_INT, 130, 0, true, false },
               { "rg16i", PIPE_FORMAT_R16G16_SINT, GLSL_TYPE_INT, 130, 0, true, false },
               { "rg8i", PIPE_FORMAT_R8G8_SINT, GLSL_TYPE_INT, 130, 0, true, false },
               { "r32i", PIPE_FORMAT_R32_SINT, GLSL_TYPE_INT, 130, 310, false, false },
               { "r16i", PIPE_FORMAT_R16_SINT, GLSL_TYPE_INT, 130, 0, true, false },
               { "r8i", PIPE_FORMAT_R8_SINT, GLSL_TYPE_INT, 130, 0, true, false },
               { "rgba16", PIPE_FORMAT_R16G16B16A16_UNORM, GLSL_TYPE_FLOAT, 130, 0, true, false },
               { "rgb10_a2", PIPE_FORMAT_R10G10B10A2_UNORM, GLSL_TYPE_FLOAT, 130, 0, true, false },
               { "rgba8", PIPE_FORMAT_R8G8B8A8_UNORM, GLSL_TYPE_FLOAT, 130, 310, false, false },
               { "rg16", PIPE_FORMAT_R16G16_UNORM, GLSL_TYPE_FLOAT, 130, 0, true, false },
               { "rg8", PIPE_FORMAT_R8G8_UNORM, GLSL_TYPE_FLOAT, 130, 0, true, false },
               { "r16", PIPE_FORMAT_R16_UNORM, GLSL_TYPE_FLOAT, 130, 0, true, false },
               { "r8", PIPE_FORMAT_R8_UNORM, GLSL_TYPE_FLOAT, 130, 0, true, false },
               { "rgba16_snorm", PIPE_FORMAT_R16G16B16A16_SNORM, GLSL_TYPE_FLOAT, 130, 0, true, false },
               { "rgba8_snorm", PIPE_FORMAT_R8G8B8A8_SNORM, GLSL_TYPE_FLOAT, 130, 310, false, false },
               { "rg16_snorm", PIPE_FORMAT_R16G16_SNORM, GLSL_TYPE_FLOAT, 130, 0, true, false },
               { "rg8_snorm", PIPE_FORMAT_R8G8_SNORM, GLSL_TYPE_FLOAT, 130, 0, true, false },
               { "r16_snorm", PIPE_FORMAT_R16_SNORM, GLSL_TYPE_FLOAT, 130, 0, true, false },
               { "r8_snorm", PIPE_FORMAT_R8_SNORM, GLSL_TYPE_FLOAT, 130, 0, true, false },

               /* From GL_EXT_shader_image_load_store: */
               /* base_type is incorrect but it'll be patched later when we know
                * the variable type. See ast_to_hir.cpp */
               { "size1x8", PIPE_FORMAT_R8_SINT, GLSL_TYPE_VOID, 130, 0, false, true },
               { "size1x16", PIPE_FORMAT_R16_SINT, GLSL_TYPE_VOID, 130, 0, false, true },
               { "size1x32", PIPE_FORMAT_R32_SINT, GLSL_TYPE_VOID, 130, 0, false, true },
               { "size2x32", PIPE_FORMAT_R32G32_SINT, GLSL_TYPE_VOID, 130, 0, false, true },
               { "size4x32", PIPE_FORMAT_R32G32B32A32_SINT, GLSL_TYPE_VOID, 130, 0, false, true },
            };

            for (unsigned i = 0; i < ARRAY_SIZE(map); i++) {
               if ((state->is_version(map[i].required_glsl,
                                      map[i].required_essl) ||
                    (state->NV_image_formats_enable &&
                     map[i].nv_image_formats)) &&
                   match_layout_qualifier(yystack.l_mark[0].identifier, map[i].name, state) == 0) {
                  /* Skip ARB_shader_image_load_store qualifiers if not enabled */
                  if (!map[i].ext_qualifiers && !(state->ARB_shader_image_load_store_enable ||
                                                  state->is_version(420, 310))) {
                     continue;
                  }
                  /* Skip EXT_shader_image_load_store qualifiers if not enabled */
                  if (map[i].ext_qualifiers && !state->EXT_shader_image_load_store_enable) {
                     continue;
                  }
                  yyval.type_qualifier.flags.q.explicit_image_format = 1;
                  yyval.type_qualifier.image_format = map[i].format;
                  yyval.type_qualifier.image_base_type = map[i].base_type;
                  break;
               }
            }
         }
      }

      if (!yyval.type_qualifier.flags.i) {
         if (match_layout_qualifier(yystack.l_mark[0].identifier, "early_fragment_tests", state) == 0) {
            /* From section 4.4.1.3 of the GLSL 4.50 specification
             * (Fragment Shader Inputs):
             *
             *  "Fragment shaders also allow the following layout
             *   qualifier on in only (not with variable declarations)
             *     layout-qualifier-id
             *        early_fragment_tests
             *   [...]"
             */
            if (state->stage != MESA_SHADER_FRAGMENT) {
               _mesa_glsl_error(& yystack.p_mark[0], state,
                                "early_fragment_tests layout qualifier only "
                                "valid in fragment shaders");
            }

            yyval.type_qualifier.flags.q.early_fragment_tests = 1;
         }

         if (match_layout_qualifier(yystack.l_mark[0].identifier, "inner_coverage", state) == 0) {
            if (state->stage != MESA_SHADER_FRAGMENT) {
               _mesa_glsl_error(& yystack.p_mark[0], state,
                                "inner_coverage layout qualifier only "
                                "valid in fragment shaders");
            }

            if (state->INTEL_conservative_rasterization_enable) {
               yyval.type_qualifier.flags.q.inner_coverage = 1;
            } else {
               _mesa_glsl_error(& yystack.p_mark[0], state,
                                "inner_coverage layout qualifier present, "
                                "but the INTEL_conservative_rasterization extension "
                                "is not enabled.");
            }
         }

         if (match_layout_qualifier(yystack.l_mark[0].identifier, "post_depth_coverage", state) == 0) {
            if (state->stage != MESA_SHADER_FRAGMENT) {
               _mesa_glsl_error(& yystack.p_mark[0], state,
                                "post_depth_coverage layout qualifier only "
                                "valid in fragment shaders");
            }

            if (state->ARB_post_depth_coverage_enable ||
                state->INTEL_conservative_rasterization_enable) {
               yyval.type_qualifier.flags.q.post_depth_coverage = 1;
            } else {
               _mesa_glsl_error(& yystack.p_mark[0], state,
                                "post_depth_coverage layout qualifier present, "
                                "but the GL_ARB_post_depth_coverage extension "
                                "is not enabled.");
            }
         }

         if (yyval.type_qualifier.flags.q.post_depth_coverage && yyval.type_qualifier.flags.q.inner_coverage) {
            _mesa_glsl_error(& yystack.p_mark[0], state,
                             "post_depth_coverage & inner_coverage layout qualifiers "
                             "are mutually exclusive");
         }
      }

      const bool pixel_interlock_ordered = match_layout_qualifier(yystack.l_mark[0].identifier,
         "pixel_interlock_ordered", state) == 0;
      const bool pixel_interlock_unordered = match_layout_qualifier(yystack.l_mark[0].identifier,
         "pixel_interlock_unordered", state) == 0;
      const bool sample_interlock_ordered = match_layout_qualifier(yystack.l_mark[0].identifier,
         "sample_interlock_ordered", state) == 0;
      const bool sample_interlock_unordered = match_layout_qualifier(yystack.l_mark[0].identifier,
         "sample_interlock_unordered", state) == 0;

      if (pixel_interlock_ordered + pixel_interlock_unordered +
          sample_interlock_ordered + sample_interlock_unordered > 0 &&
          state->stage != MESA_SHADER_FRAGMENT) {
         _mesa_glsl_error(& yystack.p_mark[0], state, "interlock layout qualifiers: "
                          "pixel_interlock_ordered, pixel_interlock_unordered, "
                          "sample_interlock_ordered and sample_interlock_unordered, "
                          "only valid in fragment shader input layout declaration.");
      } else if (pixel_interlock_ordered + pixel_interlock_unordered +
                 sample_interlock_ordered + sample_interlock_unordered > 0 &&
                 !state->ARB_fragment_shader_interlock_enable &&
                 !state->NV_fragment_shader_interlock_enable) {
         _mesa_glsl_error(& yystack.p_mark[0], state,
                          "interlock layout qualifier present, but the "
                          "GL_ARB_fragment_shader_interlock or "
                          "GL_NV_fragment_shader_interlock extension is not "
                          "enabled.");
      } else {
         yyval.type_qualifier.flags.q.pixel_interlock_ordered = pixel_interlock_ordered;
         yyval.type_qualifier.flags.q.pixel_interlock_unordered = pixel_interlock_unordered;
         yyval.type_qualifier.flags.q.sample_interlock_ordered = sample_interlock_ordered;
         yyval.type_qualifier.flags.q.sample_interlock_unordered = sample_interlock_unordered;
      }

      /* Layout qualifiers for tessellation evaluation shaders. */
      if (!yyval.type_qualifier.flags.i) {
         static const struct {
            const char *s;
            GLenum e;
         } map[] = {
                 /* triangles already parsed by gs-specific code */
                 { "quads", GL_QUADS },
                 { "isolines", GL_ISOLINES },
         };
         for (unsigned i = 0; i < ARRAY_SIZE(map); i++) {
            if (match_layout_qualifier(yystack.l_mark[0].identifier, map[i].s, state) == 0) {
               yyval.type_qualifier.flags.q.prim_type = 1;
               yyval.type_qualifier.prim_type = map[i].e;
               break;
            }
         }

         if (yyval.type_qualifier.flags.i && !state->has_tessellation_shader()) {
            _mesa_glsl_error(& yystack.p_mark[0], state,
                             "primitive mode qualifier `%s' requires "
                             "GLSL 4.00 or ARB_tessellation_shader", yystack.l_mark[0].identifier);
         }
      }
      if (!yyval.type_qualifier.flags.i) {
         static const struct {
            const char *s;
            enum gl_tess_spacing e;
         } map[] = {
                 { "equal_spacing", TESS_SPACING_EQUAL },
                 { "fractional_odd_spacing", TESS_SPACING_FRACTIONAL_ODD },
                 { "fractional_even_spacing", TESS_SPACING_FRACTIONAL_EVEN },
         };
         for (unsigned i = 0; i < ARRAY_SIZE(map); i++) {
            if (match_layout_qualifier(yystack.l_mark[0].identifier, map[i].s, state) == 0) {
               yyval.type_qualifier.flags.q.vertex_spacing = 1;
               yyval.type_qualifier.vertex_spacing = map[i].e;
               break;
            }
         }

         if (yyval.type_qualifier.flags.i && !state->has_tessellation_shader()) {
            _mesa_glsl_error(& yystack.p_mark[0], state,
                             "vertex spacing qualifier `%s' requires "
                             "GLSL 4.00 or ARB_tessellation_shader", yystack.l_mark[0].identifier);
         }
      }
      if (!yyval.type_qualifier.flags.i) {
         if (match_layout_qualifier(yystack.l_mark[0].identifier, "cw", state) == 0) {
            yyval.type_qualifier.flags.q.ordering = 1;
            yyval.type_qualifier.ordering = GL_CW;
         } else if (match_layout_qualifier(yystack.l_mark[0].identifier, "ccw", state) == 0) {
            yyval.type_qualifier.flags.q.ordering = 1;
            yyval.type_qualifier.ordering = GL_CCW;
         }

         if (yyval.type_qualifier.flags.i && !state->has_tessellation_shader()) {
            _mesa_glsl_error(& yystack.p_mark[0], state,
                             "ordering qualifier `%s' requires "
                             "GLSL 4.00 or ARB_tessellation_shader", yystack.l_mark[0].identifier);
         }
      }
      if (!yyval.type_qualifier.flags.i) {
         if (match_layout_qualifier(yystack.l_mark[0].identifier, "point_mode", state) == 0) {
            yyval.type_qualifier.flags.q.point_mode = 1;
            yyval.type_qualifier.point_mode = true;
         }

         if (yyval.type_qualifier.flags.i && !state->has_tessellation_shader()) {
            _mesa_glsl_error(& yystack.p_mark[0], state,
                             "qualifier `point_mode' requires "
                             "GLSL 4.00 or ARB_tessellation_shader");
         }
      }

      if (!yyval.type_qualifier.flags.i) {
         static const struct {
            const char *s;
            uint32_t mask;
         } map[] = {
                 { "blend_support_multiply",       BITFIELD_BIT(BLEND_MULTIPLY) },
                 { "blend_support_screen",         BITFIELD_BIT(BLEND_SCREEN) },
                 { "blend_support_overlay",        BITFIELD_BIT(BLEND_OVERLAY) },
                 { "blend_support_darken",         BITFIELD_BIT(BLEND_DARKEN) },
                 { "blend_support_lighten",        BITFIELD_BIT(BLEND_LIGHTEN) },
                 { "blend_support_colordodge",     BITFIELD_BIT(BLEND_COLORDODGE) },
                 { "blend_support_colorburn",      BITFIELD_BIT(BLEND_COLORBURN) },
                 { "blend_support_hardlight",      BITFIELD_BIT(BLEND_HARDLIGHT) },
                 { "blend_support_softlight",      BITFIELD_BIT(BLEND_SOFTLIGHT) },
                 { "blend_support_difference",     BITFIELD_BIT(BLEND_DIFFERENCE) },
                 { "blend_support_exclusion",      BITFIELD_BIT(BLEND_EXCLUSION) },
                 { "blend_support_hsl_hue",        BITFIELD_BIT(BLEND_HSL_HUE) },
                 { "blend_support_hsl_saturation", BITFIELD_BIT(BLEND_HSL_SATURATION) },
                 { "blend_support_hsl_color",      BITFIELD_BIT(BLEND_HSL_COLOR) },
                 { "blend_support_hsl_luminosity", BITFIELD_BIT(BLEND_HSL_LUMINOSITY) },
                 { "blend_support_all_equations",  (1u << (BLEND_HSL_LUMINOSITY + 1)) - 2 },
         };
         for (unsigned i = 0; i < ARRAY_SIZE(map); i++) {
            if (match_layout_qualifier(yystack.l_mark[0].identifier, map[i].s, state) == 0) {
               yyval.type_qualifier.flags.q.blend_support = 1;
               state->fs_blend_support |= map[i].mask;
               break;
            }
         }

         if (yyval.type_qualifier.flags.i &&
             !state->KHR_blend_equation_advanced_enable &&
             !state->is_version(0, 320)) {
            _mesa_glsl_error(& yystack.p_mark[0], state,
                             "advanced blending layout qualifiers require "
                             "ESSL 3.20 or KHR_blend_equation_advanced");
         }

         if (yyval.type_qualifier.flags.i && state->stage != MESA_SHADER_FRAGMENT) {
            _mesa_glsl_error(& yystack.p_mark[0], state,
                             "advanced blending layout qualifiers only "
                             "valid in fragment shaders");
         }
      }

      /* Layout qualifiers for ARB_compute_variable_group_size. */
      if (!yyval.type_qualifier.flags.i) {
         if (match_layout_qualifier(yystack.l_mark[0].identifier, "local_size_variable", state) == 0) {
            yyval.type_qualifier.flags.q.local_size_variable = 1;
         }

         if (yyval.type_qualifier.flags.i && !state->ARB_compute_variable_group_size_enable) {
            _mesa_glsl_error(& yystack.p_mark[0], state,
                             "qualifier `local_size_variable` requires "
                             "ARB_compute_variable_group_size");
         }
      }

      /* Layout qualifiers for ARB_bindless_texture. */
      if (!yyval.type_qualifier.flags.i) {
         if (match_layout_qualifier(yystack.l_mark[0].identifier, "bindless_sampler", state) == 0)
            yyval.type_qualifier.flags.q.bindless_sampler = 1;
         if (match_layout_qualifier(yystack.l_mark[0].identifier, "bound_sampler", state) == 0)
            yyval.type_qualifier.flags.q.bound_sampler = 1;

         if (state->has_shader_image_load_store()) {
            if (match_layout_qualifier(yystack.l_mark[0].identifier, "bindless_image", state) == 0)
               yyval.type_qualifier.flags.q.bindless_image = 1;
            if (match_layout_qualifier(yystack.l_mark[0].identifier, "bound_image", state) == 0)
               yyval.type_qualifier.flags.q.bound_image = 1;
         }

         if (yyval.type_qualifier.flags.i && !state->has_bindless()) {
            _mesa_glsl_error(& yystack.p_mark[0], state,
                             "qualifier `%s` requires "
                             "ARB_bindless_texture", yystack.l_mark[0].identifier);
         }
      }

      if (!yyval.type_qualifier.flags.i &&
          state->EXT_shader_framebuffer_fetch_non_coherent_enable) {
         if (match_layout_qualifier(yystack.l_mark[0].identifier, "noncoherent", state) == 0)
            yyval.type_qualifier.flags.q.non_coherent = 1;
      }

      /* Layout qualifiers for NV_compute_shader_derivatives.*/
      if (!yyval.type_qualifier.flags.i) {
         if (match_layout_qualifier(yystack.l_mark[0].identifier, "derivative_group_quadsNV", state) == 0) {
            yyval.type_qualifier.flags.q.derivative_group = 1;
            yyval.type_qualifier.derivative_group = DERIVATIVE_GROUP_QUADS;
         } else if (match_layout_qualifier(yystack.l_mark[0].identifier, "derivative_group_linearNV", state) == 0) {
            yyval.type_qualifier.flags.q.derivative_group = 1;
            yyval.type_qualifier.derivative_group = DERIVATIVE_GROUP_LINEAR;
         }

         if (yyval.type_qualifier.flags.i) {
            if (!state->has_compute_shader()) {
               _mesa_glsl_error(& yystack.p_mark[0], state,
                                "qualifier `%s' requires "
                                "a compute shader", yystack.l_mark[0].identifier);
            }

            if (!state->NV_compute_shader_derivatives_enable) {
               _mesa_glsl_error(& yystack.p_mark[0], state,
                                "qualifier `%s' requires "
                                "NV_compute_shader_derivatives", yystack.l_mark[0].identifier);
            }

            if (state->NV_compute_shader_derivatives_warn) {
               _mesa_glsl_warning(& yystack.p_mark[0], state,
                                  "NV_compute_shader_derivatives layout "
                                  "qualifier `%s' used", yystack.l_mark[0].identifier);
            }
         }
      }

      /* Layout qualifier for NV_viewport_array2. */
      if (!yyval.type_qualifier.flags.i && state->stage != MESA_SHADER_FRAGMENT) {
         if (match_layout_qualifier(yystack.l_mark[0].identifier, "viewport_relative", state) == 0) {
            yyval.type_qualifier.flags.q.viewport_relative = 1;
         }

         if (yyval.type_qualifier.flags.i && !state->NV_viewport_array2_enable) {
            _mesa_glsl_error(& yystack.p_mark[0], state,
                             "qualifier `%s' requires "
                             "GL_NV_viewport_array2", yystack.l_mark[0].identifier);
         }

         if (yyval.type_qualifier.flags.i && state->NV_viewport_array2_warn) {
            _mesa_glsl_warning(& yystack.p_mark[0], state,
                               "GL_NV_viewport_array2 layout "
                               "identifier `%s' used", yystack.l_mark[0].identifier);
         }
      }

      if (!yyval.type_qualifier.flags.i) {
         _mesa_glsl_error(& yystack.p_mark[0], state, "unrecognized layout identifier "
                          "`%s'", yystack.l_mark[0].identifier);
         YYERROR;
      }
   }
#line 4814 "compiler/glsl/glsl_parser.cpp"
break;
case 151:
#line 1739 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      memset(& yyval.type_qualifier, 0, sizeof(yyval.type_qualifier));
      linear_ctx *ctx = state->linalloc;

      if (yystack.l_mark[0].expression->oper != ast_int_constant &&
          yystack.l_mark[0].expression->oper != ast_uint_constant &&
          !state->has_enhanced_layouts()) {
         _mesa_glsl_error(& yystack.p_mark[-2], state,
                          "compile-time constant expressions require "
                          "GLSL 4.40 or ARB_enhanced_layouts");
      }

      if (match_layout_qualifier("align", yystack.l_mark[-2].identifier, state) == 0) {
         if (!state->has_enhanced_layouts()) {
            _mesa_glsl_error(& yystack.p_mark[-2], state,
                             "align qualifier requires "
                             "GLSL 4.40 or ARB_enhanced_layouts");
         } else {
            yyval.type_qualifier.flags.q.explicit_align = 1;
            yyval.type_qualifier.align = yystack.l_mark[0].expression;
         }
      }

      if (match_layout_qualifier("location", yystack.l_mark[-2].identifier, state) == 0) {
         yyval.type_qualifier.flags.q.explicit_location = 1;

         if (yyval.type_qualifier.flags.q.attribute == 1 &&
             state->ARB_explicit_attrib_location_warn) {
            _mesa_glsl_warning(& yystack.p_mark[-2], state,
                               "GL_ARB_explicit_attrib_location layout "
                               "identifier `%s' used", yystack.l_mark[-2].identifier);
         }
         yyval.type_qualifier.location = yystack.l_mark[0].expression;
      }

      if (match_layout_qualifier("num_views", yystack.l_mark[-2].identifier, state) == 0) {
         yyval.type_qualifier.flags.q.explicit_numviews = 1;
         yyval.type_qualifier.num_views = yystack.l_mark[0].expression;
      }

      if (match_layout_qualifier("component", yystack.l_mark[-2].identifier, state) == 0) {
         if (!state->has_enhanced_layouts()) {
            _mesa_glsl_error(& yystack.p_mark[-2], state,
                             "component qualifier requires "
                             "GLSL 4.40 or ARB_enhanced_layouts");
         } else {
            yyval.type_qualifier.flags.q.explicit_component = 1;
            yyval.type_qualifier.component = yystack.l_mark[0].expression;
         }
      }

      if (match_layout_qualifier("index", yystack.l_mark[-2].identifier, state) == 0) {
         if (state->es_shader && !state->EXT_blend_func_extended_enable) {
            _mesa_glsl_error(& yystack.p_mark[0], state, "index layout qualifier requires EXT_blend_func_extended");
            YYERROR;
         }

         yyval.type_qualifier.flags.q.explicit_index = 1;
         yyval.type_qualifier.index = yystack.l_mark[0].expression;
      }

      if ((state->has_420pack_or_es31() ||
           state->has_atomic_counters() ||
           state->has_shader_storage_buffer_objects()) &&
          match_layout_qualifier("binding", yystack.l_mark[-2].identifier, state) == 0) {
         yyval.type_qualifier.flags.q.explicit_binding = 1;
         yyval.type_qualifier.binding = yystack.l_mark[0].expression;
      }

      if ((state->has_atomic_counters() ||
           state->has_enhanced_layouts()) &&
          match_layout_qualifier("offset", yystack.l_mark[-2].identifier, state) == 0) {
         yyval.type_qualifier.flags.q.explicit_offset = 1;
         yyval.type_qualifier.offset = yystack.l_mark[0].expression;
      }

      if (match_layout_qualifier("max_vertices", yystack.l_mark[-2].identifier, state) == 0) {
         yyval.type_qualifier.flags.q.max_vertices = 1;
         yyval.type_qualifier.max_vertices = new(ctx) ast_layout_expression(yystack.p_mark[-2], yystack.l_mark[0].expression);
         if (!state->has_geometry_shader()) {
            _mesa_glsl_error(& yystack.p_mark[0], state,
                             "#version 150 max_vertices qualifier "
                             "specified");
         }
      }

      if (state->stage == MESA_SHADER_GEOMETRY) {
         if (match_layout_qualifier("stream", yystack.l_mark[-2].identifier, state) == 0 &&
             state->check_explicit_attrib_stream_allowed(& yystack.p_mark[0])) {
            yyval.type_qualifier.flags.q.stream = 1;
            yyval.type_qualifier.flags.q.explicit_stream = 1;
            yyval.type_qualifier.stream = yystack.l_mark[0].expression;
         }
      }

      if (state->has_enhanced_layouts()) {
         if (match_layout_qualifier("xfb_buffer", yystack.l_mark[-2].identifier, state) == 0) {
            yyval.type_qualifier.flags.q.xfb_buffer = 1;
            yyval.type_qualifier.flags.q.explicit_xfb_buffer = 1;
            yyval.type_qualifier.xfb_buffer = yystack.l_mark[0].expression;
         }

         if (match_layout_qualifier("xfb_offset", yystack.l_mark[-2].identifier, state) == 0) {
            yyval.type_qualifier.flags.q.explicit_xfb_offset = 1;
            yyval.type_qualifier.offset = yystack.l_mark[0].expression;
         }

         if (match_layout_qualifier("xfb_stride", yystack.l_mark[-2].identifier, state) == 0) {
            yyval.type_qualifier.flags.q.xfb_stride = 1;
            yyval.type_qualifier.flags.q.explicit_xfb_stride = 1;
            yyval.type_qualifier.xfb_stride = yystack.l_mark[0].expression;
         }
      }

      static const char * const local_size_qualifiers[3] = {
         "local_size_x",
         "local_size_y",
         "local_size_z",
      };
      for (int i = 0; i < 3; i++) {
         if (match_layout_qualifier(local_size_qualifiers[i], yystack.l_mark[-2].identifier,
                                    state) == 0) {
            if (!state->has_compute_shader()) {
               _mesa_glsl_error(& yystack.p_mark[0], state,
                                "%s qualifier requires GLSL 4.30 or "
                                "GLSL ES 3.10 or ARB_compute_shader",
                                local_size_qualifiers[i]);
               YYERROR;
            } else {
               yyval.type_qualifier.flags.q.local_size |= (1 << i);
               yyval.type_qualifier.local_size[i] = new(ctx) ast_layout_expression(yystack.p_mark[-2], yystack.l_mark[0].expression);
            }
            break;
         }
      }

      if (match_layout_qualifier("invocations", yystack.l_mark[-2].identifier, state) == 0) {
         yyval.type_qualifier.flags.q.invocations = 1;
         yyval.type_qualifier.invocations = new(ctx) ast_layout_expression(yystack.p_mark[-2], yystack.l_mark[0].expression);
         if (!state->is_version(400, 320) &&
             !state->ARB_gpu_shader5_enable &&
             !state->OES_geometry_shader_enable &&
             !state->EXT_geometry_shader_enable) {
            _mesa_glsl_error(& yystack.p_mark[0], state,
                             "GL_ARB_gpu_shader5 invocations "
                             "qualifier specified");
         }
      }

      /* Layout qualifiers for tessellation control shaders. */
      if (match_layout_qualifier("vertices", yystack.l_mark[-2].identifier, state) == 0) {
         yyval.type_qualifier.flags.q.vertices = 1;
         yyval.type_qualifier.vertices = new(ctx) ast_layout_expression(yystack.p_mark[-2], yystack.l_mark[0].expression);
         if (!state->has_tessellation_shader()) {
            _mesa_glsl_error(& yystack.p_mark[-2], state,
                             "vertices qualifier requires GLSL 4.00 or "
                             "ARB_tessellation_shader");
         }
      }

      /* If the identifier didn't match any known layout identifiers,
       * emit an error.
       */
      if (!yyval.type_qualifier.flags.i) {
         _mesa_glsl_error(& yystack.p_mark[-2], state, "unrecognized layout identifier "
                          "`%s'", yystack.l_mark[-2].identifier);
         YYERROR;
      }
   }
#line 4987 "compiler/glsl/glsl_parser.cpp"
break;
case 152:
#line 1909 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      yyval.type_qualifier = yystack.l_mark[0].type_qualifier;
      /* Layout qualifiers for ARB_uniform_buffer_object. */
      if (yyval.type_qualifier.flags.q.uniform && !state->has_uniform_buffer_objects()) {
         _mesa_glsl_error(& yystack.p_mark[0], state,
                          "#version 140 / GL_ARB_uniform_buffer_object "
                          "layout qualifier `uniform' is used");
      } else if (yyval.type_qualifier.flags.q.uniform && state->ARB_uniform_buffer_object_warn) {
         _mesa_glsl_warning(& yystack.p_mark[0], state,
                            "#version 140 / GL_ARB_uniform_buffer_object "
                            "layout qualifier `uniform' is used");
      }
   }
#line 5004 "compiler/glsl/glsl_parser.cpp"
break;
case 153:
#line 1935 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      memset(& yyval.type_qualifier, 0, sizeof(yyval.type_qualifier));
      yyval.type_qualifier.flags.q.row_major = 1;
   }
#line 5012 "compiler/glsl/glsl_parser.cpp"
break;
case 154:
#line 1940 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      memset(& yyval.type_qualifier, 0, sizeof(yyval.type_qualifier));
      yyval.type_qualifier.flags.q.packed = 1;
   }
#line 5020 "compiler/glsl/glsl_parser.cpp"
break;
case 155:
#line 1945 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      memset(& yyval.type_qualifier, 0, sizeof(yyval.type_qualifier));
      yyval.type_qualifier.flags.q.shared = 1;
   }
#line 5028 "compiler/glsl/glsl_parser.cpp"
break;
case 156:
#line 1953 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      memset(& yyval.type_qualifier, 0, sizeof(yyval.type_qualifier));
      yyval.type_qualifier.flags.q.subroutine = 1;
   }
#line 5036 "compiler/glsl/glsl_parser.cpp"
break;
case 157:
#line 1958 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      memset(& yyval.type_qualifier, 0, sizeof(yyval.type_qualifier));
      yyval.type_qualifier.flags.q.subroutine = 1;
      yyval.type_qualifier.subroutine_list = yystack.l_mark[-1].subroutine_list;
   }
#line 5045 "compiler/glsl/glsl_parser.cpp"
break;
case 158:
#line 1967 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
        linear_ctx *ctx = state->linalloc;
        ast_declaration *decl = new(ctx)  ast_declaration(yystack.l_mark[0].identifier, NULL, NULL);
        decl->set_location(yystack.p_mark[0]);

        yyval.subroutine_list = new(ctx) ast_subroutine_list();
        yyval.subroutine_list->declarations.push_tail(&decl->link);
   }
#line 5057 "compiler/glsl/glsl_parser.cpp"
break;
case 159:
#line 1976 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
        linear_ctx *ctx = state->linalloc;
        ast_declaration *decl = new(ctx)  ast_declaration(yystack.l_mark[0].identifier, NULL, NULL);
        decl->set_location(yystack.p_mark[0]);

        yyval.subroutine_list = yystack.l_mark[-2].subroutine_list;
        yyval.subroutine_list->declarations.push_tail(&decl->link);
   }
#line 5069 "compiler/glsl/glsl_parser.cpp"
break;
case 160:
#line 1988 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      memset(& yyval.type_qualifier, 0, sizeof(yyval.type_qualifier));
      yyval.type_qualifier.flags.q.smooth = 1;
   }
#line 5077 "compiler/glsl/glsl_parser.cpp"
break;
case 161:
#line 1993 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      memset(& yyval.type_qualifier, 0, sizeof(yyval.type_qualifier));
      yyval.type_qualifier.flags.q.flat = 1;
   }
#line 5085 "compiler/glsl/glsl_parser.cpp"
break;
case 162:
#line 1998 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      memset(& yyval.type_qualifier, 0, sizeof(yyval.type_qualifier));
      yyval.type_qualifier.flags.q.noperspective = 1;
   }
#line 5093 "compiler/glsl/glsl_parser.cpp"
break;
case 163:
#line 2007 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      memset(& yyval.type_qualifier, 0, sizeof(yyval.type_qualifier));
      yyval.type_qualifier.flags.q.invariant = 1;
   }
#line 5101 "compiler/glsl/glsl_parser.cpp"
break;
case 164:
#line 2012 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      memset(& yyval.type_qualifier, 0, sizeof(yyval.type_qualifier));
      yyval.type_qualifier.flags.q.precise = 1;
   }
#line 5109 "compiler/glsl/glsl_parser.cpp"
break;
case 171:
#line 2023 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      memset(&yyval.type_qualifier, 0, sizeof(yyval.type_qualifier));
      yyval.type_qualifier.precision = yystack.l_mark[0].n;
   }
#line 5117 "compiler/glsl/glsl_parser.cpp"
break;
case 172:
#line 2041 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      if (yystack.l_mark[0].type_qualifier.flags.q.precise)
         _mesa_glsl_error(&yystack.p_mark[-1], state, "duplicate \"precise\" qualifier");

      yyval.type_qualifier = yystack.l_mark[0].type_qualifier;
      yyval.type_qualifier.flags.q.precise = 1;
   }
#line 5128 "compiler/glsl/glsl_parser.cpp"
break;
case 173:
#line 2049 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      if (yystack.l_mark[0].type_qualifier.flags.q.invariant)
         _mesa_glsl_error(&yystack.p_mark[-1], state, "duplicate \"invariant\" qualifier");

      if (!state->has_420pack_or_es31() && yystack.l_mark[0].type_qualifier.flags.q.precise)
         _mesa_glsl_error(&yystack.p_mark[-1], state,
                          "\"invariant\" must come after \"precise\"");

      yyval.type_qualifier = yystack.l_mark[0].type_qualifier;
      yyval.type_qualifier.flags.q.invariant = 1;

      /* GLSL ES 3.00 spec, section 4.6.1 "The Invariant Qualifier":
       *
       * "Only variables output from a shader can be candidates for invariance.
       * This includes user-defined output variables and the built-in output
       * variables. As only outputs can be declared as invariant, an invariant
       * output from one shader stage will still match an input of a subsequent
       * stage without the input being declared as invariant."
       *
       * On the desktop side, this text first appears in GLSL 4.20.
       */
      if (state->is_version(420, 300) && yyval.type_qualifier.flags.q.in)
         _mesa_glsl_error(&yystack.p_mark[-1], state, "invariant qualifiers cannot be used with shader inputs");
   }
#line 5156 "compiler/glsl/glsl_parser.cpp"
break;
case 174:
#line 2074 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      /* Section 4.3 of the GLSL 1.40 specification states:
       * "...qualified with one of these interpolation qualifiers"
       *
       * GLSL 1.30 claims to allow "one or more", but insists that:
       * "These interpolation qualifiers may only precede the qualifiers in,
       *  centroid in, out, or centroid out in a declaration."
       *
       * ...which means that e.g. smooth can't precede smooth, so there can be
       * only one after all, and the 1.40 text is a clarification, not a change.
       */
      if (yystack.l_mark[0].type_qualifier.has_interpolation())
         _mesa_glsl_error(&yystack.p_mark[-1], state, "duplicate interpolation qualifier");

      if (!state->has_420pack_or_es31() &&
          (yystack.l_mark[0].type_qualifier.flags.q.precise || yystack.l_mark[0].type_qualifier.flags.q.invariant)) {
         _mesa_glsl_error(&yystack.p_mark[-1], state, "interpolation qualifiers must come "
                          "after \"precise\" or \"invariant\"");
      }

      yyval.type_qualifier = yystack.l_mark[-1].type_qualifier;
      yyval.type_qualifier.merge_qualifier(&yystack.p_mark[-1], state, yystack.l_mark[0].type_qualifier, false);
   }
#line 5183 "compiler/glsl/glsl_parser.cpp"
break;
case 175:
#line 2098 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      /* In the absence of ARB_shading_language_420pack, layout qualifiers may
       * appear no later than auxiliary storage qualifiers. There is no
       * particularly clear spec language mandating this, but in all examples
       * the layout qualifier precedes the storage qualifier.
       *
       * We allow combinations of layout with interpolation, invariant or
       * precise qualifiers since these are useful in ARB_separate_shader_objects.
       * There is no clear spec guidance on this either.
       */
      yyval.type_qualifier = yystack.l_mark[-1].type_qualifier;
      yyval.type_qualifier.merge_qualifier(& yystack.p_mark[-1], state, yystack.l_mark[0].type_qualifier, false, yystack.l_mark[0].type_qualifier.has_layout());
   }
#line 5200 "compiler/glsl/glsl_parser.cpp"
break;
case 176:
#line 2112 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      yyval.type_qualifier = yystack.l_mark[-1].type_qualifier;
      yyval.type_qualifier.merge_qualifier(&yystack.p_mark[-1], state, yystack.l_mark[0].type_qualifier, false);
   }
#line 5208 "compiler/glsl/glsl_parser.cpp"
break;
case 177:
#line 2117 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      if (yystack.l_mark[0].type_qualifier.has_auxiliary_storage()) {
         _mesa_glsl_error(&yystack.p_mark[-1], state,
                          "duplicate auxiliary storage qualifier (centroid or sample)");
      }

      if ((!state->has_420pack_or_es31() && !state->EXT_gpu_shader4_enable) &&
          (yystack.l_mark[0].type_qualifier.flags.q.precise || yystack.l_mark[0].type_qualifier.flags.q.invariant ||
           yystack.l_mark[0].type_qualifier.has_interpolation() || yystack.l_mark[0].type_qualifier.has_layout())) {
         _mesa_glsl_error(&yystack.p_mark[-1], state, "auxiliary storage qualifiers must come "
                          "just before storage qualifiers");
      }
      yyval.type_qualifier = yystack.l_mark[-1].type_qualifier;
      yyval.type_qualifier.merge_qualifier(&yystack.p_mark[-1], state, yystack.l_mark[0].type_qualifier, false);
   }
#line 5227 "compiler/glsl/glsl_parser.cpp"
break;
case 178:
#line 2133 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      /* Section 4.3 of the GLSL 1.20 specification states:
       * "Variable declarations may have a storage qualifier specified..."
       *  1.30 clarifies this to "may have one storage qualifier".
       *
       * GL_EXT_gpu_shader4 allows "varying out" in fragment shaders.
       */
      if (yystack.l_mark[0].type_qualifier.has_storage() &&
          (!state->EXT_gpu_shader4_enable ||
           state->stage != MESA_SHADER_FRAGMENT ||
           !yystack.l_mark[-1].type_qualifier.flags.q.varying || !yystack.l_mark[0].type_qualifier.flags.q.out))
         _mesa_glsl_error(&yystack.p_mark[-1], state, "duplicate storage qualifier");

      if (!state->has_420pack_or_es31() &&
          (yystack.l_mark[0].type_qualifier.flags.q.precise || yystack.l_mark[0].type_qualifier.flags.q.invariant || yystack.l_mark[0].type_qualifier.has_interpolation() ||
           yystack.l_mark[0].type_qualifier.has_layout() || yystack.l_mark[0].type_qualifier.has_auxiliary_storage())) {
         _mesa_glsl_error(&yystack.p_mark[-1], state, "storage qualifiers must come after "
                          "precise, invariant, interpolation, layout and auxiliary "
                          "storage qualifiers");
      }

      yyval.type_qualifier = yystack.l_mark[-1].type_qualifier;
      yyval.type_qualifier.merge_qualifier(&yystack.p_mark[-1], state, yystack.l_mark[0].type_qualifier, false);
   }
#line 5255 "compiler/glsl/glsl_parser.cpp"
break;
case 179:
#line 2158 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      if (yystack.l_mark[0].type_qualifier.precision != ast_precision_none)
         _mesa_glsl_error(&yystack.p_mark[-1], state, "duplicate precision qualifier");

      if (!(state->has_420pack_or_es31()) &&
          yystack.l_mark[0].type_qualifier.flags.i != 0)
         _mesa_glsl_error(&yystack.p_mark[-1], state, "precision qualifiers must come last");

      yyval.type_qualifier = yystack.l_mark[0].type_qualifier;
      yyval.type_qualifier.precision = yystack.l_mark[-1].n;
   }
#line 5270 "compiler/glsl/glsl_parser.cpp"
break;
case 180:
#line 2170 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      yyval.type_qualifier = yystack.l_mark[-1].type_qualifier;
      yyval.type_qualifier.merge_qualifier(&yystack.p_mark[-1], state, yystack.l_mark[0].type_qualifier, false);
   }
#line 5278 "compiler/glsl/glsl_parser.cpp"
break;
case 181:
#line 2178 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      memset(& yyval.type_qualifier, 0, sizeof(yyval.type_qualifier));
      yyval.type_qualifier.flags.q.centroid = 1;
   }
#line 5286 "compiler/glsl/glsl_parser.cpp"
break;
case 182:
#line 2183 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      memset(& yyval.type_qualifier, 0, sizeof(yyval.type_qualifier));
      yyval.type_qualifier.flags.q.sample = 1;
   }
#line 5294 "compiler/glsl/glsl_parser.cpp"
break;
case 183:
#line 2188 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      memset(& yyval.type_qualifier, 0, sizeof(yyval.type_qualifier));
      yyval.type_qualifier.flags.q.patch = 1;
   }
#line 5302 "compiler/glsl/glsl_parser.cpp"
break;
case 184:
#line 2195 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      memset(& yyval.type_qualifier, 0, sizeof(yyval.type_qualifier));
      yyval.type_qualifier.flags.q.constant = 1;
   }
#line 5310 "compiler/glsl/glsl_parser.cpp"
break;
case 185:
#line 2200 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      memset(& yyval.type_qualifier, 0, sizeof(yyval.type_qualifier));
      yyval.type_qualifier.flags.q.attribute = 1;
   }
#line 5318 "compiler/glsl/glsl_parser.cpp"
break;
case 186:
#line 2205 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      memset(& yyval.type_qualifier, 0, sizeof(yyval.type_qualifier));
      yyval.type_qualifier.flags.q.varying = 1;
   }
#line 5326 "compiler/glsl/glsl_parser.cpp"
break;
case 187:
#line 2210 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      memset(& yyval.type_qualifier, 0, sizeof(yyval.type_qualifier));
      yyval.type_qualifier.flags.q.in = 1;
   }
#line 5334 "compiler/glsl/glsl_parser.cpp"
break;
case 188:
#line 2215 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      memset(& yyval.type_qualifier, 0, sizeof(yyval.type_qualifier));
      yyval.type_qualifier.flags.q.out = 1;

      if (state->stage == MESA_SHADER_GEOMETRY &&
          state->has_explicit_attrib_stream()) {
         /* Section 4.3.8.2 (Output Layout Qualifiers) of the GLSL 4.00
          * spec says:
          *
          *     "If the block or variable is declared with the stream
          *     identifier, it is associated with the specified stream;
          *     otherwise, it is associated with the current default stream."
          */
          yyval.type_qualifier.flags.q.stream = 1;
          yyval.type_qualifier.flags.q.explicit_stream = 0;
          yyval.type_qualifier.stream = state->out_qualifier->stream;
      }

      if (state->has_enhanced_layouts() && state->exts->ARB_transform_feedback3) {
          yyval.type_qualifier.flags.q.xfb_buffer = 1;
          yyval.type_qualifier.flags.q.explicit_xfb_buffer = 0;
          yyval.type_qualifier.xfb_buffer = state->out_qualifier->xfb_buffer;
      }
   }
#line 5362 "compiler/glsl/glsl_parser.cpp"
break;
case 189:
#line 2240 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      memset(& yyval.type_qualifier, 0, sizeof(yyval.type_qualifier));
      yyval.type_qualifier.flags.q.in = 1;
      yyval.type_qualifier.flags.q.out = 1;

      if (!state->has_framebuffer_fetch() ||
          !state->is_version(130, 300) ||
          state->stage != MESA_SHADER_FRAGMENT)
         _mesa_glsl_error(&yystack.p_mark[0], state, "A single interface variable cannot be "
                          "declared as both input and output");
   }
#line 5377 "compiler/glsl/glsl_parser.cpp"
break;
case 190:
#line 2252 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      memset(& yyval.type_qualifier, 0, sizeof(yyval.type_qualifier));
      yyval.type_qualifier.flags.q.uniform = 1;
   }
#line 5385 "compiler/glsl/glsl_parser.cpp"
break;
case 191:
#line 2257 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      memset(& yyval.type_qualifier, 0, sizeof(yyval.type_qualifier));
      yyval.type_qualifier.flags.q.buffer = 1;
   }
#line 5393 "compiler/glsl/glsl_parser.cpp"
break;
case 192:
#line 2262 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      memset(& yyval.type_qualifier, 0, sizeof(yyval.type_qualifier));
      yyval.type_qualifier.flags.q.shared_storage = 1;
   }
#line 5401 "compiler/glsl/glsl_parser.cpp"
break;
case 193:
#line 2270 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      memset(& yyval.type_qualifier, 0, sizeof(yyval.type_qualifier));
      yyval.type_qualifier.flags.q.coherent = 1;
   }
#line 5409 "compiler/glsl/glsl_parser.cpp"
break;
case 194:
#line 2275 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      memset(& yyval.type_qualifier, 0, sizeof(yyval.type_qualifier));
      yyval.type_qualifier.flags.q._volatile = 1;
   }
#line 5417 "compiler/glsl/glsl_parser.cpp"
break;
case 195:
#line 2280 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      STATIC_ASSERT(sizeof(yyval.type_qualifier.flags.q) <= sizeof(yyval.type_qualifier.flags.i));
      memset(& yyval.type_qualifier, 0, sizeof(yyval.type_qualifier));
      yyval.type_qualifier.flags.q.restrict_flag = 1;
   }
#line 5426 "compiler/glsl/glsl_parser.cpp"
break;
case 196:
#line 2286 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      memset(& yyval.type_qualifier, 0, sizeof(yyval.type_qualifier));
      yyval.type_qualifier.flags.q.read_only = 1;
   }
#line 5434 "compiler/glsl/glsl_parser.cpp"
break;
case 197:
#line 2291 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      memset(& yyval.type_qualifier, 0, sizeof(yyval.type_qualifier));
      yyval.type_qualifier.flags.q.write_only = 1;
   }
#line 5442 "compiler/glsl/glsl_parser.cpp"
break;
case 198:
#line 2299 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      linear_ctx *ctx = state->linalloc;
      yyval.array_specifier = new(ctx) ast_array_specifier(yystack.p_mark[-1], new(ctx) ast_expression(
                                                  ast_unsized_array_dim, NULL,
                                                  NULL, NULL));
      yyval.array_specifier->set_location_range(yystack.p_mark[-1], yystack.p_mark[0]);
   }
#line 5453 "compiler/glsl/glsl_parser.cpp"
break;
case 199:
#line 2307 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      linear_ctx *ctx = state->linalloc;
      yyval.array_specifier = new(ctx) ast_array_specifier(yystack.p_mark[-2], yystack.l_mark[-1].expression);
      yyval.array_specifier->set_location_range(yystack.p_mark[-2], yystack.p_mark[0]);
   }
#line 5462 "compiler/glsl/glsl_parser.cpp"
break;
case 200:
#line 2313 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      linear_ctx *ctx = state->linalloc;
      yyval.array_specifier = yystack.l_mark[-2].array_specifier;

      if (state->check_arrays_of_arrays_allowed(& yystack.p_mark[-2])) {
         yyval.array_specifier->add_dimension(new(ctx) ast_expression(ast_unsized_array_dim, NULL,
                                                   NULL, NULL));
      }
   }
#line 5475 "compiler/glsl/glsl_parser.cpp"
break;
case 201:
#line 2323 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      yyval.array_specifier = yystack.l_mark[-3].array_specifier;

      if (state->check_arrays_of_arrays_allowed(& yystack.p_mark[-3])) {
         yyval.array_specifier->add_dimension(yystack.l_mark[-1].expression);
      }
   }
#line 5486 "compiler/glsl/glsl_parser.cpp"
break;
case 203:
#line 2335 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      yyval.type_specifier = yystack.l_mark[-1].type_specifier;
      yyval.type_specifier->array_specifier = yystack.l_mark[0].array_specifier;
   }
#line 5494 "compiler/glsl/glsl_parser.cpp"
break;
case 204:
#line 2343 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      linear_ctx *ctx = state->linalloc;
      yyval.type_specifier = new(ctx) ast_type_specifier(yystack.l_mark[0].type);
      yyval.type_specifier->set_location(yystack.p_mark[0]);
   }
#line 5503 "compiler/glsl/glsl_parser.cpp"
break;
case 205:
#line 2349 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      linear_ctx *ctx = state->linalloc;
      yyval.type_specifier = new(ctx) ast_type_specifier(yystack.l_mark[0].struct_specifier);
      yyval.type_specifier->set_location(yystack.p_mark[0]);
   }
#line 5512 "compiler/glsl/glsl_parser.cpp"
break;
case 206:
#line 2355 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      linear_ctx *ctx = state->linalloc;
      yyval.type_specifier = new(ctx) ast_type_specifier(yystack.l_mark[0].identifier);
      yyval.type_specifier->set_location(yystack.p_mark[0]);
   }
#line 5521 "compiler/glsl/glsl_parser.cpp"
break;
case 207:
#line 2363 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{ yyval.type = &glsl_type_builtin_void; }
#line 5526 "compiler/glsl/glsl_parser.cpp"
break;
case 208:
#line 2364 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{ yyval.type = yystack.l_mark[0].type; }
#line 5531 "compiler/glsl/glsl_parser.cpp"
break;
case 209:
#line 2366 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      if (yystack.l_mark[0].type == &glsl_type_builtin_int) {
         yyval.type = &glsl_type_builtin_uint;
      } else {
         _mesa_glsl_error(&yystack.p_mark[-1], state,
                          "\"unsigned\" is only allowed before \"int\"");
      }
   }
#line 5543 "compiler/glsl/glsl_parser.cpp"
break;
case 210:
#line 2378 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      state->check_precision_qualifiers_allowed(&yystack.p_mark[0]);
      yyval.n = ast_precision_high;
   }
#line 5551 "compiler/glsl/glsl_parser.cpp"
break;
case 211:
#line 2383 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      state->check_precision_qualifiers_allowed(&yystack.p_mark[0]);
      yyval.n = ast_precision_medium;
   }
#line 5559 "compiler/glsl/glsl_parser.cpp"
break;
case 212:
#line 2388 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      state->check_precision_qualifiers_allowed(&yystack.p_mark[0]);
      yyval.n = ast_precision_low;
   }
#line 5567 "compiler/glsl/glsl_parser.cpp"
break;
case 213:
#line 2396 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      linear_ctx *ctx = state->linalloc;
      yyval.struct_specifier = new(ctx) ast_struct_specifier(yystack.l_mark[-3].identifier, yystack.l_mark[-1].declarator_list);
      yyval.struct_specifier->set_location_range(yystack.p_mark[-3], yystack.p_mark[0]);
      state->symbols->add_type(yystack.l_mark[-3].identifier, &glsl_type_builtin_void);
   }
#line 5577 "compiler/glsl/glsl_parser.cpp"
break;
case 214:
#line 2403 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      linear_ctx *ctx = state->linalloc;

      /* All anonymous structs have the same name. This simplifies matching of
       * globals whose type is an unnamed struct.
       *
       * It also avoids a memory leak when the same shader is compiled over and
       * over again.
       */
      yyval.struct_specifier = new(ctx) ast_struct_specifier("#anon_struct", yystack.l_mark[-1].declarator_list);

      yyval.struct_specifier->set_location_range(yystack.p_mark[-2], yystack.p_mark[0]);
   }
#line 5594 "compiler/glsl/glsl_parser.cpp"
break;
case 215:
#line 2420 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      yyval.declarator_list = yystack.l_mark[0].declarator_list;
      yystack.l_mark[0].declarator_list->link.self_link();
   }
#line 5602 "compiler/glsl/glsl_parser.cpp"
break;
case 216:
#line 2425 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      yyval.declarator_list = yystack.l_mark[-1].declarator_list;
      yyval.declarator_list->link.insert_before(& yystack.l_mark[0].declarator_list->link);
   }
#line 5610 "compiler/glsl/glsl_parser.cpp"
break;
case 217:
#line 2433 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      linear_ctx *ctx = state->linalloc;
      ast_fully_specified_type *const type = yystack.l_mark[-2].fully_specified_type;
      type->set_location(yystack.p_mark[-2]);

      if (state->has_bindless()) {
         ast_type_qualifier input_layout_mask;

         /* Allow to declare qualifiers for images. */
         input_layout_mask.flags.i = 0;
         input_layout_mask.flags.q.coherent = 1;
         input_layout_mask.flags.q._volatile = 1;
         input_layout_mask.flags.q.restrict_flag = 1;
         input_layout_mask.flags.q.read_only = 1;
         input_layout_mask.flags.q.write_only = 1;
         input_layout_mask.flags.q.explicit_image_format = 1;

         if ((type->qualifier.flags.i & ~input_layout_mask.flags.i) != 0) {
            _mesa_glsl_error(&yystack.p_mark[-2], state,
                             "only precision and image qualifiers may be "
                             "applied to structure members");
         }
      } else {
         if (type->qualifier.flags.i != 0)
            _mesa_glsl_error(&yystack.p_mark[-2], state,
                             "only precision qualifiers may be applied to "
                             "structure members");
      }

      yyval.declarator_list = new(ctx) ast_declarator_list(type);
      yyval.declarator_list->set_location(yystack.p_mark[-1]);

      yyval.declarator_list->declarations.push_degenerate_list_at_head(& yystack.l_mark[-1].declaration->link);
   }
#line 5648 "compiler/glsl/glsl_parser.cpp"
break;
case 218:
#line 2471 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      yyval.declaration = yystack.l_mark[0].declaration;
      yystack.l_mark[0].declaration->link.self_link();
   }
#line 5656 "compiler/glsl/glsl_parser.cpp"
break;
case 219:
#line 2476 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      yyval.declaration = yystack.l_mark[-2].declaration;
      yyval.declaration->link.insert_before(& yystack.l_mark[0].declaration->link);
   }
#line 5664 "compiler/glsl/glsl_parser.cpp"
break;
case 220:
#line 2484 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      linear_ctx *ctx = state->linalloc;
      yyval.declaration = new(ctx) ast_declaration(yystack.l_mark[0].identifier, NULL, NULL);
      yyval.declaration->set_location(yystack.p_mark[0]);
   }
#line 5673 "compiler/glsl/glsl_parser.cpp"
break;
case 221:
#line 2490 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      linear_ctx *ctx = state->linalloc;
      yyval.declaration = new(ctx) ast_declaration(yystack.l_mark[-1].identifier, yystack.l_mark[0].array_specifier, NULL);
      yyval.declaration->set_location_range(yystack.p_mark[-1], yystack.p_mark[0]);
   }
#line 5682 "compiler/glsl/glsl_parser.cpp"
break;
case 223:
#line 2500 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      yyval.expression = yystack.l_mark[-1].expression;
   }
#line 5689 "compiler/glsl/glsl_parser.cpp"
break;
case 224:
#line 2504 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      yyval.expression = yystack.l_mark[-2].expression;
   }
#line 5696 "compiler/glsl/glsl_parser.cpp"
break;
case 225:
#line 2511 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      linear_ctx *ctx = state->linalloc;
      yyval.expression = new(ctx) ast_aggregate_initializer();
      yyval.expression->set_location(yystack.p_mark[0]);
      yyval.expression->expressions.push_tail(& yystack.l_mark[0].expression->link);
   }
#line 5706 "compiler/glsl/glsl_parser.cpp"
break;
case 226:
#line 2518 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      yystack.l_mark[-2].expression->expressions.push_tail(& yystack.l_mark[0].expression->link);
   }
#line 5713 "compiler/glsl/glsl_parser.cpp"
break;
case 228:
#line 2530 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{ yyval.node = (ast_node *) yystack.l_mark[0].compound_statement; }
#line 5718 "compiler/glsl/glsl_parser.cpp"
break;
case 237:
#line 2546 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      linear_ctx *ctx = state->linalloc;
      yyval.compound_statement = new(ctx) ast_compound_statement(true, NULL);
      yyval.compound_statement->set_location_range(yystack.p_mark[-1], yystack.p_mark[0]);
   }
#line 5727 "compiler/glsl/glsl_parser.cpp"
break;
case 238:
#line 2552 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      state->symbols->push_scope();
   }
#line 5734 "compiler/glsl/glsl_parser.cpp"
break;
case 239:
#line 2556 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      linear_ctx *ctx = state->linalloc;
      yyval.compound_statement = new(ctx) ast_compound_statement(true, yystack.l_mark[-1].node);
      yyval.compound_statement->set_location_range(yystack.p_mark[-3], yystack.p_mark[0]);
      state->symbols->pop_scope();
   }
#line 5744 "compiler/glsl/glsl_parser.cpp"
break;
case 240:
#line 2565 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{ yyval.node = (ast_node *) yystack.l_mark[0].compound_statement; }
#line 5749 "compiler/glsl/glsl_parser.cpp"
break;
case 242:
#line 2571 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      linear_ctx *ctx = state->linalloc;
      yyval.compound_statement = new(ctx) ast_compound_statement(false, NULL);
      yyval.compound_statement->set_location_range(yystack.p_mark[-1], yystack.p_mark[0]);
   }
#line 5758 "compiler/glsl/glsl_parser.cpp"
break;
case 243:
#line 2577 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      linear_ctx *ctx = state->linalloc;
      yyval.compound_statement = new(ctx) ast_compound_statement(false, yystack.l_mark[-1].node);
      yyval.compound_statement->set_location_range(yystack.p_mark[-2], yystack.p_mark[0]);
   }
#line 5767 "compiler/glsl/glsl_parser.cpp"
break;
case 244:
#line 2586 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      if (yystack.l_mark[0].node == NULL) {
         _mesa_glsl_error(& yystack.p_mark[0], state, "<nil> statement");
         assert(yystack.l_mark[0].node != NULL);
      }

      yyval.node = yystack.l_mark[0].node;
      yyval.node->link.self_link();
   }
#line 5780 "compiler/glsl/glsl_parser.cpp"
break;
case 245:
#line 2596 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      if (yystack.l_mark[0].node == NULL) {
         _mesa_glsl_error(& yystack.p_mark[0], state, "<nil> statement");
         assert(yystack.l_mark[0].node != NULL);
      }
      yyval.node = yystack.l_mark[-1].node;
      yyval.node->link.insert_before(& yystack.l_mark[0].node->link);
   }
#line 5792 "compiler/glsl/glsl_parser.cpp"
break;
case 246:
#line 2605 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      if (!state->allow_extension_directive_midshader) {
         _mesa_glsl_error(& yystack.p_mark[-1], state,
                          "#extension directive is not allowed "
                          "in the middle of a shader");
         YYERROR;
      }
   }
#line 5804 "compiler/glsl/glsl_parser.cpp"
break;
case 247:
#line 2617 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      linear_ctx *ctx = state->linalloc;
      yyval.node = new(ctx) ast_expression_statement(NULL);
      yyval.node->set_location(yystack.p_mark[0]);
   }
#line 5813 "compiler/glsl/glsl_parser.cpp"
break;
case 248:
#line 2623 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      linear_ctx *ctx = state->linalloc;
      yyval.node = new(ctx) ast_expression_statement(yystack.l_mark[-1].expression);
      yyval.node->set_location(yystack.p_mark[-1]);
   }
#line 5822 "compiler/glsl/glsl_parser.cpp"
break;
case 249:
#line 2632 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      yyval.node = new(state->linalloc) ast_selection_statement(yystack.l_mark[-2].expression, yystack.l_mark[0].selection_rest_statement.then_statement,
                                                        yystack.l_mark[0].selection_rest_statement.else_statement);
      yyval.node->set_location_range(yystack.p_mark[-4], yystack.p_mark[0]);
   }
#line 5831 "compiler/glsl/glsl_parser.cpp"
break;
case 250:
#line 2641 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      yyval.selection_rest_statement.then_statement = yystack.l_mark[-2].node;
      yyval.selection_rest_statement.else_statement = yystack.l_mark[0].node;
   }
#line 5839 "compiler/glsl/glsl_parser.cpp"
break;
case 251:
#line 2646 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      yyval.selection_rest_statement.then_statement = yystack.l_mark[0].node;
      yyval.selection_rest_statement.else_statement = NULL;
   }
#line 5847 "compiler/glsl/glsl_parser.cpp"
break;
case 252:
#line 2654 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      yyval.node = (ast_node *) yystack.l_mark[0].expression;
   }
#line 5854 "compiler/glsl/glsl_parser.cpp"
break;
case 253:
#line 2658 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      linear_ctx *ctx = state->linalloc;
      ast_declaration *decl = new(ctx) ast_declaration(yystack.l_mark[-2].identifier, NULL, yystack.l_mark[0].expression);
      ast_declarator_list *declarator = new(ctx) ast_declarator_list(yystack.l_mark[-3].fully_specified_type);
      decl->set_location_range(yystack.p_mark[-2], yystack.p_mark[0]);
      declarator->set_location(yystack.p_mark[-3]);

      declarator->declarations.push_tail(&decl->link);
      yyval.node = declarator;
   }
#line 5868 "compiler/glsl/glsl_parser.cpp"
break;
case 254:
#line 2676 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      yyval.node = new(state->linalloc) ast_switch_statement(yystack.l_mark[-2].expression, yystack.l_mark[0].switch_body);
      yyval.node->set_location_range(yystack.p_mark[-4], yystack.p_mark[0]);
   }
#line 5876 "compiler/glsl/glsl_parser.cpp"
break;
case 255:
#line 2684 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      yyval.switch_body = new(state->linalloc) ast_switch_body(NULL);
      yyval.switch_body->set_location_range(yystack.p_mark[-1], yystack.p_mark[0]);
   }
#line 5884 "compiler/glsl/glsl_parser.cpp"
break;
case 256:
#line 2689 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      yyval.switch_body = new(state->linalloc) ast_switch_body(yystack.l_mark[-1].case_statement_list);
      yyval.switch_body->set_location_range(yystack.p_mark[-2], yystack.p_mark[0]);
   }
#line 5892 "compiler/glsl/glsl_parser.cpp"
break;
case 257:
#line 2697 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      yyval.case_label = new(state->linalloc) ast_case_label(yystack.l_mark[-1].expression);
      yyval.case_label->set_location(yystack.p_mark[-1]);
   }
#line 5900 "compiler/glsl/glsl_parser.cpp"
break;
case 258:
#line 2702 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      yyval.case_label = new(state->linalloc) ast_case_label(NULL);
      yyval.case_label->set_location(yystack.p_mark[0]);
   }
#line 5908 "compiler/glsl/glsl_parser.cpp"
break;
case 259:
#line 2710 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      ast_case_label_list *labels = new(state->linalloc) ast_case_label_list();

      labels->labels.push_tail(& yystack.l_mark[0].case_label->link);
      yyval.case_label_list = labels;
      yyval.case_label_list->set_location(yystack.p_mark[0]);
   }
#line 5919 "compiler/glsl/glsl_parser.cpp"
break;
case 260:
#line 2718 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      yyval.case_label_list = yystack.l_mark[-1].case_label_list;
      yyval.case_label_list->labels.push_tail(& yystack.l_mark[0].case_label->link);
   }
#line 5927 "compiler/glsl/glsl_parser.cpp"
break;
case 261:
#line 2726 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      ast_case_statement *stmts = new(state->linalloc) ast_case_statement(yystack.l_mark[-1].case_label_list);
      stmts->set_location(yystack.p_mark[0]);

      stmts->stmts.push_tail(& yystack.l_mark[0].node->link);
      yyval.case_statement = stmts;
   }
#line 5938 "compiler/glsl/glsl_parser.cpp"
break;
case 262:
#line 2734 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      yyval.case_statement = yystack.l_mark[-1].case_statement;
      yyval.case_statement->stmts.push_tail(& yystack.l_mark[0].node->link);
   }
#line 5946 "compiler/glsl/glsl_parser.cpp"
break;
case 263:
#line 2742 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      ast_case_statement_list *cases= new(state->linalloc) ast_case_statement_list();
      cases->set_location(yystack.p_mark[0]);

      cases->cases.push_tail(& yystack.l_mark[0].case_statement->link);
      yyval.case_statement_list = cases;
   }
#line 5957 "compiler/glsl/glsl_parser.cpp"
break;
case 264:
#line 2750 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      yyval.case_statement_list = yystack.l_mark[-1].case_statement_list;
      yyval.case_statement_list->cases.push_tail(& yystack.l_mark[0].case_statement->link);
   }
#line 5965 "compiler/glsl/glsl_parser.cpp"
break;
case 265:
#line 2758 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      linear_ctx *ctx = state->linalloc;
      yyval.node = new(ctx) ast_iteration_statement(ast_iteration_statement::ast_while,
                                            NULL, yystack.l_mark[-2].node, NULL, yystack.l_mark[0].node);
      yyval.node->set_location_range(yystack.p_mark[-4], yystack.p_mark[-1]);
   }
#line 5975 "compiler/glsl/glsl_parser.cpp"
break;
case 266:
#line 2765 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      linear_ctx *ctx = state->linalloc;
      yyval.node = new(ctx) ast_iteration_statement(ast_iteration_statement::ast_do_while,
                                            NULL, yystack.l_mark[-2].expression, NULL, yystack.l_mark[-5].node);
      yyval.node->set_location_range(yystack.p_mark[-6], yystack.p_mark[-1]);
   }
#line 5985 "compiler/glsl/glsl_parser.cpp"
break;
case 267:
#line 2772 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      linear_ctx *ctx = state->linalloc;
      yyval.node = new(ctx) ast_iteration_statement(ast_iteration_statement::ast_for,
                                            yystack.l_mark[-3].node, yystack.l_mark[-2].for_rest_statement.cond, yystack.l_mark[-2].for_rest_statement.rest, yystack.l_mark[0].node);
      yyval.node->set_location_range(yystack.p_mark[-5], yystack.p_mark[0]);
   }
#line 5995 "compiler/glsl/glsl_parser.cpp"
break;
case 271:
#line 2788 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      yyval.node = NULL;
   }
#line 6002 "compiler/glsl/glsl_parser.cpp"
break;
case 272:
#line 2795 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      yyval.for_rest_statement.cond = yystack.l_mark[-1].node;
      yyval.for_rest_statement.rest = NULL;
   }
#line 6010 "compiler/glsl/glsl_parser.cpp"
break;
case 273:
#line 2800 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      yyval.for_rest_statement.cond = yystack.l_mark[-2].node;
      yyval.for_rest_statement.rest = yystack.l_mark[0].expression;
   }
#line 6018 "compiler/glsl/glsl_parser.cpp"
break;
case 274:
#line 2809 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      linear_ctx *ctx = state->linalloc;
      yyval.node = new(ctx) ast_jump_statement(ast_jump_statement::ast_continue, NULL);
      yyval.node->set_location(yystack.p_mark[-1]);
   }
#line 6027 "compiler/glsl/glsl_parser.cpp"
break;
case 275:
#line 2815 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      linear_ctx *ctx = state->linalloc;
      yyval.node = new(ctx) ast_jump_statement(ast_jump_statement::ast_break, NULL);
      yyval.node->set_location(yystack.p_mark[-1]);
   }
#line 6036 "compiler/glsl/glsl_parser.cpp"
break;
case 276:
#line 2821 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      linear_ctx *ctx = state->linalloc;
      yyval.node = new(ctx) ast_jump_statement(ast_jump_statement::ast_return, NULL);
      yyval.node->set_location(yystack.p_mark[-1]);
   }
#line 6045 "compiler/glsl/glsl_parser.cpp"
break;
case 277:
#line 2827 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      linear_ctx *ctx = state->linalloc;
      yyval.node = new(ctx) ast_jump_statement(ast_jump_statement::ast_return, yystack.l_mark[-1].expression);
      yyval.node->set_location_range(yystack.p_mark[-2], yystack.p_mark[-1]);
   }
#line 6054 "compiler/glsl/glsl_parser.cpp"
break;
case 278:
#line 2833 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      linear_ctx *ctx = state->linalloc;
      yyval.node = new(ctx) ast_jump_statement(ast_jump_statement::ast_discard, NULL);
      yyval.node->set_location(yystack.p_mark[-1]);
   }
#line 6063 "compiler/glsl/glsl_parser.cpp"
break;
case 279:
#line 2842 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      linear_ctx *ctx = state->linalloc;
      yyval.node = new(ctx) ast_demote_statement();
      yyval.node->set_location(yystack.p_mark[-1]);
   }
#line 6072 "compiler/glsl/glsl_parser.cpp"
break;
case 280:
#line 2850 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{ yyval.node = yystack.l_mark[0].function_definition; }
#line 6077 "compiler/glsl/glsl_parser.cpp"
break;
case 281:
#line 2851 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{ yyval.node = yystack.l_mark[0].node; }
#line 6082 "compiler/glsl/glsl_parser.cpp"
break;
case 282:
#line 2852 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{ yyval.node = yystack.l_mark[0].node; }
#line 6087 "compiler/glsl/glsl_parser.cpp"
break;
case 283:
#line 2853 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{ yyval.node = yystack.l_mark[0].node; }
#line 6092 "compiler/glsl/glsl_parser.cpp"
break;
case 284:
#line 2854 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{ yyval.node = NULL; }
#line 6097 "compiler/glsl/glsl_parser.cpp"
break;
case 285:
#line 2859 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      linear_ctx *ctx = state->linalloc;
      yyval.function_definition = new(ctx) ast_function_definition();
      yyval.function_definition->set_location_range(yystack.p_mark[-1], yystack.p_mark[0]);
      yyval.function_definition->prototype = yystack.l_mark[-1].function;
      yyval.function_definition->body = yystack.l_mark[0].compound_statement;

      state->symbols->pop_scope();
   }
#line 6110 "compiler/glsl/glsl_parser.cpp"
break;
case 286:
#line 2873 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      yyval.node = yystack.l_mark[0].interface_block;
   }
#line 6117 "compiler/glsl/glsl_parser.cpp"
break;
case 287:
#line 2877 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      ast_interface_block *block = (ast_interface_block *) yystack.l_mark[0].node;

      if (!yystack.l_mark[-1].type_qualifier.merge_qualifier(& yystack.p_mark[-1], state, block->layout, false,
                              block->layout.has_layout())) {
         YYERROR;
      }

      block->layout = yystack.l_mark[-1].type_qualifier;

      yyval.node = block;
   }
#line 6133 "compiler/glsl/glsl_parser.cpp"
break;
case 288:
#line 2890 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      ast_interface_block *block = (ast_interface_block *)yystack.l_mark[0].node;

      if (!block->default_layout.flags.q.buffer) {
            _mesa_glsl_error(& yystack.p_mark[-1], state,
                             "memory qualifiers can only be used in the "
                             "declaration of shader storage blocks");
      }
      if (!yystack.l_mark[-1].type_qualifier.merge_qualifier(& yystack.p_mark[-1], state, block->layout, false)) {
         YYERROR;
      }
      block->layout = yystack.l_mark[-1].type_qualifier;
      yyval.node = block;
   }
#line 6151 "compiler/glsl/glsl_parser.cpp"
break;
case 289:
#line 2908 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      ast_interface_block *const block = yystack.l_mark[-1].interface_block;

      if (yystack.l_mark[-6].type_qualifier.flags.q.uniform) {
         block->default_layout = *state->default_uniform_qualifier;
      } else if (yystack.l_mark[-6].type_qualifier.flags.q.buffer) {
         block->default_layout = *state->default_shader_storage_qualifier;
      }
      block->block_name = yystack.l_mark[-5].identifier;
      block->declarations.push_degenerate_list_at_head(& yystack.l_mark[-3].declarator_list->link);

      _mesa_ast_process_interface_block(& yystack.p_mark[-6], state, block, yystack.l_mark[-6].type_qualifier);

      yyval.interface_block = block;
   }
#line 6170 "compiler/glsl/glsl_parser.cpp"
break;
case 290:
#line 2927 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      memset(& yyval.type_qualifier, 0, sizeof(yyval.type_qualifier));
      yyval.type_qualifier.flags.q.in = 1;
   }
#line 6178 "compiler/glsl/glsl_parser.cpp"
break;
case 291:
#line 2932 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      memset(& yyval.type_qualifier, 0, sizeof(yyval.type_qualifier));
      yyval.type_qualifier.flags.q.out = 1;
   }
#line 6186 "compiler/glsl/glsl_parser.cpp"
break;
case 292:
#line 2937 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      memset(& yyval.type_qualifier, 0, sizeof(yyval.type_qualifier));
      yyval.type_qualifier.flags.q.uniform = 1;
   }
#line 6194 "compiler/glsl/glsl_parser.cpp"
break;
case 293:
#line 2942 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      memset(& yyval.type_qualifier, 0, sizeof(yyval.type_qualifier));
      yyval.type_qualifier.flags.q.buffer = 1;
   }
#line 6202 "compiler/glsl/glsl_parser.cpp"
break;
case 294:
#line 2947 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      if (!yystack.l_mark[-1].type_qualifier.flags.q.patch) {
         _mesa_glsl_error(&yystack.p_mark[-1], state, "invalid interface qualifier");
      }
      if (yystack.l_mark[0].type_qualifier.has_auxiliary_storage()) {
         _mesa_glsl_error(&yystack.p_mark[-1], state, "duplicate patch qualifier");
      }
      yyval.type_qualifier = yystack.l_mark[0].type_qualifier;
      yyval.type_qualifier.flags.q.patch = 1;
   }
#line 6216 "compiler/glsl/glsl_parser.cpp"
break;
case 295:
#line 2961 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      yyval.interface_block = new(state->linalloc) ast_interface_block(NULL, NULL);
   }
#line 6223 "compiler/glsl/glsl_parser.cpp"
break;
case 296:
#line 2965 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      yyval.interface_block = new(state->linalloc) ast_interface_block(yystack.l_mark[0].identifier, NULL);
      yyval.interface_block->set_location(yystack.p_mark[0]);
   }
#line 6231 "compiler/glsl/glsl_parser.cpp"
break;
case 297:
#line 2970 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      yyval.interface_block = new(state->linalloc) ast_interface_block(yystack.l_mark[-1].identifier, yystack.l_mark[0].array_specifier);
      yyval.interface_block->set_location_range(yystack.p_mark[-1], yystack.p_mark[0]);
   }
#line 6239 "compiler/glsl/glsl_parser.cpp"
break;
case 298:
#line 2978 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      yyval.declarator_list = yystack.l_mark[0].declarator_list;
      yystack.l_mark[0].declarator_list->link.self_link();
   }
#line 6247 "compiler/glsl/glsl_parser.cpp"
break;
case 299:
#line 2983 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      yyval.declarator_list = yystack.l_mark[-1].declarator_list;
      yystack.l_mark[0].declarator_list->link.insert_before(& yyval.declarator_list->link);
   }
#line 6255 "compiler/glsl/glsl_parser.cpp"
break;
case 300:
#line 2991 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      linear_ctx *ctx = state->linalloc;
      ast_fully_specified_type *type = yystack.l_mark[-2].fully_specified_type;
      type->set_location(yystack.p_mark[-2]);

      if (type->qualifier.flags.q.attribute) {
         _mesa_glsl_error(& yystack.p_mark[-2], state,
                          "keyword 'attribute' cannot be used with "
                          "interface block member");
      } else if (type->qualifier.flags.q.varying) {
         _mesa_glsl_error(& yystack.p_mark[-2], state,
                          "keyword 'varying' cannot be used with "
                          "interface block member");
      }

      yyval.declarator_list = new(ctx) ast_declarator_list(type);
      yyval.declarator_list->set_location(yystack.p_mark[-1]);

      yyval.declarator_list->declarations.push_degenerate_list_at_head(& yystack.l_mark[-1].declaration->link);
   }
#line 6279 "compiler/glsl/glsl_parser.cpp"
break;
case 301:
#line 3015 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      yyval.type_qualifier = yystack.l_mark[-1].type_qualifier;
      if (!yyval.type_qualifier.merge_qualifier(& yystack.p_mark[-1], state, yystack.l_mark[0].type_qualifier, false, true)) {
         YYERROR;
      }
   }
#line 6289 "compiler/glsl/glsl_parser.cpp"
break;
case 303:
#line 3026 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      yyval.type_qualifier = yystack.l_mark[-1].type_qualifier;
      if (!yyval.type_qualifier.merge_qualifier(& yystack.p_mark[-1], state, yystack.l_mark[0].type_qualifier, false, true)) {
         YYERROR;
      }
   }
#line 6299 "compiler/glsl/glsl_parser.cpp"
break;
case 305:
#line 3037 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      yyval.type_qualifier = yystack.l_mark[-1].type_qualifier;
      if (!yyval.type_qualifier.merge_qualifier(& yystack.p_mark[-1], state, yystack.l_mark[0].type_qualifier, false, true)) {
         YYERROR;
      }
      if (!yyval.type_qualifier.validate_in_qualifier(& yystack.p_mark[-1], state)) {
         YYERROR;
      }
   }
#line 6312 "compiler/glsl/glsl_parser.cpp"
break;
case 306:
#line 3047 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      if (!yystack.l_mark[-2].type_qualifier.validate_in_qualifier(& yystack.p_mark[-2], state)) {
         YYERROR;
      }
   }
#line 6321 "compiler/glsl/glsl_parser.cpp"
break;
case 307:
#line 3056 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      yyval.type_qualifier = yystack.l_mark[-1].type_qualifier;
      if (!yyval.type_qualifier.merge_qualifier(& yystack.p_mark[-1], state, yystack.l_mark[0].type_qualifier, false, true)) {
         YYERROR;
      }
      if (!yyval.type_qualifier.validate_out_qualifier(& yystack.p_mark[-1], state)) {
         YYERROR;
      }
   }
#line 6334 "compiler/glsl/glsl_parser.cpp"
break;
case 308:
#line 3066 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      if (!yystack.l_mark[-2].type_qualifier.validate_out_qualifier(& yystack.p_mark[-2], state)) {
         YYERROR;
      }
   }
#line 6343 "compiler/glsl/glsl_parser.cpp"
break;
case 309:
#line 3075 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      yyval.node = NULL;
      if (!state->default_uniform_qualifier->
             merge_qualifier(& yystack.p_mark[0], state, yystack.l_mark[0].type_qualifier, false)) {
         YYERROR;
      }
      if (!state->default_uniform_qualifier->
             push_to_global(& yystack.p_mark[0], state)) {
         YYERROR;
      }
   }
#line 6358 "compiler/glsl/glsl_parser.cpp"
break;
case 310:
#line 3087 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      yyval.node = NULL;
      if (!state->default_shader_storage_qualifier->
             merge_qualifier(& yystack.p_mark[0], state, yystack.l_mark[0].type_qualifier, false)) {
         YYERROR;
      }
      if (!state->default_shader_storage_qualifier->
             push_to_global(& yystack.p_mark[0], state)) {
         YYERROR;
      }

      /* From the GLSL 4.50 spec, section 4.4.5:
       *
       *     "It is a compile-time error to specify the binding identifier for
       *     the global scope or for block member declarations."
       */
      if (state->default_shader_storage_qualifier->flags.q.explicit_binding) {
         _mesa_glsl_error(& yystack.p_mark[0], state,
                          "binding qualifier cannot be set for default layout");
      }
   }
#line 6383 "compiler/glsl/glsl_parser.cpp"
break;
case 311:
#line 3109 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      yyval.node = NULL;
      if (!yystack.l_mark[0].type_qualifier.merge_into_in_qualifier(& yystack.p_mark[0], state, yyval.node)) {
         YYERROR;
      }
      if (!state->in_qualifier->push_to_global(& yystack.p_mark[0], state)) {
         YYERROR;
      }
   }
#line 6396 "compiler/glsl/glsl_parser.cpp"
break;
case 312:
#line 3119 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      yyval.node = NULL;
      if (!yystack.l_mark[0].type_qualifier.merge_into_out_qualifier(& yystack.p_mark[0], state, yyval.node)) {
         YYERROR;
      }
      if (!state->out_qualifier->push_to_global(& yystack.p_mark[0], state)) {
         YYERROR;
      }

      (void)yynerrs;
   }
#line 6411 "compiler/glsl/glsl_parser.cpp"
break;
#line 6413 "compiler/glsl/glsl_parser.cpp"
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
