#include "../include/emulator.h"
#include <string.h>

int main(int argc, char **argv) {
  if (argc != 2) {
    fprintf(stderr, "USAGE:\n");
    fprintf(stderr,
            "\tJSON MODE: emu -j (Read from stdin and write to stdout)\n");
    fprintf(stderr, "\tRegular MODE: emu output.obj\n");
    return 1;
  }

  // Declare shared state context
  EmulatorContext ctx;
  // Initialise context
  ctx.pc = 0;
  ctx.sp = 0;
  ctx.a = 0;
  ctx.b = 0;
  ctx.json_mode = (strcmp(argv[1], "-j") == 0) ? 1 : 0;

  // Initialise the file descriptors
  FILE *obj_file = ctx.json_mode ? stdin : fopen(argv[1], "r");

  // Populate memory registers
  populate_memory(&ctx, obj_file);

  if (ctx.json_mode) {
    fprintf(stdout, "[");
  }
  // Run instructions in memory
  run(&ctx);

  if (ctx.json_mode) {
    fprintf(stdout, ",");
    print_memory_complete_json(&ctx);
    fprintf(stdout, "]");
  }

  // Close file descriptors
  fclose(obj_file);
  return 0;
}
