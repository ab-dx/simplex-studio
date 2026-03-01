#include <stdio.h>

typedef enum {
  NONE,
  NUMBER,
  LABEL_REF
} OperandType; // Type of operand for instr

typedef struct {
  int pc;                 // Program Counter
  char original_line[64]; // Original string for instruction
  char defined_label[64]; // Label for instruction
  char mnemonic[16];      // Instruction Mnemonic
  OperandType op_type;    // Instruction operand type
  int op_value;           // Instruction operand immediate value
  char op_label[64];      // Instruction operand label
} Line;

typedef enum {
  NO_OPERAND,
  HAS_OPERAND
} ExpectedOp; // Does the instruction expect operand

typedef struct {
  char mnemonic[16];      // Instruction Mnemonic
  int opcode;             // Instruction opcode
  ExpectedOp expected_op; // Instruction operand expected
} InstructionDef;

typedef struct {
  char name[64]; // Name of symbol/label
  int address;   // PC address
} Symbol;

typedef struct {
  Line lines[1024];      // Array to hold parsed lines
  int line_count;        // Count of lines parsed
  Symbol sym_table[256]; // Array for label definitions
  int sym_count;         // Count of labels defined
} AssemblerContext;

void pass_1(AssemblerContext *ctx, FILE *input_file);

void print_Line(Line line);
void print_Symbol(Symbol symbol);
void print_assembler_context(AssemblerContext ctx);
