#include "stdafx.h"
#include "CppUnitTest.h"
#include "CppUnitTestAssert.h"

// Тестируемый файл
#include <GetValueType.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace fuura::tools
{
	TEST_CLASS(GetValueTypeTest)
	{
	public:

		TEST_METHOD(Test_GetValueType)
		{
			Assert::AreEqual(ValueType::Int,    GetValueType<int>());
			Assert::AreEqual(ValueType::Double, GetValueType<double>());
			Assert::AreEqual(ValueType::Bool,   GetValueType<bool>());
		}
	};
}