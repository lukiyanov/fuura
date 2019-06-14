#include "stdafx.h"
#include "FunctionCall.h"
#include "Exception.h"
using namespace std;
using namespace fuura;
//using namespace fuura::language;

// ----------------------------------------------------------------------------
	/*
FunctionCall::FunctionCall(
	string_view								  functionName,
	std::list<std::unique_ptr<ICalculatable>> arguments,
	FuuraSemantics&							  semantics,
	antlr4::Token *                           tokenInfo)
: m_arguments(move(arguments))
{
	list<ValueType> argTypes;
	for (auto argument = arguments.begin(), end = arguments.end(); argument != end; ++argument)
		argTypes.push_back((*argument)->GetType());

	m_function = semantics.GetFunctionRegistry().GetFunction(functionName, argTypes);

	if (!m_function)
	{
		throw SyntaxError(std::string("Вызов неизвестной функции ") + functionName.data(),
			tokenInfo->getLine(), tokenInfo->getCharPositionInLine());
}
	}*/

// ----------------------------------------------------------------------------