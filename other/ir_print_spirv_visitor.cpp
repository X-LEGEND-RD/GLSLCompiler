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

#include "ir_print_spirv_visitor.h"
#include "compiler/glsl_types.h"
#include "glsl_parser_extras.h"
#include "main/macros.h"
#include "util/hash_table.h"
#include "compiler/spirv/spirv.h"
#include "compiler/spirv/GLSL.std.450.h"

binary_buffer::binary_buffer(unsigned int* buf, size_t size)
   : buf(buf)
   , step(0)
   , size(size)
{
}

void binary_buffer::push(unsigned int value) {
   buf[step++] = value;
}

void binary_buffer::push(const char* text) {
   size_t len = strlen(text);
   size_t count = (len + sizeof(unsigned int)) / sizeof(unsigned int);
   for (size_t i = 0; i < count; ++i)
      buf[step + i] = 0;
   memcpy(buf + step, text, len);
   step += count;
}

size_t binary_buffer::count() const {
   return step;
}

spirv_buffer::spirv_buffer(unsigned int* buf, size_t size)
   : binary_buffer(buf, size)
   , extensions_data(new unsigned int[16384])
   , names_data(new unsigned int[16384])
   , decorates_data(new unsigned int[16384])
   , types_data(new unsigned int[16384])
   , uniforms_data(new unsigned int[16384])
   , inouts_data(new unsigned int[16384])
   , functions_data(new unsigned int[16384])
   , extensions(extensions_data, 16384)
   , names(names_data, 16384)
   , decorates(decorates_data, 16384)
   , types(types_data, 16384)
   , uniforms(uniforms_data, 16384)
   , inouts(inouts_data, 16384)
   , functions(functions_data, 16384)
{
   precision_float = GLSL_PRECISION_NONE;
   precision_int = GLSL_PRECISION_NONE;
}

spirv_buffer::~spirv_buffer() {
   delete[] extensions_data;
   delete[] names_data;
   delete[] decorates_data;
   delete[] types_data;
   delete[] uniforms_data;
   delete[] inouts_data;
   delete[] functions_data;
}

extern "C" {
void
_mesa_print_spirv(spirv_buffer *f, exec_list *instructions)
{
   f->id = 1;
   f->import_id = 0;
   f->uniform_struct_id = 0;
   f->uniform_id = 0;
   f->uniform_pointer_id = 0;
   f->uniform_offset = 0;
   f->function_id = 0;
   f->main_id = 0;
   f->void_id = 0;
   f->bool_id = 0;
   memset(f->float_id, 0, sizeof(f->float_id));
   memset(f->int_id, 0, sizeof(f->int_id));
   memset(f->const_float_id, 0, sizeof(f->const_float_id));
   memset(f->const_int_id, 0, sizeof(f->const_int_id));

   // ExtInstImport
   f->import_id = f->id++;
   f->extensions.push(SpvOpExtInstImport | (6 << SpvWordCountShift));
   f->extensions.push(f->import_id);
   f->extensions.push("GLSL.std.450");

   // MemoryModel Logical GLSL450
   f->extensions.push(SpvOpMemoryModel | (3 << SpvWordCountShift));
   f->extensions.push(SpvAddressingModelLogical);
   f->extensions.push(SpvMemoryModelGLSL450);

   foreach_in_list(ir_instruction, ir, instructions) {
      ir_print_spirv_visitor v(f);
      ir->accept(&v);
   }

   unsigned int uniforms_count = f->uniforms.count();
   if (uniforms_count != 0) {
      f->types.push(SpvOpTypeStruct | ((uniforms_count + 2) << SpvWordCountShift));
      f->types.push(f->uniform_struct_id);
      for (unsigned int i = 0; i < f->uniforms.count(); ++i) {
         f->types.push(f->uniforms_data[i]);
      }

      f->types.push(SpvOpTypePointer | (4 << SpvWordCountShift));
      f->types.push(f->uniform_pointer_id);
      f->types.push(SpvStorageClassUniform);
      f->types.push(f->uniform_struct_id);

      f->types.push(SpvOpVariable | (4 << SpvWordCountShift));
      f->types.push(f->uniform_pointer_id);
      f->types.push(f->uniform_id);
      f->types.push(SpvStorageClassUniform);
   }

   // Header
   unsigned int bound_id = f->id++;
   f->push(SpvMagicNumber);
   f->push(SpvVersion);
   f->push(0x000B0000);
   f->push(bound_id);
   f->push(0u);

   // Capability
   f->push(SpvOpCapability | (2 << SpvWordCountShift));
   f->push(SpvCapabilityShader);

   for (unsigned int i = 0; i < f->extensions.count(); ++i) {
      f->push(f->extensions_data[i]);
   }

   // EntryPoint Fragment 4  "main" 20 22 37 43 46 49
   f->push(SpvOpEntryPoint | ((5 + f->inouts.count()) << SpvWordCountShift));
   f->push(SpvExecutionModelFragment);
   f->push(f->main_id);
   f->push("main");
   for (unsigned int i = 0; i < f->inouts.count(); ++i) {
      f->push(f->inouts_data[i]);
   }

   // ExecutionMode 4 OriginUpperLeft
   f->push(SpvOpExecutionMode | (3 << SpvWordCountShift));
   f->push(f->main_id);
   f->push(SpvExecutionModeOriginUpperLeft);

   // Source ESSL 310
   f->push(SpvOpSource | (3 << SpvWordCountShift));
   f->push(SpvSourceLanguageESSL);
   f->push(310u);

   for (unsigned int i = 0; i < f->names.count(); ++i) {
      f->push(f->names_data[i]);
   }

   for (unsigned int i = 0; i < f->decorates.count(); ++i) {
      f->push(f->decorates_data[i]);
   }

   for (unsigned int i = 0; i < f->types.count(); ++i) {
      f->push(f->types_data[i]);
   }

   for (unsigned int i = 0; i < f->functions.count(); ++i) {
      f->push(f->functions_data[i]);
   }
}

} /* extern "C" */

