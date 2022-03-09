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
#line 100 "../mesa/src/compiler/glsl/glsl_parser.yy"
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
#line 256 "compiler/glsl/glsl_parser.cpp"

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
#define DOUBLECONSTANT 300
#define INTCONSTANT 301
#define UINTCONSTANT 302
#define BOOLCONSTANT 303
#define INT64CONSTANT 304
#define UINT64CONSTANT 305
#define FIELD_SELECTION 306
#define LEFT_OP 307
#define RIGHT_OP 308
#define INC_OP 309
#define DEC_OP 310
#define LE_OP 311
#define GE_OP 312
#define EQ_OP 313
#define NE_OP 314
#define AND_OP 315
#define OR_OP 316
#define XOR_OP 317
#define MUL_ASSIGN 318
#define DIV_ASSIGN 319
#define ADD_ASSIGN 320
#define MOD_ASSIGN 321
#define LEFT_ASSIGN 322
#define RIGHT_ASSIGN 323
#define AND_ASSIGN 324
#define XOR_ASSIGN 325
#define OR_ASSIGN 326
#define SUB_ASSIGN 327
#define INVARIANT 328
#define PRECISE 329
#define LOWP 330
#define MEDIUMP 331
#define HIGHP 332
#define SUPERP 333
#define PRECISION 334
#define VERSION_TOK 335
#define EXTENSION 336
#define LINE 337
#define COLON 338
#define EOL 339
#define INTERFACE_TOK 340
#define OUTPUT 341
#define PRAGMA_DEBUG_ON 342
#define PRAGMA_DEBUG_OFF 343
#define PRAGMA_OPTIMIZE_ON 344
#define PRAGMA_OPTIMIZE_OFF 345
#define PRAGMA_WARNING_ON 346
#define PRAGMA_WARNING_OFF 347
#define PRAGMA_INVARIANT_ALL 348
#define LAYOUT_TOK 349
#define DOT_TOK 350
#define ASM 351
#define CLASS 352
#define UNION 353
#define ENUM 354
#define TYPEDEF 355
#define TEMPLATE 356
#define THIS 357
#define PACKED_TOK 358
#define GOTO 359
#define INLINE_TOK 360
#define NOINLINE 361
#define PUBLIC_TOK 362
#define STATIC 363
#define EXTERN 364
#define EXTERNAL 365
#define LONG_TOK 366
#define SHORT_TOK 367
#define HALF 368
#define FIXED_TOK 369
#define UNSIGNED 370
#define INPUT_TOK 371
#define HVEC2 372
#define HVEC3 373
#define HVEC4 374
#define FVEC2 375
#define FVEC3 376
#define FVEC4 377
#define SAMPLER3DRECT 378
#define SIZEOF 379
#define CAST 380
#define NAMESPACE 381
#define USING 382
#define RESOURCE 383
#define PATCH 384
#define SUBROUTINE 385
#define ERROR_TOK 386
#define COMMON 387
#define PARTITION 388
#define ACTIVE 389
#define FILTER 390
#define ROW_MAJOR 391
#define THEN 392
#define YYERRCODE 256
typedef int YYINT;
static const YYINT _mesa_glsl_lhs[] = {                  -1,
  107,    0,  104,  104,  104,   68,   68,   68,   68,   68,
   68,   68,  105,  105,    1,    1,    1,  108,  106,  106,
  106,    3,    3,   40,   40,   40,   40,   40,   40,   40,
   40,   40,   57,   57,   57,   57,   57,   57,   56,   63,
   62,   61,   61,   59,   59,   58,   58,   60,   66,   66,
   54,   54,   54,   54,   65,   65,   65,   65,   53,   53,
   53,   53,   52,   52,   52,   51,   51,   51,   50,   50,
   50,   50,   50,   49,   49,   49,   48,   48,   47,   47,
   46,   46,   45,   45,   44,   44,   43,   43,   42,   42,
   41,   41,   64,   64,   64,   64,   64,   64,   64,   64,
   64,   64,   64,   39,   39,   55,   73,   73,   73,   73,
   25,   28,   28,   27,   27,   26,   29,   29,   29,   30,
   30,   31,   31,   31,   31,   31,   31,   32,   32,   32,
   33,   69,   69,   69,   69,   69,   70,   70,   70,   70,
   70,   70,   70,   24,   24,   12,   13,   13,   14,   14,
   14,   15,   15,   15,   17,   17,   18,   18,   11,   11,
   11,    8,    8,    8,    8,    8,    8,    8,    8,    8,
    8,    8,    8,    8,    8,    8,    8,    8,    8,    9,
    9,    9,   10,   10,   10,   10,   10,   10,   10,   10,
   10,   16,   16,   16,   16,   16,   22,   22,   22,   22,
   20,   20,   21,   21,   21,   23,   23,   23,    7,    7,
    7,   79,   79,   80,   80,   81,   83,   83,   82,   82,
   71,   71,   71,   72,   72,   74,    4,    4,    6,    6,
    6,    6,    6,    6,    6,   36,  109,   36,   37,   37,
   35,   35,    5,    5,    5,   38,   38,   86,   87,   87,
   95,   95,   88,   89,   89,   91,   91,   90,   90,   92,
   92,   93,   93,   94,   94,   94,   97,   97,   96,   96,
   98,   98,   75,   75,   75,   75,   75,   76,   67,   67,
   67,   67,   67,   34,   77,   77,   77,   78,   19,   19,
   19,   19,   19,    2,    2,    2,   84,   84,   85,  100,
  100,  101,  101,  102,  102,  103,  103,   99,   99,   99,
   99,
};
static const YYINT _mesa_glsl_len[] = {                   2,
    0,    4,    0,    3,    4,    2,    2,    2,    2,    2,
    2,    2,    0,    2,    1,    1,    1,    5,    1,    2,
    2,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    3,    1,    4,    1,    3,    2,    2,    1,    1,
    1,    2,    2,    2,    1,    2,    3,    2,    1,    1,
    1,    2,    2,    2,    1,    1,    1,    1,    1,    3,
    3,    3,    1,    3,    3,    1,    3,    3,    1,    3,
    3,    3,    3,    1,    3,    3,    1,    3,    1,    3,
    1,    3,    1,    3,    1,    3,    1,    3,    1,    5,
    1,    3,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    3,    1,    2,    2,    4,    1,
    2,    1,    1,    2,    3,    3,    2,    3,    3,    2,
    2,    0,    2,    2,    2,    2,    2,    1,    1,    1,
    1,    1,    3,    4,    6,    5,    1,    2,    3,    5,
    4,    2,    2,    1,    2,    4,    1,    3,    1,    3,
    1,    1,    1,    1,    1,    4,    1,    3,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    2,    2,    2,    2,    2,    2,    2,    2,    2,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    2,    3,    3,    4,
    1,    2,    1,    1,    1,    1,    1,    2,    1,    1,
    1,    5,    4,    1,    2,    3,    1,    3,    1,    2,
    1,    3,    4,    1,    3,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    2,    0,    4,    1,    1,
    2,    3,    1,    2,    2,    1,    2,    5,    3,    1,
    1,    4,    5,    2,    3,    3,    2,    1,    2,    2,
    2,    1,    2,    5,    7,    6,    1,    1,    1,    0,
    2,    3,    2,    2,    2,    3,    2,    2,    1,    1,
    1,    1,    1,    2,    1,    2,    2,    7,    1,    1,
    1,    1,    2,    0,    1,    2,    1,    2,    3,    2,
    3,    2,    3,    2,    3,    2,    3,    1,    1,    1,
    1,
};
static const YYINT _mesa_glsl_defred[] = {                0,
    0,    0,   13,    0,    0,   15,   16,   17,    4,    0,
    0,    0,   14,    5,    0,  184,  183,  207,    0,  180,
    0,    0,  188,    0,  185,  181,  161,  160,  159,  192,
  193,  194,  195,  196,  191,    0,  206,  205,    0,    0,
  211,  210,  209,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,  182,    0,  283,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  144,    0,  203,    0,    0,
    0,    0,    0,  279,   19,  281,    0,  132,  280,  110,
  285,  204,  282,  308,  309,  310,  311,    0,    0,    0,
    0,  190,  186,  187,  189,   22,   23,    0,    0,  142,
  172,    0,    0,    0,  143,  171,    0,    6,    7,    8,
    9,   11,   12,   10,    0,  208,    0,  178,  145,  176,
  293,  177,  173,    0,    0,    0,    0,  174,  286,  300,
  302,  304,  306,  179,    0,  287,  175,    0,    0,    0,
    0,    0,    0,    0,  107,    0,  284,    0,  128,  129,
  130,    0,    0,    0,  114,    0,    0,    0,  111,    0,
  108,   20,   21,    0,    0,    0,  214,    0,    0,  154,
  153,  152,    0,    0,  147,  151,  157,    0,  303,  305,
  307,  301,    0,   29,   30,   25,   26,   31,   27,   28,
    0,    0,    0,  197,   55,   56,   57,   58,   24,   49,
   33,  106,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,   59,    0,    0,    0,    0,    0,   41,
   40,   35,    0,    0,    0,    0,    0,  116,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  246,    0,
  241,  243,    0,  228,    0,    0,  227,  230,    0,  104,
   91,    0,  226,  229,  234,  235,  231,  232,  233,  123,
  124,  126,  127,    0,    0,  120,  121,  125,  115,    0,
   18,    0,  217,    0,  213,  215,    0,  109,    0,  146,
    0,  156,    0,    0,    0,    0,   52,   53,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  198,
   37,   38,    0,    0,   42,    0,   43,    0,   46,   54,
   48,  199,    0,    0,  221,  141,    0,  274,  273,  240,
  239,    0,    0,    0,  278,  277,  275,    0,    0,    0,
  236,    0,  242,  244,  245,    0,  247,   94,   95,   97,
   96,   99,  100,  101,  102,  103,   98,   93,    0,    0,
    0,    0,    0,    0,    0,  216,  212,  150,  148,  158,
    0,    0,  298,   32,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,   60,   61,   62,   36,    0,    0,   47,  200,  224,
    0,  140,    0,  267,  268,    0,    0,  276,    0,    0,
    0,    0,    0,  105,   92,  118,    0,  136,    0,  218,
  299,    0,    0,    0,   34,    0,  222,    0,  269,    0,
    0,    0,    0,    0,    0,  238,  135,    0,  288,   90,
  223,  225,    0,    0,    0,    0,  248,    0,  253,    0,
  264,    0,    0,  266,    0,    0,    0,  254,    0,  258,
    0,    0,  252,  265,  249,    0,  257,  260,  259,  261,
  255,    0,  256,
};
#if defined(YYDESTRUCT_CALL) || defined(YYSTYPE_TOSTRING)
static const YYINT _mesa_glsl_stos[] = {                  0,
  335,  394,  498,  301,  499,  296,  297,  298,  339,  395,
  336,  501,  502,  339,  395,  257,  258,  259,  261,  273,
  274,  275,  276,  277,  278,  279,  280,  281,  282,  287,
  288,  289,  290,  291,  292,  293,  294,  297,  328,  329,
  330,  331,  332,  334,  342,  343,  344,  345,  346,  347,
  348,  349,  370,  384,  385,   59,  401,  402,  403,  404,
  405,  406,  410,  411,  413,  414,  415,  417,  418,  419,
  420,  421,  422,  428,  461,  462,  463,  464,  467,  471,
  472,  473,  493,  494,  495,  496,  497,  500,  338,  123,
  395,  261,  274,  275,  277,  296,  298,  328,  329,  397,
  402,  403,  406,  410,  397,  402,  401,  339,  339,  339,
  339,  339,  339,  339,   40,  259,   40,  402,  414,  402,
  413,  402,  402,  261,  274,  275,  277,  402,  471,  494,
  495,  496,  497,  402,  406,  471,  402,  298,   91,  416,
  296,  298,  395,  397,   59,  123,  429,  258,  274,  275,
  276,  329,  401,  410,  424,  425,  426,   44,   41,   44,
   59,  461,  502,  395,  418,  474,  475,  123,  414,  292,
  358,  391,  395,  407,  408,  409,  395,  412,   59,   59,
   59,   59,  123,  299,  300,  301,  302,  303,  304,  305,
  309,  310,   40,   93,   43,   45,   33,  126,  397,  414,
  434,  436,  437,  438,  439,  440,  441,  442,  443,  444,
  445,  446,  447,  448,  449,  451,  452,  453,  454,  455,
  456,  457,  459,  460,   91,   61,  416,   40,  260,  262,
  263,  265,  266,  267,  268,  269,  270,  295,   59,  123,
  125,  398,  399,  400,  414,  419,  430,  432,  433,  435,
  436,  448,  467,  468,  469,  470,  480,  482,  488,  425,
  425,  425,  425,  406,  414,  423,  427,  425,  424,  395,
  339,  395,  476,  477,  125,  475,  474,   59,   61,   41,
   44,   41,   44,  418,  478,  479,  448,  448,  433,  316,
   63,  317,  315,  124,   94,   38,  313,  314,  311,  312,
   60,   62,  307,  308,   43,   45,   42,   47,   37,   93,
  309,  310,  350,   91,   41,   44,   41,  294,  435,  448,
   40,   93,  449,  123,  435,  465,   61,   59,   59,  400,
  429,  431,   40,   40,   59,   59,   59,  433,   40,   40,
  125,  503,  125,  398,  502,   44,   59,  318,  319,  320,
  321,  322,  323,  324,  325,  326,  327,   61,  458,  414,
  395,   61,  416,  416,   44,   59,  125,  449,  408,  395,
  477,  125,  478,   41,  438,  433,  439,  440,  441,  442,
  443,  444,  444,  445,  445,  445,  445,  446,  446,  447,
  447,  448,  448,  448,  306,  433,  450,  435,   93,  465,
  466,  465,  295,  432,  468,  491,  433,   59,  433,  418,
  433,  489,  399,  435,  435,  395,  416,  465,   61,  476,
   59,  298,  396,   58,   93,   44,  125,   40,  489,  490,
  492,   41,   41,  395,   41,  125,  465,  416,   59,  435,
  125,  465,  433,   59,   41,  398,  481,  123,  483,   61,
  431,   41,  433,  431,  264,  271,  272,  125,  484,  485,
  486,  487,  465,   59,  398,  433,   58,  398,  485,  398,
  125,  486,   58,
};
#endif /* YYDESTRUCT_CALL || YYSTYPE_TOSTRING */
static const YYINT _mesa_glsl_dgoto[] = {                 2,
  272,  423,  199,  242,  243,  244,   57,   58,   59,   60,
   61,  103,  174,  175,  176,  104,   64,  178,   65,  200,
   67,  140,   68,   69,  246,   71,   72,   73,  266,  155,
  156,  157,  267,   74,  331,  247,  332,  248,  249,  201,
  250,  251,  203,  204,  205,  206,  207,  208,  209,  210,
  211,  212,  213,  252,  215,  397,  216,  217,  218,  219,
  220,  221,  222,  359,  223,  224,   75,   76,   77,   78,
  326,  401,  253,  254,  255,  256,   80,   81,   82,  166,
  167,  273,  274,  285,  286,  257,  447,  258,  449,  459,
  460,  461,  462,  259,  412,  430,  406,  431,   83,   84,
   85,   86,   87,    3,    5,   88,   12,  345,  342,
};
static const YYINT _mesa_glsl_sindex[] = {             -298,
 -260,    0,    0,  -16, -277,    0,    0,    0,    0, -278,
  107, 2050,    0,    0, -273,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0, -115,    0,    0, 3216, 3216,
    0,    0,    0,  238, -266, -258, -249, -246, -216, -207,
 -199,  157,  -93,    0,  184,    0, 3279, -185, 3345, 3279,
 3279, 3408, 3345, 3279,  -88,    0,  135,    0,  286,  -26,
  832,  146,  189,    0,    0,    0,   43,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0, 1849,  107, 3087,
  118,    0,    0,    0,    0,    0,    0, 3279, 3279,    0,
    0, 3279, 3279, 3279,    0,    0, -185,    0,    0,    0,
    0,    0,    0,    0,  -52,    0,  107,    0,    0,    0,
    0,    0,    0,  190,  198,  227,  245,    0,    0,    0,
    0,    0,    0,    0, 3345,    0,    0,  173, 1659,  224,
    0,    0,  -33,  278,    0,  878,    0,  832,    0,    0,
    0,  832,  832,  832,    0,   96,  832,  832,    0,  107,
    0,    0,    0,  -14,  107, 2630,    0, 3087,  261,    0,
    0,    0,  266,   77,    0,    0,    0,  109,    0,    0,
    0,    0, 3087,    0,    0,    0,    0,    0,    0,    0,
 1775, 1775, 1775,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  -56,   40,   20,  205,  316,  350,  -23,  -50,
   65,  114,  149,    0,  324,  -75,  209,  374, 1795,    0,
    0,    0, 1775,  385, 1695,   82,  -19,    0,  381,  383,
 1007,  406,  411,  398,  408, 1713,  413,  441,    0,  347,
    0,    0,  373,    0,    0,  438,    0,    0,   57,    0,
    0,  237,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0, -185,  107,    0,    0,    0,    0,   14,
    0,  135,    0,   86,    0,    0, 2745,    0, 1775,    0,
  -52,    0,  107,  107,  368, 3087,    0,    0,  269, 1775,
 1775, 1775, 1775, 1775, 1775, 1775, 1775, 1775, 1775, 1775,
 1775, 1775, 1775, 1775, 1775, 1775, 1775, 1775, 1775,    0,
    0,    0,  194, 1775,    0, 1775,    0,    0,    0,    0,
    0,    0,  415,   82,    0,    0,   82,    0,    0,    0,
    0,  235, 1384, 1775,    0,    0,    0,  129, 1775, 1502,
    0, 1192,    0,    0,    0, 1775,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0, 1775,  107,
  135,   82,   19,  224,  107,    0,    0,    0,    0,    0,
  134,  268,    0,    0,   40,   26,   20,  205,  316,  350,
  -23,  -50,  -50,   65,   65,   65,   65,  114,  114,  149,
  149,    0,    0,    0,    0,  507,  478,    0,    0,    0,
  -42,    0,  537,    0,    0, 1502,  296,    0,  322,  107,
  507,  538,  561,    0,    0,    0,  224,    0,   82,    0,
    0,  135,  526, 1775,    0,   49,    0, 1775,    0,  528,
  547, 1192,  466,  534, 1007,    0,    0,  224,    0,    0,
    0,    0,  333, 1775, 1007,  332,    0, -111,    0,   82,
    0,  539,  507,    0, 1192, 1775,  541,    0,  690,    0,
 1192, -108,    0,    0,    0,   70,    0,    0,    0,    0,
    0, 1192,    0,
};
static const YYINT _mesa_glsl_rindex[] = {             1949,
    0,    0,    0,    0, 2150,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0, 2829,    0,
 2892, 2958,    0, 3021,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  -94,   67,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0, 3150,    0,  182,    0,  195,  197,
  421,  432,  434,  512,    0,    0,    3,    0,  145,    0,
  -38,  556,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  600,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  -94,   67,    0,
    0,  195,  432,  434,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0, 2829, 2892, 2958, 3021,    0,    0,    0,
    0,    0,    0,    0,  432,    0,    0,    0,    0,  111,
  178,  253,  150,    0,    0,    0,    0,  180,    0,    0,
    0,  180,  180,  180,    0,    0,  180,  180,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  354,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,   -5,  143, 1316, 1817,  275,  170,  154, 1198,
  564, 2492,  721,    0,    0, 2328,    0,    0,  562,    0,
    0,    0,    0,    0,    0,    0,  179,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0, 1321,
    0,    0,    0,    0,  -25,    0,    0,    0,    0,    0,
    0, 2211,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  370,    0,    0,    0,    0,  199,
    0,  248,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  482,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,   16,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  394,    0,  258,  265,    0,    0,    0,    0,    0,    0,
    0,  550,    0,    0, 1024,    0, 2258, 2446, 1352, 1289,
 1004, 1841, 2655,  881, 2540, 2622, 2629, 2503, 2532, 1804,
 2413,    0,    0,    0,    0,  517,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  552,    0,    0,    0,    0,
    7,    0,    0,    0,    0,    0,  439,    0,    0,    0,
    0,  553,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  557,    0,    0,
    0,    0,    0,  574,    0,  244,    0,    0,    0,    0,
    0,    0,  576,    0,    0,    0,    0,    0,    0,    0,
 -104,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  -95,    0,
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
    0,    0,    0,
};
#endif
static const YYINT _mesa_glsl_gindex[] = {                0,
    2,    0,   10,  338,  277, -220,  542, 2725,  -35,    0,
    0,   23,    0,  344,    0,  -11,    0,    0,  578,  -12,
    0, -134,    0,  -70,   12,    0,    0,    0,    0,  486,
  274,    0,    0,    0,  575,    0, -296,  326, 2545,    0,
 1498,  -99,    0,  389,  393,  388,  403,  397,  402,   99,
  163,  126,  222, 2761, -180,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  618,    0,    0,    0,
  294,    0,   15,  375,    0,    0,  -31,    0,    0,  543,
 -148,  345,  428,  430,    0,    0,    0,    0,    0,    0,
  260,  255,    0,    0,  315,    0,    0,    0,    0,  662,
  670,  672,  674,    0,    0,    0,    0,   18,    0,
};
#define YYTABLESIZE 3793
static const YYINT _mesa_glsl_table[] = {                66,
   63,  426,  112,  102,  102,   10,  291,   90,  227,  301,
  330,  302,   15,  458,   49,  314,  471,  276,  144,  165,
  262,  102,   13,   70,  102,  102,   79,  226,  102,  263,
  129,  136,  145,  144,   62,   89,    1,   91,   89,  202,
    4,  327,  201,  201,  323,  119,  201,  251,  100,  105,
   63,   63,   89,   89,  102,  206,   44,  139,   11,  154,
   14,  201,  102,  102,   89,  251,  102,  102,  102,  346,
  143,  225,  108,   18,  362,   66,   63,   66,  144,  419,
  109,  197,  427,  424,   62,  135,  160,   89,  193,  110,
  164,  195,  111,  196,  169,  165,  146,  165,  368,   70,
  346,  161,   79,  129,  139,  163,  206,   36,   37,  225,
   62,   38,  284,  346,  197,  347,  173,  280,  177,   89,
  281,  193,  112,   63,  195,  202,  196,  473,  276,  365,
  102,  113,  102,  245,   63,  363,  154,  364,  451,  114,
  154,  154,  154,  265,  366,  154,  154,  102,  454,  282,
  202,  202,  283,   66,  202,   66,  305,  135,  306,  456,
  457,  270,  456,  457,  162,  116,  262,  262,  135,  202,
   66,  324,  346,  441,  198,  263,  263,  365,  264,  202,
    6,    7,    8,   87,   53,  309,   87,  408,  137,  158,
  307,   77,  421,  138,   77,  308,  115,   77,  162,  162,
   87,   87,  162,  137,  324,   87,  165,  198,  138,  138,
   79,   77,   77,   79,  330,  284,   77,   22,  245,   63,
  122,   15,  139,  117,  330,  139,  417,   79,   79,  159,
  245,   63,   79,  311,  312,   87,   15,  139,   15,  170,
  168,  102,  133,    6,    7,    8,   77,   77,  179,  315,
  102,  360,  316,  135,  122,  122,  180,  133,  122,  290,
  299,  300,   79,   79,   66,  135,  361,   87,   15,  410,
  144,  144,  144,   66,  313,  162,  250,   77,   77,    6,
    7,    8,  173,  250,  370,  181,  250,  438,  250,  297,
  298,  219,   23,   79,   79,  183,   17,  358,  201,  201,
  201,  134,  250,  182,  102,  171,  219,   18,  220,  374,
  122,   17,  346,   17,  225,   81,  134,  228,   81,  278,
  245,   63,    9,  220,  271,  163,  279,  245,  294,  245,
   63,  122,   81,   81,  293,  410,  432,   81,  172,  346,
   18,   36,   37,   17,   96,   38,   97,  184,  185,  186,
  187,  188,  189,  190,   18,  135,  292,  191,  192,  163,
  163,  416,  433,  163,  135,  346,  250,   81,  250,  250,
  102,  303,  304,  452,   36,   37,  346,   96,   38,   97,
  184,  185,  186,  187,  188,  189,  190,  296,   36,   37,
  191,  192,   38,  245,  149,  382,  383,  149,   81,   81,
  245,   63,    6,    7,    8,  197,  202,  202,  202,  295,
  131,  434,  193,  131,  317,  195,  310,  196,   53,  245,
   63,  260,  245,   63,  321,  261,  262,  263,  388,  389,
  268,  239,  245,   63,  117,  135,  163,  117,  122,  328,
  170,  329,  245,   63,   52,  333,  245,   63,  245,   63,
  334,   53,  339,  164,  135,  165,  335,  135,   87,  245,
   63,  384,  385,  386,  387,   53,  336,  135,   77,   77,
   77,  341,  122,  122,  170,  170,  122,  135,  170,  119,
  340,  135,  119,  135,   79,   79,   79,  164,  164,  165,
  165,  164,  372,  165,  135,  240,  145,  343,  198,  395,
  250,  250,  250,  250,  250,  250,  250,  399,  250,  250,
  250,  250,  250,  250,  250,  250,  250,  250,  250,  250,
  250,  250,  250,  250,  250,  250,  390,  391,  122,  403,
  250,  250,  250,  250,  250,  250,  250,  250,  250,  250,
  250,  250,  250,  250,  250,  250,  250,  250,  250,  122,
  346,  170,  250,  250,  348,  349,  350,  351,  352,  353,
  354,  355,  356,  357,  164,  422,  165,   41,   42,   43,
  425,  250,  250,  250,  250,  250,  428,  250,  435,  250,
  344,  141,    7,  142,  439,  107,  444,  445,  448,   81,
   81,   81,  250,  197,  450,  455,  113,  464,  467,    2,
  193,   69,   45,  195,   69,  196,  297,   69,  294,   39,
  270,  295,  153,  250,  271,  296,  272,  400,  413,  239,
  402,   69,   69,   69,  369,   69,   69,  250,  250,   16,
   17,   18,  229,   19,  230,  231,  121,  232,  233,  234,
  235,  236,  237,  269,  147,   20,   21,   22,   23,   24,
   25,   26,   27,   28,   29,  418,   69,   69,  404,   30,
   31,   32,   33,   34,   35,   36,   37,  238,   96,   38,
   97,  184,  185,  186,  187,  188,  189,  190,  375,  166,
  378,  191,  192,  240,  377,  436,  198,   69,   69,  153,
  167,  380,  168,  153,  153,  153,  379,  381,  153,  153,
   39,   40,   41,   42,   43,  162,   44,  405,   11,  420,
  277,  371,  437,  166,  166,  373,  472,  166,  469,  442,
  429,   52,  197,  130,  167,  167,  168,  168,  167,  193,
  168,  131,  195,  132,  196,  133,    0,    0,    0,    0,
    0,    0,   53,  463,    0,    0,    0,    0,  239,    0,
  344,    0,    0,    0,    0,    0,   54,   55,   63,    0,
    0,   63,    0,   63,   63,   63,    0,    0,    0,  446,
  169,    0,    0,    0,    0,    0,    0,    0,   63,   63,
   63,    0,   63,   63,    0,    0,    0,    0,    0,    0,
  166,    0,  465,    0,    0,    0,  468,    0,  470,    0,
    0,  167,    0,  168,  169,  169,    0,    0,  169,  470,
    0,    0,  240,   63,   63,  198,    0,   16,   17,   18,
  229,   19,  230,  231,    0,  232,  233,  234,  235,  236,
  237,    0,    0,   20,   21,   22,   23,   24,   25,   26,
   27,   28,   29,    0,   63,   63,    0,   30,   31,   32,
   33,   34,   35,   36,   37,  238,   96,   38,   97,  184,
  185,  186,  187,  188,  189,  190,    0,    0,    0,  191,
  192,    0,    0,    0,   69,   69,   69,   69,   69,   69,
   69,  169,    0,    0,    0,    0,    0,    0,   39,   40,
   41,   42,   43,    0,   44,    0,   11,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,   52,
  197,    0,    0,    0,    0,    0,    0,  193,   72,    0,
  195,   72,  196,    0,   72,    0,    0,    0,    0,    0,
   53,    0,    0,    0,    0,    0,  239,    0,   72,   72,
   72,    0,   72,   72,   54,   55,   16,   17,   18,  229,
   19,  230,  231,    0,  232,  233,  234,  235,  236,  237,
  456,  457,   20,   21,   22,   23,   24,   25,   26,   27,
   28,   29,    0,   72,   72,    0,   30,   31,   32,   33,
   34,   35,   36,   37,  238,   96,   38,   97,  184,  185,
  186,  187,  188,  189,  190,    0,    0,    0,  191,  192,
  240,    0,  241,  198,   72,   72,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,   39,   40,   41,
   42,   43,    0,   44,    0,    0,    0,   63,   63,    0,
    0,   63,   63,   63,   63,   63,   63,   63,   52,  197,
    0,   78,    0,    0,   78,    0,  193,   78,    0,  195,
    0,  196,    0,    0,    0,    0,    0,    0,    0,   53,
    0,   78,   78,    0,   88,  239,   78,   88,    0,    0,
    0,    0,    0,   54,   55,    0,    0,    0,    0,    0,
    0,   88,   88,    0,    0,    0,   88,    0,    0,  148,
    0,    0,    0,    0,    0,    0,   78,   78,    0,    0,
    0,    0,    0,    0,    0,  149,  150,  151,    0,    0,
    0,    0,    0,    0,    0,    0,   88,    0,   30,   31,
   32,   33,   34,    0,    0,    0,    0,   78,   78,  146,
    0,    0,  198,    0,   16,   17,   18,  229,   19,  230,
  231,    0,  232,  233,  234,  235,  236,  237,   88,    0,
   20,   21,   22,   23,   24,   25,   26,   27,   28,   29,
  152,   41,   42,   43,   30,   31,   32,   33,   34,   35,
   36,   37,  238,   96,   38,   97,  184,  185,  186,  187,
  188,  189,  190,    0,    0,    0,  191,  192,    0,    0,
    0,   72,   72,   72,   72,   72,   72,   72,    0,    0,
    0,    0,    0,    0,    0,   39,   40,   41,   42,   43,
    0,   44,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  197,    0,   52,    0,    0,    0,
    0,  193,    0,    0,  195,   74,  196,    0,   74,    0,
    0,   74,    0,    0,    0,    0,    0,   53,    0,    0,
  239,    0,    0,    0,    0,   74,   74,    0,    0,    0,
   74,   54,   55,   16,   17,   18,  229,   19,  230,  231,
    0,  232,  233,  234,  235,  236,  237,    0,    0,   20,
   21,   22,   23,   24,   25,   26,   27,   28,   29,    0,
   74,   74,    0,   30,   31,   32,   33,   34,   35,   36,
   37,  238,   96,   38,   97,  184,  185,  186,  187,  188,
  189,  190,    0,    0,  240,  191,  192,  198,   78,   78,
   78,   74,   74,    0,    0,    0,    0,    0,    0,   80,
    0,    0,   80,    0,   39,   40,   41,   42,   43,   88,
   44,    0,    0,    0,    0,    0,   80,   80,    0,    0,
    0,   80,    0,  237,    0,   52,   85,    0,    0,   85,
  237,    0,    0,  237,    0,  237,    0,    0,    0,    0,
    0,    0,    0,   85,   85,    0,   53,    0,   85,  237,
    0,   80,   80,    0,    0,    0,    0,    0,    0,    0,
   54,   55,   82,    0,    0,   82,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,   85,   82,
   82,    0,   80,   80,   82,    0,  197,    0,    0,    0,
    0,    0,    0,  193,    0,    0,  195,    0,  196,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
   85,    0,  239,  237,   82,    0,  237,    0,   16,   17,
   18,  229,   19,  230,  231,    0,  232,  233,  234,  235,
  236,  237,    0,    0,   20,   21,   22,   23,   24,   25,
   26,   27,   28,   29,    0,   82,   82,    0,   30,   31,
   32,   33,   34,   35,   36,   37,  238,   96,   38,   97,
  184,  185,  186,  187,  188,  189,  190,    0,    0,    0,
  191,  192,    0,    0,    0,    0,    0,    0,    0,  198,
   74,   74,   74,   74,   74,    0,    0,    0,    0,   39,
   40,   41,   42,   43,    0,   44,    0,    0,    0,    0,
    0,    0,    0,    0,  197,    0,    0,    0,    0,    0,
   52,  193,    0,    0,  195,    0,  196,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,   53,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,   54,   55,  237,  237,  237,
  237,  237,  237,  237,    0,  237,  237,  237,  237,  237,
  237,    0,    0,  237,  237,  237,  237,  237,  237,  237,
  237,  237,  237,   80,   80,   80,    0,  237,  237,  237,
  237,  237,  237,  237,  237,  237,  237,  237,  237,  237,
  237,  237,  237,  237,  237,  237,    0,  198,    0,  237,
  237,   85,   85,    0,    0,    0,    0,    0,    0,    0,
   16,   17,   18,    0,   19,    0,    0,    0,  237,  237,
  237,  237,  237,    0,  237,    0,   20,   21,   22,   23,
   24,   25,   26,   27,   28,   29,   82,   82,   82,  237,
   30,   31,   32,   33,   34,   35,   36,   37,    0,   96,
   38,   97,  184,  185,  186,  187,  188,  189,  190,    0,
  237,  197,  191,  192,    0,    0,    0,    0,  193,    0,
    0,  195,    0,  196,  237,  237,    0,    0,    0,    0,
    0,   39,   40,   41,   42,   43,  319,   44,    0,    0,
    0,    0,    0,  325,    0,    0,    0,  197,    0,    0,
    0,    0,   52,    0,  193,    0,    0,  195,    0,  196,
    0,    0,    0,    0,    0,  197,    0,    0,    0,    0,
    0,  194,  193,   53,    0,  195,    0,  196,   16,   17,
   18,    0,   92,    0,    0,    0,    0,   54,   55,    0,
    0,  337,    0,    0,   20,   93,   94,   23,   95,   25,
   26,   27,   28,   29,  198,    0,    0,  322,   30,   31,
   32,   33,   34,   35,   36,   37,    0,   96,   38,   97,
  184,  185,  186,  187,  188,  189,  190,  197,    0,    0,
  191,  192,    0,  398,  193,    0,    0,  195,    0,  196,
  198,  325,    0,    0,  325,    0,    0,  197,    0,   98,
   99,   41,   42,   43,  193,    0,    0,  195,  198,  196,
    0,   64,    0,  414,   64,    0,   64,   64,   64,    0,
   52,    0,    0,    0,    0,    0,  415,   83,    0,  325,
   83,   64,   64,   64,    0,   64,   64,    0,    0,    0,
    0,   53,    0,    0,   83,   83,    0,    0,   75,   83,
    0,   75,    0,    0,   75,   54,   55,    0,    0,    0,
    0,    0,    0,    0,    0,    0,   64,   64,   75,   75,
  198,    0,    0,   75,    0,    0,    0,   56,    0,   83,
    0,    0,    0,    0,    0,    0,  325,   18,    0,    0,
  198,  440,    0,  325,    0,    0,    0,   64,   64,    0,
    0,    0,    0,   75,   75,    0,    0,    0,    0,    0,
    0,   83,    0,    0,    0,    0,    0,  325,    0,    0,
    0,   36,   37,   18,   96,   38,   97,  184,  185,  186,
  187,  188,  189,  190,   75,   75,    0,  191,  192,    0,
    0,   18,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,   36,   37,    0,
   96,   38,   97,  184,  185,  186,  187,  188,  189,  190,
    0,    0,    0,  191,  192,   36,   37,    3,   96,   38,
   97,  184,  185,  186,  187,  188,  189,  190,    0,    0,
    0,  191,  192,    0,    0,    0,    0,    0,   53,    0,
    0,    0,    0,   18,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,   18,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,   53,    0,    0,   36,   37,    0,
   96,   38,   97,  184,  185,  186,  187,  188,  189,  190,
    0,    0,   53,  191,  192,    0,    0,   36,  318,    0,
   96,   38,   97,  184,  185,  186,  187,  188,  189,  190,
    0,    0,    0,  191,  192,   16,   17,   18,   56,   19,
   64,   64,    0,    0,   64,   64,   64,   64,   64,   64,
   64,   20,   21,   22,   23,   24,   25,   26,   27,   28,
   29,   83,   83,   83,    0,   30,   31,   32,   33,   34,
   35,   36,   37,    0,   53,   38,    0,    0,    0,    0,
    0,    0,    0,   75,   75,   75,   75,   75,    0,    0,
    0,    0,    0,    0,   53,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,   39,   40,   41,   42,
   43,    0,   44,    0,   11,    0,    0,    0,    0,    0,
   45,   46,   47,   48,   49,   50,   51,   52,    0,    0,
    0,    0,    0,    0,    0,    3,    3,    3,    1,    3,
    0,    0,    0,    0,    0,    0,    0,    0,   53,    0,
    0,    3,    3,    3,    3,    3,    3,    3,    3,    3,
    3,    0,   54,   55,    0,    3,    3,    3,    3,    3,
    3,    3,    3,    0,    0,    3,    0,   59,   59,    0,
    0,   59,   59,   59,   59,   59,    0,   59,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,   59,   59,
   59,    0,   59,   59,    0,    0,    3,    3,    3,    3,
    3,    0,    3,    0,    3,    0,    0,    0,    0,    0,
    3,    3,    3,    3,    3,    3,    3,    3,   86,    0,
    0,   86,    0,   59,   59,    0,   16,   17,   18,    0,
   19,    0,    0,    0,    0,   86,   86,    0,    3,    0,
   86,    0,   20,   21,   22,   23,   24,   25,   26,   27,
   28,   29,    3,    3,   59,   59,   30,   31,   32,   33,
   34,   35,   36,   37,    0,    0,   38,    0,    0,    0,
   86,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,   51,   51,    0,   50,   51,   51,
   51,   51,   51,    0,   51,    0,    0,   39,   40,   41,
   42,   43,   86,   44,    0,   51,   51,   51,   51,   51,
   51,   45,   46,   47,   48,   49,   50,   51,   52,    0,
    0,    0,    0,    0,    0,    0,    1,    1,    1,    0,
    1,    0,    0,    0,    0,    0,    0,    0,    0,   53,
   51,   51,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    0,   54,   55,    0,    1,    1,    1,    1,
    1,    1,    1,    1,    0,    0,    1,    0,    0,    0,
   65,   51,   51,   65,    0,   65,   65,   65,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
   65,   65,   65,    0,   65,   65,    0,    1,    1,    1,
    1,    1,    0,    1,    0,    0,   84,    0,    0,   84,
    0,    1,    1,    1,    1,    1,    1,    1,    1,    0,
    0,    0,    0,   84,   84,   65,   65,    0,   84,    0,
    0,    0,    0,    0,    0,    0,    0,   59,   59,    1,
    0,   59,   59,   59,   59,   59,   59,   59,    0,   66,
    0,    0,   66,    1,    1,   66,   65,   65,   84,    0,
   67,    0,    0,   67,    0,    0,   67,    0,    0,   66,
   66,   66,    0,   66,   66,    0,    0,    0,    0,    0,
   67,   67,   67,    0,   67,   67,    0,    0,    0,   68,
   84,    0,   68,   86,   86,   68,    0,   73,    0,    0,
   73,    0,    0,   73,   66,   66,    0,    0,    0,   68,
   68,   68,    0,   68,   68,   67,   67,   73,   73,   73,
    0,   73,   73,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,   66,   66,    0,    0,    0,
    0,    0,    0,    0,   68,   68,   67,   67,    0,    0,
    0,    0,   73,   73,   51,   51,    0,    0,   51,   51,
   51,   51,   51,   51,   51,   51,   51,   51,   51,   51,
   51,   51,   51,   51,   51,   68,   68,    0,    0,   70,
    0,    0,   70,   73,   73,   70,   71,    0,    0,   71,
    0,    0,   71,    0,    0,    0,    0,    0,    0,   70,
   70,   70,    0,   70,   70,    0,   71,   71,   71,    0,
   71,   71,   76,    0,    0,   76,    0,    0,   76,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,   76,   76,   70,   70,    0,   76,    0,   65,
   65,   71,   71,   65,   65,   65,   65,   65,   65,   65,
    0,    0,    0,    0,    0,    0,    0,  289,    0,    0,
    0,    0,    0,    0,    0,   70,   70,   76,   76,    0,
    0,    0,   71,   71,  275,    0,    0,    0,    0,    0,
   84,   84,   84,  101,  106,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,   76,   76,
  338,  118,    0,  120,  122,  123,  128,  134,  137,    0,
    0,    0,    0,    0,    0,    0,    0,    0,   66,   66,
    0,    0,   66,   66,   66,   66,   66,   66,   66,   67,
   67,    0,    0,   67,   67,   67,   67,   67,   67,   67,
    0,    0,  101,  106,    0,    0,  120,  128,  134,    0,
    0,    0,    0,    0,    0,  376,    0,    0,   68,   68,
    0,    0,   68,   68,   68,   68,   68,   68,   68,    0,
   73,   73,   73,   73,   73,   73,   73,    0,  396,  128,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  367,
    0,    0,    0,    0,    0,    0,    0,    0,  407,    0,
    0,    0,    0,  409,  411,    0,   16,   17,   18,    0,
   92,    0,    0,    0,    0,    0,    0,    0,    0,  214,
    0,    0,   20,   93,   94,   23,   95,   25,   26,   27,
   28,   29,    0,    0,    0,    0,   30,   31,   32,   33,
   34,   35,   36,   37,    0,    0,   38,    0,    0,    0,
    0,    0,   70,   70,   70,   70,   70,   70,   70,   71,
   71,   71,   71,   71,   71,   71,    0,    0,    0,    0,
  411,  287,  288,    0,    0,    0,    0,   98,   99,   41,
   42,   43,    0,    0,    0,    0,    0,   76,   76,   76,
   76,   76,  443,    0,    0,    0,    0,    0,   52,    0,
    0,    0,    0,  320,    0,  214,    0,    0,  453,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,   53,
  466,   16,   17,   18,    0,   92,    0,    0,    0,    0,
    0,    0,    0,   54,   55,    0,    0,   20,   93,   94,
   23,   95,   25,   26,   27,   28,   29,    0,    0,    0,
    0,   30,   31,   32,   33,   34,   35,   36,   37,  214,
    0,   38,    0,    0,    0,    0,    0,    0,    0,    0,
  214,    0,  214,  214,  214,  214,  214,  214,  214,  214,
  214,  214,  214,  214,  214,  214,  214,  392,  393,  394,
    0,    0,   98,   99,   41,   42,   43,    0,    0,    0,
    0,    0,    0,    0,    0,  190,  190,  190,    0,  190,
    0,    0,    0,   52,    0,    0,    0,    0,    0,    0,
    0,  190,  190,  190,  190,  190,  190,  190,  190,  190,
  190,    0,    0,    0,   53,  190,  190,  190,  190,  190,
  190,  190,  190,    0,    0,  190,  292,    0,   54,   55,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  186,  186,
  186,    0,  186,    0,    0,    0,  190,  190,  190,  190,
  190,    0,    0,    0,  186,  186,  186,  186,  186,  186,
  186,  186,  186,  186,    0,    0,    0,  190,  186,  186,
  186,  186,  186,  186,  186,  186,    0,    0,  186,  289,
    0,    0,    0,    0,    0,    0,    0,    0,  190,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  190,  190,  187,  187,  187,    0,  187,  186,
  186,  186,  186,  186,    0,    0,    0,    0,    0,    0,
  187,  187,  187,  187,  187,  187,  187,  187,  187,  187,
  186,    0,    0,    0,  187,  187,  187,  187,  187,  187,
  187,  187,    0,    0,  187,  290,    0,    0,    0,    0,
    0,  186,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  186,  186,  189,  189,  189,
    0,  189,    0,    0,    0,  187,  187,  187,  187,  187,
    0,    0,    0,  189,  189,  189,  189,  189,  189,  189,
  189,  189,  189,    0,    0,    0,  187,  189,  189,  189,
  189,  189,  189,  189,  189,    0,    0,  189,  291,    0,
    0,    0,    0,    0,    0,    0,    0,  187,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  187,  187,   16,   17,   18,    0,   92,  189,  189,
  189,  189,  189,    0,    0,    0,    0,    0,    0,   20,
   93,   94,   23,   95,   25,   26,   27,   28,   29,  189,
    0,    0,    0,   30,   31,   32,   33,   34,   35,   36,
   37,    0,    0,   38,    0,    0,    0,    0,    0,    0,
  189,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  189,  189,  155,  155,  155,    0,
  155,    0,    0,    0,   98,   99,   41,   42,   43,    0,
    0,    0,  155,  155,  155,  155,  155,  155,  155,  155,
  155,  155,    0,    0,    0,   52,  155,  155,  155,  155,
  155,  155,  155,  155,    0,    0,  155,    0,    0,    0,
    0,    0,    0,    0,    0,    0,   53,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
   54,   55,   16,   17,    0,    0,   92,  155,  155,  155,
  155,  155,    0,    0,    0,    0,    0,    0,   20,   93,
   94,   23,   95,   25,   26,   27,   28,   29,  155,    0,
    0,    0,   30,   31,   32,   33,   34,   35,    0,    0,
    0,   96,    0,   97,    0,    0,    0,    0,    0,  155,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,  155,  155,   16,   17,    0,    0,   92,
    0,    0,    0,   98,   99,   41,   42,   43,    0,    0,
    0,   20,   93,   94,   23,   95,   25,   26,   27,   28,
   29,    0,    0,    0,   52,   30,   31,   32,   33,   34,
   35,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,   54,
   55,   16,   17,    0,    0,   19,   98,   99,   41,   42,
   43,    0,    0,    0,    0,    0,    0,   20,   21,   22,
   23,   24,   25,   26,   27,   28,   29,   52,    0,    0,
    0,   30,   31,   32,   33,   34,   35,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,   54,   55,   16,   17,    0,    0,  124,    0,
    0,    0,   98,   99,   41,   42,   43,    0,    0,    0,
   20,  125,  126,   23,  127,   25,   26,   27,   28,   29,
    0,    0,    0,   52,   30,   31,   32,   33,   34,   35,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,   54,   55,
    0,    0,    0,    0,    0,   98,   99,   41,   42,   43,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,   52,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,   54,   55,
};
static const YYINT _mesa_glsl_check[] = {                12,
   12,   44,   41,   39,   40,    4,   63,  123,  143,   60,
  231,   62,   11,  125,   40,   91,  125,  166,   44,   90,
  125,   57,    5,   12,   60,   61,   12,   61,   64,  125,
   62,   63,   59,   59,   12,   41,  335,   36,   44,  139,
  301,   61,   40,   41,  225,   58,   44,   41,   39,   40,
   62,   63,   58,   59,   90,   40,   41,   91,  336,   71,
  339,   59,   98,   99,  338,   59,  102,  103,  104,   44,
   69,   91,  339,  259,   61,   88,   88,   90,   69,   61,
  339,   33,  125,   58,   62,   63,   44,   93,   40,  339,
   89,   43,  339,   45,  107,  166,  123,  168,  279,   88,
   44,   59,   88,  135,   91,   88,   91,  293,  294,   91,
   88,  297,  183,   44,   33,   59,  115,   41,  117,  125,
   44,   40,  339,  135,   43,  225,   45,   58,  277,   44,
  166,  339,  168,  146,  146,  270,  148,  272,  435,  339,
  152,  153,  154,  156,   59,  157,  158,  183,  445,   41,
   40,   41,   44,  166,   44,  168,   43,  135,   45,  271,
  272,  160,  271,  272,  259,  259,  271,  272,  146,   59,
  183,  123,   44,  125,  126,  271,  272,   44,  156,  279,
  296,  297,  298,   41,  370,   37,   44,   59,   44,   44,
   42,   38,   59,   44,   41,   47,   40,   44,  293,  294,
   58,   59,  297,   59,  123,   63,  277,  126,   59,  298,
   41,   58,   59,   44,  435,  286,   63,   40,  231,  231,
  259,   44,   44,   40,  445,   91,  361,   58,   59,   41,
  243,  243,   63,  309,  310,   93,   59,   59,   61,  292,
  123,  277,   44,  296,  297,  298,   93,   94,   59,   41,
  286,  264,   44,  231,  293,  294,   59,   59,  297,  316,
  311,  312,   93,   94,  277,  243,  265,  125,   91,  340,
  296,  297,  298,  286,  350,  370,   33,  124,  125,  296,
  297,  298,  281,   40,  283,   59,   43,  422,   45,  313,
  314,   44,   40,  124,  125,  123,   44,   61,  296,  297,
  298,   44,   59,   59,  340,  358,   59,  259,   44,   41,
  349,   59,   44,   61,   91,   41,   59,   40,   44,   59,
  333,  333,  339,   59,  339,  259,   61,  340,  124,  342,
  342,  370,   58,   59,  315,  406,   41,   63,  391,   44,
  259,  293,  294,   91,  296,  297,  298,  299,  300,  301,
  302,  303,  304,  305,  259,  333,  317,  309,  310,  293,
  294,  360,   41,  297,  342,   44,  123,   93,  125,  126,
  406,  307,  308,   41,  293,  294,   44,  296,  297,  298,
  299,  300,  301,  302,  303,  304,  305,   38,  293,  294,
  309,  310,  297,  406,   41,  297,  298,   44,  124,  125,
  413,  413,  296,  297,  298,   33,  296,  297,  298,   94,
   41,  410,   40,   44,   41,   43,   93,   45,  370,  432,
  432,  148,  435,  435,   40,  152,  153,  154,  303,  304,
  157,   59,  445,  445,   41,  413,  370,   44,  259,   59,
  259,   59,  455,  455,  349,   40,  459,  459,  461,  461,
   40,  370,   40,  259,  432,  259,   59,  435,  316,  472,
  472,  299,  300,  301,  302,  370,   59,  445,  315,  316,
  317,  125,  293,  294,  293,  294,  297,  455,  297,   41,
   40,  459,   44,  461,  315,  316,  317,  293,  294,  293,
  294,  297,  125,  297,  472,  123,   59,  125,  126,  306,
  257,  258,  259,  260,  261,  262,  263,   93,  265,  266,
  267,  268,  269,  270,  271,  272,  273,  274,  275,  276,
  277,  278,  279,  280,  281,  282,  305,  306,  349,  295,
  287,  288,  289,  290,  291,  292,  293,  294,  295,  296,
  297,  298,  299,  300,  301,  302,  303,  304,  305,  370,
   44,  370,  309,  310,  318,  319,  320,  321,  322,  323,
  324,  325,  326,  327,  370,  298,  370,  330,  331,  332,
   93,  328,  329,  330,  331,  332,   40,  334,   41,  336,
  243,  296,  297,  298,   59,   44,   59,   41,  123,  315,
  316,  317,  349,   33,   61,  264,   41,   59,   58,    0,
   40,   38,   41,   43,   41,   45,  125,   44,   59,   93,
   59,   59,   71,  370,   41,   59,   41,  324,  342,   59,
  327,   58,   59,   60,  281,   62,   63,  384,  385,  257,
  258,  259,  260,  261,  262,  263,   59,  265,  266,  267,
  268,  269,  270,  158,   70,  273,  274,  275,  276,  277,
  278,  279,  280,  281,  282,  362,   93,   94,  333,  287,
  288,  289,  290,  291,  292,  293,  294,  295,  296,  297,
  298,  299,  300,  301,  302,  303,  304,  305,  290,  259,
  293,  309,  310,  123,  292,  125,  126,  124,  125,  148,
  259,  295,  259,  152,  153,  154,  294,  296,  157,  158,
  328,  329,  330,  331,  332,   88,  334,  333,  336,  365,
  168,  284,  419,  293,  294,  286,  462,  297,  459,  426,
  406,  349,   33,   62,  293,  294,  293,  294,  297,   40,
  297,   62,   43,   62,   45,   62,   -1,   -1,   -1,   -1,
   -1,   -1,  370,  450,   -1,   -1,   -1,   -1,   59,   -1,
  413,   -1,   -1,   -1,   -1,   -1,  384,  385,   38,   -1,
   -1,   41,   -1,   43,   44,   45,   -1,   -1,   -1,  432,
  259,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   58,   59,
   60,   -1,   62,   63,   -1,   -1,   -1,   -1,   -1,   -1,
  370,   -1,  455,   -1,   -1,   -1,  459,   -1,  461,   -1,
   -1,  370,   -1,  370,  293,  294,   -1,   -1,  297,  472,
   -1,   -1,  123,   93,   94,  126,   -1,  257,  258,  259,
  260,  261,  262,  263,   -1,  265,  266,  267,  268,  269,
  270,   -1,   -1,  273,  274,  275,  276,  277,  278,  279,
  280,  281,  282,   -1,  124,  125,   -1,  287,  288,  289,
  290,  291,  292,  293,  294,  295,  296,  297,  298,  299,
  300,  301,  302,  303,  304,  305,   -1,   -1,   -1,  309,
  310,   -1,   -1,   -1,  311,  312,  313,  314,  315,  316,
  317,  370,   -1,   -1,   -1,   -1,   -1,   -1,  328,  329,
  330,  331,  332,   -1,  334,   -1,  336,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  349,
   33,   -1,   -1,   -1,   -1,   -1,   -1,   40,   38,   -1,
   43,   41,   45,   -1,   44,   -1,   -1,   -1,   -1,   -1,
  370,   -1,   -1,   -1,   -1,   -1,   59,   -1,   58,   59,
   60,   -1,   62,   63,  384,  385,  257,  258,  259,  260,
  261,  262,  263,   -1,  265,  266,  267,  268,  269,  270,
  271,  272,  273,  274,  275,  276,  277,  278,  279,  280,
  281,  282,   -1,   93,   94,   -1,  287,  288,  289,  290,
  291,  292,  293,  294,  295,  296,  297,  298,  299,  300,
  301,  302,  303,  304,  305,   -1,   -1,   -1,  309,  310,
  123,   -1,  125,  126,  124,  125,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  328,  329,  330,
  331,  332,   -1,  334,   -1,   -1,   -1,  307,  308,   -1,
   -1,  311,  312,  313,  314,  315,  316,  317,  349,   33,
   -1,   38,   -1,   -1,   41,   -1,   40,   44,   -1,   43,
   -1,   45,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  370,
   -1,   58,   59,   -1,   41,   59,   63,   44,   -1,   -1,
   -1,   -1,   -1,  384,  385,   -1,   -1,   -1,   -1,   -1,
   -1,   58,   59,   -1,   -1,   -1,   63,   -1,   -1,  258,
   -1,   -1,   -1,   -1,   -1,   -1,   93,   94,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  274,  275,  276,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   93,   -1,  287,  288,
  289,  290,  291,   -1,   -1,   -1,   -1,  124,  125,  123,
   -1,   -1,  126,   -1,  257,  258,  259,  260,  261,  262,
  263,   -1,  265,  266,  267,  268,  269,  270,  125,   -1,
  273,  274,  275,  276,  277,  278,  279,  280,  281,  282,
  329,  330,  331,  332,  287,  288,  289,  290,  291,  292,
  293,  294,  295,  296,  297,  298,  299,  300,  301,  302,
  303,  304,  305,   -1,   -1,   -1,  309,  310,   -1,   -1,
   -1,  311,  312,  313,  314,  315,  316,  317,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  328,  329,  330,  331,  332,
   -1,  334,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   33,   -1,  349,   -1,   -1,   -1,
   -1,   40,   -1,   -1,   43,   38,   45,   -1,   41,   -1,
   -1,   44,   -1,   -1,   -1,   -1,   -1,  370,   -1,   -1,
   59,   -1,   -1,   -1,   -1,   58,   59,   -1,   -1,   -1,
   63,  384,  385,  257,  258,  259,  260,  261,  262,  263,
   -1,  265,  266,  267,  268,  269,  270,   -1,   -1,  273,
  274,  275,  276,  277,  278,  279,  280,  281,  282,   -1,
   93,   94,   -1,  287,  288,  289,  290,  291,  292,  293,
  294,  295,  296,  297,  298,  299,  300,  301,  302,  303,
  304,  305,   -1,   -1,  123,  309,  310,  126,  315,  316,
  317,  124,  125,   -1,   -1,   -1,   -1,   -1,   -1,   41,
   -1,   -1,   44,   -1,  328,  329,  330,  331,  332,  316,
  334,   -1,   -1,   -1,   -1,   -1,   58,   59,   -1,   -1,
   -1,   63,   -1,   33,   -1,  349,   41,   -1,   -1,   44,
   40,   -1,   -1,   43,   -1,   45,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   58,   59,   -1,  370,   -1,   63,   59,
   -1,   93,   94,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  384,  385,   41,   -1,   -1,   44,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   93,   58,
   59,   -1,  124,  125,   63,   -1,   33,   -1,   -1,   -1,
   -1,   -1,   -1,   40,   -1,   -1,   43,   -1,   45,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  125,   -1,   59,  123,   93,   -1,  126,   -1,  257,  258,
  259,  260,  261,  262,  263,   -1,  265,  266,  267,  268,
  269,  270,   -1,   -1,  273,  274,  275,  276,  277,  278,
  279,  280,  281,  282,   -1,  124,  125,   -1,  287,  288,
  289,  290,  291,  292,  293,  294,  295,  296,  297,  298,
  299,  300,  301,  302,  303,  304,  305,   -1,   -1,   -1,
  309,  310,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  126,
  313,  314,  315,  316,  317,   -1,   -1,   -1,   -1,  328,
  329,  330,  331,  332,   -1,  334,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   33,   -1,   -1,   -1,   -1,   -1,
  349,   40,   -1,   -1,   43,   -1,   45,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  370,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  384,  385,  257,  258,  259,
  260,  261,  262,  263,   -1,  265,  266,  267,  268,  269,
  270,   -1,   -1,  273,  274,  275,  276,  277,  278,  279,
  280,  281,  282,  315,  316,  317,   -1,  287,  288,  289,
  290,  291,  292,  293,  294,  295,  296,  297,  298,  299,
  300,  301,  302,  303,  304,  305,   -1,  126,   -1,  309,
  310,  316,  317,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  257,  258,  259,   -1,  261,   -1,   -1,   -1,  328,  329,
  330,  331,  332,   -1,  334,   -1,  273,  274,  275,  276,
  277,  278,  279,  280,  281,  282,  315,  316,  317,  349,
  287,  288,  289,  290,  291,  292,  293,  294,   -1,  296,
  297,  298,  299,  300,  301,  302,  303,  304,  305,   -1,
  370,   33,  309,  310,   -1,   -1,   -1,   -1,   40,   -1,
   -1,   43,   -1,   45,  384,  385,   -1,   -1,   -1,   -1,
   -1,  328,  329,  330,  331,  332,  219,  334,   -1,   -1,
   -1,   -1,   -1,  226,   -1,   -1,   -1,   33,   -1,   -1,
   -1,   -1,  349,   -1,   40,   -1,   -1,   43,   -1,   45,
   -1,   -1,   -1,   -1,   -1,   33,   -1,   -1,   -1,   -1,
   -1,   93,   40,  370,   -1,   43,   -1,   45,  257,  258,
  259,   -1,  261,   -1,   -1,   -1,   -1,  384,  385,   -1,
   -1,   59,   -1,   -1,  273,  274,  275,  276,  277,  278,
  279,  280,  281,  282,  126,   -1,   -1,   93,  287,  288,
  289,  290,  291,  292,  293,  294,   -1,  296,  297,  298,
  299,  300,  301,  302,  303,  304,  305,   33,   -1,   -1,
  309,  310,   -1,  316,   40,   -1,   -1,   43,   -1,   45,
  126,  324,   -1,   -1,  327,   -1,   -1,   33,   -1,  328,
  329,  330,  331,  332,   40,   -1,   -1,   43,  126,   45,
   -1,   38,   -1,  346,   41,   -1,   43,   44,   45,   -1,
  349,   -1,   -1,   -1,   -1,   -1,  359,   41,   -1,  362,
   44,   58,   59,   60,   -1,   62,   63,   -1,   -1,   -1,
   -1,  370,   -1,   -1,   58,   59,   -1,   -1,   38,   63,
   -1,   41,   -1,   -1,   44,  384,  385,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   93,   94,   58,   59,
  126,   -1,   -1,   63,   -1,   -1,   -1,   59,   -1,   93,
   -1,   -1,   -1,   -1,   -1,   -1,  419,  259,   -1,   -1,
  126,  424,   -1,  426,   -1,   -1,   -1,  124,  125,   -1,
   -1,   -1,   -1,   93,   94,   -1,   -1,   -1,   -1,   -1,
   -1,  125,   -1,   -1,   -1,   -1,   -1,  450,   -1,   -1,
   -1,  293,  294,  259,  296,  297,  298,  299,  300,  301,
  302,  303,  304,  305,  124,  125,   -1,  309,  310,   -1,
   -1,  259,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  293,  294,   -1,
  296,  297,  298,  299,  300,  301,  302,  303,  304,  305,
   -1,   -1,   -1,  309,  310,  293,  294,   59,  296,  297,
  298,  299,  300,  301,  302,  303,  304,  305,   -1,   -1,
   -1,  309,  310,   -1,   -1,   -1,   -1,   -1,  370,   -1,
   -1,   -1,   -1,  259,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  259,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  370,   -1,   -1,  293,  294,   -1,
  296,  297,  298,  299,  300,  301,  302,  303,  304,  305,
   -1,   -1,  370,  309,  310,   -1,   -1,  293,  294,   -1,
  296,  297,  298,  299,  300,  301,  302,  303,  304,  305,
   -1,   -1,   -1,  309,  310,  257,  258,  259,   59,  261,
  307,  308,   -1,   -1,  311,  312,  313,  314,  315,  316,
  317,  273,  274,  275,  276,  277,  278,  279,  280,  281,
  282,  315,  316,  317,   -1,  287,  288,  289,  290,  291,
  292,  293,  294,   -1,  370,  297,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  313,  314,  315,  316,  317,   -1,   -1,
   -1,   -1,   -1,   -1,  370,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  328,  329,  330,  331,
  332,   -1,  334,   -1,  336,   -1,   -1,   -1,   -1,   -1,
  342,  343,  344,  345,  346,  347,  348,  349,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  257,  258,  259,   59,  261,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  370,   -1,
   -1,  273,  274,  275,  276,  277,  278,  279,  280,  281,
  282,   -1,  384,  385,   -1,  287,  288,  289,  290,  291,
  292,  293,  294,   -1,   -1,  297,   -1,   37,   38,   -1,
   -1,   41,   42,   43,   44,   45,   -1,   47,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   58,   59,
   60,   -1,   62,   63,   -1,   -1,  328,  329,  330,  331,
  332,   -1,  334,   -1,  336,   -1,   -1,   -1,   -1,   -1,
  342,  343,  344,  345,  346,  347,  348,  349,   41,   -1,
   -1,   44,   -1,   93,   94,   -1,  257,  258,  259,   -1,
  261,   -1,   -1,   -1,   -1,   58,   59,   -1,  370,   -1,
   63,   -1,  273,  274,  275,  276,  277,  278,  279,  280,
  281,  282,  384,  385,  124,  125,  287,  288,  289,  290,
  291,  292,  293,  294,   -1,   -1,  297,   -1,   -1,   -1,
   93,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   37,   38,   -1,   40,   41,   42,
   43,   44,   45,   -1,   47,   -1,   -1,  328,  329,  330,
  331,  332,  125,  334,   -1,   58,   59,   60,   61,   62,
   63,  342,  343,  344,  345,  346,  347,  348,  349,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  257,  258,  259,   -1,
  261,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  370,
   93,   94,  273,  274,  275,  276,  277,  278,  279,  280,
  281,  282,   -1,  384,  385,   -1,  287,  288,  289,  290,
  291,  292,  293,  294,   -1,   -1,  297,   -1,   -1,   -1,
   38,  124,  125,   41,   -1,   43,   44,   45,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   58,   59,   60,   -1,   62,   63,   -1,  328,  329,  330,
  331,  332,   -1,  334,   -1,   -1,   41,   -1,   -1,   44,
   -1,  342,  343,  344,  345,  346,  347,  348,  349,   -1,
   -1,   -1,   -1,   58,   59,   93,   94,   -1,   63,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  307,  308,  370,
   -1,  311,  312,  313,  314,  315,  316,  317,   -1,   38,
   -1,   -1,   41,  384,  385,   44,  124,  125,   93,   -1,
   38,   -1,   -1,   41,   -1,   -1,   44,   -1,   -1,   58,
   59,   60,   -1,   62,   63,   -1,   -1,   -1,   -1,   -1,
   58,   59,   60,   -1,   62,   63,   -1,   -1,   -1,   38,
  125,   -1,   41,  316,  317,   44,   -1,   38,   -1,   -1,
   41,   -1,   -1,   44,   93,   94,   -1,   -1,   -1,   58,
   59,   60,   -1,   62,   63,   93,   94,   58,   59,   60,
   -1,   62,   63,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  124,  125,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   93,   94,  124,  125,   -1,   -1,
   -1,   -1,   93,   94,  307,  308,   -1,   -1,  311,  312,
  313,  314,  315,  316,  317,  318,  319,  320,  321,  322,
  323,  324,  325,  326,  327,  124,  125,   -1,   -1,   38,
   -1,   -1,   41,  124,  125,   44,   38,   -1,   -1,   41,
   -1,   -1,   44,   -1,   -1,   -1,   -1,   -1,   -1,   58,
   59,   60,   -1,   62,   63,   -1,   58,   59,   60,   -1,
   62,   63,   38,   -1,   -1,   41,   -1,   -1,   44,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   58,   59,   93,   94,   -1,   63,   -1,  307,
  308,   93,   94,  311,  312,  313,  314,  315,  316,  317,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  193,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  124,  125,   93,   94,   -1,
   -1,   -1,  124,  125,  125,   -1,   -1,   -1,   -1,   -1,
  315,  316,  317,   39,   40,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  124,  125,
  236,   57,   -1,   59,   60,   61,   62,   63,   64,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  307,  308,
   -1,   -1,  311,  312,  313,  314,  315,  316,  317,  307,
  308,   -1,   -1,  311,  312,  313,  314,  315,  316,  317,
   -1,   -1,   98,   99,   -1,   -1,  102,  103,  104,   -1,
   -1,   -1,   -1,   -1,   -1,  291,   -1,   -1,  307,  308,
   -1,   -1,  311,  312,  313,  314,  315,  316,  317,   -1,
  311,  312,  313,  314,  315,  316,  317,   -1,  314,  135,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  125,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  334,   -1,
   -1,   -1,   -1,  339,  340,   -1,  257,  258,  259,   -1,
  261,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  139,
   -1,   -1,  273,  274,  275,  276,  277,  278,  279,  280,
  281,  282,   -1,   -1,   -1,   -1,  287,  288,  289,  290,
  291,  292,  293,  294,   -1,   -1,  297,   -1,   -1,   -1,
   -1,   -1,  311,  312,  313,  314,  315,  316,  317,  311,
  312,  313,  314,  315,  316,  317,   -1,   -1,   -1,   -1,
  406,  191,  192,   -1,   -1,   -1,   -1,  328,  329,  330,
  331,  332,   -1,   -1,   -1,   -1,   -1,  313,  314,  315,
  316,  317,  428,   -1,   -1,   -1,   -1,   -1,  349,   -1,
   -1,   -1,   -1,  223,   -1,  225,   -1,   -1,  444,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  370,
  456,  257,  258,  259,   -1,  261,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  384,  385,   -1,   -1,  273,  274,  275,
  276,  277,  278,  279,  280,  281,  282,   -1,   -1,   -1,
   -1,  287,  288,  289,  290,  291,  292,  293,  294,  279,
   -1,  297,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  290,   -1,  292,  293,  294,  295,  296,  297,  298,  299,
  300,  301,  302,  303,  304,  305,  306,  307,  308,  309,
   -1,   -1,  328,  329,  330,  331,  332,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  257,  258,  259,   -1,  261,
   -1,   -1,   -1,  349,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  273,  274,  275,  276,  277,  278,  279,  280,  281,
  282,   -1,   -1,   -1,  370,  287,  288,  289,  290,  291,
  292,  293,  294,   -1,   -1,  297,  298,   -1,  384,  385,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  257,  258,
  259,   -1,  261,   -1,   -1,   -1,  328,  329,  330,  331,
  332,   -1,   -1,   -1,  273,  274,  275,  276,  277,  278,
  279,  280,  281,  282,   -1,   -1,   -1,  349,  287,  288,
  289,  290,  291,  292,  293,  294,   -1,   -1,  297,  298,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  370,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  384,  385,  257,  258,  259,   -1,  261,  328,
  329,  330,  331,  332,   -1,   -1,   -1,   -1,   -1,   -1,
  273,  274,  275,  276,  277,  278,  279,  280,  281,  282,
  349,   -1,   -1,   -1,  287,  288,  289,  290,  291,  292,
  293,  294,   -1,   -1,  297,  298,   -1,   -1,   -1,   -1,
   -1,  370,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  384,  385,  257,  258,  259,
   -1,  261,   -1,   -1,   -1,  328,  329,  330,  331,  332,
   -1,   -1,   -1,  273,  274,  275,  276,  277,  278,  279,
  280,  281,  282,   -1,   -1,   -1,  349,  287,  288,  289,
  290,  291,  292,  293,  294,   -1,   -1,  297,  298,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  370,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  384,  385,  257,  258,  259,   -1,  261,  328,  329,
  330,  331,  332,   -1,   -1,   -1,   -1,   -1,   -1,  273,
  274,  275,  276,  277,  278,  279,  280,  281,  282,  349,
   -1,   -1,   -1,  287,  288,  289,  290,  291,  292,  293,
  294,   -1,   -1,  297,   -1,   -1,   -1,   -1,   -1,   -1,
  370,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  384,  385,  257,  258,  259,   -1,
  261,   -1,   -1,   -1,  328,  329,  330,  331,  332,   -1,
   -1,   -1,  273,  274,  275,  276,  277,  278,  279,  280,
  281,  282,   -1,   -1,   -1,  349,  287,  288,  289,  290,
  291,  292,  293,  294,   -1,   -1,  297,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  370,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  384,  385,  257,  258,   -1,   -1,  261,  328,  329,  330,
  331,  332,   -1,   -1,   -1,   -1,   -1,   -1,  273,  274,
  275,  276,  277,  278,  279,  280,  281,  282,  349,   -1,
   -1,   -1,  287,  288,  289,  290,  291,  292,   -1,   -1,
   -1,  296,   -1,  298,   -1,   -1,   -1,   -1,   -1,  370,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  384,  385,  257,  258,   -1,   -1,  261,
   -1,   -1,   -1,  328,  329,  330,  331,  332,   -1,   -1,
   -1,  273,  274,  275,  276,  277,  278,  279,  280,  281,
  282,   -1,   -1,   -1,  349,  287,  288,  289,  290,  291,
  292,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  384,
  385,  257,  258,   -1,   -1,  261,  328,  329,  330,  331,
  332,   -1,   -1,   -1,   -1,   -1,   -1,  273,  274,  275,
  276,  277,  278,  279,  280,  281,  282,  349,   -1,   -1,
   -1,  287,  288,  289,  290,  291,  292,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  384,  385,  257,  258,   -1,   -1,  261,   -1,
   -1,   -1,  328,  329,  330,  331,  332,   -1,   -1,   -1,
  273,  274,  275,  276,  277,  278,  279,  280,  281,  282,
   -1,   -1,   -1,  349,  287,  288,  289,  290,  291,  292,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  384,  385,
   -1,   -1,   -1,   -1,   -1,  328,  329,  330,  331,  332,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  349,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  384,  385,
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
   -1,   -1,
};
#endif
#define YYFINAL 2
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 392
#define YYUNDFTOKEN 504
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
"FLOATCONSTANT","DOUBLECONSTANT","INTCONSTANT","UINTCONSTANT","BOOLCONSTANT",
"INT64CONSTANT","UINT64CONSTANT","FIELD_SELECTION","LEFT_OP","RIGHT_OP",
"INC_OP","DEC_OP","LE_OP","GE_OP","EQ_OP","NE_OP","AND_OP","OR_OP","XOR_OP",
"MUL_ASSIGN","DIV_ASSIGN","ADD_ASSIGN","MOD_ASSIGN","LEFT_ASSIGN",
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

