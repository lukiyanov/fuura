#include "stdafx.h"
#include "CppUnitTest.h"
#include "CppUnitTestAssert.h"

// Тестируемый класс
#include <Value.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace fuura::interpretation
{
	TEST_CLASS(ValueTest)
	{
	public:

		TEST_METHOD(Test_SetGetInt)
		{
			Value value = 123;
			Assert::AreEqual(123, int(value));
			value = 234;
			Assert::AreEqual(234, int(value));
		}

		TEST_METHOD(Test_SetGetDouble)
		{
			Value value = 123.0;
			Assert::AreEqual(123.0, double(value));
			value = 234.0;
			Assert::AreEqual(234.0, double(value));
		}

		TEST_METHOD(Test_SetGetBool)
		{
			Value value = true;
			Assert::AreEqual(true, bool(value));
			value = false;
			Assert::AreEqual(false, bool(value));
		}
	};
}