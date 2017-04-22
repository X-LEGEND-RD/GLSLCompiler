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

#include "ir_print_glsl_visitor.h"
#include "compiler/glsl_types.h"
#include "glsl_parser_extras.h"
#include "main/macros.h"
#include "util/hash_table.h"

string_buffer::string_buffer(char* buf, size_t size)
   : buf(buf)
   , step(0)
   , size(size)
{
}

void string_buffer::printf(const char* format, ...) {
   va_list args;

   va_start(args, format);
   size_t count = vsnprintf(buf + step, size - step, format, args);
   va_end(args);

   step += count;
}

const char* string_buffer::string() const {
   return buf;
}

size_t string_buffer::offset() const {
   return step;
}

static void print_type(string_buffer *buf, const glsl_type *t);

extern "C" {
void
_mesa_print_glsl(string_buffer *buf, exec_list *instructions, struct _mesa_glsl_parse_state *state)
{
   // print version & extensions
   if (state) {
      buf->printf("#version %i", state->language_version);
      if (state->es_shader && state->language_version >= 300)
         buf->printf(" es");
      buf->printf("\n");
      if (state->es_shader) {
         buf->printf("precision %s float;\n", state->stage == MESA_SHADER_VERTEX ? "highp" : "mediump");
         buf->printf("precision mediump int;\n");
      }
#define EXT(ext) \
      if (state->ext ## _enable) \
         buf->printf("#extension GL_" #ext " : enable\n");
      EXT(ARB_shader_texture_lod);
      EXT(ARB_draw_instanced);
      //EXT(EXT_gpu_shader4);
      //EXT(EXT_shader_texture_lod);
      EXT(OES_standard_derivatives);
      //EXT(EXT_shadow_samplers);
      //EXT(EXT_frag_depth);
      if (state->es_shader && state->language_version < 300)
      {
         EXT(EXT_draw_buffers);
         //EXT(EXT_draw_instanced);
         EXT(OES_texture_3D);
      }
      EXT(ARM_framebuffer_read);
      EXT(ARM_shader_framebuffer_fetch);
      EXT(EXT_shader_framebuffer_fetch);
      EXT(NV_shader_framebuffer_fetch);
      EXT(ARB_shader_bit_encoding);
      EXT(EXT_texture_array);
#undef EXT
   }

   foreach_in_list(ir_instruction, ir, instructions) {
      ir_print_glsl_visitor v(buf, state);
      size_t offset = buf->offset();
      ir->accept(&v);
      if (offset == buf->offset())
         continue;
      if (ir->ir_type == ir_type_variable)
         buf->printf(";");
      if (ir->ir_type != ir_type_function)
         buf->printf("\n");
   }
}

} /* extern "C" */

ir_print_glsl_visitor::ir_print_glsl_visitor(string_buffer *buf, struct _mesa_glsl_parse_state *state)
   : buf(buf)
   , state(state)
{
   indentation = 0;
   printable_names =
      _mesa_hash_table_create(NULL, _mesa_hash_pointer, _mesa_key_pointer_equal);
   symbols = _mesa_symbol_table_ctor();
   mem_ctx = ralloc_context(NULL);
}

ir_print_glsl_visitor::~ir_print_glsl_visitor()
{
   _mesa_hash_table_destroy(printable_names, NULL);
   _mesa_symbol_table_dtor(symbols);
   ralloc_free(mem_ctx);
}

void ir_print_glsl_visitor::indent(void)
{
   for (int i = 0; i < indentation; i++)
      buf->printf("  ");
}

const char *
ir_print_glsl_visitor::unique_name(ir_variable *var)
{
   /* var->name can be NULL in function prototypes when a type is given for a
    * parameter but no name is given.  In that case, just return an empty
    * string.  Don't worry about tracking the generated name in the printable
    * names hash because this is the only scope where it can ever appear.
    */
   if (var->name == NULL) {
      static unsigned arg = 1;
      return ralloc_asprintf(this->mem_ctx, "parameter_%u", arg++);
   }

   /* Do we already have a name for this variable? */
   struct hash_entry * entry =
      _mesa_hash_table_search(this->printable_names, var);

   if (entry != NULL) {
      return (const char *) entry->data;
   }

   /* If there's no conflict, just use the original name */
   const char* name = NULL;
   if (_mesa_symbol_table_find_symbol(this->symbols, var->name) == NULL) {
      name = var->name;
   } else {
      static unsigned i = 1;
      name = ralloc_asprintf(this->mem_ctx, "%s_%u", var->name, ++i);
   }
   _mesa_hash_table_insert(this->printable_names, var, (void *) name);
   _mesa_symbol_table_add_symbol(this->symbols, name, var);
   return name;
}

static void
print_type(string_buffer *buf, const glsl_type *t)
{
   if (t->base_type == GLSL_TYPE_ARRAY) {
      print_type(buf, t->fields.array);
      buf->printf("[%u]", t->length);
   } else if ((t->base_type == GLSL_TYPE_STRUCT) && !is_gl_identifier(t->name)) {
      buf->printf("%s_%p", t->name, (void *) t);
   } else {
      buf->printf("%s", t->name);
   }
}

void ir_print_glsl_visitor::visit(ir_rvalue *)
{
   buf->printf("error");
}

void ir_print_glsl_visitor::visit(ir_variable *ir)
{
   if (is_gl_identifier(ir->name))
      return;
   if (ir->type->base_type == GLSL_TYPE_VOID)
      return;

   if (state->language_version <= 120) {
      if (state->stage == MESA_SHADER_VERTEX) {
         const char *const mode[] = { "", "uniform ", "", "", "attribute ", "varying ", "in ", "out ", "inout ", "", "", "" };
         buf->printf("%s", mode[ir->data.mode]);
      } else if (state->stage == MESA_SHADER_FRAGMENT) {
         const char *const mode[] = { "", "uniform ", "", "", "varying ", "out ", "in ", "out ", "inout ", "", "", "" };
         buf->printf("%s", mode[ir->data.mode]);
      }
   } else {
      const char *const mode[] = { "", "uniform ", "", "", "in ", "out ", "in ", "out ", "inout ", "", "", "" };
      buf->printf("%s", mode[ir->data.mode]);
   }
   int default_precision = GLSL_PRECISION_NONE;
   if (state->es_shader)
      default_precision = (state->stage == MESA_SHADER_VERTEX) ? GLSL_PRECISION_HIGH : GLSL_PRECISION_MEDIUM;
   if (ir->data.precision != default_precision) {
      const char *const precision[] = { "", "highp ", "mediump ", "lowp " };
      buf->printf("%s", precision[ir->data.precision]);
   }
   print_type(buf, ir->type);
   buf->printf(" %s", unique_name(ir));
}

void ir_print_glsl_visitor::visit(ir_function_signature *ir)
{
   _mesa_symbol_table_push_scope(symbols);

   print_type(buf, ir->return_type);
   buf->printf(" %s(", ir->function_name());
   foreach_in_list(ir_variable, inst, &ir->parameters) {
      if (inst != ir->parameters.head_sentinel.next)
         buf->printf(", ");
      inst->accept(this);
   }
   buf->printf(")\n{\n");

   indentation++;
   foreach_in_list(ir_instruction, inst, &ir->body) {
      indent();
      inst->accept(this);
      if (inst->ir_type == ir_type_if)
         buf->printf("\n");
      else
         buf->printf(";\n");
   }
   indentation--;
   indent();

   buf->printf("}\n");

   _mesa_symbol_table_pop_scope(symbols);
}

void ir_print_glsl_visitor::visit(ir_function *ir)
{
   foreach_in_list(ir_function_signature, sig, &ir->signatures) {
      indent();
      sig->accept(this);
   }
}

static const char *const operator_glsl_strs[] = {
   "~",
   "!",
   "-",
   "abs",
   "sign",
   "1.0/",
   "inversesqrt",
   "sqrt",
   "normalize",
   "exp",
   "log",
   "exp2",
   "log2",
   "int",
   "uint",
   "float",
   "bool",
   "float",
   "bool",
   "int",
   "float",
   "uint",
   "int",
   "float",
   "double",
   "int",
   "double",
   "uint",
   "double",
   "bool",
   "intBitsToFloat",
   "floatBitsToInt",
   "uintBitsToFloat",
   "floatBitsToUint",
   "trunc",
   "ceil",
   "floor",
   "fract",
   "roundEven",
   "sin",
   "cos",
   "dFdx",
   "dFdxCoarse",
   "dFdxFine",
   "dFdy",
   "dFdyCoarse",
   "dFdyFine",
   "packSnorm2x16",
   "packSnorm4x8",
   "packUnorm2x16",
   "packUnorm4x8",
   "packHalf2x16",
   "unpackSnorm2x16",
   "unpackSnorm4x8",
   "unpackUnorm2x16",
   "unpackUnorm4x8",
   "unpackHalf2x16",
   "bitfield_reverse",
   "bit_count",
   "find_msb",
   "find_lsb",
   "saturate",
   "packDouble2x32",
   "unpackDouble2x32",
   "frexp_sig",
   "frexp_exp",
   "noise",
   "subroutine_to_int",
   "interpolate_at_centroid",
   "get_buffer_size",
   "ssbo_unsized_array_length",
   "vote_any",
   "vote_all",
   "vote_eq",
   "+",
   "-",
   "*",
   "imul_high",
   "/",
   "carry",
   "borrow",
   "mod",
   "<",
   ">",
   "<=",
   ">=",
   "equal",
   "notEqual",
   "==",
   "!=",
   "<<",
   ">>",
   "&",
   "^",
   "|",
   "&&",
   "^^",
   "||",
   "dot",
   "min",
   "max",
   "pow",
   "ubo_load",
   "ldexp",
   "vector_extract",
   "interpolate_at_offset",
   "interpolate_at_sample",
   "fma",
   "mix",
   "csel",
   "bitfield_extract",
   "vector_insert",
   "bitfield_insert",
   "vector",
};

static const char *const operator_vec_glsl_strs[] = {
   "lessThan",
   "greaterThan",
   "lessThanEqual",
   "greaterThanEqual",
   "equal",
   "notEqual",
};

static bool is_binop_func_like(ir_expression_operation op, const glsl_type* type)
{
   if (op == ir_binop_equal || op == ir_binop_nequal || op == ir_binop_mod || (op >= ir_binop_dot && op <= ir_binop_pow))
      return true;
   if (type->is_vector() && (op >= ir_binop_less && op <= ir_binop_nequal))
      return true;
   return false;
}

void ir_print_glsl_visitor::visit(ir_expression *ir)
{
   if (ir->get_num_operands() == 1) {
      if (ir->operation >= ir_unop_f2i && ir->operation <= ir_unop_d2b) {
         print_type(buf, ir->type);
         buf->printf("(");
      } else if (ir->operation == ir_unop_rcp) {
         buf->printf("(1.0/(");
      } else {
         buf->printf("%s(", operator_glsl_strs[ir->operation]);
      }
      if (ir->operands[0])
   	     ir->operands[0]->accept(this);
      buf->printf(")");
      if (ir->operation == ir_unop_rcp) {
         buf->printf(")");
      }
   }
   else if (ir->operation == ir_binop_vector_extract)
   {
      if (ir->operands[0])
         ir->operands[0]->accept(this);
      buf->printf("[");
      if (ir->operands[1])
         ir->operands[1]->accept(this);
      buf->printf("]");
   }
   else if (is_binop_func_like(ir->operation, ir->type))
   {
      if (ir->operation == ir_binop_mod)
      {
         buf->printf("(");
         print_type(buf, ir->type);
         buf->printf("(");
      }
      if (ir->type->is_vector() && (ir->operation >= ir_binop_less && ir->operation <= ir_binop_nequal))
         buf->printf("%s(", operator_vec_glsl_strs[ir->operation-ir_binop_less]);
      else
         buf->printf("%s(", operator_glsl_strs[ir->operation]);

      if (ir->operands[0])
         ir->operands[0]->accept(this);
      buf->printf(", ");
      if (ir->operands[1])
         ir->operands[1]->accept(this);
      buf->printf(")");
      if (ir->operation == ir_binop_mod)
         buf->printf("))");
   }
   else if (ir->get_num_operands() == 2)
   {
      buf->printf("(");
      if (ir->operands[0])
         ir->operands[0]->accept(this);

      buf->printf(" %s ", operator_glsl_strs[ir->operation]);

      if (ir->operands[1])
          ir->operands[1]->accept(this);
      buf->printf(")");
   }
   else
   {
      // ternary op
      buf->printf("%s(", operator_glsl_strs[ir->operation]);
      if (ir->operands[0])
         ir->operands[0]->accept(this);
      buf->printf(", ");
      if (ir->operands[1])
         ir->operands[1]->accept(this);
      buf->printf(", ");
      if (ir->operands[2])
         ir->operands[2]->accept(this);
      buf->printf(")");
   }
}

void ir_print_glsl_visitor::visit(ir_texture *ir)
{
   if (ir->op == ir_samples_identical) {
      buf->printf("%s(", ir->opcode_string());
      ir->sampler->accept(this);
      buf->printf(", ");
      ir->coordinate->accept(this);
      buf->printf(")");
      return;
   }

   if (state && state->language_version < 130) {
      buf->printf(ir->sampler->type->sampler_shadow ? "shadow" : "texture");
      switch (ir->sampler->type->sampler_dimensionality)
      {
      case GLSL_SAMPLER_DIM_1D:        buf->printf("1D");       break;
      case GLSL_SAMPLER_DIM_2D:        buf->printf("2D");       break;
      case GLSL_SAMPLER_DIM_3D:        buf->printf("3D");       break;
      case GLSL_SAMPLER_DIM_CUBE:      buf->printf("Cube");     break;
      case GLSL_SAMPLER_DIM_RECT:      buf->printf("Rect");     break;
      case GLSL_SAMPLER_DIM_BUF:       buf->printf("Buf");      break;
      case GLSL_SAMPLER_DIM_EXTERNAL:  buf->printf("External"); break;
      case GLSL_SAMPLER_DIM_MS:        buf->printf("MS");       break;
      case GLSL_SAMPLER_DIM_SUBPASS:   buf->printf("Subpass");  break;
      }
   } else if (ir->op == ir_txf) {
      buf->printf("texelFetch");
   } else {
      buf->printf("texture");
   }

   if (ir->projector)
      buf->printf("Proj");
   if (ir->op == ir_txl)
      buf->printf("Lod");
   if (ir->op == ir_txd)
      buf->printf("Grad");
   if (ir->offset != NULL)
      buf->printf("Offset");

   buf->printf("(");
   ir->sampler->accept(this);

   if (ir->op != ir_txs && ir->op != ir_query_levels && ir->op != ir_texture_samples) {

      buf->printf(", ");
      ir->coordinate->accept(this);

      if (ir->offset != NULL) {
         buf->printf(", ");
         ir->offset->accept(this);
      }
   }

   if (ir->op != ir_txf && ir->op != ir_txf_ms && ir->op != ir_txs && ir->op != ir_tg4 && ir->op != ir_query_levels && ir->op != ir_texture_samples) {

      if (ir->projector) {
         buf->printf(", ");
         ir->projector->accept(this);
      }

      if (ir->shadow_comparitor) {
         buf->printf(", ");
         ir->shadow_comparitor->accept(this);
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
      buf->printf(", ");
      ir->lod_info.bias->accept(this);
      break;
   case ir_txl:
   case ir_txf:
   case ir_txs:
      buf->printf(", ");
      ir->lod_info.lod->accept(this);
      break;
   case ir_txf_ms:
      buf->printf(", ");
      ir->lod_info.sample_index->accept(this);
      break;
   case ir_txd:
      buf->printf(", ");
      ir->lod_info.grad.dPdx->accept(this);
      buf->printf(", ");
      ir->lod_info.grad.dPdy->accept(this);
      break;
   case ir_tg4:
      ir->lod_info.component->accept(this);
      break;
   case ir_samples_identical:
      unreachable("ir_samples_identical was already handled");
   };
   buf->printf(")");
}

void ir_print_glsl_visitor::visit(ir_swizzle *ir)
{
   const unsigned swiz[4] = {
      ir->mask.x,
      ir->mask.y,
      ir->mask.z,
      ir->mask.w,
   };

   ir->val->accept(this);
   buf->printf(".");
   for (unsigned i = 0; i < ir->mask.num_components; i++) {
      buf->printf("%c", "xyzw"[swiz[i]]);
   }
}

void ir_print_glsl_visitor::visit(ir_dereference_variable *ir)
{
   ir_variable *var = ir->variable_referenced();
   buf->printf("%s", unique_name(var));
}

void ir_print_glsl_visitor::visit(ir_dereference_array *ir)
{
   ir->array->accept(this);
   buf->printf("[");
   ir->array_index->accept(this);
   buf->printf("]");
}

void ir_print_glsl_visitor::visit(ir_dereference_record *ir)
{
   ir->record->accept(this);
   buf->printf(".%s", ir->field);
}

void ir_print_glsl_visitor::visit(ir_assignment *ir)
{
   if (ir->condition)
      ir->condition->accept(this);

   ir->lhs->accept(this);

   if (ir->lhs->type->components() > 1 && ir->write_mask != 0xF) {
      char mask[5];
      unsigned j = 0;

      for (unsigned i = 0; i < 4; i++) {
         if ((ir->write_mask & (1 << i)) != 0) {
            mask[j] = "xyzw"[i];
            j++;
         }
      }
      mask[j] = '\0';
      buf->printf(".%s", mask);
   }

   buf->printf(" = ");
   ir->rhs->accept(this);
}

void ir_print_glsl_visitor::visit(ir_constant *ir)
{
   print_type(buf, ir->type);
   buf->printf("(");

   if (ir->type->is_array()) {
      for (unsigned i = 0; i < ir->type->length; i++)
         ir->get_array_element(i)->accept(this);
   } else if (ir->type->is_record()) {
      ir_constant *value = (ir_constant *) ir->components.get_head();
      for (unsigned i = 0; i < ir->type->length; i++) {
         buf->printf("(%s ", ir->type->fields.structure[i].name);
         value->accept(this);
         buf->printf(")");

         value = (ir_constant *) value->next;
      }
   } else {
      for (unsigned i = 0; i < ir->type->components(); i++) {
         if (i != 0)
            buf->printf(", ");
         switch (ir->type->base_type) {
         case GLSL_TYPE_UINT:  buf->printf("%u", ir->value.u[i]); break;
         case GLSL_TYPE_INT:   buf->printf("%d", ir->value.i[i]); break;
         case GLSL_TYPE_FLOAT:
            if (ir->value.f[i] == 0.0f)
               /* 0.0 == -0.0, so print with %f to get the proper sign. */
               buf->printf("%.1f", ir->value.f[i]);
            else if (fabs(ir->value.f[i]) < 0.000001f)
               buf->printf("%a", ir->value.f[i]);
            else if (fabs(ir->value.f[i]) > 1000000.0f)
               buf->printf("%e", ir->value.f[i]);
            else if (fmod(ir->value.f[i] * 10.0f, 1.0f) == 0.0f)
               buf->printf("%.1f", ir->value.f[i]);
            else
               buf->printf("%f", ir->value.f[i]);
            break;
         case GLSL_TYPE_BOOL:  buf->printf("%d", ir->value.b[i]); break;
         case GLSL_TYPE_DOUBLE:
            if (ir->value.d[i] == 0.0)
               /* 0.0 == -0.0, so print with %f to get the proper sign. */
               buf->printf("%.1f", ir->value.d[i]);
            else if (fabs(ir->value.d[i]) < 0.000001)
               buf->printf("%a", ir->value.d[i]);
            else if (fabs(ir->value.d[i]) > 1000000.0)
               buf->printf("%e", ir->value.d[i]);
            else if (fmod(ir->value.d[i] * 10.0, 1.0) == 0.0)
               buf->printf("%.1f", ir->value.d[i]);
            else
               buf->printf("%f", ir->value.d[i]);
            break;
         default:
            unreachable("Invalid constant type");
         }
      }
   }
   buf->printf(")");
}

void
ir_print_glsl_visitor::visit(ir_call *ir)
{
   if (ir->return_deref) {
      ir->return_deref->accept(this);
      buf->printf(" = ");
   }
   buf->printf("%s", ir->callee_name());
   buf->printf("(");
   foreach_in_list(ir_rvalue, param, &ir->actual_parameters) {
      if (param != ir->actual_parameters.head_sentinel.next)
         buf->printf(", ");
      param->accept(this);
   }
   buf->printf(")");
}

void
ir_print_glsl_visitor::visit(ir_return *ir)
{
   ir_rvalue *const value = ir->get_value();
   if (value) {
      buf->printf("return ");
      value->accept(this);
   }
}

void
ir_print_glsl_visitor::visit(ir_discard *ir)
{
   if (ir->condition) {
      buf->printf("if ");
      ir->condition->accept(this);
      buf->printf("\n");
      indentation++;
      indent();
      indentation--;
   }

   buf->printf("discard");
}

void
ir_print_glsl_visitor::visit(ir_if *ir)
{
   buf->printf("if (");
   ir->condition->accept(this);
   buf->printf(") {\n");
   indentation++;

   foreach_in_list(ir_instruction, inst, &ir->then_instructions) {
      indent();
      inst->accept(this);
      buf->printf(";\n");
   }
   indentation--;
   indent();

   buf->printf("}\n");

   indent();
   if (!ir->else_instructions.is_empty()) {
      buf->printf("else {\n");
      indentation++;

      foreach_in_list(ir_instruction, inst, &ir->else_instructions) {
         indent();
         inst->accept(this);
         buf->printf(";\n");
      }
      indentation--;
      indent();

      buf->printf("}\n");
   }
}

void
ir_print_glsl_visitor::visit(ir_loop *ir)
{
   buf->printf("while (true) {\n");
   indentation++;

   foreach_in_list(ir_instruction, inst, &ir->body_instructions) {
      indent();
      inst->accept(this);
      buf->printf("\n");
   }
   indentation--;
   indent();

   buf->printf("}\n");
}

void
ir_print_glsl_visitor::visit(ir_loop_jump *ir)
{
   buf->printf("%s", ir->is_break() ? "break" : "continue");
}

void
ir_print_glsl_visitor::visit(ir_emit_vertex *ir)
{
   buf->printf("(emit-vertex ");
   ir->stream->accept(this);
   buf->printf(")\n");
}

void
ir_print_glsl_visitor::visit(ir_end_primitive *ir)
{
   buf->printf("(end-primitive ");
   ir->stream->accept(this);
   buf->printf(")\n");
}

void
ir_print_glsl_visitor::visit(ir_barrier *)
{
   buf->printf("(barrier)\n");
}
