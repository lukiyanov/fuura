#pragma once
#include "Value.h"

namespace fuura {
	namespace tools
	{
		// ---------------------------------------------------------------------------
		// Получение соответствующего ValueType по типу С++.
		template <typename T> inline fuura::ValueType GetValueType()
		{
			static_assert(false, "Следует определить специализацию GetValueType<Q> для данного класса.");
		}

		// ---------------------------------------------------------------------------
		template <> constexpr inline fuura::ValueType GetValueType<int>()
		{
			return fuura::ValueType::Int;
		}

		// ---------------------------------------------------------------------------
		template <> constexpr inline fuura::ValueType GetValueType<double>()
		{
			return fuura::ValueType::Double;
		}

		// ---------------------------------------------------------------------------
		template <> constexpr inline fuura::ValueType GetValueType<bool>()
		{
			return fuura::ValueType::Bool;
		}

		// ---------------------------------------------------------------------------
	}
}