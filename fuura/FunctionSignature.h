#pragma once
#include "Value.h"
#include "GetValueType.h"

namespace fuura::tools
{
	// ---------------------------------------------------------------------------
	// Раскручивает список аргументов и возвращает тип аргумента с индексом N.
	// Нумерация индексов с нуля. Является частью FunctionSignature.
	// ---------------------------------------------------------------------------
	namespace
	{
		template <typename ...Args> struct ArgumentListTypeUnpacker;

		template <> struct ArgumentListTypeUnpacker<>
		{
			static fuura::ValueType GetType(size_t argumentIndex)
			{
				throw std::out_of_range("Выход за границы списка аргументов в tools::GetType().");
			}
		};

		template <typename This, typename ...Rest> struct ArgumentListTypeUnpacker<This, Rest...>
			: public ArgumentListTypeUnpacker<Rest...>
		{
			constexpr static fuura::ValueType GetType(size_t argumentIndex)
			{
				if (argumentIndex != 0)
					return ArgumentListTypeUnpacker<Rest...>::GetType(argumentIndex - 1);
				else
					return fuura::tools::GetValueType<This>();
			}
		};
	}

	///////////////////////////////////////////////////////////////////////////
	//
	//	Раскладывает тип функции на результат и аргументы.
	//	-----------------------------------------------------------------------
	//	FunctionSignature<F>::Result				- тип результата F.
	//	FunctionSignature<F>::ArgCount			- количество аргументов F.
	//	FunctionSignature<F>::GetArgumentType(2)	- получить тип аргумента F с индексом 2,
	//											т.е. третьего, если считать с единицы.
	///////////////////////////////////////////////////////////////////////////
	template <typename ...Args> struct FunctionSignature;

	template <typename ResultType, typename ...Args>
	struct FunctionSignature<ResultType(Args...)>
	{
		// Тип результата функции.
		using Result = ResultType;

		// Количество аргументов функции.
		enum { ArgCount = sizeof ...(Args) };

		// Получает тип аргумента функции по его номеру. Нумерация с 0.
		constexpr static fuura::ValueType GetArgumentType(size_t argumentIndex)
		{
			return ArgumentListTypeUnpacker<Args...>::GetType(argumentIndex);
		}
	};

	///////////////////////////////////////////////////////////////////////////
}