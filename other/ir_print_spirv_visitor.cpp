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

static const unsigned int reflection_float_type[4][4] = {
   GL_FLOAT,         GL_FLOAT_VEC2,    GL_FLOAT_VEC3,    GL_FLOAT_VEC4,
   GL_FLOAT_VEC2,    GL_FLOAT_MAT2,    GL_FLOAT_MAT2x3,  GL_FLOAT_MAT2x4,
   GL_FLOAT_VEC3,    GL_FLOAT_MAT3x2,  GL_FLOAT_MAT3,    GL_FLOAT_MAT3x4,
   GL_FLOAT_VEC4,    GL_FLOAT_MAT4x2,  GL_FLOAT_MAT4x3,  GL_FLOAT_MAT4,
};

static const unsigned int reflection_int_type[4] = {
   GL_INT, GL_INT_VEC2, GL_INT_VEC3, GL_INT_VEC4,
};

static const unsigned int storage_mode[] = {
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

static const unsigned int stage_type[] = {
   SpvExecutionModelVertex,
   SpvExecutionModelTessellationControl,
   SpvExecutionModelTessellationEvaluation,
   SpvExecutionModelGeometry,
   SpvExecutionModelFragment,
   SpvExecutionModelGLCompute,
};

binary_buffer::binary_buffer()
{
   u_vector_init(&vector_buffer, sizeof(int), 1024);
}

binary_buffer::~binary_buffer()
{
   u_vector_finish(&vector_buffer);
}

void binary_buffer::push(unsigned short low, unsigned short high)
{
   int* buf = (int*)u_vector_add(&vector_buffer);
   (*buf) = (high << 16) | low;
}

void binary_buffer::push(unsigned int value)
{
   int* buf = (int*)u_vector_add(&vector_buffer);
   (*buf) = value;
}

void binary_buffer::push(const char* text)
{
   size_t len = strlen(text);
   while (len >= sizeof(int)) {
      unsigned int value = 0;
      memcpy(&value, text, sizeof(int));
      push(value);
      text += sizeof(int);
      len -= sizeof(int);
   }
   unsigned int value = 0;
   memcpy(&value, text, len);
   push(value);
}

unsigned int binary_buffer::count()
{
   return u_vector_length(&vector_buffer);
}

unsigned int* binary_buffer::data()
{
   return (unsigned int*)u_vector_tail(&vector_buffer);
}

unsigned int& binary_buffer::operator[] (size_t i)
{
   return data()[i];
}

spirv_buffer::spirv_buffer()
{
}

spirv_buffer::~spirv_buffer()
{
}

extern "C" {
void
_mesa_print_spirv(spirv_buffer *f, exec_list *instructions, gl_shader_stage stage, unsigned version, bool es, unsigned binding)
{
   f->id = 1;
   f->binding_id = binding;
   f->import_id = 0;
   f->uniform_struct_id = 0;
   f->uniform_id = 0;
   f->uniform_pointer_id = 0;
   f->uniform_offset = 0;
   f->function_id = 0;
   f->main_id = 0;
   f->gl_per_vertex_id = 0;
   f->void_id = 0;
   f->bool_id = 0;
   memset(f->float_id, 0, sizeof(f->float_id));
   memset(f->int_id, 0, sizeof(f->int_id));
   memset(f->const_float_id, 0, sizeof(f->const_float_id));
   memset(f->const_int_id, 0, sizeof(f->const_int_id));
   memset(f->sampler_id, 0, sizeof(f->sampler_id));
   memset(f->pointer_bool_id, 0, sizeof(f->pointer_bool_id));
   memset(f->pointer_float_id, 0, sizeof(f->pointer_float_id));
   memset(f->pointer_int_id, 0, sizeof(f->pointer_int_id));
   memset(f->pointer_sampler_id, 0, sizeof(f->pointer_sampler_id));
   f->shader_stage = stage;
   f->input_loc = 0;
   f->output_loc = 0;

   if (es) {
      if (stage == MESA_SHADER_FRAGMENT) {
         f->precision_float = GLSL_PRECISION_MEDIUM;
         f->precision_int = GLSL_PRECISION_MEDIUM;
      } else {
         f->precision_float = GLSL_PRECISION_HIGH;
         f->precision_int = GLSL_PRECISION_MEDIUM;
      }
   } else {
      f->precision_float = GLSL_PRECISION_NONE;
      f->precision_int = GLSL_PRECISION_NONE;
   }

   // ExtInstImport
   f->import_id = f->id++;
   f->extensions.push(SpvOpExtInstImport, 6);
   f->extensions.push(f->import_id);
   f->extensions.push("GLSL.std.450");

   // MemoryModel Logical GLSL450
   f->extensions.push(SpvOpMemoryModel, 3);
   f->extensions.push(SpvAddressingModelLogical);
   f->extensions.push(SpvMemoryModelGLSL450);

   // spirv visitor
   ir_print_spirv_visitor v(f);

   // collect type desclare
   foreach_in_list(ir_instruction, ir, instructions) {
      ir_variable* var = ir->as_variable();
      if (var) {
         v.visit_type(var->type);
      }
   }

   // collect uniform
   foreach_in_list(ir_instruction, ir, instructions) {
      ir_variable* var = ir->as_variable();
      if (var && var->data.mode == ir_var_uniform && var->type->is_sampler() == false) {
         var->accept(&v);
      }
   }

   unsigned int uniforms_count = f->uniforms.count();
   if (uniforms_count != 0) {
      f->types.push(SpvOpTypeStruct, uniforms_count + 2);
      f->types.push(f->uniform_struct_id);
      for (unsigned int i = 0; i < f->uniforms.count(); ++i) {
         f->types.push(f->uniforms[i]);
      }

      f->types.push(SpvOpTypePointer, 4);
      f->types.push(f->uniform_pointer_id);
      f->types.push(SpvStorageClassUniform);
      f->types.push(f->uniform_struct_id);

      f->types.push(SpvOpVariable, 4);
      f->types.push(f->uniform_pointer_id);
      f->types.push(f->uniform_id);
      f->types.push(SpvStorageClassUniform);
   }

   // collect non-uniform
   foreach_in_list(ir_instruction, ir, instructions) {
      ir_variable* var = ir->as_variable();
      if (var && (var->data.mode != ir_var_uniform || var->type->is_sampler() == true)) {
         var->accept(&v);
      }
   }

   foreach_in_list(ir_instruction, ir, instructions) {
      if (ir->as_variable() == NULL)
         ir->accept(&v);
   }

   // Header - Mesa-IR/SPIR-V Translator
   unsigned int bound_id = f->id++;
   f->push(SpvMagicNumber);
   f->push(0x00010000);
   f->push(0x00100000);
   f->push(bound_id);
   f->push(0u);

   // Capability
   f->push(SpvOpCapability, 2);
   f->push(SpvCapabilityShader);

   for (unsigned int i = 0; i < f->extensions.count(); ++i) {
      f->push(f->extensions[i]);
   }

   // EntryPoint Fragment 4  "main" 20 22 37 43 46 49
   f->push(SpvOpEntryPoint, f->inouts.count() + 5);
   f->push(stage_type[stage]);
   f->push(f->main_id);
   f->push("main");
   for (unsigned int i = 0; i < f->inouts.count(); ++i) {
      f->push(f->inouts[i]);
   }

   // ExecutionMode 4 OriginUpperLeft
   if (stage == MESA_SHADER_FRAGMENT) {
      f->push(SpvOpExecutionMode, 3);
      f->push(f->main_id);
      f->push(SpvExecutionModeOriginUpperLeft);
   }

   // Source ESSL 300
   f->push(SpvOpSource, 3);
   f->push(es ? SpvSourceLanguageESSL : SpvSourceLanguageGLSL);
   f->push(version);

   for (unsigned int i = 0; i < f->names.count(); ++i) {
      f->push(f->names[i]);
   }

   for (unsigned int i = 0; i < f->decorates.count(); ++i) {
      f->push(f->decorates[i]);
   }

   for (unsigned int i = 0; i < f->types.count(); ++i) {
      f->push(f->types[i]);
   }

   // gl_PerVertex
   unsigned int per_vertices_count = f->per_vertices.count();
   if (per_vertices_count != 0) {
      f->push(SpvOpTypeStruct, per_vertices_count + 2);
      f->push(f->gl_per_vertex_id);
      for (unsigned int i = 0; i < f->per_vertices.count(); ++i) {
         f->push(f->per_vertices[i]);
      }
   }

   // Built-in
   for (unsigned int i = 0; i < f->builtins.count(); ++i) {
      f->push(f->builtins[i]);
   }

   for (unsigned int i = 0; i < f->functions.count(); ++i) {
      f->push(f->functions[i]);
   }
}

} /* extern "C" */

ir_print_spirv_visitor::ir_print_spirv_visitor(spirv_buffer *f)
   : f(f)
{
   indentation = 0;
   unique_name_number = 0;
   printable_names =
      _mesa_hash_table_create(NULL, _mesa_hash_pointer, _mesa_key_pointer_equal);
   symbols = _mesa_symbol_table_ctor();
   mem_ctx = ralloc_context(NULL);
}

ir_print_spirv_visitor::~ir_print_spirv_visitor()
{
   _mesa_hash_table_destroy(printable_names, NULL);
   _mesa_symbol_table_dtor(symbols);
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
      return (unsigned int)(intptr_t)entry->data;
   }

   /* If there's no conflict, just use the original name */
   const char* name = NULL;
   if (_mesa_symbol_table_find_symbol(this->symbols, var->name) == NULL) {
      name = var->name;
   } else {
      name = ralloc_asprintf(this->mem_ctx, "%s_%u", var->name, ++unique_name_number);
   }

   unsigned int name_id = f->id++;
   unsigned int len = (int)strlen(name);
   unsigned int count = (len + sizeof(int)) / sizeof(int);
   f->names.push(SpvOpName, count + 2);
   f->names.push(name_id);
   f->names.push(name);
   var->ir_pointer = name_id;

   _mesa_hash_table_insert(this->printable_names, var, (void *)(intptr_t) name_id);
   _mesa_symbol_table_add_symbol(this->symbols, name, var);

   return name_id;
}

