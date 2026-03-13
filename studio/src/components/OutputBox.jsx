export default function OutputBox({ output }) {
  return (
    <div className="bg-secondary/30 border border-border rounded-lg p-4 min-h-[100px] max-h-[200px] overflow-y-auto whitespace-pre-wrap break-all text-xs text-muted-foreground font-mono">
      {output || 'Awaiting input...'}
    </div>
  )
}
