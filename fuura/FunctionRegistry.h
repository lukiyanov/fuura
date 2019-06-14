#pragma once
#include <string>
#include <string_view>

#include "ICalculatable.h"
#include "FunctionWrapper.h"

#include "OverloadedFunctionSet.h"
#include "Token.h"
#include "Convert.h"

namespace fuura::language
{
	class FuuraSemantics;
	enum class MatchState { FullMatch, MatchWithCast, Mismatch };

	///////////////////////////////////////////////////////////////////////////
	//
	//	������ �������, ��������� ��� ������ �� fuura-����.
	//	�� �� ������ ������������ ��� ������ ������� ICalculatable.
	//	������������ ���������� �������, ��� �� ����� ����������, ��� � �� ��
	//	�����. ��������� ������� �������������� �����.
	//
	///////////////////////////////////////////////////////////////////////////
	class FunctionRegistry
	{
	public:
		// --------------------------------------------------------------------
		// ������������ ��������� ��� ������������� �������.
		// ���� ������� � ����� ������ � ����������� ��� ����������������,
		// ������������ ����������.
		// --------------------------------------------------------------------
		template <typename FunctionType>
		void RegisterFunction(std::string_view name, FunctionType* func);

		// --------------------------------------------------------------------
		// ������ ������, ����������� ����� ������� � ����������� �����������,
		// ���� �� ���������� ���������� ���� ��� ����������.
		//
		// ��� ���������� ����� ���������� �������:
		//	1. ���� ������� � ����� ������ �� �������, ���������� ����������
		//	2. �������� ���������� � ����������� ������ ����������
		//	3. ���� ����� ���, ���������� ����������
		//	4. ����� ��� ���� ������ ���������� ����������
		//	5. ���� ����� ����� ������� - ���������� �
		//	6. ���� ����� ���, �� ���� ����������, ���� ���������� ������� ����� �������� �� ��������� ����������� ����������
		//	7. ���� ����� ���������, ���������� ����������
		//	8. ���� ����� ���, ���������� ����������
		//	9. ���������� ��������� ����������
		//
		// --------------------------------------------------------------------
		std::unique_ptr<ICalculatable> CreateFunction(std::string_view name, std::list<std::unique_ptr<ICalculatable>>& args, FuuraSemantics& semantics, antlr4::Token* tokenInfo);

	private:
		std::pair<MatchState, std::unique_ptr<IFunctionWrapper>> FindFunction(std::string_view name, std::list<std::unique_ptr<ICalculatable>>& argTypes, FuuraSemantics& semantics, antlr4::Token* tokenInfo);

	private:
		// ������������������ �������.
		std::map<std::string, OverloadedFunctionSet> m_functions;
	};

	///////////////////////////////////////////////////////////////////////////

	// ------------------------------------------------------------------------
	template <typename FunctionType>
	void FunctionRegistry::RegisterFunction(std::string_view name, FunctionType* func)
	{
		const auto nameLower = tools::ToLower(name);
		auto iter = m_functions.find(nameLower);

		// ����� ���� ������� � ����� ������ -> ��������� � �������.
		if (iter != m_functions.end())
		{
			iter->second.Insert(std::make_unique<FunctionWrapper<FunctionType>>(func));
			return;
		}

		// ���� ������� � ����� ������ ����������� -> ������ ��� � ��������� � ���� �������.
		std::pair<std::string, OverloadedFunctionSet> pair;
		pair.first = nameLower;
		pair.second.Insert(std::make_unique<FunctionWrapper<FunctionType>>(func));
		m_functions.insert(std::move(pair));
	}

	// ------------------------------------------------------------------------
}