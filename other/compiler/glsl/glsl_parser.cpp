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
#define PIXEL_LOCAL 283
#define PIXEL_LOCAL_IN 284
#define PIXEL_LOCAL_OUT 285
#define IMAGE1DSHADOW 286
#define IMAGE2DSHADOW 287
#define IMAGE1DARRAYSHADOW 288
#define IMAGE2DARRAYSHADOW 289
#define COHERENT 290
#define VOLATILE 291
#define RESTRICT 292
#define READONLY 293
#define WRITEONLY 294
#define SHARED 295
#define TASKPAYLOAD 296
#define PERPRIMITIVE 297
#define STRUCT 298
#define VOID_TOK 299
#define WHILE 300
#define IDENTIFIER 301
#define TYPE_IDENTIFIER 302
#define NEW_IDENTIFIER 303
#define FLOATCONSTANT 304
#define FLOAT16CONSTANT 305
#define DOUBLECONSTANT 306
#define INTCONSTANT 307
#define UINTCONSTANT 308
#define BOOLCONSTANT 309
#define INT64CONSTANT 310
#define UINT64CONSTANT 311
#define FIELD_SELECTION 312
#define LEFT_OP 313
#define RIGHT_OP 314
#define INC_OP 315
#define DEC_OP 316
#define LE_OP 317
#define GE_OP 318
#define EQ_OP 319
#define NE_OP 320
#define AND_OP 321
#define OR_OP 322
#define XOR_OP 323
#define MUL_ASSIGN 324
#define DIV_ASSIGN 325
#define ADD_ASSIGN 326
#define MOD_ASSIGN 327
#define LEFT_ASSIGN 328
#define RIGHT_ASSIGN 329
#define AND_ASSIGN 330
#define XOR_ASSIGN 331
#define OR_ASSIGN 332
#define SUB_ASSIGN 333
#define INVARIANT 334
#define PRECISE 335
#define LOWP 336
#define MEDIUMP 337
#define HIGHP 338
#define SUPERP 339
#define PRECISION 340
#define VERSION_TOK 341
#define EXTENSION 342
#define LINE 343
#define COLON 344
#define EOL 345
#define INTERFACE_TOK 346
#define OUTPUT 347
#define PRAGMA_DEBUG_ON 348
#define PRAGMA_DEBUG_OFF 349
#define PRAGMA_OPTIMIZE_ON 350
#define PRAGMA_OPTIMIZE_OFF 351
#define PRAGMA_WARNING_ON 352
#define PRAGMA_WARNING_OFF 353
#define PRAGMA_INVARIANT_ALL 354
#define LAYOUT_TOK 355
#define DOT_TOK 356
#define ASM 357
#define CLASS 358
#define UNION 359
#define ENUM 360
#define TYPEDEF 361
#define TEMPLATE 362
#define THIS 363
#define PACKED_TOK 364
#define GOTO 365
#define INLINE_TOK 366
#define NOINLINE 367
#define PUBLIC_TOK 368
#define STATIC 369
#define EXTERN 370
#define EXTERNAL 371
#define LONG_TOK 372
#define SHORT_TOK 373
#define HALF 374
#define FIXED_TOK 375
#define UNSIGNED 376
#define INPUT_TOK 377
#define HVEC2 378
#define HVEC3 379
#define HVEC4 380
#define FVEC2 381
#define FVEC3 382
#define FVEC4 383
#define SAMPLER3DRECT 384
#define SIZEOF 385
#define CAST 386
#define NAMESPACE 387
#define USING 388
#define RESOURCE 389
#define PATCH 390
#define SUBROUTINE 391
#define ERROR_TOK 392
#define COMMON 393
#define PARTITION 394
#define ACTIVE 395
#define FILTER 396
#define ROW_MAJOR 397
#define THEN 398
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
    9,    9,    9,    9,   10,   10,   10,   10,   10,   10,
   10,   10,   10,   10,   10,   10,   10,   16,   16,   16,
   16,   16,   22,   22,   22,   22,   20,   20,   21,   21,
   21,   23,   23,   23,    7,    7,    7,   79,   79,   80,
   80,   81,   83,   83,   82,   82,   71,   71,   71,   72,
   72,   74,    4,    4,    6,    6,    6,    6,    6,    6,
    6,   36,  109,   36,   37,   37,   35,   35,    5,    5,
    5,   38,   38,   86,   87,   87,   95,   95,   88,   89,
   89,   91,   91,   90,   90,   92,   92,   93,   93,   94,
   94,   94,   97,   97,   96,   96,   98,   98,   75,   75,
   75,   75,   75,   76,   67,   67,   67,   67,   67,   34,
   77,   77,   77,   78,   19,   19,   19,   19,   19,   19,
   19,   19,    2,    2,    2,   84,   84,   85,  100,  100,
  101,  101,  102,  102,  103,  103,   99,   99,   99,   99,
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
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    2,    3,    3,    4,    1,    2,    1,    1,
    1,    1,    1,    2,    1,    1,    1,    5,    4,    1,
    2,    3,    1,    3,    1,    2,    1,    3,    4,    1,
    3,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    2,    0,    4,    1,    1,    2,    3,    1,    2,
    2,    1,    2,    5,    3,    1,    1,    4,    5,    2,
    3,    3,    2,    1,    2,    2,    2,    1,    2,    5,
    7,    6,    1,    1,    1,    0,    2,    3,    2,    2,
    2,    3,    2,    2,    1,    1,    1,    1,    1,    2,
    1,    2,    2,    7,    1,    1,    1,    1,    1,    1,
    1,    2,    0,    1,    2,    1,    2,    3,    2,    3,
    2,    3,    2,    3,    2,    3,    1,    1,    1,    1,
};
static const YYINT _mesa_glsl_defred[] = {                0,
    0,    0,   13,    0,    0,   15,   16,   17,    4,    0,
    0,    0,   14,    5,    0,  186,  185,  213,    0,  181,
    0,    0,  190,    0,  187,  182,  162,  161,  160,    0,
    0,    0,  198,  199,  200,  201,  202,  193,  194,  184,
    0,  212,  211,    0,    0,  217,  216,  215,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  183,    0,
  289,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  145,    0,  209,    0,    0,    0,    0,    0,  285,   19,
  287,    0,  133,  286,  111,  291,  210,  288,  317,  318,
  319,  320,    0,    0,    0,    0,  192,  188,  189,  191,
  195,  196,  197,   22,   23,    0,    0,  143,  173,    0,
    0,    0,  144,  172,    0,    6,    7,    8,    9,   11,
   12,   10,    0,  214,    0,  179,  146,  177,  302,  178,
  174,    0,    0,    0,    0,  175,  292,  309,  311,  313,
  315,  180,    0,  293,  176,    0,    0,    0,    0,    0,
    0,    0,  108,    0,  290,    0,  129,  130,  131,    0,
    0,    0,  115,    0,    0,    0,  112,    0,  109,   20,
   21,    0,    0,    0,  220,    0,    0,  155,  154,  153,
    0,    0,  148,  152,  158,    0,  312,  314,  316,  310,
    0,   30,   29,   31,   25,   26,   32,   27,   28,    0,
    0,    0,  203,   56,   57,   58,   59,   24,   50,   34,
  107,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,   60,    0,    0,    0,    0,    0,   42,   41,
   36,    0,    0,    0,    0,    0,  117,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  252,    0,  247,
  249,    0,  234,    0,    0,  233,  236,    0,  105,   92,
    0,  232,  235,  240,  241,  237,  238,  239,  124,  125,
  127,  128,    0,    0,  121,  122,  126,  116,    0,   18,
    0,  223,    0,  219,  221,    0,  110,    0,  147,    0,
  157,    0,    0,    0,    0,   53,   54,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  204,   38,
   39,    0,    0,   43,    0,   44,    0,   47,   55,   49,
  205,    0,    0,  227,  142,    0,  280,  279,  246,  245,
    0,    0,    0,  284,  283,  281,    0,    0,    0,  242,
    0,  248,  250,  251,    0,  253,   95,   96,   98,   97,
  100,  101,  102,  103,  104,   99,   94,    0,    0,    0,
    0,    0,    0,    0,  222,  218,  151,  149,  159,    0,
    0,  307,   33,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
   61,   62,   63,   37,    0,    0,   48,  206,  230,    0,
  141,    0,  273,  274,    0,    0,  282,    0,    0,    0,
    0,    0,  106,   93,  119,    0,  137,    0,  224,  308,
    0,    0,    0,   35,    0,  228,    0,  275,    0,    0,
    0,    0,    0,    0,  244,  136,    0,  294,   91,  229,
  231,    0,    0,    0,    0,  254,    0,  259,    0,  270,
    0,    0,  272,    0,    0,    0,  260,    0,  264,    0,
    0,  258,  271,  255,    0,  263,  266,  265,  267,  261,
    0,  262,
};
#if defined(YYDESTRUCT_CALL) || defined(YYSTYPE_TOSTRING)
static const YYINT _mesa_glsl_stos[] = {                  0,
  341,  400,  504,  307,  505,  301,  302,  303,  345,  401,
  342,  507,  508,  345,  401,  257,  258,  259,  261,  273,
  274,  275,  276,  277,  278,  279,  280,  281,  282,  283,
  284,  285,  290,  291,  292,  293,  294,  295,  296,  297,
  298,  299,  302,  334,  335,  336,  337,  338,  340,  348,
  349,  350,  351,  352,  353,  354,  355,  376,  390,  391,
   59,  407,  408,  409,  410,  411,  412,  416,  417,  419,
  420,  421,  423,  424,  425,  426,  427,  428,  434,  467,
  468,  469,  470,  473,  477,  478,  479,  499,  500,  501,
  502,  503,  506,  344,  123,  401,  261,  274,  275,  277,
  283,  284,  285,  301,  303,  334,  335,  403,  408,  409,
  412,  416,  403,  408,  407,  345,  345,  345,  345,  345,
  345,  345,   40,  259,   40,  408,  420,  408,  419,  408,
  408,  261,  274,  275,  277,  408,  477,  500,  501,  502,
  503,  408,  412,  477,  408,  303,   91,  422,  301,  303,
  401,  403,   59,  123,  435,  258,  274,  275,  276,  335,
  407,  416,  430,  431,  432,   44,   41,   44,   59,  467,
  508,  401,  424,  480,  481,  123,  420,  295,  364,  397,
  401,  413,  414,  415,  401,  418,   59,   59,   59,   59,
  123,  304,  305,  306,  307,  308,  309,  310,  311,  315,
  316,   40,   93,   43,   45,   33,  126,  403,  420,  440,
  442,  443,  444,  445,  446,  447,  448,  449,  450,  451,
  452,  453,  454,  455,  457,  458,  459,  460,  461,  462,
  463,  465,  466,   91,   61,  422,   40,  260,  262,  263,
  265,  266,  267,  268,  269,  270,  300,   59,  123,  125,
  404,  405,  406,  420,  425,  436,  438,  439,  441,  442,
  454,  473,  474,  475,  476,  486,  488,  494,  431,  431,
  431,  431,  412,  420,  429,  433,  431,  430,  401,  345,
  401,  482,  483,  125,  481,  480,   59,   61,   41,   44,
   41,   44,  424,  484,  485,  454,  454,  439,  322,   63,
  323,  321,  124,   94,   38,  319,  320,  317,  318,   60,
   62,  313,  314,   43,   45,   42,   47,   37,   93,  315,
  316,  356,   91,   41,   44,   41,  299,  441,  454,   40,
   93,  455,  123,  441,  471,   61,   59,   59,  406,  435,
  437,   40,   40,   59,   59,   59,  439,   40,   40,  125,
  509,  125,  404,  508,   44,   59,  324,  325,  326,  327,
  328,  329,  330,  331,  332,  333,   61,  464,  420,  401,
   61,  422,  422,   44,   59,  125,  455,  414,  401,  483,
  125,  484,   41,  444,  439,  445,  446,  447,  448,  449,
  450,  450,  451,  451,  451,  451,  452,  452,  453,  453,
  454,  454,  454,  312,  439,  456,  441,   93,  471,  472,
  471,  300,  438,  474,  497,  439,   59,  439,  424,  439,
  495,  405,  441,  441,  401,  422,  471,   61,  482,   59,
  303,  402,   58,   93,   44,  125,   40,  495,  496,  498,
   41,   41,  401,   41,  125,  471,  422,   59,  441,  125,
  471,  439,   59,   41,  404,  487,  123,  489,   61,  437,
   41,  439,  437,  264,  271,  272,  125,  490,  491,  492,
  493,  471,   59,  404,  439,   58,  404,  491,  404,  125,
  492,   58,
};
#endif /* YYDESTRUCT_CALL || YYSTYPE_TOSTRING */
static const YYINT _mesa_glsl_dgoto[] = {                 2,
  281,  432,  208,  251,  252,  253,   62,   63,   64,   65,
   66,  111,  182,  183,  184,  112,   69,  186,   70,  209,
   72,  148,   73,   74,  255,   76,   77,   78,  275,  163,
  164,  165,  276,   79,  340,  256,  341,  257,  258,  210,
  259,  260,  212,  213,  214,  215,  216,  217,  218,  219,
  220,  221,  222,  261,  224,  406,  225,  226,  227,  228,
  229,  230,  231,  368,  232,  233,   80,   81,   82,   83,
  335,  410,  262,  263,  264,  265,   85,   86,   87,  174,
  175,  282,  283,  294,  295,  266,  456,  267,  458,  468,
  469,  470,  471,  268,  421,  439,  415,  440,   88,   89,
   90,   91,   92,    3,    5,   93,   12,  354,  351,
};
static const YYINT _mesa_glsl_sindex[] = {             -333,
 -283,    0,    0, -176, -311,    0,    0,    0,    0, -302,
   69, 2334,    0,    0, -238,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  -95,    0,    0, 3850, 3850,    0,    0,    0,  152, -204,
 -198, -172, -164, -142, -123, -119,  220,    3,    0,  242,
    0, 3916,   64, 3985, 3916, 3916, 4051, 3985, 3916,  -16,
    0,  203,    0,  112,   10,  870,  262,  272,    0,    0,
    0,   87,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0, 2078,   69, 3715,  201,    0,    0,    0,    0,
    0,    0,    0,    0,    0, 3916, 3916,    0,    0, 3916,
 3916, 3916,    0,    0,   64,    0,    0,    0,    0,    0,
    0,    0,  422,    0,   69,    0,    0,    0,    0,    0,
    0,  263,  277,  279,  286,    0,    0,    0,    0,    0,
    0,    0, 3985,    0,    0,  229, 1852,  284,    0,    0,
  -59,  351,    0,  963,    0,  870,    0,    0,    0,  870,
  870,  870,    0,  430,  870,  870,    0,   69,    0,    0,
    0,   53,   69, 3000,    0, 3715,  342,    0,    0,    0,
  360,  131,    0,    0,    0,  151,    0,    0,    0,    0,
 3715,    0,    0,    0,    0,    0,    0,    0,    0, 1956,
 1956, 1956,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  -50,  103,  123,  311,  366,  413,  -64,  -48,  125,
  205,   97,    0,  373,  -80,  173,  427, 2018,    0,    0,
    0, 1956,  441, 1872, 1934,  -43,    0,  435,  439, 1126,
  466,  477,  480,  482, 1893,  502,  527,    0,  440,    0,
    0,  357,    0,    0,  511,    0,    0,  104,    0,    0,
   56,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,   64,   69,    0,    0,    0,    0,  -32,    0,
  203,    0,  130,    0,    0, 3175,    0, 1956,    0,  422,
    0,   69,   69,  446, 3715,    0,    0,  190, 1956, 1956,
 1956, 1956, 1956, 1956, 1956, 1956, 1956, 1956, 1956, 1956,
 1956, 1956, 1956, 1956, 1956, 1956, 1956, 1956,    0,    0,
    0,  261, 1956,    0, 1956,    0,    0,    0,    0,    0,
    0,  481, 1934,    0,    0, 1934,    0,    0,    0,    0,
  280, 1573, 1956,    0,    0,    0,  139, 1956, 1733,    0,
 1289,    0,    0,    0, 1956,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0, 1956,   69,  203,
 1934,   62,  284,   69,    0,    0,    0,    0,    0,  140,
  281,    0,    0,  103,   -3,  123,  311,  366,  413,  -64,
  -48,  -48,  125,  125,  125,  125,  205,  205,   97,   97,
    0,    0,    0,    0,  531,  486,    0,    0,    0,  -38,
    0,  545,    0,    0, 1733,  251,    0,  303,   69,  531,
  551,  637,    0,    0,    0,  284,    0, 1934,    0,    0,
  203,  537, 1956,    0,  738,    0, 1956,    0,  542,  561,
 1289,  463,  546, 1126,    0,    0,  284,    0,    0,    0,
    0,  323, 1956, 1126,  346,    0,  -62,    0, 1934,    0,
  552,  531,    0, 1289, 1956,  554,    0,  800,    0, 1289,
  -18,    0,    0,    0,   34,    0,    0,    0,    0,    0,
 1289,    0,
};
static const YYINT _mesa_glsl_rindex[] = {             2214,
    0,    0,    0,    0, 2455,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0, 3241,    0,
 3310, 3376,    0, 3445,    0,    0,    0,    0,    0, 3511,
 3580, 3646,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,  110,  307,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0, 3781,
    0,  516,    0,  525,  532,  549,  573,  578,  583,    0,
    0,  160,    0,  199,    0,  -34,  572,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  621,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  110,  307,    0,    0,  525,
  573,  578,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0, 3241, 3310, 3376, 3445,    0,    0,    0,    0,    0,
    0,    0,  573,    0,    0,    0,    0,  198,  333,  750,
  222,    0,    0,    0,    0,  452,    0,    0,    0,  452,
  452,  452,    0,    0,  452,  452,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  352,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  302,   77, 1598,  -21,  -14,  663,  186,   -5, 2923,
   36,  643,    0,    0, 2597,    0,    0,  604,    0,    0,
    0,    0,    0,    0,    0,  246,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0, 1452,    0,
    0,    0,    0,   26,    0,    0,    0,    0,    0,    0,
 2718,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,  379,    0,    0,    0,    0,  275,    0,
  276,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  521,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  -15,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  384,
    0,  282,  289,    0,    0,    0,    0,    0,    0,    0,
  610,    0,    0,  378,    0, 2021,  174, 1578,  711,  672,
  127,  153, 2932, 3022, 3045, 3104, 2838, 2895, 2756, 2810,
    0,    0,    0,    0,  581,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  612,    0,    0,    0,    0,  -37,
    0,    0,    0,    0,    0,  390,    0,    0,    0,    0,
  616,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  617,    0,    0,    0,
    0,    0,  638,    0,  253,    0,    0,    0,    0,    0,
    0,  644,    0,    0,    0,    0,    0,    0,    0,   13,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
   32,    0,
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
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,
};
#endif
static const YYINT _mesa_glsl_gindex[] = {                0,
   -1,    0,  114,  331,  327, -231,  416, 2029,    2,    0,
    0,   23,    0,  400,    0,  -11,    0,    0,  634,  -12,
    0,  -99,    0,  -90,    7,    0,    0,    0,    0,  543,
  438,    0,    0,    0,  633,    0, -394,  372, 2966,    0,
 2112, -132,    0,  419,  414,  417,  424,  434,  415,  148,
   96,  166,  170, 1507, -213,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  641,    0,    0,    0,
  169,    0,   22,  397,    0,    0,   -6,    0,    0,  564,
 -158,  367,  449,  448,    0,    0,    0,    0,    0,    0,
  278,  273,    0,    0,  330,    0,    0,    0,    0,  682,
  691,  692,  694,    0,    0,    0,    0,   12,    0,
};
#define YYTABLESIZE 4442
static const YYINT _mesa_glsl_table[] = {                71,
   68,  235,   10,  257,  173,  435,  113,    1,  339,   15,
  323,  310,  300,  311,  211,  285,   13,  336,   75,   84,
  332,  257,   84,    4,  212,   45,   82,   95,  371,   82,
   11,  147,   75,   84,   67,   75,   84,   84,   75,   96,
  355,   84,   14,   82,   82,  110,  110,  234,   82,  460,
  127,  236,   75,   75,  433,   68,   68,   75,  147,  463,
  137,  144,  467,  110,  162,   50,  110,  110,  153,  145,
  110,   84,  151,   67,  377,  212,   67,  355,   82,   67,
   71,   68,   71,  173,  145,  173,  436,   75,   75,   67,
  143,  482,  172,   67,   67,   67,  110,   67,   67,   75,
  293,  211,  177,   84,  171,   94,  480,  110,  110,   82,
   82,  110,  110,  110,   84,   67,  367,   88,   75,   75,
   88,  181,  428,  185,    6,    7,    8,  285,   67,   67,
  168,   68,  154,  318,   88,   88,  137,  268,  316,   88,
  116,  254,   68,  317,  162,  169,  117,  355,  162,  162,
  162,  274,  234,  162,  162,  211,  269,  108,  113,   67,
   67,   71,  356,   71,   76,  143,  279,   76,    9,   88,
   76,  289,  118,  374,  290,  110,  143,  110,   71,  372,
  119,  373,  355,  374,   76,   76,  273,  152,  375,   76,
   77,  291,  110,   77,  292,  173,   77,  417,  430,  207,
  207,   88,  120,  207,  293,    6,    7,    8,  465,  466,
   77,   77,  339,  324,   85,   77,  325,   85,  207,   76,
   76,  121,  339,   78,  123,  122,   78,  254,   68,   78,
  383,   85,   85,  355,  320,  321,   85,  208,  208,  254,
   68,  208,  138,   78,   78,   77,   77,  314,   78,  315,
   76,   76,  465,  466,  306,  307,  208,  138,  419,  123,
  369,  124,  143,  123,  123,  139,   85,  123,  308,  309,
  426,  299,  370,   71,  143,  322,   77,   77,   78,   78,
  139,  125,   71,  268,  268,  256,  146,  110,  181,  140,
  379,  441,  256,  147,  355,  256,  110,  256,   85,   84,
   84,   84,  269,  269,  140,  166,   82,   82,   82,   78,
   78,  256,  167,   75,   75,   75,   75,   75,  134,  225,
  123,  187,   18,  176,  419,  135,  145,  145,  145,  254,
   68,  447,  226,  134,  225,  188,  254,  189,  254,   68,
  135,  123,   90,  442,  190,   90,  355,  226,   67,   67,
  110,  191,   67,   67,   67,   67,   67,   67,   67,   90,
   90,   41,   42,  461,  143,   43,  355,  425,  163,    6,
    7,    8,   22,  143,  234,  256,   15,  256,  256,  357,
  358,  359,  360,  361,  362,  363,  364,  365,  366,  206,
  237,   15,  150,   15,   90,  150,  202,  280,   88,  204,
  287,  205,  254,  393,  394,  395,  396,  163,  163,  254,
   68,  163,  149,    7,  150,  248,  110,  443,   89,  132,
  288,   89,  132,   15,  118,  301,   90,  118,  254,   68,
  120,  254,   68,  120,  303,   89,   89,  312,  313,   58,
   89,  254,   68,  302,  143,   76,   76,   76,   76,   76,
  305,  254,   68,  391,  392,  254,   68,  254,   68,  304,
  207,  207,  207,  143,  115,  319,  143,  326,  254,   68,
   89,   77,   77,   77,   77,   77,  143,  397,  398,  249,
  330,  352,  207,  399,  400,  163,  143,   46,   47,   48,
  143,  161,  143,  337,   85,   85,   85,  338,  208,  208,
  208,  409,   89,  143,  411,  342,   78,   78,   78,  256,
  256,  256,  256,  256,  256,  256,  343,  256,  256,  256,
  256,  256,  256,  256,  256,  256,  256,  256,  256,  256,
  256,  256,  256,  256,  256,  256,  256,  256,  344,  427,
  345,  348,  256,  256,  256,  256,  256,  256,  256,  256,
  256,  256,  256,  256,  256,  256,  256,  256,  256,  256,
  256,  256,  256,  256,  350,  164,  349,  256,  256,  153,
  381,  161,  404,  408,  355,  161,  161,  161,  434,  412,
  161,  161,  353,  431,  437,  457,  256,  256,  256,  256,
  256,  444,  256,  269,  256,  448,  446,  270,  271,  272,
  453,  454,  277,  451,  164,  164,  459,  256,  164,  464,
  473,  476,  114,   16,   17,   18,  238,   19,  239,  240,
    2,  241,  242,  243,  244,  245,  246,  472,  256,   20,
   21,   22,   23,   24,   25,   26,   27,   28,   29,   30,
   31,   32,  256,  256,   46,  306,   33,   34,   35,   36,
   37,   38,   39,   40,   41,   42,  247,  104,   43,  105,
  192,  193,  194,  195,  196,  197,  198,  199,  303,  206,
  276,  200,  201,   40,  304,  305,  202,  422,  277,  204,
   64,  205,  164,   64,  278,   64,   64,   64,   18,  378,
   44,   45,   46,   47,   48,  248,   49,  129,   11,   89,
   64,   64,   64,   80,   64,   64,   80,  155,  278,   79,
  123,   57,   79,  413,  386,   79,  178,  384,  387,  390,
   80,   80,    6,    7,    8,   80,  388,   41,   42,   79,
   79,   43,   58,  170,   79,   64,   64,  389,  414,  286,
  429,  380,  382,  481,  438,  478,   59,   60,  138,  123,
  123,   81,  353,  123,   81,   80,   80,  139,  140,  249,
  141,  445,  207,    0,   79,   79,   64,   64,   81,   81,
  206,  455,    0,   81,  171,    0,    0,  202,    0,    0,
  204,    0,  205,  165,   57,  179,   80,   80,    0,   23,
  166,    0,    0,   17,  474,   79,   79,    0,  477,    0,
  479,    0,    0,   81,   81,   58,  123,  167,   17,    0,
   17,  479,    0,  171,  171,    0,    0,  171,  180,    0,
    0,    0,  165,  165,    0,    0,  165,  123,    0,  166,
  166,  168,  206,  166,   81,   81,  169,    0,    0,  202,
   17,  170,  204,    0,  205,    0,  167,  167,    0,    0,
  167,    0,    0,    0,    0,    0,    0,    0,  248,    0,
  333,    0,  450,  207,    0,    0,    0,    0,    0,    0,
  168,  168,    0,    0,  168,  169,  169,    0,    0,  169,
  170,  170,    0,    0,  170,    0,    0,    0,    0,    0,
    0,  171,    0,   16,   17,   18,  238,   19,  239,  240,
  165,  241,  242,  243,  244,  245,  246,  166,    0,   20,
   21,   22,   23,   24,   25,   26,   27,   28,   29,   30,
   31,   32,  249,    0,  167,  207,   33,   34,   35,   36,
   37,   38,   39,   40,   41,   42,  247,  104,   43,  105,
  192,  193,  194,  195,  196,  197,  198,  199,  168,    0,
    0,  200,  201,  169,    0,   64,   64,    0,  170,   64,
   64,   64,   64,   64,   64,   64,    0,    0,    0,    0,
   44,   45,   46,   47,   48,    0,   49,    0,   11,    0,
    0,    0,    0,   80,   80,   80,    0,    0,    0,    0,
    0,   57,   79,   79,   79,  206,   18,    0,    0,    0,
    0,    0,  202,    0,    0,  204,    0,  205,    0,    0,
    0,    0,   58,    0,    0,    0,    0,    0,    0,    0,
    0,  248,    0,    0,    0,    0,   59,   60,    0,    0,
    0,   81,   81,   81,    0,   41,   42,    0,  104,   43,
  105,  192,  193,  194,  195,  196,  197,  198,  199,    0,
    0,    0,  200,  201,    0,    0,   16,   17,   18,  238,
   19,  239,  240,    0,  241,  242,  243,  244,  245,  246,
  465,  466,   20,   21,   22,   23,   24,   25,   26,   27,
   28,   29,   30,   31,   32,  249,    0,  250,  207,   33,
   34,   35,   36,   37,   38,   39,   40,   41,   42,  247,
  104,   43,  105,  192,  193,  194,  195,  196,  197,  198,
  199,    0,    0,   58,  200,  201,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  156,    0,    0,
    0,    0,    0,   44,   45,   46,   47,   48,    0,   49,
    0,    0,    0,  157,  158,  159,    0,    0,    0,    0,
    0,    0,    0,    0,   57,    0,    0,    0,  206,   33,
   34,   35,   36,   37,    0,  202,    0,    0,  204,    0,
  205,    0,    0,    0,    0,   58,    0,    0,    0,    0,
    0,    0,    0,    0,  248,    0,    0,    0,    0,   59,
   60,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  160,   46,   47,   48,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,   16,
   17,   18,  238,   19,  239,  240,    0,  241,  242,  243,
  244,  245,  246,    0,    0,   20,   21,   22,   23,   24,
   25,   26,   27,   28,   29,   30,   31,   32,  154,    0,
    0,  207,   33,   34,   35,   36,   37,   38,   39,   40,
   41,   42,  247,  104,   43,  105,  192,  193,  194,  195,
  196,  197,  198,  199,    0,    0,    0,  200,  201,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,   44,   45,   46,   47,
   48,    0,   49,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,   57,    0,    0,
    0,  206,    0,    0,    0,    0,    0,    0,  202,    0,
    0,  204,    0,  205,    0,    0,    0,    0,   58,    0,
    0,    0,    0,    0,    0,    0,    0,  248,    0,    0,
    0,    0,   59,   60,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,   16,   17,   18,  238,   19,  239,  240,    0,
  241,  242,  243,  244,  245,  246,    0,    0,   20,   21,
   22,   23,   24,   25,   26,   27,   28,   29,   30,   31,
   32,  249,    0,    0,  207,   33,   34,   35,   36,   37,
   38,   39,   40,   41,   42,  247,  104,   43,  105,  192,
  193,  194,  195,  196,  197,  198,  199,    0,    0,    0,
  200,  201,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,   44,
   45,   46,   47,   48,    0,   49,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
   57,    0,    0,    0,  243,    0,    0,    0,    0,    0,
    0,  243,    0,    0,  243,    0,  243,    0,    0,    0,
    0,   58,    0,    0,    0,    0,    0,    0,    0,    0,
  243,    0,    0,    0,    0,   59,   60,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,   16,   17,   18,  238,   19,
  239,  240,    0,  241,  242,  243,  244,  245,  246,    0,
    0,   20,   21,   22,   23,   24,   25,   26,   27,   28,
   29,   30,   31,   32,  243,    0,    0,  243,   33,   34,
   35,   36,   37,   38,   39,   40,   41,   42,  247,  104,
   43,  105,  192,  193,  194,  195,  196,  197,  198,  199,
    0,    0,    0,  200,  201,  206,    0,    0,    0,    0,
    0,    0,  202,    0,    0,  204,    0,  205,   83,    0,
    0,   83,   44,   45,   46,   47,   48,    0,   49,    0,
    0,  248,    0,    0,    0,   83,   83,    0,   86,    0,
   83,   86,    0,   57,    0,    0,    0,    0,    0,    0,
    0,    0,    0,  223,    0,   86,   86,    0,    0,    0,
   86,    0,    0,    0,   58,    0,    0,    0,    0,    0,
   83,    0,    0,    0,    0,    0,    0,    0,   59,   60,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
   86,    0,    0,    0,    0,    0,    0,    0,  207,    0,
    0,   83,   83,    0,    0,    0,  296,  297,  243,  243,
  243,  243,  243,  243,  243,    0,  243,  243,  243,  243,
  243,  243,   86,    0,  243,  243,  243,  243,  243,  243,
  243,  243,  243,  243,  243,  243,  243,    0,  329,    0,
  223,  243,  243,  243,  243,  243,  243,  243,  243,  243,
  243,  243,  243,  243,  243,  243,  243,  243,  243,  243,
  243,  243,  243,    0,    0,  206,  243,  243,    0,    0,
    0,    0,  202,    0,    0,  204,    0,  205,    0,    0,
    0,    0,    0,    0,    0,  243,  243,  243,  243,  243,
    0,  243,    0,    0,  223,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  223,  243,  223,  223,  223,
  223,  223,  223,  223,  223,  223,  223,  223,  223,  223,
  223,  223,  401,  402,  403,    0,    0,  243,    0,   16,
   17,   18,    0,   19,    0,    0,    0,    0,    0,    0,
    0,  243,  243,    0,    0,   20,   21,   22,   23,   24,
   25,   26,   27,   28,   29,   30,   31,   32,  207,    0,
    0,    0,   33,   34,   35,   36,   37,   38,   39,   40,
   41,   42,    0,  104,   43,  105,  192,  193,  194,  195,
  196,  197,  198,  199,  206,    0,    0,  200,  201,    0,
    0,  202,    0,    0,  204,    0,  205,    0,   83,   83,
   83,    0,    0,    0,  206,    0,   44,   45,   46,   47,
   48,  202,   49,    0,  204,    0,  205,    0,    0,   86,
   86,    0,    0,    0,    0,  206,    0,   57,    0,    0,
    0,    0,  202,    0,    0,  204,    0,  205,    0,    0,
    0,    0,    0,    0,  203,    0,    0,    0,   58,    0,
    0,  346,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,   59,   60,  331,    0,  206,    0,    0,    0,
    0,    0,    0,  202,    0,    0,  204,  207,  205,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  206,   16,
   17,   18,    0,   97,    0,  202,    0,  207,  204,    0,
  205,    0,    0,    0,    0,   20,   98,   99,   23,  100,
   25,   26,   27,   28,   29,  101,  102,  103,  207,    0,
    0,    0,   33,   34,   35,   36,   37,   38,   39,   40,
   41,   42,    0,  104,   43,  105,  192,  193,  194,  195,
  196,  197,  198,  199,    0,    0,    0,  200,  201,    0,
  206,    0,    0,    0,    0,    0,  333,  202,    0,  207,
  204,   87,  205,    0,   87,    0,  106,  107,   46,   47,
   48,    0,  109,  114,    0,    0,    0,    0,   87,   87,
    0,  207,    0,   87,    0,    0,    0,   57,    0,    0,
  126,    0,  128,  130,  131,  136,  142,  145,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,   58,    0,
   18,    0,    0,   87,    0,    0,    0,    0,    0,    0,
    0,    0,   59,   60,    0,    0,    0,    0,    0,    0,
   18,    0,    0,    0,  109,  114,   61,    0,  128,  136,
  142,    0,    0,  207,    0,   87,    0,    0,    0,   41,
   42,   18,  104,   43,  105,  192,  193,  194,  195,  196,
  197,  198,  199,    0,    0,    0,  200,  201,    0,   41,
   42,  136,  104,   43,  105,  192,  193,  194,  195,  196,
  197,  198,  199,    0,    0,    0,  200,  201,    0,    0,
   41,   42,   18,  104,   43,  105,  192,  193,  194,  195,
  196,  197,  198,  199,    0,    0,    0,  200,  201,    0,
    0,    0,    0,    0,   18,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,   58,    0,    0,
    0,   41,   42,    0,  104,   43,  105,  192,  193,  194,
  195,  196,  197,  198,  199,    0,    0,   58,  200,  201,
    0,    0,    0,   41,   42,    0,  104,   43,  105,  192,
  193,  194,  195,  196,  197,  198,  199,    0,   58,    0,
  200,  201,    3,    0,    0,    0,   18,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,   58,
    0,    0,    0,    0,    0,   41,  327,    0,  104,   43,
  105,  192,  193,  194,  195,  196,  197,  198,  199,    0,
    0,   58,  200,  201,   16,   17,   18,    0,   19,  328,
    0,    0,   87,   87,    0,    0,  334,    0,    0,    0,
   20,   21,   22,   23,   24,   25,   26,   27,   28,   29,
   30,   31,   32,    0,    0,    0,    0,   33,   34,   35,
   36,   37,   38,   39,   40,   41,   42,    0,    0,   43,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,   61,   58,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,   44,   45,   46,   47,   48,    0,   49,    0,   11,
    0,    0,    0,    0,    0,   50,   51,   52,   53,   54,
   55,   56,   57,    0,    0,    0,  407,    0,    0,    0,
    0,    0,    0,    0,  334,    0,    0,  334,    0,    0,
    0,    0,    0,   58,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  423,   59,   60,    0,
    3,    3,    3,    0,    3,    0,    0,    0,    0,  424,
    0,    0,  334,    0,    0,    0,    3,    3,    3,    3,
    3,    3,    3,    3,    3,    3,    3,    3,    3,    0,
    0,    0,    0,    3,    3,    3,    3,    3,    3,    3,
    3,    3,    3,    1,    0,    3,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  334,
    0,    0,    0,    0,  449,    0,  334,    3,    3,    3,
    3,    3,    0,    3,    0,    3,    0,    0,    0,    0,
    0,    3,    3,    3,    3,    3,    3,    3,    3,    0,
  334,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    3,
   16,   17,   18,    0,   19,    0,    0,    0,    0,    0,
    0,    0,    0,    3,    3,    0,   20,   21,   22,   23,
   24,   25,   26,   27,   28,   29,   30,   31,   32,    0,
    0,    0,    0,   33,   34,   35,   36,   37,   38,   39,
   40,   41,   42,   52,   52,   43,   51,   52,   52,   52,
   52,   52,    0,   52,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,   52,   52,   52,   52,   52,   52,
    0,    0,    0,    0,    0,    0,    0,   44,   45,   46,
   47,   48,    0,   49,    0,    0,    0,    0,    0,    0,
    0,   50,   51,   52,   53,   54,   55,   56,   57,   52,
   52,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,   58,
    0,    1,    1,    1,    0,    1,    0,    0,    0,    0,
   52,   52,    0,   59,   60,    0,    0,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    0,    0,    0,    0,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,   60,   60,    1,    0,   60,   60,
   60,   60,   60,    0,   60,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,   60,   60,   60,    0,   60,
   60,    0,    0,    0,    0,    0,    0,    0,    1,    1,
    1,    1,    1,   65,    1,    0,   65,    0,   65,   65,
   65,    0,    1,    1,    1,    1,    1,    1,    1,    1,
   60,   60,    0,   65,   65,   65,    0,   65,   65,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    1,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,   60,   60,    0,    1,    1,    0,   66,   65,   65,
   66,    0,   66,   66,   66,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,   66,   66,   66,
    0,   66,   66,    0,    0,   68,    0,    0,   68,   65,
   65,   68,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,   68,   68,   68,    0,   68,
   68,    0,   66,   66,    0,    0,    0,    0,    0,   52,
   52,    0,    0,   52,   52,   52,   52,   52,   52,   52,
   52,   52,   52,   52,   52,   52,   52,   52,   52,   52,
   68,   68,   69,   66,   66,   69,    0,    0,   69,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,   69,   69,   69,    0,   69,   69,    0,    0,
   70,   68,   68,   70,    0,    0,   70,    0,    0,   73,
    0,    0,   73,    0,    0,   73,    0,    0,    0,    0,
   70,   70,   70,    0,   70,   70,    0,   69,   69,   73,
   73,   73,    0,   73,   73,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,   70,   70,    0,   69,   69,
    0,    0,    0,    0,   73,   73,    0,    0,    0,    0,
   60,   60,    0,    0,   60,   60,   60,   60,   60,   60,
   60,    0,    0,    0,    0,    0,   70,   70,    0,    0,
    0,    0,    0,    0,    0,   73,   73,    0,    0,   74,
    0,    0,   74,    0,    0,   74,    0,    0,   65,   65,
    0,    0,   65,   65,   65,   65,   65,   65,   65,   74,
   74,   74,   71,   74,   74,   71,    0,    0,   71,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,   71,   71,   71,    0,   71,   71,    0,    0,
    0,    0,    0,    0,   74,   74,    0,    0,    0,    0,
    0,    0,   66,   66,  284,    0,   66,   66,   66,   66,
   66,   66,   66,    0,    0,    0,    0,   71,   71,    0,
    0,   72,    0,    0,   72,   74,   74,   72,    0,    0,
   68,   68,    0,    0,   68,   68,   68,   68,   68,   68,
   68,   72,   72,   72,    0,   72,   72,  298,   71,   71,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,   72,   72,    0,    0,
    0,    0,    0,    0,    0,    0,    0,   69,   69,    0,
  347,   69,   69,   69,   69,   69,   69,   69,    0,    0,
    0,    0,    0,    0,    0,    0,    0,   72,   72,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,   70,
   70,   70,   70,   70,   70,   70,    0,    0,   73,   73,
   73,   73,   73,   73,   73,    0,   16,   17,   18,    0,
   97,    0,    0,    0,    0,  385,    0,    0,    0,    0,
    0,    0,   20,   98,   99,   23,  100,   25,   26,   27,
   28,   29,  101,  102,  103,    0,    0,    0,  405,   33,
   34,   35,   36,   37,   38,   39,   40,   41,   42,  376,
    0,   43,    0,    0,    0,    0,    0,    0,  416,    0,
    0,    0,    0,  418,  420,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,  106,  107,   46,   47,   48,   74,   74,
   74,   74,   74,   74,   74,    0,    0,    0,    0,    0,
    0,    0,    0,    0,   57,    0,    0,    0,    0,    0,
    0,   71,   71,   71,   71,   71,   71,   71,    0,    0,
    0,    0,    0,    0,    0,   58,    0,    0,    0,    0,
  420,    0,    0,    0,    0,    0,    0,    0,    0,   59,
   60,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  452,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  462,    0,
   72,   72,   72,   72,   72,   72,   72,    0,    0,    0,
  475,   16,   17,   18,    0,   97,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,   20,   98,   99,
   23,  100,   25,   26,   27,   28,   29,  101,  102,  103,
    0,    0,    0,    0,   33,   34,   35,   36,   37,   38,
   39,   40,   41,   42,    0,    0,   43,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  192,  192,  192,
    0,  192,    0,    0,    0,    0,    0,    0,  106,  107,
   46,   47,   48,  192,  192,  192,  192,  192,  192,  192,
  192,  192,  192,  192,  192,  192,    0,    0,    0,   57,
  192,  192,  192,  192,  192,  192,  192,  192,  192,  192,
    0,    0,  192,  298,    0,    0,    0,    0,    0,    0,
   58,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,   59,   60,  188,  188,  188,    0,
  188,    0,    0,    0,  192,  192,  192,  192,  192,    0,
    0,    0,  188,  188,  188,  188,  188,  188,  188,  188,
  188,  188,  188,  188,  188,  192,    0,    0,    0,  188,
  188,  188,  188,  188,  188,  188,  188,  188,  188,    0,
    0,  188,  295,    0,    0,    0,  192,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  192,  192,  189,  189,  189,    0,  189,    0,    0,    0,
    0,    0,    0,  188,  188,  188,  188,  188,  189,  189,
  189,  189,  189,  189,  189,  189,  189,  189,  189,  189,
  189,    0,    0,    0,  188,  189,  189,  189,  189,  189,
  189,  189,  189,  189,  189,    0,    0,  189,  296,    0,
    0,    0,    0,    0,    0,  188,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  188,
  188,  191,  191,  191,    0,  191,    0,    0,    0,  189,
  189,  189,  189,  189,    0,    0,    0,  191,  191,  191,
  191,  191,  191,  191,  191,  191,  191,  191,  191,  191,
  189,    0,    0,    0,  191,  191,  191,  191,  191,  191,
  191,  191,  191,  191,    0,    0,  191,  297,    0,    0,
    0,  189,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  189,  189,  195,  195,  195,
    0,  195,    0,    0,    0,    0,    0,    0,  191,  191,
  191,  191,  191,  195,  195,  195,  195,  195,  195,  195,
  195,  195,  195,  195,  195,  195,    0,    0,    0,  191,
  195,  195,  195,  195,  195,  195,  195,  195,  195,  195,
    0,    0,  195,  299,    0,    0,    0,    0,    0,    0,
  191,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  191,  191,  196,  196,  196,    0,
  196,    0,    0,    0,  195,  195,  195,  195,  195,    0,
    0,    0,  196,  196,  196,  196,  196,  196,  196,  196,
  196,  196,  196,  196,  196,  195,    0,    0,    0,  196,
  196,  196,  196,  196,  196,  196,  196,  196,  196,    0,
    0,  196,  300,    0,    0,    0,  195,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  195,  195,  197,  197,  197,    0,  197,    0,    0,    0,
    0,    0,    0,  196,  196,  196,  196,  196,  197,  197,
  197,  197,  197,  197,  197,  197,  197,  197,  197,  197,
  197,    0,    0,    0,  196,  197,  197,  197,  197,  197,
  197,  197,  197,  197,  197,    0,    0,  197,  301,    0,
    0,    0,    0,    0,    0,  196,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  196,
  196,   16,   17,   18,    0,   97,    0,    0,    0,  197,
  197,  197,  197,  197,    0,    0,    0,   20,   98,   99,
   23,  100,   25,   26,   27,   28,   29,  101,  102,  103,
  197,    0,    0,    0,   33,   34,   35,   36,   37,   38,
   39,   40,   41,   42,    0,    0,   43,    0,    0,    0,
    0,  197,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  197,  197,  156,  156,  156,
    0,  156,    0,    0,    0,    0,    0,    0,  106,  107,
   46,   47,   48,  156,  156,  156,  156,  156,  156,  156,
  156,  156,  156,  156,  156,  156,    0,    0,    0,   57,
  156,  156,  156,  156,  156,  156,  156,  156,  156,  156,
    0,    0,  156,    0,    0,    0,    0,    0,    0,    0,
   58,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,   59,   60,   16,   17,    0,    0,
   97,    0,    0,    0,  156,  156,  156,  156,  156,    0,
    0,    0,   20,   98,   99,   23,  100,   25,   26,   27,
   28,   29,  101,  102,  103,  156,    0,    0,    0,   33,
   34,   35,   36,   37,   38,   39,   40,    0,    0,    0,
  104,    0,  105,    0,    0,    0,  156,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  156,  156,   16,   17,    0,    0,   97,    0,    0,    0,
    0,    0,    0,  106,  107,   46,   47,   48,   20,   98,
   99,   23,  100,   25,   26,   27,   28,   29,  101,  102,
  103,    0,    0,    0,   57,   33,   34,   35,   36,   37,
   38,   39,   40,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,   59,
   60,   16,   17,    0,    0,   19,    0,    0,    0,  106,
  107,   46,   47,   48,    0,    0,    0,   20,   21,   22,
   23,   24,   25,   26,   27,   28,   29,   30,   31,   32,
   57,    0,    0,    0,   33,   34,   35,   36,   37,   38,
   39,   40,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,   59,   60,   16,   17,    0,
    0,  132,    0,    0,    0,    0,    0,    0,  106,  107,
   46,   47,   48,   20,  133,  134,   23,  135,   25,   26,
   27,   28,   29,   30,   31,   32,    0,    0,    0,   57,
   33,   34,   35,   36,   37,   38,   39,   40,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,   59,   60,    0,    0,    0,    0,
    0,    0,    0,    0,  106,  107,   46,   47,   48,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,   57,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
   59,   60,
};
static const YYINT _mesa_glsl_check[] = {                12,
   12,   61,    4,   41,   95,   44,   41,  341,  240,   11,
   91,   60,   63,   62,  147,  174,    5,   61,   12,   41,
  234,   59,   44,  307,   40,   41,   41,  123,   61,   44,
  342,   91,   38,   12,   12,   41,   58,   59,   44,   41,
   44,   63,  345,   58,   59,   44,   45,   91,   63,  444,
   63,  151,   58,   59,   58,   67,   68,   63,   91,  454,
   67,   68,  125,   62,   76,   40,   65,   66,   59,   44,
   69,   93,   74,   38,  288,   91,   41,   44,   93,   44,
   93,   93,   95,  174,   59,  176,  125,   93,   94,   67,
   68,   58,   94,   58,   59,   60,   95,   62,   63,   93,
  191,  234,  115,  125,   93,  344,  125,  106,  107,  124,
  125,  110,  111,  112,   93,   93,   61,   41,  124,  125,
   44,  123,   61,  125,  301,  302,  303,  286,   93,   94,
   44,  143,  123,   37,   58,   59,  143,  125,   42,   63,
  345,  154,  154,   47,  156,   59,  345,   44,  160,  161,
  162,  164,   91,  165,  166,  288,  125,   44,   45,  124,
  125,  174,   59,  176,   38,  143,  168,   41,  345,   93,
   44,   41,  345,   44,   44,  174,  154,  176,  191,  279,
  345,  281,   44,   44,   58,   59,  164,   74,   59,   63,
   38,   41,  191,   41,   44,  286,   44,   59,   59,   40,
   41,  125,  345,   44,  295,  301,  302,  303,  271,  272,
   58,   59,  444,   41,   41,   63,   44,   44,   59,   93,
   94,  345,  454,   38,  259,  345,   41,  240,  240,   44,
   41,   58,   59,   44,  315,  316,   63,   40,   41,  252,
  252,   44,   44,   58,   59,   93,   94,   43,   63,   45,
  124,  125,  271,  272,  319,  320,   59,   59,  349,   40,
  273,  259,  240,  298,  299,   44,   93,  302,  317,  318,
  370,  322,  274,  286,  252,  356,  124,  125,   93,   94,
   59,   40,  295,  271,  272,   33,  303,  286,  290,   44,
  292,   41,   40,   91,   44,   43,  295,   45,  125,  321,
  322,  323,  271,  272,   59,   44,  321,  322,  323,  124,
  125,   59,   41,  319,  320,  321,  322,  323,   44,   44,
  355,   59,  259,  123,  415,   44,  301,  302,  303,  342,
  342,  431,   44,   59,   59,   59,  349,   59,  351,  351,
   59,  376,   41,   41,   59,   44,   44,   59,  313,  314,
  349,  123,  317,  318,  319,  320,  321,  322,  323,   58,
   59,  298,  299,   41,  342,  302,   44,  369,  259,  301,
  302,  303,   40,  351,   91,  123,   44,  125,  126,  324,
  325,  326,  327,  328,  329,  330,  331,  332,  333,   33,
   40,   59,   41,   61,   93,   44,   40,  345,  322,   43,
   59,   45,  415,  308,  309,  310,  311,  298,  299,  422,
  422,  302,  301,  302,  303,   59,  415,  419,   41,   41,
   61,   44,   44,   91,   41,  323,  125,   44,  441,  441,
   41,  444,  444,   44,  124,   58,   59,  313,  314,  376,
   63,  454,  454,  321,  422,  319,  320,  321,  322,  323,
   38,  464,  464,  306,  307,  468,  468,  470,  470,   94,
  301,  302,  303,  441,   49,   93,  444,   41,  481,  481,
   93,  319,  320,  321,  322,  323,  454,  312,  313,  123,
   40,  125,  126,  314,  315,  376,  464,  336,  337,  338,
  468,   76,  470,   59,  321,  322,  323,   59,  301,  302,
  303,  333,  125,  481,  336,   40,  321,  322,  323,  257,
  258,  259,  260,  261,  262,  263,   40,  265,  266,  267,
  268,  269,  270,  271,  272,  273,  274,  275,  276,  277,
  278,  279,  280,  281,  282,  283,  284,  285,   59,  371,
   59,   40,  290,  291,  292,  293,  294,  295,  296,  297,
  298,  299,  300,  301,  302,  303,  304,  305,  306,  307,
  308,  309,  310,  311,  125,  259,   40,  315,  316,   59,
  125,  156,  312,   93,   44,  160,  161,  162,   93,  300,
  165,  166,  252,  303,   40,  123,  334,  335,  336,  337,
  338,   41,  340,  156,  342,   59,  428,  160,  161,  162,
   59,   41,  165,  435,  298,  299,   61,  355,  302,  264,
   59,   58,   41,  257,  258,  259,  260,  261,  262,  263,
    0,  265,  266,  267,  268,  269,  270,  459,  376,  273,
  274,  275,  276,  277,  278,  279,  280,  281,  282,  283,
  284,  285,  390,  391,   41,  125,  290,  291,  292,  293,
  294,  295,  296,  297,  298,  299,  300,  301,  302,  303,
  304,  305,  306,  307,  308,  309,  310,  311,   59,   33,
   59,  315,  316,   93,   59,   59,   40,  351,   41,   43,
   38,   45,  376,   41,   41,   43,   44,   45,  259,  290,
  334,  335,  336,  337,  338,   59,  340,   64,  342,  322,
   58,   59,   60,   41,   62,   63,   44,   75,  166,   38,
  259,  355,   41,  342,  301,   44,  295,  299,  302,  305,
   58,   59,  301,  302,  303,   63,  303,  298,  299,   58,
   59,  302,  376,   93,   63,   93,   94,  304,  342,  176,
  374,  293,  295,  471,  415,  468,  390,  391,   67,  298,
  299,   41,  422,  302,   44,   93,   94,   67,   67,  123,
   67,  125,  126,   -1,   93,   94,  124,  125,   58,   59,
   33,  441,   -1,   63,  259,   -1,   -1,   40,   -1,   -1,
   43,   -1,   45,  259,  355,  364,  124,  125,   -1,   40,
  259,   -1,   -1,   44,  464,  124,  125,   -1,  468,   -1,
  470,   -1,   -1,   93,   94,  376,  355,  259,   59,   -1,
   61,  481,   -1,  298,  299,   -1,   -1,  302,  397,   -1,
   -1,   -1,  298,  299,   -1,   -1,  302,  376,   -1,  298,
  299,  259,   33,  302,  124,  125,  259,   -1,   -1,   40,
   91,  259,   43,   -1,   45,   -1,  298,  299,   -1,   -1,
  302,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   59,   -1,
  123,   -1,  125,  126,   -1,   -1,   -1,   -1,   -1,   -1,
  298,  299,   -1,   -1,  302,  298,  299,   -1,   -1,  302,
  298,  299,   -1,   -1,  302,   -1,   -1,   -1,   -1,   -1,
   -1,  376,   -1,  257,  258,  259,  260,  261,  262,  263,
  376,  265,  266,  267,  268,  269,  270,  376,   -1,  273,
  274,  275,  276,  277,  278,  279,  280,  281,  282,  283,
  284,  285,  123,   -1,  376,  126,  290,  291,  292,  293,
  294,  295,  296,  297,  298,  299,  300,  301,  302,  303,
  304,  305,  306,  307,  308,  309,  310,  311,  376,   -1,
   -1,  315,  316,  376,   -1,  313,  314,   -1,  376,  317,
  318,  319,  320,  321,  322,  323,   -1,   -1,   -1,   -1,
  334,  335,  336,  337,  338,   -1,  340,   -1,  342,   -1,
   -1,   -1,   -1,  321,  322,  323,   -1,   -1,   -1,   -1,
   -1,  355,  321,  322,  323,   33,  259,   -1,   -1,   -1,
   -1,   -1,   40,   -1,   -1,   43,   -1,   45,   -1,   -1,
   -1,   -1,  376,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   59,   -1,   -1,   -1,   -1,  390,  391,   -1,   -1,
   -1,  321,  322,  323,   -1,  298,  299,   -1,  301,  302,
  303,  304,  305,  306,  307,  308,  309,  310,  311,   -1,
   -1,   -1,  315,  316,   -1,   -1,  257,  258,  259,  260,
  261,  262,  263,   -1,  265,  266,  267,  268,  269,  270,
  271,  272,  273,  274,  275,  276,  277,  278,  279,  280,
  281,  282,  283,  284,  285,  123,   -1,  125,  126,  290,
  291,  292,  293,  294,  295,  296,  297,  298,  299,  300,
  301,  302,  303,  304,  305,  306,  307,  308,  309,  310,
  311,   -1,   -1,  376,  315,  316,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  258,   -1,   -1,
   -1,   -1,   -1,  334,  335,  336,  337,  338,   -1,  340,
   -1,   -1,   -1,  274,  275,  276,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  355,   -1,   -1,   -1,   33,  290,
  291,  292,  293,  294,   -1,   40,   -1,   -1,   43,   -1,
   45,   -1,   -1,   -1,   -1,  376,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   59,   -1,   -1,   -1,   -1,  390,
  391,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  335,  336,  337,  338,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  257,
  258,  259,  260,  261,  262,  263,   -1,  265,  266,  267,
  268,  269,  270,   -1,   -1,  273,  274,  275,  276,  277,
  278,  279,  280,  281,  282,  283,  284,  285,  123,   -1,
   -1,  126,  290,  291,  292,  293,  294,  295,  296,  297,
  298,  299,  300,  301,  302,  303,  304,  305,  306,  307,
  308,  309,  310,  311,   -1,   -1,   -1,  315,  316,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  334,  335,  336,  337,
  338,   -1,  340,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  355,   -1,   -1,
   -1,   33,   -1,   -1,   -1,   -1,   -1,   -1,   40,   -1,
   -1,   43,   -1,   45,   -1,   -1,   -1,   -1,  376,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   59,   -1,   -1,
   -1,   -1,  390,  391,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  257,  258,  259,  260,  261,  262,  263,   -1,
  265,  266,  267,  268,  269,  270,   -1,   -1,  273,  274,
  275,  276,  277,  278,  279,  280,  281,  282,  283,  284,
  285,  123,   -1,   -1,  126,  290,  291,  292,  293,  294,
  295,  296,  297,  298,  299,  300,  301,  302,  303,  304,
  305,  306,  307,  308,  309,  310,  311,   -1,   -1,   -1,
  315,  316,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  334,
  335,  336,  337,  338,   -1,  340,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  355,   -1,   -1,   -1,   33,   -1,   -1,   -1,   -1,   -1,
   -1,   40,   -1,   -1,   43,   -1,   45,   -1,   -1,   -1,
   -1,  376,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   59,   -1,   -1,   -1,   -1,  390,  391,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  257,  258,  259,  260,  261,
  262,  263,   -1,  265,  266,  267,  268,  269,  270,   -1,
   -1,  273,  274,  275,  276,  277,  278,  279,  280,  281,
  282,  283,  284,  285,  123,   -1,   -1,  126,  290,  291,
  292,  293,  294,  295,  296,  297,  298,  299,  300,  301,
  302,  303,  304,  305,  306,  307,  308,  309,  310,  311,
   -1,   -1,   -1,  315,  316,   33,   -1,   -1,   -1,   -1,
   -1,   -1,   40,   -1,   -1,   43,   -1,   45,   41,   -1,
   -1,   44,  334,  335,  336,  337,  338,   -1,  340,   -1,
   -1,   59,   -1,   -1,   -1,   58,   59,   -1,   41,   -1,
   63,   44,   -1,  355,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  147,   -1,   58,   59,   -1,   -1,   -1,
   63,   -1,   -1,   -1,  376,   -1,   -1,   -1,   -1,   -1,
   93,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  390,  391,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   93,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  126,   -1,
   -1,  124,  125,   -1,   -1,   -1,  200,  201,  257,  258,
  259,  260,  261,  262,  263,   -1,  265,  266,  267,  268,
  269,  270,  125,   -1,  273,  274,  275,  276,  277,  278,
  279,  280,  281,  282,  283,  284,  285,   -1,  232,   -1,
  234,  290,  291,  292,  293,  294,  295,  296,  297,  298,
  299,  300,  301,  302,  303,  304,  305,  306,  307,  308,
  309,  310,  311,   -1,   -1,   33,  315,  316,   -1,   -1,
   -1,   -1,   40,   -1,   -1,   43,   -1,   45,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  334,  335,  336,  337,  338,
   -1,  340,   -1,   -1,  288,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  299,  355,  301,  302,  303,
  304,  305,  306,  307,  308,  309,  310,  311,  312,  313,
  314,  315,  316,  317,  318,   -1,   -1,  376,   -1,  257,
  258,  259,   -1,  261,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  390,  391,   -1,   -1,  273,  274,  275,  276,  277,
  278,  279,  280,  281,  282,  283,  284,  285,  126,   -1,
   -1,   -1,  290,  291,  292,  293,  294,  295,  296,  297,
  298,  299,   -1,  301,  302,  303,  304,  305,  306,  307,
  308,  309,  310,  311,   33,   -1,   -1,  315,  316,   -1,
   -1,   40,   -1,   -1,   43,   -1,   45,   -1,  321,  322,
  323,   -1,   -1,   -1,   33,   -1,  334,  335,  336,  337,
  338,   40,  340,   -1,   43,   -1,   45,   -1,   -1,  322,
  323,   -1,   -1,   -1,   -1,   33,   -1,  355,   -1,   -1,
   -1,   -1,   40,   -1,   -1,   43,   -1,   45,   -1,   -1,
   -1,   -1,   -1,   -1,   93,   -1,   -1,   -1,  376,   -1,
   -1,   59,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  390,  391,   93,   -1,   33,   -1,   -1,   -1,
   -1,   -1,   -1,   40,   -1,   -1,   43,  126,   45,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   33,  257,
  258,  259,   -1,  261,   -1,   40,   -1,  126,   43,   -1,
   45,   -1,   -1,   -1,   -1,  273,  274,  275,  276,  277,
  278,  279,  280,  281,  282,  283,  284,  285,  126,   -1,
   -1,   -1,  290,  291,  292,  293,  294,  295,  296,  297,
  298,  299,   -1,  301,  302,  303,  304,  305,  306,  307,
  308,  309,  310,  311,   -1,   -1,   -1,  315,  316,   -1,
   33,   -1,   -1,   -1,   -1,   -1,  123,   40,   -1,  126,
   43,   41,   45,   -1,   44,   -1,  334,  335,  336,  337,
  338,   -1,   44,   45,   -1,   -1,   -1,   -1,   58,   59,
   -1,  126,   -1,   63,   -1,   -1,   -1,  355,   -1,   -1,
   62,   -1,   64,   65,   66,   67,   68,   69,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  376,   -1,
  259,   -1,   -1,   93,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  390,  391,   -1,   -1,   -1,   -1,   -1,   -1,
  259,   -1,   -1,   -1,  106,  107,   59,   -1,  110,  111,
  112,   -1,   -1,  126,   -1,  125,   -1,   -1,   -1,  298,
  299,  259,  301,  302,  303,  304,  305,  306,  307,  308,
  309,  310,  311,   -1,   -1,   -1,  315,  316,   -1,  298,
  299,  143,  301,  302,  303,  304,  305,  306,  307,  308,
  309,  310,  311,   -1,   -1,   -1,  315,  316,   -1,   -1,
  298,  299,  259,  301,  302,  303,  304,  305,  306,  307,
  308,  309,  310,  311,   -1,   -1,   -1,  315,  316,   -1,
   -1,   -1,   -1,   -1,  259,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  376,   -1,   -1,
   -1,  298,  299,   -1,  301,  302,  303,  304,  305,  306,
  307,  308,  309,  310,  311,   -1,   -1,  376,  315,  316,
   -1,   -1,   -1,  298,  299,   -1,  301,  302,  303,  304,
  305,  306,  307,  308,  309,  310,  311,   -1,  376,   -1,
  315,  316,   59,   -1,   -1,   -1,  259,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  376,
   -1,   -1,   -1,   -1,   -1,  298,  299,   -1,  301,  302,
  303,  304,  305,  306,  307,  308,  309,  310,  311,   -1,
   -1,  376,  315,  316,  257,  258,  259,   -1,  261,  228,
   -1,   -1,  322,  323,   -1,   -1,  235,   -1,   -1,   -1,
  273,  274,  275,  276,  277,  278,  279,  280,  281,  282,
  283,  284,  285,   -1,   -1,   -1,   -1,  290,  291,  292,
  293,  294,  295,  296,  297,  298,  299,   -1,   -1,  302,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   59,  376,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  334,  335,  336,  337,  338,   -1,  340,   -1,  342,
   -1,   -1,   -1,   -1,   -1,  348,  349,  350,  351,  352,
  353,  354,  355,   -1,   -1,   -1,  325,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  333,   -1,   -1,  336,   -1,   -1,
   -1,   -1,   -1,  376,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  355,  390,  391,   -1,
  257,  258,  259,   -1,  261,   -1,   -1,   -1,   -1,  368,
   -1,   -1,  371,   -1,   -1,   -1,  273,  274,  275,  276,
  277,  278,  279,  280,  281,  282,  283,  284,  285,   -1,
   -1,   -1,   -1,  290,  291,  292,  293,  294,  295,  296,
  297,  298,  299,   59,   -1,  302,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  428,
   -1,   -1,   -1,   -1,  433,   -1,  435,  334,  335,  336,
  337,  338,   -1,  340,   -1,  342,   -1,   -1,   -1,   -1,
   -1,  348,  349,  350,  351,  352,  353,  354,  355,   -1,
  459,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  376,
  257,  258,  259,   -1,  261,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  390,  391,   -1,  273,  274,  275,  276,
  277,  278,  279,  280,  281,  282,  283,  284,  285,   -1,
   -1,   -1,   -1,  290,  291,  292,  293,  294,  295,  296,
  297,  298,  299,   37,   38,  302,   40,   41,   42,   43,
   44,   45,   -1,   47,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   58,   59,   60,   61,   62,   63,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  334,  335,  336,
  337,  338,   -1,  340,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  348,  349,  350,  351,  352,  353,  354,  355,   93,
   94,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  376,
   -1,  257,  258,  259,   -1,  261,   -1,   -1,   -1,   -1,
  124,  125,   -1,  390,  391,   -1,   -1,  273,  274,  275,
  276,  277,  278,  279,  280,  281,  282,  283,  284,  285,
   -1,   -1,   -1,   -1,  290,  291,  292,  293,  294,  295,
  296,  297,  298,  299,   37,   38,  302,   -1,   41,   42,
   43,   44,   45,   -1,   47,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   58,   59,   60,   -1,   62,
   63,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  334,  335,
  336,  337,  338,   38,  340,   -1,   41,   -1,   43,   44,
   45,   -1,  348,  349,  350,  351,  352,  353,  354,  355,
   93,   94,   -1,   58,   59,   60,   -1,   62,   63,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  376,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  124,  125,   -1,  390,  391,   -1,   38,   93,   94,
   41,   -1,   43,   44,   45,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   58,   59,   60,
   -1,   62,   63,   -1,   -1,   38,   -1,   -1,   41,  124,
  125,   44,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   58,   59,   60,   -1,   62,
   63,   -1,   93,   94,   -1,   -1,   -1,   -1,   -1,  313,
  314,   -1,   -1,  317,  318,  319,  320,  321,  322,  323,
  324,  325,  326,  327,  328,  329,  330,  331,  332,  333,
   93,   94,   38,  124,  125,   41,   -1,   -1,   44,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   58,   59,   60,   -1,   62,   63,   -1,   -1,
   38,  124,  125,   41,   -1,   -1,   44,   -1,   -1,   38,
   -1,   -1,   41,   -1,   -1,   44,   -1,   -1,   -1,   -1,
   58,   59,   60,   -1,   62,   63,   -1,   93,   94,   58,
   59,   60,   -1,   62,   63,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   93,   94,   -1,  124,  125,
   -1,   -1,   -1,   -1,   93,   94,   -1,   -1,   -1,   -1,
  313,  314,   -1,   -1,  317,  318,  319,  320,  321,  322,
  323,   -1,   -1,   -1,   -1,   -1,  124,  125,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  124,  125,   -1,   -1,   38,
   -1,   -1,   41,   -1,   -1,   44,   -1,   -1,  313,  314,
   -1,   -1,  317,  318,  319,  320,  321,  322,  323,   58,
   59,   60,   38,   62,   63,   41,   -1,   -1,   44,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   58,   59,   60,   -1,   62,   63,   -1,   -1,
   -1,   -1,   -1,   -1,   93,   94,   -1,   -1,   -1,   -1,
   -1,   -1,  313,  314,  125,   -1,  317,  318,  319,  320,
  321,  322,  323,   -1,   -1,   -1,   -1,   93,   94,   -1,
   -1,   38,   -1,   -1,   41,  124,  125,   44,   -1,   -1,
  313,  314,   -1,   -1,  317,  318,  319,  320,  321,  322,
  323,   58,   59,   60,   -1,   62,   63,  202,  124,  125,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   93,   94,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  313,  314,   -1,
  245,  317,  318,  319,  320,  321,  322,  323,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  124,  125,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  317,
  318,  319,  320,  321,  322,  323,   -1,   -1,  317,  318,
  319,  320,  321,  322,  323,   -1,  257,  258,  259,   -1,
  261,   -1,   -1,   -1,   -1,  300,   -1,   -1,   -1,   -1,
   -1,   -1,  273,  274,  275,  276,  277,  278,  279,  280,
  281,  282,  283,  284,  285,   -1,   -1,   -1,  323,  290,
  291,  292,  293,  294,  295,  296,  297,  298,  299,  125,
   -1,  302,   -1,   -1,   -1,   -1,   -1,   -1,  343,   -1,
   -1,   -1,   -1,  348,  349,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  334,  335,  336,  337,  338,  317,  318,
  319,  320,  321,  322,  323,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  355,   -1,   -1,   -1,   -1,   -1,
   -1,  317,  318,  319,  320,  321,  322,  323,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  376,   -1,   -1,   -1,   -1,
  415,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  390,
  391,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  437,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  453,   -1,
  317,  318,  319,  320,  321,  322,  323,   -1,   -1,   -1,
  465,  257,  258,  259,   -1,  261,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  273,  274,  275,
  276,  277,  278,  279,  280,  281,  282,  283,  284,  285,
   -1,   -1,   -1,   -1,  290,  291,  292,  293,  294,  295,
  296,  297,  298,  299,   -1,   -1,  302,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  257,  258,  259,
   -1,  261,   -1,   -1,   -1,   -1,   -1,   -1,  334,  335,
  336,  337,  338,  273,  274,  275,  276,  277,  278,  279,
  280,  281,  282,  283,  284,  285,   -1,   -1,   -1,  355,
  290,  291,  292,  293,  294,  295,  296,  297,  298,  299,
   -1,   -1,  302,  303,   -1,   -1,   -1,   -1,   -1,   -1,
  376,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  390,  391,  257,  258,  259,   -1,
  261,   -1,   -1,   -1,  334,  335,  336,  337,  338,   -1,
   -1,   -1,  273,  274,  275,  276,  277,  278,  279,  280,
  281,  282,  283,  284,  285,  355,   -1,   -1,   -1,  290,
  291,  292,  293,  294,  295,  296,  297,  298,  299,   -1,
   -1,  302,  303,   -1,   -1,   -1,  376,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  390,  391,  257,  258,  259,   -1,  261,   -1,   -1,   -1,
   -1,   -1,   -1,  334,  335,  336,  337,  338,  273,  274,
  275,  276,  277,  278,  279,  280,  281,  282,  283,  284,
  285,   -1,   -1,   -1,  355,  290,  291,  292,  293,  294,
  295,  296,  297,  298,  299,   -1,   -1,  302,  303,   -1,
   -1,   -1,   -1,   -1,   -1,  376,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  390,
  391,  257,  258,  259,   -1,  261,   -1,   -1,   -1,  334,
  335,  336,  337,  338,   -1,   -1,   -1,  273,  274,  275,
  276,  277,  278,  279,  280,  281,  282,  283,  284,  285,
  355,   -1,   -1,   -1,  290,  291,  292,  293,  294,  295,
  296,  297,  298,  299,   -1,   -1,  302,  303,   -1,   -1,
   -1,  376,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  390,  391,  257,  258,  259,
   -1,  261,   -1,   -1,   -1,   -1,   -1,   -1,  334,  335,
  336,  337,  338,  273,  274,  275,  276,  277,  278,  279,
  280,  281,  282,  283,  284,  285,   -1,   -1,   -1,  355,
  290,  291,  292,  293,  294,  295,  296,  297,  298,  299,
   -1,   -1,  302,  303,   -1,   -1,   -1,   -1,   -1,   -1,
  376,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  390,  391,  257,  258,  259,   -1,
  261,   -1,   -1,   -1,  334,  335,  336,  337,  338,   -1,
   -1,   -1,  273,  274,  275,  276,  277,  278,  279,  280,
  281,  282,  283,  284,  285,  355,   -1,   -1,   -1,  290,
  291,  292,  293,  294,  295,  296,  297,  298,  299,   -1,
   -1,  302,  303,   -1,   -1,   -1,  376,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  390,  391,  257,  258,  259,   -1,  261,   -1,   -1,   -1,
   -1,   -1,   -1,  334,  335,  336,  337,  338,  273,  274,
  275,  276,  277,  278,  279,  280,  281,  282,  283,  284,
  285,   -1,   -1,   -1,  355,  290,  291,  292,  293,  294,
  295,  296,  297,  298,  299,   -1,   -1,  302,  303,   -1,
   -1,   -1,   -1,   -1,   -1,  376,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  390,
  391,  257,  258,  259,   -1,  261,   -1,   -1,   -1,  334,
  335,  336,  337,  338,   -1,   -1,   -1,  273,  274,  275,
  276,  277,  278,  279,  280,  281,  282,  283,  284,  285,
  355,   -1,   -1,   -1,  290,  291,  292,  293,  294,  295,
  296,  297,  298,  299,   -1,   -1,  302,   -1,   -1,   -1,
   -1,  376,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  390,  391,  257,  258,  259,
   -1,  261,   -1,   -1,   -1,   -1,   -1,   -1,  334,  335,
  336,  337,  338,  273,  274,  275,  276,  277,  278,  279,
  280,  281,  282,  283,  284,  285,   -1,   -1,   -1,  355,
  290,  291,  292,  293,  294,  295,  296,  297,  298,  299,
   -1,   -1,  302,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  376,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  390,  391,  257,  258,   -1,   -1,
  261,   -1,   -1,   -1,  334,  335,  336,  337,  338,   -1,
   -1,   -1,  273,  274,  275,  276,  277,  278,  279,  280,
  281,  282,  283,  284,  285,  355,   -1,   -1,   -1,  290,
  291,  292,  293,  294,  295,  296,  297,   -1,   -1,   -1,
  301,   -1,  303,   -1,   -1,   -1,  376,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  390,  391,  257,  258,   -1,   -1,  261,   -1,   -1,   -1,
   -1,   -1,   -1,  334,  335,  336,  337,  338,  273,  274,
  275,  276,  277,  278,  279,  280,  281,  282,  283,  284,
  285,   -1,   -1,   -1,  355,  290,  291,  292,  293,  294,
  295,  296,  297,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  390,
  391,  257,  258,   -1,   -1,  261,   -1,   -1,   -1,  334,
  335,  336,  337,  338,   -1,   -1,   -1,  273,  274,  275,
  276,  277,  278,  279,  280,  281,  282,  283,  284,  285,
  355,   -1,   -1,   -1,  290,  291,  292,  293,  294,  295,
  296,  297,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  390,  391,  257,  258,   -1,
   -1,  261,   -1,   -1,   -1,   -1,   -1,   -1,  334,  335,
  336,  337,  338,  273,  274,  275,  276,  277,  278,  279,
  280,  281,  282,  283,  284,  285,   -1,   -1,   -1,  355,
  290,  291,  292,  293,  294,  295,  296,  297,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  390,  391,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  334,  335,  336,  337,  338,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  355,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  390,  391,
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
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,
};
#endif
#define YYFINAL 2
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 398
#define YYUNDFTOKEN 510
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
"PIXEL_LOCAL","PIXEL_LOCAL_IN","PIXEL_LOCAL_OUT","IMAGE1DSHADOW",
"IMAGE2DSHADOW","IMAGE1DARRAYSHADOW","IMAGE2DARRAYSHADOW","COHERENT","VOLATILE",
"RESTRICT","READONLY","WRITEONLY","SHARED","TASKPAYLOAD","PERPRIMITIVE",
"STRUCT","VOID_TOK","WHILE","IDENTIFIER","TYPE_IDENTIFIER","NEW_IDENTIFIER",
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
"auxiliary_storage_qualifier : PERPRIMITIVE",
"storage_qualifier : CONST_TOK",
"storage_qualifier : ATTRIBUTE",
"storage_qualifier : VARYING",
"storage_qualifier : IN_TOK",
"storage_qualifier : OUT_TOK",
"storage_qualifier : INOUT_TOK",
"storage_qualifier : UNIFORM",
"storage_qualifier : BUFFER",
"storage_qualifier : SHARED",
"storage_qualifier : TASKPAYLOAD",
"storage_qualifier : PIXEL_LOCAL",
"storage_qualifier : PIXEL_LOCAL_IN",
"storage_qualifier : PIXEL_LOCAL_OUT",
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
"interface_qualifier : PIXEL_LOCAL",
"interface_qualifier : PIXEL_LOCAL_IN",
"interface_qualifier : PIXEL_LOCAL_OUT",
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
#line 297 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      _mesa_glsl_initialize_types(state);
   }
