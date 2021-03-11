#ifndef _glcpp_parser__defines_h_
#define _glcpp_parser__defines_h_

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
extern YYLTYPE glcpp_parser_lloc;

#endif /* _glcpp_parser__defines_h_ */
