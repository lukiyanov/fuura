#pragma once
#include "Value.h"

namespace fuura::tools
{
	// ��������� ���������������� �++ ���� �� �������� ������������ ValueType.
	// ---------------------------------------------------------------------------
	template <ValueType v> struct GetCppType
	{
		using type = void;
	};

	// ---------------------------------------------------------------------------
	template <> struct GetCppType<ValueType::Int>
	{
		using type = int;
	};

	// ---------------------------------------------------------------------------
	template <> struct GetCppType<ValueType::Bool>
	{
		using type = bool;
	};

	// ---------------------------------------------------------------------------
	template <> struct GetCppType<ValueType::Double>
	{
		using type = double;
	};

	// ---------------------------------------------------------------------------
}