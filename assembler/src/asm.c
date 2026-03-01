#include "../include/assembler.h"

int main(int argc, char **argv) {
  if (argc != 2) {
    fprintf(stderr, "USAGE: asm input.asm\n");
    return 1;
  }
  printf("Assembling %s...\n", argv[1]);

  // Declare the shared state context
  AssemblerContext ctx;
  // Initialise line and symbol counts to zero
  ctx.line_count = 0;
  ctx.sym_count = 0;

  // Initialise the file descriptor
  FILE *input_file = fopen(argv[1], "r");
  // Perform the first pass
  pass_1(&ctx, input_file);

  print_assembler_context(ctx);

  // Close file descriptor
  fclose(input_file);

  return 0;
}
