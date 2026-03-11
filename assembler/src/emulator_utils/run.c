#include "../../include/emulator.h"
#include <stdint.h>

void run(EmulatorContext *ctx) {
  if (ctx->json_mode)
    fprintf(stdout, "[");
  ctx->pc = 0;
  int cycle_count = 0;          /* Safety counter */
  const int MAX_CYCLES = 10000; /* Limit for malicious emulations */
  while (ctx->pc < ctx->program_size) {
    if (cycle_count++ > MAX_CYCLES) { /* Check the limit */
      if (!ctx->json_mode) {
        printf("\nERROR: Execution Limit Exceeded! Infinite loop detected.\n");
      } else {
        fprintf(stderr, "{\"error\": \"Timeout: Execution Limit Exceeded\"}]");
      }
      return;
    }
    /* int instr = ctx->memory[ctx->pc]; */
    /* int opcode = instr & 0x000000FF; // Bottom 8 bits for opcode */
    /* int operand = instr >> 8;        // Top 24 bits for operand */
    uint32_t instr = (uint32_t)ctx->memory[ctx->pc];
    int opcode = instr & 0xFFu;
    int operand = (int)(instr >> 8); /* now 0..2^24-1 */
    if (operand & 0x00800000)        /* if sign bit of 24-bit is set */
      operand |= 0xFF000000;

    int next_pc = ctx->pc + 1;

    switch (opcode) {
    default:
      if (!ctx->json_mode) {
        printf("ERROR: Invalid Opcode %d at PC 0x%08X\n", opcode, ctx->pc);
      } else {
        fprintf(stdout, "{\"error\": \"Invalid Opcode\"}]");
      }
      return;
      break;
    case 0: /* ldc */
      ctx->b = ctx->a;
      ctx->a = operand;
      break;
    case 1: /* adc */
      ctx->a = ctx->a + operand;
      break;
    case 2: /* ldl */
      ctx->b = ctx->a;
      ctx->a = ctx->memory[ctx->sp + operand];
      break;
    case 3: /* stl */
      ctx->memory[ctx->sp + operand] = ctx->a;
      ctx->a = ctx->b;
      break;
    case 4: /* ldnl */
      ctx->a = ctx->memory[ctx->a + operand];
      break;
    case 5: /* stnl */
      ctx->memory[ctx->a + operand] = ctx->b;
      break;
    case 6: /* add */
      ctx->a = ctx->a + ctx->b;
      break;
    case 7: /* sub */
      ctx->a = ctx->b - ctx->a;
      break;
    case 8: /* shl */
      ctx->a = ctx->b << ctx->a;
      break;
    case 9: /* shr */
      ctx->a = ctx->b >> ctx->a;
      break;
    case 10: /* adj */
      ctx->sp = ctx->sp - operand;
      break;
    case 11: /* a2sp */
      ctx->sp = ctx->a;
      ctx->a = ctx->b;
      break;
    case 12: /* sp2a */
      ctx->b = ctx->a;
      ctx->a = ctx->sp;
      break;
    case 13: /* call */
      ctx->b = ctx->a;
      ctx->a = ctx->pc;
      next_pc = ctx->pc + operand + 1;
      break;
    case 14: /* return */
             /* ctx->pc = ctx->a; */
      next_pc = ctx->a + 1;
      ctx->a = ctx->b;
      break;
    case 15: /* brz */
      if (ctx->a == 0)
        next_pc = ctx->pc + operand + 1;
      break;
    case 16: /* brlz */
      if (ctx->a < 0)
        next_pc = ctx->pc + operand + 1;
      break;
    case 17: /* br */
      next_pc = ctx->pc + operand + 1;
      break;
    case 18: /* HALT */
      if (!ctx->json_mode) {
        printf("\nInstr: 0x%08X ", instr);
        printf("Operand: %d Opcode: %d\n", operand, opcode);
        print_memory(ctx);
      } else {
        print_memory_json(ctx);
        fprintf(stdout, "]");
      }
      return;
      break;
    }
    if (!ctx->json_mode) {
      printf("\nInstr: 0x%08X ", instr);
      printf("Operand: %d Opcode: %d\n", operand, opcode);
      print_memory(ctx);
    } else {
      print_memory_json(ctx);
      fprintf(stdout, ",");
    }
    ctx->pc = next_pc;
  }
}
