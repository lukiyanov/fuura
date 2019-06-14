#include "stdafx.h"
#include "CppUnitTest.h"
#include "CppUnitTestAssert.h"

// Тестируемый класс
#include <Convert.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace fuura::tools
{
	TEST_CLASS(ConvertTest)
	{
	public:

		TEST_METHOD(Test_ToLower)
		{
			std::string str("abcdefghijklmnopq r \nstuvwx y z 0123456789 _");
			Assert::AreEqual(str, ToLower("AbCdEFghIjklMnOPQ R \nsTuvWx y z 0123456789 _"));
		}

		TEST_METHOD(Test_StrToTypeInt)
		{
			Assert::AreEqual(12345, StrToType<int>("12345"));
			Assert::AreEqual(-12345, StrToType<int>("-12345"));
		}

		TEST_METHOD(Test_StrToTypeDouble)
		{
			Assert::AreEqual(12345.678, StrToType<double>("12345.678"));
			Assert::AreEqual(-12345.678, StrToType<double>("-12345.678"));
		}

		TEST_METHOD(Test_StrToTypeBool)
		{
			Assert::AreEqual(true,  StrToType<bool>("true"));
			Assert::AreEqual(false, StrToType<bool>("false"));
		}
	};
}