# DECLARATION OF AUTHORSHIP
# AUTHOR: Abhinav Datta (2401CS30)
# The following code is a part of CS2206 Mini Project: 2 Pass Assembler Simplex ISA (2026)

TEST_ASMS := $(wildcard tests/*/*.asm)

asm: src/asm.c src/assembler_utils/pass1.c src/assembler_utils/pass2.c src/assembler_utils/instr.c src/assembler_utils/symbol.c src/assembler_utils/format.c
	gcc src/asm.c src/assembler_utils/pass1.c src/assembler_utils/pass2.c src/assembler_utils/instr.c src/assembler_utils/symbol.c src/assembler_utils/format.c -Iinclude -o build/target/asm

emu: src/emu.c src/emulator_utils/memory.c src/emulator_utils/run.c
	gcc src/emu.c src/emulator_utils/memory.c src/emulator_utils/run.c -Iinclude -o build/target/emu

test: tests/*
	@for asm_file in $(TEST_ASMS); do \
		dir=$$(dirname $$asm_file); \
		echo "Assembling $$asm_file : $$dir/output.obj"; \
		./build/target/asm $$asm_file $$dir/output.obj $$dir/output.lst > $$dir/out.log 2>&1; \
	done
