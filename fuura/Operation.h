#pragma once

namespace fuura::language
{
	// ѕолный перечень унарных операций.
	enum class UnaryOperation
	{
		Invert,			// -a
		Not,			// not a
		OPERATION_COUNT // ѕоследний элемент, используетс€ дл€ определени€ количества операций.
	};

	// ѕолный перечень бинарных операций.
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

		OPERATION_COUNT		// ѕоследний элемент, используетс€ дл€ определени€ количества операций.
	};
}