#line 88 "../mesa/src/compiler/glsl/glsl_parser.yy"
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
#line 294 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      _mesa_glsl_initialize_types(state);
   }
#line 3155 "compiler/glsl/glsl_parser.cpp"
break;
case 2:
#line 298 "../mesa/src/compiler/glsl/glsl_parser.yy"
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
#line 3176 "compiler/glsl/glsl_parser.cpp"
break;
case 4:
#line 320 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      state->process_version_directive(&yystack.p_mark[-1], yystack.l_mark[-1].n, NULL);
      if (state->error) {
         YYERROR;
      }
   }
#line 3186 "compiler/glsl/glsl_parser.cpp"
break;
case 5:
#line 327 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      state->process_version_directive(&yystack.p_mark[-2], yystack.l_mark[-2].n, yystack.l_mark[-1].identifier);
      if (state->error) {
         YYERROR;
      }
   }
#line 3196 "compiler/glsl/glsl_parser.cpp"
break;
case 6:
#line 336 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{ yyval.node = NULL; }
#line 3201 "compiler/glsl/glsl_parser.cpp"
break;
case 7:
#line 337 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{ yyval.node = NULL; }
#line 3206 "compiler/glsl/glsl_parser.cpp"
break;
case 8:
#line 338 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{ yyval.node = NULL; }
#line 3211 "compiler/glsl/glsl_parser.cpp"
break;
case 9:
#line 339 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{ yyval.node = NULL; }
#line 3216 "compiler/glsl/glsl_parser.cpp"
break;
case 10:
#line 341 "../mesa/src/compiler/glsl/glsl_parser.yy"
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
#line 3243 "compiler/glsl/glsl_parser.cpp"
break;
case 11:
#line 365 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      void *mem_ctx = state->linalloc;
      yyval.node = new(mem_ctx) ast_warnings_toggle(true);
   }
