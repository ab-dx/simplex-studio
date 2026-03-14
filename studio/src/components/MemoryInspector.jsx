/* DECLARATION OF AUTHORSHIP
 * AUTHOR: Abhinav Datta (2401CS30)
 * The following code is a part of CS2206 Mini Project: 2 Pass Assembler
 * Simplex ISA (2026)
 * */
import { useState, useRef } from "react";

function formatMemoryValue(val) {
	if (typeof val === "object" && val !== null) {
		const key = Object.keys(val)[0];
		const hexStr = val[key];
		const decStr = parseInt(hexStr, 16).toString();
		return { dec: decStr, hex: hexStr };
	}
	const hexStr = (val >>> 0).toString(16).toUpperCase().padStart(8, "0");
	return { dec: val.toString(), hex: hexStr };
}

export default function MemoryInspector({ finalMemory }) {
	const [address, setAddress] = useState("");
	const [value, setValue] = useState("---");
	const [jumpAddr, setJumpAddr] = useState("");
	const gridRef = useRef(null);

	const inspectMemory = () => {
		if (!finalMemory || finalMemory.length === 0) return;

		const isHex = address.toLowerCase().startsWith("0x");
		const addr = parseInt(address, isHex ? 16 : 10);

		if (isNaN(addr) || addr < 0 || addr >= finalMemory.length) {
			setValue("[OUT OF BOUNDS]");
			return;
		}

		const val = JSON.stringify(finalMemory[addr]);
		const hexVal = (val >>> 0).toString(16).toUpperCase().padStart(8, "0");
		setValue(`${val} (0x${hexVal})`);
	};

	const jumpToMemory = () => {
		if (!finalMemory || !jumpAddr.trim()) return;
		const isHex = jumpAddr.toLowerCase().startsWith("0x");
		const addr = parseInt(jumpAddr, isHex ? 16 : 10);
		if (isNaN(addr) || addr < 0 || addr >= finalMemory.length) return;

		const row = document.getElementById(`mem-row-${addr}`);
		if (row) {
			row.scrollIntoView({ behavior: "smooth", block: "center" });
			row.classList.add("bg-primary/10");
			setTimeout(() => row.classList.remove("bg-primary/10"), 1500);
		}
	};

	return (
		<div className="flex flex-col gap-4">
			<div className="bg-secondary/30 border border-border rounded-lg p-4 flex flex-col gap-3">
				<label className="font-medium text-sm text-foreground">
					Memory Grid
				</label>
				<div className="flex gap-2">
					<input
						type="text"
						value={jumpAddr}
						onChange={(e) => setJumpAddr(e.target.value)}
						placeholder="Jump to ADDR (e.g. 64 or 0x40)"
						className="flex-1 px-3 py-2 text-sm font-mono bg-background border border-border rounded-md text-foreground focus:outline-none focus:ring-2 focus:ring-primary/20 focus:border-primary transition-colors placeholder:text-muted-foreground/50"
						onKeyDown={(e) => e.key === "Enter" && jumpToMemory()}
					/>
					<button
						onClick={jumpToMemory}
						className="bg-primary text-primary-foreground py-2 px-4 rounded-md font-medium text-sm cursor-pointer hover:bg-primary/90 transition-colors"
					>
						GO
					</button>
				</div>
				<div className="h-[250px] overflow-y-auto bg-background border border-border rounded-lg">
					{!finalMemory || finalMemory.length === 0 ? (
						<div className="p-4 text-center text-muted-foreground text-sm">
							Emulate code to view memory.
						</div>
					) : (
						<table className="w-full text-sm font-mono">
							<thead className="sticky top-0 bg-muted text-foreground font-semibold border-b border-border">
								<tr>
									<th className="px-3 py-2 text-left">ADDR</th>
									<th className="px-3 py-2 text-left">DECIMAL</th>
									<th className="px-3 py-2 text-left">HEX</th>
								</tr>
							</thead>
							<tbody ref={gridRef}>
								{finalMemory.map((val, i) => {
									const { dec, hex } = formatMemoryValue(val);
									return (
										<tr
											key={i}
											id={`mem-row-${i}`}
											className="border-b border-border/50 hover:bg-muted/30 transition-colors"
										>
											<td className="px-3 py-1 text-blue-600 dark:text-blue-400">
												{i}
											</td>
											<td className="px-3 py-1 text-foreground">{dec}</td>
											<td className="px-3 py-1 text-muted-foreground">
												0x{hex}
											</td>
										</tr>
									);
								})}
							</tbody>
						</table>
					)}
				</div>
			</div>
		</div>
	);
}
