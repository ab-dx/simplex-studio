#include "../../include/emulator.h"

void populate_memory(EmulatorContext *ctx, FILE *obj_file) {
  while (fread(&ctx->memory[ctx->pc], sizeof(int), 1, obj_file)) {
    ctx->pc++;
  }
  ctx->pc = 0;
}

void print_memory(EmulatorContext *ctx) {
  printf("REG: PC: 0x%08X\tSP: 0x%08X\tA: 0x%08X\tB: 0x%08X\n", ctx->pc,
         ctx->sp, ctx->a, ctx->b);
}