#line 3251 "compiler/glsl/glsl_parser.cpp"
break;
case 12:
#line 370 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      void *mem_ctx = state->linalloc;
      yyval.node = new(mem_ctx) ast_warnings_toggle(false);
   }
#line 3259 "compiler/glsl/glsl_parser.cpp"
break;
case 18:
#line 389 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      if (!_mesa_glsl_process_extension(yystack.l_mark[-3].identifier, & yystack.p_mark[-3], yystack.l_mark[-1].identifier, & yystack.p_mark[-1], state)) {
         YYERROR;
      }
   }
#line 3268 "compiler/glsl/glsl_parser.cpp"
break;
case 19:
#line 398 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      /* FINISHME: The NULL test is required because pragmas are set to
       * FINISHME: NULL. (See production rule for external_declaration.)
       */
      if (yystack.l_mark[0].node != NULL)
         state->translation_unit.push_tail(& yystack.l_mark[0].node->link);
   }
#line 3279 "compiler/glsl/glsl_parser.cpp"
break;
case 20:
#line 406 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      /* FINISHME: The NULL test is required because pragmas are set to
       * FINISHME: NULL. (See production rule for external_declaration.)
       */
      if (yystack.l_mark[0].node != NULL)
         state->translation_unit.push_tail(& yystack.l_mark[0].node->link);
   }
