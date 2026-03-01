#include <stdio.h>

typedef enum { NONE, NUMBER, LABEL_REF } OperandType;

typedef struct {
  int pc;
  char original_line[64];
  char defined_label[64];
  char mnemonic[16];
  OperandType op_type;
  int op_value;
  char op_label[64];
} Line;

typedef enum { NO_OPERAND, HAS_OPERAND } ExpectedOp;

typedef struct {
  char mnemonic[16];
  int opcode;
  ExpectedOp expected_op;
} InstructionDef;

typedef struct {
  char name[64];
  int address;
} Symbol;

typedef struct {
  Line lines[1024];      // Array to hold parsed instructions
  int line_count;        // How many lines we've parsed
  Symbol sym_table[256]; // Array for our label definitions
  int sym_count;         // How many labels we've defined
} AssemblerContext;

void pass_1(AssemblerContext *ctx, FILE *input_file);
