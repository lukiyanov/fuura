#pragma once
#include <string_view>
#include <string>

#include "FunctionSignature.h"

namespace fuura
{
	// ---------------------------------------------------------------------------
	// ������ std::string_view ��� ������ ��� ���������� ������������ �������.
	// �� � ������� �� string_view ����� ����������� ����������� �� ���������,
	// ��� ������ ������������ ����� �������� ����� ���������.
	// ---------------------------------------------------------------------------
	struct ArgumentName
	{
		const std::string_view argName;

	public:
		ArgumentName(const char* name) : argName(name) {}			// ��� ������� ��������������
		ArgumentName(std::string_view name) : argName(name) {}		// ��� ������� ��������������
		ArgumentName(const std::string& name) : argName(name) {}	// ��� ������� ��������������
	};

	// ---------------------------------------------------------------------------
	// ����� ����� ����� ������� �� ����������� ���������� ��� ���������� �
	// ������� MakeFunction. ��� �� ����� ���� ������ ���������� ����������
	// ������� Func (�.�. FunctionSignature<Func>::ArgCount), � ��������� ���� ���
	// � ArgumentName ����������� ����������� �� ���������, �� ����� ���� � ������.
	// ---------------------------------------------------------------------------
	template <int Count> struct ArgumentNameList
	{
		ArgumentName arguments[Count];
	};

	// ---------------------------------------------------------------------------
	template <> struct ArgumentNameList<0>
	{
	};

	// ---------------------------------------------------------------------------
}