#line 3290 "compiler/glsl/glsl_parser.cpp"
break;
case 21:
#line 413 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      if (!state->allow_extension_directive_midshader) {
         _mesa_glsl_error(& yystack.p_mark[0], state,
                          "#extension directive is not allowed "
                          "in the middle of a shader");
         YYERROR;
      }
   }
#line 3302 "compiler/glsl/glsl_parser.cpp"
break;
case 24:
#line 430 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      void *ctx = state->linalloc;
      yyval.expression = new(ctx) ast_expression(ast_identifier, NULL, NULL, NULL);
      yyval.expression->set_location(yystack.p_mark[0]);
      yyval.expression->primary_expression.identifier = yystack.l_mark[0].identifier;
   }
#line 3312 "compiler/glsl/glsl_parser.cpp"
break;
case 25:
#line 437 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      void *ctx = state->linalloc;
      yyval.expression = new(ctx) ast_expression(ast_int_constant, NULL, NULL, NULL);
      yyval.expression->set_location(yystack.p_mark[0]);
      yyval.expression->primary_expression.int_constant = yystack.l_mark[0].n;
   }
#line 3322 "compiler/glsl/glsl_parser.cpp"
break;
case 26:
#line 444 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      void *ctx = state->linalloc;
      yyval.expression = new(ctx) ast_expression(ast_uint_constant, NULL, NULL, NULL);
      yyval.expression->set_location(yystack.p_mark[0]);
      yyval.expression->primary_expression.uint_constant = yystack.l_mark[0].n;
   }
