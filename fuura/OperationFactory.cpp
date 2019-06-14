#include "stdafx.h"
#include "OperationFactory.h"
#include "Calculatables.h"

#include "GetValueType.h"
#include "ArgumentTypeCastDecoratorFactory.h"
#include "Exception.h"
#include "ToString.h"
#include "Token.h"

using namespace fuura;
using namespace fuura::language;
using namespace fuura::tools;
using namespace std;


///////////////////////////////////////////////////////////////////////////////
//
//	UnaryOperationTable
//
///////////////////////////////////////////////////////////////////////////////

// ----------------------------------------------------------------------------
UnaryOperationTable::UnaryOperationTable()
{
	static int operationNumber;
	m_operation = static_cast<UnaryOperation>(operationNumber++);
}

// ----------------------------------------------------------------------------
std::unique_ptr<ICalculatable> UnaryOperationTable::CreateOperation(std::unique_ptr<ICalculatable> arg, antlr4::Token* tokenInfo)
{
	const auto typeIndex = static_cast<std::size_t>(arg->GetType());
	if (!m_table[typeIndex])
		throw SyntaxError(string("Унарная операция \"") + ToString(m_operation) + "\" не поддерживается для типа \"" + ToString(arg->GetType()) + '\"',
			tokenInfo->getLine(), tokenInfo->getCharPositionInLine());

	return m_table[typeIndex]->Create(std::move(arg));
}

// ----------------------------------------------------------------------------
void UnaryOperationTable::SetFactory(ValueType argType, std::unique_ptr<IUnaryOperationFactory> factory)
{
	const auto typeIndex = static_cast<std::size_t>(argType);
	if (m_table[typeIndex])
	{
		throw std::exception(
			(string("Попытка повторного задания фабрики операций для операции \"")
				+ ToString(m_operation) + ' ' + ToString(argType) + "\"."
			).c_str()
		);
	}
	m_table[typeIndex] = std::move(factory);
}


///////////////////////////////////////////////////////////////////////////////
//
//	BinaryOperationTable
//
///////////////////////////////////////////////////////////////////////////////

// ----------------------------------------------------------------------------
BinaryOperationTable::BinaryOperationTable()
{
	static int operationNumber;
	m_operation = static_cast<BinaryOperation>(operationNumber++);
}

// ----------------------------------------------------------------------------
std::unique_ptr<ICalculatable> BinaryOperationTable::CreateOperation(std::unique_ptr<ICalculatable> first, std::unique_ptr<ICalculatable> second, antlr4::Token* tokenInfo)
{
	const auto typeIndexI = static_cast<std::size_t>(first->GetType());
	const auto typeIndexJ = static_cast<std::size_t>(second->GetType());
	if (!m_table[typeIndexI][typeIndexJ])
		throw SyntaxError(string("Бинарная операция \"") + ToString(m_operation) + "\" не поддерживается для выражения вида \""
			+ ToString(first->GetType()) + ' ' + ToString(m_operation) + ' ' + ToString(second->GetType()) + '\"',
			tokenInfo->getLine(), tokenInfo->getCharPositionInLine());

	return m_table[typeIndexI][typeIndexJ]->Create(std::move(first), std::move(second));
}

// ----------------------------------------------------------------------------
void BinaryOperationTable::SetFactory(ValueType firstType, ValueType secondType, std::unique_ptr<IBinaryOperationFactory> factory)
{
	const auto typeIndexI = static_cast<std::size_t>(firstType);
	const auto typeIndexJ = static_cast<std::size_t>(secondType);
	if (m_table[typeIndexI][typeIndexJ])
	{
		throw std::exception(
			(string("Попытка повторного задания фабрики операций для операции \"")
				+ ToString(firstType) + ' ' + ToString(m_operation) + ' ' + ToString(secondType) + "\"."
			).c_str()
		);
	}
	m_table[typeIndexI][typeIndexJ] = std::move(factory);
}


