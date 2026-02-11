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