bool ir_print_spirv_visitor::is_unique_name_exist(ir_variable *var)
{
   /* var->name can be NULL in function prototypes when a type is given for a
   * parameter but no name is given.  In that case, just return an empty
   * string.  Don't worry about tracking the generated name in the printable
   * names hash because this is the only scope where it can ever appear.
   */
   if (var->name == NULL) {
      return false;
   }

   /* Do we already have a name for this variable? */
   struct hash_entry * entry =
      _mesa_hash_table_search(this->printable_names, var);

   if (entry != NULL) {
      return true;
   }

   return (_mesa_symbol_table_find_symbol(this->symbols, var->name) != NULL);
}

void ir_print_spirv_visitor::visit(ir_rvalue *)
{
   //fprintf(f, "error");
}

unsigned int ir_print_spirv_visitor::visit_type(const struct glsl_type *type)
{
   if (type->is_sampler()) {
      if (f->sampler_id[type->sampler_dimensionality] == 0) {
         unsigned int type_id = visit_type(glsl_type::float_type);
         unsigned int image_id = f->id++;
         f->types.push(SpvOpTypeImage, 9);
         f->types.push(image_id);
         f->types.push(type_id);
         switch (type->sampler_dimensionality) {
            case GLSL_SAMPLER_DIM_1D:        f->types.push(SpvDim1D);            break;
            case GLSL_SAMPLER_DIM_2D:        f->types.push(SpvDim2D);            break;
            case GLSL_SAMPLER_DIM_3D:        f->types.push(SpvDim3D);            break;
            case GLSL_SAMPLER_DIM_CUBE:      f->types.push(SpvDimCube);          break;
            case GLSL_SAMPLER_DIM_RECT:      f->types.push(SpvDimRect);          break;
            case GLSL_SAMPLER_DIM_BUF:       f->types.push(SpvDimBuffer);        break;
            case GLSL_SAMPLER_DIM_EXTERNAL:  f->types.push(SpvDim1D);            break;// TODO
            case GLSL_SAMPLER_DIM_MS:        f->types.push(SpvDim1D);            break;// TODO
            case GLSL_SAMPLER_DIM_SUBPASS:   f->types.push(SpvDimSubpassData);   break;
         }
         f->types.push(0u);
         f->types.push(0u);
         f->types.push(0u);
         f->types.push(1u);
         f->types.push(SpvImageFormatUnknown);

         unsigned int sampled_image_id = f->id++;
         f->types.push(SpvOpTypeSampledImage, 3);
         f->types.push(sampled_image_id);
         f->types.push(image_id);

         f->sampler_id[type->sampler_dimensionality] = sampled_image_id;
      }
      return f->sampler_id[type->sampler_dimensionality];
   } else if (type->is_array()) {

      ir_constant ir_array_size(type->array_size());
      ir_array_size.ir_value = 0;
      visit(&ir_array_size);

      unsigned int base_type_id = visit_type(type->fields.array);
      unsigned int vector_id = f->id++;
      f->types.push(SpvOpTypeArray, 4);
      f->types.push(vector_id);
      f->types.push(base_type_id);
      f->types.push(ir_array_size.ir_value);

      f->decorates.push(SpvOpDecorate, 4);
      f->decorates.push(vector_id);
      f->decorates.push(SpvDecorationArrayStride);
      f->decorates.push(type->fields.array->std430_array_stride(false));

      return vector_id;
   } else if (type->is_boolean()) {
      if (f->bool_id == 0) {
         f->bool_id = f->id++;
         f->types.push(SpvOpTypeBool, 2);
         f->types.push(f->bool_id);
      }
      return f->bool_id;
   } else if (type->is_void()) {
      if (f->void_id == 0) {
         f->void_id = f->id++;
         f->types.push(SpvOpTypeVoid, 2);
         f->types.push(f->void_id);
      }
      return f->void_id;
   }

   unsigned int vector_id;
   unsigned int* ids;
   if (type->is_float()) {
      ids = f->float_id;
   } else if (type->is_integer()) {
      ids = f->int_id;
   } else {
      return 0;
   }

   unsigned int offset = (type->vector_elements - 1) + (type->matrix_columns - 1) * 4;
   if (ids[0] == 0) {
      ids[0] = f->id++;
      if (type->is_float()) {
         f->types.push(SpvOpTypeFloat, 3);
         f->types.push(ids[0]);
         f->types.push(32u);
      } else if (type->is_integer()) {
         f->types.push(SpvOpTypeInt, 4);
         f->types.push(ids[0]);
         f->types.push(32u);
         f->types.push(1u);
      }
   }
   unsigned int component = type->vector_elements;
   if (component > 1 && ids[component - 1] == 0) {
      ids[component - 1] = f->id++;
      f->types.push(SpvOpTypeVector, 4);
      f->types.push(ids[component - 1]);
      f->types.push(ids[0]);
      f->types.push(type->vector_elements);
   }
   unsigned int column = type->matrix_columns;
   if (column > 4) {
      vector_id = f->id++;
      f->types.push(SpvOpTypeMatrix, 4);
      f->types.push(vector_id);
      f->types.push(ids[component - 1]);
      f->types.push(type->matrix_columns);
   } else if (column > 1 && ids[offset] == 0) {
      vector_id = ids[offset] = f->id++;
      f->types.push(SpvOpTypeMatrix, 4);
      f->types.push(ids[offset]);
      f->types.push(ids[component - 1]);
      f->types.push(type->matrix_columns);
   } else {
      vector_id = ids[offset];
   }

   return vector_id;
}

