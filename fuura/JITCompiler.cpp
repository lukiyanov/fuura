#include "stdafx.h"
#include "JITCompiler.h"
#include "ExecutionFlow.h"
using namespace fuura::compilation;
using namespace std;

// ----------------------------------------------------------------------------
void JITCompiler::Compile(ISyntaxTreeContainer& functionToCompile)
{
	/*
	VirtualRegisterManager vrm;
	ExecutionFlow executionFlow;

	auto tree = functionToCompile.GetSyntaxTree();
	tree->GenerateFlow(executionFlow, vrm);

	

	if (debugTraceFile)
	{
		ofstream fout(debugTraceFile.value());
		fout << executionFlow << endl << endl;

		// Подставляются командно-зависимые регистры, например eax:edx в div/idiv.
		// executionFlow.SetCmdDependentRegisters();
		// fout << executionFlow << endl << endl;

		// Последняя команда должна возвращать результат в eax.
		// tree.SetResultRegister(eax);	// А если double float, то где?
		// fout << executionFlow << endl << endl;

		// Разрешение всех прочих регистров.
		// tree.ResolveRegisters();
		// fout << executionFlow << endl << endl;

		// AsmTranslator asmTranslator;
		// tree.Compile(asmTranslator);
		// asmTranslator.GetCode();
		// fout << executionFlow << endl << endl;

		fout.flush();
	}
	*/
}

// ----------------------------------------------------------------------------