ir_print_spirv_visitor::ir_print_spirv_visitor(spirv_buffer *f)
   : f(f)
{
   indentation = 0;
   printable_names =
      _mesa_hash_table_create(NULL, _mesa_hash_pointer, _mesa_key_pointer_equal);
   mem_ctx = ralloc_context(NULL);
}

ir_print_spirv_visitor::~ir_print_spirv_visitor()
{
   _mesa_hash_table_destroy(printable_names, NULL);
   ralloc_free(mem_ctx);
}

unsigned int
ir_print_spirv_visitor::unique_name(ir_variable *var)
{
   /* var->name can be NULL in function prototypes when a type is given for a
    * parameter but no name is given.  In that case, just return an empty
    * string.  Don't worry about tracking the generated name in the printable
    * names hash because this is the only scope where it can ever appear.
    */
   if (var->name == NULL) {
      static unsigned arg = 1;
      return (unsigned int) arg++;
   }

   /* Do we already have a name for this variable? */
   struct hash_entry * entry =
      _mesa_hash_table_search(this->printable_names, var);

   if (entry != NULL) {
      return (unsigned int)(intptr_t) entry->data;
   }

   unsigned int name_id = f->id++;
   size_t len = strlen(var->name);
   size_t count = (len + sizeof(unsigned int)) / sizeof(unsigned int);
   f->names.push(SpvOpName | ((count + 2) << SpvWordCountShift));
   f->names.push(name_id);
   f->names.push(var->name);
   var->ir_temp = name_id;

   if (var->data.precision == GLSL_PRECISION_MEDIUM) {
      f->decorates.push(SpvOpDecorate | (3 << SpvWordCountShift));
      f->decorates.push(var->ir_temp);
      f->decorates.push(SpvDecorationRelaxedPrecision);
   }

   _mesa_hash_table_insert(this->printable_names, var, (void *)(intptr_t) name_id);

   return name_id;
}

void ir_print_spirv_visitor::visit(ir_rvalue *)
{
   //fprintf(f, "error");
}

unsigned int visit_type(spirv_buffer *f, const struct glsl_type *type)
{
   unsigned int vector_id;
   unsigned int* ids;
   if (type->is_array()) {
      unsigned int int_type_id = visit_type(f, glsl_type::int_type);
      unsigned int base_type_id = visit_type(f, type->fields.array);

      unsigned int constant_id = f->id++;
      f->types.push(SpvOpConstant | (4 << SpvWordCountShift));
      f->types.push(int_type_id);
      f->types.push(constant_id);
      f->types.push(type->array_size());

      vector_id = f->id++;
      f->types.push(SpvOpTypeArray | (4 << SpvWordCountShift));
      f->types.push(vector_id);
      f->types.push(base_type_id);
      f->types.push(constant_id);

      return vector_id;
   }
   if (type->is_float()) {
      ids = f->float_id;
   } else if (type->is_integer()) {
      ids = f->int_id;
   } else if (type->is_boolean()) {
      if (f->bool_id == 0) {
         f->bool_id = f->id++;
         f->types.push(SpvOpTypeBool | (2 << SpvWordCountShift));
         f->types.push(f->bool_id);
      }
      return f->bool_id;
   } else {
      return 0;
   }

   unsigned int offset = (type->vector_elements - 1) + (type->matrix_columns - 1) * 4;
   if (ids[0] == 0) {
      ids[0] = f->id++;
      if (type->is_float()) {
         f->types.push(SpvOpTypeFloat | (3 << SpvWordCountShift));
         f->types.push(ids[0]);
         f->types.push(32u);
      } else if (type->is_integer()) {
         f->types.push(SpvOpTypeInt | (4 << SpvWordCountShift));
         f->types.push(ids[0]);
         f->types.push(32u);
         f->types.push(1u);
      }
   }
   unsigned int component = type->vector_elements;
   if (component > 1 && ids[component - 1] == 0) {
      ids[component - 1] = f->id++;
      f->types.push(SpvOpTypeVector | (4 << SpvWordCountShift));
      f->types.push(ids[component - 1]);
      f->types.push(ids[0]);
      f->types.push(type->vector_elements);
   }
   unsigned int column = type->matrix_columns;
   if (column > 4) {
      vector_id = f->id++;
      f->types.push(SpvOpTypeMatrix | (4 << SpvWordCountShift));
      f->types.push(vector_id);
      f->types.push(ids[component - 1]);
      f->types.push(type->matrix_columns);
   } else if (column > 1 && ids[offset] == 0) {
      vector_id = ids[offset] = f->id++;
      f->types.push(SpvOpTypeMatrix | (4 << SpvWordCountShift));
      f->types.push(ids[offset]);
      f->types.push(ids[component - 1]);
      f->types.push(type->matrix_columns);
   } else {
      vector_id = ids[offset];
   }

   return vector_id;
}