#line 3372 "compiler/glsl/glsl_parser.cpp"
break;
case 2:
#line 301 "../mesa/src/compiler/glsl/glsl_parser.yy"
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
#line 3393 "compiler/glsl/glsl_parser.cpp"
break;
case 4:
#line 323 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      state->process_version_directive(&yystack.p_mark[-1], yystack.l_mark[-1].n, NULL);
      if (state->error) {
         YYERROR;
      }
   }
#line 3403 "compiler/glsl/glsl_parser.cpp"
break;
case 5:
#line 330 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      state->process_version_directive(&yystack.p_mark[-2], yystack.l_mark[-2].n, yystack.l_mark[-1].identifier);
      if (state->error) {
         YYERROR;
      }
   }
#line 3413 "compiler/glsl/glsl_parser.cpp"
break;
case 6:
#line 339 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{ yyval.node = NULL; }
#line 3418 "compiler/glsl/glsl_parser.cpp"
break;
case 7:
#line 340 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{ yyval.node = NULL; }
#line 3423 "compiler/glsl/glsl_parser.cpp"
break;
case 8:
#line 341 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{ yyval.node = NULL; }
#line 3428 "compiler/glsl/glsl_parser.cpp"
break;
case 9:
#line 342 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{ yyval.node = NULL; }
#line 3433 "compiler/glsl/glsl_parser.cpp"
break;
case 10:
#line 344 "../mesa/src/compiler/glsl/glsl_parser.yy"
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
#line 3460 "compiler/glsl/glsl_parser.cpp"
break;
case 11:
#line 368 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      linear_ctx *mem_ctx = state->linalloc;
      yyval.node = new(mem_ctx) ast_warnings_toggle(true);
   }
