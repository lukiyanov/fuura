#pragma once
#include <memory>
#include <list>
#include <vector>

#include "ICalculatable.h"
#include "FunctionWrapper.h"

namespace fuura::language
{
	// ------------------------------------------------------------------------
	// Вызов функции C++ из fuura-кода.
	// ------------------------------------------------------------------------
	class FunctionCall : public ICalculatable
	{
		std::unique_ptr<IFunctionWrapper> m_function;
		std::list<std::unique_ptr<ICalculatable>> m_arguments;

	public:
		// --------------------------------------------------------------------
		FunctionCall(std::unique_ptr<IFunctionWrapper> function, std::list<std::unique_ptr<ICalculatable>>& arguments)
			: m_function(std::move(function)), m_arguments(std::move(arguments))
		{}

		// --------------------------------------------------------------------
		Value Calculate() const override
		{
			std::vector<Value> args(m_arguments.size());
			int i = 0;
			for (auto iter = m_arguments.begin(), end = m_arguments.end(); iter != end; ++iter)
				args[i++] = (*iter)->Calculate();
			return m_function->Execute(args);
		}

		// --------------------------------------------------------------------
		ValueType GetType() const override
		{
			return m_function->GetResultType();
		}

		// --------------------------------------------------------------------
	};

	// ------------------------------------------------------------------------
}