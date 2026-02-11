#!/bin/sh

mkdir compiler &>/dev/null
python3 ../mesa/src/compiler/builtin_types_c.py compiler/builtin_types.c
python3 ../mesa/src/compiler/builtin_types_h.py compiler/builtin_types.h

mkdir compiler/glsl &>/dev/null
flex -o compiler/glsl/glsl_lexer.cpp ../mesa/src/compiler/glsl/glsl_lexer.ll
byacc -o compiler/glsl/glsl_parser.cpp -p _mesa_glsl_ --defines=compiler/glsl/glsl_parser.h ../mesa/src/compiler/glsl/glsl_parser.yy
python3 ../mesa/src/compiler/glsl/ir_expression_operation.py constant >compiler/glsl/ir_expression_operation_constant.h
python3 ../mesa/src/compiler/glsl/ir_expression_operation.py enum >compiler/glsl/ir_expression_operation.h
python3 ../mesa/src/compiler/glsl/ir_expression_operation.py strings >compiler/glsl/ir_expression_operation_strings.h

mkdir compiler/glsl/glcpp &>/dev/null
flex -o compiler/glsl/glcpp/glcpp-lex.c ../mesa/src/compiler/glsl/glcpp/glcpp-lex.l
byacc -o compiler/glsl/glcpp/glcpp-parse.c -p glcpp_parser_ --defines=compiler/glsl/glcpp/glcpp-parse.h ../mesa/src/compiler/glsl/glcpp/glcpp-parse.y

mkdir compiler/nir &>/dev/null
python3 ../mesa/src/compiler/nir/nir_intrinsics_h.py --out compiler/nir/nir_intrinsics.h
python3 ../mesa/src/compiler/nir/nir_intrinsics_indices_h.py --out compiler/nir/nir_intrinsics_indices.h
python3 ../mesa/src/compiler/nir/nir_opcodes_h.py >compiler/nir/nir_opcodes.h

mkdir util &>/dev/null
python3 ../mesa/src/util/format_srgb.py >util/format_srgb.c

mkdir util/format &>/dev/null
python3 ../mesa/src/util/format/u_format_table.py ../mesa/src/util/format/u_format.yaml >util/format/u_format_table.c
python3 ../mesa/src/util/format/u_format_table.py ../mesa/src/util/format/u_format.yaml --enums >util/format/u_format_gen.h
python3 ../mesa/src/util/format/u_format_table.py ../mesa/src/util/format/u_format.yaml --header >util/format/u_format_pack.h