#line 3332 "compiler/glsl/glsl_parser.cpp"
break;
case 27:
#line 451 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      void *ctx = state->linalloc;
      yyval.expression = new(ctx) ast_expression(ast_int64_constant, NULL, NULL, NULL);
      yyval.expression->set_location(yystack.p_mark[0]);
      yyval.expression->primary_expression.int64_constant = yystack.l_mark[0].n64;
   }
#line 3342 "compiler/glsl/glsl_parser.cpp"
break;
case 28:
#line 458 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      void *ctx = state->linalloc;
      yyval.expression = new(ctx) ast_expression(ast_uint64_constant, NULL, NULL, NULL);
      yyval.expression->set_location(yystack.p_mark[0]);
      yyval.expression->primary_expression.uint64_constant = yystack.l_mark[0].n64;
   }
#line 3352 "compiler/glsl/glsl_parser.cpp"
break;
case 29:
#line 465 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      void *ctx = state->linalloc;
      yyval.expression = new(ctx) ast_expression(ast_float_constant, NULL, NULL, NULL);
      yyval.expression->set_location(yystack.p_mark[0]);
      yyval.expression->primary_expression.float_constant = yystack.l_mark[0].real;
   }
#line 3362 "compiler/glsl/glsl_parser.cpp"
break;
case 30:
#line 472 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      void *ctx = state->linalloc;
      yyval.expression = new(ctx) ast_expression(ast_double_constant, NULL, NULL, NULL);
      yyval.expression->set_location(yystack.p_mark[0]);
      yyval.expression->primary_expression.double_constant = yystack.l_mark[0].dreal;
   }
#line 3372 "compiler/glsl/glsl_parser.cpp"
break;
case 31:
#line 479 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      void *ctx = state->linalloc;
      yyval.expression = new(ctx) ast_expression(ast_bool_constant, NULL, NULL, NULL);
      yyval.expression->set_location(yystack.p_mark[0]);
      yyval.expression->primary_expression.bool_constant = yystack.l_mark[0].n;
   }
#line 3382 "compiler/glsl/glsl_parser.cpp"
break;
case 32:
#line 486 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      yyval.expression = yystack.l_mark[-1].expression;
   }
#line 3389 "compiler/glsl/glsl_parser.cpp"
break;
case 34:
#line 494 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      void *ctx = state->linalloc;
      yyval.expression = new(ctx) ast_expression(ast_array_index, yystack.l_mark[-3].expression, yystack.l_mark[-1].expression, NULL);
      yyval.expression->set_location_range(yystack.p_mark[-3], yystack.p_mark[0]);
   }
#line 3398 "compiler/glsl/glsl_parser.cpp"
break;
case 35:
#line 500 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      yyval.expression = yystack.l_mark[0].expression;
   }
#line 3405 "compiler/glsl/glsl_parser.cpp"
break;
case 36:
#line 504 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      void *ctx = state->linalloc;
      yyval.expression = new(ctx) ast_expression(ast_field_selection, yystack.l_mark[-2].expression, NULL, NULL);
      yyval.expression->set_location_range(yystack.p_mark[-2], yystack.p_mark[0]);
      yyval.expression->primary_expression.identifier = yystack.l_mark[0].identifier;
   }
#line 3415 "compiler/glsl/glsl_parser.cpp"
break;
case 37:
#line 511 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      void *ctx = state->linalloc;
      yyval.expression = new(ctx) ast_expression(ast_post_inc, yystack.l_mark[-1].expression, NULL, NULL);
      yyval.expression->set_location_range(yystack.p_mark[-1], yystack.p_mark[0]);
   }
#line 3424 "compiler/glsl/glsl_parser.cpp"
break;
case 38:
#line 517 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      void *ctx = state->linalloc;
      yyval.expression = new(ctx) ast_expression(ast_post_dec, yystack.l_mark[-1].expression, NULL, NULL);
      yyval.expression->set_location_range(yystack.p_mark[-1], yystack.p_mark[0]);
   }
#line 3433 "compiler/glsl/glsl_parser.cpp"
break;
case 46:
#line 548 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      yyval.expression = yystack.l_mark[-1].expression;
      yyval.expression->set_location(yystack.p_mark[-1]);
      yyval.expression->expressions.push_tail(& yystack.l_mark[0].expression->link);
   }
#line 3442 "compiler/glsl/glsl_parser.cpp"
break;
case 47:
#line 554 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      yyval.expression = yystack.l_mark[-2].expression;
      yyval.expression->set_location(yystack.p_mark[-2]);
      yyval.expression->expressions.push_tail(& yystack.l_mark[0].expression->link);
   }
#line 3451 "compiler/glsl/glsl_parser.cpp"
break;
case 49:
#line 570 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      void *ctx = state->linalloc;
      yyval.expression = new(ctx) ast_function_expression(yystack.l_mark[0].type_specifier);
      yyval.expression->set_location(yystack.p_mark[0]);
      }
#line 3460 "compiler/glsl/glsl_parser.cpp"
break;
case 50:
#line 576 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      void *ctx = state->linalloc;
      yyval.expression = new(ctx) ast_function_expression(yystack.l_mark[0].expression);
      yyval.expression->set_location(yystack.p_mark[0]);
      }
#line 3469 "compiler/glsl/glsl_parser.cpp"
break;
case 52:
#line 591 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      void *ctx = state->linalloc;
      yyval.expression = new(ctx) ast_expression(ast_pre_inc, yystack.l_mark[0].expression, NULL, NULL);
      yyval.expression->set_location(yystack.p_mark[-1]);
   }
#line 3478 "compiler/glsl/glsl_parser.cpp"
break;
case 53:
#line 597 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      void *ctx = state->linalloc;
      yyval.expression = new(ctx) ast_expression(ast_pre_dec, yystack.l_mark[0].expression, NULL, NULL);
      yyval.expression->set_location(yystack.p_mark[-1]);
   }
#line 3487 "compiler/glsl/glsl_parser.cpp"
break;
case 54:
#line 603 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      void *ctx = state->linalloc;
      yyval.expression = new(ctx) ast_expression(yystack.l_mark[-1].n, yystack.l_mark[0].expression, NULL, NULL);
      yyval.expression->set_location_range(yystack.p_mark[-1], yystack.p_mark[0]);
   }
#line 3496 "compiler/glsl/glsl_parser.cpp"
break;
case 55:
#line 612 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{ yyval.n = ast_plus; }
#line 3501 "compiler/glsl/glsl_parser.cpp"
break;
case 56:
#line 613 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{ yyval.n = ast_neg; }
#line 3506 "compiler/glsl/glsl_parser.cpp"
break;
case 57:
#line 614 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{ yyval.n = ast_logic_not; }
#line 3511 "compiler/glsl/glsl_parser.cpp"
break;
case 58:
#line 615 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{ yyval.n = ast_bit_not; }
#line 3516 "compiler/glsl/glsl_parser.cpp"
break;
case 60:
#line 621 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      void *ctx = state->linalloc;
      yyval.expression = new(ctx) ast_expression_bin(ast_mul, yystack.l_mark[-2].expression, yystack.l_mark[0].expression);
      yyval.expression->set_location_range(yystack.p_mark[-2], yystack.p_mark[0]);
   }
#line 3525 "compiler/glsl/glsl_parser.cpp"
break;
case 61:
#line 627 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      void *ctx = state->linalloc;
      yyval.expression = new(ctx) ast_expression_bin(ast_div, yystack.l_mark[-2].expression, yystack.l_mark[0].expression);
      yyval.expression->set_location_range(yystack.p_mark[-2], yystack.p_mark[0]);
   }
#line 3534 "compiler/glsl/glsl_parser.cpp"
break;
case 62:
#line 633 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      void *ctx = state->linalloc;
      yyval.expression = new(ctx) ast_expression_bin(ast_mod, yystack.l_mark[-2].expression, yystack.l_mark[0].expression);
      yyval.expression->set_location_range(yystack.p_mark[-2], yystack.p_mark[0]);
   }
#line 3543 "compiler/glsl/glsl_parser.cpp"
break;
case 64:
#line 643 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      void *ctx = state->linalloc;
      yyval.expression = new(ctx) ast_expression_bin(ast_add, yystack.l_mark[-2].expression, yystack.l_mark[0].expression);
      yyval.expression->set_location_range(yystack.p_mark[-2], yystack.p_mark[0]);
   }
#line 3552 "compiler/glsl/glsl_parser.cpp"
break;
case 65:
#line 649 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      void *ctx = state->linalloc;
      yyval.expression = new(ctx) ast_expression_bin(ast_sub, yystack.l_mark[-2].expression, yystack.l_mark[0].expression);
      yyval.expression->set_location_range(yystack.p_mark[-2], yystack.p_mark[0]);
   }
#line 3561 "compiler/glsl/glsl_parser.cpp"
break;
case 67:
#line 659 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      void *ctx = state->linalloc;
      yyval.expression = new(ctx) ast_expression_bin(ast_lshift, yystack.l_mark[-2].expression, yystack.l_mark[0].expression);
      yyval.expression->set_location_range(yystack.p_mark[-2], yystack.p_mark[0]);
   }
#line 3570 "compiler/glsl/glsl_parser.cpp"
break;
case 68:
#line 665 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      void *ctx = state->linalloc;
      yyval.expression = new(ctx) ast_expression_bin(ast_rshift, yystack.l_mark[-2].expression, yystack.l_mark[0].expression);
      yyval.expression->set_location_range(yystack.p_mark[-2], yystack.p_mark[0]);
   }
#line 3579 "compiler/glsl/glsl_parser.cpp"
break;
case 70:
#line 675 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      void *ctx = state->linalloc;
      yyval.expression = new(ctx) ast_expression_bin(ast_less, yystack.l_mark[-2].expression, yystack.l_mark[0].expression);
      yyval.expression->set_location_range(yystack.p_mark[-2], yystack.p_mark[0]);
   }
#line 3588 "compiler/glsl/glsl_parser.cpp"
break;
case 71:
#line 681 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      void *ctx = state->linalloc;
      yyval.expression = new(ctx) ast_expression_bin(ast_greater, yystack.l_mark[-2].expression, yystack.l_mark[0].expression);
      yyval.expression->set_location_range(yystack.p_mark[-2], yystack.p_mark[0]);
   }
#line 3597 "compiler/glsl/glsl_parser.cpp"
break;
case 72:
#line 687 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      void *ctx = state->linalloc;
      yyval.expression = new(ctx) ast_expression_bin(ast_lequal, yystack.l_mark[-2].expression, yystack.l_mark[0].expression);
      yyval.expression->set_location_range(yystack.p_mark[-2], yystack.p_mark[0]);
   }
#line 3606 "compiler/glsl/glsl_parser.cpp"
break;
case 73:
#line 693 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      void *ctx = state->linalloc;
      yyval.expression = new(ctx) ast_expression_bin(ast_gequal, yystack.l_mark[-2].expression, yystack.l_mark[0].expression);
      yyval.expression->set_location_range(yystack.p_mark[-2], yystack.p_mark[0]);
   }
#line 3615 "compiler/glsl/glsl_parser.cpp"
break;
case 75:
#line 703 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      void *ctx = state->linalloc;
      yyval.expression = new(ctx) ast_expression_bin(ast_equal, yystack.l_mark[-2].expression, yystack.l_mark[0].expression);
      yyval.expression->set_location_range(yystack.p_mark[-2], yystack.p_mark[0]);
   }
#line 3624 "compiler/glsl/glsl_parser.cpp"
break;
case 76:
#line 709 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      void *ctx = state->linalloc;
      yyval.expression = new(ctx) ast_expression_bin(ast_nequal, yystack.l_mark[-2].expression, yystack.l_mark[0].expression);
      yyval.expression->set_location_range(yystack.p_mark[-2], yystack.p_mark[0]);
   }
#line 3633 "compiler/glsl/glsl_parser.cpp"
break;
case 78:
#line 719 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      void *ctx = state->linalloc;
      yyval.expression = new(ctx) ast_expression_bin(ast_bit_and, yystack.l_mark[-2].expression, yystack.l_mark[0].expression);
      yyval.expression->set_location_range(yystack.p_mark[-2], yystack.p_mark[0]);
   }
#line 3642 "compiler/glsl/glsl_parser.cpp"
break;
case 80:
#line 729 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      void *ctx = state->linalloc;
      yyval.expression = new(ctx) ast_expression_bin(ast_bit_xor, yystack.l_mark[-2].expression, yystack.l_mark[0].expression);
      yyval.expression->set_location_range(yystack.p_mark[-2], yystack.p_mark[0]);
   }
#line 3651 "compiler/glsl/glsl_parser.cpp"
break;
case 82:
#line 739 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      void *ctx = state->linalloc;
      yyval.expression = new(ctx) ast_expression_bin(ast_bit_or, yystack.l_mark[-2].expression, yystack.l_mark[0].expression);
      yyval.expression->set_location_range(yystack.p_mark[-2], yystack.p_mark[0]);
   }
#line 3660 "compiler/glsl/glsl_parser.cpp"
break;
case 84:
#line 749 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      void *ctx = state->linalloc;
      yyval.expression = new(ctx) ast_expression_bin(ast_logic_and, yystack.l_mark[-2].expression, yystack.l_mark[0].expression);
      yyval.expression->set_location_range(yystack.p_mark[-2], yystack.p_mark[0]);
   }
#line 3669 "compiler/glsl/glsl_parser.cpp"
break;
case 86:
#line 759 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      void *ctx = state->linalloc;
      yyval.expression = new(ctx) ast_expression_bin(ast_logic_xor, yystack.l_mark[-2].expression, yystack.l_mark[0].expression);
      yyval.expression->set_location_range(yystack.p_mark[-2], yystack.p_mark[0]);
   }
#line 3678 "compiler/glsl/glsl_parser.cpp"
break;
case 88:
#line 769 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      void *ctx = state->linalloc;
      yyval.expression = new(ctx) ast_expression_bin(ast_logic_or, yystack.l_mark[-2].expression, yystack.l_mark[0].expression);
      yyval.expression->set_location_range(yystack.p_mark[-2], yystack.p_mark[0]);
   }
#line 3687 "compiler/glsl/glsl_parser.cpp"
break;
case 90:
#line 779 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      void *ctx = state->linalloc;
      yyval.expression = new(ctx) ast_expression(ast_conditional, yystack.l_mark[-4].expression, yystack.l_mark[-2].expression, yystack.l_mark[0].expression);
      yyval.expression->set_location_range(yystack.p_mark[-4], yystack.p_mark[0]);
   }
#line 3696 "compiler/glsl/glsl_parser.cpp"
break;
case 92:
#line 789 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      void *ctx = state->linalloc;
      yyval.expression = new(ctx) ast_expression(yystack.l_mark[-1].n, yystack.l_mark[-2].expression, yystack.l_mark[0].expression, NULL);
      yyval.expression->set_location_range(yystack.p_mark[-2], yystack.p_mark[0]);
   }
#line 3705 "compiler/glsl/glsl_parser.cpp"
break;
case 93:
#line 797 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{ yyval.n = ast_assign; }
#line 3710 "compiler/glsl/glsl_parser.cpp"
break;
case 94:
#line 798 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{ yyval.n = ast_mul_assign; }
#line 3715 "compiler/glsl/glsl_parser.cpp"
break;
case 95:
#line 799 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{ yyval.n = ast_div_assign; }
#line 3720 "compiler/glsl/glsl_parser.cpp"
break;
case 96:
#line 800 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{ yyval.n = ast_mod_assign; }
#line 3725 "compiler/glsl/glsl_parser.cpp"
break;
case 97:
#line 801 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{ yyval.n = ast_add_assign; }
#line 3730 "compiler/glsl/glsl_parser.cpp"
break;
case 98:
#line 802 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{ yyval.n = ast_sub_assign; }
#line 3735 "compiler/glsl/glsl_parser.cpp"
break;
case 99:
#line 803 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{ yyval.n = ast_ls_assign; }
#line 3740 "compiler/glsl/glsl_parser.cpp"
break;
case 100:
#line 804 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{ yyval.n = ast_rs_assign; }
#line 3745 "compiler/glsl/glsl_parser.cpp"
break;
case 101:
#line 805 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{ yyval.n = ast_and_assign; }
#line 3750 "compiler/glsl/glsl_parser.cpp"
break;
case 102:
#line 806 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{ yyval.n = ast_xor_assign; }
#line 3755 "compiler/glsl/glsl_parser.cpp"
break;
case 103:
#line 807 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{ yyval.n = ast_or_assign; }
#line 3760 "compiler/glsl/glsl_parser.cpp"
break;
case 104:
#line 812 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      yyval.expression = yystack.l_mark[0].expression;
   }
#line 3767 "compiler/glsl/glsl_parser.cpp"
break;
case 105:
#line 816 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      void *ctx = state->linalloc;
      if (yystack.l_mark[-2].expression->oper != ast_sequence) {
         yyval.expression = new(ctx) ast_expression(ast_sequence, NULL, NULL, NULL);
         yyval.expression->set_location_range(yystack.p_mark[-2], yystack.p_mark[0]);
         yyval.expression->expressions.push_tail(& yystack.l_mark[-2].expression->link);
      } else {
         yyval.expression = yystack.l_mark[-2].expression;
      }

      yyval.expression->expressions.push_tail(& yystack.l_mark[0].expression->link);
   }
#line 3783 "compiler/glsl/glsl_parser.cpp"
break;
case 107:
#line 836 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      state->symbols->pop_scope();
      yyval.node = yystack.l_mark[-1].function;
   }
#line 3791 "compiler/glsl/glsl_parser.cpp"
break;
case 108:
#line 841 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      yyval.node = yystack.l_mark[-1].declarator_list;
   }
#line 3798 "compiler/glsl/glsl_parser.cpp"
break;
case 109:
#line 845 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      yystack.l_mark[-1].type_specifier->default_precision = yystack.l_mark[-2].n;
      yyval.node = yystack.l_mark[-1].type_specifier;
   }
