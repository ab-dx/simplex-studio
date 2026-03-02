#include <stdio.h>
#define MEM_SIZE 1024

typedef struct {
  int memory[MEM_SIZE];
  int pc;
  int sp;
  int a;
  int b;
  int json_mode;
  int program_size;
} EmulatorContext;

void populate_memory(EmulatorContext *ctx, FILE *obj_file);
void print_memory(EmulatorContext *ctx);
void print_memory_json(EmulatorContext *ctx);
void print_memory_complete_json(EmulatorContext *ctx);
void run(EmulatorContext *ctx);
