#include "../include/assembler.h"

int main(int argc, char **argv) {
  if (argc != 4) {
    fprintf(stderr, "USAGE: asm input.asm output.obj output.lst\n");
    return 1;
  }
  printf("Assembling %s...\n", argv[1]);

  // Declare the shared state context
  AssemblerContext ctx;
  // Initialise line and symbol counts to zero
  ctx.line_count = 0;
  ctx.sym_count = 0;

  // Initialise the file descriptors
  FILE *input_file = fopen(argv[1], "r");
  FILE *output_obj_file = fopen(argv[2], "wb");
  FILE *output_lst_file = fopen(argv[3], "w");

  // Perform the first pass
  pass_1(&ctx, input_file);

  print_assembler_context(ctx);

  // Perform the second pass after building context
  pass_2(&ctx, output_obj_file, output_lst_file);

  // Close file descriptor
  fclose(input_file);
  fclose(output_obj_file);
  fclose(output_lst_file);

  return 0;
}
