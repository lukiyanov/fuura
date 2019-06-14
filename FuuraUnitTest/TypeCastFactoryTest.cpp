#include "stdafx.h"
#include "CppUnitTest.h"
#include "CppUnitTestAssert.h"
#include <Calculatables.h>
#include <FuuraSemantics.h>

// ����������� �����
#include <TypeCastFactory.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace fuura::language
{
	TEST_CLASS(TypeCastFactoryTest)
	{
	public:

		TEST_METHOD(Test_TypeCasts)
		{
			FuuraSemantics semantics;
			TypeCastFactory& typeCastFactory = semantics.GetImplicitTypeCastFactory();

			// �������������� int -> double �� �������� �++
			auto result = typeCastFactory.CreateTypeCast(std::make_unique<Constant<int>>("123"), ValueType::Double);
			Assert::AreEqual(double(123), double(result->Calculate()));

			// ������ �������������� � ����� �����������.
			Assert::IsTrue(nullptr == typeCastFactory.CreateTypeCast(std::make_unique<Constant<int>>("123"), ValueType::Bool));

			Assert::IsTrue(nullptr == typeCastFactory.CreateTypeCast(std::make_unique<Constant<double>>("123.2"), ValueType::Int));
			Assert::IsTrue(nullptr == typeCastFactory.CreateTypeCast(std::make_unique<Constant<double>>("123.2"), ValueType::Bool));

			Assert::IsTrue(nullptr == typeCastFactory.CreateTypeCast(std::make_unique<Constant<bool>>("false"), ValueType::Int));
			Assert::IsTrue(nullptr == typeCastFactory.CreateTypeCast(std::make_unique<Constant<bool>>("false"), ValueType::Double));
		}

	};
}