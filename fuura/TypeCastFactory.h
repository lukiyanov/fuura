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
	//	Менеджер неявных преобразований типов.
	//
	///////////////////////////////////////////////////////////////////////////
	class TypeCastFactory
	{
	public:
		// --------------------------------------------------------------------
		// Создаёт ICalculatable, преобразующего выражение what в тип castTo,
		// либо возвращает нулевой указатель если такое преобразование отсутствует.
		// --------------------------------------------------------------------
		std::unique_ptr<ICalculatable> CreateTypeCast(std::unique_ptr<ICalculatable> what, ValueType castTo) const;

		// --------------------------------------------------------------------
		// Возвращает "максимум" изо всех полученных типов, такой, к которому
		// можно привести все остальные. Если это невозможно, возвращает
		// std::nullopt.
		// --------------------------------------------------------------------
		std::optional<ValueType> CalculateCommonTypeOf(std::set<ValueType>& types) const;

		// --------------------------------------------------------------------
		// Возвращает признак того, существует ли преобразование типов из типа
		// castFrom к типу castTo.
		// --------------------------------------------------------------------
		bool TypeCastExists(ValueType castFrom, ValueType castTo) const;

		// --------------------------------------------------------------------
		// Устанавливает фабрику преобразований из типа from в тип to.
		// --------------------------------------------------------------------
		void DeclareTypeCast(ValueType from, ValueType to, std::unique_ptr<IUnaryOperationFactory> factory);

		// --------------------------------------------------------------------
		// Устанавливает фабрику преобразований из типа From в тип To способом,
		// принятым в языке C++. Чуть более автоматизированная разновидность
		// DeclareTypeCast.
		// --------------------------------------------------------------------
		template <typename From, typename To>
		void DeclareCppTypeCast();

	private:
		// Общее количество существующих в языке типов.
		static const std::size_t TYPE_COUNT = static_cast<std::size_t>(ValueType::TYPE_COUNT);

		// В m_table[тип1][тип2] находится фабрика, создающая преобразование из типа "тип1" в тип "тип2".
		// Если же там нулевой указатель, то такое преобразование отсутствует.
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