// 0 not_exist, 1 exist, 2 no defined
char ir_print_spirv_visitor::check_point_to_type(const struct glsl_type *type, unsigned int point_to)
{
   unsigned int* ids;
   if (type->is_array()) {
      unsigned int base_type_id = visit_type(type->fields.array);
      unsigned int constant_id = 0;

      if (type->array_size() < 16) {
         constant_id = f->const_int_id[type->array_size()];
      }
      return (constant_id == point_to) ? 1 : (constant_id == 0) ? 2 : 0;
   }
   if (type->is_float()) {
      ids = f->float_id;
   } else if (type->is_integer()) {
      ids = f->int_id;
   } else if (type->is_boolean()) {
      return (f->bool_id == point_to) ? 1 : (f->bool_id == 0) ? 2 : 0;
   } else {
      return false;
   }

   unsigned int offset = (type->vector_elements - 1) + (type->matrix_columns - 1) * 4;

   return (ids[offset] == point_to) ? 1 : (ids[offset] == 0) ? 2 : 0;
}

unsigned int ir_print_spirv_visitor::visit_type_pointer(const struct glsl_type *type, unsigned int mode, unsigned int point_to)
{
   if (mode >= ir_var_mode_count) {
      return 0;
   }

   if (type->is_sampler()) {
      if (f->pointer_sampler_id[type->sampler_dimensionality] == 0) {
         f->pointer_sampler_id[type->sampler_dimensionality] = f->id++;
         f->types.push(SpvOpTypePointer, 4);
         f->types.push(f->pointer_sampler_id[type->sampler_dimensionality]);
         f->types.push(SpvStorageClassUniformConstant);
         f->types.push(point_to);
      }
      return f->pointer_sampler_id[type->sampler_dimensionality];
   } else if (type->is_array()) {
      return visit_type_pointer(type->fields.array, mode, point_to);
   } else if (type->is_boolean()) {
      if (f->pointer_bool_id[mode] == 0) {
         f->pointer_bool_id[mode] = f->id++;
         f->types.push(SpvOpTypePointer, 4);
         f->types.push(f->pointer_bool_id[mode]);
         f->types.push(storage_mode[mode]);
         f->types.push(point_to);
      }
      return f->pointer_bool_id[mode];
   }

   unsigned int vector_id;
   unsigned int* ids;
   if (type->is_float()) {
      ids = f->pointer_float_id;
   } else if (type->is_integer()) {
      ids = f->pointer_int_id;
   } else {
      return 0;
   }

   char is_type_exist = check_point_to_type(type, point_to);

   unsigned int offset = (type->vector_elements - 1) + (type->matrix_columns - 1) * 4;
   offset += (mode * 16);
   if ((ids[offset] == 0) || (is_type_exist != 1)) {
      vector_id = f->id++;
      if (is_type_exist == 1) {
         ids[offset] = vector_id;
      }
      f->types.push(SpvOpTypePointer, 4);
      f->types.push(vector_id);
      f->types.push(storage_mode[mode]);
      f->types.push(point_to);
   } else {
      vector_id = ids[offset];
   }
   return vector_id;
}

void ir_print_spirv_visitor::visit_value(ir_rvalue *ir)
{
   if (ir->ir_value == 0) {
      if (ir->ir_pointer == 0 && ir->ir_uniform) {
         ir_constant ir_uniform(ir->ir_uniform - 1);
         ir_uniform.ir_value = 0;
         visit(&ir_uniform);

         unsigned int uniform_type = visit_type(ir->type);
         unsigned int type_pointer_id = visit_type_pointer(ir->type, ir_var_uniform, uniform_type);
         unsigned int pointer_id = f->id++;

         f->functions.push(SpvOpAccessChain, 5);
         f->functions.push(type_pointer_id);
         f->functions.push(pointer_id);
         f->functions.push(f->uniform_id);
         f->functions.push(ir_uniform.ir_value);

         ir->ir_pointer = pointer_id;
      }
      if (ir->ir_pointer != 0) {
         unsigned int type_id = visit_type(ir->type);
         unsigned int value_id = f->id++;
         f->functions.push(SpvOpLoad, 4);
         f->functions.push(type_id);
         f->functions.push(value_id);
         f->functions.push(ir->ir_pointer);
         ir->ir_value = value_id;
         visit_precision(ir->ir_value, ir->type->base_type, GLSL_PRECISION_NONE);
      }
   }
}

void ir_print_spirv_visitor::visit_precision(unsigned int id, unsigned int type, unsigned int precision)
{
   switch (type) {
   default:
      break;
   case GLSL_TYPE_UINT:
   case GLSL_TYPE_INT:
      if (precision == GLSL_PRECISION_MEDIUM || f->precision_int == GLSL_PRECISION_MEDIUM) {
         f->decorates.push(SpvOpDecorate, 3);
         f->decorates.push(id);
         f->decorates.push(SpvDecorationRelaxedPrecision);
      }
      break;
   case GLSL_TYPE_FLOAT:
      if (precision == GLSL_PRECISION_MEDIUM || f->precision_float == GLSL_PRECISION_MEDIUM) {
         f->decorates.push(SpvOpDecorate, 3);
         f->decorates.push(id);
         f->decorates.push(SpvDecorationRelaxedPrecision);
      }
      break;
   }
}

