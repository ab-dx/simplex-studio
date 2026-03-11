#include "../../include/emulator.h"

void populate_memory(EmulatorContext *ctx, FILE *obj_file) {
  for (int i = 0; i < MEM_SIZE; i++)
    ctx->memory[i] = 0;

  ctx->pc = 0;
  while (ctx->pc < MEM_SIZE &&
         fread(&ctx->memory[ctx->pc], sizeof(int), 1, obj_file)) {
    ctx->pc++;
  }
  ctx->program_size = ctx->pc;
}

void print_memory(EmulatorContext *ctx) {
  printf("REG: PC: 0x%08X\tSP: 0x%08X\tA: 0x%08X\tB: 0x%08X\n", ctx->pc,
         ctx->sp, ctx->a, ctx->b);
}

void print_memory_json(EmulatorContext *ctx) {
  fprintf(stdout,
          "{\"PC\": \"0x%08X\", \"SP\": \"0x%08X\", \"A\": \"0x%08X\", \"B\": "
          "\"0x%08X\"}",
          ctx->pc, ctx->sp, ctx->a, ctx->b);
}

void print_memory_complete_json(EmulatorContext *ctx) {
  fprintf(stdout, "[");
  for (int i = 0; i < MEM_SIZE; i++) {
    if (i == MEM_SIZE - 1) {
      fprintf(stdout, "{\"%d\": \"%08X\"}", i,
              ctx->memory[i]); /* without trailing comma */
      continue;
    }
    fprintf(stdout, "{\"%d\": \"%08X\"},", i, ctx->memory[i]);
  }
  fprintf(stdout, "]");
}
