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
#ifndef PATCH_H
#define PATCH_H

#define HAVE_OPENGL_ES_2 1
#define HAVE_PTHREAD
#define HAVE_STRUCT_TIMESPEC

#include <getopt.h>
#include <stdint.h>

#ifdef __cplusplus
#undef signbit
#include <glsl/list.h>
class exec_node_patch : public exec_node {
public:
   struct exec_node *parent;
   unsigned int ir_value;
   unsigned int ir_pointer;
   unsigned int ir_label;
   unsigned int ir_label_break;
   unsigned int ir_uniform_location;
   unsigned int ir_binding_point;
};
#define exec_node exec_node_patch
#include "ir.h"
#undef exec_node
#endif

#define __concat(x, y) x ## y
#define _concat(x, y) __concat(x, y)

struct standalone_options_patch {
   int glsl_version;
   int dump_ast;
   int dump_hir;
   int dump_lir;
   int do_link;
   int just_log;
   int lower_precision;
   int dump_glsl;
   int dump_spirv;
   int dump_spirv_validation;
   int dump_spirv_glsl;
};

#define standalone_options _concat(standalone_options, __LINE__)
#define standalone_options31 standalone_options_old
#define standalone_options44 standalone_options_patch
#include "standalone.h"
#undef standalone_options
#define standalone_options standalone_options_patch

struct nir_shader *
glsl_to_nir_patch(struct gl_shader *shader, struct gl_context *ctx);

#define glsl_to_nir _concat(glsl_to_nir, __LINE__)
#define glsl_to_nir2449(shader, ...) glsl_to_nir_patch(shader, ctx)

#define gl_nir_link_glsl _concat(gl_nir_link_glsl, __LINE__)
#define gl_nir_link_glsl431(...) (void)0

#endif /* PATCH_H */
