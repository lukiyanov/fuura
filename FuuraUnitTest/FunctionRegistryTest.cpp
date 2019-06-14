#include "stdafx.h"
#include "CppUnitTest.h"
#include "CppUnitTestAssert.h"
#include <FuuraSemantics.h>
#include <Exception.h>
#include "MockToken.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace fuura::language
{
	TEST_CLASS(FunctionRegistryTest)
	{
		MockToken token;
		enum {
			bool_Foo,
			int_Foo_int,
			double_Foo_int_bool,
			double_Foo_double_bool,
			double_Foo_double_bool_bool,
			double_Foo_double_bool_bool2,
			double_Foo_double_int,
			double_Foo_int_double
		};

		static bool   foo()						{ return bool_Foo; }
		static int    foo(int)					{ return int_Foo_int; }
		static double foo(int, bool)			{ return double_Foo_int_bool; }
		static double foo(double, bool)			{ return double_Foo_double_bool; }
		static double bar1(double, bool, bool)	{ return double_Foo_double_bool_bool; }
		static int    bar2(double, bool, bool)	{ return double_Foo_double_bool_bool2; }
		static double foo(double, int)			{ return double_Foo_double_int; }
		static double foo(int, double)			{ return double_Foo_int_double; }
		static double mul(double a, double b)	{ return a * b; }

		using ArgList = list<unique_ptr<ICalculatable>>;
	public:

		TEST_METHOD(Test_OverloadedFunctionTypeCasting)
		{
			// Тест проверяет корректность приведения типов при перегрузке функций.
			// ----------------------------------------------------------------

			FuuraSemantics semantics;
			auto& functions = semantics.GetFunctionRegistry();
			functions.RegisterFunction<double(double, double)>("mul", &mul);

			{
				ArgList args;
				args.push_back(make_unique<Constant<int>>("123"));
				args.push_back(make_unique<Constant<int>>("456"));
				auto func = functions.CreateFunction("mul", args, semantics, &token);
				Assert::AreEqual(ValueType::Double, func->GetType());
				Assert::AreEqual(double(123) * double(456), double(func->Calculate()));
			}
		}

		TEST_METHOD(Test_FunctionOverloading)
		{
			// Тест демонстрирует правила перегрузки функций.
			// ----------------------------------------------------------------

			FuuraSemantics semantics;
			auto& functions = semantics.GetFunctionRegistry();

			// Перегружаем функцию:
			functions.RegisterFunction<bool()>("fOo", &foo);
			functions.RegisterFunction<int(int)>("FOO", &foo);
			functions.RegisterFunction<double(int, bool)>("fOO", &foo);
			functions.RegisterFunction<double(double, bool)>("fOO", &foo);
			functions.RegisterFunction<double(double, int)>("foo", &foo);
			functions.RegisterFunction<double(int, double)>("foo", &foo);
			functions.RegisterFunction<double(double, bool, bool)>("foo", &bar1);

			// Добавляем несколько других функций:
			functions.RegisterFunction<double(double)>("sin2", &sin);
			functions.RegisterFunction<double(double)>("cos2", &cos);
			functions.RegisterFunction<double(double, double)>("mul2", &mul);

			// Функция с такими аргументами уже зарегистрирована:
			Assert::ExpectException<std::exception>([&functions]() {
				functions.RegisterFunction<int(double, bool, bool)>("foo", &bar2);
			});

			// ----------------------------------------------------------------

			{
				ArgList args = {};
				auto func = functions.CreateFunction("foo", args, semantics, &token);
				// Должны получить функцию bool foo()
				Assert::AreEqual(ValueType::Bool, func->GetType());
				Assert::AreEqual(bool(bool_Foo), bool(func->Calculate()));
			}

			{
				ArgList args;
				args.push_back(make_unique<Constant<int>>("123"));
				auto func = functions.CreateFunction("foo", args, semantics, &token);
				// Должны получить функцию int foo(int)
				Assert::AreEqual(ValueType::Int, func->GetType());
				Assert::AreEqual(int(int_Foo_int), int(func->Calculate()));
			}

			{
				ArgList args;
				args.push_back(make_unique<Constant<int>>("123"));
				args.push_back(make_unique<Constant<bool>>("true"));
				auto func = functions.CreateFunction("foo", args, semantics, &token);
				// Должны получить функцию double foo(int, bool).
				// Хотя есть преобразование в double foo(double, bool),
				// но точное совпадение предпочтительнее.
				Assert::AreEqual(ValueType::Double, func->GetType());
				Assert::AreEqual(double(double_Foo_int_bool), double(func->Calculate()));
			}

			{
				ArgList args;
				args.push_back(make_unique<Constant<double>>("123.4"));
				args.push_back(make_unique<Constant<bool>>("true"));
				auto func = functions.CreateFunction("foo", args, semantics, &token);
				// Должны получить функцию double foo(double, bool).
				Assert::AreEqual(ValueType::Double, func->GetType());
				Assert::AreEqual(double(double_Foo_double_bool), double(func->Calculate()));
			}

			{
				ArgList args;
				args.push_back(make_unique<Constant<double>>("123.4"));
				args.push_back(make_unique<Constant<int>>("-23"));
				auto func = functions.CreateFunction("foo", args, semantics, &token);
				// Должны получить функцию double foo(double, int).
				Assert::AreEqual(ValueType::Double, func->GetType());
				Assert::AreEqual(double(double_Foo_double_int), double(func->Calculate()));
			}

			{
				ArgList args;
				args.push_back(make_unique<Constant<int>>("-23"));
				args.push_back(make_unique<Constant<double>>("123.4"));
				auto func = functions.CreateFunction("foo", args, semantics, &token);
				// Должны получить функцию double foo(int, double).
				Assert::AreEqual(ValueType::Double, func->GetType());
				Assert::AreEqual(double(double_Foo_int_double), double(func->Calculate()));
			}

			{
				ArgList args;
				args.push_back(make_unique<Constant<int>>("123"));
				args.push_back(make_unique<Constant<bool>>("true"));
				args.push_back(make_unique<Constant<bool>>("false"));
				auto func = functions.CreateFunction("foo", args, semantics, &token);
				// Должны получить функцию double foo(double, bool, bool) т.к. int приводится к double.
				Assert::AreEqual(ValueType::Double, func->GetType());
				Assert::AreEqual(double(double_Foo_double_bool_bool), double(func->Calculate()));
			}

			// ----------------------------------------------------------------
			
			// Функция с таким именем не зарегистрирована:
			Assert::ExpectException<SyntaxError>([&functions, &semantics, tok = &token]() {
				ArgList args = {};
				auto func = functions.CreateFunction("unexistentFuncName", args, semantics, tok);
			});

			// Функция с таким числом параметров не зарегистрирована:
			Assert::ExpectException<SyntaxError>([&functions, &semantics, tok = &token]() {
				ArgList args = {};
				args.push_back(make_unique<Constant<int>>("12"));
				args.push_back(make_unique<Constant<int>>("12"));
				args.push_back(make_unique<Constant<int>>("12"));
				args.push_back(make_unique<Constant<int>>("12"));
				args.push_back(make_unique<Constant<int>>("12"));
				auto func = functions.CreateFunction("foo", args, semantics, tok);
			});

			// Функция с такими параметрами не зарегистрирована:
			Assert::ExpectException<SyntaxError>([&functions, &semantics, tok = &token]() {
				ArgList args = {};
				args.push_back(make_unique<Constant<bool>>("true"));
				args.push_back(make_unique<Constant<bool>>("true"));
				auto func = functions.CreateFunction("foo", args, semantics, tok);
			});

			// Неоднозначное соответствие между (int, double) и (double, int):
			Assert::ExpectException<SyntaxError>([&functions, &semantics, tok = &token]() {
				ArgList args = {};
				args.push_back(make_unique<Constant<int>>("123"));
				args.push_back(make_unique<Constant<int>>("123"));
				auto func = functions.CreateFunction("foo", args, semantics, tok);
			});

			// ----------------------------------------------------------------
		}

	};
}