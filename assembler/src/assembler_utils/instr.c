/* DECLARATION OF AUTHORSHIP
 * AUTHOR: Abhinav Datta (2401CS30)
 * The following code is a part of CS2206 Mini Project: 2 Pass Assembler
 * Simplex ISA (2026)
 * */
#include "../../include/assembler.h"
#include <string.h>

#define NUM_INSTR 20

InstructionDef instr_table[NUM_INSTR] = {
    {"data", -1, HAS_OPERAND}, /* Special instruction */
    {"ldc", 0, HAS_OPERAND},    {"adc", 1, HAS_OPERAND},
    {"ldl", 2, HAS_OPERAND},    {"stl", 3, HAS_OPERAND},
    {"ldnl", 4, HAS_OPERAND},   {"stnl", 5, HAS_OPERAND},
    {"add", 6, NO_OPERAND},     {"sub", 7, NO_OPERAND},
    {"shl", 8, NO_OPERAND},     {"shr", 9, NO_OPERAND},
    {"adj", 10, HAS_OPERAND},   {"a2sp", 11, NO_OPERAND},
    {"sp2a", 12, NO_OPERAND},   {"call", 13, HAS_OPERAND},
    {"return", 14, NO_OPERAND}, {"brz", 15, HAS_OPERAND},
    {"brlz", 16, HAS_OPERAND},  {"br", 17, HAS_OPERAND},
    {"HALT", 18, NO_OPERAND},
}; /* SIMPLEX Instruction set defined */

InstructionDef *lookup_instruction(char *mnemonic) {
  for (int i = 0; i < NUM_INSTR;
       i++) { /* For each instruction in the defined table */
    if (strcmp(mnemonic, instr_table[i].mnemonic) ==
        0) { /* Check for instruction with matching mnemonic */
      return &(instr_table[i]); /* Return matching instruction */
    }
  }
  return NULL; /* Return NULL if not found */
}