void ir_print_spirv_visitor::visit(ir_variable *ir)
{
   unsigned int vector_id = visit_type(f, ir->type);

   const unsigned int mode[] = {
      SpvStorageClassFunction,       // ir_var_auto
      SpvStorageClassUniform,        // ir_var_uniform
      SpvStorageClassWorkgroup,      // ir_var_shader_storage
      SpvStorageClassCrossWorkgroup, // ir_var_shader_shared
      SpvStorageClassInput,          // ir_var_shader_in
      SpvStorageClassOutput,         // ir_var_shader_out
      SpvStorageClassInput,          // ir_var_function_in
      SpvStorageClassOutput,         // ir_var_function_out
      SpvStorageClassWorkgroup,      // ir_var_function_inout
      SpvStorageClassPushConstant,   // ir_var_const_in
      SpvStorageClassGeneric,        // ir_var_system_value
      SpvStorageClassFunction,       // ir_var_temporary
   };

   if (ir->data.mode == ir_var_uniform) {

      if (f->uniform_struct_id == 0) {
         f->uniform_struct_id = f->id++;
         size_t len = strlen("Global");
         size_t count = (len + sizeof(unsigned int)) / sizeof(unsigned int);
         f->names.push(SpvOpName | ((count + 2) << SpvWordCountShift));
         f->names.push(f->uniform_struct_id);
         f->names.push("Global");

         f->decorates.push(SpvOpDecorate | (3 << SpvWordCountShift));
         f->decorates.push(f->uniform_struct_id);
         f->decorates.push(SpvDecorationBlock);
      }

      if (f->uniform_id == 0) {

         f->uniform_pointer_id = f->id++;
         f->uniform_id = f->id++;

         size_t len = strlen("global");
         size_t count = (len + sizeof(unsigned int)) / sizeof(unsigned int);
         f->names.push(SpvOpName | ((count + 2) << SpvWordCountShift));
         f->names.push(f->uniform_id);
         f->names.push("global");

         f->decorates.push(SpvOpDecorate | (4 << SpvWordCountShift));
         f->decorates.push(f->uniform_id);
         f->decorates.push(SpvDecorationDescriptorSet);
         f->decorates.push(0u);
      }

      if (ir->type->is_sampler()) {

         unsigned int name_id = f->id++;
         size_t len = strlen(ir->name);
         size_t count = (len + sizeof(unsigned int)) / sizeof(unsigned int);
         f->names.push(SpvOpName | ((count + 2) << SpvWordCountShift));
         f->names.push(name_id);
         f->names.push(ir->name);

         f->decorates.push(SpvOpDecorate | (4 << SpvWordCountShift));
         f->decorates.push(name_id);
         f->decorates.push(SpvDecorationDescriptorSet);
         f->decorates.push(0u);

      } else {

         size_t len = strlen(ir->name);
         size_t count = (len + sizeof(unsigned int)) / sizeof(unsigned int);
         f->names.push(SpvOpMemberName | ((count + 3) << SpvWordCountShift));
         f->names.push(f->uniform_struct_id);
         f->names.push(f->uniforms.count());
         f->names.push(ir->name);

         if (ir->data.precision == GLSL_PRECISION_MEDIUM) {
            f->decorates.push(SpvOpMemberDecorate | (4 << SpvWordCountShift));
            f->decorates.push(f->uniform_struct_id);
            f->decorates.push(f->uniforms.count());
            f->decorates.push(SpvDecorationRelaxedPrecision);
         }

         f->decorates.push(SpvOpMemberDecorate | (5 << SpvWordCountShift));
         f->decorates.push(f->uniform_struct_id);
         f->decorates.push(f->uniforms.count());
         f->decorates.push(SpvDecorationOffset);
         f->decorates.push(f->uniform_offset);

         ir->ir_temp2 = f->uniforms.count();

         f->uniforms.push(vector_id);
         f->uniform_offset += ir->type->matrix_columns * 16;
      }

   } else {

      unsigned int pointer_id = f->id++;
      f->types.push(SpvOpTypePointer | (4 << SpvWordCountShift));
      f->types.push(pointer_id);
      f->types.push(mode[ir->data.mode]);
      f->types.push(vector_id);

      unsigned int name_id = unique_name(ir);

      if (ir->data.mode == ir_var_auto || ir->data.mode == ir_var_temporary) {
         f->functions.push(SpvOpVariable | (4 << SpvWordCountShift));
         f->functions.push(pointer_id);
         f->functions.push(name_id);
         f->functions.push(mode[ir->data.mode]);
      } else {
         f->types.push(SpvOpVariable | (4 << SpvWordCountShift));
         f->types.push(pointer_id);
         f->types.push(name_id);
         f->types.push(mode[ir->data.mode]);
      }

      if (ir->data.mode == ir_var_shader_in || ir->data.mode == ir_var_shader_out || ir->data.mode == ir_var_temporary) {
         f->inouts.push(name_id);
      }
   }
}

void ir_print_spirv_visitor::visit(ir_function_signature *ir)
{
   // TypeVoid
   unsigned int type_id;
   if (ir->return_type->base_type == GLSL_TYPE_VOID) {
      if (f->void_id == 0) {
         f->void_id = f->id++;
         f->types.push(SpvOpTypeVoid | (2 << SpvWordCountShift));
         f->types.push(f->void_id);
      }
      type_id = f->void_id;
   } else {
      return;
      type_id = f->id++;
      f->types.push(SpvOpTypeVoid | (2 << SpvWordCountShift));
      f->types.push(type_id);
   }

   // TypeFunction
   unsigned int function_id = f->id++;
   f->types.push(SpvOpTypeFunction | (3 << SpvWordCountShift));
   f->types.push(function_id);
   f->types.push(type_id);

   // TypeName
   unsigned int function_name_id = f->id++;
   size_t len = strlen(ir->function_name());
   size_t count = (len + sizeof(unsigned int)) / sizeof(unsigned int);
   f->names.push(SpvOpName | ((count + 2) << SpvWordCountShift));
   f->names.push(function_name_id);
   f->names.push(ir->function_name());
   f->functions.push(SpvOpFunction | (5 << SpvWordCountShift));
   f->functions.push(type_id);
   f->functions.push(function_name_id);
   f->functions.push(SpvFunctionControlMaskNone);
   f->functions.push(function_id);

   if (stricmp(ir->function_name(), "main") == 0) {
      f->main_id = function_name_id;
   }

   // Label
   unsigned int label_id = f->id++;
   f->functions.push(SpvOpLabel | (2 << SpvWordCountShift));
   f->functions.push(label_id);

   foreach_in_list(ir_variable, inst, &ir->parameters) {
      inst->accept(this);
   }

   foreach_in_list(ir_instruction, inst, &ir->body) {
      inst->accept(this);
   }

   // Return
   f->functions.push(SpvOpReturn | (1 << SpvWordCountShift));

   // FunctionEnd
   f->functions.push(SpvOpFunctionEnd | (1 << SpvWordCountShift));
}

void ir_print_spirv_visitor::visit(ir_function *ir)
{
   foreach_in_list(ir_function_signature, sig, &ir->signatures) {
      sig->accept(this);
   }
}

