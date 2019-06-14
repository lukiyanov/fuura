#include "stdafx.h"
#include "FunctionRegistry.h"
#include "Exception.h"
#include "ToString.h"
#include "FuuraSemantics.h"
#include "FunctionCall.h"
using namespace fuura;
using namespace fuura::language;
using namespace std;

// ----------------------------------------------------------------------------
namespace fuura::language
{
	// ------------------------------------------------------------------------
	// ���������� ������ ����: "���(���1, ���2, ���3)"
	// ------------------------------------------------------------------------
	string FunctionToString(list<unique_ptr<ICalculatable>>& argTypes, string_view name = "")
	{
		std::string str = name.data();
		str += '(';
		if (argTypes.size())
		{
			auto iter = argTypes.begin();
			str += tools::ToString((*iter)->GetType());
			++iter;
			for (auto end = argTypes.end(); iter != end; ++iter)
				str += ", " + tools::ToString((*iter)->GetType());
		}
		str += ')';
		return str;
	}
}

// ----------------------------------------------------------------------------
// ���������� ������� ������������ ���������� ������� wrapper ����������,
// ���������� ����� args � ������ ��������� �������������� �����,
// ������������ � typeCastFactory.
// ----------------------------------------------------------------------------
MatchState CalculateMatchState(IFunctionWrapper& wrapper, list<unique_ptr<ICalculatable>>& argTypes, TypeCastFactory& typeCastFactory)
{
	auto currentFuncArgs = wrapper.GetArgumentTypes();
	auto matchState = MatchState::FullMatch;
	auto originalArgsIter = argTypes.begin();
	for (size_t argNum = 0, argCount = argTypes.size(); argNum < argCount; ++argNum, ++originalArgsIter)
	{
		const ValueType expected = currentFuncArgs[argNum];
		const ValueType actual = (*originalArgsIter)->GetType();
		// ���� �� ��������� ��������� ���� �� ���������...
		if (expected != actual)
		{
			// �������� ����� �������������� �� ���������� ���� � �������...
			if (typeCastFactory.TypeCastExists(actual, expected))
			{
				// ���� ��� ����, �� ������������� ��� ������� ��������, �� ��������� ���������� �����.
				matchState = MatchState::MatchWithCast;
			}
			else
			{
				// ���� ��������������� ���, �� ������������� ��� ������ ������� �� �������� ���������.
				// � ����� �� ��������� � ���������� ��������.
				matchState = MatchState::Mismatch;
				break;
			}
		}
	}

	return matchState;
}

// ----------------------------------------------------------------------------
// ��������� � ���������� � args �������������� �� ����� types, ��������� ��������� �������������� �� semantics.
// ----------------------------------------------------------------------------
void CastArgsTo(list<unique_ptr<ICalculatable>>& args, vector<ValueType>&& types, FuuraSemantics& semantics)
{
	auto& typeCastFactory = semantics.GetImplicitTypeCastFactory();

	auto argument = args.begin();
	for (auto type = types.begin(), end = types.end(); type != end; ++type, ++argument)
	{
		if ((*argument)->GetType() != *type)
			*argument = typeCastFactory.CreateTypeCast(move(*argument), *type);
	}
}