#line 3468 "compiler/glsl/glsl_parser.cpp"
break;
case 12:
#line 373 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      linear_ctx *mem_ctx = state->linalloc;
      yyval.node = new(mem_ctx) ast_warnings_toggle(false);
   }
#line 3476 "compiler/glsl/glsl_parser.cpp"
break;
case 18:
#line 392 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      if (!_mesa_glsl_process_extension(yystack.l_mark[-3].identifier, & yystack.p_mark[-3], yystack.l_mark[-1].identifier, & yystack.p_mark[-1], state)) {
         YYERROR;
      }
   }
#line 3485 "compiler/glsl/glsl_parser.cpp"
break;
case 19:
#line 401 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      /* FINISHME: The NULL test is required because pragmas are set to
       * FINISHME: NULL. (See production rule for external_declaration.)
       */
      if (yystack.l_mark[0].node != NULL)
         state->translation_unit.push_tail(& yystack.l_mark[0].node->link);
   }
#line 3496 "compiler/glsl/glsl_parser.cpp"
break;
case 20:
#line 409 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      /* FINISHME: The NULL test is required because pragmas are set to
       * FINISHME: NULL. (See production rule for external_declaration.)
       */
      if (yystack.l_mark[0].node != NULL)
         state->translation_unit.push_tail(& yystack.l_mark[0].node->link);
   }
