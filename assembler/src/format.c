#include "../include/assembler.h"

void print_Line(Line line) {
  printf("Line:\n");
  printf("\tOriginal line: %s\n", line.original_line);
  printf("\tPC: %d", line.pc);
  printf("\tDefined Label: %s", line.defined_label);
  printf("\tMnemonic: %s", line.mnemonic);
  printf("\tOperand Type: %s", line.op_type == NONE     ? "NONE"
                               : line.op_type == NUMBER ? "NUMBER"
                                                        : "LABEL_REF");
  printf("\tOp value: %d", line.op_value);
  printf("\tOp Label: %s\n", line.op_label);
}

void print_Symbol(Symbol symbol) {
  printf("Symbol:\n");
  printf("\tName: %s", symbol.name);
  printf("\tAddress: %d\n", symbol.address);
}

void print_assembler_context(AssemblerContext ctx) {
  printf("\nAssemblerContext:\n");
  printf("\tSymbol count: %d\n", ctx.sym_count);
  printf("\tLine count: %d\n", ctx.line_count);
  printf("Lines:\n");
  for (int i = 0; i < ctx.line_count; i++) {
    printf("%d. ", i);
    print_Line(ctx.lines[i]);
  }
  printf("Symbols:\n");
  for (int i = 0; i < ctx.sym_count; i++) {
    printf("%d. ", i);
    print_Symbol(ctx.sym_table[i]);
  }
}
