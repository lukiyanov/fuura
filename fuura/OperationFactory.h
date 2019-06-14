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
*	Файл содержит класс OperationFactory, который содержит таблицу всех
*	операторов языка. Он возвращает ICalculatable для запрошенной операции
*	с выбранной комбинацией типов аргументов, либо же генерирует исключение,
*	если для указанных аргументов запрошенная операция отсутствует.
*
*	Все остальные классы файла - просто часть реализации OperationFactory.
*
******************************************************************************/

namespace fuura::language
{
	//////////////////////////////////////////////////////////////////////////////
	// Фабрика для одного унарного оператора.
	// Обрабатывает все допустимые типы аргументов для какой-то одной унарной операции.
	//////////////////////////////////////////////////////////////////////////////
	class UnaryOperationTable
	{
	public:
		// --------------------------------------------------------------------
		UnaryOperationTable();

		// --------------------------------------------------------------------
		// Генерирует операцию, соответствующую переданному аргументу
		// или же выбрасывает исключение о её отсутсивии.
		// --------------------------------------------------------------------
		std::unique_ptr<ICalculatable> CreateOperation(std::unique_ptr<ICalculatable> arg, antlr4::Token* tokenInfo);

		// --------------------------------------------------------------------
		// Устанавливает фабрику для указанного типа аргумента.
		// --------------------------------------------------------------------
		void SetFactory(ValueType argType, std::unique_ptr<IUnaryOperationFactory> factory);

		// --------------------------------------------------------------------
		// Возвращает операцию, которую обрабатывает таблица.
		// --------------------------------------------------------------------
		UnaryOperation GetOperation() const { return m_operation; }

		// --------------------------------------------------------------------
		// Устанавливает операцию, которую обрабатывает таблица.
		// --------------------------------------------------------------------
		void SetOperation(UnaryOperation operation) { m_operation = operation; }

	private:
		// Какую операцию реализует данная таблица?
		UnaryOperation m_operation;

		// Общее количество существующих в языке типов.
		static const std::size_t TYPE_COUNT = static_cast<std::size_t>(ValueType::TYPE_COUNT);

		// В m_table[тип] находится фабрика, создающая ICalculatable для данной унарной операции
		// с аргументом типа "тип".
		// Если же там нулевой указатель, то данная унарная операция для типа "тип" отсутствует.
		std::unique_ptr<IUnaryOperationFactory> m_table[TYPE_COUNT];
	};

	//////////////////////////////////////////////////////////////////////////////
	// Фабрика для одного бинарного оператора.
	// Обрабатывает все допустимые комбинации аргументов для какой-то одной бинарной операции.
	//////////////////////////////////////////////////////////////////////////////
	class BinaryOperationTable
	{
	public:
		// --------------------------------------------------------------------
		BinaryOperationTable();

		// --------------------------------------------------------------------
		// Генерирует операцию, соответствующую переданным аргументам.
		// --------------------------------------------------------------------
		std::unique_ptr<ICalculatable> CreateOperation(std::unique_ptr<ICalculatable> first, std::unique_ptr<ICalculatable> second, antlr4::Token* tokenInfo);

		// --------------------------------------------------------------------
		// Устанавливает фабрику операций, соответствующую переданным аргументам.
		// --------------------------------------------------------------------
		void SetFactory(ValueType firstType, ValueType secondType, std::unique_ptr<IBinaryOperationFactory> factory);

		// --------------------------------------------------------------------
		// Возвращает операцию, которую обрабатывает таблица.
		// --------------------------------------------------------------------
		BinaryOperation GetOperation() const { return m_operation; }

		// --------------------------------------------------------------------
		// Устанавливает операцию, которую обрабатывает таблица.
		// --------------------------------------------------------------------
		void SetOperation(BinaryOperation operation) { m_operation = operation; }

	private:
		// Какую операцию реализует данная таблица?
		BinaryOperation m_operation;

