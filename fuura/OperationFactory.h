#pragma once
#include <vector>
#include <functional>
#include <memory>

#include "ICalculatable.h"
#include "Operation.h"
#include "ICalculatableFactories.h"
#include "TypeCastFactory.h"

namespace antlr4
{
	class Token;
}

/******************************************************************************
*
*	���� �������� ����� OperationFactory, ������� �������� ������� ����
*	���������� �����. �� ���������� ICalculatable ��� ����������� ��������
*	� ��������� ����������� ����� ����������, ���� �� ���������� ����������,
*	���� ��� ��������� ���������� ����������� �������� �����������.
*
*	��� ��������� ������ ����� - ������ ����� ���������� OperationFactory.
*
******************************************************************************/

namespace fuura::language
{
	//////////////////////////////////////////////////////////////////////////////
	// ������� ��� ������ �������� ���������.
	// ������������ ��� ���������� ���� ���������� ��� �����-�� ����� ������� ��������.
	//////////////////////////////////////////////////////////////////////////////
	class UnaryOperationTable
	{
	public:
		// --------------------------------------------------------------------
		UnaryOperationTable();

		// --------------------------------------------------------------------
		// ���������� ��������, ��������������� ����������� ���������
		// ��� �� ����������� ���������� � � ����������.
		// --------------------------------------------------------------------
		std::unique_ptr<ICalculatable> CreateOperation(std::unique_ptr<ICalculatable> arg, antlr4::Token* tokenInfo);

		// --------------------------------------------------------------------
		// ������������� ������� ��� ���������� ���� ���������.
		// --------------------------------------------------------------------
		void SetFactory(ValueType argType, std::unique_ptr<IUnaryOperationFactory> factory);

		// --------------------------------------------------------------------
		// ���������� ��������, ������� ������������ �������.
		// --------------------------------------------------------------------
		UnaryOperation GetOperation() const { return m_operation; }

		// --------------------------------------------------------------------
		// ������������� ��������, ������� ������������ �������.
		// --------------------------------------------------------------------
		void SetOperation(UnaryOperation operation) { m_operation = operation; }

	private:
		// ����� �������� ��������� ������ �������?
		UnaryOperation m_operation;

		// ����� ���������� ������������ � ����� �����.
		static const std::size_t TYPE_COUNT = static_cast<std::size_t>(ValueType::TYPE_COUNT);

		// � m_table[���] ��������� �������, ��������� ICalculatable ��� ������ ������� ��������
		// � ���������� ���� "���".
		// ���� �� ��� ������� ���������, �� ������ ������� �������� ��� ���� "���" �����������.
		std::unique_ptr<IUnaryOperationFactory> m_table[TYPE_COUNT];
	};

	//////////////////////////////////////////////////////////////////////////////
	// ������� ��� ������ ��������� ���������.
	// ������������ ��� ���������� ���������� ���������� ��� �����-�� ����� �������� ��������.
	//////////////////////////////////////////////////////////////////////////////
	class BinaryOperationTable
	{
	public:
		// --------------------------------------------------------------------
		BinaryOperationTable();

		// --------------------------------------------------------------------
		// ���������� ��������, ��������������� ���������� ����������.
		// --------------------------------------------------------------------
		std::unique_ptr<ICalculatable> CreateOperation(std::unique_ptr<ICalculatable> first, std::unique_ptr<ICalculatable> second, antlr4::Token* tokenInfo);

		// --------------------------------------------------------------------
		// ������������� ������� ��������, ��������������� ���������� ����������.
		// --------------------------------------------------------------------
		void SetFactory(ValueType firstType, ValueType secondType, std::unique_ptr<IBinaryOperationFactory> factory);

		// --------------------------------------------------------------------
		// ���������� ��������, ������� ������������ �������.
		// --------------------------------------------------------------------
		BinaryOperation GetOperation() const { return m_operation; }

		// --------------------------------------------------------------------
		// ������������� ��������, ������� ������������ �������.
		// --------------------------------------------------------------------
		void SetOperation(BinaryOperation operation) { m_operation = operation; }

	private:
		// ����� �������� ��������� ������ �������?
		BinaryOperation m_operation;

		// ����� ���������� ������������ � ����� �����.
		static const std::size_t TYPE_COUNT = static_cast<std::size_t>(ValueType::TYPE_COUNT);

		// � m_table[���1][���2] ��������� �������, ��������� ICalculatable ��� ������ �������� ��������
		// � ������ ���������� ���� "���1" � ������ - ���� "���2".
		// ���� �� ��� ������� ���������, �� ������ �������� �������� ��� ���������� ��������� ��������� �����������.
		std::unique_ptr<IBinaryOperationFactory> m_table[TYPE_COUNT][TYPE_COUNT];
	};

	//////////////////////////////////////////////////////////////////////////////
	//
	//	���������� �������� ���������� ��� ���� ��������� ��������� �����.
	//	���������� ���������� ��������� �������� � ����������� �� ����� ����������.
	//	� ������ ���������� ������������������ �������� ��� ����� ����������
	//	����������, ���������� ����������.
	//
	//////////////////////////////////////////////////////////////////////////////
	class OperationFactory
	{
	public:
		// --------------------------------------------------------------------
		OperationFactory();

