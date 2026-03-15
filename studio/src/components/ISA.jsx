import React from "react";

export default function ISA() {
	// Extracted directly from your emulator's switch(opcode) block
	const instructions = [
		{ op: 0, mnem: "ldc", desc: "B = A; A = value" },
		{ op: 1, mnem: "adc", desc: "A = A + value" },
		{ op: 2, mnem: "ldl", desc: "B = A; A = memory[SP + offset]" },
		{ op: 3, mnem: "stl", desc: "memory[SP + offset] = A; A = B" },
		{ op: 4, mnem: "ldnl", desc: "A = memory[A + offset]" },
		{ op: 5, mnem: "stnl", desc: "memory[A + offset] = B" },
		{ op: 6, mnem: "add", desc: "A = A + B" },
		{ op: 7, mnem: "sub", desc: "A = B - A" },
		{ op: 8, mnem: "shl", desc: "A = B << A" },
		{ op: 9, mnem: "shr", desc: "A = B >> A" },
		{ op: 10, mnem: "adj", desc: "SP = SP - value" },
		{ op: 11, mnem: "a2sp", desc: "SP = A; A = B" },
		{ op: 12, mnem: "sp2a", desc: "B = A; A = SP" },
		{ op: 13, mnem: "call", desc: "B = A; A = PC; PC = PC + offset + 1" },
		{ op: 14, mnem: "return", desc: "PC = A + 1; A = B" },
		{ op: 15, mnem: "brz", desc: "if (A == 0) PC = PC + offset + 1" },
		{ op: 16, mnem: "brlz", desc: "if (A < 0) PC = PC + offset + 1" },
		{ op: 17, mnem: "br", desc: "PC = PC + offset + 1" },
		{ op: 18, mnem: "HALT", desc: "Stop execution" },
	];

	return (
		<div className="bg-card border border-border rounded-xl p-6 flex flex-col gap-4 shadow-sm col-span-3">
			<div>
				<label className="font-semibold text-foreground">SIMPLEX ISA</label>
				<p className="text-xs text-muted-foreground">
					Instruction Set Reference
				</p>
			</div>

			<div className="w-full h-[660px] bg-secondary/10 text-foreground border border-border rounded-lg font-mono text-sm overflow-y-auto focus-within:ring-2 focus-within:ring-primary/20 focus-within:border-primary transition-colors">
				<div className="sticky top-0 bg-secondary/90 backdrop-blur border-b border-border p-3 grid grid-cols-[3rem_4rem_1fr] gap-4 font-bold text-xs uppercase tracking-wider z-10">
					<div className="text-center">Op</div>
					<div>Instr</div>
					<div>Operation</div>
				</div>

				<div className="flex flex-col">
					{instructions.map((instr, idx) => (
						<div
							key={instr.op}
							className={`p-3 grid grid-cols-[3rem_4rem_1fr] gap-4 items-center transition-colors hover:bg-primary/10 ${
								idx % 2 === 0 ? "bg-transparent" : "bg-secondary/30"
							}`}
						>
							<div className="text-center text-muted-foreground text-xs">
								{instr.op}
							</div>
							<div className="font-semibold text-primary">{instr.mnem}</div>
							<div className="text-muted-foreground whitespace-nowrap overflow-x-auto no-scrollbar">
								{instr.desc}
							</div>
						</div>
					))}
				</div>
			</div>
		</div>
	);
}
