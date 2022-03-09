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

#define HAVE_PTHREAD
#define HAVE_SCONS
#define HAVE_TIMESPEC_GET

#include <c99_math.h>
#include <getopt.h>

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
   int dump_builder;
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
#define standalone_options45 standalone_options_patch
#include "standalone.h"
#undef standalone_options
#define standalone_options standalone_options_patch

void
compile_shader_patch(struct gl_context *ctx, struct gl_shader *shader, const struct standalone_options_patch *options);

#define compile_shader _concat(compile_shader, __LINE__)
#define compile_shader498(ctx, shader) compile_shader_patch(ctx, shader, options)

#endif /* PATCH_H */
