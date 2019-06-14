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
	//	Реестр функций, доступных для вызова из fuura-кода.
	//	Он же создаёт производящие эти вызовы объекты ICalculatable.
	//	Поддерживает перегрузку функций, как по числу параметров, так и по их
	//	типам. Учитывает неявные преобразования типов.
	//
	///////////////////////////////////////////////////////////////////////////
	class FunctionRegistry
	{
	public:
		// --------------------------------------------------------------------
		// Регистрирует доступную для использования функцию.
		// Если функция с таким именем и параметрами уже зарегистрирована,
		// генерируется исключение.
		// --------------------------------------------------------------------
		template <typename FunctionType>
		void RegisterFunction(std::string_view name, FunctionType* func);

		// --------------------------------------------------------------------
		// Создаёт объект, выполняющий вызов функции с полученными аргументами,
		// либо же генерирует исключение если это невозможно.
		//
		// Как происходит поиск подходящей функции:
		//	1. Если функция с таким именем не найдена, генерируем исключение
		//	2. Отбираем реализации с совпадающим числом аргументов
		//	3. Если таких нет, генерируем исключение
		//	4. Среди них ищем точное совпадение аргументов
		//	5. Если нашли такую функцию - возвращаем её
		//	6. Если такой нет, то ищем реализацию, типы аргументов которой можно получить из имеющихся приведением аргументов
		//	7. Если таких несколько, генерируем исключение
		//	8. Если таких нет, генерируем исключение
		//	9. Возвращаем найденную реализацию
		//
		// --------------------------------------------------------------------
		std::unique_ptr<ICalculatable> CreateFunction(std::string_view name, std::list<std::unique_ptr<ICalculatable>>& args, FuuraSemantics& semantics, antlr4::Token* tokenInfo);

	private:
		std::pair<MatchState, std::unique_ptr<IFunctionWrapper>> FindFunction(std::string_view name, std::list<std::unique_ptr<ICalculatable>>& argTypes, FuuraSemantics& semantics, antlr4::Token* tokenInfo);

	private:
		// Зарегистрированные функции.
		std::map<std::string, OverloadedFunctionSet> m_functions;
	};

	///////////////////////////////////////////////////////////////////////////

	// ------------------------------------------------------------------------
	template <typename FunctionType>
	void FunctionRegistry::RegisterFunction(std::string_view name, FunctionType* func)
	{
		const auto nameLower = tools::ToLower(name);
		auto iter = m_functions.find(nameLower);

		// Нашли блок функций с таким именем -> добавляем и выходим.
		if (iter != m_functions.end())
		{
			iter->second.Insert(std::make_unique<FunctionWrapper<FunctionType>>(func));
			return;
		}

		// Блок функций с таким именем отсутствуем -> создаём его и добавляем в него функцию.
		std::pair<std::string, OverloadedFunctionSet> pair;
		pair.first = nameLower;
		pair.second.Insert(std::make_unique<FunctionWrapper<FunctionType>>(func));
		m_functions.insert(std::move(pair));
	}

	// ------------------------------------------------------------------------
}