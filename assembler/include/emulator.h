/* DECLARATION OF AUTHORSHIP
 * AUTHOR: Abhinav Datta (2401CS30)
 * The following code is a part of CS2206 Mini Project: 2 Pass Assembler
 * Simplex ISA (2026)
 * */
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
