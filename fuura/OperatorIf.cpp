#include "stdafx.h"
#include "OperatorIf.h"
#include "ToString.h"
#include "Exception.h"
#include "TypeCastFactory.h"
using namespace fuura;
using namespace fuura::language;
using namespace fuura::tools;
using namespace std;

void OperatorIf::CheckBoolType(ValueType type, antlr4::Token* token)
{
	if (type != ValueType::Bool)
	{
		throw SyntaxError(
			std::string("��������� ������ ������� if ������ ����� ��� ")
			+ ToString(ValueType::Bool) + ", ������ ����� ���������� " + ToString(type),
			token->getLine(), token->getCharPositionInLine());
	}
}

// ----------------------------------------------------------------------------
OperatorIf::OperatorIf(std::unique_ptr<ICalculatable> condition, std::unique_ptr<ICalculatable> expression, antlr4::Token* token)
{
	CheckBoolType(condition->GetType(), token);
	m_branches.push_back(Pair(std::move(condition), std::move(expression)));
}

// ----------------------------------------------------------------------------
void OperatorIf::ElseIf(std::unique_ptr<ICalculatable> condition, std::unique_ptr<ICalculatable> expression, antlr4::Token* token)
{
	CheckBoolType(condition->GetType(), token);
	m_branches.push_back(Pair(std::move(condition), std::move(expression)));
}

// ----------------------------------------------------------------------------
void OperatorIf::Else(std::unique_ptr<ICalculatable> expression, antlr4::Token* token, const TypeCastFactory& tcFactory)
{
	m_else = std::move(expression);

	// ���������, ���������� �� ����.
	set<ValueType> types;
	for (auto& pair : m_branches)
		types.insert(pair.second->GetType());
	types.insert(m_else->GetType());
	auto commonType = tcFactory.CalculateCommonTypeOf(types);

	// ���� ���� ������������, �� ���������� ������.
	if (!commonType.has_value())
	{
		string message("�� ������� �������� ����� if (������� else) � ������� ����. ������������ ���� ������ �� �������: ");
		for (auto& pair : m_branches)
			message += ToString(pair.second->GetType()) + ", ";
		message += ToString(m_else->GetType());
		
		throw SyntaxError(message, token->getLine(), token->getCharPositionInLine());
	}

	// ���� ���� ����������, �� ���������� �������������� � ������ ���� �� �� �����, ��� ������� ��� ���������.
	m_commonType = *commonType;
	for (auto& pair : m_branches)
	{
		if (pair.second->GetType() != m_commonType)
			pair.second = tcFactory.CreateTypeCast(move(pair.second), m_commonType);
	}
}

// ----------------------------------------------------------------------------
Value OperatorIf::Calculate() const
{
	for (auto& pair : m_branches)
		if (pair.first->Calculate().boolValue)
			return pair.second->Calculate();

	return m_else->Calculate();
}

// ----------------------------------------------------------------------------
ValueType OperatorIf::GetType() const
{
	return m_commonType;
}

// ----------------------------------------------------------------------------