void ir_print_spirv_visitor::visit(ir_expression *ir)
{
   unsigned int return_id = visit_type(f, ir->type);

   if (ir->operation >= ir_unop_bit_not && ir->operation <= ir_unop_vote_eq) {
      if (ir->get_num_operands() != 1)
         return;

      if (ir->operands[0] == NULL)
         return;
      ir->operands[0]->accept(this);

      unsigned int value_id = f->id++;
      switch (ir->operation) {
      default:
      case ir_unop_neg:
         f->functions.push(SpvOpFNegate | (4 << SpvWordCountShift));
         f->functions.push(return_id);
         f->functions.push(value_id);
         break;
      case ir_unop_rcp: {
         ir_constant ir(1.0f);
         ir.ir_temp = 0;
         visit(&ir);

         f->functions.push(SpvOpFDiv | (5 << SpvWordCountShift));
         f->functions.push(return_id);
         f->functions.push(value_id);
         f->functions.push(ir.ir_temp);
         break;
      }
      case ir_unop_abs:
      case ir_unop_sign:
      case ir_unop_rsq:
      case ir_unop_sqrt:
      case ir_unop_normalize:
      case ir_unop_exp:
      case ir_unop_log:
      case ir_unop_exp2:
      case ir_unop_log2:
      case ir_unop_trunc:
      case ir_unop_ceil:
      case ir_unop_floor:
      case ir_unop_fract:
      case ir_unop_round_even:
      case ir_unop_sin:
      case ir_unop_cos:
         f->functions.push(SpvOpExtInst | (6 << SpvWordCountShift));
         f->functions.push(return_id);
         f->functions.push(value_id);
         f->functions.push(f->import_id);
         switch (ir->operation) {
         default:
         case ir_unop_abs:       f->functions.push(GLSLstd450FAbs);        break;
         case ir_unop_sign:      f->functions.push(GLSLstd450FSign);       break;
         case ir_unop_rsq:       f->functions.push(GLSLstd450InverseSqrt); break;
         case ir_unop_sqrt:      f->functions.push(GLSLstd450Sqrt);        break;
         case ir_unop_normalize: f->functions.push(GLSLstd450Normalize);   break;
         case ir_unop_exp:       f->functions.push(GLSLstd450Exp);         break;
         case ir_unop_log:       f->functions.push(GLSLstd450Log);         break;
         case ir_unop_exp2:      f->functions.push(GLSLstd450Exp2);        break;
         case ir_unop_log2:      f->functions.push(GLSLstd450Log2);        break;
         case ir_unop_trunc:     f->functions.push(GLSLstd450Trunc);       break;
         case ir_unop_ceil:      f->functions.push(GLSLstd450Ceil);        break;
         case ir_unop_floor:     f->functions.push(GLSLstd450Floor);       break;
         case ir_unop_fract:     f->functions.push(GLSLstd450Fract);       break;
         case ir_unop_round_even:f->functions.push(GLSLstd450RoundEven);   break;
         case ir_unop_sin:       f->functions.push(GLSLstd450Sin);         break;
         case ir_unop_cos:       f->functions.push(GLSLstd450Cos);         break;
         }
         break;
      }
      f->functions.push(ir->operands[0]->ir_temp);
      ir->ir_temp = value_id;
   } else if (ir->operation >= ir_binop_add && ir->operation <= ir_binop_interpolate_at_sample) {
      if (ir->get_num_operands() != 2)
         return;

      if (ir->operands[0] == NULL || ir->operands[1] == NULL)
         return;
      ir->operands[0]->accept(this);
      ir->operands[1]->accept(this);

      unsigned int value_id = f->id++;
      switch (ir->operation) {
      default:
      case ir_binop_add:
      case ir_binop_sub:
      case ir_binop_mul:
      case ir_binop_div:
      case ir_binop_mod:
      case ir_binop_less:
      case ir_binop_greater:
      case ir_binop_lequal:
      case ir_binop_gequal:
      case ir_binop_equal:
      case ir_binop_nequal:
      case ir_binop_dot:
         switch (ir->operation) {
         default:
         case ir_binop_add:         f->functions.push(SpvOpFAdd | (5 << SpvWordCountShift));                    break;
         case ir_binop_sub:         f->functions.push(SpvOpFSub | (5 << SpvWordCountShift));                    break;
         case ir_binop_mul:         f->functions.push(SpvOpFMul | (5 << SpvWordCountShift));                    break;
         case ir_binop_div:         f->functions.push(SpvOpFDiv | (5 << SpvWordCountShift));                    break;
         case ir_binop_mod:         f->functions.push(SpvOpFMod | (5 << SpvWordCountShift));                    break;
         case ir_binop_less:        f->functions.push(SpvOpFOrdLessThan | (5 << SpvWordCountShift));            break;
         case ir_binop_greater:     f->functions.push(SpvOpFOrdGreaterThan | (5 << SpvWordCountShift));         break;
         case ir_binop_lequal:      f->functions.push(SpvOpFOrdLessThanEqual | (5 << SpvWordCountShift));       break;
         case ir_binop_gequal:      f->functions.push(SpvOpFOrdGreaterThanEqual | (5 << SpvWordCountShift));    break;
         case ir_binop_equal:       f->functions.push(SpvOpFOrdEqual | (5 << SpvWordCountShift));               break;
         case ir_binop_nequal:      f->functions.push(SpvOpFOrdNotEqual | (5 << SpvWordCountShift));            break;
         case ir_binop_dot:         f->functions.push(SpvOpDot | (5 << SpvWordCountShift));                     break;
         }
         f->functions.push(return_id);
         f->functions.push(value_id);
         break;
      case ir_binop_min:
      case ir_binop_max:
      case ir_binop_pow:
      case ir_binop_ldexp:
         f->functions.push(SpvOpExtInst | (7 << SpvWordCountShift));
         f->functions.push(return_id);
         f->functions.push(value_id);
         f->functions.push(f->import_id);
         switch (ir->operation) {
         default:
         case ir_binop_min:      f->functions.push(GLSLstd450FMin);  break;
         case ir_binop_max:      f->functions.push(GLSLstd450FMax);  break;
         case ir_binop_pow:      f->functions.push(GLSLstd450Pow);   break;
         case ir_binop_ldexp:    f->functions.push(GLSLstd450Ldexp); break;
         }
         break;
      }
      f->functions.push(ir->operands[0]->ir_temp);
      f->functions.push(ir->operands[1]->ir_temp);
      ir->ir_temp = value_id;
   } else if (ir->operation >= ir_triop_fma && ir->operation <= ir_triop_vector_insert) {
      if (ir->get_num_operands() != 3)
         return;

      if (ir->operands[0] == NULL || ir->operands[1] == NULL || ir->operands[2] == NULL)
         return;
      ir->operands[0]->accept(this);
      ir->operands[1]->accept(this);
      ir->operands[2]->accept(this);

      unsigned int value_id = f->id++;
      switch (ir->operation) {
      default:
      case ir_triop_fma:
      case ir_triop_lrp:
         f->functions.push(SpvOpExtInst | (8 << SpvWordCountShift));
         f->functions.push(return_id);
         f->functions.push(value_id);
         f->functions.push(f->import_id);
         switch (ir->operation) {
         default:
         case ir_triop_fma:   f->functions.push(GLSLstd450Fma);   break;
         case ir_triop_lrp:   f->functions.push(GLSLstd450FMix);  break;
         }
         break;
      }
      f->functions.push(ir->operands[0]->ir_temp);
      f->functions.push(ir->operands[1]->ir_temp);
      f->functions.push(ir->operands[2]->ir_temp);
      ir->ir_temp = value_id;
   }

   switch (ir->type->base_type) {
   default:
      break;
   case GLSL_TYPE_UINT:
   case GLSL_TYPE_INT:
      if (f->precision_int == GLSL_PRECISION_MEDIUM) {
         f->decorates.push(SpvOpDecorate | (3 << SpvWordCountShift));
         f->decorates.push(ir->ir_temp);
         f->decorates.push(SpvDecorationRelaxedPrecision);
      }
      break;
   case GLSL_TYPE_FLOAT:
      if (f->precision_float == GLSL_PRECISION_MEDIUM) {
         f->decorates.push(SpvOpDecorate | (3 << SpvWordCountShift));
         f->decorates.push(ir->ir_temp);
         f->decorates.push(SpvDecorationRelaxedPrecision);
      }
      break;
   }
}

