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

		// ������������� ��������-��������� ��������, �������� eax:edx � div/idiv.
		// executionFlow.SetCmdDependentRegisters();
		// fout << executionFlow << endl << endl;

		// ��������� ������� ������ ���������� ��������� � eax.
		// tree.SetResultRegister(eax);	// � ���� double float, �� ���?
		// fout << executionFlow << endl << endl;

		// ���������� ���� ������ ���������.
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