#line 3507 "compiler/glsl/glsl_parser.cpp"
break;
case 21:
#line 416 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      if (!state->allow_extension_directive_midshader) {
         _mesa_glsl_error(& yystack.p_mark[0], state,
                          "#extension directive is not allowed "
                          "in the middle of a shader");
         YYERROR;
      }
   }
#line 3519 "compiler/glsl/glsl_parser.cpp"
break;
case 24:
#line 433 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      linear_ctx *ctx = state->linalloc;
      yyval.expression = new(ctx) ast_expression(ast_identifier, NULL, NULL, NULL);
      yyval.expression->set_location(yystack.p_mark[0]);
      yyval.expression->primary_expression.identifier = yystack.l_mark[0].identifier;
   }
#line 3529 "compiler/glsl/glsl_parser.cpp"
break;
case 25:
#line 440 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      linear_ctx *ctx = state->linalloc;
      yyval.expression = new(ctx) ast_expression(ast_int_constant, NULL, NULL, NULL);
      yyval.expression->set_location(yystack.p_mark[0]);
      yyval.expression->primary_expression.int_constant = yystack.l_mark[0].n;
   }
#line 3539 "compiler/glsl/glsl_parser.cpp"
break;
case 26:
#line 447 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      linear_ctx *ctx = state->linalloc;
      yyval.expression = new(ctx) ast_expression(ast_uint_constant, NULL, NULL, NULL);
      yyval.expression->set_location(yystack.p_mark[0]);
      yyval.expression->primary_expression.uint_constant = yystack.l_mark[0].n;
   }
#line 3549 "compiler/glsl/glsl_parser.cpp"
break;
case 27:
#line 454 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      linear_ctx *ctx = state->linalloc;
      yyval.expression = new(ctx) ast_expression(ast_int64_constant, NULL, NULL, NULL);
      yyval.expression->set_location(yystack.p_mark[0]);
      yyval.expression->primary_expression.int64_constant = yystack.l_mark[0].n64;
   }
#line 3559 "compiler/glsl/glsl_parser.cpp"
break;
case 28:
#line 461 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      linear_ctx *ctx = state->linalloc;
      yyval.expression = new(ctx) ast_expression(ast_uint64_constant, NULL, NULL, NULL);
      yyval.expression->set_location(yystack.p_mark[0]);
      yyval.expression->primary_expression.uint64_constant = yystack.l_mark[0].n64;
   }
#line 3569 "compiler/glsl/glsl_parser.cpp"
break;
case 29:
#line 468 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      linear_ctx *ctx = state->linalloc;
      yyval.expression = new(ctx) ast_expression(ast_float16_constant, NULL, NULL, NULL);
      yyval.expression->set_location(yystack.p_mark[0]);
      yyval.expression->primary_expression.float16_constant = yystack.l_mark[0].real;
   }
#line 3579 "compiler/glsl/glsl_parser.cpp"
break;
case 30:
#line 475 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      linear_ctx *ctx = state->linalloc;
      yyval.expression = new(ctx) ast_expression(ast_float_constant, NULL, NULL, NULL);
      yyval.expression->set_location(yystack.p_mark[0]);
      yyval.expression->primary_expression.float_constant = yystack.l_mark[0].real;
   }
#line 3589 "compiler/glsl/glsl_parser.cpp"
break;
case 31:
#line 482 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      linear_ctx *ctx = state->linalloc;
      yyval.expression = new(ctx) ast_expression(ast_double_constant, NULL, NULL, NULL);
      yyval.expression->set_location(yystack.p_mark[0]);
      yyval.expression->primary_expression.double_constant = yystack.l_mark[0].dreal;
   }
#line 3599 "compiler/glsl/glsl_parser.cpp"
break;
case 32:
#line 489 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      linear_ctx *ctx = state->linalloc;
      yyval.expression = new(ctx) ast_expression(ast_bool_constant, NULL, NULL, NULL);
      yyval.expression->set_location(yystack.p_mark[0]);
      yyval.expression->primary_expression.bool_constant = yystack.l_mark[0].n;
   }