void ir_print_spirv_visitor::visit(ir_texture *ir)
{
   if (ir->op == ir_samples_identical) {
      ir->sampler->accept(this);
      ir->coordinate->accept(this);
      return;
   }

   unsigned int ids_data[16];
   binary_buffer ids(ids_data, 16);

   ir->sampler->accept(this);
   ids.push(ir->sampler->ir_temp);

   if (ir->op != ir_txs && ir->op != ir_query_levels && ir->op != ir_texture_samples) {

      ir->coordinate->accept(this);
      ids.push(ir->coordinate->ir_temp);

      if (ir->offset != NULL) {
         ir->offset->accept(this);
         ids.push(ir->offset->ir_temp);
      }
   }

   if (ir->op != ir_txf && ir->op != ir_txf_ms && ir->op != ir_txs && ir->op != ir_tg4 && ir->op != ir_query_levels && ir->op != ir_texture_samples) {

      if (ir->projector) {
         ir->projector->accept(this);
         ids.push(ir->projector->ir_temp);
      }

      if (ir->shadow_comparitor) {
         ir->shadow_comparitor->accept(this);
         ids.push(ir->shadow_comparitor->ir_temp);
      }
   }

   switch (ir->op)
   {
   case ir_tex:
   case ir_lod:
   case ir_query_levels:
   case ir_texture_samples:
      break;
   case ir_txb:
      ir->lod_info.bias->accept(this);
      ids.push(ir->lod_info.bias->ir_temp);
      break;
   case ir_txl:
   case ir_txf:
   case ir_txs:
      ir->lod_info.lod->accept(this);
      ids.push(ir->lod_info.lod->ir_temp);
      break;
   case ir_txf_ms:
      ir->lod_info.sample_index->accept(this);
      ids.push(ir->lod_info.sample_index->ir_temp);
      break;
   case ir_txd:
      ir->lod_info.grad.dPdx->accept(this);
      ids.push(ir->lod_info.grad.dPdx->ir_temp);
      ir->lod_info.grad.dPdy->accept(this);
      ids.push(ir->lod_info.grad.dPdy->ir_temp);
      break;
   case ir_tg4:
      ir->lod_info.component->accept(this);
      ids.push(ir->lod_info.component->ir_temp);
      break;
   case ir_samples_identical:
      unreachable("ir_samples_identical was already handled");
   };

   unsigned int op_id;
   switch (ir->op) {
   default:
   case ir_tex: {
      op_id = ir->projector ? SpvOpImageSampleProjImplicitLod : SpvOpImageSampleImplicitLod;
      unsigned int type_id = visit_type(f, glsl_type::float_type);
      unsigned int result_id = f->id++;
      f->functions.push(op_id | ((3 + ids.count()) << SpvWordCountShift));
      f->functions.push(type_id);
      f->functions.push(result_id);
      for (unsigned int i = 0; i < ids.count(); ++i) {
         f->functions.push(ids_data[i]);
      }
      ir->ir_temp = result_id;

      const ir_dereference_variable* var = ir->sampler->as_dereference_variable();
      if (var && var->var->data.precision == GLSL_PRECISION_MEDIUM) {
         f->decorates.push(SpvOpDecorate | (3 << SpvWordCountShift));
         f->decorates.push(result_id);
         f->decorates.push(SpvDecorationRelaxedPrecision);
      }
      break;
   }
   case ir_txl:
      op_id = ir->projector ? SpvOpImageSampleProjExplicitLod : SpvOpImageSampleExplicitLod;
      break;
   case ir_txd:
      op_id = SpvOpImageGather;
      break;
   case ir_txf:
      op_id = SpvOpImageFetch;
      break;
   }
}

void ir_print_spirv_visitor::visit(ir_swizzle *ir)
{
   ir->val->accept(this);

   unsigned int type_id = visit_type(f, ir->type);
   unsigned int value_id = f->id++;
   unsigned int source_id = ir->val->ir_temp;
   f->functions.push(SpvOpVectorShuffle | ((5 + ir->mask.num_components) << SpvWordCountShift));
   f->functions.push(type_id);
   f->functions.push(value_id);
   f->functions.push(source_id);
   f->functions.push(source_id);
   if (ir->mask.num_components >= 1)
      f->functions.push(ir->mask.x);
   if (ir->mask.num_components >= 2)
      f->functions.push(ir->mask.y);
   if (ir->mask.num_components >= 3)
      f->functions.push(ir->mask.z);
   if (ir->mask.num_components >= 4)
      f->functions.push(ir->mask.w);
   ir->ir_temp = value_id;
}