#line 3806 "compiler/glsl/glsl_parser.cpp"
break;
case 110:
#line 850 "../mesa/src/compiler/glsl/glsl_parser.yy"
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
#line 3823 "compiler/glsl/glsl_parser.cpp"
break;
case 114:
#line 876 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      yyval.function = yystack.l_mark[-1].function;
      yyval.function->parameters.push_tail(& yystack.l_mark[0].parameter_declarator->link);
   }
#line 3831 "compiler/glsl/glsl_parser.cpp"
break;
case 115:
#line 881 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      yyval.function = yystack.l_mark[-2].function;
      yyval.function->parameters.push_tail(& yystack.l_mark[0].parameter_declarator->link);
   }
#line 3839 "compiler/glsl/glsl_parser.cpp"
break;
case 116:
#line 889 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      void *ctx = state->linalloc;
      yyval.function = new(ctx) ast_function();
      yyval.function->set_location(yystack.p_mark[-1]);
      yyval.function->return_type = yystack.l_mark[-2].fully_specified_type;
      yyval.function->identifier = yystack.l_mark[-1].identifier;

      if (yystack.l_mark[-2].fully_specified_type->qualifier.is_subroutine_decl()) {
         /* add type for IDENTIFIER search */
         state->symbols->add_type(yystack.l_mark[-1].identifier, glsl_type::get_subroutine_instance(yystack.l_mark[-1].identifier));
      } else
         state->symbols->add_function(new(state) ir_function(yystack.l_mark[-1].identifier));
      state->symbols->push_scope();
   }
#line 3857 "compiler/glsl/glsl_parser.cpp"
break;
case 117:
#line 907 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      void *ctx = state->linalloc;
      yyval.parameter_declarator = new(ctx) ast_parameter_declarator();
      yyval.parameter_declarator->set_location_range(yystack.p_mark[-1], yystack.p_mark[0]);
      yyval.parameter_declarator->type = new(ctx) ast_fully_specified_type();
      yyval.parameter_declarator->type->set_location(yystack.p_mark[-1]);
      yyval.parameter_declarator->type->specifier = yystack.l_mark[-1].type_specifier;
      yyval.parameter_declarator->identifier = yystack.l_mark[0].identifier;
      state->symbols->add_variable(new(state) ir_variable(NULL, yystack.l_mark[0].identifier, ir_var_auto));
   }
#line 3871 "compiler/glsl/glsl_parser.cpp"
break;
case 118:
#line 918 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      _mesa_glsl_error(&yystack.p_mark[-2], state, "is is not allowed on function parameter");
      YYERROR;
   }
#line 3879 "compiler/glsl/glsl_parser.cpp"
break;
case 119:
#line 923 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      void *ctx = state->linalloc;
      yyval.parameter_declarator = new(ctx) ast_parameter_declarator();
      yyval.parameter_declarator->set_location_range(yystack.p_mark[-2], yystack.p_mark[0]);
      yyval.parameter_declarator->type = new(ctx) ast_fully_specified_type();
      yyval.parameter_declarator->type->set_location(yystack.p_mark[-2]);
      yyval.parameter_declarator->type->specifier = yystack.l_mark[-2].type_specifier;
      yyval.parameter_declarator->identifier = yystack.l_mark[-1].identifier;
      yyval.parameter_declarator->array_specifier = yystack.l_mark[0].array_specifier;
      state->symbols->add_variable(new(state) ir_variable(NULL, yystack.l_mark[-1].identifier, ir_var_auto));
   }
#line 3894 "compiler/glsl/glsl_parser.cpp"
break;
case 120:
#line 938 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      yyval.parameter_declarator = yystack.l_mark[0].parameter_declarator;
      yyval.parameter_declarator->type->qualifier = yystack.l_mark[-1].type_qualifier;
      if (!yyval.parameter_declarator->type->qualifier.push_to_global(& yystack.p_mark[-1], state)) {
         YYERROR;
      }
   }
#line 3905 "compiler/glsl/glsl_parser.cpp"
break;
case 121:
#line 946 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      void *ctx = state->linalloc;
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
#line 3921 "compiler/glsl/glsl_parser.cpp"
break;
case 122:
#line 962 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      memset(& yyval.type_qualifier, 0, sizeof(yyval.type_qualifier));
   }
#line 3928 "compiler/glsl/glsl_parser.cpp"
break;
case 123:
#line 966 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      if (yystack.l_mark[0].type_qualifier.flags.q.constant)
         _mesa_glsl_error(&yystack.p_mark[-1], state, "duplicate const qualifier");

      yyval.type_qualifier = yystack.l_mark[0].type_qualifier;
      yyval.type_qualifier.flags.q.constant = 1;
   }
#line 3939 "compiler/glsl/glsl_parser.cpp"
break;
case 124:
#line 974 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      if (yystack.l_mark[0].type_qualifier.flags.q.precise)
         _mesa_glsl_error(&yystack.p_mark[-1], state, "duplicate precise qualifier");

      yyval.type_qualifier = yystack.l_mark[0].type_qualifier;
      yyval.type_qualifier.flags.q.precise = 1;
   }
#line 3950 "compiler/glsl/glsl_parser.cpp"
break;
case 125:
#line 982 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      if ((yystack.l_mark[-1].type_qualifier.flags.q.in || yystack.l_mark[-1].type_qualifier.flags.q.out) && (yystack.l_mark[0].type_qualifier.flags.q.in || yystack.l_mark[0].type_qualifier.flags.q.out))
         _mesa_glsl_error(&yystack.p_mark[-1], state, "duplicate in/out/inout qualifier");

      if (!state->has_420pack_or_es31() && yystack.l_mark[0].type_qualifier.flags.q.constant)
         _mesa_glsl_error(&yystack.p_mark[-1], state, "in/out/inout must come after const "
                                      "or precise");

      yyval.type_qualifier = yystack.l_mark[-1].type_qualifier;
      yyval.type_qualifier.merge_qualifier(&yystack.p_mark[-1], state, yystack.l_mark[0].type_qualifier, false);
   }
#line 3965 "compiler/glsl/glsl_parser.cpp"
break;
case 126:
#line 994 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      if (yystack.l_mark[0].type_qualifier.precision != ast_precision_none)
         _mesa_glsl_error(&yystack.p_mark[-1], state, "duplicate precision qualifier");

      if (!state->has_420pack_or_es31() &&
          yystack.l_mark[0].type_qualifier.flags.i != 0)
         _mesa_glsl_error(&yystack.p_mark[-1], state, "precision qualifiers must come last");

      yyval.type_qualifier = yystack.l_mark[0].type_qualifier;
      yyval.type_qualifier.precision = yystack.l_mark[-1].n;
   }
#line 3980 "compiler/glsl/glsl_parser.cpp"
break;
case 127:
#line 1006 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      yyval.type_qualifier = yystack.l_mark[-1].type_qualifier;
      yyval.type_qualifier.merge_qualifier(&yystack.p_mark[-1], state, yystack.l_mark[0].type_qualifier, false);
   }
#line 3988 "compiler/glsl/glsl_parser.cpp"
break;
case 128:
#line 1013 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      memset(& yyval.type_qualifier, 0, sizeof(yyval.type_qualifier));
      yyval.type_qualifier.flags.q.in = 1;
   }
#line 3996 "compiler/glsl/glsl_parser.cpp"
break;
case 129:
#line 1018 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      memset(& yyval.type_qualifier, 0, sizeof(yyval.type_qualifier));
      yyval.type_qualifier.flags.q.out = 1;
   }
#line 4004 "compiler/glsl/glsl_parser.cpp"
break;
case 130:
#line 1023 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      memset(& yyval.type_qualifier, 0, sizeof(yyval.type_qualifier));
      yyval.type_qualifier.flags.q.in = 1;
      yyval.type_qualifier.flags.q.out = 1;
   }
#line 4013 "compiler/glsl/glsl_parser.cpp"
break;
case 133:
#line 1037 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      void *ctx = state->linalloc;
      ast_declaration *decl = new(ctx) ast_declaration(yystack.l_mark[0].identifier, NULL, NULL);
      decl->set_location(yystack.p_mark[0]);

      yyval.declarator_list = yystack.l_mark[-2].declarator_list;
      yyval.declarator_list->declarations.push_tail(&decl->link);
      state->symbols->add_variable(new(state) ir_variable(NULL, yystack.l_mark[0].identifier, ir_var_auto));
   }
#line 4026 "compiler/glsl/glsl_parser.cpp"
break;
case 134:
#line 1047 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      void *ctx = state->linalloc;
      ast_declaration *decl = new(ctx) ast_declaration(yystack.l_mark[-1].identifier, yystack.l_mark[0].array_specifier, NULL);
      decl->set_location_range(yystack.p_mark[-1], yystack.p_mark[0]);

      yyval.declarator_list = yystack.l_mark[-3].declarator_list;
      yyval.declarator_list->declarations.push_tail(&decl->link);
      state->symbols->add_variable(new(state) ir_variable(NULL, yystack.l_mark[-1].identifier, ir_var_auto));
   }
#line 4039 "compiler/glsl/glsl_parser.cpp"
break;
case 135:
#line 1057 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      void *ctx = state->linalloc;
      ast_declaration *decl = new(ctx) ast_declaration(yystack.l_mark[-3].identifier, yystack.l_mark[-2].array_specifier, yystack.l_mark[0].expression);
      decl->set_location_range(yystack.p_mark[-3], yystack.p_mark[-2]);

      yyval.declarator_list = yystack.l_mark[-5].declarator_list;
      yyval.declarator_list->declarations.push_tail(&decl->link);
      state->symbols->add_variable(new(state) ir_variable(NULL, yystack.l_mark[-3].identifier, ir_var_auto));
   }
#line 4052 "compiler/glsl/glsl_parser.cpp"
break;
case 136:
#line 1067 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      void *ctx = state->linalloc;
      ast_declaration *decl = new(ctx) ast_declaration(yystack.l_mark[-2].identifier, NULL, yystack.l_mark[0].expression);
      decl->set_location(yystack.p_mark[-2]);

      yyval.declarator_list = yystack.l_mark[-4].declarator_list;
      yyval.declarator_list->declarations.push_tail(&decl->link);
      state->symbols->add_variable(new(state) ir_variable(NULL, yystack.l_mark[-2].identifier, ir_var_auto));
   }
#line 4065 "compiler/glsl/glsl_parser.cpp"
break;
case 137:
#line 1081 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      void *ctx = state->linalloc;
      /* Empty declaration list is valid. */
      yyval.declarator_list = new(ctx) ast_declarator_list(yystack.l_mark[0].fully_specified_type);
      yyval.declarator_list->set_location(yystack.p_mark[0]);
   }
#line 4075 "compiler/glsl/glsl_parser.cpp"
break;
case 138:
#line 1088 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      void *ctx = state->linalloc;
      ast_declaration *decl = new(ctx) ast_declaration(yystack.l_mark[0].identifier, NULL, NULL);
      decl->set_location(yystack.p_mark[0]);

      yyval.declarator_list = new(ctx) ast_declarator_list(yystack.l_mark[-1].fully_specified_type);
      yyval.declarator_list->set_location_range(yystack.p_mark[-1], yystack.p_mark[0]);
      yyval.declarator_list->declarations.push_tail(&decl->link);
      state->symbols->add_variable(new(state) ir_variable(NULL, yystack.l_mark[0].identifier, ir_var_auto));
   }
#line 4089 "compiler/glsl/glsl_parser.cpp"
break;
case 139:
#line 1099 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      void *ctx = state->linalloc;
      ast_declaration *decl = new(ctx) ast_declaration(yystack.l_mark[-1].identifier, yystack.l_mark[0].array_specifier, NULL);
      decl->set_location_range(yystack.p_mark[-1], yystack.p_mark[0]);

      yyval.declarator_list = new(ctx) ast_declarator_list(yystack.l_mark[-2].fully_specified_type);
      yyval.declarator_list->set_location_range(yystack.p_mark[-2], yystack.p_mark[0]);
      yyval.declarator_list->declarations.push_tail(&decl->link);
      state->symbols->add_variable(new(state) ir_variable(NULL, yystack.l_mark[-1].identifier, ir_var_auto));
   }
#line 4103 "compiler/glsl/glsl_parser.cpp"
break;
case 140:
#line 1110 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      void *ctx = state->linalloc;
      ast_declaration *decl = new(ctx) ast_declaration(yystack.l_mark[-3].identifier, yystack.l_mark[-2].array_specifier, yystack.l_mark[0].expression);
      decl->set_location_range(yystack.p_mark[-3], yystack.p_mark[-2]);

      yyval.declarator_list = new(ctx) ast_declarator_list(yystack.l_mark[-4].fully_specified_type);
      yyval.declarator_list->set_location_range(yystack.p_mark[-4], yystack.p_mark[-2]);
      yyval.declarator_list->declarations.push_tail(&decl->link);
      state->symbols->add_variable(new(state) ir_variable(NULL, yystack.l_mark[-3].identifier, ir_var_auto));
   }
#line 4117 "compiler/glsl/glsl_parser.cpp"
break;
case 141:
#line 1121 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      void *ctx = state->linalloc;
      ast_declaration *decl = new(ctx) ast_declaration(yystack.l_mark[-2].identifier, NULL, yystack.l_mark[0].expression);
      decl->set_location(yystack.p_mark[-2]);

      yyval.declarator_list = new(ctx) ast_declarator_list(yystack.l_mark[-3].fully_specified_type);
      yyval.declarator_list->set_location_range(yystack.p_mark[-3], yystack.p_mark[-2]);
      yyval.declarator_list->declarations.push_tail(&decl->link);
      state->symbols->add_variable(new(state) ir_variable(NULL, yystack.l_mark[-2].identifier, ir_var_auto));
   }
#line 4131 "compiler/glsl/glsl_parser.cpp"
break;
case 142:
#line 1132 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      void *ctx = state->linalloc;
      ast_declaration *decl = new(ctx) ast_declaration(yystack.l_mark[0].identifier, NULL, NULL);
      decl->set_location(yystack.p_mark[0]);

      yyval.declarator_list = new(ctx) ast_declarator_list(NULL);
      yyval.declarator_list->set_location_range(yystack.p_mark[-1], yystack.p_mark[0]);
      yyval.declarator_list->invariant = true;

      yyval.declarator_list->declarations.push_tail(&decl->link);
   }
#line 4146 "compiler/glsl/glsl_parser.cpp"
break;
case 143:
#line 1144 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      void *ctx = state->linalloc;
      ast_declaration *decl = new(ctx) ast_declaration(yystack.l_mark[0].identifier, NULL, NULL);
      decl->set_location(yystack.p_mark[0]);

      yyval.declarator_list = new(ctx) ast_declarator_list(NULL);
      yyval.declarator_list->set_location_range(yystack.p_mark[-1], yystack.p_mark[0]);
      yyval.declarator_list->precise = true;

      yyval.declarator_list->declarations.push_tail(&decl->link);
   }
#line 4161 "compiler/glsl/glsl_parser.cpp"
break;
case 144:
#line 1159 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      void *ctx = state->linalloc;
      yyval.fully_specified_type = new(ctx) ast_fully_specified_type();
      yyval.fully_specified_type->set_location(yystack.p_mark[0]);
      yyval.fully_specified_type->specifier = yystack.l_mark[0].type_specifier;
   }
#line 4171 "compiler/glsl/glsl_parser.cpp"
break;
case 145:
#line 1166 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      void *ctx = state->linalloc;
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
#line 4189 "compiler/glsl/glsl_parser.cpp"
break;
case 146:
#line 1184 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      yyval.type_qualifier = yystack.l_mark[-1].type_qualifier;
   }
#line 4196 "compiler/glsl/glsl_parser.cpp"
break;
case 148:
#line 1192 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      yyval.type_qualifier = yystack.l_mark[-2].type_qualifier;
      if (!yyval.type_qualifier.merge_qualifier(& yystack.p_mark[0], state, yystack.l_mark[0].type_qualifier, true)) {
         YYERROR;
      }
   }
#line 4206 "compiler/glsl/glsl_parser.cpp"
break;
case 149:
#line 1202 "../mesa/src/compiler/glsl/glsl_parser.yy"
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
#line 4732 "compiler/glsl/glsl_parser.cpp"
break;
case 150:
#line 1725 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      memset(& yyval.type_qualifier, 0, sizeof(yyval.type_qualifier));
      void *ctx = state->linalloc;

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
                             "specified", yystack.l_mark[0].expression);
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
#line 4900 "compiler/glsl/glsl_parser.cpp"
break;
case 151:
#line 1890 "../mesa/src/compiler/glsl/glsl_parser.yy"
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
#line 4917 "compiler/glsl/glsl_parser.cpp"
break;
case 152:
#line 1916 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      memset(& yyval.type_qualifier, 0, sizeof(yyval.type_qualifier));
      yyval.type_qualifier.flags.q.row_major = 1;
   }
#line 4925 "compiler/glsl/glsl_parser.cpp"
break;
case 153:
#line 1921 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      memset(& yyval.type_qualifier, 0, sizeof(yyval.type_qualifier));
      yyval.type_qualifier.flags.q.packed = 1;
   }
#line 4933 "compiler/glsl/glsl_parser.cpp"
break;
case 154:
#line 1926 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      memset(& yyval.type_qualifier, 0, sizeof(yyval.type_qualifier));
      yyval.type_qualifier.flags.q.shared = 1;
   }
#line 4941 "compiler/glsl/glsl_parser.cpp"
break;
case 155:
#line 1934 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      memset(& yyval.type_qualifier, 0, sizeof(yyval.type_qualifier));
      yyval.type_qualifier.flags.q.subroutine = 1;
   }
#line 4949 "compiler/glsl/glsl_parser.cpp"
break;
case 156:
#line 1939 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      memset(& yyval.type_qualifier, 0, sizeof(yyval.type_qualifier));
      yyval.type_qualifier.flags.q.subroutine = 1;
      yyval.type_qualifier.subroutine_list = yystack.l_mark[-1].subroutine_list;
   }
#line 4958 "compiler/glsl/glsl_parser.cpp"
break;
case 157:
#line 1948 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
        void *ctx = state->linalloc;
        ast_declaration *decl = new(ctx)  ast_declaration(yystack.l_mark[0].identifier, NULL, NULL);
        decl->set_location(yystack.p_mark[0]);

        yyval.subroutine_list = new(ctx) ast_subroutine_list();
        yyval.subroutine_list->declarations.push_tail(&decl->link);
   }
#line 4970 "compiler/glsl/glsl_parser.cpp"
break;
case 158:
#line 1957 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
        void *ctx = state->linalloc;
        ast_declaration *decl = new(ctx)  ast_declaration(yystack.l_mark[0].identifier, NULL, NULL);
        decl->set_location(yystack.p_mark[0]);

        yyval.subroutine_list = yystack.l_mark[-2].subroutine_list;
        yyval.subroutine_list->declarations.push_tail(&decl->link);
   }
#line 4982 "compiler/glsl/glsl_parser.cpp"
break;
case 159:
#line 1969 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      memset(& yyval.type_qualifier, 0, sizeof(yyval.type_qualifier));
      yyval.type_qualifier.flags.q.smooth = 1;
   }
