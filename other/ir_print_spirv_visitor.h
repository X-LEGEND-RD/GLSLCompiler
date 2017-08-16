/* -*- c++ -*- */
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

#pragma once
#ifndef IR_PRINT_SPIRV_VISITOR_H
#define IR_PRINT_SPIRV_VISITOR_H

#include "ir.h"
#include "ir_visitor.h"

extern "C" {
#include "program/symbol_table.h"
#include "util/u_vector.h"
}

class binary_buffer {
public:
   binary_buffer();
   virtual ~binary_buffer();
   void push(unsigned int value);
   void push(const char* text);
   unsigned int count();
   unsigned int* data();
   unsigned int operator[] (size_t i);
protected:
   struct u_vector vector_buffer;
};

class spirv_buffer : public binary_buffer {
public:
   spirv_buffer();
   ~spirv_buffer();

   binary_buffer extensions;
   binary_buffer names;
   binary_buffer decorates;
   binary_buffer types;
   binary_buffer uniforms;
   binary_buffer inouts;
   binary_buffer per_vertices;
   binary_buffer builtins;
   binary_buffer functions;
   binary_buffer reflections;

   unsigned int precision_float;
   unsigned int precision_int;

   unsigned int id;
   unsigned int binding_id;
   unsigned int binding_start_id;   // we use one global uniform block per shader for vulkan

   unsigned int import_id;
   unsigned int uniform_struct_id;
   unsigned int uniform_id;
   unsigned int uniform_pointer_id;
   unsigned int uniform_offset;
   unsigned int function_id;
   unsigned int main_id;

   unsigned int gl_per_vertex_id;
   unsigned int gl_position_id;
   unsigned int gl_point_size;

   unsigned int void_id;
   unsigned int bool_id;
   unsigned int float_id[4*4];
   unsigned int int_id[4*4];
   unsigned int const_float_id[16];
   unsigned int const_int_id[16];
   unsigned int sampler_id[GLSL_SAMPLER_DIM_SUBPASS_MS + 1];

   unsigned int pointer_bool_id[12];
   unsigned int pointer_float_id[12*4*4];
   unsigned int pointer_int_id[12*4*4];
   unsigned int pointer_sampler[GLSL_SAMPLER_DIM_SUBPASS_MS + 1];

   unsigned int input_loc;
   unsigned int output_loc;

   unsigned short descript_set_definition;

   gl_shader_stage shader_stage;
};

/**
 * Abstract base class of visitors of IR instruction trees
 */
class ir_print_spirv_visitor : public ir_visitor {
public:
   ir_print_spirv_visitor(spirv_buffer *f);
   virtual ~ir_print_spirv_visitor();

   /**
    * \name Visit methods
    *
    * As typical for the visitor pattern, there must be one \c visit method for
    * each concrete subclass of \c ir_instruction.  Virtual base classes within
    * the hierarchy should not have \c visit methods.
    */
   /*@{*/
   virtual void visit(ir_rvalue *);
   virtual void visit(ir_variable *);
   virtual void visit(ir_function_signature *);
   virtual void visit(ir_function *);
   virtual void visit(ir_expression *);
   virtual void visit(ir_texture *);
   virtual void visit(ir_swizzle *);
   virtual void visit(ir_dereference_variable *);
   virtual void visit(ir_dereference_array *);
   virtual void visit(ir_dereference_record *);
   virtual void visit(ir_assignment *);
   virtual void visit(ir_constant *);
   virtual void visit(ir_call *);
   virtual void visit(ir_return *);
   virtual void visit(ir_discard *);
   virtual void visit(ir_if *);
   virtual void visit(ir_loop *);
   virtual void visit(ir_loop_jump *);
   virtual void visit(ir_emit_vertex *);
   virtual void visit(ir_end_primitive *);
   virtual void visit(ir_barrier *);
   /*@}*/

public:
   unsigned int visit_type(const struct glsl_type *type);
   char check_point_to_type(const struct glsl_type *type, unsigned int point_to);
   unsigned int visit_type_pointer(const struct glsl_type *type, unsigned int mode_index, unsigned int point_to);
   void visit_value(ir_rvalue *ir);
   unsigned int visit_sampler_type(glsl_sampler_dim sampler_dim);
   unsigned int visit_sampler_variable(ir_variable *ir_var, unsigned int pointer_type);

private:
   /**
    * Fetch/generate a unique name for ir_variable.
    *
    * GLSL IR permits multiple ir_variables to share the same name.  This works
    * fine until we try to print it, when we really need a unique one.
    */
   unsigned int unique_name(ir_variable *var);

   bool is_unique_name_exist(ir_variable *var);

   int unique_name_number;
   /** A mapping from ir_variable * -> unique printable names. */
   hash_table *printable_names;
   hash_table *sampler_vars;
   _mesa_symbol_table *symbols;

   void *mem_ctx;
   spirv_buffer *f;

   int indentation;
};

#endif /* IR_PRINT_SPIRV_VISITOR_H */
