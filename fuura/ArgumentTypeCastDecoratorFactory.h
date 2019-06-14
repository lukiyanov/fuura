#pragma once
#include "ICalculatableFactories.h"
#include "TypeCastFactory.h"

namespace fuura::language
{
	//////////////////////////////////////////////////////////////////////////////
	//
	//	Декорирует другую фабрику, добавляя унарную операцию преобразования типов на
	//	вход первого аргумента, передаваемого в функцию Create декорируемой фабрики.
	//
	//////////////////////////////////////////////////////////////////////////////
	class FirstArgumentTypeCastDecoratorFactory : public IBinaryOperationFactory
	{
		/********************************************************************************
		Здесь:
			A, B - некоторые типы (ValueType).
			[A], [B] - ICalculatables некоторых типов A и B соответственно, они
		               поступают на вход ICalculatables, генерируемым данной фабрикой.
			[A -> B], [B op B] - ICalculatables, генерируемые данной фабрикой.
			M => N - M порождает N

                                         +---------------------------------------------+
                                         |    FirstArgumentTypeCastDecoratorFactory    |
                                         +---------------------------------------------+
		                                 |   +------------------+                      |
		               [A]      [B]      |   | m_castToType = B |                      |
		                |        |       |   +------------------+                      |
		                v        |       |            |                                |
		            +--------+   |       |            v   +-------------------------+  |
		            | A -> B | <=|=======|===========(+)==|    m_typeCastFactory    |  |
		            +--------+   |       |                +-------------------------+  |
		                |        |		 |                                             |
		               [B]       |		 |                                             |
		                |        |		 |                                             |
		                v        v		 |                                             |
		            +----------------+   |      +-------------------------+            |
		            |     B op B     | <=|======|     m_innerFactory      |            |
		            +----------------+   |      +-------------------------+            |
		                   |			 |                                             |
                           v             |                                             |
		                  ...            +---------------------------------------------+

		********************************************************************************/

		// Конечная фабрика, которая в действительности реализует операцию.
		std::unique_ptr<IBinaryOperationFactory> m_innerFactory;

		// Фабрика преобразований типов. Она генерирует преобразование,
		// после которого типы обоих аргументов подходят для поступления на вход
		// операции [B op B].
		// Должен существовать на протяжении всего периода жизни объекта данного класса.
		TypeCastFactory& m_typeCastFactory;

		// Тип к которому должен приводиться первый аргумент генерируемой операции.
		ValueType m_castToType;

	public:
		// --------------------------------------------------------------------
		// typeCastFactory должен существовать на протяжении всего периода жизни объекта данного класса.
		// --------------------------------------------------------------------
		FirstArgumentTypeCastDecoratorFactory(std::unique_ptr<IBinaryOperationFactory> innerFactory, TypeCastFactory& typeCastFactory, ValueType castToType)
			: m_innerFactory(std::move(innerFactory)), m_typeCastFactory(typeCastFactory), m_castToType(castToType)
		{}

		// --------------------------------------------------------------------
		std::unique_ptr<ICalculatable> Create(std::unique_ptr<ICalculatable> first, std::unique_ptr<ICalculatable> second) override
		{
			auto firstCasted = m_typeCastFactory.CreateTypeCast(std::move(first), m_castToType);
			return m_innerFactory->Create(std::move(firstCasted), std::move(second));
		}

		// --------------------------------------------------------------------
		std::unique_ptr<IBinaryOperationFactory> Clone() override
		{
			return std::make_unique<FirstArgumentTypeCastDecoratorFactory>(m_innerFactory->Clone(), m_typeCastFactory, m_castToType);
		}

		// --------------------------------------------------------------------
	};


	//////////////////////////////////////////////////////////////////////////////
	//
	//	Декорирует другую фабрику, добавляя унарную операцию преобразования типов на
	//	вход второго аргумента, передаваемого в функцию Create декорируемой фабрики.
	//
	//////////////////////////////////////////////////////////////////////////////
	class SecondArgumentTypeCastDecoratorFactory : public IBinaryOperationFactory
	{
		/********************************************************************************
		Здесь:
			A, B - некоторые типы (ValueType).
			[A], [B] - ICalculatables некоторых типов A и B соответственно, они
		               поступают на вход ICalculatables, генерируемым данной фабрикой.
			[A -> B], [B op B] - ICalculatables, генерируемые данной фабрикой.
			M => N - M порождает N

                                         +---------------------------------------------+
                                         |    SecondArgumentTypeCastDecoratorFactory   |
                                         +---------------------------------------------+
                                         |   +------------------+                      |
                 [B]      [A]            |   | m_castToType = B |                      |
                  |        |             |   +------------------+                      |
                  |        v             |            |                                |
                  |   +--------+         |            v   +-------------------------+  |
                  |   | A -> B | <=======|===========(+)==|    m_typeCastFactory    |  |
                  |   +--------+         |                +-------------------------+  |
                  |        |             |                                             |
                  |       [B]            |                                             |
                  |        |             |                                             |
                  v        v             |                                             |
              +----------------+         |      +-------------------------+            |
              |     B op B     | <=======|======|     m_innerFactory      |            |
              +----------------+         |      +-------------------------+            |
                     |                   |                                             |
                     v                   |                                             |
                    ...                  +---------------------------------------------+
           						        
		********************************************************************************/

		// Конечная фабрика, которая в действительности реализует операцию.
		std::unique_ptr<IBinaryOperationFactory> m_innerFactory;

		// Фабрика преобразований типов. Она генерирует преобразование,
		// после которого типы обоих аргументов подходят для поступления на вход
		// операции [B op B].
		// Должен существовать на протяжении всего периода жизни объекта данного класса.
		TypeCastFactory& m_typeCastFactory;

		// Тип к которому должен приводиться второй аргумент генерируемой операции.
		ValueType m_castToType;

	public:
		// --------------------------------------------------------------------
		// typeCastFactory должен существовать на протяжении всего периода жизни объекта данного класса.
		// --------------------------------------------------------------------
		SecondArgumentTypeCastDecoratorFactory(std::unique_ptr<IBinaryOperationFactory> innerFactory, TypeCastFactory& typeCastFactory, ValueType castToType)
			: m_innerFactory(std::move(innerFactory)), m_typeCastFactory(typeCastFactory), m_castToType(castToType)
		{}

		// --------------------------------------------------------------------
		std::unique_ptr<ICalculatable> Create(std::unique_ptr<ICalculatable> first, std::unique_ptr<ICalculatable> second) override
		{
			auto secondCasted = m_typeCastFactory.CreateTypeCast(std::move(second), m_castToType);
			return m_innerFactory->Create(std::move(first), std::move(secondCasted));
		}

		// --------------------------------------------------------------------
		std::unique_ptr<IBinaryOperationFactory> Clone() override
		{
			return std::make_unique<SecondArgumentTypeCastDecoratorFactory>(m_innerFactory->Clone(), m_typeCastFactory, m_castToType);
		}

		// --------------------------------------------------------------------
	};

	//////////////////////////////////////////////////////////////////////////////
}