///////////////////////////////////////////////////////////////////////////////
//
//	OperationFactory
//
///////////////////////////////////////////////////////////////////////////////

// --------------------------------------------------------------------
OperationFactory::OperationFactory()
	: m_unaryOperations(UNARY_OPERATION_COUNT), m_binaryOperations(BINARY_OPERATION_COUNT)
{
	for (size_t i = 0; i < UNARY_OPERATION_COUNT; i++)
		m_unaryOperations[i].SetOperation(static_cast<UnaryOperation>(i));

	for (size_t i = 0; i < BINARY_OPERATION_COUNT; i++)
		m_binaryOperations[i].SetOperation(static_cast<BinaryOperation>(i));
}

// --------------------------------------------------------------------
std::unique_ptr<ICalculatable> OperationFactory::CreateUnaryOperation(UnaryOperation operation, std::unique_ptr<ICalculatable> arg, antlr4::Token* tokenInfo)
{
	const auto operationIndex = static_cast<std::size_t>(operation);
	return m_unaryOperations[operationIndex].CreateOperation(std::move(arg), tokenInfo);
}

// --------------------------------------------------------------------
std::unique_ptr<ICalculatable> OperationFactory::CreateBinaryOperation(BinaryOperation operation, std::unique_ptr<ICalculatable> first, std::unique_ptr<ICalculatable> second, antlr4::Token* tokenInfo)
{
	const auto operationIndex = static_cast<std::size_t>(operation);
	return m_binaryOperations[operationIndex].CreateOperation(std::move(first), std::move(second), tokenInfo);
}

// --------------------------------------------------------------------
void OperationFactory::SetFactory(UnaryOperation operation, ValueType argType, std::unique_ptr<IUnaryOperationFactory> factory)
{
	const auto operationIndex = static_cast<std::size_t>(operation);
	m_unaryOperations[operationIndex].SetFactory(argType, std::move(factory));
}

// --------------------------------------------------------------------
void OperationFactory::SetFactory(BinaryOperation operation, ValueType firstType, ValueType secondType, std::unique_ptr<IBinaryOperationFactory> factory, TypeCastFactory& tcFactory)
{
	const auto operationIndex = static_cast<std::size_t>(operation);
	const size_t typeCount = static_cast<std::size_t>(ValueType::TYPE_COUNT);

	// Если нужно добавить операцию вида A op B, то также добавляем операции вида A0 op B и A op B0,
	// где A0 - типы, приводимые к A, B0 - типы, приводимые к B.	
	// Обходим сразу оба аргумента в одном цикле.
	for (size_t i = 0; i < typeCount; i++)
	{
		// Проверяем, существуют ли преобразования из данного типа в firstType или secondType.
		auto type = static_cast<ValueType>(i);

		if (tcFactory.TypeCastExists(type, firstType))
		{
			// Если преобразование type->firstType существует, то также добавляем адаптированную версию
			// с типом type вместо firstType.
			m_binaryOperations[operationIndex].SetFactory(type, secondType,
				// Декорируем первый аргумент типа type преобразованием к типу firstType.
				make_unique<FirstArgumentTypeCastDecoratorFactory>(factory->Clone(), tcFactory, firstType)
			);
		}

		if (tcFactory.TypeCastExists(type, secondType))
		{
			// Если преобразование type->secondType существует, то также добавляем адаптированную версию
			// с типом type вместо secondType.
			m_binaryOperations[operationIndex].SetFactory(firstType, type,
				// Декорируем второй аргумент типа type преобразованием к типу secondType.
				make_unique<SecondArgumentTypeCastDecoratorFactory>(factory->Clone(), tcFactory, secondType)
			);
		}
	}

	// Наконец, добавляем изначальную фабрику и теряем указатель на неё.
	m_binaryOperations[operationIndex].SetFactory(firstType, secondType, std::move(factory));
}

// --------------------------------------------------------------------