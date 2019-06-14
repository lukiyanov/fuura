#pragma once
#include <array>
#include <map>
#include <tuple>
#include <string>
#include <string_view>

#include "Value.h"
#include "ArgumentNameList.h"
#include "FunctionSignature.h"
#include "ArgumentInfo.h"
#include "Convert.h"
#include "Exception.h"
#include "Token.h"
#include "ToString.h"
#include "IArgumentSet.h"

namespace fuura
{
	//////////////////////////////////////////////////////////////////////////////
	//
	//	��������� ����� ���������� �������.
	//	���� ��� �������� ������ ��� ��� ��������� � ����� ��������� �������������
	//	�� �������� (��� �����) ��� �������� � ��� ����������, � �.�. ��������.
	//
	//////////////////////////////////////////////////////////////////////////////
	template <typename ...Args>
	class ArgumentSet : public IArgumentSet
	{
	public:
		// --------------------------------------------------------------------------
		// ������� ��� ���������� �� �����������.
		// --------------------------------------------------------------------------
		ArgumentSet(ArgumentNameList<sizeof ... (Args)>&& argNames);

		// --------------------------------------------------------------------------
		// �������� ���������� �� ���������� ���������, ���������� ���������� ����
		// �������� � ����� ������ �� ��� ������.
		// �� ��������� ���������.
		// --------------------------------------------------------------------------
		ArgumentInfo GetArgumentInfo(std::string_view name, antlr4::Token* tokenInfo) override;

		// --------------------------------------------------------------------------
		// ������������� �������� �������� ���������� � args.
		// --------------------------------------------------------------------------
		void SetArgumentValues(Args... args);


	private:
		// --------------------------------------------------------------------------
		// ��������� m_argumentInfo.
		// --------------------------------------------------------------------------
		void FillArgumentInfo(ArgumentNameList<sizeof... (Args)>&& argNames);

		// --------------------------------------------------------------------------
		// ��������� � ������� m_argumentInfo ��������������� ������,
		// �������� ��� ���� ���������� ������� � ����� ������.
		// --------------------------------------------------------------------------
		void InsertArgumentToMap(size_t argumentIndex, std::string_view name, ValueType type);


	private:
		constexpr static std::size_t ARG_COUNT = sizeof ...(Args);

		// ��� �������� ������� �������� ���������� �������.
		// �������� ��� �� ������ �� ������������, �� ������������ �� ���� ������, ������ ���:
		// 1. �� ��� ������ ��������� �������� m_argumentInfo.
		// 2. �� ��� ������ ��������� ���������������� ��� ����� ����������� ����� ��������.
		std::unique_ptr<Value[]> m_argumentValues = std::make_unique<Value[]>(ARG_COUNT);

		// ��� ��������� -> { ���������� � �� }
		std::map<std::string, ArgumentInfo> m_argumentInfo;
	};

	//////////////////////////////////////////////////////////////////////////////

	// ������������� ��� ������ ��� ����������.
	template <>
	class ArgumentSet<> : public IArgumentSet
	{
	public:
		ArgumentSet(ArgumentNameList<0>&& argNames) {}
		void SetArgumentValues() {}
		ArgumentInfo GetArgumentInfo(std::string_view name, antlr4::Token* tokenInfo) override
		{
			throw SyntaxError(
				std::string("�������� � ������ \"") + name.data() + "\" �� ���������",
				tokenInfo->getLine(),
				tokenInfo->getCharPositionInLine()
			);
		}
	};

	//////////////////////////////////////////////////////////////////////////////

	// --------------------------------------------------------------------------
	template <typename ...Args>
	ArgumentSet<Args...>::ArgumentSet(ArgumentNameList<sizeof ... (Args)>&& argNames)
	{
		FillArgumentInfo(std::move(argNames));
	}

	// --------------------------------------------------------------------------
	template <typename ...Args>
	ArgumentInfo ArgumentSet<Args...>::GetArgumentInfo(std::string_view name, antlr4::Token* tokenInfo)
	{
		const auto nameLower = tools::ToLower(name);
		auto iter = m_argumentInfo.find(nameLower);
		if (iter == m_argumentInfo.end())
		{
			throw SyntaxError(
				std::string("�������� � ������ \"") + name.data() + "\" �� ���������",
				tokenInfo->getLine(),
				tokenInfo->getCharPositionInLine()
			);
		}

		return iter->second;
	}

	// --------------------------------------------------------------------------
	template <typename ...Args>
	void ArgumentSet<Args...>::SetArgumentValues(Args... args)
	{
		int CurrentArgumentIndex = 0;

		((m_argumentValues[CurrentArgumentIndex++] = args), ...);
	}

	// --------------------------------------------------------------------------
	template <typename ...Args>
	void ArgumentSet<Args...>::FillArgumentInfo(ArgumentNameList<sizeof... (Args)>&& argNames)
	{
		for (int i = 0; i < ARG_COUNT; i++)
		{
			// � name - ��� �������� ���������.
			const auto name = argNames.arguments[i].argName;
			if (name.empty())
			{
				throw std::exception(
					(std::string("� �������� ����� ��������� �") + tools::ToString(i) + " �������� ������ ������.").c_str()
				);
			}

			using MyCallback = tools::FunctionSignature<void(Args...)>;
			InsertArgumentToMap(i, name, MyCallback::GetArgumentType(i));
		}
	}

	// --------------------------------------------------------------------------
	template <typename ...Args>
	void ArgumentSet<Args...>::InsertArgumentToMap(size_t argumentIndex, std::string_view name, ValueType type)
	{
		// ������ ����� ������ �������.
		std::pair<std::string, ArgumentInfo> pair(
			tools::ToLower(name.data()),
			{ type, &(m_argumentValues[argumentIndex]) }
		);

		// �������� �������� ��������� ������ � �������.
		bool inserted;
		std::tie(std::ignore, inserted) = m_argumentInfo.insert(std::move(pair));
		if (!inserted)
		{
			throw std::exception(
				(std::string("�������� � ������ ") + name.data() + " �������� ������.").c_str()
			);
		}
	}

	// --------------------------------------------------------------------------
}