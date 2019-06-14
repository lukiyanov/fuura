#include "stdafx.h"
#include "CppUnitTest.h"
#include "CppUnitTestAssert.h"

#include <Exception.h>
#include <ToString.h>
#include <GetValueType.h>
#include <FuuraSemantics.h>
#include "MockToken.h"

// Тестируемые файлы
#include <OperationFactory.h>
#include <Calculatables.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

// Get<Unary/Binary>OpTable объявлены как [[deprecated]] чтобы не использовать их нигде кроме тестов.
// Мы используем их в тесте, поэтому глушим предупреждение.
#pragma warning (push)
#pragma warning (disable:4996)

namespace fuura::language
{
	TEST_CLASS(OperationFactoryTest)
	{
		MockToken mockToken;
		FuuraSemantics semantics;

	public:

		TEST_METHOD(Test_CheckUnaryOperationIDs)
		{
			auto& factory = semantics.GetOperationFactory();
			auto count = static_cast<int>(UnaryOperation::OPERATION_COUNT);

			// Каждая фабрика для конкретной операции должна правильно понимать,
			// какую операцию она реализует.
			for (int i = 0; i < count; i++)
			{
				auto operation = static_cast<UnaryOperation>(i);
				auto& table = factory.GetUnaryOpTable(operation);
				Assert::AreEqual(table.GetOperation(), operation);
			}
		}

		TEST_METHOD(Test_CheckBinaryOperationIDs)
		{
			auto& factory = semantics.GetOperationFactory();
			auto count = static_cast<int>(BinaryOperation::OPERATION_COUNT);

			// Каждая фабрика для конкретной операции должна правильно понимать,
			// какую операцию она реализует.
			for (int i = 0; i < count; i++)
			{
				auto operation = static_cast<BinaryOperation>(i);
				auto& table = factory.GetBinaryOpTable(operation);
				Assert::AreEqual(table.GetOperation(), operation);
			}
		}

		TEST_METHOD(Test_InvalidOperationParams)
		{
			auto& factory = semantics.GetOperationFactory();

			Assert::ExpectException<SyntaxError>([&]() {
				factory.CreateUnaryOperation(UnaryOperation::Invert, std::make_unique<Constant<bool>>("true"), &mockToken);
			});

			Assert::ExpectException<SyntaxError>([&]() {
				factory.CreateUnaryOperation(UnaryOperation::Not, std::make_unique<Constant<int>>("321"), &mockToken);
			});

			Assert::ExpectException<SyntaxError>([&]() {
				factory.CreateBinaryOperation(BinaryOperation::Add, std::make_unique<Constant<int>>("321"), std::make_unique<Constant<bool>>("false"), &mockToken);
			});

			Assert::ExpectException<SyntaxError>([&]() {
				factory.CreateBinaryOperation(BinaryOperation::LessOrEqual, std::make_unique<Constant<int>>("321"), std::make_unique<Constant<bool>>("false"), &mockToken);
			});

			Assert::ExpectException<SyntaxError>([&]() {
				factory.CreateBinaryOperation(BinaryOperation::Or, std::make_unique<Constant<int>>("321"), std::make_unique<Constant<bool>>("false"), &mockToken);
			});
		}

		TEST_METHOD(Test_UnaryOperations)
		{
			auto& factory = semantics.GetOperationFactory();
			{
				auto result = factory.CreateUnaryOperation(UnaryOperation::Not, std::make_unique<Constant<bool>>("true"), &mockToken);
				Assert::AreEqual(ValueType::Bool, result->GetType());
				Assert::AreEqual(false, bool(result->Calculate()));
			}

			{
				auto result = factory.CreateUnaryOperation(UnaryOperation::Invert, std::make_unique<Constant<int>>("321"), &mockToken);
				Assert::AreEqual(ValueType::Int, result->GetType());
				Assert::AreEqual(-321, int(result->Calculate()));
			}

			{
				auto result = factory.CreateUnaryOperation(UnaryOperation::Invert, std::make_unique<Constant<double>>("43.21"), &mockToken);
				Assert::AreEqual(ValueType::Double, result->GetType());
				Assert::AreEqual(-43.21, double(result->Calculate()));
			}
		}

		TEST_METHOD(Test_AddOperation)
		{
			TestBinaryOperation(BinaryOperation::Add, 321,  100,  321 + 100);
			TestBinaryOperation(BinaryOperation::Add, -123, 100,  -123 + 100);
			TestBinaryOperation(BinaryOperation::Add, -123, -100, -123 - 100);
			TestBinaryOperation(BinaryOperation::Add, 0,    200,  0 + 200);
			TestBinaryOperation(BinaryOperation::Add, 0,    0,    0 + 0);

			TestBinaryOperation(BinaryOperation::Add, 321,  100.0,  321 + 100.0);
			TestBinaryOperation(BinaryOperation::Add, -123.0, 100,  -123.0 + 100);
			TestBinaryOperation(BinaryOperation::Add, -123.12, -100.3, -123.12 - 100.3);
			TestBinaryOperation(BinaryOperation::Add, 0,    200.0,  0 + 200.0);
			TestBinaryOperation(BinaryOperation::Add, 0,    0.0,    0 + 0.0);
		}

		TEST_METHOD(Test_SubtractOperation)
		{
			TestBinaryOperation(BinaryOperation::Subtract, 321,  100,  321 - 100);
			TestBinaryOperation(BinaryOperation::Subtract, -123, 100,  -123 - 100);
			TestBinaryOperation(BinaryOperation::Subtract, -123, -100, -123 - (-100));
			TestBinaryOperation(BinaryOperation::Subtract, 0,    200,  0 - 200);
			TestBinaryOperation(BinaryOperation::Subtract, 0,    0,    0 - 0);

			TestBinaryOperation(BinaryOperation::Subtract, 321,     100.0,  321 - 100.0);
			TestBinaryOperation(BinaryOperation::Subtract, -123.0,  100,    -123.0 - 100);
			TestBinaryOperation(BinaryOperation::Subtract, -123.12, -100.3, -123.12 - -100.3);
			TestBinaryOperation(BinaryOperation::Subtract, 0,       200.0,  0 - 200.0);
			TestBinaryOperation(BinaryOperation::Subtract, 0,       0.0,    0 - 0.0);
		}
			
		TEST_METHOD(Test_MultiplyOperation)
		{
			TestBinaryOperation(BinaryOperation::Multiply, 321,  100,  321 * 100);
			TestBinaryOperation(BinaryOperation::Multiply, -123, 100,  -123 * 100);
			TestBinaryOperation(BinaryOperation::Multiply, -123, -100, -123 * (-100));
			TestBinaryOperation(BinaryOperation::Multiply, 0,    200,  0 * 200);
			TestBinaryOperation(BinaryOperation::Multiply, 0,    0,    0 * 0);

			TestBinaryOperation(BinaryOperation::Multiply, 321,    100.2,  321 * 100.2);
			TestBinaryOperation(BinaryOperation::Multiply, -123.3, 100,    -123.3 * 100);
			TestBinaryOperation(BinaryOperation::Multiply, -123.2, -100,   -123.2 * (-100));
			TestBinaryOperation(BinaryOperation::Multiply, 0.2,    200.2,  0.2 * 200.2);
			TestBinaryOperation(BinaryOperation::Multiply, 0.0,    200,    0.0 * 200);
		}

		TEST_METHOD(Test_RealDivideOperation)
		{
			TestBinaryOperation(BinaryOperation::RealDivide, 321,    100,  321.0 / 100);
			TestBinaryOperation(BinaryOperation::RealDivide, -123.2, 100,  -123.2 / 100);
			TestBinaryOperation(BinaryOperation::RealDivide, -123,   -100, -123.0 / (-100));
			TestBinaryOperation(BinaryOperation::RealDivide, 0,      200,  0.0 / 200);
		}

		TEST_METHOD(Test_IntegerDivideOperation)
		{
			TestBinaryOperation(BinaryOperation::IntegerDivide, 321,  100,  321 / 100);
			TestBinaryOperation(BinaryOperation::IntegerDivide, -123, 100,  -123 / 100);
			TestBinaryOperation(BinaryOperation::IntegerDivide, -123, -100, -123 / (-100));
			TestBinaryOperation(BinaryOperation::IntegerDivide, 0,    200,  0 / 200);
		}

		TEST_METHOD(Test_GetDivRemainderOperation)
		{
			TestBinaryOperation(BinaryOperation::GetDivRemainder, 321,  100,  321 % 100);
			TestBinaryOperation(BinaryOperation::GetDivRemainder, -123, 100,  -123 % 100);
			TestBinaryOperation(BinaryOperation::GetDivRemainder, -123, -100, -123 % (-100));
			TestBinaryOperation(BinaryOperation::GetDivRemainder, 0,    200,  0 % 200);
		}

		TEST_METHOD(Test_RaiseToPowerOperation)
		{
			TestBinaryOperation(BinaryOperation::RaiseToPower, 1.1,  100,  double(std::pow(1.1, 100)));
			TestBinaryOperation(BinaryOperation::RaiseToPower, -12,  4,    double(std::pow(-12, 4)));
			TestBinaryOperation(BinaryOperation::RaiseToPower, -12,  -4,   double(std::pow(-12, -4)));
			TestBinaryOperation(BinaryOperation::RaiseToPower, 0,    20,   double(std::pow(0, 20)));
			TestBinaryOperation(BinaryOperation::RaiseToPower, 0,    0,    double(std::pow(0, 0)));

			TestBinaryOperation(BinaryOperation::RaiseToPower, 1.1,   10, double(std::pow(1.1, 10)));
			TestBinaryOperation(BinaryOperation::RaiseToPower, -12.1, 4,  double(std::pow(-12.1, 4)));
			TestBinaryOperation(BinaryOperation::RaiseToPower, -12.1, -4, double(std::pow(-12.1, -4)));
			TestBinaryOperation(BinaryOperation::RaiseToPower, 0.0,   20, double(std::pow(0.0, 20)));
			TestBinaryOperation(BinaryOperation::RaiseToPower, 0.0,   0,  double(std::pow(0.0, 0)));

			TestBinaryOperation(BinaryOperation::RaiseToPower, 12.1, 4.1,  double(std::pow(12.1, 4.1)));
			TestBinaryOperation(BinaryOperation::RaiseToPower, 12.1, -4.1, double(std::pow(12.1, -4.1)));
		}

		TEST_METHOD(Test_EqualOperation)
		{
			TestBinaryOperation(BinaryOperation::Equal, 321,  100,  321 == 100);
			TestBinaryOperation(BinaryOperation::Equal, -123, 100,  -123 == 100);
			TestBinaryOperation(BinaryOperation::Equal, -123, -123, -123 == -123);
			TestBinaryOperation(BinaryOperation::Equal, 0,    200,  0 == 200);
			TestBinaryOperation(BinaryOperation::Equal, 0,    0,    0 == 0);

			TestBinaryOperation(BinaryOperation::Equal, 321,    100.1,  321 == 100.1);
			TestBinaryOperation(BinaryOperation::Equal, -123.2, 100,    -123.2 == 100);
			TestBinaryOperation(BinaryOperation::Equal, -123.2, -123.2, -123.2 == -123.2);
			TestBinaryOperation(BinaryOperation::Equal, -123,   -123.2, -123 == -123.2);
			TestBinaryOperation(BinaryOperation::Equal, 0,      200.2,  0 == 200.2);
			TestBinaryOperation(BinaryOperation::Equal, 0.0,    0.0,    0.0 == 0.0);
		}

		TEST_METHOD(Test_NotEqualOperation)
		{
			TestBinaryOperation(BinaryOperation::NotEqual, 321,  100,  321 != 100);
			TestBinaryOperation(BinaryOperation::NotEqual, -123, 100,  -123 != 100);
			TestBinaryOperation(BinaryOperation::NotEqual, -123, -123, -123 != -123);
			TestBinaryOperation(BinaryOperation::NotEqual, 0,    200,  0 != 200);
			TestBinaryOperation(BinaryOperation::NotEqual, 0,    0,    0 != 0);

			TestBinaryOperation(BinaryOperation::NotEqual, 321,    100.1,  321 != 100.1);
			TestBinaryOperation(BinaryOperation::NotEqual, -123.2, 100,    -123.2 != 100);
			TestBinaryOperation(BinaryOperation::NotEqual, -123.2, -123.2, -123.2 != -123.2);
			TestBinaryOperation(BinaryOperation::NotEqual, -123,   -123.2, -123 != -123.2);
			TestBinaryOperation(BinaryOperation::NotEqual, 0,      200.2,  0 != 200.2);
			TestBinaryOperation(BinaryOperation::NotEqual, 0.0,    0.0,    0.0 != 0.0);
		}

		TEST_METHOD(Test_LessOperation)
		{
			TestBinaryOperation(BinaryOperation::Less, 321,  100,  321 < 100);
			TestBinaryOperation(BinaryOperation::Less, -123, 100,  -123 < 100);
			TestBinaryOperation(BinaryOperation::Less, -123, -123, -123 < -123);
			TestBinaryOperation(BinaryOperation::Less, 0,    200,  0 < 200);
			TestBinaryOperation(BinaryOperation::Less, 0,    0,    0 < 0);

			TestBinaryOperation(BinaryOperation::Less, 321,    100.1,  321 < 100.1);
			TestBinaryOperation(BinaryOperation::Less, -123.2, 100,    -123.2 < 100);
			TestBinaryOperation(BinaryOperation::Less, -123.2, -123.2, -123.2 < -123.2);
			TestBinaryOperation(BinaryOperation::Less, -123,   -123.2, -123 < -123.2);
			TestBinaryOperation(BinaryOperation::Less, 0,      200.2,  0 < 200.2);
			TestBinaryOperation(BinaryOperation::Less, 0.0,    0.0,    0.0 < 0.0);
		}

		TEST_METHOD(Test_GreaterOperation)
		{
			TestBinaryOperation(BinaryOperation::Greater, 321,  100,  321 > 100);
			TestBinaryOperation(BinaryOperation::Greater, -123, 100,  -123 > 100);
			TestBinaryOperation(BinaryOperation::Greater, -123, -123, -123 > -123);
			TestBinaryOperation(BinaryOperation::Greater, 0,    200,  0 > 200);
			TestBinaryOperation(BinaryOperation::Greater, 0,    0,    0 > 0);

			TestBinaryOperation(BinaryOperation::Greater, 321,    100.1,  321 > 100.1);
			TestBinaryOperation(BinaryOperation::Greater, -123.2, 100,    -123.2 > 100);
			TestBinaryOperation(BinaryOperation::Greater, -123.2, -123.2, -123.2 > -123.2);
			TestBinaryOperation(BinaryOperation::Greater, -123,   -123.2, -123 > -123.2);
			TestBinaryOperation(BinaryOperation::Greater, 0,      200.2,  0 > 200.2);
			TestBinaryOperation(BinaryOperation::Greater, 0.0,    0.0,    0.0 > 0.0);
		}

		TEST_METHOD(Test_GreaterOrEqualOperation)
		{
			TestBinaryOperation(BinaryOperation::GreaterOrEqual, 321,  100,  321 >= 100);
			TestBinaryOperation(BinaryOperation::GreaterOrEqual, -123, 100,  -123 >= 100);
			TestBinaryOperation(BinaryOperation::GreaterOrEqual, -123, -123, -123 >= -123);
			TestBinaryOperation(BinaryOperation::GreaterOrEqual, 0,    200,  0 >= 200);
			TestBinaryOperation(BinaryOperation::GreaterOrEqual, 0,    0,    0 >= 0);

			TestBinaryOperation(BinaryOperation::GreaterOrEqual, 321,    100.1,  321 >= 100.1);
			TestBinaryOperation(BinaryOperation::GreaterOrEqual, -123.2, 100,    -123.2 >= 100);
			TestBinaryOperation(BinaryOperation::GreaterOrEqual, -123.2, -123.2, -123.2 >= -123.2);
			TestBinaryOperation(BinaryOperation::GreaterOrEqual, -123,   -123.2, -123 >= -123.2);
			TestBinaryOperation(BinaryOperation::GreaterOrEqual, 0,      200.2,  0 >= 200.2);
			TestBinaryOperation(BinaryOperation::GreaterOrEqual, 0.0,    0.0,    0.0 >= 0.0);
		}

		TEST_METHOD(Test_LessOrEqualOperation)
		{
			TestBinaryOperation(BinaryOperation::LessOrEqual, 321,  100,  321 <= 100);
			TestBinaryOperation(BinaryOperation::LessOrEqual, -123, 100,  -123 <= 100);
			TestBinaryOperation(BinaryOperation::LessOrEqual, -123, -123, -123 <= -123);
			TestBinaryOperation(BinaryOperation::LessOrEqual, 0,    200,  0 <= 200);
			TestBinaryOperation(BinaryOperation::LessOrEqual, 0,    0,    0 <= 0);

			TestBinaryOperation(BinaryOperation::LessOrEqual, 321,    100.1,  321 <= 100.1);
			TestBinaryOperation(BinaryOperation::LessOrEqual, -123.2, 100,    -123.2 <= 100);
			TestBinaryOperation(BinaryOperation::LessOrEqual, -123.2, -123.2, -123.2 <= -123.2);
			TestBinaryOperation(BinaryOperation::LessOrEqual, -123,   -123.2, -123 <= -123.2);
			TestBinaryOperation(BinaryOperation::LessOrEqual, 0,      200.2,  0 <= 200.2);
			TestBinaryOperation(BinaryOperation::LessOrEqual, 0.0,    0.0,    0.0 <= 0.0);
		}

		TEST_METHOD(Test_OrOperation)
		{
			TestBinaryOperation(BinaryOperation::Or, false, false, false || false);
			TestBinaryOperation(BinaryOperation::Or, false, true,  false || true);
			TestBinaryOperation(BinaryOperation::Or, true,  false, true  || false);
			TestBinaryOperation(BinaryOperation::Or, true,  true,  true  || true);
		}

		TEST_METHOD(Test_AndOperation)
		{
			TestBinaryOperation(BinaryOperation::And, false, false, false && false);
			TestBinaryOperation(BinaryOperation::And, false, true,  false && true);
			TestBinaryOperation(BinaryOperation::And, true,  false, true  && false);
			TestBinaryOperation(BinaryOperation::And, true,  true,  true  && true);
		}

		TEST_METHOD(Test_OperatorIf)
		{
			using namespace std;
			auto& factory = semantics.GetOperationFactory();

			// Условние не bool.
			Assert::ExpectException<SyntaxError>([mt = &mockToken]() {
				auto dummy = make_unique<OperatorIf>(make_unique <Constant<int>>("1234"), make_unique <Constant<int>>("123"), mt);
			});

			// Типы веток нельзя привести к одному.
			Assert::ExpectException<SyntaxError>([mt = &mockToken, sm = &semantics]() {
				auto opif = make_unique<OperatorIf>(make_unique <Constant<bool>>("false"), make_unique <Constant<int>>("123"), mt);
				opif->ElseIf(make_unique <Constant<bool>>("true"), make_unique <Constant<double>>("123.456"), mt);
				opif->Else(make_unique <Constant<bool>>("false"), mt, sm->GetImplicitTypeCastFactory());
				Assert::AreEqual(123.456, double(opif->Calculate()));
				Assert::AreEqual(ValueType::Double, opif->GetType());
			});

			// Всё ок. Тип оператора - double, поскольку типы веток или являются double или для них существует преобразование в double.
			auto opif = make_unique<OperatorIf>(make_unique <Constant<bool>>("false"), make_unique <Constant<int>>("123"), &mockToken);
			opif->ElseIf(make_unique <Constant<bool>>("true"), make_unique <Constant<double>>("123.456"), &mockToken);
			opif->Else(make_unique <Constant<int>>("666"), &mockToken, semantics.GetImplicitTypeCastFactory());
			Assert::AreEqual(123.456, double(opif->Calculate()));
			Assert::AreEqual(ValueType::Double, opif->GetType());
		}

		// --------------------------------------------------------------------
		template <typename LeftParamType, typename RightParamType, typename ExpectedResultType>
		void TestBinaryOperation(BinaryOperation op, LeftParamType leftParam, RightParamType rightParam, ExpectedResultType expectedResultValue)
		{
			auto& factory = semantics.GetOperationFactory();
			// Создаём бинарную операцию, принимающую как параметры две константы,
			// значения констант берём из leftParam и rightParam.
			auto result = factory.CreateBinaryOperation(op,
				std::make_unique<Constant<LeftParamType>>(tools::ToString(leftParam)),
				std::make_unique<Constant<RightParamType>>(tools::ToString(rightParam)),
				&mockToken);

			auto expectedResultType = tools::GetValueType<ExpectedResultType>();
			auto actualResultType   = result->GetType();
			Assert::AreEqual(expectedResultType, actualResultType);

			ExpectedResultType actualResultValue = result->Calculate();
			Assert::AreEqual(expectedResultValue, actualResultValue);
		}

		// --------------------------------------------------------------------
	};
}

#pragma warning (pop)