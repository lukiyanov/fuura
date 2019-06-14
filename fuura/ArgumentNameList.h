#pragma once
#include <string_view>
#include <string>

#include "FunctionSignature.h"

namespace fuura
{
	// ---------------------------------------------------------------------------
	// «амена std::string_view дл€ списка имЄн аргументов генерируемой функции.
	// Ќо в отличие от string_view здесь отсутствует конструктор по умолчанию,
	// что делает об€зательным €вное указание имени аргумента.
	// ---------------------------------------------------------------------------
	struct ArgumentName
	{
		const std::string_view argName;

	public:
		ArgumentName(const char* name) : argName(name) {}			// дл€ не€вных преобразований
		ArgumentName(std::string_view name) : argName(name) {}		// дл€ не€вных преобразований
		ArgumentName(const std::string& name) : argName(name) {}	// дл€ не€вных преобразований
	};

	// ---------------------------------------------------------------------------
	//  ласс нужен чтобы следить за количеством переданных имЄн аргументов в
	// функцию MakeFunction. ќно не может быть больше количества аргументов
	// функции Func (т.е. FunctionSignature<Func>::ArgCount), а благодар€ тому что
	// у ArgumentName отсутствует конструктор по умолчанию, не может быть и меньше.
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