void ir_print_spirv_visitor::visit(ir_variable *ir)
{
   if (is_gl_identifier(ir->name))
      return;

   unsigned int type_id = visit_type(ir->type);

   if (ir->data.mode == ir_var_uniform) {

      if (ir->type->is_sampler()) {
          // move to visit_sampler_type
      } else {

         if (f->uniform_struct_id == 0) {

            unsigned int binding_id = f->binding_id++;
            char block_name[64] = {};
            snprintf(block_name, sizeof(block_name), "Global%d", binding_id);

            f->uniform_struct_id = f->id++;
            f->uniform_pointer_id = f->id++;
            f->uniform_id = f->id++;

            unsigned int len = (int)strlen(block_name);
            unsigned int count = (len + sizeof(int)) / sizeof(int);
            f->names.push(SpvOpName, count + 2);
            f->names.push(f->uniform_struct_id);
            f->names.push(block_name);

            unsigned int empty_len = (int)strlen("");
            unsigned int empty_count = (empty_len + sizeof(int)) / sizeof(int);
            f->names.push(SpvOpName, empty_count + 2);
            f->names.push(f->uniform_id);
            f->names.push("");

            f->decorates.push(SpvOpDecorate, 3);
            f->decorates.push(f->uniform_struct_id);
            f->decorates.push(SpvDecorationBlock);

            f->decorates.push(SpvOpDecorate, 4);
            f->decorates.push(f->uniform_id);
            f->decorates.push(SpvDecorationDescriptorSet);
            f->decorates.push(0u);

            f->decorates.push(SpvOpDecorate, 4);
            f->decorates.push(f->uniform_id);
            f->decorates.push(SpvDecorationBinding);
            f->decorates.push(binding_id);
         }

         unsigned int len = (int)strlen(ir->name);
         unsigned int count = (len + sizeof(int)) / sizeof(int);
         f->names.push(SpvOpMemberName, count + 3);
         f->names.push(f->uniform_struct_id);
         f->names.push(f->uniforms.count());
         f->names.push(ir->name);

         if (ir->type->is_matrix()) {
            f->decorates.push(SpvOpMemberDecorate, 4);
            f->decorates.push(f->uniform_struct_id);
            f->decorates.push(f->uniforms.count());
            f->decorates.push(SpvDecorationColMajor);
         }

         unsigned int base_alignment = ir->type->std430_base_alignment(false);
         unsigned int current_size = ir->type->std430_size(false);
         f->uniform_offset = (f->uniform_offset + base_alignment - 1) & ~(base_alignment - 1);
         f->decorates.push(SpvOpMemberDecorate, 5);
         f->decorates.push(f->uniform_struct_id);
         f->decorates.push(f->uniforms.count());
         f->decorates.push(SpvDecorationOffset);
         f->decorates.push(f->uniform_offset);

         if (ir->type->is_matrix()) {
            f->decorates.push(SpvOpMemberDecorate, 5);
            f->decorates.push(f->uniform_struct_id);
            f->decorates.push(f->uniforms.count());
            f->decorates.push(SpvDecorationMatrixStride);
            f->decorates.push(ir->type->vector_elements * 4);
         }

         f->reflections.push(GL_UNIFORM);
         const glsl_type* base_type = ir->type->is_array() ? ir->type->fields.array : ir->type;
         if (base_type->is_float()) {
            f->reflections.push(reflection_float_type[base_type->vector_elements - 1][base_type->matrix_columns - 1]);
         } else {
            f->reflections.push(reflection_int_type[base_type->vector_elements - 1]);
         }
         f->reflections.push(f->uniform_offset);
         f->reflections.push(ir->type->is_array() ? ir->type->fields.array->components() : 1u);
         f->reflections.push(0u);
         f->reflections.push(((int)strlen(ir->name) + sizeof(int)) / sizeof(int));
         f->reflections.push(ir->name);

         ir->ir_uniform = f->uniforms.count();
         f->uniforms.push(type_id);
         f->uniform_offset += current_size;
      }

   } else {

      unsigned int pointer_id = visit_type_pointer(ir->type, ir->data.mode, type_id);
      unsigned int name_id = unique_name(ir);

      if (ir->data.mode == ir_var_auto || ir->data.mode == ir_var_temporary) {
         f->functions.push(SpvOpVariable, 4);
         f->functions.push(pointer_id);
         f->functions.push(name_id);
         f->functions.push(storage_mode[ir->data.mode]);
         visit_precision(name_id, ir->type->base_type, ir->data.precision);
      } else {
         f->types.push(SpvOpVariable, 4);
         f->types.push(pointer_id);
         f->types.push(name_id);
         f->types.push(storage_mode[ir->data.mode]);
      }

      if (ir->data.mode == ir_var_shader_in || ir->data.mode == ir_var_shader_out) {
         f->inouts.push(name_id);

         unsigned int loc_id;
         if (ir->data.explicit_location) {
            switch (f->shader_stage) {
            case MESA_SHADER_VERTEX:
               loc_id = (ir->data.mode == ir_var_shader_in)
                  ? (ir->data.location - VERT_ATTRIB_GENERIC0)
                  : (ir->data.location - VARYING_SLOT_VAR0);
               break;

            case MESA_SHADER_FRAGMENT:
               loc_id = (ir->data.mode == ir_var_shader_out)
                  ? (ir->data.location - FRAG_RESULT_DATA0)
                  : (ir->data.location - VARYING_SLOT_VAR0);
               break;

            default:
               unreachable("Unexpected shader type");
               break;
            }
         }
         else {
            loc_id = ir->data.mode == ir_var_shader_in ? f->input_loc++ : f->output_loc++;
         }

         f->decorates.push(SpvOpDecorate, 4);
         f->decorates.push(name_id);
         f->decorates.push(SpvDecorationLocation);
         f->decorates.push(loc_id);

         if (f->shader_stage == MESA_SHADER_VERTEX && ir->data.mode == ir_var_shader_in) {
            f->reflections.push(GL_PROGRAM_INPUT);
            const glsl_type* base_type = ir->type->is_array() ? ir->type->fields.array : ir->type;
            if (base_type->is_float()) {
               f->reflections.push(reflection_float_type[base_type->vector_elements - 1][base_type->matrix_columns - 1]);
            } else {
               f->reflections.push(reflection_int_type[base_type->vector_elements - 1]);
            }
            unsigned int current_size = ir->type->std430_size(false);
            f->reflections.push(0u);
            f->reflections.push(current_size);
            f->reflections.push(loc_id);
            f->reflections.push(((int)strlen(ir->name) + sizeof(int)) / sizeof(int));
            f->reflections.push(ir->name);
         }
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
         f->types.push(SpvOpTypeVoid, 2);
         f->types.push(f->void_id);
      }
      type_id = f->void_id;
   } else {
      return;
   }

   // TypeFunction
   unsigned int function_id = f->id++;
   f->types.push(SpvOpTypeFunction, 3);
   f->types.push(function_id);
   f->types.push(type_id);

   // TypeName
   unsigned int function_name_id = 0;
   if (stricmp(ir->function_name(), "main") == 0) {
      function_name_id = f->main_id = f->id++;
   } else {
      function_name_id = f->id++;
   }
   unsigned int len = (int)strlen(ir->function_name());
   unsigned int count = (len + sizeof(int)) / sizeof(int);
   f->names.push(SpvOpName, count + 2);
   f->names.push(function_name_id);
   f->names.push(ir->function_name());
   f->functions.push(SpvOpFunction, 5);
   f->functions.push(type_id);
   f->functions.push(function_name_id);
   f->functions.push(SpvFunctionControlMaskNone);
   f->functions.push(function_id);

   // Label
   unsigned int label_id = f->id++;
   f->functions.push(SpvOpLabel, 2);
   f->functions.push(label_id);

   foreach_in_list(ir_variable, inst, &ir->parameters) {
      inst->accept(this);
   }

   foreach_in_list(ir_instruction, inst, &ir->body) {
      if (inst->as_variable()) {
         inst->accept(this);
      }
   }

   foreach_in_list(ir_instruction, inst, &ir->body) {
      if (inst->as_variable() == NULL) {
         inst->accept(this);
      }
   }

   // Return
   f->functions.push(SpvOpReturn, 1);

   // FunctionEnd
   f->functions.push(SpvOpFunctionEnd, 1);
}

void ir_print_spirv_visitor::visit(ir_function *ir)
{
   foreach_in_list(ir_function_signature, sig, &ir->signatures) {
      sig->accept(this);
   }
}

