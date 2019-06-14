#include "stdafx.h"
#include "CppUnitTest.h"
#include "CppUnitTestAssert.h"
#include <vector>

// Тестируемый класс
#include <FunctionWrapper.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace fuura::language
{
	TEST_CLASS(FunctionWrapperTest)
	{
		static double foo(int c, bool, double, int) { return 123 + c; }

	public:

		TEST_METHOD(Test_FunctionWrapper)
		{
			FunctionWrapper<double(int, bool, double, int)> wrapperRealization(&foo);
			IFunctionWrapper& wrapper = wrapperRealization;

			// Проверка типа возвращаемого значения.
			Assert::AreEqual(ValueType::Double, wrapper.GetResultType());

			// Проверка типов аргументов.
			auto argTypes = wrapper.GetArgumentTypes();
			Assert::AreEqual(4u, argTypes.size());
			Assert::AreEqual(ValueType::Int,    argTypes[0]);
			Assert::AreEqual(ValueType::Bool,   argTypes[1]);
			Assert::AreEqual(ValueType::Double, argTypes[2]);
			Assert::AreEqual(ValueType::Int,    argTypes[3]);

			// Вызов функции и проверка результата.
			std::vector<Value> args = { -120, true, 1.0, 0 };
			double expected = 123 - 120;
			double actual = wrapper.Execute(args);
			Assert::AreEqual(expected, actual);

			// Меньше параметров -> ошибка
			Assert::ExpectException<std::out_of_range>([&wrapper]() {
				std::vector<Value> args = { -120, true };
				wrapper.Execute(args);
			});

			// Больше параметров -> ошибка
			Assert::ExpectException<std::out_of_range>([&wrapper]() {
				std::vector<Value> args = { -120, true, 1.0, 1, 2 };
				wrapper.Execute(args);
			});
		}

	};
}