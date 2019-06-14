#pragma once

namespace fuura::language
{
	// ������ �������� ������� ��������.
	enum class UnaryOperation
	{
		Invert,			// -a
		Not,			// not a
		OPERATION_COUNT // ��������� �������, ������������ ��� ����������� ���������� ��������.
	};

	// ������ �������� �������� ��������.
	enum class BinaryOperation
	{
		Add,				// +
		Subtract,			// -
		Multiply,			// *
		RealDivide,			// /
		IntegerDivide,		// div
		GetDivRemainder,	// %
		RaiseToPower,		// ^

		Equal,				// =
		NotEqual,			// !=
		Greater,			// >
		Less,				// <
		GreaterOrEqual,		// >=
		LessOrEqual,		// <=

		Or,					// or
		And,				// and

		OPERATION_COUNT		// ��������� �������, ������������ ��� ����������� ���������� ��������.
	};
}