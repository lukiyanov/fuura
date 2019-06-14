#pragma once

#include "CppUnitTest.h"
#include "CppUnitTestAssert.h"
#include <Value.h>
#include <Operation.h>

namespace Microsoft::VisualStudio::CppUnitTestFramework
{
	template<> inline std::wstring ToString<fuura::ValueType>(const fuura::ValueType& t) { RETURN_WIDE_STRING((int)t); }
	template<> inline std::wstring ToString<fuura::language::UnaryOperation> (const fuura::language::UnaryOperation& t) { RETURN_WIDE_STRING((int)t); }
	template<> inline std::wstring ToString<fuura::language::BinaryOperation>(const fuura::language::BinaryOperation& t) { RETURN_WIDE_STRING((int)t); }
}