#line 3609 "compiler/glsl/glsl_parser.cpp"
break;
case 33:
#line 496 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      yyval.expression = yystack.l_mark[-1].expression;
   }
#line 3616 "compiler/glsl/glsl_parser.cpp"
break;
case 35:
#line 504 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      linear_ctx *ctx = state->linalloc;
      yyval.expression = new(ctx) ast_expression(ast_array_index, yystack.l_mark[-3].expression, yystack.l_mark[-1].expression, NULL);
      yyval.expression->set_location_range(yystack.p_mark[-3], yystack.p_mark[0]);
   }
#line 3625 "compiler/glsl/glsl_parser.cpp"
break;
case 36:
#line 510 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      yyval.expression = yystack.l_mark[0].expression;
   }
#line 3632 "compiler/glsl/glsl_parser.cpp"
break;
case 37:
#line 514 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      linear_ctx *ctx = state->linalloc;
      yyval.expression = new(ctx) ast_expression(ast_field_selection, yystack.l_mark[-2].expression, NULL, NULL);
      yyval.expression->set_location_range(yystack.p_mark[-2], yystack.p_mark[0]);
      yyval.expression->primary_expression.identifier = yystack.l_mark[0].identifier;
   }
#line 3642 "compiler/glsl/glsl_parser.cpp"
break;
case 38:
#line 521 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      linear_ctx *ctx = state->linalloc;
      yyval.expression = new(ctx) ast_expression(ast_post_inc, yystack.l_mark[-1].expression, NULL, NULL);
      yyval.expression->set_location_range(yystack.p_mark[-1], yystack.p_mark[0]);
   }
#line 3651 "compiler/glsl/glsl_parser.cpp"
break;
case 39:
#line 527 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      linear_ctx *ctx = state->linalloc;
      yyval.expression = new(ctx) ast_expression(ast_post_dec, yystack.l_mark[-1].expression, NULL, NULL);
      yyval.expression->set_location_range(yystack.p_mark[-1], yystack.p_mark[0]);
   }
#line 3660 "compiler/glsl/glsl_parser.cpp"
break;
case 47:
#line 558 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      yyval.expression = yystack.l_mark[-1].expression;
      yyval.expression->set_location(yystack.p_mark[-1]);
      yyval.expression->expressions.push_tail(& yystack.l_mark[0].expression->link);
   }
#line 3669 "compiler/glsl/glsl_parser.cpp"
break;
case 48:
#line 564 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      yyval.expression = yystack.l_mark[-2].expression;
      yyval.expression->set_location(yystack.p_mark[-2]);
      yyval.expression->expressions.push_tail(& yystack.l_mark[0].expression->link);
   }
#line 3678 "compiler/glsl/glsl_parser.cpp"
break;
case 50:
#line 580 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      linear_ctx *ctx = state->linalloc;
      yyval.expression = new(ctx) ast_function_expression(yystack.l_mark[0].type_specifier);
      yyval.expression->set_location(yystack.p_mark[0]);
      }
#line 3687 "compiler/glsl/glsl_parser.cpp"
break;
case 51:
#line 586 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      linear_ctx *ctx = state->linalloc;
      yyval.expression = new(ctx) ast_function_expression(yystack.l_mark[0].expression);
      yyval.expression->set_location(yystack.p_mark[0]);
      }
#line 3696 "compiler/glsl/glsl_parser.cpp"
break;
case 53:
#line 601 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      linear_ctx *ctx = state->linalloc;
      yyval.expression = new(ctx) ast_expression(ast_pre_inc, yystack.l_mark[0].expression, NULL, NULL);
      yyval.expression->set_location(yystack.p_mark[-1]);
   }
#line 3705 "compiler/glsl/glsl_parser.cpp"
break;
case 54:
#line 607 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      linear_ctx *ctx = state->linalloc;
      yyval.expression = new(ctx) ast_expression(ast_pre_dec, yystack.l_mark[0].expression, NULL, NULL);
      yyval.expression->set_location(yystack.p_mark[-1]);
   }
#line 3714 "compiler/glsl/glsl_parser.cpp"
break;
case 55:
#line 613 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      linear_ctx *ctx = state->linalloc;
      yyval.expression = new(ctx) ast_expression(yystack.l_mark[-1].n, yystack.l_mark[0].expression, NULL, NULL);
      yyval.expression->set_location_range(yystack.p_mark[-1], yystack.p_mark[0]);
   }
#line 3723 "compiler/glsl/glsl_parser.cpp"
break;
case 56:
#line 622 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{ yyval.n = ast_plus; }
#line 3728 "compiler/glsl/glsl_parser.cpp"
break;
case 57:
#line 623 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{ yyval.n = ast_neg; }
#line 3733 "compiler/glsl/glsl_parser.cpp"
break;
case 58:
#line 624 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{ yyval.n = ast_logic_not; }
#line 3738 "compiler/glsl/glsl_parser.cpp"
break;
case 59:
#line 625 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{ yyval.n = ast_bit_not; }
#line 3743 "compiler/glsl/glsl_parser.cpp"
break;
case 61:
#line 631 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      linear_ctx *ctx = state->linalloc;
      yyval.expression = new(ctx) ast_expression_bin(ast_mul, yystack.l_mark[-2].expression, yystack.l_mark[0].expression);
      yyval.expression->set_location_range(yystack.p_mark[-2], yystack.p_mark[0]);
   }
#line 3752 "compiler/glsl/glsl_parser.cpp"
break;
case 62:
#line 637 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      linear_ctx *ctx = state->linalloc;
      yyval.expression = new(ctx) ast_expression_bin(ast_div, yystack.l_mark[-2].expression, yystack.l_mark[0].expression);
      yyval.expression->set_location_range(yystack.p_mark[-2], yystack.p_mark[0]);
   }
#line 3761 "compiler/glsl/glsl_parser.cpp"
break;
case 63:
#line 643 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      linear_ctx *ctx = state->linalloc;
      yyval.expression = new(ctx) ast_expression_bin(ast_mod, yystack.l_mark[-2].expression, yystack.l_mark[0].expression);
      yyval.expression->set_location_range(yystack.p_mark[-2], yystack.p_mark[0]);
   }
#line 3770 "compiler/glsl/glsl_parser.cpp"
break;
case 65:
#line 653 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      linear_ctx *ctx = state->linalloc;
      yyval.expression = new(ctx) ast_expression_bin(ast_add, yystack.l_mark[-2].expression, yystack.l_mark[0].expression);
      yyval.expression->set_location_range(yystack.p_mark[-2], yystack.p_mark[0]);
   }
#line 3779 "compiler/glsl/glsl_parser.cpp"
break;
case 66:
#line 659 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      linear_ctx *ctx = state->linalloc;
      yyval.expression = new(ctx) ast_expression_bin(ast_sub, yystack.l_mark[-2].expression, yystack.l_mark[0].expression);
      yyval.expression->set_location_range(yystack.p_mark[-2], yystack.p_mark[0]);
   }
#line 3788 "compiler/glsl/glsl_parser.cpp"
break;
case 68:
#line 669 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      linear_ctx *ctx = state->linalloc;
      yyval.expression = new(ctx) ast_expression_bin(ast_lshift, yystack.l_mark[-2].expression, yystack.l_mark[0].expression);
      yyval.expression->set_location_range(yystack.p_mark[-2], yystack.p_mark[0]);
   }
#line 3797 "compiler/glsl/glsl_parser.cpp"
break;
case 69:
#line 675 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      linear_ctx *ctx = state->linalloc;
      yyval.expression = new(ctx) ast_expression_bin(ast_rshift, yystack.l_mark[-2].expression, yystack.l_mark[0].expression);
      yyval.expression->set_location_range(yystack.p_mark[-2], yystack.p_mark[0]);
   }
#line 3806 "compiler/glsl/glsl_parser.cpp"
break;
case 71:
#line 685 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      linear_ctx *ctx = state->linalloc;
      yyval.expression = new(ctx) ast_expression_bin(ast_less, yystack.l_mark[-2].expression, yystack.l_mark[0].expression);
      yyval.expression->set_location_range(yystack.p_mark[-2], yystack.p_mark[0]);
   }
#line 3815 "compiler/glsl/glsl_parser.cpp"
break;
case 72:
#line 691 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      linear_ctx *ctx = state->linalloc;
      yyval.expression = new(ctx) ast_expression_bin(ast_greater, yystack.l_mark[-2].expression, yystack.l_mark[0].expression);
      yyval.expression->set_location_range(yystack.p_mark[-2], yystack.p_mark[0]);
   }
#line 3824 "compiler/glsl/glsl_parser.cpp"
break;
case 73:
#line 697 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      linear_ctx *ctx = state->linalloc;
      yyval.expression = new(ctx) ast_expression_bin(ast_lequal, yystack.l_mark[-2].expression, yystack.l_mark[0].expression);
      yyval.expression->set_location_range(yystack.p_mark[-2], yystack.p_mark[0]);
   }
#line 3833 "compiler/glsl/glsl_parser.cpp"
break;
case 74:
#line 703 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      linear_ctx *ctx = state->linalloc;
      yyval.expression = new(ctx) ast_expression_bin(ast_gequal, yystack.l_mark[-2].expression, yystack.l_mark[0].expression);
      yyval.expression->set_location_range(yystack.p_mark[-2], yystack.p_mark[0]);
   }
#line 3842 "compiler/glsl/glsl_parser.cpp"
break;
case 76:
#line 713 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      linear_ctx *ctx = state->linalloc;
      yyval.expression = new(ctx) ast_expression_bin(ast_equal, yystack.l_mark[-2].expression, yystack.l_mark[0].expression);
      yyval.expression->set_location_range(yystack.p_mark[-2], yystack.p_mark[0]);
   }
#line 3851 "compiler/glsl/glsl_parser.cpp"
break;
case 77:
#line 719 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      linear_ctx *ctx = state->linalloc;
      yyval.expression = new(ctx) ast_expression_bin(ast_nequal, yystack.l_mark[-2].expression, yystack.l_mark[0].expression);
      yyval.expression->set_location_range(yystack.p_mark[-2], yystack.p_mark[0]);
   }
#line 3860 "compiler/glsl/glsl_parser.cpp"
break;
case 79:
#line 729 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      linear_ctx *ctx = state->linalloc;
      yyval.expression = new(ctx) ast_expression_bin(ast_bit_and, yystack.l_mark[-2].expression, yystack.l_mark[0].expression);
      yyval.expression->set_location_range(yystack.p_mark[-2], yystack.p_mark[0]);
   }
#line 3869 "compiler/glsl/glsl_parser.cpp"
break;
case 81:
#line 739 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      linear_ctx *ctx = state->linalloc;
      yyval.expression = new(ctx) ast_expression_bin(ast_bit_xor, yystack.l_mark[-2].expression, yystack.l_mark[0].expression);
      yyval.expression->set_location_range(yystack.p_mark[-2], yystack.p_mark[0]);
   }
#line 3878 "compiler/glsl/glsl_parser.cpp"
break;
case 83:
#line 749 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      linear_ctx *ctx = state->linalloc;
      yyval.expression = new(ctx) ast_expression_bin(ast_bit_or, yystack.l_mark[-2].expression, yystack.l_mark[0].expression);
      yyval.expression->set_location_range(yystack.p_mark[-2], yystack.p_mark[0]);
   }
#line 3887 "compiler/glsl/glsl_parser.cpp"
break;
case 85:
#line 759 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      linear_ctx *ctx = state->linalloc;
      yyval.expression = new(ctx) ast_expression_bin(ast_logic_and, yystack.l_mark[-2].expression, yystack.l_mark[0].expression);
      yyval.expression->set_location_range(yystack.p_mark[-2], yystack.p_mark[0]);
   }
#line 3896 "compiler/glsl/glsl_parser.cpp"
break;
case 87:
#line 769 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      linear_ctx *ctx = state->linalloc;
      yyval.expression = new(ctx) ast_expression_bin(ast_logic_xor, yystack.l_mark[-2].expression, yystack.l_mark[0].expression);
      yyval.expression->set_location_range(yystack.p_mark[-2], yystack.p_mark[0]);
   }
#line 3905 "compiler/glsl/glsl_parser.cpp"
break;
case 89:
#line 779 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      linear_ctx *ctx = state->linalloc;
      yyval.expression = new(ctx) ast_expression_bin(ast_logic_or, yystack.l_mark[-2].expression, yystack.l_mark[0].expression);
      yyval.expression->set_location_range(yystack.p_mark[-2], yystack.p_mark[0]);
   }
#line 3914 "compiler/glsl/glsl_parser.cpp"
break;
case 91:
#line 789 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      linear_ctx *ctx = state->linalloc;
      yyval.expression = new(ctx) ast_expression(ast_conditional, yystack.l_mark[-4].expression, yystack.l_mark[-2].expression, yystack.l_mark[0].expression);
      yyval.expression->set_location_range(yystack.p_mark[-4], yystack.p_mark[0]);
   }
#line 3923 "compiler/glsl/glsl_parser.cpp"
break;
case 93:
#line 799 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      linear_ctx *ctx = state->linalloc;
      yyval.expression = new(ctx) ast_expression(yystack.l_mark[-1].n, yystack.l_mark[-2].expression, yystack.l_mark[0].expression, NULL);
      yyval.expression->set_location_range(yystack.p_mark[-2], yystack.p_mark[0]);
   }
#line 3932 "compiler/glsl/glsl_parser.cpp"
break;
case 94:
#line 807 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{ yyval.n = ast_assign; }
#line 3937 "compiler/glsl/glsl_parser.cpp"
break;
case 95:
#line 808 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{ yyval.n = ast_mul_assign; }
#line 3942 "compiler/glsl/glsl_parser.cpp"
break;
case 96:
#line 809 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{ yyval.n = ast_div_assign; }
#line 3947 "compiler/glsl/glsl_parser.cpp"
break;
case 97:
#line 810 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{ yyval.n = ast_mod_assign; }
#line 3952 "compiler/glsl/glsl_parser.cpp"
break;
case 98:
#line 811 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{ yyval.n = ast_add_assign; }
#line 3957 "compiler/glsl/glsl_parser.cpp"
break;
case 99:
#line 812 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{ yyval.n = ast_sub_assign; }
#line 3962 "compiler/glsl/glsl_parser.cpp"
break;
case 100:
#line 813 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{ yyval.n = ast_ls_assign; }
#line 3967 "compiler/glsl/glsl_parser.cpp"
break;
case 101:
#line 814 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{ yyval.n = ast_rs_assign; }
#line 3972 "compiler/glsl/glsl_parser.cpp"
break;
case 102:
#line 815 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{ yyval.n = ast_and_assign; }
#line 3977 "compiler/glsl/glsl_parser.cpp"
break;
case 103:
#line 816 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{ yyval.n = ast_xor_assign; }
#line 3982 "compiler/glsl/glsl_parser.cpp"
break;
case 104:
#line 817 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{ yyval.n = ast_or_assign; }
#line 3987 "compiler/glsl/glsl_parser.cpp"
break;
case 105:
#line 822 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      yyval.expression = yystack.l_mark[0].expression;
   }
#line 3994 "compiler/glsl/glsl_parser.cpp"
break;
case 106:
#line 826 "../mesa/src/compiler/glsl/glsl_parser.yy"
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
#line 4010 "compiler/glsl/glsl_parser.cpp"
break;
case 108:
#line 846 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      state->symbols->pop_scope();
      yyval.node = yystack.l_mark[-1].function;
   }
#line 4018 "compiler/glsl/glsl_parser.cpp"
break;
case 109:
#line 851 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      yyval.node = yystack.l_mark[-1].declarator_list;
   }
#line 4025 "compiler/glsl/glsl_parser.cpp"
break;
case 110:
#line 855 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      yystack.l_mark[-1].type_specifier->default_precision = yystack.l_mark[-2].n;
      yyval.node = yystack.l_mark[-1].type_specifier;
   }
#line 4033 "compiler/glsl/glsl_parser.cpp"
break;
case 111:
#line 860 "../mesa/src/compiler/glsl/glsl_parser.yy"
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
#line 4050 "compiler/glsl/glsl_parser.cpp"
break;
case 115:
#line 886 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      yyval.function = yystack.l_mark[-1].function;
      yyval.function->parameters.push_tail(& yystack.l_mark[0].parameter_declarator->link);
   }
#line 4058 "compiler/glsl/glsl_parser.cpp"
break;
case 116:
#line 891 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      yyval.function = yystack.l_mark[-2].function;
      yyval.function->parameters.push_tail(& yystack.l_mark[0].parameter_declarator->link);
   }
#line 4066 "compiler/glsl/glsl_parser.cpp"
break;
case 117:
#line 899 "../mesa/src/compiler/glsl/glsl_parser.yy"
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
         state->symbols->add_function(new(ctx) ir_function(yystack.l_mark[-1].identifier));
      state->symbols->push_scope();
   }
#line 4084 "compiler/glsl/glsl_parser.cpp"
break;
case 118:
#line 917 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      linear_ctx *ctx = state->linalloc;
      yyval.parameter_declarator = new(ctx) ast_parameter_declarator();
      yyval.parameter_declarator->set_location_range(yystack.p_mark[-1], yystack.p_mark[0]);
      yyval.parameter_declarator->type = new(ctx) ast_fully_specified_type();
      yyval.parameter_declarator->type->set_location(yystack.p_mark[-1]);
      yyval.parameter_declarator->type->specifier = yystack.l_mark[-1].type_specifier;
      yyval.parameter_declarator->identifier = yystack.l_mark[0].identifier;
      state->symbols->add_variable(new(ctx) ir_variable(NULL, yystack.l_mark[0].identifier, ir_var_auto));
   }
#line 4098 "compiler/glsl/glsl_parser.cpp"
break;
case 119:
#line 928 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      _mesa_glsl_error(&yystack.p_mark[-2], state, "is is not allowed on function parameter");
      YYERROR;
   }
#line 4106 "compiler/glsl/glsl_parser.cpp"
break;
case 120:
#line 933 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      linear_ctx *ctx = state->linalloc;
      yyval.parameter_declarator = new(ctx) ast_parameter_declarator();
      yyval.parameter_declarator->set_location_range(yystack.p_mark[-2], yystack.p_mark[0]);
      yyval.parameter_declarator->type = new(ctx) ast_fully_specified_type();
      yyval.parameter_declarator->type->set_location(yystack.p_mark[-2]);
      yyval.parameter_declarator->type->specifier = yystack.l_mark[-2].type_specifier;
      yyval.parameter_declarator->identifier = yystack.l_mark[-1].identifier;
      yyval.parameter_declarator->array_specifier = yystack.l_mark[0].array_specifier;
      state->symbols->add_variable(new(ctx) ir_variable(NULL, yystack.l_mark[-1].identifier, ir_var_auto));
   }
#line 4121 "compiler/glsl/glsl_parser.cpp"
break;
case 121:
#line 948 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      yyval.parameter_declarator = yystack.l_mark[0].parameter_declarator;
      yyval.parameter_declarator->type->qualifier = yystack.l_mark[-1].type_qualifier;
      if (!yyval.parameter_declarator->type->qualifier.push_to_global(& yystack.p_mark[-1], state)) {
         YYERROR;
      }
   }
#line 4132 "compiler/glsl/glsl_parser.cpp"
break;
case 122:
#line 956 "../mesa/src/compiler/glsl/glsl_parser.yy"
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
#line 4148 "compiler/glsl/glsl_parser.cpp"
break;
case 123:
#line 972 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      memset(& yyval.type_qualifier, 0, sizeof(yyval.type_qualifier));
   }
#line 4155 "compiler/glsl/glsl_parser.cpp"
break;
case 124:
#line 976 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      if (yystack.l_mark[0].type_qualifier.flags.q.constant)
         _mesa_glsl_error(&yystack.p_mark[-1], state, "duplicate const qualifier");

      yyval.type_qualifier = yystack.l_mark[0].type_qualifier;
      yyval.type_qualifier.flags.q.constant = 1;
   }
#line 4166 "compiler/glsl/glsl_parser.cpp"
break;
case 125:
#line 984 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      if (yystack.l_mark[0].type_qualifier.flags.q.precise)
         _mesa_glsl_error(&yystack.p_mark[-1], state, "duplicate precise qualifier");

      yyval.type_qualifier = yystack.l_mark[0].type_qualifier;
      yyval.type_qualifier.flags.q.precise = 1;
   }
#line 4177 "compiler/glsl/glsl_parser.cpp"
break;
case 126:
#line 992 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      if ((yystack.l_mark[-1].type_qualifier.flags.q.in || yystack.l_mark[-1].type_qualifier.flags.q.out) && (yystack.l_mark[0].type_qualifier.flags.q.in || yystack.l_mark[0].type_qualifier.flags.q.out))
         _mesa_glsl_error(&yystack.p_mark[-1], state, "duplicate in/out/inout qualifier");

      if (!state->has_420pack_or_es31() && yystack.l_mark[0].type_qualifier.flags.q.constant)
         _mesa_glsl_error(&yystack.p_mark[-1], state, "in/out/inout must come after const "
                                      "or precise");

      yyval.type_qualifier = yystack.l_mark[-1].type_qualifier;
      yyval.type_qualifier.merge_qualifier(&yystack.p_mark[-1], state, yystack.l_mark[0].type_qualifier, false);
   }
