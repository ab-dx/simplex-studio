#include <stdio.h>

typedef struct {
  int memory[10 * 1024];
  int pc;
  int sp;
  int a;
  int b;
  int json_mode;
} EmulatorContext;

void populate_memory(EmulatorContext *ctx, FILE *obj_file);
void print_memory(EmulatorContext *ctx);
void print_memory_json(EmulatorContext *ctx);
void print_memory_complete_json(EmulatorContext *ctx);
void run(EmulatorContext *ctx);
