#include "../include/assembler.h"
#include <string.h>

Symbol *lookup_symbol(AssemblerContext *ctx, char *label) {
  for (int i = 0; i < ctx->sym_count;
       i++) { // For each label in the symbol table

    if (strcmp(label, ctx->sym_table[i].name) ==
        0) {                       // Check for symbol with matching name
      return &(ctx->sym_table[i]); // Return matching symbol
    }
  }
  return NULL; // Return NULL if not found
}

void set_symbol_used(AssemblerContext *ctx, char *label) {
  for (int i = 0; i < ctx->sym_count;
       i++) { // For each label in the symbol table

    if (strcmp(label, ctx->sym_table[i].name) ==
        0) {                      // Check for symbol with matching name
      ctx->sym_table[i].used = 1; // Set as used
    }
  }
}
