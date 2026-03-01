#include "../include/emulator.h"

int main(int argc, char **argv) {
  if (argc != 2) {
    fprintf(stderr, "USAGE emu output.obj");
    return 1;
  }

  // Declare shared state context
  EmulatorContext ctx;
  // Initialise context
  ctx.pc = 0;
  ctx.sp = 0;
  ctx.a = 0;
  ctx.b = 0;

  // Initialise the file descriptors
  FILE *obj_file = fopen(argv[1], "r");

  // Populate memory registers
  populate_memory(&ctx, obj_file);

  // Run instructions in memory
  run(&ctx);

  // Close file descriptors
  fclose(obj_file);
  return 0;
}
