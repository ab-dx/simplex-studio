#include <stdio.h>

typedef struct {
  int memory[1024];
  int pc;
  int sp;
  int a;
  int b;
} EmulatorContext;

void populate_memory(EmulatorContext *ctx, FILE *obj_file);
void print_memory(EmulatorContext *ctx);
void run(EmulatorContext *ctx);
