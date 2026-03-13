import MemoryInspector from "./MemoryInspector.jsx";

export default function DebugControls({
	visible,
	currentStep,
	totalSteps,
	onPrev,
	onNext,
	finalMemory,
}) {
	if (!visible) return null;

	return (
		<div className="flex flex-col gap-4 pt-2 border-t border-border/50">
			<div className="flex items-center justify-between gap-4 bg-secondary/30 border border-border rounded-lg p-3">
				<button
					onClick={onPrev}
					disabled={currentStep === 0}
					className="bg-background text-foreground border border-border py-1.5 px-3 rounded-md text-sm font-medium cursor-pointer hover:bg-secondary transition-colors disabled:opacity-40 disabled:cursor-not-allowed"
				>
					← Prev
				</button>
				<span className="text-sm text-muted-foreground font-medium">
					<span className="text-foreground">{currentStep + 1}</span> /{" "}
					{totalSteps}
				</span>
				<button
					onClick={onNext}
					disabled={currentStep >= totalSteps - 1}
					className="bg-background text-foreground border border-border py-1.5 px-3 rounded-md text-sm font-medium cursor-pointer hover:bg-secondary transition-colors disabled:opacity-40 disabled:cursor-not-allowed"
				>
					Next →
				</button>
			</div>

			<MemoryInspector finalMemory={finalMemory} />
		</div>
	);
}
