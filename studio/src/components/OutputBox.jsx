/* DECLARATION OF AUTHORSHIP
 * AUTHOR: Abhinav Datta (2401CS30)
 * The following code is a part of CS2206 Mini Project: 2 Pass Assembler
 * Simplex ISA (2026)
 * */
export default function OutputBox({ output }) {
	return (
		<div className="bg-secondary/30 border border-border rounded-lg p-4 min-h-[100px] max-h-[200px] overflow-y-auto whitespace-pre-wrap break-all text-xs text-muted-foreground font-mono">
			{output || "Awaiting input..."}
		</div>
	);
}
