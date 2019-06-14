#pragma once
#include <set>
#include <memory>
#include <optional>
#include "Value.h"
#include "ICalculatable.h"
#include "ICalculatableFactories.h"
#include "Calculatables.h"
#include "GetValueType.h"

namespace fuura::language
{
	///////////////////////////////////////////////////////////////////////////
	//
	//	�������� ������� �������������� �����.
	//
	///////////////////////////////////////////////////////////////////////////
	class TypeCastFactory
	{
	public:
		// --------------------------------------------------------------------
		// ������ ICalculatable, �������������� ��������� what � ��� castTo,
		// ���� ���������� ������� ��������� ���� ����� �������������� �����������.
		// --------------------------------------------------------------------
		std::unique_ptr<ICalculatable> CreateTypeCast(std::unique_ptr<ICalculatable> what, ValueType castTo) const;

		// --------------------------------------------------------------------
		// ���������� "��������" ��� ���� ���������� �����, �����, � ��������
		// ����� �������� ��� ���������. ���� ��� ����������, ����������
		// std::nullopt.
		// --------------------------------------------------------------------
		std::optional<ValueType> CalculateCommonTypeOf(std::set<ValueType>& types) const;

		// --------------------------------------------------------------------
		// ���������� ������� ����, ���������� �� �������������� ����� �� ����
		// castFrom � ���� castTo.
		// --------------------------------------------------------------------
		bool TypeCastExists(ValueType castFrom, ValueType castTo) const;

		// --------------------------------------------------------------------
		// ������������� ������� �������������� �� ���� from � ��� to.
		// --------------------------------------------------------------------
		void DeclareTypeCast(ValueType from, ValueType to, std::unique_ptr<IUnaryOperationFactory> factory);

		// --------------------------------------------------------------------
		// ������������� ������� �������������� �� ���� From � ��� To ��������,
		// �������� � ����� C++. ���� ����� ������������������ �������������
		// DeclareTypeCast.
		// --------------------------------------------------------------------
		template <typename From, typename To>
		void DeclareCppTypeCast();

	private:
		// ����� ���������� ������������ � ����� �����.
		static const std::size_t TYPE_COUNT = static_cast<std::size_t>(ValueType::TYPE_COUNT);

		// � m_table[���1][���2] ��������� �������, ��������� �������������� �� ���� "���1" � ��� "���2".
		// ���� �� ��� ������� ���������, �� ����� �������������� �����������.
		std::unique_ptr<IUnaryOperationFactory> m_table[TYPE_COUNT][TYPE_COUNT];
	};

	///////////////////////////////////////////////////////////////////////////

	// ----------------------------------------------------------------------------
	template <typename From, typename To>
	void TypeCastFactory::DeclareCppTypeCast()
	{
		DeclareTypeCast(
			tools::GetValueType<From>(),
			tools::GetValueType<To>(),
			std::make_unique<UnaryOperationFactory<CppTypeCast<From, To>>>()
		);
	}

	// ----------------------------------------------------------------------------
}