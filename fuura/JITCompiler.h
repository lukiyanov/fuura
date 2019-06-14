#pragma once
#include <ostream>
#include "ISyntaxTreeContainer.h"

// #include "CompiledFunction.h"	// TODO: возвращаемое значение

namespace fuura::compilation
{
	class JITCompiler
	{
	public:
		void Compile(ISyntaxTreeContainer& functionToCompile);
		void Compile(ISyntaxTreeContainer& functionToCompile, std::ostream& debugTraceOut);
	};
}