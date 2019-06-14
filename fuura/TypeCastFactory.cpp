#include "stdafx.h"
#include "TypeCastFactory.h"
#include "ToString.h"
#include <string>

using namespace fuura;
using namespace fuura::language;
using namespace std;

// ----------------------------------------------------------------------------
void TypeCastFactory::DeclareTypeCast(ValueType from, ValueType to, std::unique_ptr<IUnaryOperationFactory> factory)
{
	// Ќе€вные преобразовани€ типа в себ€ запрещены.
	if (from == to)
	{
		throw std::exception(
			(string("«адано не€вное преобразование типа ") + tools::ToString(from) + " в себ€.").c_str()
		);
	}

	const auto fromIndex = static_cast<std::size_t>(from);
	const auto toIndex   = static_cast<std::size_t>(to);
	m_table[fromIndex][toIndex] = std::move(factory);
}

// ----------------------------------------------------------------------------
unique_ptr<ICalculatable> TypeCastFactory::CreateTypeCast(unique_ptr<ICalculatable> what, ValueType castTo) const
{
	const auto typeFromIndex = static_cast<std::size_t>(what->GetType());
	const auto typeToIndex   = static_cast<std::size_t>(castTo);
	
	if (!m_table[typeFromIndex][typeToIndex])
		return std::unique_ptr<ICalculatable>();

	return m_table[typeFromIndex][typeToIndex]->Create(std::move(what));
}

// ----------------------------------------------------------------------------
optional<ValueType> TypeCastFactory::CalculateCommonTypeOf(std::set<ValueType>& types) const
{
	for (auto typeCastTo : types)
	{
		bool match = true;
		for (auto typeCastFrom : types)
		{
			if (typeCastFrom != typeCastTo && !TypeCastExists(typeCastFrom, typeCastTo))
			{
				match = false;
				break;
			}
		}

		if (match)
			return typeCastTo;
	}

	return std::nullopt;
}

// ----------------------------------------------------------------------------
bool TypeCastFactory::TypeCastExists(ValueType castFrom, ValueType castTo) const
{
	const auto typeFromIndex = static_cast<std::size_t>(castFrom);
	const auto typeToIndex   = static_cast<std::size_t>(castTo);

	return bool(m_table[typeFromIndex][typeToIndex]);
}

// ----------------------------------------------------------------------------