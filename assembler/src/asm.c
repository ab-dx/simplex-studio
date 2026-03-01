#include "../include/assembler.h"

int main(int argc, char **argv) {
  if (!(argc == 4 || argc == 2)) {
    fprintf(stderr, "USAGE: \n");
    fprintf(stderr, "\tasm input.asm output.obj output.lst\n");
    fprintf(stderr, "\tasm -i (Read from stdin and write to stdout)\n");
    return 1;
  }

  // Declare the shared state context
  AssemblerContext ctx;
  // Initialise line and symbol counts to zero
  ctx.line_count = 0;
  ctx.sym_count = 0;

  // Declare the file descriptors
  FILE *input_file;
  FILE *output_obj_file;
  FILE *output_lst_file;

  // Assign file descriptors based on mode
  if (argc == 4) {
    input_file = fopen(argv[1], "r");
    output_obj_file = fopen(argv[2], "wb");
    output_lst_file = fopen(argv[3], "w");
    ctx.io_mode = 0;
  } else if (argc == 2) {
    input_file = stdin;
    output_obj_file = stdout;
    output_lst_file = fopen("/tmp/output.lst", "w");
    ctx.io_mode = 1;
  }

  // Perform the first pass
  pass_1(&ctx, input_file);

  if (!ctx.io_mode)
    print_assembler_context(ctx);

  // Perform the second pass after building context
  pass_2(&ctx, output_obj_file, output_lst_file);

  // Close file descriptors
  fclose(input_file);
  fclose(output_obj_file);
  fclose(output_lst_file);

  return 0;
}
