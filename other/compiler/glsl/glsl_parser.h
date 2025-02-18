#ifndef __mesa_glsl__defines_h_
#define __mesa_glsl__defines_h_

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
#ifdef YYSTYPE
#undef  YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
#endif
#ifndef YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
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
extern YYLTYPE _mesa_glsl_lloc;

#endif /* __mesa_glsl__defines_h_ */