void ir_print_spirv_visitor::visit(ir_expression *ir)
{
   unsigned int operands[4] = {};

   for (unsigned int i = 0; i < ir->get_num_operands(); ++i) {
      if (ir->operands[i] == NULL)
         return;
      ir->operands[i]->accept(this);
      visit_value(ir->operands[i]);
      operands[i] = ir->operands[i]->ir_value;
   }

   unsigned int type_id = visit_type(ir->type);
   bool float_type;
   bool signed_type;
   switch (ir->type->base_type)
   {
   default:
   case GLSL_TYPE_FLOAT:
   case GLSL_TYPE_DOUBLE:
      float_type = true;
      signed_type = true;
      break;
   case GLSL_TYPE_INT:
   case GLSL_TYPE_INT64:
      float_type = false;
      signed_type = true;
      break;
   case GLSL_TYPE_UINT:
   case GLSL_TYPE_UINT64:
      float_type = false;
      signed_type = false;
      break;
   }

   if (ir->operation == ir_unop_saturate) {
      if (ir->get_num_operands() != 1)
         return;

      ir_constant zero_ir(0.0f);
      ir_constant one_ir(1.0f);
      zero_ir.ir_value = 0;
      one_ir.ir_value = 0;
      visit(&zero_ir);
      visit(&one_ir);

      unsigned int value_id = f->id++;
      f->functions.push(SpvOpExtInst, 8);
      f->functions.push(type_id);
      f->functions.push(value_id);
      f->functions.push(f->import_id);
      f->functions.push(float_type ? GLSLstd450FClamp : signed_type ? GLSLstd450SClamp : GLSLstd450UClamp);
      f->functions.push(operands[0]);
      f->functions.push(zero_ir.ir_value);
      f->functions.push(one_ir.ir_value);
      ir->ir_value = value_id;
   } else if (ir->operation == ir_binop_mul) {
      if (ir->get_num_operands() != 2)
         return;
      unsigned int value_id = f->id++;
      if (ir->operands[0]->type->is_scalar()) {
         if (ir->operands[1]->type->is_scalar()) {
            f->functions.push(float_type ? SpvOpFMul : SpvOpIMul, 5);
         } else if (ir->operands[1]->type->is_vector()) {
            f->functions.push(SpvOpVectorTimesScalar, 5);
            operands[0] = ir->operands[1]->ir_value;
            operands[1] = ir->operands[0]->ir_value;
         } else if (ir->operands[1]->type->is_matrix()) {
            f->functions.push(SpvOpMatrixTimesScalar, 5);
            operands[0] = ir->operands[1]->ir_value;
            operands[1] = ir->operands[0]->ir_value;
         } else {
            unreachable("unknown multiply operation");
         }
      } else if (ir->operands[0]->type->is_vector()) {
         if (ir->operands[1]->type->is_scalar()) {
            f->functions.push(SpvOpVectorTimesScalar, 5);
         } else if (ir->operands[1]->type->is_vector()) {
            f->functions.push(float_type ? SpvOpFMul : SpvOpIMul, 5);
         } else if (ir->operands[1]->type->is_matrix()) {
            f->functions.push(SpvOpVectorTimesMatrix, 5);
         } else {
            unreachable("unknown multiply operation");
         }
      } else if (ir->operands[0]->type->is_matrix()) {
         if (ir->operands[1]->type->is_scalar()) {
            f->functions.push(SpvOpMatrixTimesScalar, 5);
         } else if (ir->operands[1]->type->is_vector()) {
            f->functions.push(SpvOpMatrixTimesVector, 5);
         } else if (ir->operands[1]->type->is_matrix()) {
            f->functions.push(SpvOpMatrixTimesMatrix, 5);
         } else {
            unreachable("unknown multiply operation");
         }
      } else {
         unreachable("unknown multiply operation");
      }
      f->functions.push(type_id);
      f->functions.push(value_id);
      f->functions.push(operands[0]);
      f->functions.push(operands[1]);
      ir->ir_value = value_id;
   } else if (ir->operation >= ir_unop_bit_not && ir->operation <= ir_unop_vote_eq) {
      if (ir->get_num_operands() != 1)
         return;

      unsigned int value_id = f->id++;
      switch (ir->operation) {
      default:
         unreachable("unknown operation");
      case ir_unop_neg:
         f->functions.push(float_type ? SpvOpFNegate : SpvOpSNegate, 4);
         f->functions.push(type_id);
         f->functions.push(value_id);
         break;
      case ir_unop_rcp: {
         ir_constant ir(1.0f);
         ir.ir_value = 0;
         visit(&ir);

         f->functions.push(float_type ? SpvOpFDiv : signed_type ? SpvOpSDiv : SpvOpUDiv, 5);
         f->functions.push(type_id);
         f->functions.push(value_id);
         f->functions.push(ir.ir_value);
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
         f->functions.push(SpvOpExtInst, 6);
         f->functions.push(type_id);
         f->functions.push(value_id);
         f->functions.push(f->import_id);
         switch (ir->operation) {
         default:
         case ir_unop_abs:       f->functions.push(float_type ? GLSLstd450FAbs  : GLSLstd450SAbs);    break;
         case ir_unop_sign:      f->functions.push(float_type ? GLSLstd450FSign : GLSLstd450SSign);   break;
         case ir_unop_rsq:       f->functions.push(GLSLstd450InverseSqrt);                            break;
         case ir_unop_sqrt:      f->functions.push(GLSLstd450Sqrt);                                   break;
         case ir_unop_normalize: f->functions.push(GLSLstd450Normalize);                              break;
         case ir_unop_exp:       f->functions.push(GLSLstd450Exp);                                    break;
         case ir_unop_log:       f->functions.push(GLSLstd450Log);                                    break;
         case ir_unop_exp2:      f->functions.push(GLSLstd450Exp2);                                   break;
         case ir_unop_log2:      f->functions.push(GLSLstd450Log2);                                   break;
         case ir_unop_trunc:     f->functions.push(GLSLstd450Trunc);                                  break;
         case ir_unop_ceil:      f->functions.push(GLSLstd450Ceil);                                   break;
         case ir_unop_floor:     f->functions.push(GLSLstd450Floor);                                  break;
         case ir_unop_fract:     f->functions.push(GLSLstd450Fract);                                  break;
         case ir_unop_round_even:f->functions.push(GLSLstd450RoundEven);                              break;
         case ir_unop_sin:       f->functions.push(GLSLstd450Sin);                                    break;
         case ir_unop_cos:       f->functions.push(GLSLstd450Cos);                                    break;
         }
         break;
      case ir_unop_f2i:
      case ir_unop_f2u:
      case ir_unop_i2f:
      case ir_unop_u2f:
      case ir_unop_i2u:
      case ir_unop_u2i:
         switch (ir->operation) {
         default:
         case ir_unop_f2i:   f->functions.push(SpvOpConvertFToS, 4); break;
         case ir_unop_f2u:   f->functions.push(SpvOpConvertFToU, 4); break;
         case ir_unop_i2f:   f->functions.push(SpvOpConvertSToF, 4); break;
         case ir_unop_u2f:   f->functions.push(SpvOpConvertUToF, 4); break;
         case ir_unop_i2u:   f->functions.push(SpvOpUConvert, 4);    break;
         case ir_unop_u2i:   f->functions.push(SpvOpSConvert, 4);    break;
         }
         f->functions.push(type_id);
         f->functions.push(value_id);
         break;
      }
      f->functions.push(operands[0]);
      ir->ir_value = value_id;
   } else if (ir->operation >= ir_binop_add && ir->operation <= ir_binop_interpolate_at_sample) {
      if (ir->get_num_operands() != 2)
         return;

      unsigned int value_id = f->id++;
      switch (ir->operation) {
      default:
         unreachable("unknown operation");
      case ir_binop_add:
      case ir_binop_sub:
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
         case ir_binop_add:     f->functions.push(float_type ? SpvOpFAdd                 : SpvOpIAdd, 5);                                                      break;
         case ir_binop_sub:     f->functions.push(float_type ? SpvOpFSub                 : SpvOpISub, 5);                                                      break;
         case ir_binop_div:     f->functions.push(float_type ? SpvOpFDiv                 : signed_type ? SpvOpSDiv              : SpvOpUDiv, 5);               break;
         case ir_binop_mod:     f->functions.push(float_type ? SpvOpFMod                 : signed_type ? SpvOpSMod              : SpvOpUMod, 5);               break;
         case ir_binop_less:    f->functions.push(float_type ? SpvOpFOrdLessThan         : signed_type ? SpvOpSLessThan         : SpvOpULessThan, 5);          break;
         case ir_binop_greater: f->functions.push(float_type ? SpvOpFOrdGreaterThan      : signed_type ? SpvOpSGreaterThan      : SpvOpUGreaterThan, 5);       break;
         case ir_binop_lequal:  f->functions.push(float_type ? SpvOpFOrdLessThanEqual    : signed_type ? SpvOpSLessThanEqual    : SpvOpULessThanEqual, 5);     break;
         case ir_binop_gequal:  f->functions.push(float_type ? SpvOpFOrdGreaterThanEqual : signed_type ? SpvOpSGreaterThanEqual : SpvOpUGreaterThanEqual, 5);  break;
         case ir_binop_equal:   f->functions.push(float_type ? SpvOpFOrdEqual            : SpvOpIEqual, 5);                                                    break;
         case ir_binop_nequal:  f->functions.push(float_type ? SpvOpFOrdNotEqual         : SpvOpINotEqual, 5);                                                 break;
         case ir_binop_dot:     f->functions.push(SpvOpDot, 5);                                                                                                break;
         }
         f->functions.push(type_id);
         f->functions.push(value_id);
         break;
      case ir_binop_min:
      case ir_binop_max:
      case ir_binop_pow:
      case ir_binop_ldexp:
         f->functions.push(SpvOpExtInst, 7);
         f->functions.push(type_id);
         f->functions.push(value_id);
         f->functions.push(f->import_id);
         switch (ir->operation) {
         default:
         case ir_binop_min:      f->functions.push(float_type ? GLSLstd450FMin : signed_type ? GLSLstd450SMin : GLSLstd450UMin); break;
         case ir_binop_max:      f->functions.push(float_type ? GLSLstd450FMax : signed_type ? GLSLstd450SMax : GLSLstd450UMax); break;
         case ir_binop_pow:      f->functions.push(GLSLstd450Pow);                                                               break;
         case ir_binop_ldexp:    f->functions.push(GLSLstd450Ldexp);                                                             break;
         }
         break;
      }
      f->functions.push(operands[0]);
      f->functions.push(operands[1]);
      ir->ir_value = value_id;
   } else if (ir->operation >= ir_triop_fma && ir->operation <= ir_triop_vector_insert) {
      if (ir->get_num_operands() != 3)
         return;

      for (unsigned int i = 0; i < 3; ++i) {
         if (ir->operands[i]->type == ir->type) {
            operands[i] = ir->operands[i]->ir_value;
         } else if (ir->operands[i]->type->components() == 1) {
            operands[i] = f->id++;
            f->functions.push(SpvOpCompositeConstruct, ir->type->components() + 3);
            f->functions.push(type_id);
            f->functions.push(operands[i]);
            for (unsigned int j = 0; j < ir->type->components(); ++j) {
               f->functions.push(ir->operands[i]->ir_value);
            }
         } else {
            unreachable("operands must match result or be scalar");
         }
      }

      unsigned int value_id = f->id++;
      switch (ir->operation) {
      default:
         unreachable("unknown operation");
      case ir_triop_fma:
      case ir_triop_lrp:
         f->functions.push(SpvOpExtInst, 8);
         f->functions.push(type_id);
         f->functions.push(value_id);
         f->functions.push(f->import_id);
         switch (ir->operation) {
         default:
         case ir_triop_fma:   f->functions.push(GLSLstd450Fma);                                 break;
         case ir_triop_lrp:   f->functions.push(float_type ? GLSLstd450FMix : GLSLstd450IMix);  break;
         }
         break;
      }
      f->functions.push(operands[0]);
      f->functions.push(operands[1]);
      f->functions.push(operands[2]);
      ir->ir_value = value_id;
   }

   visit_precision(ir->ir_value, ir->type->base_type, GLSL_PRECISION_NONE);
}

