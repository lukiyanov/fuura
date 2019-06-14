#pragma once
#include <memory>
#include <list>

#include "ICalculatable.h"
#include "IArgumentSet.h"
#include "Convert.h"
#include "GetValueType.h"
#include "Token.h"

namespace fuura::language
{
	class TypeCastFactory;

	// ------------------------------------------------------------------------
	// if (...) ... else ... ;
	// все ветви должны быть совместимого типа, включа€ else.
	// все услови€ должны быть типа bool.
	// ------------------------------------------------------------------------
	class OperatorIf : public ICalculatable
	{
		using Pair = std::pair<std::unique_ptr<ICalculatable>, std::unique_ptr<ICalculatable>>;

		std::list<Pair> m_branches;
		std::unique_ptr<ICalculatable> m_else;

		// “ип, к которому привод€тс€ все ветви оператора.
		ValueType m_commonType;

	private:
		// --------------------------------------------------------------------
		// ѕровер€ет, действительно ли полученный тип €вл€етс€ булевским
		// и если нет, то генерирует исключение.
		// --------------------------------------------------------------------
		void CheckBoolType(ValueType type, antlr4::Token* token);

	public:
		// --------------------------------------------------------------------
		OperatorIf(std::unique_ptr<ICalculatable> condition, std::unique_ptr<ICalculatable> expression, antlr4::Token* token);

		// --------------------------------------------------------------------
		void ElseIf(std::unique_ptr<ICalculatable> condition, std::unique_ptr<ICalculatable> expression, antlr4::Token* token);

		// --------------------------------------------------------------------
		// NB: ветка else должна присутствовать всегда, поэтому именно в ней мы подводим итоги
		// о корректности задани€ оператора.
		void Else(std::unique_ptr<ICalculatable> expression, antlr4::Token* token, const TypeCastFactory& tcFactory);

		// --------------------------------------------------------------------
		Value Calculate() const override;

		// --------------------------------------------------------------------
		ValueType GetType() const override;
	};

	// ------------------------------------------------------------------------
}