#pragma once
#include <memory>
#include "ICalculatable.h"
#include "GetValueType.h"

namespace fuura::language
{
	// ------------------------------------------------------------------------
	// Преобразование из типа T1 в тип T2 по правилам языка С++.
	// what должен иметь тип T1.
	// ------------------------------------------------------------------------
	template <typename T1, typename T2>
	class CppTypeCast : public ICalculatable
	{
		std::unique_ptr<ICalculatable> m_what;
	public:
		CppTypeCast(std::unique_ptr<ICalculatable> what)
			: m_what(std::move(what))
		{
		}

		Value Calculate() const override
		{
			const T1 before = m_what->Calculate();
			const T2 after = before;
			return after;
		}

		ValueType GetType() const override
		{
			return fuura::tools::GetValueType<T2>();
		}
	};

	// ------------------------------------------------------------------------
}