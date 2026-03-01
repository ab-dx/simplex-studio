asm: src/asm.c src/assembler_utils/pass1.c src/assembler_utils/pass2.c src/assembler_utils/instr.c src/assembler_utils/symbol.c src/assembler_utils/format.c
	gcc src/asm.c src/assembler_utils/pass1.c src/assembler_utils/pass2.c src/assembler_utils/instr.c src/assembler_utils/symbol.c src/assembler_utils/format.c -Iinclude -o build/target/asm

emu: src/emu.c src/emulator_utils/memory.c src/emulator_utils/run.c
	gcc src/emu.c src/emulator_utils/memory.c src/emulator_utils/run.c -Iinclude -o build/target/emu