// ----------------------------------------------------------------------------
// ��� ���������� ����� ���������� �������:
//	1. ���� ������� � ����� ������ �� �������, ���������� ����������
//	2. �������� ���������� � ����������� ������ ����������
//	3. ���� ����� ���, ���������� ����������
//	4. ����� ��� ���� ������� � ������ ����������� ����������
//	5. ���� ����� - ���������� �
//	6. ���� ����������, ���� ���������� ������� ����� �������� �� ��������� ����������� ����������
//	7. ���� ����� ���������, ���������� ����������
//	8. ���� ����� ���, ���������� ����������
//	9. ���������� ��������� ����������
// --------------------------------------------------------------------
pair<MatchState, unique_ptr<IFunctionWrapper>> FunctionRegistry::FindFunction(string_view name, list<unique_ptr<ICalculatable>>& args, FuuraSemantics& semantics, antlr4::Token * tokenInfo)
{
	const auto nameLower = tools::ToLower(name);
	auto iter = m_functions.find(nameLower);

	// 1. ���� ������� � ����� ������ �� �������, ���������� ����������
	if (iter == m_functions.end())
	{
		throw SyntaxError(string("������� � ������ \"") + nameLower + "\" �� �������.",
			tokenInfo->getLine(), tokenInfo->getCharPositionInLine());
	}

	// 2. �������� ���������� � ����������� ������ ����������
	const auto argCount = args.size();
	auto funcsFixed = iter->second.Find(argCount);

	//	3. ���� ����� ���, ���������� ����������
	if (!funcsFixed)
	{
		throw SyntaxError(string("��� ������� � ������ \"") + nameLower + "\" ��� ������������� ����������, ����������� " + tools::ToString(argCount) + " ����������.",
			tokenInfo->getLine(), tokenInfo->getCharPositionInLine());
	}
	
	//	4. ����� ��� ���� ������ ���������� ����������
	// (� ������ ������� ���� ��� ���������� �������� ����� �� ������������� ������ ������)
	auto& typeCastFactory = semantics.GetImplicitTypeCastFactory();

	// ������������ ���� ������ ������������ �� �������:
	IFunctionWrapper* matchWithCastWrapper = nullptr;		// ������ �� ���������, � �������� ����� �������� ���������
	bool notMonosemanticError = false;						// ���������� 2 ��� ����� ���������, � ������� �� ������� ����� �������� ���������

	for (auto ppWrapper = funcsFixed->Begin(), end = funcsFixed->End(); ppWrapper != end; ++ppWrapper)
	{
		// ������� �������.
		IFunctionWrapper& wrapper = **ppWrapper;

		// ���������� ������� ���������� ������� ������� ������� ������������ ����������.
		auto matchState = CalculateMatchState(wrapper, args, typeCastFactory);

		// 5. ���� ����� ������� � ������ ����������� - ���������� � �����.
		if (matchState == MatchState::FullMatch)
			return pair(MatchState::FullMatch, unique_ptr<IFunctionWrapper>(wrapper.Clone()));

		//	6. ���� ����������, ���� ���������� ������� ����� �������� �� ��������� ����������� ����������
		// ��� ������ ���������� ��������, � �������� ����� ��������, ���� ������� ������������.
		// ��� ������ - ��������������� ���� ���������������, �� ������ ���� �� ������������ � �������
		// ����� ����� ������ ������������ ����������.
		if (matchState == MatchState::MatchWithCast)
		{
			if (!matchWithCastWrapper)
				matchWithCastWrapper = &wrapper;
			else
				notMonosemanticError = true;
		}
	}

	// ��������� ��� ��������. ������� ������������ �� �������.

	//	7. ���� ����� � ������� ����� �������� ���������������� ���������� ���������, ���������� ����������.
	if (notMonosemanticError)
	{
		throw SyntaxError(string("������������� �����: ") + FunctionToString(args, name),
			tokenInfo->getLine(), tokenInfo->getCharPositionInLine());
	}

	//	8. ���� ����� � ������� ����� �������� ���������������� ���������� ��� ������, ���������� ����������.
	if (!matchWithCastWrapper)
	{
		throw SyntaxError(string("��� ���������� ������� \"") + nameLower + "\", ����������� � �������: " + FunctionToString(args, name),
			tokenInfo->getLine(), tokenInfo->getCharPositionInLine());
	}

	//	9. ���������� ��������� ����������
	return pair(MatchState::MatchWithCast, unique_ptr<IFunctionWrapper>(matchWithCastWrapper->Clone()));
}

// ----------------------------------------------------------------------------
unique_ptr<ICalculatable> FunctionRegistry::CreateFunction(string_view name, list<unique_ptr<ICalculatable>>& args, FuuraSemantics& semantics, antlr4::Token * tokenInfo)
{
	auto [match, func] = FindFunction(name, args, semantics, tokenInfo);
	if (match == MatchState::MatchWithCast)
		CastArgsTo(args, func->GetArgumentTypes(), semantics);
	return make_unique<FunctionCall>(move(func), args);
}

// ----------------------------------------------------------------------------
