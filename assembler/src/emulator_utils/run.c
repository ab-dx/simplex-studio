#include "../../include/emulator.h"

void run(EmulatorContext *ctx) {
  if (ctx->json_mode)
    fprintf(stdout, "[");
  ctx->pc = 0;
  while (1) {
    int instr = ctx->memory[ctx->pc];

    int opcode = instr & 0x000000FF; // Bottom 8 bits for opcode
    int operand = instr >> 8;        // Top 24 bits for operand

    switch (opcode) {
    default:
      if (!ctx->json_mode) {
        printf("ERROR: Invalid Opcode %d at PC 0x%08X\n", opcode, ctx->pc);
      } else {
        fprintf(stdout, "{\"error\": \"Invalid Opcode\"}]");
      }
      break;
    case 0: // ldc
      ctx->b = ctx->a;
      ctx->a = operand;
      break;
    case 1: // adc
      ctx->a = ctx->a + operand;
      break;
    case 2: // ldl
      ctx->b = ctx->a;
      ctx->a = ctx->memory[ctx->sp + operand];
      break;
    case 3: // stl
      ctx->memory[ctx->sp + operand] = ctx->a;
      ctx->a = ctx->b;
      break;
    case 4: // ldnl
      ctx->a = ctx->memory[ctx->a + operand];
      break;
    case 5: // stnl
      ctx->memory[ctx->a + operand] = ctx->b;
      break;
    case 6: // add
      ctx->a = ctx->a + ctx->b;
      break;
    case 7: // sub
      ctx->a = ctx->b - ctx->a;
      break;
    case 8: // shl
      ctx->a = ctx->b << ctx->a;
      break;
    case 9: // shr
      ctx->a = ctx->b >> ctx->a;
      break;
    case 10: // adj
      ctx->sp = ctx->sp + operand;
      break;
    case 11: // a2sp
      ctx->sp = ctx->a;
      ctx->a = ctx->b;
      break;
    case 12: // sp2a
      ctx->b = ctx->a;
      ctx->a = ctx->sp;
      break;
    case 13: // call
      ctx->b = ctx->a;
      ctx->a = ctx->pc;
      ctx->pc = ctx->pc + operand - 1; // +1 cancels out later
      break;
    case 14: // return
      ctx->pc = ctx->a;
      ctx->a = ctx->b;
      break;
    case 15: // brz
      if (ctx->a == 0) {
        ctx->pc = ctx->pc + operand - 1; // +1 cancels out later
      }
      break;
    case 16: // brlz
      if (ctx->a < 0) {
        ctx->pc = ctx->pc + operand - 1; // +1 cancels out later
      }
      break;
    case 17:                           // br
      ctx->pc = ctx->pc + operand - 1; // +1 cancels out later
      break;
    case 18: // HALT
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
    ctx->pc++;
  }
}
