#include "stdafx.h"
#include "FuuraSemantics.h"
using namespace fuura;
using namespace fuura::language;
using namespace std;

// ----------------------------------------------------------------------------
FuuraSemantics::FuuraSemantics()
{
	// Настраиваем неявные преобразования типов.
	// Разрешаем неявные преобразования int -> double.
	// Таким образом, int допустимо всюду где требуется double.
	m_typeCastFactory.DeclareCppTypeCast<int, double>();

	// Задаём операции.
	// Унарные:
	m_operationFactory.SetFactory<bool,   Not>	  (UnaryOperation::Not);	// not a (bool)
	m_operationFactory.SetFactory<int,    Invert> (UnaryOperation::Invert);	// -a    (int)
	m_operationFactory.SetFactory<double, Invert> (UnaryOperation::Invert);	// -a    (double)

	// Бинарные:
	m_operationFactory.SetFactory<int, IntegerDivide>  (BinaryOperation::IntegerDivide, m_typeCastFactory);	// div	(int)
	m_operationFactory.SetFactory<int, GetDivRemainder>(BinaryOperation::GetDivRemainder, m_typeCastFactory);// %	(int)

	m_operationFactory.SetFactory<bool, Or> (BinaryOperation::Or, m_typeCastFactory);						// or	(bool)
	m_operationFactory.SetFactory<bool, And>(BinaryOperation::And, m_typeCastFactory);						// and	(bool)

	m_operationFactory.SetFactory<int,    Add>(BinaryOperation::Add, m_typeCastFactory);					// + (int)
	m_operationFactory.SetFactory<double, Add>(BinaryOperation::Add, m_typeCastFactory);					// + (double)

	m_operationFactory.SetFactory<int,    Subtract>(BinaryOperation::Subtract, m_typeCastFactory);			// - (int)
	m_operationFactory.SetFactory<double, Subtract>(BinaryOperation::Subtract, m_typeCastFactory);			// - (double)

	m_operationFactory.SetFactory<int,    Multiply>(BinaryOperation::Multiply, m_typeCastFactory);			// * (int)
	m_operationFactory.SetFactory<double, Multiply>(BinaryOperation::Multiply, m_typeCastFactory);			// * (double)

	m_operationFactory.SetFactory<int,    RealDivide>(BinaryOperation::RealDivide, m_typeCastFactory);		// / (int)
	m_operationFactory.SetFactory<double, RealDivide>(BinaryOperation::RealDivide, m_typeCastFactory);		// / (double)

	m_operationFactory.SetFactory<int,    RaiseToPower>(BinaryOperation::RaiseToPower, m_typeCastFactory);	// ^ (int)
	m_operationFactory.SetFactory<double, RaiseToPower>(BinaryOperation::RaiseToPower, m_typeCastFactory);	// ^ (double)

	m_operationFactory.SetFactory<int,    Equal>(BinaryOperation::Equal, m_typeCastFactory);				// = (int)
	m_operationFactory.SetFactory<double, Equal>(BinaryOperation::Equal, m_typeCastFactory);				// = (double)

	m_operationFactory.SetFactory<int,    NotEqual>(BinaryOperation::NotEqual, m_typeCastFactory);			// != (int)
	m_operationFactory.SetFactory<double, NotEqual>(BinaryOperation::NotEqual, m_typeCastFactory);			// != (double)

	m_operationFactory.SetFactory<int,    Less>(BinaryOperation::Less, m_typeCastFactory);					// < (int)
	m_operationFactory.SetFactory<double, Less>(BinaryOperation::Less, m_typeCastFactory);					// < (double)

	m_operationFactory.SetFactory<int,    Greater>(BinaryOperation::Greater, m_typeCastFactory);			// > (int)
	m_operationFactory.SetFactory<double, Greater>(BinaryOperation::Greater, m_typeCastFactory);			// > (double)

	m_operationFactory.SetFactory<int,    LessOrEqual>(BinaryOperation::LessOrEqual, m_typeCastFactory);	// <= (int)
	m_operationFactory.SetFactory<double, LessOrEqual>(BinaryOperation::LessOrEqual, m_typeCastFactory);	// <= (double)

	m_operationFactory.SetFactory<int,    GreaterOrEqual>(BinaryOperation::GreaterOrEqual, m_typeCastFactory);	// >= (int)
	m_operationFactory.SetFactory<double, GreaterOrEqual>(BinaryOperation::GreaterOrEqual, m_typeCastFactory);	// >= (double)

	// Задаём доступные функции
	m_functionRegistry.RegisterFunction<double(double)>("sin", &sin);
	m_functionRegistry.RegisterFunction<double(double)>("cos", &cos);
	m_functionRegistry.RegisterFunction<double(double)>("tan", &tan);

	m_functionRegistry.RegisterFunction<double(double)>("exp", &exp);
	m_functionRegistry.RegisterFunction<double(double)>("ln",  &log);
	m_functionRegistry.RegisterFunction<double(double)>("log", &log10);
}

// ----------------------------------------------------------------------------
void FuuraSemantics::UpdateArgumentSet(IArgumentSet* argumentSet)
{
	m_argumentSet = argumentSet;
}

// ----------------------------------------------------------------------------
IArgumentSet& FuuraSemantics::GetArgumentSet()
{
	return *m_argumentSet;
}

// ----------------------------------------------------------------------------
OperationFactory& FuuraSemantics::GetOperationFactory()
{
	return m_operationFactory;
}

// ----------------------------------------------------------------------------
TypeCastFactory& FuuraSemantics::GetImplicitTypeCastFactory()
{
	return m_typeCastFactory;
}

// ----------------------------------------------------------------------------
FunctionRegistry& fuura::language::FuuraSemantics::GetFunctionRegistry()
{
	return m_functionRegistry;
}

// ----------------------------------------------------------------------------