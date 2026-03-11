#include "../../include/assembler.h"
#include <stdlib.h>
#include <string.h>

void pass_2(AssemblerContext *ctx, FILE *output_obj_file,
            FILE *output_lst_file) {
  for (int pc = 0; pc < ctx->line_count; pc++) {
    Line line = ctx->lines[pc]; /* Retrieve current line */
    int result = 0;             /* Resultant HEX Instruction */

    if (strcmp(line.mnemonic, "") == 0) {
      /* Empty instruction, only label on this line */
      /* Write instruction as text to listing file */
      /* Write 0 to obj file */
      /* fprintf(output_lst_file, "%08X\t        \t%s\n", pc, */
      /* line.original_line); */
      fprintf(output_lst_file, "%08X\t%08X\t%s\n", pc, result,
              line.original_line);
      fwrite(&result, sizeof(int), 1, output_obj_file);

      continue;
    }

    InstructionDef *instr =
        lookup_instruction(line.mnemonic); /* Retrieve instr for mnemonic */

    int offset = 0;        /* For PC relative addressing */
    int target = 0;        /* Target address for PC relative addressing */
    Symbol *target_symbol; /* Target symbol */

    if (instr == NULL) {
      fprintf(stderr, "ERROR: Unknown Instruction: %s\n", line.mnemonic);
      ctx->has_error = 1;
      exit(1);
    }

    switch (instr->expected_op) {
    default:
    case NO_OPERAND:
      if (line.op_type != NONE) {
        fprintf(stderr, "ERROR: Unexpected operand for %s\n", line.mnemonic);
        exit(1);
      }
      /* Write Opcode only as 32 bit payload */
      result = instr->opcode;
      break;
    case HAS_OPERAND:
      switch (line.op_type) {
      case NONE:
        fprintf(stderr, "ERROR: Expected operand for %s\n", line.mnemonic);
        ctx->has_error = 1;
        exit(1);
        break;
      case NUMBER:
        /* Special case for handling "data" */
        if (strcmp(line.mnemonic, "data") == 0) {
          result = line.op_value;
          break;
        }

        /* operand value for top 8 digits (HEX) */
        /* & with 0xFFFFFF to handle correct left shift for negative numbers */
        /* opcode for bottom 4 digits (HEX) */
        result = (((line.op_value & 0xFFFFFF) << 8) | instr->opcode);
        break;
      case LABEL_REF:
        /* Offset = Target address - (PC + 1) */
        target_symbol = lookup_symbol(ctx, line.op_label);
        if (target_symbol == NULL) {
          fprintf(stderr, "ERROR: Symbol %s not found\n", line.op_label);
          ctx->has_error = 1;
          exit(1);
        }
        /* Set symbol as used */
        set_symbol_used(ctx, line.op_label);
        target = target_symbol->address;
        int is_relative = (instr->opcode == 13 ||
                           (instr->opcode >= 15 && instr->opcode <= 17));

        if (is_relative) {
          offset = target - pc - 1;
        } else {
          offset = target; /* Absolute address for ldc */
        }
        result = (((offset & 0xFFFFFF) << 8) | instr->opcode);
        break;
      }
      break;
    }

    /* Write instruction as text to listing file */
    fprintf(output_lst_file, "%08X\t%08X\t%s\n", pc, result,
            line.original_line);
    fwrite(&result, sizeof(int), 1, output_obj_file);
  }

  /* Check for unused symbols to issue warning */
  for (int i = 0; i < ctx->sym_count;
       i++) { /* For each label in the symbol table */
    if (!(ctx->sym_table[i].used)) {
      fprintf(stderr, "WARNING: Unused symbol %s\n", ctx->sym_table[i].name);
    }
  }
  if (ctx->has_error) {
    fprintf(stderr, "Errors found, avoid using outputs\n");
    exit(1);
  }
}
