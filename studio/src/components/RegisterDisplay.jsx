export default function RegisterDisplay({ state }) {
  const display = state || { PC: '--------', SP: '--------', A: '--------', B: '--------' }

  return (
    <div className="grid grid-cols-2 gap-3 text-sm bg-secondary/30 border border-border rounded-lg p-4">
      <div className="flex justify-between items-center gap-4">
        <span className="text-muted-foreground font-medium">PC</span>
        <span className="text-primary font-mono font-semibold">{display.PC}</span>
      </div>
      <div className="flex justify-between items-center gap-4">
        <span className="text-muted-foreground font-medium">SP</span>
        <span className="text-primary font-mono font-semibold">{display.SP}</span>
      </div>
      <div className="flex justify-between items-center gap-4">
        <span className="text-muted-foreground font-medium">A</span>
        <span className="text-primary font-mono font-semibold">{display.A}</span>
      </div>
      <div className="flex justify-between items-center gap-4">
        <span className="text-muted-foreground font-medium">B</span>
        <span className="text-primary font-mono font-semibold">{display.B}</span>
      </div>
    </div>
  )
}
