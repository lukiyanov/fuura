#include "stdafx.h"
#include "CppUnitTest.h"
#include "CppUnitTestAssert.h"

// Тестируемый файл
#include <ToString.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace fuura::language;

namespace fuura::tools
{
	TEST_CLASS(ToStringTest)
	{
	public:

		// --------------------------------------------------------------------
		TEST_METHOD(Test_ToString_Int)
		{
			Assert::AreEqual(std::string("-1234567"), ToString(-1234567));
		}

		// --------------------------------------------------------------------
		TEST_METHOD(Test_ToString_Bool)
		{
			Assert::AreEqual(std::string("true"),  ToString(true));
			Assert::AreEqual(std::string("false"), ToString(false));
		}

		// --------------------------------------------------------------------
		TEST_METHOD(Test_ToString_ValueType)
		{
			auto count = static_cast<int>(ValueType::TYPE_COUNT);

			// Не должно возникнуть исключений. Конкретные значения не важны.
			// Почему так? Потому, что если мы добавим новый тип и не напишем для него преобразование в строку,
			// то этот тест не будент пройден.
			for (int i = 0; i < count; i++)
				ToString(static_cast<ValueType>(i));
			
			// Должно возникнуть исключение при выходе за границы.
			Assert::ExpectException<std::out_of_range>(
				[count]() { ToString(ValueType::TYPE_COUNT); }
			);
		}

		// --------------------------------------------------------------------
		TEST_METHOD(Test_ToString_UnaryOperation)
		{
			auto count = static_cast<int>(UnaryOperation::OPERATION_COUNT);

			// Не должно возникнуть исключений. Конкретные значения не важны.
			for (int i = 0; i < count; i++)
				ToString(static_cast<UnaryOperation>(i));

			// Должно возникнуть исключение при выходе за границы.
			Assert::ExpectException<std::out_of_range>(
				[count]() { ToString(UnaryOperation::OPERATION_COUNT); }
			);
		}

		// --------------------------------------------------------------------
		TEST_METHOD(Test_ToString_BinaryOperation)
		{
			auto count = static_cast<int>(BinaryOperation::OPERATION_COUNT);

			// Не должно возникнуть исключений. Конкретные значения не важны.
			for (int i = 0; i < count; i++)
				ToString(static_cast<BinaryOperation>(i));

			// Должно возникнуть исключение при выходе за границы.
			Assert::ExpectException<std::out_of_range>(
				[count]() { ToString(BinaryOperation::OPERATION_COUNT); }
			);
		}

		// --------------------------------------------------------------------
	};
}