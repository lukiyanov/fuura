#include "stdafx.h"
#include "CppUnitTest.h"
#include "CppUnitTestAssert.h"

// ����������� ����
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

			// �� ������ ���������� ����������. ���������� �������� �� �����.
			// ������ ���? ������, ��� ���� �� ������� ����� ��� � �� ������� ��� ���� �������������� � ������,
			// �� ���� ���� �� ������ �������.
			for (int i = 0; i < count; i++)
				ToString(static_cast<ValueType>(i));
			
			// ������ ���������� ���������� ��� ������ �� �������.
			Assert::ExpectException<std::out_of_range>(
				[count]() { ToString(ValueType::TYPE_COUNT); }
			);
		}

		// --------------------------------------------------------------------
		TEST_METHOD(Test_ToString_UnaryOperation)
		{
			auto count = static_cast<int>(UnaryOperation::OPERATION_COUNT);

			// �� ������ ���������� ����������. ���������� �������� �� �����.
			for (int i = 0; i < count; i++)
				ToString(static_cast<UnaryOperation>(i));

			// ������ ���������� ���������� ��� ������ �� �������.
			Assert::ExpectException<std::out_of_range>(
				[count]() { ToString(UnaryOperation::OPERATION_COUNT); }
			);
		}

		// --------------------------------------------------------------------
		TEST_METHOD(Test_ToString_BinaryOperation)
		{
			auto count = static_cast<int>(BinaryOperation::OPERATION_COUNT);

			// �� ������ ���������� ����������. ���������� �������� �� �����.
			for (int i = 0; i < count; i++)
				ToString(static_cast<BinaryOperation>(i));

			// ������ ���������� ���������� ��� ������ �� �������.
			Assert::ExpectException<std::out_of_range>(
				[count]() { ToString(BinaryOperation::OPERATION_COUNT); }
			);
		}

		// --------------------------------------------------------------------
	};
}