void ir_print_spirv_visitor::visit(ir_texture *ir)
{
   if (ir->op == ir_samples_identical) {
      ir->sampler->accept(this);
      ir->coordinate->accept(this);
      return;
   }

   binary_buffer ids;

   ir->sampler->accept(this);
   visit_value(ir->sampler);
   ids.push(ir->sampler->ir_value);

   if (ir->op != ir_txs && ir->op != ir_query_levels && ir->op != ir_texture_samples) {

      ir->coordinate->accept(this);
      visit_value(ir->coordinate);
      ids.push(ir->coordinate->ir_value);

      if (ir->offset != NULL) {
         ir->offset->accept(this);
         visit_value(ir->offset);
         ids.push(ir->offset->ir_value);
      }
   }

   if (ir->op != ir_txf && ir->op != ir_txf_ms && ir->op != ir_txs && ir->op != ir_tg4 && ir->op != ir_query_levels && ir->op != ir_texture_samples) {

      if (ir->projector) {
         ir->projector->accept(this);
         visit_value(ir->projector);
         ids.push(ir->projector->ir_value);
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
      visit_value(ir->lod_info.bias);
      ids.push(ir->lod_info.bias->ir_value);
      break;
   case ir_txl:
   case ir_txf:
   case ir_txs:
      ir->lod_info.lod->accept(this);
      visit_value(ir->lod_info.lod);
      ids.push(ir->lod_info.lod->ir_value);
      break;
   case ir_txf_ms:
      ir->lod_info.sample_index->accept(this);
      visit_value(ir->lod_info.sample_index);
      ids.push(ir->lod_info.sample_index->ir_value);
      break;
   case ir_txd:
      ir->lod_info.grad.dPdx->accept(this);
      ir->lod_info.grad.dPdy->accept(this);
      visit_value(ir->lod_info.grad.dPdx);
      visit_value(ir->lod_info.grad.dPdy);
      ids.push(ir->lod_info.grad.dPdx->ir_value);
      ids.push(ir->lod_info.grad.dPdy->ir_value);
      break;
   case ir_tg4:
      ir->lod_info.component->accept(this);
      visit_value(ir->lod_info.component);
      ids.push(ir->lod_info.component->ir_value);
      break;
   case ir_samples_identical:
      unreachable("ir_samples_identical was already handled");
   };

   unsigned short op_id;
   switch (ir->op) {
   default:
   case ir_tex: {
      op_id = ir->projector ? SpvOpImageSampleProjImplicitLod : SpvOpImageSampleImplicitLod;
      unsigned int type_id = visit_type(ir->type);
      unsigned int result_id = f->id++;
      f->functions.push(op_id, ids.count() + 3);
      f->functions.push(type_id);
      f->functions.push(result_id);
      for (unsigned int i = 0; i < ids.count(); ++i) {
         f->functions.push(ids[i]);
      }
      ir->ir_value = result_id;
#if 0
      const ir_dereference_variable* var = ir->sampler->as_dereference_variable();
      if (var && var->var->data.precision == GLSL_PRECISION_MEDIUM) {
         f->decorates.push(SpvOpDecorate, 3);
         f->decorates.push(result_id);
         f->decorates.push(SpvDecorationRelaxedPrecision);
      }
#endif
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

   visit_value(ir->val);

   unsigned int type_id = visit_type(ir->type);
   unsigned int value_id = f->id++;
   unsigned int source_id = ir->val->ir_value;

   if (ir->mask.num_components == 1) {
      f->functions.push(SpvOpCompositeExtract, 5);
      f->functions.push(type_id);
      f->functions.push(value_id);
      f->functions.push(source_id);
      f->functions.push(ir->mask.x);
      ir->ir_value = value_id;
      return;
   }

   f->functions.push(SpvOpVectorShuffle, ir->mask.num_components + 5);
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
   ir->ir_value = value_id;
}

void ir_print_spirv_visitor::visit(ir_dereference_variable *ir)
{
   ir_variable *var = ir->variable_referenced();
   if (is_gl_identifier(var->name) == false && var->data.mode != ir_var_uniform)
      unique_name(var);

   switch (var->data.mode) {
   case ir_var_uniform:
      if (var->type->is_sampler() == false) {
         ir->ir_uniform = var->ir_uniform + 1;
         break;
      } else {
          unsigned int sampled_image_id = visit_type(var->type);
          if (var->ir_pointer == 0) {
             unsigned int name_id = unique_name(var);
             unsigned int binding_id = f->binding_id++;
             unsigned int type_pointer_id = visit_type_pointer(ir->type, var->data.mode, sampled_image_id);

             f->decorates.push(SpvOpDecorate, 4);
             f->decorates.push(name_id);
             f->decorates.push(SpvDecorationDescriptorSet);
             f->decorates.push(0u);

             f->decorates.push(SpvOpDecorate, 4);
             f->decorates.push(name_id);
             f->decorates.push(SpvDecorationBinding);
             f->decorates.push(binding_id);

             f->types.push(SpvOpVariable, 4);
             f->types.push(type_pointer_id);
             f->types.push(var->ir_pointer);
             f->types.push(SpvStorageClassUniformConstant);

             f->reflections.push(GL_SAMPLER);
             switch (var->type->sampler_dimensionality) {
                case GLSL_SAMPLER_DIM_1D:        f->reflections.push(GL_SAMPLER_1D);    break;
                case GLSL_SAMPLER_DIM_2D:        f->reflections.push(GL_SAMPLER_2D);    break;
                case GLSL_SAMPLER_DIM_3D:        f->reflections.push(GL_SAMPLER_3D);    break;
                case GLSL_SAMPLER_DIM_CUBE:      f->reflections.push(GL_SAMPLER_CUBE);  break;
             }
             f->reflections.push(0u);
             f->reflections.push(0u);
             f->reflections.push(binding_id);
             f->reflections.push(((int)strlen(var->name) + sizeof(int)) / sizeof(int));
             f->reflections.push(var->name);
          }

          unsigned int value_id = f->id++;
          f->functions.push(SpvOpLoad, 4);
          f->functions.push(sampled_image_id);
          f->functions.push(value_id);
          f->functions.push(var->ir_pointer);
 
          ir->ir_value = value_id;
      }
      ir->ir_pointer = var->ir_pointer;
      break;
   case ir_var_shader_out:
      if (f->shader_stage != MESA_SHADER_FRAGMENT && is_gl_identifier(var->name)) {

         if (f->gl_per_vertex_id == 0) {
            f->gl_per_vertex_id = f->id++;
            unsigned int len = (int)strlen("gl_PerVertex");
            unsigned int count = (len + sizeof(int)) / sizeof(int);
            f->names.push(SpvOpName, count + 2);
            f->names.push(f->gl_per_vertex_id);
            f->names.push("gl_PerVertex");

            f->decorates.push(SpvOpDecorate, 3);
            f->decorates.push(f->gl_per_vertex_id);
            f->decorates.push(SpvDecorationBlock);
         }

         if (var->ir_initialized == 0) {

            const glsl_type* type;
            SpvBuiltIn built_in;
            if (strcmp(var->name, "gl_Position") == 0) {
               type = glsl_type::vec4_type;
               built_in = SpvBuiltInPosition;
            } else if (strcmp(var->name, "gl_PointSize") == 0) {
               type = glsl_type::float_type;
               built_in = SpvBuiltInPointSize;
            } else {
               break;
            }

            unsigned int len = (int)strlen(var->name);
            unsigned int count = (len + sizeof(int)) / sizeof(int);
            f->names.push(SpvOpMemberName, count + 3);
            f->names.push(f->gl_per_vertex_id);
            f->names.push(f->per_vertices.count());
            f->names.push(var->name);

            f->decorates.push(SpvOpMemberDecorate, 5);
            f->decorates.push(f->gl_per_vertex_id);
            f->decorates.push(f->per_vertices.count());
            f->decorates.push(SpvDecorationBuiltIn);
            f->decorates.push(built_in);

            unsigned int struct_pointer_id = f->id++;
            f->builtins.push(SpvOpTypePointer, 4);
            f->builtins.push(struct_pointer_id);
            f->builtins.push(SpvStorageClassOutput);
            f->builtins.push(f->gl_per_vertex_id);

            unsigned int type_id = visit_type(type);
            unsigned int type_pointer_id = visit_type_pointer(type, var->data.mode, type_id);

            unsigned int variable_id = f->id++;
            f->builtins.push(SpvOpVariable, 4);
            f->builtins.push(struct_pointer_id);
            f->builtins.push(variable_id);
            f->builtins.push(SpvStorageClassOutput);

            unsigned int int_type_id = visit_type(glsl_type::int_type);
            unsigned int constant_id = f->id++;
            f->builtins.push(SpvOpConstant, 4);
            f->builtins.push(int_type_id);
            f->builtins.push(constant_id);
            f->builtins.push(f->per_vertices.count());

            f->per_vertices.push(type_id);

            unsigned int pointer_id = f->id++;
            f->functions.push(SpvOpAccessChain, 5);
            f->functions.push(type_pointer_id);
            f->functions.push(pointer_id);
            f->functions.push(variable_id);
            f->functions.push(constant_id);

            var->ir_initialized = pointer_id;
         }

         ir->ir_pointer = var->ir_initialized;
         break;
      }
      ir->ir_pointer = var->ir_pointer;
      break;
   default:
      ir->ir_pointer = var->ir_pointer;
      break;
   }
}

void ir_print_spirv_visitor::visit(ir_dereference_array *ir)
{
   ir->array->accept(this);
   ir->array_index->accept(this);

   visit_value(ir->array_index);

   unsigned int type_id = visit_type(ir->type);
   unsigned int pointer_id = f->id++;
   if (ir->array->ir_uniform) {
      ir_constant ir_uniform(ir->array->ir_uniform - 1);
      ir_uniform.ir_value = 0;
      visit(&ir_uniform);

      unsigned int type_id_pointer = visit_type_pointer(ir->type, ir_var_uniform, type_id);
      f->functions.push(SpvOpAccessChain, 6);
      f->functions.push(type_id_pointer);
      f->functions.push(pointer_id);
      f->functions.push(f->uniform_id);
      f->functions.push(ir_uniform.ir_value);
      f->functions.push(ir->array_index->ir_value);
   } else {
      unsigned int type_id_pointer = visit_type_pointer(ir->type, ir_var_auto, type_id);
      f->functions.push(SpvOpAccessChain, 5);
      f->functions.push(type_id_pointer);
      f->functions.push(pointer_id);
      f->functions.push(ir->array->ir_pointer);
      f->functions.push(ir->array_index->ir_value);
   }

   ir->ir_pointer = pointer_id;
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
   visit_value(ir->rhs);

   unsigned int value_id;
   bool full_write = (_mesa_bitcount(ir->write_mask) == ir->lhs->type->components());
   if (full_write && (ir->lhs->type->components() == ir->rhs->type->components())) {

      value_id = ir->rhs->ir_value;

   } else if (ir->rhs->type->components() == 1) {

      if (full_write) {

         unsigned int type_id = visit_type(ir->lhs->type);
         value_id = f->id++;
         f->functions.push(SpvOpCompositeConstruct, ir->lhs->type->components() + 3);
         f->functions.push(type_id);
         f->functions.push(value_id);
         for (unsigned int i = 0; i < ir->lhs->type->components(); ++i) {
            f->functions.push(ir->rhs->ir_value);
         }

      } else {
         ir_variable *var = ir->lhs->variable_referenced();
         unsigned int type_id = visit_type(ir->lhs->type->get_base_type());
         unsigned int type_pointer_id = visit_type_pointer(ir->lhs->type->get_base_type(), var->data.mode, type_id);
         for (unsigned int i = 0; i < ir->lhs->type->components(); ++i) {
            if (ir->write_mask & (1 << i)) {
               ir_constant ir_index(i);
               ir_index.ir_value = 0;
               visit(&ir_index);

               unsigned int access_id = f->id++;
               f->functions.push(SpvOpAccessChain, 5);
               f->functions.push(type_pointer_id);
               f->functions.push(access_id);
               f->functions.push(ir->lhs->ir_pointer);
               f->functions.push(ir_index.ir_value);

               f->functions.push(SpvOpStore, 3);
               f->functions.push(access_id);
               f->functions.push(ir->rhs->ir_value);
            }
         }
         return;
      }

   } else {

      visit_value(ir->lhs);

      unsigned int type_id = visit_type(ir->lhs->type);
      value_id = f->id++;
      f->functions.push(SpvOpVectorShuffle, ir->lhs->type->components() + 5);
      f->functions.push(type_id);
      f->functions.push(value_id);
      f->functions.push(ir->lhs->ir_value);
      f->functions.push(ir->rhs->ir_value);

      for (unsigned int i = 0, j = 0; i < ir->lhs->type->components(); ++i) {
         if (ir->write_mask & (1 << i)) {
            f->functions.push(ir->lhs->type->components() + j++);
         } else {
            f->functions.push(i);
         }
      }
   }

   if (ir->lhs->ir_pointer != 0) {
      f->functions.push(SpvOpStore, 3);
      f->functions.push(ir->lhs->ir_pointer);
      f->functions.push(value_id);
   }

   ir->lhs->ir_value = value_id;
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
               ir->ir_value = f->const_int_id[ir->value.u[0]];
            break;
         case GLSL_TYPE_INT:
            if (ir->value.i[0] >= 0 && ir->value.i[0] <= 15)
               ir->ir_value = f->const_int_id[ir->value.i[0]];
            break;
         case GLSL_TYPE_FLOAT:
            if (ir->value.f[0] >= 0.0f && ir->value.f[0] <= 15.0f && fmodf(ir->value.f[0], 1.0f) == 0.0f)
               ir->ir_value = f->const_float_id[(int)ir->value.f[0]];
            break;
         default:
            break;
         }
         if (ir->ir_value)
            return;

         unsigned int type_id = visit_type(ir->type);
         unsigned int constant_id = f->id++;
         f->types.push(SpvOpConstant, 4);
         f->types.push(type_id);
         f->types.push(constant_id);
         switch (ir->type->base_type) {
         case GLSL_TYPE_UINT:  f->types.push(ir->value.u[0]);           break;
         case GLSL_TYPE_INT:   f->types.push(ir->value.i[0]);           break;
         case GLSL_TYPE_FLOAT: f->types.push(*(int*)&ir->value.f[0]);   break;
         default:
            f->types.push(0u);
            unreachable("Invalid constant type");
         }
         ir->ir_value = constant_id;
#if 0
      visit_precision(ir->ir_value, ir->type->base_type, GLSL_PRECISION_NONE);
#endif

         switch (ir->type->base_type) {
         case GLSL_TYPE_UINT:
            if (ir->value.u[0] <= 15)
               f->const_int_id[ir->value.u[0]] = ir->ir_value;
            break;
         case GLSL_TYPE_INT:
            if (ir->value.i[0] >= 0 && ir->value.i[0] <= 15)
               f->const_int_id[ir->value.i[0]] = ir->ir_value;
            break;
         case GLSL_TYPE_FLOAT:
            if (ir->value.f[0] >= 0.0f && ir->value.f[0] <= 15.0f && fmodf(ir->value.f[0], 1.0f) == 0.0f)
               f->const_float_id[(int)ir->value.f[0]] = ir->ir_value;
            break;
         default:
            break;
         }
      } else {
         binary_buffer ids;
         for (unsigned int i = 0; i < ir->type->components(); i++) {
            switch (ir->type->base_type) {
            case GLSL_TYPE_UINT: {
               ir_constant ir_const(ir->value.u[i]);
               ir_const.ir_value = 0;
               visit(&ir_const);
               ids.push(ir_const.ir_value);
               break;
            }
            case GLSL_TYPE_INT: {
               ir_constant ir_const(ir->value.i[i]);
               ir_const.ir_value = 0;
               visit(&ir_const);
               ids.push(ir_const.ir_value);
               break;
            }
            case GLSL_TYPE_FLOAT:  {
               ir_constant ir_const(ir->value.f[i]);
               ir_const.ir_value = 0;
               visit(&ir_const);
               ids.push(ir_const.ir_value);
               break;
            }
            default:
               unreachable("Invalid constant type");
            }
         }
         unsigned int value_id = f->id++;
         unsigned int type_id = visit_type(ir->type);
         f->types.push(SpvOpConstantComposite, ids.count() + 3);
         f->types.push(type_id);
         f->types.push(value_id);
         for (unsigned i = 0; i < ids.count(); i++) {
            f->types.push(ids[i]);
         }
         ir->ir_value = value_id;
      }
#if 0
      visit_precision(ir->ir_value, ir->type->base_type, GLSL_PRECISION_NONE);
#endif
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
      f->functions.push(SpvOpSelectionMerge, 3);
      f->functions.push(label_end_id);
      f->functions.push(SpvSelectionControlMaskNone);

      f->functions.push(SpvOpBranchConditional, 4);
      f->functions.push(ir->condition->ir_value);
      f->functions.push(label_begin_id);
      f->functions.push(label_end_id);

      f->functions.push(SpvOpLabel, 2);
      f->functions.push(label_begin_id);

      f->functions.push(SpvOpKill, 1);

      f->functions.push(SpvOpLabel, 2);
      f->functions.push(label_end_id);
   } else {
      f->functions.push(SpvOpKill, 1);
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
   } else {
      f->functions.push(SpvOpSelectionMerge, 3);
      f->functions.push(label_else_id);
      f->functions.push(SpvSelectionControlMaskNone);
   }

   f->functions.push(SpvOpBranchConditional, 4);
   f->functions.push(ir->condition->ir_value);
   f->functions.push(label_then_id);
   f->functions.push(label_else_id);

   f->functions.push(SpvOpLabel, 2);
   f->functions.push(label_then_id);

   foreach_in_list(ir_instruction, inst, &ir->then_instructions) {
      inst->parent = ir;
      inst->accept(this);
   }

   if (ir->else_instructions.is_empty() == false) {

      f->functions.push(SpvOpBranch, 2);
      f->functions.push(label_end_id);
      f->functions.push(SpvOpLabel, 2);
      f->functions.push(label_else_id);

      foreach_in_list(ir_instruction, inst, &ir->else_instructions) {
         inst->parent = ir;
         inst->accept(this);
      }
   }

   f->functions.push(SpvOpBranch, 2);
   f->functions.push(label_end_id);
   f->functions.push(SpvOpLabel, 2);
   f->functions.push(label_end_id);
}