		// Общее количество существующих в языке типов.
		static const std::size_t TYPE_COUNT = static_cast<std::size_t>(ValueType::TYPE_COUNT);

		// В m_table[тип1][тип2] находится фабрика, создающая ICalculatable для данной бинарной операции
		// с первым аргументом типа "тип1" и вторым - типа "тип2".
		// Если же там нулевой указатель, то данная бинарная операция для указанного сочетания операндов отсутствует.
		std::unique_ptr<IBinaryOperationFactory> m_table[TYPE_COUNT][TYPE_COUNT];
	};

	//////////////////////////////////////////////////////////////////////////////
	//
	//	Фактически содержит информацию обо всех доступных операциях языка.
	//	Генерирует реализации требуемых операций в зависимости от типов аргументов.
	//	В случае отсутствия зарегистрированной операции для такой комбинации
	//	аргументов, генерирует исключение.
	//
	//////////////////////////////////////////////////////////////////////////////
	class OperationFactory
	{
	public:
		// --------------------------------------------------------------------
		OperationFactory();

		// --------------------------------------------------------------------
		// Полностью создаёт унарную операцию с указанными параметрами,
		// либо генерирует исключение, если это не удалось.
		// --------------------------------------------------------------------
		std::unique_ptr<ICalculatable> CreateUnaryOperation(UnaryOperation operation, std::unique_ptr<ICalculatable> arg, antlr4::Token* tokenInfo);

		// --------------------------------------------------------------------
		// Полностью создаёт бинарную операцию с указанными параметрами,
		// либо генерирует исключение, если это не удалось.
		// --------------------------------------------------------------------
		std::unique_ptr<ICalculatable> CreateBinaryOperation(BinaryOperation operation, std::unique_ptr<ICalculatable> first, std::unique_ptr<ICalculatable> second, antlr4::Token* tokenInfo);

		// --------------------------------------------------------------------
		// Устанавливает фабрику операций, соответствующую переданным аргументам.
		// Унарная версия.
		// --------------------------------------------------------------------
		void SetFactory(UnaryOperation operation, ValueType argType, std::unique_ptr<IUnaryOperationFactory> factory);

		// --------------------------------------------------------------------
		// То же, но выводит ValueType операндов самостоятельно. Для обычных классов.
		// Унарная версия.
		// --------------------------------------------------------------------
		template <typename ArgType, class CalculatableT>
		void SetFactory(UnaryOperation operation);

		// --------------------------------------------------------------------
		// То же, но выводит ValueType операндов самостоятельно. Для шаблонов.
		// Унарная версия.
		// --------------------------------------------------------------------
		template <typename ArgType, template<typename> class CalculatableT>
		void SetFactory(UnaryOperation operation);

		// --------------------------------------------------------------------
		// Устанавливает фабрику операций, соответствующую переданным аргументам.
		// Бинарная версия.
		// --------------------------------------------------------------------
		void SetFactory(BinaryOperation operation, ValueType firstType, ValueType secondType, std::unique_ptr<IBinaryOperationFactory> factory, TypeCastFactory& tcFactory);

		// --------------------------------------------------------------------
		// То же, но выводит ValueType операндов самостоятельно. Для обычных классов.
		// Бинарная версия.
		// --------------------------------------------------------------------
		template <typename ArgType, class CalculatableT>
		void SetFactory(BinaryOperation operation, TypeCastFactory& tcFactory);

		// --------------------------------------------------------------------
		// То же, но выводит ValueType операндов самостоятельно. Для шаблонов.
		// Бинарная версия.
		// --------------------------------------------------------------------
		template <typename ArgType, template<typename> class CalculatableT>
		void SetFactory(BinaryOperation operation, TypeCastFactory& tcFactory);

	public:
		// --------------------------------------------------------------------
		[[deprecated("Только для тестирования")]]
		UnaryOperationTable& GetUnaryOpTable(UnaryOperation op) { return m_unaryOperations[static_cast<int>(op)]; }

		// --------------------------------------------------------------------
		[[deprecated("Только для тестирования")]]
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