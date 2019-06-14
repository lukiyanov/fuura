#include "stdafx.h"
#include "CppUnitTest.h"
#include "CppUnitTestAssert.h"

// Тестируемый файл
#include <FunctionSignature.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace fuura::tools
{
	TEST_CLASS(FunctionSignatureTest)
	{
	public:

		TEST_METHOD(Test_FunctionSignature)
		{
			using T = double(int, bool, double, int);
			
			// Результат
			Assert::AreEqual(ValueType::Double, GetValueType<FunctionSignature<T>::Result>());
			// Число аргументов
			Assert::AreEqual(4, int(FunctionSignature<T>::ArgCount));
			// Сами аргументы
			Assert::AreEqual(ValueType::Int,    FunctionSignature<T>::GetArgumentType(0));
			Assert::AreEqual(ValueType::Bool,   FunctionSignature<T>::GetArgumentType(1));
			Assert::AreEqual(ValueType::Double, FunctionSignature<T>::GetArgumentType(2));
			Assert::AreEqual(ValueType::Int,    FunctionSignature<T>::GetArgumentType(3));
		}
	};
}