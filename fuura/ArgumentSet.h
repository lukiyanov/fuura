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
	//	Реализует набор аргументов функции.
	//	Один раз выделяет память под все аргументы и затем позволяет устанавливать
	//	их значения (все разом) или получать о них информацию, в т.ч. значение.
	//
	//////////////////////////////////////////////////////////////////////////////
	template <typename ...Args>
	class ArgumentSet : public IArgumentSet
	{
	public:
		// --------------------------------------------------------------------------
		// Регистр имён аргументов не различается.
		// --------------------------------------------------------------------------
		ArgumentSet(ArgumentNameList<sizeof ... (Args)>&& argNames);

		// --------------------------------------------------------------------------
		// Получает информацию по указанному аргументу, генерирует исключение если
		// аргумент с таким именем не был найден.
		// Не различает регистров.
		// --------------------------------------------------------------------------
		ArgumentInfo GetArgumentInfo(std::string_view name, antlr4::Token* tokenInfo) override;

		// --------------------------------------------------------------------------
		// Устанавливает значения хранимых аргументов в args.
		// --------------------------------------------------------------------------
		void SetArgumentValues(Args... args);


	private:
		// --------------------------------------------------------------------------
		// Заполняет m_argumentInfo.
		// --------------------------------------------------------------------------
		void FillArgumentInfo(ArgumentNameList<sizeof... (Args)>&& argNames);

		// --------------------------------------------------------------------------
		// Добавляет в словарь m_argumentInfo соответствующую запись,
		// проверяя при этом отсутствие записей с таким ключом.
		// --------------------------------------------------------------------------
		void InsertArgumentToMap(size_t argumentIndex, std::string_view name, ValueType type);


	private:
		constexpr static std::size_t ARG_COUNT = sizeof ...(Args);

		// Тут хранятся текущие значения аргументов функции.
		// Значения эти не должны ни копироваться, ни перемещаться из этой памяти, потому что:
		// 1. На эти АДРЕСА ссылаются элементы m_argumentInfo.
		// 2. На эти АДРЕСА ссылается интерпретируемый код после прохождения этапа парсинга.
		std::unique_ptr<Value[]> m_argumentValues = std::make_unique<Value[]>(ARG_COUNT);

		// Имя аргумента -> { информация о нём }
		std::map<std::string, ArgumentInfo> m_argumentInfo;
	};

	//////////////////////////////////////////////////////////////////////////////

	// Специализация для случая без аргументов.
	template <>
	class ArgumentSet<> : public IArgumentSet
	{
	public:
		ArgumentSet(ArgumentNameList<0>&& argNames) {}
		void SetArgumentValues() {}
		ArgumentInfo GetArgumentInfo(std::string_view name, antlr4::Token* tokenInfo) override
		{
			throw SyntaxError(
				std::string("Аргумент с именем \"") + name.data() + "\" не обнаружен",
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
				std::string("Аргумент с именем \"") + name.data() + "\" не обнаружен",
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
			// В name - имя текущего аргумента.
			const auto name = argNames.arguments[i].argName;
			if (name.empty())
			{
				throw std::exception(
					(std::string("В качестве имени аргумента №") + tools::ToString(i) + " передана пустая строка.").c_str()
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
		// Создаём новую запись словаря.
		std::pair<std::string, ArgumentInfo> pair(
			tools::ToLower(name.data()),
			{ type, &(m_argumentValues[argumentIndex]) }
		);

		// Пытаемся вставить созданную запись в словарь.
		bool inserted;
		std::tie(std::ignore, inserted) = m_argumentInfo.insert(std::move(pair));
		if (!inserted)
		{
			throw std::exception(
				(std::string("Аргумент с именем ") + name.data() + " объявлен дважды.").c_str()
			);
		}
	}

	// --------------------------------------------------------------------------
}