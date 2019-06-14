#pragma once
#include "ICalculatable.h"

namespace fuura::compilation
{
	class ISyntaxTreeContainer
	{
	public:
		virtual ~ISyntaxTreeContainer() = default;

		virtual language::ICalculatable* GetSyntaxTree() = 0;
	};
}