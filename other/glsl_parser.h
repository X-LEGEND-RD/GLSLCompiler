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
#define INTERFACE 340
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