void
ir_print_spirv_visitor::visit(ir_loop *ir)
{
   unsigned int label_id = f->id++;

   f->functions.push(SpvOpBranch, 2);
   f->functions.push(label_id);
   f->functions.push(SpvOpLabel, 2);
   f->functions.push(label_id);

   unsigned int label_inner_id = f->id++;
   unsigned int label_outer_id = f->id++;

   f->functions.push(SpvOpLoopMerge, 4);
   f->functions.push(label_outer_id);
   f->functions.push(label_inner_id);
   f->functions.push(SpvLoopControlMaskNone);

   f->functions.push(SpvOpBranch, 2);
   f->functions.push(label_inner_id);
   f->functions.push(SpvOpLabel, 2);
   f->functions.push(label_inner_id);

   ir->ir_label = label_id;
   ir->ir_label_break = label_outer_id;

   foreach_in_list(ir_instruction, inst, &ir->body_instructions) {
      inst->parent = ir;
      inst->accept(this);
   }

   f->functions.push(SpvOpBranch, 2);
   f->functions.push(label_id);
   f->functions.push(SpvOpLabel, 2);
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

   f->functions.push(SpvOpBranch, 2);
   f->functions.push(ir->is_break() ? loop->ir_label_break : loop->ir_label);
   f->functions.push(SpvOpLabel, 2);
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