#line 4192 "compiler/glsl/glsl_parser.cpp"
break;
case 127:
#line 1004 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      if (yystack.l_mark[0].type_qualifier.precision != ast_precision_none)
         _mesa_glsl_error(&yystack.p_mark[-1], state, "duplicate precision qualifier");

      if (!state->has_420pack_or_es31() &&
          yystack.l_mark[0].type_qualifier.flags.i != 0)
         _mesa_glsl_error(&yystack.p_mark[-1], state, "precision qualifiers must come last");

      yyval.type_qualifier = yystack.l_mark[0].type_qualifier;
      yyval.type_qualifier.precision = yystack.l_mark[-1].n;
   }
#line 4207 "compiler/glsl/glsl_parser.cpp"
break;
case 128:
#line 1016 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      yyval.type_qualifier = yystack.l_mark[-1].type_qualifier;
      yyval.type_qualifier.merge_qualifier(&yystack.p_mark[-1], state, yystack.l_mark[0].type_qualifier, false);
   }
#line 4215 "compiler/glsl/glsl_parser.cpp"
break;
case 129:
#line 1023 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      memset(& yyval.type_qualifier, 0, sizeof(yyval.type_qualifier));
      yyval.type_qualifier.flags.q.in = 1;
   }
#line 4223 "compiler/glsl/glsl_parser.cpp"
break;
case 130:
#line 1028 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      memset(& yyval.type_qualifier, 0, sizeof(yyval.type_qualifier));
      yyval.type_qualifier.flags.q.out = 1;
   }
#line 4231 "compiler/glsl/glsl_parser.cpp"
break;
case 131:
#line 1033 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      memset(& yyval.type_qualifier, 0, sizeof(yyval.type_qualifier));
      yyval.type_qualifier.flags.q.in = 1;
      yyval.type_qualifier.flags.q.out = 1;
   }
#line 4240 "compiler/glsl/glsl_parser.cpp"
break;
case 134:
#line 1047 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      linear_ctx *ctx = state->linalloc;
      ast_declaration *decl = new(ctx) ast_declaration(yystack.l_mark[0].identifier, NULL, NULL);
      decl->set_location(yystack.p_mark[0]);

      yyval.declarator_list = yystack.l_mark[-2].declarator_list;
      yyval.declarator_list->declarations.push_tail(&decl->link);
      state->symbols->add_variable(new(ctx) ir_variable(NULL, yystack.l_mark[0].identifier, ir_var_auto));
   }
#line 4253 "compiler/glsl/glsl_parser.cpp"
break;
case 135:
#line 1057 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      linear_ctx *ctx = state->linalloc;
      ast_declaration *decl = new(ctx) ast_declaration(yystack.l_mark[-1].identifier, yystack.l_mark[0].array_specifier, NULL);
      decl->set_location_range(yystack.p_mark[-1], yystack.p_mark[0]);

      yyval.declarator_list = yystack.l_mark[-3].declarator_list;
      yyval.declarator_list->declarations.push_tail(&decl->link);
      state->symbols->add_variable(new(ctx) ir_variable(NULL, yystack.l_mark[-1].identifier, ir_var_auto));
   }
#line 4266 "compiler/glsl/glsl_parser.cpp"
break;
case 136:
#line 1067 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      linear_ctx *ctx = state->linalloc;
      ast_declaration *decl = new(ctx) ast_declaration(yystack.l_mark[-3].identifier, yystack.l_mark[-2].array_specifier, yystack.l_mark[0].expression);
      decl->set_location_range(yystack.p_mark[-3], yystack.p_mark[-2]);

      yyval.declarator_list = yystack.l_mark[-5].declarator_list;
      yyval.declarator_list->declarations.push_tail(&decl->link);
      state->symbols->add_variable(new(ctx) ir_variable(NULL, yystack.l_mark[-3].identifier, ir_var_auto));
   }
#line 4279 "compiler/glsl/glsl_parser.cpp"
break;
case 137:
#line 1077 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      linear_ctx *ctx = state->linalloc;
      ast_declaration *decl = new(ctx) ast_declaration(yystack.l_mark[-2].identifier, NULL, yystack.l_mark[0].expression);
      decl->set_location(yystack.p_mark[-2]);

      yyval.declarator_list = yystack.l_mark[-4].declarator_list;
      yyval.declarator_list->declarations.push_tail(&decl->link);
      state->symbols->add_variable(new(ctx) ir_variable(NULL, yystack.l_mark[-2].identifier, ir_var_auto));
   }
#line 4292 "compiler/glsl/glsl_parser.cpp"
break;
case 138:
#line 1091 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      linear_ctx *ctx = state->linalloc;
      /* Empty declaration list is valid. */
      yyval.declarator_list = new(ctx) ast_declarator_list(yystack.l_mark[0].fully_specified_type);
      yyval.declarator_list->set_location(yystack.p_mark[0]);
   }
#line 4302 "compiler/glsl/glsl_parser.cpp"
break;
case 139:
#line 1098 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      linear_ctx *ctx = state->linalloc;
      ast_declaration *decl = new(ctx) ast_declaration(yystack.l_mark[0].identifier, NULL, NULL);
      decl->set_location(yystack.p_mark[0]);

      yyval.declarator_list = new(ctx) ast_declarator_list(yystack.l_mark[-1].fully_specified_type);
      yyval.declarator_list->set_location_range(yystack.p_mark[-1], yystack.p_mark[0]);
      yyval.declarator_list->declarations.push_tail(&decl->link);
      state->symbols->add_variable(new(ctx) ir_variable(NULL, yystack.l_mark[0].identifier, ir_var_auto));
   }
#line 4316 "compiler/glsl/glsl_parser.cpp"
break;
case 140:
#line 1109 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      linear_ctx *ctx = state->linalloc;
      ast_declaration *decl = new(ctx) ast_declaration(yystack.l_mark[-1].identifier, yystack.l_mark[0].array_specifier, NULL);
      decl->set_location_range(yystack.p_mark[-1], yystack.p_mark[0]);

      yyval.declarator_list = new(ctx) ast_declarator_list(yystack.l_mark[-2].fully_specified_type);
      yyval.declarator_list->set_location_range(yystack.p_mark[-2], yystack.p_mark[0]);
      yyval.declarator_list->declarations.push_tail(&decl->link);
      state->symbols->add_variable(new(ctx) ir_variable(NULL, yystack.l_mark[-1].identifier, ir_var_auto));
   }
#line 4330 "compiler/glsl/glsl_parser.cpp"
break;
case 141:
#line 1120 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      linear_ctx *ctx = state->linalloc;
      ast_declaration *decl = new(ctx) ast_declaration(yystack.l_mark[-3].identifier, yystack.l_mark[-2].array_specifier, yystack.l_mark[0].expression);
      decl->set_location_range(yystack.p_mark[-3], yystack.p_mark[-2]);

      yyval.declarator_list = new(ctx) ast_declarator_list(yystack.l_mark[-4].fully_specified_type);
      yyval.declarator_list->set_location_range(yystack.p_mark[-4], yystack.p_mark[-2]);
      yyval.declarator_list->declarations.push_tail(&decl->link);
      state->symbols->add_variable(new(ctx) ir_variable(NULL, yystack.l_mark[-3].identifier, ir_var_auto));
   }
#line 4344 "compiler/glsl/glsl_parser.cpp"
break;
case 142:
#line 1131 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      linear_ctx *ctx = state->linalloc;
      ast_declaration *decl = new(ctx) ast_declaration(yystack.l_mark[-2].identifier, NULL, yystack.l_mark[0].expression);
      decl->set_location(yystack.p_mark[-2]);

      yyval.declarator_list = new(ctx) ast_declarator_list(yystack.l_mark[-3].fully_specified_type);
      yyval.declarator_list->set_location_range(yystack.p_mark[-3], yystack.p_mark[-2]);
      yyval.declarator_list->declarations.push_tail(&decl->link);
      state->symbols->add_variable(new(ctx) ir_variable(NULL, yystack.l_mark[-2].identifier, ir_var_auto));
   }
#line 4358 "compiler/glsl/glsl_parser.cpp"
break;
case 143:
#line 1142 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      linear_ctx *ctx = state->linalloc;
      ast_declaration *decl = new(ctx) ast_declaration(yystack.l_mark[0].identifier, NULL, NULL);
      decl->set_location(yystack.p_mark[0]);

      yyval.declarator_list = new(ctx) ast_declarator_list(NULL);
      yyval.declarator_list->set_location_range(yystack.p_mark[-1], yystack.p_mark[0]);
      yyval.declarator_list->invariant = true;

      yyval.declarator_list->declarations.push_tail(&decl->link);
   }
#line 4373 "compiler/glsl/glsl_parser.cpp"
break;
case 144:
#line 1154 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      linear_ctx *ctx = state->linalloc;
      ast_declaration *decl = new(ctx) ast_declaration(yystack.l_mark[0].identifier, NULL, NULL);
      decl->set_location(yystack.p_mark[0]);

      yyval.declarator_list = new(ctx) ast_declarator_list(NULL);
      yyval.declarator_list->set_location_range(yystack.p_mark[-1], yystack.p_mark[0]);
      yyval.declarator_list->precise = true;

      yyval.declarator_list->declarations.push_tail(&decl->link);
   }
#line 4388 "compiler/glsl/glsl_parser.cpp"
break;
case 145:
#line 1169 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      linear_ctx *ctx = state->linalloc;
      yyval.fully_specified_type = new(ctx) ast_fully_specified_type();
      yyval.fully_specified_type->set_location(yystack.p_mark[0]);
      yyval.fully_specified_type->specifier = yystack.l_mark[0].type_specifier;
   }
#line 4398 "compiler/glsl/glsl_parser.cpp"
break;
case 146:
#line 1176 "../mesa/src/compiler/glsl/glsl_parser.yy"
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
#line 4416 "compiler/glsl/glsl_parser.cpp"
break;
case 147:
#line 1194 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      yyval.type_qualifier = yystack.l_mark[-1].type_qualifier;
   }
#line 4423 "compiler/glsl/glsl_parser.cpp"
break;
case 149:
#line 1202 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      yyval.type_qualifier = yystack.l_mark[-2].type_qualifier;
      if (!yyval.type_qualifier.merge_qualifier(& yystack.p_mark[0], state, yystack.l_mark[0].type_qualifier, true)) {
         YYERROR;
      }
   }
#line 4433 "compiler/glsl/glsl_parser.cpp"
break;
case 150:
#line 1212 "../mesa/src/compiler/glsl/glsl_parser.yy"
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
             !state->has_tessellation_shader() && !state->EXT_mesh_shader_enable) {
            _mesa_glsl_error(& yystack.p_mark[0], state, "#version 150 layout "
                             "qualifier `%s' used", yystack.l_mark[0].identifier);
         }
      }

      /* Layout qualifiers for ARB_shader_image_load_store. */
      if (state->has_shader_image_load_store() ||
          state->EXT_shader_pixel_local_storage_enable) {
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
               /* for __pixel_localEXT */
               bool pixel_local_qualifiers;
            } map[] = {
               { "rgba32f", PIPE_FORMAT_R32G32B32A32_FLOAT, GLSL_TYPE_FLOAT, 130, 310, false, false, false },
               { "rgba16f", PIPE_FORMAT_R16G16B16A16_FLOAT, GLSL_TYPE_FLOAT, 130, 310, false, false, false },
               { "rg32f", PIPE_FORMAT_R32G32_FLOAT, GLSL_TYPE_FLOAT, 130, 0, true, false, false },
               { "rg16f", PIPE_FORMAT_R16G16_FLOAT, GLSL_TYPE_FLOAT, 130, 0, true, false, true },
               { "r11f_g11f_b10f", PIPE_FORMAT_R11G11B10_FLOAT, GLSL_TYPE_FLOAT, 130, 0, true, false, true },
               { "r32f", PIPE_FORMAT_R32_FLOAT, GLSL_TYPE_FLOAT, 130, 310, false, false, true },
               { "r16f", PIPE_FORMAT_R16_FLOAT, GLSL_TYPE_FLOAT, 130, 0, true, false, false },
               { "rgba32ui", PIPE_FORMAT_R32G32B32A32_UINT, GLSL_TYPE_UINT, 130, 310, false, false, false },
               { "rgba16ui", PIPE_FORMAT_R16G16B16A16_UINT, GLSL_TYPE_UINT, 130, 310, false, false, false },
               { "rgb10_a2ui", PIPE_FORMAT_R10G10B10A2_UINT, GLSL_TYPE_UINT, 130, 0, true, false, true },
               { "rgba8ui", PIPE_FORMAT_R8G8B8A8_UINT, GLSL_TYPE_UINT, 130, 310, false, false, true },
               { "rg32ui", PIPE_FORMAT_R32G32_UINT, GLSL_TYPE_UINT, 130, 0, true, false, false },
               { "rg16ui", PIPE_FORMAT_R16G16_UINT, GLSL_TYPE_UINT, 130, 0, true, false, true },
               { "rg8ui", PIPE_FORMAT_R8G8_UINT, GLSL_TYPE_UINT, 130, 0, true, false, false },
               { "r32ui", PIPE_FORMAT_R32_UINT, GLSL_TYPE_UINT, 130, 310, false, false, true },
               { "r16ui", PIPE_FORMAT_R16_UINT, GLSL_TYPE_UINT, 130, 0, true, false, false },
               { "r8ui", PIPE_FORMAT_R8_UINT, GLSL_TYPE_UINT, 130, 0, true, false, false },
               { "rgba32i", PIPE_FORMAT_R32G32B32A32_SINT, GLSL_TYPE_INT, 130, 310, false, false, false },
               { "rgba16i", PIPE_FORMAT_R16G16B16A16_SINT, GLSL_TYPE_INT, 130, 310, false, false, false },
               { "rgba8i", PIPE_FORMAT_R8G8B8A8_SINT, GLSL_TYPE_INT, 130, 310, false, false, true },
               { "rg32i", PIPE_FORMAT_R32G32_SINT, GLSL_TYPE_INT, 130, 0, true, false, false },
               { "rg16i", PIPE_FORMAT_R16G16_SINT, GLSL_TYPE_INT, 130, 0, true, false, true },
               { "rg8i", PIPE_FORMAT_R8G8_SINT, GLSL_TYPE_INT, 130, 0, true, false, false },
               { "r32i", PIPE_FORMAT_R32_SINT, GLSL_TYPE_INT, 130, 310, false, false, true },
               { "r16i", PIPE_FORMAT_R16_SINT, GLSL_TYPE_INT, 130, 0, true, false, false },
               { "r8i", PIPE_FORMAT_R8_SINT, GLSL_TYPE_INT, 130, 0, true, false, false },
               { "rgba16", PIPE_FORMAT_R16G16B16A16_UNORM, GLSL_TYPE_FLOAT, 130, 0, true, false, false },
               { "rgb10_a2", PIPE_FORMAT_R10G10B10A2_UNORM, GLSL_TYPE_FLOAT, 130, 0, true, false, true },
               { "rgba8", PIPE_FORMAT_R8G8B8A8_UNORM, GLSL_TYPE_FLOAT, 130, 310, false, false, true },
               { "rg16", PIPE_FORMAT_R16G16_UNORM, GLSL_TYPE_FLOAT, 130, 0, true, false, true },
               { "rg8", PIPE_FORMAT_R8G8_UNORM, GLSL_TYPE_FLOAT, 130, 0, true, false, false },
               { "r16", PIPE_FORMAT_R16_UNORM, GLSL_TYPE_FLOAT, 130, 0, true, false, false },
               { "r8", PIPE_FORMAT_R8_UNORM, GLSL_TYPE_FLOAT, 130, 0, true, false, false },
               { "rgba16_snorm", PIPE_FORMAT_R16G16B16A16_SNORM, GLSL_TYPE_FLOAT, 130, 0, true, false, false },
               { "rgba8_snorm", PIPE_FORMAT_R8G8B8A8_SNORM, GLSL_TYPE_FLOAT, 130, 310, false, false, false },
               { "rg16_snorm", PIPE_FORMAT_R16G16_SNORM, GLSL_TYPE_FLOAT, 130, 0, true, false, false },
               { "rg8_snorm", PIPE_FORMAT_R8G8_SNORM, GLSL_TYPE_FLOAT, 130, 0, true, false, false },
               { "r16_snorm", PIPE_FORMAT_R16_SNORM, GLSL_TYPE_FLOAT, 130, 0, true, false, false },
               { "r8_snorm", PIPE_FORMAT_R8_SNORM, GLSL_TYPE_FLOAT, 130, 0, true, false, false },

               /* From GL_EXT_shader_image_load_store: */
               /* base_type is incorrect but it'll be patched later when we know
                * the variable type. See ast_to_hir.cpp */
               { "size1x8", PIPE_FORMAT_R8_SINT, GLSL_TYPE_VOID, 130, 0, false, true, false },
               { "size1x16", PIPE_FORMAT_R16_SINT, GLSL_TYPE_VOID, 130, 0, false, true, false },
               { "size1x32", PIPE_FORMAT_R32_SINT, GLSL_TYPE_VOID, 130, 0, false, true, false },
               { "size2x32", PIPE_FORMAT_R32G32_SINT, GLSL_TYPE_VOID, 130, 0, false, true, false },
               { "size4x32", PIPE_FORMAT_R32G32B32A32_SINT, GLSL_TYPE_VOID, 130, 0, false, true, false },
            };

            for (unsigned i = 0; i < ARRAY_SIZE(map); i++) {
               if (state->EXT_shader_pixel_local_storage_enable &&
                   map[i].pixel_local_qualifiers &&
                   match_layout_qualifier(yystack.l_mark[0].identifier, map[i].name, state) == 0) {
                  yyval.type_qualifier.flags.q.explicit_image_format = 1;
                  yyval.type_qualifier.image_format = map[i].format;
                  yyval.type_qualifier.image_base_type = map[i].base_type;
                  break;
               }
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
#line 4976 "compiler/glsl/glsl_parser.cpp"
break;
case 151:
#line 1752 "../mesa/src/compiler/glsl/glsl_parser.yy"
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
         if (!state->has_geometry_shader() && !state->EXT_mesh_shader_enable) {
            _mesa_glsl_error(& yystack.p_mark[0], state,
                             "max_vertices qualifier specified");
         }
      }

      if (match_layout_qualifier("max_primitives", yystack.l_mark[-2].identifier, state) == 0) {
         yyval.type_qualifier.flags.q.max_primitives = 1;
         yyval.type_qualifier.max_primitives = new(ctx) ast_layout_expression(yystack.p_mark[-2], yystack.l_mark[0].expression);
         if (!state->EXT_mesh_shader_enable) {
            _mesa_glsl_error(& yystack.p_mark[0], state,
                             "max_primitives qualifier specified");
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
            if (!state->has_compute_shader() && !state->EXT_mesh_shader_enable) {
               _mesa_glsl_error(& yystack.p_mark[0], state,
                                "%s qualifier requires GLSL 4.30 or "
                                "GLSL ES 3.10 or ARB_compute_shader or EXT_mesh_shader",
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
#line 5157 "compiler/glsl/glsl_parser.cpp"
break;
case 152:
#line 1930 "../mesa/src/compiler/glsl/glsl_parser.yy"
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
#line 5174 "compiler/glsl/glsl_parser.cpp"
break;
case 153:
#line 1956 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      memset(& yyval.type_qualifier, 0, sizeof(yyval.type_qualifier));
      yyval.type_qualifier.flags.q.row_major = 1;
   }
#line 5182 "compiler/glsl/glsl_parser.cpp"
break;
case 154:
#line 1961 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      memset(& yyval.type_qualifier, 0, sizeof(yyval.type_qualifier));
      yyval.type_qualifier.flags.q.packed = 1;
   }
#line 5190 "compiler/glsl/glsl_parser.cpp"
break;
case 155:
#line 1966 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      memset(& yyval.type_qualifier, 0, sizeof(yyval.type_qualifier));
      yyval.type_qualifier.flags.q.shared = 1;
   }
#line 5198 "compiler/glsl/glsl_parser.cpp"
break;
case 156:
#line 1974 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      memset(& yyval.type_qualifier, 0, sizeof(yyval.type_qualifier));
      yyval.type_qualifier.flags.q.subroutine = 1;
   }
#line 5206 "compiler/glsl/glsl_parser.cpp"
break;
case 157:
#line 1979 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      memset(& yyval.type_qualifier, 0, sizeof(yyval.type_qualifier));
      yyval.type_qualifier.flags.q.subroutine = 1;
      yyval.type_qualifier.subroutine_list = yystack.l_mark[-1].subroutine_list;
   }