void ir_print_spirv_visitor::visit(ir_dereference_variable *ir)
{
   ir_variable *var = ir->variable_referenced();
   unique_name(var);

   if (var->data.mode == ir_var_uniform || var->data.mode == ir_var_shader_in) {

      unsigned int load_type_id;

      if (var->type->is_sampler()) {

         unsigned int type_id = visit_type(f, glsl_type::float_type);
         unsigned int image_id = f->id++;
         f->types.push(SpvOpTypeImage | (9 << SpvWordCountShift));
         f->types.push(image_id);
         f->types.push(type_id);
         switch (var->type->sampler_dimensionality)
         {
            case GLSL_SAMPLER_DIM_1D:        f->types.push(SpvDim1D);          break;
            case GLSL_SAMPLER_DIM_2D:        f->types.push(SpvDim2D);          break;
            case GLSL_SAMPLER_DIM_3D:        f->types.push(SpvDim3D);          break;
            case GLSL_SAMPLER_DIM_CUBE:      f->types.push(SpvDimCube);        break;
            case GLSL_SAMPLER_DIM_RECT:      f->types.push(SpvDimRect);        break;
            case GLSL_SAMPLER_DIM_BUF:       f->types.push(SpvDimBuffer);      break;
            case GLSL_SAMPLER_DIM_EXTERNAL:  f->types.push(SpvDim1D);          break;// TODO
            case GLSL_SAMPLER_DIM_MS:        f->types.push(SpvDim1D);          break;// TODO
            case GLSL_SAMPLER_DIM_SUBPASS:   f->types.push(SpvDimSubpassData); break;
         }
         f->types.push(0u);
         f->types.push(0u);
         f->types.push(0u);
         f->types.push(1u);
         f->types.push(SpvImageFormatUnknown);

         unsigned int sampled_image_id = f->id++;
         f->types.push(SpvOpTypeSampledImage | (3 << SpvWordCountShift));
         f->types.push(sampled_image_id);
         f->types.push(image_id);

         unsigned int type_pointer_id = f->id++;
         f->types.push(SpvOpTypePointer | (4 << SpvWordCountShift));
         f->types.push(type_pointer_id);
         f->types.push(SpvStorageClassUniformConstant);
         f->types.push(sampled_image_id);

         f->types.push(SpvOpVariable | (4 << SpvWordCountShift));
         f->types.push(type_pointer_id);
         f->types.push(var->ir_temp);
         f->types.push(SpvStorageClassUniformConstant);

         load_type_id = type_pointer_id;
      } else {
         load_type_id = visit_type(f, ir->type);
      }

      if (var->data.mode == ir_var_uniform && var->type->is_sampler() == false) {

         unsigned int type_pointer_id = f->id++;
         unsigned int access_id = f->id++;
         unsigned int constant_id = f->id++;

         f->types.push(SpvOpTypePointer | (4 << SpvWordCountShift));
         f->types.push(type_pointer_id);
         f->types.push(SpvStorageClassUniform);
         f->types.push(load_type_id);

         unsigned int int_type_id = visit_type(f, glsl_type::int_type);
         f->types.push(SpvOpConstant | (4 << SpvWordCountShift));
         f->types.push(int_type_id);
         f->types.push(constant_id);
         f->types.push(var->ir_temp2);

         f->functions.push(SpvOpAccessChain | (5 << SpvWordCountShift));
         f->functions.push(type_pointer_id);
         f->functions.push(access_id);
         f->functions.push(f->uniform_id);
         f->functions.push(constant_id);

         var->ir_temp = access_id;
      }

      unsigned int value_id = f->id++;
      unsigned int pointer_id = var->ir_temp;
      f->functions.push(SpvOpLoad | (4 << SpvWordCountShift));
      f->functions.push(load_type_id);
      f->functions.push(value_id);
      f->functions.push(pointer_id);

      ir->ir_temp = value_id;
   } else if (var->data.mode == ir_var_auto || var->data.mode == ir_var_shader_out || var->data.mode == ir_var_temporary) {
      ir->ir_temp = var->ir_temp;
   }

   if (var->data.precision == GLSL_PRECISION_MEDIUM) {
      f->decorates.push(SpvOpDecorate | (3 << SpvWordCountShift));
      f->decorates.push(ir->ir_temp);
      f->decorates.push(SpvDecorationRelaxedPrecision);
   }
}

void ir_print_spirv_visitor::visit(ir_dereference_array *ir)
{
   ir->array->accept(this);
   unsigned int array_id = ir->array->ir_temp;

   ir->array_index->accept(this);
   unsigned int array_index_id = ir->array_index->ir_temp;

   unsigned int type_id = visit_type(f, ir->type);
   unsigned int return_id = f->id++;
   f->functions.push(SpvOpAccessChain | (5 << SpvWordCountShift));
   f->functions.push(type_id);
   f->functions.push(return_id);
   f->functions.push(array_id);
   f->functions.push(array_index_id);

   ir->ir_temp = return_id;
}

void ir_print_spirv_visitor::visit(ir_dereference_record *ir)
{
   //ir->record->accept(this);
   //fprintf(f, ".%s", ir->field);
}

