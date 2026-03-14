/* DECLARATION OF AUTHORSHIP
 * AUTHOR: Abhinav Datta (2401CS30)
 * The following code is a part of CS2206 Mini Project: 2 Pass Assembler
 * Simplex ISA (2026)
 * */
export default function CodeEditor({
	code,
	onCodeChange,
	onAssemble,
	onEmulate,
	disabled,
}) {
	return (
		<div className="bg-card border border-border rounded-xl p-6 flex flex-col gap-4 shadow-sm">
			<div>
				<label className="font-semibold text-foreground">Assembly Source</label>
				<p className="text-xs text-muted-foreground">
					Write your assembly code below
				</p>
			</div>
			<textarea
				value={code}
				onChange={(e) => onCodeChange(e.target.value)}
				spellCheck="false"
				className="w-full h-[400px] bg-secondary/50 text-foreground border border-border rounded-lg font-mono text-sm p-4 resize-y focus:outline-none focus:ring-2 focus:ring-primary/20 focus:border-primary transition-colors placeholder:text-muted-foreground/50"
			/>
			<div className="flex gap-3">
				<button
					onClick={onAssemble}
					disabled={disabled}
					className="flex-1 bg-primary text-primary-foreground py-2.5 px-4 rounded-lg font-medium text-sm cursor-pointer hover:bg-primary/90 transition-colors disabled:opacity-50 disabled:cursor-not-allowed"
				>
					1. Assemble
				</button>
				<button
					onClick={onEmulate}
					disabled={disabled}
					className="flex-1 bg-secondary text-secondary-foreground border border-border py-2.5 px-4 rounded-lg font-medium text-sm cursor-pointer hover:bg-secondary/80 transition-colors disabled:opacity-50 disabled:cursor-not-allowed"
				>
					2. Emulate
				</button>
			</div>
		</div>
	);
}