#line 5215 "compiler/glsl/glsl_parser.cpp"
break;
case 158:
#line 1988 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
        linear_ctx *ctx = state->linalloc;
        ast_declaration *decl = new(ctx)  ast_declaration(yystack.l_mark[0].identifier, NULL, NULL);
        decl->set_location(yystack.p_mark[0]);

        yyval.subroutine_list = new(ctx) ast_subroutine_list();
        yyval.subroutine_list->declarations.push_tail(&decl->link);
   }
#line 5227 "compiler/glsl/glsl_parser.cpp"
break;
case 159:
#line 1997 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
        linear_ctx *ctx = state->linalloc;
        ast_declaration *decl = new(ctx)  ast_declaration(yystack.l_mark[0].identifier, NULL, NULL);
        decl->set_location(yystack.p_mark[0]);

        yyval.subroutine_list = yystack.l_mark[-2].subroutine_list;
        yyval.subroutine_list->declarations.push_tail(&decl->link);
   }
#line 5239 "compiler/glsl/glsl_parser.cpp"
break;
case 160:
#line 2009 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      memset(& yyval.type_qualifier, 0, sizeof(yyval.type_qualifier));
      yyval.type_qualifier.flags.q.smooth = 1;
   }
#line 5247 "compiler/glsl/glsl_parser.cpp"
break;
case 161:
#line 2014 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      memset(& yyval.type_qualifier, 0, sizeof(yyval.type_qualifier));
      yyval.type_qualifier.flags.q.flat = 1;
   }
#line 5255 "compiler/glsl/glsl_parser.cpp"
break;
case 162:
#line 2019 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      memset(& yyval.type_qualifier, 0, sizeof(yyval.type_qualifier));
      yyval.type_qualifier.flags.q.noperspective = 1;
   }
#line 5263 "compiler/glsl/glsl_parser.cpp"
break;
case 163:
#line 2028 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      memset(& yyval.type_qualifier, 0, sizeof(yyval.type_qualifier));
      yyval.type_qualifier.flags.q.invariant = 1;
   }
#line 5271 "compiler/glsl/glsl_parser.cpp"
break;
case 164:
#line 2033 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      memset(& yyval.type_qualifier, 0, sizeof(yyval.type_qualifier));
      yyval.type_qualifier.flags.q.precise = 1;
   }
#line 5279 "compiler/glsl/glsl_parser.cpp"
break;
case 171:
#line 2044 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      memset(&yyval.type_qualifier, 0, sizeof(yyval.type_qualifier));
      yyval.type_qualifier.precision = yystack.l_mark[0].n;
   }
#line 5287 "compiler/glsl/glsl_parser.cpp"
break;
case 172:
#line 2062 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      if (yystack.l_mark[0].type_qualifier.flags.q.precise)
         _mesa_glsl_error(&yystack.p_mark[-1], state, "duplicate \"precise\" qualifier");

      yyval.type_qualifier = yystack.l_mark[0].type_qualifier;
      yyval.type_qualifier.flags.q.precise = 1;
   }
#line 5298 "compiler/glsl/glsl_parser.cpp"
break;
case 173:
#line 2070 "../mesa/src/compiler/glsl/glsl_parser.yy"
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
#line 5326 "compiler/glsl/glsl_parser.cpp"
break;
case 174:
#line 2095 "../mesa/src/compiler/glsl/glsl_parser.yy"
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
#line 5353 "compiler/glsl/glsl_parser.cpp"
break;
case 175:
#line 2119 "../mesa/src/compiler/glsl/glsl_parser.yy"
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
#line 5370 "compiler/glsl/glsl_parser.cpp"
break;
case 176:
#line 2133 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      yyval.type_qualifier = yystack.l_mark[-1].type_qualifier;
      yyval.type_qualifier.merge_qualifier(&yystack.p_mark[-1], state, yystack.l_mark[0].type_qualifier, false);
   }
#line 5378 "compiler/glsl/glsl_parser.cpp"
break;
case 177:
#line 2138 "../mesa/src/compiler/glsl/glsl_parser.yy"
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
#line 5397 "compiler/glsl/glsl_parser.cpp"
break;
case 178:
#line 2154 "../mesa/src/compiler/glsl/glsl_parser.yy"
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
#line 5425 "compiler/glsl/glsl_parser.cpp"
break;
case 179:
#line 2179 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      if (yystack.l_mark[0].type_qualifier.precision != ast_precision_none)
         _mesa_glsl_error(&yystack.p_mark[-1], state, "duplicate precision qualifier");

      if (!(state->has_420pack_or_es31()) &&
          yystack.l_mark[0].type_qualifier.flags.i != 0)
         _mesa_glsl_error(&yystack.p_mark[-1], state, "precision qualifiers must come last");

      yyval.type_qualifier = yystack.l_mark[0].type_qualifier;
      yyval.type_qualifier.precision = yystack.l_mark[-1].n;
   }
#line 5440 "compiler/glsl/glsl_parser.cpp"
break;
case 180:
#line 2191 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      yyval.type_qualifier = yystack.l_mark[-1].type_qualifier;
      yyval.type_qualifier.merge_qualifier(&yystack.p_mark[-1], state, yystack.l_mark[0].type_qualifier, false);
   }
#line 5448 "compiler/glsl/glsl_parser.cpp"
break;
case 181:
#line 2199 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      memset(& yyval.type_qualifier, 0, sizeof(yyval.type_qualifier));
      yyval.type_qualifier.flags.q.centroid = 1;
   }
#line 5456 "compiler/glsl/glsl_parser.cpp"
break;
case 182:
#line 2204 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      memset(& yyval.type_qualifier, 0, sizeof(yyval.type_qualifier));
      yyval.type_qualifier.flags.q.sample = 1;
   }
#line 5464 "compiler/glsl/glsl_parser.cpp"
break;
case 183:
#line 2209 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      memset(& yyval.type_qualifier, 0, sizeof(yyval.type_qualifier));
      yyval.type_qualifier.flags.q.patch = 1;
   }
#line 5472 "compiler/glsl/glsl_parser.cpp"
break;
case 184:
#line 2214 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      memset(& yyval.type_qualifier, 0, sizeof(yyval.type_qualifier));
      yyval.type_qualifier.flags.q.per_primitive = 1;
   }
#line 5480 "compiler/glsl/glsl_parser.cpp"
break;
case 185:
#line 2221 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      memset(& yyval.type_qualifier, 0, sizeof(yyval.type_qualifier));
      yyval.type_qualifier.flags.q.constant = 1;
   }
#line 5488 "compiler/glsl/glsl_parser.cpp"
break;
case 186:
#line 2226 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      memset(& yyval.type_qualifier, 0, sizeof(yyval.type_qualifier));
      yyval.type_qualifier.flags.q.attribute = 1;
   }
#line 5496 "compiler/glsl/glsl_parser.cpp"
break;
case 187:
#line 2231 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      memset(& yyval.type_qualifier, 0, sizeof(yyval.type_qualifier));
      yyval.type_qualifier.flags.q.varying = 1;
   }
#line 5504 "compiler/glsl/glsl_parser.cpp"
break;
case 188:
#line 2236 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      memset(& yyval.type_qualifier, 0, sizeof(yyval.type_qualifier));
      yyval.type_qualifier.flags.q.in = 1;
   }
#line 5512 "compiler/glsl/glsl_parser.cpp"
break;
case 189:
#line 2241 "../mesa/src/compiler/glsl/glsl_parser.yy"
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
#line 5540 "compiler/glsl/glsl_parser.cpp"
break;
case 190:
#line 2266 "../mesa/src/compiler/glsl/glsl_parser.yy"
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
#line 5555 "compiler/glsl/glsl_parser.cpp"
break;
case 191:
#line 2278 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      memset(& yyval.type_qualifier, 0, sizeof(yyval.type_qualifier));
      yyval.type_qualifier.flags.q.uniform = 1;
   }
#line 5563 "compiler/glsl/glsl_parser.cpp"
break;
case 192:
#line 2283 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      memset(& yyval.type_qualifier, 0, sizeof(yyval.type_qualifier));
      yyval.type_qualifier.flags.q.buffer = 1;
   }
#line 5571 "compiler/glsl/glsl_parser.cpp"
break;
case 193:
#line 2288 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      memset(& yyval.type_qualifier, 0, sizeof(yyval.type_qualifier));
      yyval.type_qualifier.flags.q.shared_storage = 1;
   }
#line 5579 "compiler/glsl/glsl_parser.cpp"
break;
case 194:
#line 2293 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      memset(& yyval.type_qualifier, 0, sizeof(yyval.type_qualifier));
      yyval.type_qualifier.flags.q.task_payload = 1;
   }
#line 5587 "compiler/glsl/glsl_parser.cpp"
break;
case 195:
#line 2298 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      memset(& yyval.type_qualifier, 0, sizeof(yyval.type_qualifier));
      yyval.type_qualifier.flags.q.pixel_local_storage = GLSL_PIXEL_LOCAL_STORAGE_INOUT;
   }
#line 5595 "compiler/glsl/glsl_parser.cpp"
break;
case 196:
#line 2303 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      memset(& yyval.type_qualifier, 0, sizeof(yyval.type_qualifier));
      yyval.type_qualifier.flags.q.pixel_local_storage = GLSL_PIXEL_LOCAL_STORAGE_IN;
   }
#line 5603 "compiler/glsl/glsl_parser.cpp"
break;
case 197:
#line 2308 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      memset(& yyval.type_qualifier, 0, sizeof(yyval.type_qualifier));
      yyval.type_qualifier.flags.q.pixel_local_storage = GLSL_PIXEL_LOCAL_STORAGE_OUT;
   }
#line 5611 "compiler/glsl/glsl_parser.cpp"
break;
case 198:
#line 2316 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      memset(& yyval.type_qualifier, 0, sizeof(yyval.type_qualifier));
      yyval.type_qualifier.flags.q.coherent = 1;
   }
#line 5619 "compiler/glsl/glsl_parser.cpp"
break;
case 199:
#line 2321 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      memset(& yyval.type_qualifier, 0, sizeof(yyval.type_qualifier));
      yyval.type_qualifier.flags.q._volatile = 1;
   }
#line 5627 "compiler/glsl/glsl_parser.cpp"
break;
case 200:
#line 2326 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      STATIC_ASSERT(sizeof(yyval.type_qualifier.flags.q) <= sizeof(yyval.type_qualifier.flags.i));
      memset(& yyval.type_qualifier, 0, sizeof(yyval.type_qualifier));
      yyval.type_qualifier.flags.q.restrict_flag = 1;
   }
#line 5636 "compiler/glsl/glsl_parser.cpp"
break;
case 201:
#line 2332 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      memset(& yyval.type_qualifier, 0, sizeof(yyval.type_qualifier));
      yyval.type_qualifier.flags.q.read_only = 1;
   }
#line 5644 "compiler/glsl/glsl_parser.cpp"
break;
case 202:
#line 2337 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      memset(& yyval.type_qualifier, 0, sizeof(yyval.type_qualifier));
      yyval.type_qualifier.flags.q.write_only = 1;
   }
#line 5652 "compiler/glsl/glsl_parser.cpp"
break;
case 203:
#line 2345 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      linear_ctx *ctx = state->linalloc;
      yyval.array_specifier = new(ctx) ast_array_specifier(yystack.p_mark[-1], new(ctx) ast_expression(
                                                  ast_unsized_array_dim, NULL,
                                                  NULL, NULL));
      yyval.array_specifier->set_location_range(yystack.p_mark[-1], yystack.p_mark[0]);
   }
#line 5663 "compiler/glsl/glsl_parser.cpp"
break;
case 204:
#line 2353 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      linear_ctx *ctx = state->linalloc;
      yyval.array_specifier = new(ctx) ast_array_specifier(yystack.p_mark[-2], yystack.l_mark[-1].expression);
      yyval.array_specifier->set_location_range(yystack.p_mark[-2], yystack.p_mark[0]);
   }
#line 5672 "compiler/glsl/glsl_parser.cpp"
break;
case 205:
#line 2359 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      linear_ctx *ctx = state->linalloc;
      yyval.array_specifier = yystack.l_mark[-2].array_specifier;

      if (state->check_arrays_of_arrays_allowed(& yystack.p_mark[-2])) {
         yyval.array_specifier->add_dimension(new(ctx) ast_expression(ast_unsized_array_dim, NULL,
                                                   NULL, NULL));
      }
   }
#line 5685 "compiler/glsl/glsl_parser.cpp"
break;
case 206:
#line 2369 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      yyval.array_specifier = yystack.l_mark[-3].array_specifier;

      if (state->check_arrays_of_arrays_allowed(& yystack.p_mark[-3])) {
         yyval.array_specifier->add_dimension(yystack.l_mark[-1].expression);
      }
   }
#line 5696 "compiler/glsl/glsl_parser.cpp"
break;
case 208:
#line 2381 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      yyval.type_specifier = yystack.l_mark[-1].type_specifier;
      yyval.type_specifier->array_specifier = yystack.l_mark[0].array_specifier;
   }
#line 5704 "compiler/glsl/glsl_parser.cpp"
break;
case 209:
#line 2389 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      linear_ctx *ctx = state->linalloc;
      yyval.type_specifier = new(ctx) ast_type_specifier(yystack.l_mark[0].type);
      yyval.type_specifier->set_location(yystack.p_mark[0]);
   }
#line 5713 "compiler/glsl/glsl_parser.cpp"
break;
case 210:
#line 2395 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      linear_ctx *ctx = state->linalloc;
      yyval.type_specifier = new(ctx) ast_type_specifier(yystack.l_mark[0].struct_specifier);
      yyval.type_specifier->set_location(yystack.p_mark[0]);
   }
#line 5722 "compiler/glsl/glsl_parser.cpp"
break;
case 211:
#line 2401 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      linear_ctx *ctx = state->linalloc;
      yyval.type_specifier = new(ctx) ast_type_specifier(yystack.l_mark[0].identifier);
      yyval.type_specifier->set_location(yystack.p_mark[0]);
   }
#line 5731 "compiler/glsl/glsl_parser.cpp"
break;
case 212:
#line 2409 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{ yyval.type = &glsl_type_builtin_void; }
#line 5736 "compiler/glsl/glsl_parser.cpp"
break;
case 213:
#line 2410 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{ yyval.type = yystack.l_mark[0].type; }
#line 5741 "compiler/glsl/glsl_parser.cpp"
break;
case 214:
#line 2412 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      if (yystack.l_mark[0].type == &glsl_type_builtin_int) {
         yyval.type = &glsl_type_builtin_uint;
      } else {
         _mesa_glsl_error(&yystack.p_mark[-1], state,
                          "\"unsigned\" is only allowed before \"int\"");
      }
   }
#line 5753 "compiler/glsl/glsl_parser.cpp"
break;
case 215:
#line 2424 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      state->check_precision_qualifiers_allowed(&yystack.p_mark[0]);
      yyval.n = ast_precision_high;
   }
#line 5761 "compiler/glsl/glsl_parser.cpp"
break;
case 216:
#line 2429 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      state->check_precision_qualifiers_allowed(&yystack.p_mark[0]);
      yyval.n = ast_precision_medium;
   }
#line 5769 "compiler/glsl/glsl_parser.cpp"
break;
case 217:
#line 2434 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      state->check_precision_qualifiers_allowed(&yystack.p_mark[0]);
      yyval.n = ast_precision_low;
   }
#line 5777 "compiler/glsl/glsl_parser.cpp"
break;
case 218:
#line 2442 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      linear_ctx *ctx = state->linalloc;
      yyval.struct_specifier = new(ctx) ast_struct_specifier(yystack.l_mark[-3].identifier, yystack.l_mark[-1].declarator_list);
      yyval.struct_specifier->set_location_range(yystack.p_mark[-3], yystack.p_mark[0]);
      state->symbols->add_type(yystack.l_mark[-3].identifier, &glsl_type_builtin_void);
   }
#line 5787 "compiler/glsl/glsl_parser.cpp"
break;
case 219:
#line 2449 "../mesa/src/compiler/glsl/glsl_parser.yy"
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
#line 5804 "compiler/glsl/glsl_parser.cpp"
break;
case 220:
#line 2466 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      yyval.declarator_list = yystack.l_mark[0].declarator_list;
      yystack.l_mark[0].declarator_list->link.self_link();
   }
#line 5812 "compiler/glsl/glsl_parser.cpp"
break;
case 221:
#line 2471 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      yyval.declarator_list = yystack.l_mark[-1].declarator_list;
      yyval.declarator_list->link.insert_before(& yystack.l_mark[0].declarator_list->link);
   }
#line 5820 "compiler/glsl/glsl_parser.cpp"
break;
case 222:
#line 2479 "../mesa/src/compiler/glsl/glsl_parser.yy"
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
#line 5858 "compiler/glsl/glsl_parser.cpp"
break;
case 223:
#line 2517 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      yyval.declaration = yystack.l_mark[0].declaration;
      yystack.l_mark[0].declaration->link.self_link();
   }
#line 5866 "compiler/glsl/glsl_parser.cpp"
break;
case 224:
#line 2522 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      yyval.declaration = yystack.l_mark[-2].declaration;
      yyval.declaration->link.insert_before(& yystack.l_mark[0].declaration->link);
   }
#line 5874 "compiler/glsl/glsl_parser.cpp"
break;
case 225:
#line 2530 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      linear_ctx *ctx = state->linalloc;
      yyval.declaration = new(ctx) ast_declaration(yystack.l_mark[0].identifier, NULL, NULL);
      yyval.declaration->set_location(yystack.p_mark[0]);
   }
#line 5883 "compiler/glsl/glsl_parser.cpp"
break;
case 226:
#line 2536 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      linear_ctx *ctx = state->linalloc;
      yyval.declaration = new(ctx) ast_declaration(yystack.l_mark[-1].identifier, yystack.l_mark[0].array_specifier, NULL);
      yyval.declaration->set_location_range(yystack.p_mark[-1], yystack.p_mark[0]);
   }
#line 5892 "compiler/glsl/glsl_parser.cpp"
break;
case 228:
#line 2546 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      yyval.expression = yystack.l_mark[-1].expression;
   }
#line 5899 "compiler/glsl/glsl_parser.cpp"
break;
case 229:
#line 2550 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      yyval.expression = yystack.l_mark[-2].expression;
   }
#line 5906 "compiler/glsl/glsl_parser.cpp"
break;
case 230:
#line 2557 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      linear_ctx *ctx = state->linalloc;
      yyval.expression = new(ctx) ast_aggregate_initializer();
      yyval.expression->set_location(yystack.p_mark[0]);
      yyval.expression->expressions.push_tail(& yystack.l_mark[0].expression->link);
   }
#line 5916 "compiler/glsl/glsl_parser.cpp"
break;
case 231:
#line 2564 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      yystack.l_mark[-2].expression->expressions.push_tail(& yystack.l_mark[0].expression->link);
   }
#line 5923 "compiler/glsl/glsl_parser.cpp"
break;
case 233:
#line 2576 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{ yyval.node = (ast_node *) yystack.l_mark[0].compound_statement; }
#line 5928 "compiler/glsl/glsl_parser.cpp"
break;
case 242:
#line 2592 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      linear_ctx *ctx = state->linalloc;
      yyval.compound_statement = new(ctx) ast_compound_statement(true, NULL);
      yyval.compound_statement->set_location_range(yystack.p_mark[-1], yystack.p_mark[0]);
   }
#line 5937 "compiler/glsl/glsl_parser.cpp"
break;
case 243:
#line 2598 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      state->symbols->push_scope();
   }
#line 5944 "compiler/glsl/glsl_parser.cpp"
break;
case 244:
#line 2602 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      linear_ctx *ctx = state->linalloc;
      yyval.compound_statement = new(ctx) ast_compound_statement(true, yystack.l_mark[-1].node);
      yyval.compound_statement->set_location_range(yystack.p_mark[-3], yystack.p_mark[0]);
      state->symbols->pop_scope();
   }
#line 5954 "compiler/glsl/glsl_parser.cpp"
break;
case 245:
#line 2611 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{ yyval.node = (ast_node *) yystack.l_mark[0].compound_statement; }
#line 5959 "compiler/glsl/glsl_parser.cpp"
break;
case 247:
#line 2617 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      linear_ctx *ctx = state->linalloc;
      yyval.compound_statement = new(ctx) ast_compound_statement(false, NULL);
      yyval.compound_statement->set_location_range(yystack.p_mark[-1], yystack.p_mark[0]);
   }
#line 5968 "compiler/glsl/glsl_parser.cpp"
break;
case 248:
#line 2623 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      linear_ctx *ctx = state->linalloc;
      yyval.compound_statement = new(ctx) ast_compound_statement(false, yystack.l_mark[-1].node);
      yyval.compound_statement->set_location_range(yystack.p_mark[-2], yystack.p_mark[0]);
   }