void ir_print_spirv_visitor::visit(ir_assignment *ir)
{
   if (ir->condition)
      ir->condition->accept(this);

   ir->rhs->accept(this);

   ir->lhs->accept(this);

   if (ir->write_mask != ((1 << ir->lhs->type->components()) - 1)) {
      if (_mesa_bitcount(ir->write_mask) == 1 && ir->rhs->type->components() == 1) {
         unsigned int index = 0;
         if (ir->write_mask & 1)      index = 0;
         else if (ir->write_mask & 2) index = 1;
         else if (ir->write_mask & 4) index = 2;
         else if (ir->write_mask & 8) index = 3;

         ir_constant const_ir(index);
         const_ir.ir_temp = 0;
         visit(&const_ir);

         unsigned int type_id = visit_type(f, ir->rhs->type);
         unsigned int return_id = f->id++;
         f->functions.push(SpvOpAccessChain | (5 << SpvWordCountShift));
         f->functions.push(type_id);
         f->functions.push(return_id);
         f->functions.push(ir->lhs->ir_temp);
         f->functions.push(const_ir.ir_temp);

         f->functions.push(SpvOpStore | (3 << SpvWordCountShift));
         f->functions.push(return_id);
         f->functions.push(ir->rhs->ir_temp);
         ir->lhs->ir_temp = ir->rhs->ir_temp;
      }
      else {
         unsigned int type_id = visit_type(f, ir->lhs->type);
         unsigned int value_id = f->id++;
         unsigned int source_id = ir->rhs->ir_temp;
         f->functions.push(SpvOpVectorShuffle | ((5 + ir->lhs->type->components()) << SpvWordCountShift));
         f->functions.push(type_id);
         f->functions.push(value_id);
         f->functions.push(source_id);
         f->functions.push(ir->lhs->ir_temp ? ir->lhs->ir_temp : source_id);
         unsigned int component_index = 0;
         for (unsigned int i = 0; i < ir->lhs->type->components(); ++i) {
#if 1
            f->functions.push(ir->write_mask & (1 << i) ? component_index++ : ir->rhs->type->components() + i);
#else
            f->functions.push(ir->write_mask & (1 << i) ? component_index++ : 0xFFFFFFFF);
#endif
         }
         f->functions.push(SpvOpStore | (3 << SpvWordCountShift));
         f->functions.push(ir->lhs->ir_temp);
         f->functions.push(value_id);
         ir->lhs->ir_temp = value_id;
      }
   } else {
      f->functions.push(SpvOpStore | (3 << SpvWordCountShift));
      f->functions.push(ir->lhs->ir_temp);
      f->functions.push(ir->rhs->ir_temp);
      ir->lhs->ir_temp = ir->rhs->ir_temp;
   }
}

void ir_print_spirv_visitor::visit(ir_constant *ir)
{
   if (ir->type->is_array()) {
      for (unsigned i = 0; i < ir->type->length; i++)
         ir->get_array_element(i)->accept(this);
   } else if (ir->type->is_record()) {
      ir_constant *value = (ir_constant *) ir->components.get_head();
      for (unsigned i = 0; i < ir->type->length; i++) {
         value->accept(this);
         value = (ir_constant *) value->next;
      }
   } else {
      if (ir->type->components() == 1) {
         switch (ir->type->base_type) {
         case GLSL_TYPE_UINT:
            if (ir->value.u[0] <= 15)
               ir->ir_temp = f->const_int_id[ir->value.u[0]];
            break;
         case GLSL_TYPE_INT:
            if (ir->value.i[0] >= 0 && ir->value.i[0] <= 15)
               ir->ir_temp = f->const_int_id[ir->value.i[0]];
            break;
         case GLSL_TYPE_FLOAT:
            if (ir->value.f[0] >= 0.0f && ir->value.f[0] <= 15.0f && fmodf(ir->value.f[0], 1.0f) == 0.0f)
               ir->ir_temp = f->const_float_id[(int)ir->value.f[0]];
            break;
         }
      }
      if (ir->ir_temp)
         return;

      unsigned int temp[16];
      binary_buffer ids(temp, 16);
      for (unsigned i = 0; i < ir->type->components(); i++) {
         unsigned int type_id = visit_type(f, ir->type->get_base_type());
         unsigned int constant_id = f->id++;
         f->types.push(SpvOpConstant | (4 << SpvWordCountShift));
         f->types.push(type_id);
         f->types.push(constant_id);
         switch (ir->type->base_type) {
         case GLSL_TYPE_UINT:  f->types.push(ir->value.u[i]); break;
         case GLSL_TYPE_INT:   f->types.push(ir->value.i[i]); break;
         case GLSL_TYPE_FLOAT: f->types.push(*(int*)&ir->value.f[i]);  break;
         default:
            f->types.push(0u); 
            unreachable("Invalid constant type");
         }
         ids.push(constant_id);
      }
      unsigned int value_id = f->id++;
      unsigned int type_id = visit_type(f, ir->type);
      if (ids.count() == 1) {
         f->functions.push(SpvOpVariable | (4 << SpvWordCountShift));
         f->functions.push(type_id);
         f->functions.push(value_id);
         f->functions.push(SpvStorageClassFunction);

         f->functions.push(SpvOpStore | (3 << SpvWordCountShift));
         f->functions.push(value_id);
         f->functions.push(temp[0]);
      } else {
         f->types.push(SpvOpConstantComposite | ((3 + ids.count()) << SpvWordCountShift));
         f->types.push(type_id);
         f->types.push(value_id);
         for (unsigned i = 0; i < ids.count(); i++) {
            f->types.push(temp[i]);
         }
      }
      switch (ir->type->base_type) {
      default:
         break;
      case GLSL_TYPE_UINT:
      case GLSL_TYPE_INT:
         if (f->precision_int == GLSL_PRECISION_MEDIUM) {
            f->decorates.push(SpvOpDecorate | (3 << SpvWordCountShift));
            f->decorates.push(value_id);
            f->decorates.push(SpvDecorationRelaxedPrecision);
         }
         break;
      case GLSL_TYPE_FLOAT:
         if (f->precision_float == GLSL_PRECISION_MEDIUM) {
            f->decorates.push(SpvOpDecorate | (3 << SpvWordCountShift));
            f->decorates.push(value_id);
            f->decorates.push(SpvDecorationRelaxedPrecision);
         }
         break;
      }
      ir->ir_temp = value_id;

      if (ir->type->components() == 1) {
         switch (ir->type->base_type) {
         case GLSL_TYPE_UINT:
            if (ir->value.u[0] <= 15)
               f->const_int_id[ir->value.u[0]] = ir->ir_temp;
            break;
         case GLSL_TYPE_INT:
            if (ir->value.i[0] >= 0 && ir->value.i[0] <= 15)
               f->const_int_id[ir->value.i[0]] = ir->ir_temp;
            break;
         case GLSL_TYPE_FLOAT:
            if (ir->value.f[0] >= 0.0f && ir->value.f[0] <= 15.0f && fmodf(ir->value.f[0], 1.0f) == 0.0f)
               f->const_float_id[(int)ir->value.f[0]] = ir->ir_temp;
            break;
         }
      }
   }
}

