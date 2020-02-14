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

#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>

/** @file main.cpp
 *
 * This file is the main() routine and scaffolding for producing
 * builtin_compiler (which doesn't include builtins itself and is used
 * to generate the profile information for builtin_function.cpp), and
 * for glsl_compiler (which does include builtins and can be used to
 * offline compile GLSL code and examine the resulting GLSL IR.
 */

#include "main/mtypes.h"
#include "standalone.h"

static struct standalone_options_patch options;

const struct option compiler_opts[] = {
   { "dump-ast", no_argument, &options.dump_ast, 1 },
   { "dump-hir", no_argument, &options.dump_hir, 1 },
   { "dump-lir", no_argument, &options.dump_lir, 1 },
   { "dump-builder", no_argument, &options.dump_builder, 1 },
   { "dump-glsl", no_argument, &options.dump_glsl, 1 },
   { "dump-spirv", no_argument, &options.dump_spirv, 1 },
   { "dump-spirv-validation", no_argument, &options.dump_spirv_validation, 1 },
   { "dump-spirv-glsl", no_argument, &options.dump_spirv_glsl, 1 },
   { "link",     no_argument, &options.do_link,  1 },
   { "just-log", no_argument, &options.just_log, 1 },
   { "version",  required_argument, NULL, 'v' },
   { NULL, 0, NULL, 0 }
};

/**
 * \brief Print proper usage and exit with failure.
 */
static void
usage_fail(const char *name)
{

   const char *header =
      "usage: %s [options] <file.vert | file.tesc | file.tese | file.geom | file.frag | file.comp>\n"
      "\n"
      "Possible options are:\n";
   printf(header, name);
   for (const struct option *o = compiler_opts; o->name != 0; ++o) {
      printf("    --%s", o->name);
      if (o->has_arg == required_argument)
         printf(" (mandatory)");
      printf("\n");
   }
   exit(EXIT_FAILURE);
}

int
main(int argc, char * const* argv)
{
   int status = EXIT_SUCCESS;

   int c;
   int idx = 0;
   while ((c = getopt_long(argc, argv, "", compiler_opts, &idx)) != -1) {
      switch (c) {
      case 'v':
         options.glsl_version = strtol(optarg, NULL, 10);
         break;
      default:
         break;
      }
   }

   if (argc <= optind)
      usage_fail(argv[0]);

   struct gl_shader_program *whole_program;
   static struct gl_context local_ctx;

   whole_program = standalone_compile_shader(&options, argc - optind,
                                             &argv[optind], &local_ctx);

   if (!whole_program)
      usage_fail(argv[0]);

   standalone_compiler_cleanup(whole_program);

   return status;
}

#include "program.h"
#include "glsl_parser_extras.h"
#include "ir_print_glsl_visitor.h"
#include "ir_print_spirv_visitor.h"

extern "C" void
_mesa_error_no_memory(const char *caller)
{
// GET_CURRENT_CONTEXT(ctx);
// _mesa_error(ctx, GL_OUT_OF_MEMORY, "out of memory in %s", caller);
}

extern "C" void
_mesa_sha1_format(char *buf, const unsigned char *sha1)
{
   static const char hex_digits[] = "0123456789abcdef";
   int i;

   for (i = 0; i < 40; i += 2) {
      buf[i] = hex_digits[sha1[i >> 1] >> 4];
      buf[i + 1] = hex_digits[sha1[i >> 1] & 0x0f];
   }
   buf[i] = '\0';
}

void
compile_shader_patch(struct gl_context *ctx, struct gl_shader *shader, const struct standalone_options_patch *options)
{
   struct _mesa_glsl_parse_state *state =
      new(shader) _mesa_glsl_parse_state(ctx, shader->Stage, shader);

   _mesa_glsl_compile_shader(ctx, shader, options->dump_ast,
                             options->dump_hir, true);

   /* Print out the resulting IR */
   if (!state->error && options->dump_lir) {
      _mesa_print_ir(stdout, shader->ir, state);
   }

   if (!state->error && options->dump_glsl) {
      _mesa_print_glsl(stdout, fprintf, shader->ir, state);
   }

   if (!state->error && (options->dump_spirv || options->dump_spirv_validation || options->dump_spirv_glsl)) {
      spirv_buffer buffer;
      _mesa_print_spirv(&buffer, shader->ir, state, 0);

      FILE* f = fopen("output.spv", "wb");
      if (f) {
         fwrite(buffer.data(), sizeof(int), buffer.count(), f);
         fclose(f);
      }

      if (options->dump_spirv) {
#ifdef _WIN32
         system("spirv-dis.exe output.spv");
#else
         system("spirv-dis output.spv");
#endif
      }
      if (options->dump_spirv_validation) {
#ifdef _WIN32
         system("spirv-val.exe output.spv");
#else
         system("spirv-val output.spv");
#endif
      }
      if (options->dump_spirv_glsl) {
#ifdef _WIN32
         system("spirv-cross.exe output.spv");
#else
         system("spirv-cross output.spv");
#endif
      }
   }

   ralloc_free(state);
   return;
}