#line 4990 "compiler/glsl/glsl_parser.cpp"
break;
case 160:
#line 1974 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      memset(& yyval.type_qualifier, 0, sizeof(yyval.type_qualifier));
      yyval.type_qualifier.flags.q.flat = 1;
   }
#line 4998 "compiler/glsl/glsl_parser.cpp"
break;
case 161:
#line 1979 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      memset(& yyval.type_qualifier, 0, sizeof(yyval.type_qualifier));
      yyval.type_qualifier.flags.q.noperspective = 1;
   }
#line 5006 "compiler/glsl/glsl_parser.cpp"
break;
case 162:
#line 1988 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      memset(& yyval.type_qualifier, 0, sizeof(yyval.type_qualifier));
      yyval.type_qualifier.flags.q.invariant = 1;
   }
#line 5014 "compiler/glsl/glsl_parser.cpp"
break;
case 163:
#line 1993 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      memset(& yyval.type_qualifier, 0, sizeof(yyval.type_qualifier));
      yyval.type_qualifier.flags.q.precise = 1;
   }
#line 5022 "compiler/glsl/glsl_parser.cpp"
break;
case 170:
#line 2004 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      memset(&yyval.type_qualifier, 0, sizeof(yyval.type_qualifier));
      yyval.type_qualifier.precision = yystack.l_mark[0].n;
   }
#line 5030 "compiler/glsl/glsl_parser.cpp"
break;
case 171:
#line 2022 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      if (yystack.l_mark[0].type_qualifier.flags.q.precise)
         _mesa_glsl_error(&yystack.p_mark[-1], state, "duplicate \"precise\" qualifier");

      yyval.type_qualifier = yystack.l_mark[0].type_qualifier;
      yyval.type_qualifier.flags.q.precise = 1;
   }
#line 5041 "compiler/glsl/glsl_parser.cpp"
break;
case 172:
#line 2030 "../mesa/src/compiler/glsl/glsl_parser.yy"
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
#line 5069 "compiler/glsl/glsl_parser.cpp"
break;
case 173:
#line 2055 "../mesa/src/compiler/glsl/glsl_parser.yy"
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
#line 5096 "compiler/glsl/glsl_parser.cpp"
break;
case 174:
#line 2079 "../mesa/src/compiler/glsl/glsl_parser.yy"
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
#line 5113 "compiler/glsl/glsl_parser.cpp"
break;
case 175:
#line 2093 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      yyval.type_qualifier = yystack.l_mark[-1].type_qualifier;
      yyval.type_qualifier.merge_qualifier(&yystack.p_mark[-1], state, yystack.l_mark[0].type_qualifier, false);
   }
#line 5121 "compiler/glsl/glsl_parser.cpp"
break;
case 176:
#line 2098 "../mesa/src/compiler/glsl/glsl_parser.yy"
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
#line 5140 "compiler/glsl/glsl_parser.cpp"
break;
case 177:
#line 2114 "../mesa/src/compiler/glsl/glsl_parser.yy"
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
#line 5168 "compiler/glsl/glsl_parser.cpp"
break;
case 178:
#line 2139 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      if (yystack.l_mark[0].type_qualifier.precision != ast_precision_none)
         _mesa_glsl_error(&yystack.p_mark[-1], state, "duplicate precision qualifier");

      if (!(state->has_420pack_or_es31()) &&
          yystack.l_mark[0].type_qualifier.flags.i != 0)
         _mesa_glsl_error(&yystack.p_mark[-1], state, "precision qualifiers must come last");

      yyval.type_qualifier = yystack.l_mark[0].type_qualifier;
      yyval.type_qualifier.precision = yystack.l_mark[-1].n;
   }
#line 5183 "compiler/glsl/glsl_parser.cpp"
break;
case 179:
#line 2151 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      yyval.type_qualifier = yystack.l_mark[-1].type_qualifier;
      yyval.type_qualifier.merge_qualifier(&yystack.p_mark[-1], state, yystack.l_mark[0].type_qualifier, false);
   }
#line 5191 "compiler/glsl/glsl_parser.cpp"
break;
case 180:
#line 2159 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      memset(& yyval.type_qualifier, 0, sizeof(yyval.type_qualifier));
      yyval.type_qualifier.flags.q.centroid = 1;
   }
#line 5199 "compiler/glsl/glsl_parser.cpp"
break;
case 181:
#line 2164 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      memset(& yyval.type_qualifier, 0, sizeof(yyval.type_qualifier));
      yyval.type_qualifier.flags.q.sample = 1;
   }
#line 5207 "compiler/glsl/glsl_parser.cpp"
break;
case 182:
#line 2169 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      memset(& yyval.type_qualifier, 0, sizeof(yyval.type_qualifier));
      yyval.type_qualifier.flags.q.patch = 1;
   }
#line 5215 "compiler/glsl/glsl_parser.cpp"
break;
case 183:
#line 2176 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      memset(& yyval.type_qualifier, 0, sizeof(yyval.type_qualifier));
      yyval.type_qualifier.flags.q.constant = 1;
   }
#line 5223 "compiler/glsl/glsl_parser.cpp"
break;
case 184:
#line 2181 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      memset(& yyval.type_qualifier, 0, sizeof(yyval.type_qualifier));
      yyval.type_qualifier.flags.q.attribute = 1;
   }
#line 5231 "compiler/glsl/glsl_parser.cpp"
break;
case 185:
#line 2186 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      memset(& yyval.type_qualifier, 0, sizeof(yyval.type_qualifier));
      yyval.type_qualifier.flags.q.varying = 1;
   }
#line 5239 "compiler/glsl/glsl_parser.cpp"
break;
case 186:
#line 2191 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      memset(& yyval.type_qualifier, 0, sizeof(yyval.type_qualifier));
      yyval.type_qualifier.flags.q.in = 1;
   }
#line 5247 "compiler/glsl/glsl_parser.cpp"
break;
case 187:
#line 2196 "../mesa/src/compiler/glsl/glsl_parser.yy"
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

      if (state->has_enhanced_layouts()) {
          yyval.type_qualifier.flags.q.xfb_buffer = 1;
          yyval.type_qualifier.flags.q.explicit_xfb_buffer = 0;
          yyval.type_qualifier.xfb_buffer = state->out_qualifier->xfb_buffer;
      }
   }
#line 5275 "compiler/glsl/glsl_parser.cpp"
break;
case 188:
#line 2221 "../mesa/src/compiler/glsl/glsl_parser.yy"
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
#line 5290 "compiler/glsl/glsl_parser.cpp"
break;
case 189:
#line 2233 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      memset(& yyval.type_qualifier, 0, sizeof(yyval.type_qualifier));
      yyval.type_qualifier.flags.q.uniform = 1;
   }
#line 5298 "compiler/glsl/glsl_parser.cpp"
break;
case 190:
#line 2238 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      memset(& yyval.type_qualifier, 0, sizeof(yyval.type_qualifier));
      yyval.type_qualifier.flags.q.buffer = 1;
   }
#line 5306 "compiler/glsl/glsl_parser.cpp"
break;
case 191:
#line 2243 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      memset(& yyval.type_qualifier, 0, sizeof(yyval.type_qualifier));
      yyval.type_qualifier.flags.q.shared_storage = 1;
   }
#line 5314 "compiler/glsl/glsl_parser.cpp"
break;
case 192:
#line 2251 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      memset(& yyval.type_qualifier, 0, sizeof(yyval.type_qualifier));
      yyval.type_qualifier.flags.q.coherent = 1;
   }
#line 5322 "compiler/glsl/glsl_parser.cpp"
break;
case 193:
#line 2256 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      memset(& yyval.type_qualifier, 0, sizeof(yyval.type_qualifier));
      yyval.type_qualifier.flags.q._volatile = 1;
   }
#line 5330 "compiler/glsl/glsl_parser.cpp"
break;
case 194:
#line 2261 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      STATIC_ASSERT(sizeof(yyval.type_qualifier.flags.q) <= sizeof(yyval.type_qualifier.flags.i));
      memset(& yyval.type_qualifier, 0, sizeof(yyval.type_qualifier));
      yyval.type_qualifier.flags.q.restrict_flag = 1;
   }
#line 5339 "compiler/glsl/glsl_parser.cpp"
break;
case 195:
#line 2267 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      memset(& yyval.type_qualifier, 0, sizeof(yyval.type_qualifier));
      yyval.type_qualifier.flags.q.read_only = 1;
   }
#line 5347 "compiler/glsl/glsl_parser.cpp"
break;
case 196:
#line 2272 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      memset(& yyval.type_qualifier, 0, sizeof(yyval.type_qualifier));
      yyval.type_qualifier.flags.q.write_only = 1;
   }
#line 5355 "compiler/glsl/glsl_parser.cpp"
break;
case 197:
#line 2280 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      void *ctx = state->linalloc;
      yyval.array_specifier = new(ctx) ast_array_specifier(yystack.p_mark[-1], new(ctx) ast_expression(
                                                  ast_unsized_array_dim, NULL,
                                                  NULL, NULL));
      yyval.array_specifier->set_location_range(yystack.p_mark[-1], yystack.p_mark[0]);
   }
#line 5366 "compiler/glsl/glsl_parser.cpp"
break;
case 198:
#line 2288 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      void *ctx = state->linalloc;
      yyval.array_specifier = new(ctx) ast_array_specifier(yystack.p_mark[-2], yystack.l_mark[-1].expression);
      yyval.array_specifier->set_location_range(yystack.p_mark[-2], yystack.p_mark[0]);
   }
#line 5375 "compiler/glsl/glsl_parser.cpp"
break;
case 199:
#line 2294 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      void *ctx = state->linalloc;
      yyval.array_specifier = yystack.l_mark[-2].array_specifier;

      if (state->check_arrays_of_arrays_allowed(& yystack.p_mark[-2])) {
         yyval.array_specifier->add_dimension(new(ctx) ast_expression(ast_unsized_array_dim, NULL,
                                                   NULL, NULL));
      }
   }
#line 5388 "compiler/glsl/glsl_parser.cpp"
break;
case 200:
#line 2304 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      yyval.array_specifier = yystack.l_mark[-3].array_specifier;

      if (state->check_arrays_of_arrays_allowed(& yystack.p_mark[-3])) {
         yyval.array_specifier->add_dimension(yystack.l_mark[-1].expression);
      }
   }
#line 5399 "compiler/glsl/glsl_parser.cpp"
break;
case 202:
#line 2316 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      yyval.type_specifier = yystack.l_mark[-1].type_specifier;
      yyval.type_specifier->array_specifier = yystack.l_mark[0].array_specifier;
   }
#line 5407 "compiler/glsl/glsl_parser.cpp"
break;
case 203:
#line 2324 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      void *ctx = state->linalloc;
      yyval.type_specifier = new(ctx) ast_type_specifier(yystack.l_mark[0].type);
      yyval.type_specifier->set_location(yystack.p_mark[0]);
   }
#line 5416 "compiler/glsl/glsl_parser.cpp"
break;
case 204:
#line 2330 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      void *ctx = state->linalloc;
      yyval.type_specifier = new(ctx) ast_type_specifier(yystack.l_mark[0].struct_specifier);
      yyval.type_specifier->set_location(yystack.p_mark[0]);
   }
#line 5425 "compiler/glsl/glsl_parser.cpp"
break;
case 205:
#line 2336 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      void *ctx = state->linalloc;
      yyval.type_specifier = new(ctx) ast_type_specifier(yystack.l_mark[0].identifier);
      yyval.type_specifier->set_location(yystack.p_mark[0]);
   }
#line 5434 "compiler/glsl/glsl_parser.cpp"
break;
case 206:
#line 2344 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{ yyval.type = glsl_type::void_type; }
#line 5439 "compiler/glsl/glsl_parser.cpp"
break;
case 207:
#line 2345 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{ yyval.type = yystack.l_mark[0].type; }
#line 5444 "compiler/glsl/glsl_parser.cpp"
break;
case 208:
#line 2347 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      if (yystack.l_mark[0].type == glsl_type::int_type) {
         yyval.type = glsl_type::uint_type;
      } else {
         _mesa_glsl_error(&yystack.p_mark[-1], state,
                          "\"unsigned\" is only allowed before \"int\"");
      }
   }
#line 5456 "compiler/glsl/glsl_parser.cpp"
break;
case 209:
#line 2359 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      state->check_precision_qualifiers_allowed(&yystack.p_mark[0]);
      yyval.n = ast_precision_high;
   }
#line 5464 "compiler/glsl/glsl_parser.cpp"
break;
case 210:
#line 2364 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      state->check_precision_qualifiers_allowed(&yystack.p_mark[0]);
      yyval.n = ast_precision_medium;
   }
#line 5472 "compiler/glsl/glsl_parser.cpp"
break;
case 211:
#line 2369 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      state->check_precision_qualifiers_allowed(&yystack.p_mark[0]);
      yyval.n = ast_precision_low;
   }
#line 5480 "compiler/glsl/glsl_parser.cpp"
break;
case 212:
#line 2377 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      void *ctx = state->linalloc;
      yyval.struct_specifier = new(ctx) ast_struct_specifier(yystack.l_mark[-3].identifier, yystack.l_mark[-1].declarator_list);
      yyval.struct_specifier->set_location_range(yystack.p_mark[-3], yystack.p_mark[0]);
      state->symbols->add_type(yystack.l_mark[-3].identifier, glsl_type::void_type);
   }
#line 5490 "compiler/glsl/glsl_parser.cpp"
break;
case 213:
#line 2384 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      void *ctx = state->linalloc;

      /* All anonymous structs have the same name. This simplifies matching of
       * globals whose type is an unnamed struct.
       *
       * It also avoids a memory leak when the same shader is compiled over and
       * over again.
       */
      yyval.struct_specifier = new(ctx) ast_struct_specifier("#anon_struct", yystack.l_mark[-1].declarator_list);

      yyval.struct_specifier->set_location_range(yystack.p_mark[-2], yystack.p_mark[0]);
   }
#line 5507 "compiler/glsl/glsl_parser.cpp"
break;
case 214:
#line 2401 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      yyval.declarator_list = yystack.l_mark[0].declarator_list;
      yystack.l_mark[0].declarator_list->link.self_link();
   }
#line 5515 "compiler/glsl/glsl_parser.cpp"
break;
case 215:
#line 2406 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      yyval.declarator_list = yystack.l_mark[-1].declarator_list;
      yyval.declarator_list->link.insert_before(& yystack.l_mark[0].declarator_list->link);
   }
#line 5523 "compiler/glsl/glsl_parser.cpp"
break;
case 216:
#line 2414 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      void *ctx = state->linalloc;
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
#line 5561 "compiler/glsl/glsl_parser.cpp"
break;
case 217:
#line 2452 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      yyval.declaration = yystack.l_mark[0].declaration;
      yystack.l_mark[0].declaration->link.self_link();
   }
#line 5569 "compiler/glsl/glsl_parser.cpp"
break;
case 218:
#line 2457 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      yyval.declaration = yystack.l_mark[-2].declaration;
      yyval.declaration->link.insert_before(& yystack.l_mark[0].declaration->link);
   }
#line 5577 "compiler/glsl/glsl_parser.cpp"
break;
case 219:
#line 2465 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      void *ctx = state->linalloc;
      yyval.declaration = new(ctx) ast_declaration(yystack.l_mark[0].identifier, NULL, NULL);
      yyval.declaration->set_location(yystack.p_mark[0]);
   }
#line 5586 "compiler/glsl/glsl_parser.cpp"
break;
case 220:
#line 2471 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      void *ctx = state->linalloc;
      yyval.declaration = new(ctx) ast_declaration(yystack.l_mark[-1].identifier, yystack.l_mark[0].array_specifier, NULL);
      yyval.declaration->set_location_range(yystack.p_mark[-1], yystack.p_mark[0]);
   }
#line 5595 "compiler/glsl/glsl_parser.cpp"
break;
case 222:
#line 2481 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      yyval.expression = yystack.l_mark[-1].expression;
   }
#line 5602 "compiler/glsl/glsl_parser.cpp"
break;
case 223:
#line 2485 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      yyval.expression = yystack.l_mark[-2].expression;
   }
#line 5609 "compiler/glsl/glsl_parser.cpp"
break;
case 224:
#line 2492 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      void *ctx = state->linalloc;
      yyval.expression = new(ctx) ast_aggregate_initializer();
      yyval.expression->set_location(yystack.p_mark[0]);
      yyval.expression->expressions.push_tail(& yystack.l_mark[0].expression->link);
   }
#line 5619 "compiler/glsl/glsl_parser.cpp"
break;
case 225:
#line 2499 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      yystack.l_mark[-2].expression->expressions.push_tail(& yystack.l_mark[0].expression->link);
   }
#line 5626 "compiler/glsl/glsl_parser.cpp"
break;
case 227:
#line 2511 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{ yyval.node = (ast_node *) yystack.l_mark[0].compound_statement; }
#line 5631 "compiler/glsl/glsl_parser.cpp"
break;
case 236:
#line 2527 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      void *ctx = state->linalloc;
      yyval.compound_statement = new(ctx) ast_compound_statement(true, NULL);
      yyval.compound_statement->set_location_range(yystack.p_mark[-1], yystack.p_mark[0]);
   }
#line 5640 "compiler/glsl/glsl_parser.cpp"
break;
case 237:
#line 2533 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      state->symbols->push_scope();
   }
#line 5647 "compiler/glsl/glsl_parser.cpp"
break;
case 238:
#line 2537 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      void *ctx = state->linalloc;
      yyval.compound_statement = new(ctx) ast_compound_statement(true, yystack.l_mark[-1].node);
      yyval.compound_statement->set_location_range(yystack.p_mark[-3], yystack.p_mark[0]);
      state->symbols->pop_scope();
   }
#line 5657 "compiler/glsl/glsl_parser.cpp"
break;
case 239:
#line 2546 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{ yyval.node = (ast_node *) yystack.l_mark[0].compound_statement; }
#line 5662 "compiler/glsl/glsl_parser.cpp"
break;
case 241:
#line 2552 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      void *ctx = state->linalloc;
      yyval.compound_statement = new(ctx) ast_compound_statement(false, NULL);
      yyval.compound_statement->set_location_range(yystack.p_mark[-1], yystack.p_mark[0]);
   }
#line 5671 "compiler/glsl/glsl_parser.cpp"
break;
case 242:
#line 2558 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      void *ctx = state->linalloc;
      yyval.compound_statement = new(ctx) ast_compound_statement(false, yystack.l_mark[-1].node);
      yyval.compound_statement->set_location_range(yystack.p_mark[-2], yystack.p_mark[0]);
   }
#line 5680 "compiler/glsl/glsl_parser.cpp"
break;
case 243:
#line 2567 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      if (yystack.l_mark[0].node == NULL) {
         _mesa_glsl_error(& yystack.p_mark[0], state, "<nil> statement");
         assert(yystack.l_mark[0].node != NULL);
      }

      yyval.node = yystack.l_mark[0].node;
      yyval.node->link.self_link();
   }
