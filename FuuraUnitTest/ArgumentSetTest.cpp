#include "stdafx.h"
#include "CppUnitTest.h"
#include "CppUnitTestAssert.h"
#include "MockToken.h"

// Тестируемый класс
#include <ArgumentSet.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace fuura::interpretation
{
	TEST_CLASS(ArgumentSetTest)
	{
		MockToken mockToken;
	public:

		TEST_METHOD(Test_InvalidArgumentName)
		{
			const int argCount = 5;
			ArgumentNameList<argCount> argNames =
			{ "int1", "int2", "double3", "bool4", "double5" };

			ArgumentSet<int, int, double, bool, double> args(std::move(argNames));

			// При запросе несуществующего имени получаем синтаксическую ошибку.
			Assert::ExpectException<SyntaxError>([&args]() {
				MockToken mockToken;
				args.GetArgumentInfo("invalidName", &mockToken);
			});
		}

		TEST_METHOD(Test_ArgumentSetting)
		{
			const int argCount = 5;
			ArgumentNameList<argCount> argNames =
				{ "int1", "int2", "double3", "bool4", "double5" };

			ArgumentSet<int, int, double, bool, double> args(std::move(argNames));

			// Проверяем соответствие типов.
			Assert::AreEqual(ValueType::Int,    args.GetArgumentInfo("int1",    &mockToken).type);
			Assert::AreEqual(ValueType::Int,    args.GetArgumentInfo("int2",    &mockToken).type);
			Assert::AreEqual(ValueType::Double, args.GetArgumentInfo("double3", &mockToken).type);
			Assert::AreEqual(ValueType::Bool,   args.GetArgumentInfo("bool4",   &mockToken).type);
			Assert::AreEqual(ValueType::Double, args.GetArgumentInfo("double5", &mockToken).type);

			// Устанавливаем значения.
			args.SetArgumentValues(78, -9, 89.0, true, -9.1);

			// Проверяем что установились верно.
			Assert::AreEqual(78,   args.GetArgumentInfo("int1",    &mockToken).pointerToValue->intValue);
			Assert::AreEqual(-9,   args.GetArgumentInfo("int2",    &mockToken).pointerToValue->intValue);
			Assert::AreEqual(89.0, args.GetArgumentInfo("double3", &mockToken).pointerToValue->doubleValue);
			Assert::AreEqual(true, args.GetArgumentInfo("bool4",   &mockToken).pointerToValue->boolValue);
			Assert::AreEqual(-9.1, args.GetArgumentInfo("double5", &mockToken).pointerToValue->doubleValue);

			// Регистр не имеет значения.
			Assert::AreEqual(78,   args.GetArgumentInfo("Int1",    &mockToken).pointerToValue->intValue);
			Assert::AreEqual(-9,   args.GetArgumentInfo("iNt2",    &mockToken).pointerToValue->intValue);
			Assert::AreEqual(89.0, args.GetArgumentInfo("doUble3", &mockToken).pointerToValue->doubleValue);
			Assert::AreEqual(true, args.GetArgumentInfo("BOOL4",   &mockToken).pointerToValue->boolValue);
			Assert::AreEqual(-9.1, args.GetArgumentInfo("dOuble5", &mockToken).pointerToValue->doubleValue);
		}

		TEST_METHOD(Test_Move)
		{
			auto func = []() {
				const int argCount = 5;
				ArgumentNameList<argCount> argNames =
				{ "int1", "int2", "double3", "bool4", "double5" };

				ArgumentSet<int, int, double, bool, double> args(std::move(argNames));
				args.SetArgumentValues(78, -9, 89.0, true, -9.1);

				return args;
			};

			auto args = func();

			Assert::AreEqual(78,   args.GetArgumentInfo("int1",    &mockToken).pointerToValue->intValue);
			Assert::AreEqual(-9,   args.GetArgumentInfo("int2",    &mockToken).pointerToValue->intValue);
			Assert::AreEqual(89.0, args.GetArgumentInfo("double3", &mockToken).pointerToValue->doubleValue);
			Assert::AreEqual(true, args.GetArgumentInfo("bool4",   &mockToken).pointerToValue->boolValue);
			Assert::AreEqual(-9.1, args.GetArgumentInfo("double5", &mockToken).pointerToValue->doubleValue);
		}

	};
}