void
ir_print_spirv_visitor::visit(ir_call *ir)
{
   //if (ir->return_deref) {
   //   ir->return_deref->accept(this);
   //   fprintf(f, " = ");
   //}
   //fprintf(f, "%s", ir->callee_name());
   //fprintf(f, "(");
   //foreach_in_list(ir_rvalue, param, &ir->actual_parameters) {
   //   if (param != ir->actual_parameters.head_sentinel.next)
   //      fprintf(f, ", ");
   //   param->accept(this);
   //}
   //fprintf(f, ")");
}

void
ir_print_spirv_visitor::visit(ir_return *ir)
{
   //ir_rvalue *const value = ir->get_value();
   //if (value) {
   //   fprintf(f, "return ");
   //   value->accept(this);
   //}
}

void
ir_print_spirv_visitor::visit(ir_discard *ir)
{
   if (ir->condition) {
      ir->condition->accept(this);
      unsigned int label_begin_id = f->id++;
      unsigned int label_end_id = f->id++;
      f->functions.push(SpvOpBranchConditional | (4 << SpvWordCountShift));
      f->functions.push(ir->condition->ir_temp);
      f->functions.push(label_begin_id);
      f->functions.push(label_end_id);

      f->functions.push(SpvOpLabel | (2 << SpvWordCountShift));
      f->functions.push(label_begin_id);

      f->functions.push(SpvOpKill | (1 << SpvWordCountShift));

      f->functions.push(SpvOpLabel | (2 << SpvWordCountShift));
      f->functions.push(label_end_id);
   } else {
      f->functions.push(SpvOpKill | (1 << SpvWordCountShift));
   }
}

void
ir_print_spirv_visitor::visit(ir_if *ir)
{
   ir->condition->accept(this);

   unsigned int label_then_id = f->id++;
   unsigned int label_else_id = f->id++;
   unsigned int label_end_id = label_else_id;
   if (ir->else_instructions.is_empty() == false) {
      label_end_id = f->id++;
   }

   f->functions.push(SpvOpBranchConditional | (4 << SpvWordCountShift));
   f->functions.push(ir->condition->ir_temp);
   f->functions.push(label_then_id);
   f->functions.push(label_else_id);

   f->functions.push(SpvOpLabel | (2 << SpvWordCountShift));
   f->functions.push(label_then_id);

   foreach_in_list(ir_instruction, inst, &ir->then_instructions) {
      inst->parent = ir;
      inst->accept(this);
   }

   if (ir->else_instructions.is_empty() == false) {

      f->functions.push(SpvOpBranch | (2 << SpvWordCountShift));
      f->functions.push(label_end_id);
      f->functions.push(SpvOpLabel | (2 << SpvWordCountShift));
      f->functions.push(label_else_id);

      foreach_in_list(ir_instruction, inst, &ir->else_instructions) {
         inst->parent = ir;
         inst->accept(this);
      }
   }

   f->functions.push(SpvOpBranch | (2 << SpvWordCountShift));
   f->functions.push(label_end_id);
   f->functions.push(SpvOpLabel | (2 << SpvWordCountShift));
   f->functions.push(label_end_id);
}

void
ir_print_spirv_visitor::visit(ir_loop *ir)
{
   unsigned int label_id = f->id++;

   f->functions.push(SpvOpBranch | (2 << SpvWordCountShift));
   f->functions.push(label_id);
   f->functions.push(SpvOpLabel | (2 << SpvWordCountShift));
   f->functions.push(label_id);

   unsigned int label_inner_id = f->id++;
   unsigned int label_outer_id = f->id++;

   f->functions.push(SpvOpLoopMerge | (4 << SpvWordCountShift));
   f->functions.push(label_outer_id);
   f->functions.push(label_inner_id);
   f->functions.push(SpvLoopControlMaskNone);

   f->functions.push(SpvOpBranch | (2 << SpvWordCountShift));
   f->functions.push(label_inner_id);
   f->functions.push(SpvOpLabel | (2 << SpvWordCountShift));
   f->functions.push(label_inner_id);

   ir->ir_temp = label_id;
   ir->ir_temp2 = label_outer_id;

   foreach_in_list(ir_instruction, inst, &ir->body_instructions) {
      inst->parent = ir;
      inst->accept(this);
   }

   f->functions.push(SpvOpBranch | (2 << SpvWordCountShift));
   f->functions.push(label_id);
   f->functions.push(SpvOpLabel | (2 << SpvWordCountShift));
   f->functions.push(label_outer_id);
}

void
ir_print_spirv_visitor::visit(ir_loop_jump *ir)
{
   const ir_loop *loop = NULL;
   ir_instruction *parent = (ir_instruction *)ir->parent;
   while (parent) {
      loop = parent->as_loop();
      if (loop)
         break;
      parent = (ir_instruction*)parent->parent;
   }
   if (loop == NULL)
      return;
   unsigned int label_id = f->id++;

   f->functions.push(SpvOpBranch | (2 << SpvWordCountShift));
   f->functions.push(ir->is_break() ? loop->ir_temp2 : loop->ir_temp);
   f->functions.push(SpvOpLabel | (2 << SpvWordCountShift));
   f->functions.push(label_id);
}

void
ir_print_spirv_visitor::visit(ir_emit_vertex *ir)
{
   //fprintf(f, "(emit-vertex ");
   //ir->stream->accept(this);
   //fprintf(f, ")\n");
}

void
ir_print_spirv_visitor::visit(ir_end_primitive *ir)
{
   //fprintf(f, "(end-primitive ");
   //ir->stream->accept(this);
   //fprintf(f, ")\n");
}

void
ir_print_spirv_visitor::visit(ir_barrier *)
{
   //fprintf(f, "(barrier)\n");
}
