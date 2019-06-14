#pragma once
#include "Value.h"

namespace fuura {
	namespace tools
	{
		// ---------------------------------------------------------------------------
		// ��������� ���������������� ValueType �� ���� �++.
		template <typename T> inline fuura::ValueType GetValueType()
		{
			static_assert(false, "������� ���������� ������������� GetValueType<Q> ��� ������� ������.");
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