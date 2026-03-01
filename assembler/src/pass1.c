#include "../include/assembler.h"
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

void trim(char *str) {
  int begin = 0, end = strlen(str) - 1;

  // Remove leading whitespace
  while (isspace(str[begin])) {
    begin++;
  }

  // Remove trailing whitespace
  while (end > begin && isspace(str[end])) {
    end--;
  }

  // If the string was trimmed, adjust the null terminator
  if (begin > 0 || end < (strlen(str) - 1)) {
    memmove(str, str + begin, end - begin + 1);
    str[end - begin + 1] = '\0';
  }
}

void process_lines(AssemblerContext *ctx, FILE *input_file,
                   void (*parse_line)(AssemblerContext *, char *)) {
  char buffer[1024]; // Buffer for storing the current line
  int c; // Current char stored as an int as EOF may be -1 on certain systems

  while ((c = fgetc(input_file)) != EOF) {
    int idx = 0; // index of the current line
    // Separately handle idx = 0 to prevent skipping the first character from
    // eof check
    while (idx == 0 || (c = fgetc(input_file)) != '\n') {
      buffer[idx++] = c; // Append character to buffer
    }
    buffer[idx] = '\0';         // Terminate line
    (*parse_line)(ctx, buffer); // Call function pointer to process the line
  }
}

void parse_line(AssemblerContext *ctx, char *buffer) {
  printf("%s\n", buffer);

  char original_line[1024];
  int symbol_found = 0;

  trim(buffer);                  // Remove leading and trailing whitespace
  strcpy(original_line, buffer); // Retain a copy of the original line

  // Returns pointer to first occurence of ; for finding comments
  char *comment_start = strchr(buffer, ';');
  // Ignore comments by terminating the buffer at comment_start
  if (comment_start != NULL) {
    *comment_start = '\0';
    // If comment begins at the beginning of the line, ignore line
    if (comment_start == buffer) {
      return;
    }
  }

  // Similarly, check for labels
  char *colon_ptr = strchr(buffer, ':');
  char label[32];
  // Split the string at : by terminating here
  if (colon_ptr != NULL) {
    *colon_ptr = '\0';
    symbol_found = 1;
    strcpy(label, buffer);
  } else {
    // If no label, set colon_ptr to point right before buffer
    colon_ptr = buffer - 1;
    label[0] = '\0';
  }

  char *instr_ptr = colon_ptr + 1; // Instruction right after label
  // Split on whitespaces, first token is the mnemonic, next is the immediate
  char *mnemonic_ptr = strtok(instr_ptr, " \t\n");
  char *imm_ptr = strtok(NULL, " \t\n");

  // Write to AssmeblerContext
  // Construct Line struct
  Line *line = &ctx->lines[ctx->line_count];
  line->pc = ctx->line_count;
  strcpy(line->original_line, original_line);

  if (mnemonic_ptr != NULL) {
    strcpy(line->mnemonic, mnemonic_ptr);
    if (imm_ptr != NULL) {
      // Check if it's a number (starts with digit, -, or +)
      if (isdigit(imm_ptr[0]) || imm_ptr[0] == '-' || imm_ptr[0] == '+') {
        line->op_type = NUMBER;
        // Hex (0x) and decimal parsing
        if (strncmp(imm_ptr, "0x", 2) == 0 || strncmp(imm_ptr, "0X", 2) == 0) {
          line->op_value = (int)strtol(imm_ptr, NULL, 16);
        } else {
          line->op_value = (int)strtol(imm_ptr, NULL, 10);
        }
        line->op_label[0] = '\0';
      } else {
        // Otherwise must be label reference
        line->op_type = LABEL_REF;
        strcpy(line->op_label, imm_ptr);
        line->op_value = 0;
      }
    } else {
      // No operand
      line->op_type = NONE;
      line->op_label[0] = '\0';
      line->op_value = 0;
    }
  }

  if (symbol_found) {
    strcpy(line->defined_label, label);
    // Construct Symbol struct
    Symbol *sym = &ctx->sym_table[ctx->sym_count];
    strcpy(sym->name, label);
    sym->address = line->pc;
    ctx->sym_count = ctx->sym_count + 1;
  }

  ctx->line_count = ctx->line_count + 1;

  printf("Label: %s\nMnemonic: %s\nImmediate: %s\n", label, mnemonic_ptr,
         imm_ptr);
}

void pass_1(AssemblerContext *ctx, FILE *input_file) {
  process_lines(ctx, input_file, parse_line);
}
