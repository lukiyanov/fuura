#pragma once
#include "ICalculatableFactories.h"
#include "TypeCastFactory.h"

namespace fuura::language
{
	//////////////////////////////////////////////////////////////////////////////
	//
	//	���������� ������ �������, �������� ������� �������� �������������� ����� ��
	//	���� ������� ���������, ������������� � ������� Create ������������ �������.
	//
	//////////////////////////////////////////////////////////////////////////////
	class FirstArgumentTypeCastDecoratorFactory : public IBinaryOperationFactory
	{
		/********************************************************************************
		�����:
			A, B - ��������� ���� (ValueType).
			[A], [B] - ICalculatables ��������� ����� A � B ��������������, ���
		               ��������� �� ���� ICalculatables, ������������ ������ ��������.
			[A -> B], [B op B] - ICalculatables, ������������ ������ ��������.
			M => N - M ��������� N

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

		// �������� �������, ������� � ���������������� ��������� ��������.
		std::unique_ptr<IBinaryOperationFactory> m_innerFactory;

		// ������� �������������� �����. ��� ���������� ��������������,
		// ����� �������� ���� ����� ���������� �������� ��� ����������� �� ����
		// �������� [B op B].
		// ������ ������������ �� ���������� ����� ������� ����� ������� ������� ������.
		TypeCastFactory& m_typeCastFactory;

		// ��� � �������� ������ ����������� ������ �������� ������������ ��������.
		ValueType m_castToType;

	public:
		// --------------------------------------------------------------------
		// typeCastFactory ������ ������������ �� ���������� ����� ������� ����� ������� ������� ������.
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
	//	���������� ������ �������, �������� ������� �������� �������������� ����� ��
	//	���� ������� ���������, ������������� � ������� Create ������������ �������.
	//
	//////////////////////////////////////////////////////////////////////////////
	class SecondArgumentTypeCastDecoratorFactory : public IBinaryOperationFactory
	{
		/********************************************************************************
		�����:
			A, B - ��������� ���� (ValueType).
			[A], [B] - ICalculatables ��������� ����� A � B ��������������, ���
		               ��������� �� ���� ICalculatables, ������������ ������ ��������.
			[A -> B], [B op B] - ICalculatables, ������������ ������ ��������.
			M => N - M ��������� N

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

		// �������� �������, ������� � ���������������� ��������� ��������.
		std::unique_ptr<IBinaryOperationFactory> m_innerFactory;

		// ������� �������������� �����. ��� ���������� ��������������,
		// ����� �������� ���� ����� ���������� �������� ��� ����������� �� ����
		// �������� [B op B].
		// ������ ������������ �� ���������� ����� ������� ����� ������� ������� ������.
		TypeCastFactory& m_typeCastFactory;

		// ��� � �������� ������ ����������� ������ �������� ������������ ��������.
		ValueType m_castToType;

	public:
		// --------------------------------------------------------------------
		// typeCastFactory ������ ������������ �� ���������� ����� ������� ����� ������� ������� ������.
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