		// --------------------------------------------------------------------
		// ��������� ������ ������� �������� � ���������� �����������,
		// ���� ���������� ����������, ���� ��� �� �������.
		// --------------------------------------------------------------------
		std::unique_ptr<ICalculatable> CreateUnaryOperation(UnaryOperation operation, std::unique_ptr<ICalculatable> arg, antlr4::Token* tokenInfo);

		// --------------------------------------------------------------------
		// ��������� ������ �������� �������� � ���������� �����������,
		// ���� ���������� ����������, ���� ��� �� �������.
		// --------------------------------------------------------------------
		std::unique_ptr<ICalculatable> CreateBinaryOperation(BinaryOperation operation, std::unique_ptr<ICalculatable> first, std::unique_ptr<ICalculatable> second, antlr4::Token* tokenInfo);

		// --------------------------------------------------------------------
		// ������������� ������� ��������, ��������������� ���������� ����������.
		// ������� ������.
		// --------------------------------------------------------------------
		void SetFactory(UnaryOperation operation, ValueType argType, std::unique_ptr<IUnaryOperationFactory> factory);

		// --------------------------------------------------------------------
		// �� ��, �� ������� ValueType ��������� ��������������. ��� ������� �������.
		// ������� ������.
		// --------------------------------------------------------------------
		template <typename ArgType, class CalculatableT>
		void SetFactory(UnaryOperation operation);

		// --------------------------------------------------------------------
		// �� ��, �� ������� ValueType ��������� ��������������. ��� ��������.
		// ������� ������.
		// --------------------------------------------------------------------
		template <typename ArgType, template<typename> class CalculatableT>
		void SetFactory(UnaryOperation operation);

		// --------------------------------------------------------------------
		// ������������� ������� ��������, ��������������� ���������� ����������.
		// �������� ������.
		// --------------------------------------------------------------------
		void SetFactory(BinaryOperation operation, ValueType firstType, ValueType secondType, std::unique_ptr<IBinaryOperationFactory> factory, TypeCastFactory& tcFactory);

		// --------------------------------------------------------------------
		// �� ��, �� ������� ValueType ��������� ��������������. ��� ������� �������.
		// �������� ������.
		// --------------------------------------------------------------------
		template <typename ArgType, class CalculatableT>
		void SetFactory(BinaryOperation operation, TypeCastFactory& tcFactory);

		// --------------------------------------------------------------------
		// �� ��, �� ������� ValueType ��������� ��������������. ��� ��������.
		// �������� ������.
		// --------------------------------------------------------------------
		template <typename ArgType, template<typename> class CalculatableT>
		void SetFactory(BinaryOperation operation, TypeCastFactory& tcFactory);

	public:
		// --------------------------------------------------------------------
		[[deprecated("������ ��� ������������")]]
		UnaryOperationTable& GetUnaryOpTable(UnaryOperation op) { return m_unaryOperations[static_cast<int>(op)]; }

		// --------------------------------------------------------------------
		[[deprecated("������ ��� ������������")]]
		BinaryOperationTable& GetBinaryOpTable(BinaryOperation op) { return m_binaryOperations[static_cast<int>(op)]; }

	private:
		static const std::size_t UNARY_OPERATION_COUNT = static_cast<std::size_t>(UnaryOperation::OPERATION_COUNT);
		static const std::size_t BINARY_OPERATION_COUNT = static_cast<std::size_t>(BinaryOperation::OPERATION_COUNT);

		std::vector<UnaryOperationTable>  m_unaryOperations;
		std::vector<BinaryOperationTable> m_binaryOperations;
	};

	//////////////////////////////////////////////////////////////////////////////

	// --------------------------------------------------------------------
	template <typename ArgType, class CalculatableT>
	void OperationFactory::SetFactory(UnaryOperation operation)
	{
		const auto arg = fuura::tools::GetValueType<ArgType>();

		SetFactory(operation, arg,
			std::make_unique<UnaryOperationFactory<CalculatableT>>());
	}

	// --------------------------------------------------------------------
	template <typename ArgType, template<typename> class CalculatableT>
	void OperationFactory::SetFactory(UnaryOperation operation)
	{
		const auto arg = fuura::tools::GetValueType<ArgType>();

		SetFactory(operation, arg,
			std::make_unique<UnaryOperationFactory<CalculatableT<ArgType>>>());
	}

	// --------------------------------------------------------------------
	template <typename ArgType, class CalculatableT>
	void OperationFactory::SetFactory(BinaryOperation operation, TypeCastFactory& tcFactory)
	{
		const auto first  = fuura::tools::GetValueType<ArgType>();
		const auto second = fuura::tools::GetValueType<ArgType>();

		SetFactory(operation, first, second,
			std::make_unique<BinaryOperationFactory<CalculatableT>>(),
			tcFactory);
	}

	// --------------------------------------------------------------------
	template <typename ArgType, template<typename> class CalculatableT>
	void OperationFactory::SetFactory(BinaryOperation operation, TypeCastFactory& tcFactory)
	{
		const auto first  = fuura::tools::GetValueType<ArgType>();
		const auto second = fuura::tools::GetValueType<ArgType>();

		SetFactory(operation, first, second,
			std::make_unique<BinaryOperationFactory<CalculatableT<ArgType>>>(),
			tcFactory);
	}

	// --------------------------------------------------------------------
}