#line 5693 "compiler/glsl/glsl_parser.cpp"
break;
case 244:
#line 2577 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      if (yystack.l_mark[0].node == NULL) {
         _mesa_glsl_error(& yystack.p_mark[0], state, "<nil> statement");
         assert(yystack.l_mark[0].node != NULL);
      }
      yyval.node = yystack.l_mark[-1].node;
      yyval.node->link.insert_before(& yystack.l_mark[0].node->link);
   }
#line 5705 "compiler/glsl/glsl_parser.cpp"
break;
case 245:
#line 2586 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      if (!state->allow_extension_directive_midshader) {
         _mesa_glsl_error(& yystack.p_mark[-1], state,
                          "#extension directive is not allowed "
                          "in the middle of a shader");
         YYERROR;
      }
   }
#line 5717 "compiler/glsl/glsl_parser.cpp"
break;
case 246:
#line 2598 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      void *ctx = state->linalloc;
      yyval.node = new(ctx) ast_expression_statement(NULL);
      yyval.node->set_location(yystack.p_mark[0]);
   }
#line 5726 "compiler/glsl/glsl_parser.cpp"
break;
case 247:
#line 2604 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      void *ctx = state->linalloc;
      yyval.node = new(ctx) ast_expression_statement(yystack.l_mark[-1].expression);
      yyval.node->set_location(yystack.p_mark[-1]);
   }
#line 5735 "compiler/glsl/glsl_parser.cpp"
break;
case 248:
#line 2613 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      yyval.node = new(state->linalloc) ast_selection_statement(yystack.l_mark[-2].expression, yystack.l_mark[0].selection_rest_statement.then_statement,
                                                        yystack.l_mark[0].selection_rest_statement.else_statement);
      yyval.node->set_location_range(yystack.p_mark[-4], yystack.p_mark[0]);
   }
#line 5744 "compiler/glsl/glsl_parser.cpp"
break;
case 249:
#line 2622 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      yyval.selection_rest_statement.then_statement = yystack.l_mark[-2].node;
      yyval.selection_rest_statement.else_statement = yystack.l_mark[0].node;
   }
#line 5752 "compiler/glsl/glsl_parser.cpp"
break;
case 250:
#line 2627 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      yyval.selection_rest_statement.then_statement = yystack.l_mark[0].node;
      yyval.selection_rest_statement.else_statement = NULL;
   }
#line 5760 "compiler/glsl/glsl_parser.cpp"
break;
case 251:
#line 2635 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      yyval.node = (ast_node *) yystack.l_mark[0].expression;
   }
#line 5767 "compiler/glsl/glsl_parser.cpp"
break;
case 252:
#line 2639 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      void *ctx = state->linalloc;
      ast_declaration *decl = new(ctx) ast_declaration(yystack.l_mark[-2].identifier, NULL, yystack.l_mark[0].expression);
      ast_declarator_list *declarator = new(ctx) ast_declarator_list(yystack.l_mark[-3].fully_specified_type);
      decl->set_location_range(yystack.p_mark[-2], yystack.p_mark[0]);
      declarator->set_location(yystack.p_mark[-3]);

      declarator->declarations.push_tail(&decl->link);
      yyval.node = declarator;
   }
#line 5781 "compiler/glsl/glsl_parser.cpp"
break;
case 253:
#line 2657 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      yyval.node = new(state->linalloc) ast_switch_statement(yystack.l_mark[-2].expression, yystack.l_mark[0].switch_body);
      yyval.node->set_location_range(yystack.p_mark[-4], yystack.p_mark[0]);
   }
#line 5789 "compiler/glsl/glsl_parser.cpp"
break;
case 254:
#line 2665 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      yyval.switch_body = new(state->linalloc) ast_switch_body(NULL);
      yyval.switch_body->set_location_range(yystack.p_mark[-1], yystack.p_mark[0]);
   }
#line 5797 "compiler/glsl/glsl_parser.cpp"
break;
case 255:
#line 2670 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      yyval.switch_body = new(state->linalloc) ast_switch_body(yystack.l_mark[-1].case_statement_list);
      yyval.switch_body->set_location_range(yystack.p_mark[-2], yystack.p_mark[0]);
   }
#line 5805 "compiler/glsl/glsl_parser.cpp"
break;
case 256:
#line 2678 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      yyval.case_label = new(state->linalloc) ast_case_label(yystack.l_mark[-1].expression);
      yyval.case_label->set_location(yystack.p_mark[-1]);
   }
#line 5813 "compiler/glsl/glsl_parser.cpp"
break;
case 257:
#line 2683 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      yyval.case_label = new(state->linalloc) ast_case_label(NULL);
      yyval.case_label->set_location(yystack.p_mark[0]);
   }
#line 5821 "compiler/glsl/glsl_parser.cpp"
break;
case 258:
#line 2691 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      ast_case_label_list *labels = new(state->linalloc) ast_case_label_list();

      labels->labels.push_tail(& yystack.l_mark[0].case_label->link);
      yyval.case_label_list = labels;
      yyval.case_label_list->set_location(yystack.p_mark[0]);
   }
#line 5832 "compiler/glsl/glsl_parser.cpp"
break;
case 259:
#line 2699 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      yyval.case_label_list = yystack.l_mark[-1].case_label_list;
      yyval.case_label_list->labels.push_tail(& yystack.l_mark[0].case_label->link);
   }
#line 5840 "compiler/glsl/glsl_parser.cpp"
break;
case 260:
#line 2707 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      ast_case_statement *stmts = new(state->linalloc) ast_case_statement(yystack.l_mark[-1].case_label_list);
      stmts->set_location(yystack.p_mark[0]);

      stmts->stmts.push_tail(& yystack.l_mark[0].node->link);
      yyval.case_statement = stmts;
   }
#line 5851 "compiler/glsl/glsl_parser.cpp"
break;
case 261:
#line 2715 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      yyval.case_statement = yystack.l_mark[-1].case_statement;
      yyval.case_statement->stmts.push_tail(& yystack.l_mark[0].node->link);
   }
#line 5859 "compiler/glsl/glsl_parser.cpp"
break;
case 262:
#line 2723 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      ast_case_statement_list *cases= new(state->linalloc) ast_case_statement_list();
      cases->set_location(yystack.p_mark[0]);

      cases->cases.push_tail(& yystack.l_mark[0].case_statement->link);
      yyval.case_statement_list = cases;
   }
#line 5870 "compiler/glsl/glsl_parser.cpp"
break;
case 263:
#line 2731 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      yyval.case_statement_list = yystack.l_mark[-1].case_statement_list;
      yyval.case_statement_list->cases.push_tail(& yystack.l_mark[0].case_statement->link);
   }
#line 5878 "compiler/glsl/glsl_parser.cpp"
break;
case 264:
#line 2739 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      void *ctx = state->linalloc;
      yyval.node = new(ctx) ast_iteration_statement(ast_iteration_statement::ast_while,
                                            NULL, yystack.l_mark[-2].node, NULL, yystack.l_mark[0].node);
      yyval.node->set_location_range(yystack.p_mark[-4], yystack.p_mark[-1]);
   }
#line 5888 "compiler/glsl/glsl_parser.cpp"
break;
case 265:
#line 2746 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      void *ctx = state->linalloc;
      yyval.node = new(ctx) ast_iteration_statement(ast_iteration_statement::ast_do_while,
                                            NULL, yystack.l_mark[-2].expression, NULL, yystack.l_mark[-5].node);
      yyval.node->set_location_range(yystack.p_mark[-6], yystack.p_mark[-1]);
   }
#line 5898 "compiler/glsl/glsl_parser.cpp"
break;
case 266:
#line 2753 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      void *ctx = state->linalloc;
      yyval.node = new(ctx) ast_iteration_statement(ast_iteration_statement::ast_for,
                                            yystack.l_mark[-3].node, yystack.l_mark[-2].for_rest_statement.cond, yystack.l_mark[-2].for_rest_statement.rest, yystack.l_mark[0].node);
      yyval.node->set_location_range(yystack.p_mark[-5], yystack.p_mark[0]);
   }
#line 5908 "compiler/glsl/glsl_parser.cpp"
break;
case 270:
#line 2769 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      yyval.node = NULL;
   }
#line 5915 "compiler/glsl/glsl_parser.cpp"
break;
case 271:
#line 2776 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      yyval.for_rest_statement.cond = yystack.l_mark[-1].node;
      yyval.for_rest_statement.rest = NULL;
   }
#line 5923 "compiler/glsl/glsl_parser.cpp"
break;
case 272:
#line 2781 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      yyval.for_rest_statement.cond = yystack.l_mark[-2].node;
      yyval.for_rest_statement.rest = yystack.l_mark[0].expression;
   }
#line 5931 "compiler/glsl/glsl_parser.cpp"
break;
case 273:
#line 2790 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      void *ctx = state->linalloc;
      yyval.node = new(ctx) ast_jump_statement(ast_jump_statement::ast_continue, NULL);
      yyval.node->set_location(yystack.p_mark[-1]);
   }
#line 5940 "compiler/glsl/glsl_parser.cpp"
break;
case 274:
#line 2796 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      void *ctx = state->linalloc;
      yyval.node = new(ctx) ast_jump_statement(ast_jump_statement::ast_break, NULL);
      yyval.node->set_location(yystack.p_mark[-1]);
   }
#line 5949 "compiler/glsl/glsl_parser.cpp"
break;
case 275:
#line 2802 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      void *ctx = state->linalloc;
      yyval.node = new(ctx) ast_jump_statement(ast_jump_statement::ast_return, NULL);
      yyval.node->set_location(yystack.p_mark[-1]);
   }
#line 5958 "compiler/glsl/glsl_parser.cpp"
break;
case 276:
#line 2808 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      void *ctx = state->linalloc;
      yyval.node = new(ctx) ast_jump_statement(ast_jump_statement::ast_return, yystack.l_mark[-1].expression);
      yyval.node->set_location_range(yystack.p_mark[-2], yystack.p_mark[-1]);
   }
#line 5967 "compiler/glsl/glsl_parser.cpp"
break;
case 277:
#line 2814 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      void *ctx = state->linalloc;
      yyval.node = new(ctx) ast_jump_statement(ast_jump_statement::ast_discard, NULL);
      yyval.node->set_location(yystack.p_mark[-1]);
   }
#line 5976 "compiler/glsl/glsl_parser.cpp"
break;
case 278:
#line 2823 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      void *ctx = state->linalloc;
      yyval.node = new(ctx) ast_demote_statement();
      yyval.node->set_location(yystack.p_mark[-1]);
   }
#line 5985 "compiler/glsl/glsl_parser.cpp"
break;
case 279:
#line 2831 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{ yyval.node = yystack.l_mark[0].function_definition; }
#line 5990 "compiler/glsl/glsl_parser.cpp"
break;
case 280:
#line 2832 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{ yyval.node = yystack.l_mark[0].node; }
#line 5995 "compiler/glsl/glsl_parser.cpp"
break;
case 281:
#line 2833 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{ yyval.node = yystack.l_mark[0].node; }
#line 6000 "compiler/glsl/glsl_parser.cpp"
break;
case 282:
#line 2834 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{ yyval.node = yystack.l_mark[0].node; }
#line 6005 "compiler/glsl/glsl_parser.cpp"
break;
case 283:
#line 2835 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{ yyval.node = NULL; }
#line 6010 "compiler/glsl/glsl_parser.cpp"
break;
case 284:
#line 2840 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      void *ctx = state->linalloc;
      yyval.function_definition = new(ctx) ast_function_definition();
      yyval.function_definition->set_location_range(yystack.p_mark[-1], yystack.p_mark[0]);
      yyval.function_definition->prototype = yystack.l_mark[-1].function;
      yyval.function_definition->body = yystack.l_mark[0].compound_statement;

      state->symbols->pop_scope();
   }
#line 6023 "compiler/glsl/glsl_parser.cpp"
break;
case 285:
#line 2854 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      yyval.node = yystack.l_mark[0].interface_block;
   }
#line 6030 "compiler/glsl/glsl_parser.cpp"
break;
case 286:
#line 2858 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      ast_interface_block *block = (ast_interface_block *) yystack.l_mark[0].node;

      if (!yystack.l_mark[-1].type_qualifier.merge_qualifier(& yystack.p_mark[-1], state, block->layout, false,
                              block->layout.has_layout())) {
         YYERROR;
      }

      block->layout = yystack.l_mark[-1].type_qualifier;

      yyval.node = block;
   }
#line 6046 "compiler/glsl/glsl_parser.cpp"
break;
case 287:
#line 2871 "../mesa/src/compiler/glsl/glsl_parser.yy"
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
#line 6064 "compiler/glsl/glsl_parser.cpp"
break;
case 288:
#line 2889 "../mesa/src/compiler/glsl/glsl_parser.yy"
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
#line 6083 "compiler/glsl/glsl_parser.cpp"
break;
case 289:
#line 2908 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      memset(& yyval.type_qualifier, 0, sizeof(yyval.type_qualifier));
      yyval.type_qualifier.flags.q.in = 1;
   }
#line 6091 "compiler/glsl/glsl_parser.cpp"
break;
case 290:
#line 2913 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      memset(& yyval.type_qualifier, 0, sizeof(yyval.type_qualifier));
      yyval.type_qualifier.flags.q.out = 1;
   }
#line 6099 "compiler/glsl/glsl_parser.cpp"
break;
case 291:
#line 2918 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      memset(& yyval.type_qualifier, 0, sizeof(yyval.type_qualifier));
      yyval.type_qualifier.flags.q.uniform = 1;
   }
#line 6107 "compiler/glsl/glsl_parser.cpp"
break;
case 292:
#line 2923 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      memset(& yyval.type_qualifier, 0, sizeof(yyval.type_qualifier));
      yyval.type_qualifier.flags.q.buffer = 1;
   }
#line 6115 "compiler/glsl/glsl_parser.cpp"
break;
case 293:
#line 2928 "../mesa/src/compiler/glsl/glsl_parser.yy"
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
#line 6129 "compiler/glsl/glsl_parser.cpp"
break;
case 294:
#line 2942 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      yyval.interface_block = new(state->linalloc) ast_interface_block(NULL, NULL);
   }
#line 6136 "compiler/glsl/glsl_parser.cpp"
break;
case 295:
#line 2946 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      yyval.interface_block = new(state->linalloc) ast_interface_block(yystack.l_mark[0].identifier, NULL);
      yyval.interface_block->set_location(yystack.p_mark[0]);
   }
#line 6144 "compiler/glsl/glsl_parser.cpp"
break;
case 296:
#line 2951 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      yyval.interface_block = new(state->linalloc) ast_interface_block(yystack.l_mark[-1].identifier, yystack.l_mark[0].array_specifier);
      yyval.interface_block->set_location_range(yystack.p_mark[-1], yystack.p_mark[0]);
   }
#line 6152 "compiler/glsl/glsl_parser.cpp"
break;
case 297:
#line 2959 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      yyval.declarator_list = yystack.l_mark[0].declarator_list;
      yystack.l_mark[0].declarator_list->link.self_link();
   }
#line 6160 "compiler/glsl/glsl_parser.cpp"
break;
case 298:
#line 2964 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      yyval.declarator_list = yystack.l_mark[-1].declarator_list;
      yystack.l_mark[0].declarator_list->link.insert_before(& yyval.declarator_list->link);
   }
#line 6168 "compiler/glsl/glsl_parser.cpp"
break;
case 299:
#line 2972 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      void *ctx = state->linalloc;
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
#line 6192 "compiler/glsl/glsl_parser.cpp"
break;
case 300:
#line 2996 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      yyval.type_qualifier = yystack.l_mark[-1].type_qualifier;
      if (!yyval.type_qualifier.merge_qualifier(& yystack.p_mark[-1], state, yystack.l_mark[0].type_qualifier, false, true)) {
         YYERROR;
      }
   }
#line 6202 "compiler/glsl/glsl_parser.cpp"
break;
case 302:
#line 3007 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      yyval.type_qualifier = yystack.l_mark[-1].type_qualifier;
      if (!yyval.type_qualifier.merge_qualifier(& yystack.p_mark[-1], state, yystack.l_mark[0].type_qualifier, false, true)) {
         YYERROR;
      }
   }
#line 6212 "compiler/glsl/glsl_parser.cpp"
break;
case 304:
#line 3018 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      yyval.type_qualifier = yystack.l_mark[-1].type_qualifier;
      if (!yyval.type_qualifier.merge_qualifier(& yystack.p_mark[-1], state, yystack.l_mark[0].type_qualifier, false, true)) {
         YYERROR;
      }
      if (!yyval.type_qualifier.validate_in_qualifier(& yystack.p_mark[-1], state)) {
         YYERROR;
      }
   }
#line 6225 "compiler/glsl/glsl_parser.cpp"
break;
case 305:
#line 3028 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      if (!yystack.l_mark[-2].type_qualifier.validate_in_qualifier(& yystack.p_mark[-2], state)) {
         YYERROR;
      }
   }
#line 6234 "compiler/glsl/glsl_parser.cpp"
break;
case 306:
#line 3037 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      yyval.type_qualifier = yystack.l_mark[-1].type_qualifier;
      if (!yyval.type_qualifier.merge_qualifier(& yystack.p_mark[-1], state, yystack.l_mark[0].type_qualifier, false, true)) {
         YYERROR;
      }
      if (!yyval.type_qualifier.validate_out_qualifier(& yystack.p_mark[-1], state)) {
         YYERROR;
      }
   }
#line 6247 "compiler/glsl/glsl_parser.cpp"
break;
case 307:
#line 3047 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      if (!yystack.l_mark[-2].type_qualifier.validate_out_qualifier(& yystack.p_mark[-2], state)) {
         YYERROR;
      }
   }
#line 6256 "compiler/glsl/glsl_parser.cpp"
break;
case 308:
#line 3056 "../mesa/src/compiler/glsl/glsl_parser.yy"
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
#line 6271 "compiler/glsl/glsl_parser.cpp"
break;
case 309:
#line 3068 "../mesa/src/compiler/glsl/glsl_parser.yy"
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
#line 6296 "compiler/glsl/glsl_parser.cpp"
break;
case 310:
#line 3090 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      yyval.node = NULL;
      if (!yystack.l_mark[0].type_qualifier.merge_into_in_qualifier(& yystack.p_mark[0], state, yyval.node)) {
         YYERROR;
      }
      if (!state->in_qualifier->push_to_global(& yystack.p_mark[0], state)) {
         YYERROR;
      }
   }
#line 6309 "compiler/glsl/glsl_parser.cpp"
break;
case 311:
#line 3100 "../mesa/src/compiler/glsl/glsl_parser.yy"
	{
      yyval.node = NULL;
      if (!yystack.l_mark[0].type_qualifier.merge_into_out_qualifier(& yystack.p_mark[0], state, yyval.node)) {
         YYERROR;
      }
      if (!state->out_qualifier->push_to_global(& yystack.p_mark[0], state)) {
         YYERROR;
      }
   }
#line 6322 "compiler/glsl/glsl_parser.cpp"
break;
#line 6324 "compiler/glsl/glsl_parser.cpp"
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
