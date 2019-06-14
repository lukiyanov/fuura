#pragma once
#include <ostream>
#include "ISyntaxTreeContainer.h"

// #include "CompiledFunction.h"	// TODO: ������������ ��������

namespace fuura::compilation
{
	class JITCompiler
	{
	public:
		void Compile(ISyntaxTreeContainer& functionToCompile);
		void Compile(ISyntaxTreeContainer& functionToCompile, std::ostream& debugTraceOut);
	};
}