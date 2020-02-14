#!/bin/sh

byacc -o glcpp-parse.c -p glcpp_parser_ --defines=glcpp-parse.h ../mesa/src/compiler/glsl/glcpp/glcpp-parse.y
flex -o glcpp-lex.c ../mesa/src/compiler/glsl/glcpp/glcpp-lex.l

byacc -o glsl_parser.cpp -p _mesa_glsl_ --defines=glsl_parser.h ../mesa/src/compiler/glsl/glsl_parser.yy
flex -o glsl_lexer.cpp ../mesa/src/compiler/glsl/glsl_lexer.ll

python3 ../mesa/src/compiler/glsl/ir_expression_operation.py constant >ir_expression_operation_constant.h
python3 ../mesa/src/compiler/glsl/ir_expression_operation.py strings >ir_expression_operation_strings.h