#line 5977 "compiler/glsl/glsl_parser.cpp"
break;
case 249:
#line 2632 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      if (yystack.l_mark[0].node == NULL) {
         _mesa_glsl_error(& yystack.p_mark[0], state, "<nil> statement");
         assert(yystack.l_mark[0].node != NULL);
      }

      yyval.node = yystack.l_mark[0].node;
      yyval.node->link.self_link();
   }
#line 5990 "compiler/glsl/glsl_parser.cpp"
break;
case 250:
#line 2642 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      if (yystack.l_mark[0].node == NULL) {
         _mesa_glsl_error(& yystack.p_mark[0], state, "<nil> statement");
         assert(yystack.l_mark[0].node != NULL);
      }
      yyval.node = yystack.l_mark[-1].node;
      yyval.node->link.insert_before(& yystack.l_mark[0].node->link);
   }
#line 6002 "compiler/glsl/glsl_parser.cpp"
break;
case 251:
#line 2651 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      if (!state->allow_extension_directive_midshader) {
         _mesa_glsl_error(& yystack.p_mark[-1], state,
                          "#extension directive is not allowed "
                          "in the middle of a shader");
         YYERROR;
      }
   }
#line 6014 "compiler/glsl/glsl_parser.cpp"
break;
case 252:
#line 2663 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      linear_ctx *ctx = state->linalloc;
      yyval.node = new(ctx) ast_expression_statement(NULL);
      yyval.node->set_location(yystack.p_mark[0]);
   }
#line 6023 "compiler/glsl/glsl_parser.cpp"
break;
case 253:
#line 2669 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      linear_ctx *ctx = state->linalloc;
      yyval.node = new(ctx) ast_expression_statement(yystack.l_mark[-1].expression);
      yyval.node->set_location(yystack.p_mark[-1]);
   }
#line 6032 "compiler/glsl/glsl_parser.cpp"
break;
case 254:
#line 2678 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      yyval.node = new(state->linalloc) ast_selection_statement(yystack.l_mark[-2].expression, yystack.l_mark[0].selection_rest_statement.then_statement,
                                                        yystack.l_mark[0].selection_rest_statement.else_statement);
      yyval.node->set_location_range(yystack.p_mark[-4], yystack.p_mark[0]);
   }
#line 6041 "compiler/glsl/glsl_parser.cpp"
break;
case 255:
#line 2687 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      yyval.selection_rest_statement.then_statement = yystack.l_mark[-2].node;
      yyval.selection_rest_statement.else_statement = yystack.l_mark[0].node;
   }
#line 6049 "compiler/glsl/glsl_parser.cpp"
break;
case 256:
#line 2692 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      yyval.selection_rest_statement.then_statement = yystack.l_mark[0].node;
      yyval.selection_rest_statement.else_statement = NULL;
   }
#line 6057 "compiler/glsl/glsl_parser.cpp"
break;
case 257:
#line 2700 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      yyval.node = (ast_node *) yystack.l_mark[0].expression;
   }
#line 6064 "compiler/glsl/glsl_parser.cpp"
break;
case 258:
#line 2704 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      linear_ctx *ctx = state->linalloc;
      ast_declaration *decl = new(ctx) ast_declaration(yystack.l_mark[-2].identifier, NULL, yystack.l_mark[0].expression);
      ast_declarator_list *declarator = new(ctx) ast_declarator_list(yystack.l_mark[-3].fully_specified_type);
      decl->set_location_range(yystack.p_mark[-2], yystack.p_mark[0]);
      declarator->set_location(yystack.p_mark[-3]);

      declarator->declarations.push_tail(&decl->link);
      yyval.node = declarator;
   }
#line 6078 "compiler/glsl/glsl_parser.cpp"
break;
case 259:
#line 2722 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      yyval.node = new(state->linalloc) ast_switch_statement(yystack.l_mark[-2].expression, yystack.l_mark[0].switch_body);
      yyval.node->set_location_range(yystack.p_mark[-4], yystack.p_mark[0]);
   }
#line 6086 "compiler/glsl/glsl_parser.cpp"
break;
case 260:
#line 2730 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      yyval.switch_body = new(state->linalloc) ast_switch_body(NULL);
      yyval.switch_body->set_location_range(yystack.p_mark[-1], yystack.p_mark[0]);
   }
#line 6094 "compiler/glsl/glsl_parser.cpp"
break;
case 261:
#line 2735 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      yyval.switch_body = new(state->linalloc) ast_switch_body(yystack.l_mark[-1].case_statement_list);
      yyval.switch_body->set_location_range(yystack.p_mark[-2], yystack.p_mark[0]);
   }
#line 6102 "compiler/glsl/glsl_parser.cpp"
break;
case 262:
#line 2743 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      yyval.case_label = new(state->linalloc) ast_case_label(yystack.l_mark[-1].expression);
      yyval.case_label->set_location(yystack.p_mark[-1]);
   }
#line 6110 "compiler/glsl/glsl_parser.cpp"
break;
case 263:
#line 2748 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      yyval.case_label = new(state->linalloc) ast_case_label(NULL);
      yyval.case_label->set_location(yystack.p_mark[0]);
   }
#line 6118 "compiler/glsl/glsl_parser.cpp"
break;
case 264:
#line 2756 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      ast_case_label_list *labels = new(state->linalloc) ast_case_label_list();

      labels->labels.push_tail(& yystack.l_mark[0].case_label->link);
      yyval.case_label_list = labels;
      yyval.case_label_list->set_location(yystack.p_mark[0]);
   }
#line 6129 "compiler/glsl/glsl_parser.cpp"
break;
case 265:
#line 2764 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      yyval.case_label_list = yystack.l_mark[-1].case_label_list;
      yyval.case_label_list->labels.push_tail(& yystack.l_mark[0].case_label->link);
   }
#line 6137 "compiler/glsl/glsl_parser.cpp"
break;
case 266:
#line 2772 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      ast_case_statement *stmts = new(state->linalloc) ast_case_statement(yystack.l_mark[-1].case_label_list);
      stmts->set_location(yystack.p_mark[0]);

      stmts->stmts.push_tail(& yystack.l_mark[0].node->link);
      yyval.case_statement = stmts;
   }
#line 6148 "compiler/glsl/glsl_parser.cpp"
break;
case 267:
#line 2780 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      yyval.case_statement = yystack.l_mark[-1].case_statement;
      yyval.case_statement->stmts.push_tail(& yystack.l_mark[0].node->link);
   }
#line 6156 "compiler/glsl/glsl_parser.cpp"
break;
case 268:
#line 2788 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      ast_case_statement_list *cases= new(state->linalloc) ast_case_statement_list();
      cases->set_location(yystack.p_mark[0]);

      cases->cases.push_tail(& yystack.l_mark[0].case_statement->link);
      yyval.case_statement_list = cases;
   }
#line 6167 "compiler/glsl/glsl_parser.cpp"
break;
case 269:
#line 2796 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      yyval.case_statement_list = yystack.l_mark[-1].case_statement_list;
      yyval.case_statement_list->cases.push_tail(& yystack.l_mark[0].case_statement->link);
   }
#line 6175 "compiler/glsl/glsl_parser.cpp"
break;
case 270:
#line 2804 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      linear_ctx *ctx = state->linalloc;
      yyval.node = new(ctx) ast_iteration_statement(ast_iteration_statement::ast_while,
                                            NULL, yystack.l_mark[-2].node, NULL, yystack.l_mark[0].node);
      yyval.node->set_location_range(yystack.p_mark[-4], yystack.p_mark[-1]);
   }
#line 6185 "compiler/glsl/glsl_parser.cpp"
break;
case 271:
#line 2811 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      linear_ctx *ctx = state->linalloc;
      yyval.node = new(ctx) ast_iteration_statement(ast_iteration_statement::ast_do_while,
                                            NULL, yystack.l_mark[-2].expression, NULL, yystack.l_mark[-5].node);
      yyval.node->set_location_range(yystack.p_mark[-6], yystack.p_mark[-1]);
   }
#line 6195 "compiler/glsl/glsl_parser.cpp"
break;
case 272:
#line 2818 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      linear_ctx *ctx = state->linalloc;
      yyval.node = new(ctx) ast_iteration_statement(ast_iteration_statement::ast_for,
                                            yystack.l_mark[-3].node, yystack.l_mark[-2].for_rest_statement.cond, yystack.l_mark[-2].for_rest_statement.rest, yystack.l_mark[0].node);
      yyval.node->set_location_range(yystack.p_mark[-5], yystack.p_mark[0]);
   }
#line 6205 "compiler/glsl/glsl_parser.cpp"
break;
case 276:
#line 2834 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      yyval.node = NULL;
   }
#line 6212 "compiler/glsl/glsl_parser.cpp"
break;
case 277:
#line 2841 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      yyval.for_rest_statement.cond = yystack.l_mark[-1].node;
      yyval.for_rest_statement.rest = NULL;
   }
#line 6220 "compiler/glsl/glsl_parser.cpp"
break;
case 278:
#line 2846 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      yyval.for_rest_statement.cond = yystack.l_mark[-2].node;
      yyval.for_rest_statement.rest = yystack.l_mark[0].expression;
   }
#line 6228 "compiler/glsl/glsl_parser.cpp"
break;
case 279:
#line 2855 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      linear_ctx *ctx = state->linalloc;
      yyval.node = new(ctx) ast_jump_statement(ast_jump_statement::ast_continue, NULL);
      yyval.node->set_location(yystack.p_mark[-1]);
   }
#line 6237 "compiler/glsl/glsl_parser.cpp"
break;
case 280:
#line 2861 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      linear_ctx *ctx = state->linalloc;
      yyval.node = new(ctx) ast_jump_statement(ast_jump_statement::ast_break, NULL);
      yyval.node->set_location(yystack.p_mark[-1]);
   }
#line 6246 "compiler/glsl/glsl_parser.cpp"
break;
case 281:
#line 2867 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      linear_ctx *ctx = state->linalloc;
      yyval.node = new(ctx) ast_jump_statement(ast_jump_statement::ast_return, NULL);
      yyval.node->set_location(yystack.p_mark[-1]);
   }
#line 6255 "compiler/glsl/glsl_parser.cpp"
break;
case 282:
#line 2873 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      linear_ctx *ctx = state->linalloc;
      yyval.node = new(ctx) ast_jump_statement(ast_jump_statement::ast_return, yystack.l_mark[-1].expression);
      yyval.node->set_location_range(yystack.p_mark[-2], yystack.p_mark[-1]);
   }
#line 6264 "compiler/glsl/glsl_parser.cpp"
break;
case 283:
#line 2879 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      linear_ctx *ctx = state->linalloc;
      yyval.node = new(ctx) ast_jump_statement(ast_jump_statement::ast_discard, NULL);
      yyval.node->set_location(yystack.p_mark[-1]);
   }
#line 6273 "compiler/glsl/glsl_parser.cpp"
break;
case 284:
#line 2888 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      linear_ctx *ctx = state->linalloc;
      yyval.node = new(ctx) ast_demote_statement();
      yyval.node->set_location(yystack.p_mark[-1]);
   }
#line 6282 "compiler/glsl/glsl_parser.cpp"
break;
case 285:
#line 2896 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{ yyval.node = yystack.l_mark[0].function_definition; }
#line 6287 "compiler/glsl/glsl_parser.cpp"
break;
case 286:
#line 2897 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{ yyval.node = yystack.l_mark[0].node; }
#line 6292 "compiler/glsl/glsl_parser.cpp"
break;
case 287:
#line 2898 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{ yyval.node = yystack.l_mark[0].node; }
#line 6297 "compiler/glsl/glsl_parser.cpp"
break;
case 288:
#line 2899 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{ yyval.node = yystack.l_mark[0].node; }
#line 6302 "compiler/glsl/glsl_parser.cpp"
break;
case 289:
#line 2900 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{ yyval.node = NULL; }
#line 6307 "compiler/glsl/glsl_parser.cpp"
break;
case 290:
#line 2905 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      linear_ctx *ctx = state->linalloc;
      yyval.function_definition = new(ctx) ast_function_definition();
      yyval.function_definition->set_location_range(yystack.p_mark[-1], yystack.p_mark[0]);
      yyval.function_definition->prototype = yystack.l_mark[-1].function;
      yyval.function_definition->body = yystack.l_mark[0].compound_statement;

      state->symbols->pop_scope();
   }
#line 6320 "compiler/glsl/glsl_parser.cpp"
break;
case 291:
#line 2919 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      yyval.node = yystack.l_mark[0].interface_block;
   }
#line 6327 "compiler/glsl/glsl_parser.cpp"
break;
case 292:
#line 2923 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      ast_interface_block *block = (ast_interface_block *) yystack.l_mark[0].node;

      if (!yystack.l_mark[-1].type_qualifier.merge_qualifier(& yystack.p_mark[-1], state, block->layout, false,
                              block->layout.has_layout())) {
         YYERROR;
      }

      block->layout = yystack.l_mark[-1].type_qualifier;

      yyval.node = block;
   }
#line 6343 "compiler/glsl/glsl_parser.cpp"
break;
case 293:
#line 2936 "../mesa/src/compiler/glsl/glsl_parser.yy"
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
#line 6361 "compiler/glsl/glsl_parser.cpp"
break;
case 294:
#line 2954 "../mesa/src/compiler/glsl/glsl_parser.yy"
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
#line 6380 "compiler/glsl/glsl_parser.cpp"
break;
case 295:
#line 2973 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      memset(& yyval.type_qualifier, 0, sizeof(yyval.type_qualifier));
      yyval.type_qualifier.flags.q.in = 1;
   }
#line 6388 "compiler/glsl/glsl_parser.cpp"
break;
case 296:
#line 2978 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      memset(& yyval.type_qualifier, 0, sizeof(yyval.type_qualifier));
      yyval.type_qualifier.flags.q.out = 1;
   }
#line 6396 "compiler/glsl/glsl_parser.cpp"
break;
case 297:
#line 2983 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      memset(& yyval.type_qualifier, 0, sizeof(yyval.type_qualifier));
      yyval.type_qualifier.flags.q.uniform = 1;
   }
#line 6404 "compiler/glsl/glsl_parser.cpp"
break;
case 298:
#line 2988 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      memset(& yyval.type_qualifier, 0, sizeof(yyval.type_qualifier));
      yyval.type_qualifier.flags.q.buffer = 1;
   }
#line 6412 "compiler/glsl/glsl_parser.cpp"
break;
case 299:
#line 2993 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      memset(& yyval.type_qualifier, 0, sizeof(yyval.type_qualifier));
      yyval.type_qualifier.flags.q.pixel_local_storage = GLSL_PIXEL_LOCAL_STORAGE_INOUT;
   }
#line 6420 "compiler/glsl/glsl_parser.cpp"
break;
case 300:
#line 2998 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      memset(& yyval.type_qualifier, 0, sizeof(yyval.type_qualifier));
      yyval.type_qualifier.flags.q.pixel_local_storage = GLSL_PIXEL_LOCAL_STORAGE_IN;
   }
#line 6428 "compiler/glsl/glsl_parser.cpp"
break;
case 301:
#line 3003 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      memset(& yyval.type_qualifier, 0, sizeof(yyval.type_qualifier));
      yyval.type_qualifier.flags.q.pixel_local_storage = GLSL_PIXEL_LOCAL_STORAGE_OUT;
   }
#line 6436 "compiler/glsl/glsl_parser.cpp"
break;
case 302:
#line 3008 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      if (!yystack.l_mark[-1].type_qualifier.flags.q.patch && !yystack.l_mark[-1].type_qualifier.flags.q.per_primitive) {
         _mesa_glsl_error(&yystack.p_mark[-1], state, "invalid interface qualifier");
      }
      if (yystack.l_mark[0].type_qualifier.has_auxiliary_storage()) {
         _mesa_glsl_error(&yystack.p_mark[-1], state, "duplicate auxiliary storage qualifier");
      }
      yyval.type_qualifier = yystack.l_mark[0].type_qualifier;
      yyval.type_qualifier.flags.q.patch = yystack.l_mark[-1].type_qualifier.flags.q.patch;
      yyval.type_qualifier.flags.q.per_primitive = yystack.l_mark[-1].type_qualifier.flags.q.per_primitive;
   }
#line 6451 "compiler/glsl/glsl_parser.cpp"
break;
case 303:
#line 3023 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      yyval.interface_block = new(state->linalloc) ast_interface_block(NULL, NULL);
   }
#line 6458 "compiler/glsl/glsl_parser.cpp"
break;
case 304:
#line 3027 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      yyval.interface_block = new(state->linalloc) ast_interface_block(yystack.l_mark[0].identifier, NULL);
      yyval.interface_block->set_location(yystack.p_mark[0]);
   }
#line 6466 "compiler/glsl/glsl_parser.cpp"
break;
case 305:
#line 3032 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      yyval.interface_block = new(state->linalloc) ast_interface_block(yystack.l_mark[-1].identifier, yystack.l_mark[0].array_specifier);
      yyval.interface_block->set_location_range(yystack.p_mark[-1], yystack.p_mark[0]);
   }
#line 6474 "compiler/glsl/glsl_parser.cpp"
break;
case 306:
#line 3040 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      yyval.declarator_list = yystack.l_mark[0].declarator_list;
      yystack.l_mark[0].declarator_list->link.self_link();
   }
#line 6482 "compiler/glsl/glsl_parser.cpp"
break;
case 307:
#line 3045 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      yyval.declarator_list = yystack.l_mark[-1].declarator_list;
      yystack.l_mark[0].declarator_list->link.insert_before(& yyval.declarator_list->link);
   }
#line 6490 "compiler/glsl/glsl_parser.cpp"
break;
case 308:
#line 3053 "../mesa/src/compiler/glsl/glsl_parser.yy"
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
#line 6514 "compiler/glsl/glsl_parser.cpp"
break;
case 309:
#line 3077 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      yyval.type_qualifier = yystack.l_mark[-1].type_qualifier;
      if (!yyval.type_qualifier.merge_qualifier(& yystack.p_mark[-1], state, yystack.l_mark[0].type_qualifier, false, true)) {
         YYERROR;
      }
   }
#line 6524 "compiler/glsl/glsl_parser.cpp"
break;
case 311:
#line 3088 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      yyval.type_qualifier = yystack.l_mark[-1].type_qualifier;
      if (!yyval.type_qualifier.merge_qualifier(& yystack.p_mark[-1], state, yystack.l_mark[0].type_qualifier, false, true)) {
         YYERROR;
      }
   }
#line 6534 "compiler/glsl/glsl_parser.cpp"
break;
case 313:
#line 3099 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      yyval.type_qualifier = yystack.l_mark[-1].type_qualifier;
      if (!yyval.type_qualifier.merge_qualifier(& yystack.p_mark[-1], state, yystack.l_mark[0].type_qualifier, false, true)) {
         YYERROR;
      }
      if (!yyval.type_qualifier.validate_in_qualifier(& yystack.p_mark[-1], state)) {
         YYERROR;
      }
   }
#line 6547 "compiler/glsl/glsl_parser.cpp"
break;
case 314:
#line 3109 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      if (!yystack.l_mark[-2].type_qualifier.validate_in_qualifier(& yystack.p_mark[-2], state)) {
         YYERROR;
      }
   }
#line 6556 "compiler/glsl/glsl_parser.cpp"
break;
case 315:
#line 3118 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      yyval.type_qualifier = yystack.l_mark[-1].type_qualifier;
      if (!yyval.type_qualifier.merge_qualifier(& yystack.p_mark[-1], state, yystack.l_mark[0].type_qualifier, false, true)) {
         YYERROR;
      }
      if (!yyval.type_qualifier.validate_out_qualifier(& yystack.p_mark[-1], state)) {
         YYERROR;
      }
   }
#line 6569 "compiler/glsl/glsl_parser.cpp"
break;
case 316:
#line 3128 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      if (!yystack.l_mark[-2].type_qualifier.validate_out_qualifier(& yystack.p_mark[-2], state)) {
         YYERROR;
      }
   }
#line 6578 "compiler/glsl/glsl_parser.cpp"
break;
case 317:
#line 3137 "../mesa/src/compiler/glsl/glsl_parser.yy"
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
#line 6593 "compiler/glsl/glsl_parser.cpp"
break;
case 318:
#line 3149 "../mesa/src/compiler/glsl/glsl_parser.yy"
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
#line 6618 "compiler/glsl/glsl_parser.cpp"
break;
case 319:
#line 3171 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      yyval.node = NULL;
      if (!yystack.l_mark[0].type_qualifier.merge_into_in_qualifier(& yystack.p_mark[0], state, yyval.node)) {
         YYERROR;
      }
      if (!state->in_qualifier->push_to_global(& yystack.p_mark[0], state)) {
         YYERROR;
      }
   }
#line 6631 "compiler/glsl/glsl_parser.cpp"
break;
case 320:
#line 3181 "../mesa/src/compiler/glsl/glsl_parser.yy"
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
#line 6646 "compiler/glsl/glsl_parser.cpp"
break;
#line 6648 "compiler/glsl/glsl_parser.cpp"
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
