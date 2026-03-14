/* DECLARATION OF AUTHORSHIP
 * AUTHOR: Abhinav Datta (2401CS30)
 * The following code is a part of CS2206 Mini Project: 2 Pass Assembler
 * Simplex ISA (2026)
 * */
import { useState } from "react";
import CodeEditor from "./components/CodeEditor";
import RegisterDisplay from "./components/RegisterDisplay";
import DebugControls from "./components/DebugControls";
import OutputBox from "./components/OutputBox";

const DEFAULT_CODE = `ldc 0x1000
a2sp
ldc 5
HALT`;

export default function App() {
	const [code, setCode] = useState(DEFAULT_CODE);
	const [output, setOutput] = useState("Awaiting input...");
	const [currentBinaryBlob, setCurrentBinaryBlob] = useState(null);
	const [executionSteps, setExecutionSteps] = useState([]);
	const [finalMemory, setFinalMemory] = useState([]);
	const [currentStepIndex, setCurrentStepIndex] = useState(0);
	const [showDebugControls, setShowDebugControls] = useState(false);

	const assemble = async () => {
		setOutput("STATUS: ASSEMBLING...\n");
		setShowDebugControls(false);

		try {
			const payload = code.trim() + "\n";
			const response = await fetch("http://localhost:8080/assemble", {
				method: "POST",
				body: payload,
			});

			if (!response.ok) throw new Error(`HTTP ${response.status}`);

			const blob = await response.blob();
			setCurrentBinaryBlob(blob);
			const buffer = await blob.arrayBuffer();
			const view = new Uint8Array(buffer);

			if (view.length === 0) {
				setOutput("ERROR: Assembler returned 0 bytes.");
				return;
			}

			let hexDump = "--- MACHINE CODE (HEX) ---\n";
			for (let i = 0; i < view.length; i++) {
				hexDump += view[i].toString(16).padStart(2, "0").toUpperCase();
				if ((i + 1) % 4 === 0) hexDump += "\n";
				else hexDump += " ";
			}
			setOutput(hexDump);
		} catch (err) {
			setOutput("ASSEMBLER ERROR:\n" + err.message);
		}
	};

	const emulate = async () => {
		if (!currentBinaryBlob) {
			alert("You must Assemble the code before Emulating!");
			return;
		}

		setOutput((prev) => prev + "\nSTATUS: EMULATING...\n");
		setShowDebugControls(false);

		try {
			const response = await fetch("http://localhost:8080/emulate", {
				method: "POST",
				body: currentBinaryBlob,
			});

			if (!response.ok) throw new Error(`HTTP ${response.status}`);

			const rawJsonString = await response.text();
			setOutput(
				(prev) =>
					prev +
					"\n--- EMULATOR OUTPUT RECEIVED ---\nSize: " +
					rawJsonString.length +
					" bytes.",
			);
			console.log(rawJsonString);
			const parsedData = JSON.parse(rawJsonString);
			setExecutionSteps(parsedData[0]);
			setFinalMemory(parsedData[1]);
			setCurrentStepIndex(0);
			setShowDebugControls(true);
			renderStep(parsedData[0], 0);
		} catch (err) {
			setOutput((prev) => prev + "\nEMULATOR ERROR:\n" + err.message);
		}
	};

	const renderStep = (steps, index) => {};

	const getCurrentState = () => {
		if (!executionSteps || executionSteps.length === 0) return null;
		return executionSteps[currentStepIndex];
	};

	const nextStep = () => {
		if (currentStepIndex < executionSteps.length - 1) {
			setCurrentStepIndex((prev) => prev + 1);
		}
	};

	const prevStep = () => {
		if (currentStepIndex > 0) {
			setCurrentStepIndex((prev) => prev - 1);
		}
	};

	const currentState = getCurrentState();

	return (
		<div className="min-h-screen p-6 ">
			<div className="mx-auto">
				<div className="mb-8">
					<h1 className="text-3xl md:text-4xl font-bold text-foreground tracking-tight">
						Simplex <span className="text-muted-foreground">Studio</span>
					</h1>
					<p className="text-muted-foreground mt-1 text-sm">
						Assembly editor & emulator
					</p>
				</div>

				<div className="grid grid-cols-1 lg:grid-cols-2 gap-6">
					<CodeEditor
						code={code}
						onCodeChange={setCode}
						onAssemble={assemble}
						onEmulate={emulate}
						disabled={false}
					/>

					<div className="bg-card border border-border rounded-xl p-6 flex flex-col gap-4 shadow-sm">
						<div>
							<label className="font-semibold text-foreground">Registers</label>
							<p className="text-xs text-muted-foreground">
								Live execution state
							</p>
						</div>
						<RegisterDisplay state={currentState} />

						<DebugControls
							visible={showDebugControls}
							currentStep={currentStepIndex}
							totalSteps={executionSteps.length}
							onPrev={prevStep}
							onNext={nextStep}
							finalMemory={finalMemory}
						/>

						<div className="mt-2">
							<label className="font-semibold text-foreground">Output</label>
							<p className="text-xs text-muted-foreground">
								Assembler & emulator results
							</p>
						</div>
						<OutputBox output={output} />
					</div>
				</div>
			</div>
		</div>
	);
}
