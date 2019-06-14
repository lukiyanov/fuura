#include "stdafx.h"
#include "CppUnitTest.h"
#include "CppUnitTestAssert.h"

// Тестируемый класс
#include <Translator.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace fuura::interpretation
{
	TEST_CLASS(TranslatorTest)
	{
	public:

		TEST_METHOD(Test_SyntaxError)
		{
			fuura::Translator translator;

			// Различные синтаксические ошибки.
			// TODO: побольше их.

			Assert::ExpectException<SyntaxError>([&translator]() {
				auto func = translator.MakeFunction<int()>({}, "12-");
			});
			Assert::ExpectException<SyntaxError>([&translator]() {
				auto func = translator.MakeFunction<int()>({}, "-true");
			});
			Assert::ExpectException<SyntaxError>([&translator]() {
				auto func = translator.MakeFunction<int()>({}, "(23");
			});
			Assert::ExpectException<SyntaxError>([&translator]() {
				auto func = translator.MakeFunction<int()>({}, "");
			});
		}

		TEST_METHOD(Test_RetValueIntToDouble)
		{
			fuura::Translator translator;

			// Если существует преобразование из реально возвращаемого типа в требуемый,
			// то ошибки не происходит.
			// Например, если функция объявлена как double, то она вполне может
			// возвращать и int, который будет преобразован к double.
			auto func = translator.MakeFunction<double()>({}, "12");

			Assert::AreEqual(12., func());
		}

		TEST_METHOD(Test_FunctionResultTypeMismatch)
		{
			fuura::Translator translator;

			// Заявленный тип результата функции и реально получаемый должны совпадать,
			// если не существует неявного преобразования от получанного типа к ожидаемому.
			// В примерах ниже такое преобразование отсутствует.

			// Ожидается int, получено bool
			Assert::ExpectException<SyntaxError>([&translator]() {
				auto func = translator.MakeFunction<int()>({}, "true");
			});

			// Ожидается int, получено double
			Assert::ExpectException<SyntaxError>([&translator]() {
				auto func = translator.MakeFunction<int()>({}, "12.0");
			});

			// Ожидается bool, получено int
			Assert::ExpectException<SyntaxError>([&translator]() {
				auto func = translator.MakeFunction<bool()>({}, "12");
			});

			// Ожидается bool, получено double
			Assert::ExpectException<SyntaxError>([&translator]() {
				auto func = translator.MakeFunction<bool()>({}, "12.0");
			});

			// Ожидается double, получено bool
			Assert::ExpectException<SyntaxError>([&translator]() {
				auto func = translator.MakeFunction<double()>({}, "true");
			});
		}

		TEST_METHOD(Test_ParsingAndExecution)
		{
			fuura::Translator translator;
			auto source = "if(x < 2)(x + 3*(y)) * 2 else 0.2 / y;";
			auto valid = [](int x, double y) -> double {
				if (x < 2) return (x + 3 * (y)) * 2;
				else return 0.2 / y;
			};

			auto func = translator.MakeFunction<double(int, double)>({ "x", "y" }, source);
			Assert::AreEqual(valid(123, -11),     func(123, -11));
			Assert::AreEqual(valid(123, -123.45), func(123, -123.45));
			Assert::AreEqual(valid(1,   -11),     func(1, -11));

			std::function<double(int, double)> f = func;
			Assert::AreEqual(valid(101, 0.02), f(101, 0.02));
		}

		TEST_METHOD(Test_FunctionDirectAssign)
		{
			auto generate = []() {
				auto source = "if(x < 2)(x + 3*(y)) * 2 else 0.2 / y;";
				fuura::Translator translator;
				std::function<double(int, double)> func = translator.MakeFunction<double(int, double)>({ "x", "y" }, source);
				return func;
			};

			auto valid = [](int x, double y) -> double {
				if (x < 2) return (x + 3 * (y)) * 2;
				else return 0.2 / y;
			};

			auto func = generate();
			Assert::AreEqual(valid(123, -11),     func(123, -11));
			Assert::AreEqual(valid(123, -123.45), func(123, -123.45));
			Assert::AreEqual(valid(1,   -11),     func(1, -11));
		}

	};
}