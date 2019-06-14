#pragma once
#include <vector>
#include "Value.h"
#include "GetValueType.h"
#include "UnpackAndCall.h"
#include "ForEach.h"
#include "ToString.h"

namespace fuura::language
{
	///////////////////////////////////////////////////////////////////////////
	//
	//	Позволяет абстрагироваться от типов аргументов и возвращаемого
	//	значения функции, сохраняя при этом возможность её выполнить или
	//	получить её адрес.
	//
	//	Вся ответственность за несовпадение типов аргументов - на пользователе
	//	класса.
	//
	///////////////////////////////////////////////////////////////////////////
	class IFunctionWrapper
	{
	public:
		// --------------------------------------------------------------------
		// Возвращает число параметров.
		// --------------------------------------------------------------------
		virtual size_t GetArgumentCount() const = 0;

		// --------------------------------------------------------------------
		// Возвращает типы параметров аргументов по порядку.
		// --------------------------------------------------------------------
		virtual std::vector<ValueType> GetArgumentTypes() const = 0;

		// --------------------------------------------------------------------
		// Получает тип, возвращаемый функцией.
		// --------------------------------------------------------------------
		virtual ValueType GetResultType() const = 0;

		// --------------------------------------------------------------------
		// Выполняет функцию на заданном наборе аргументов.
		// --------------------------------------------------------------------
		virtual Value Execute(std::vector<Value>& argValues) const = 0;

		// --------------------------------------------------------------------
		// Создаёт копию объекта.
		// --------------------------------------------------------------------
		virtual IFunctionWrapper* Clone() const = 0;

		// --------------------------------------------------------------------
		// Определяет равенство по точному совпадению сигнатуры функции.
		// --------------------------------------------------------------------
		virtual bool operator == (const IFunctionWrapper& wrapper) const
		{
			auto myArgs  = GetArgumentTypes();
			auto hisArgs = wrapper.GetArgumentTypes();
			return myArgs == hisArgs && GetResultType() == wrapper.GetResultType();
		}

		// --------------------------------------------------------------------
		virtual bool operator != (const IFunctionWrapper& wrapper) const
		{
			return !(*this == wrapper);
		}

		// --------------------------------------------------------------------
	};

	///////////////////////////////////////////////////////////////////////////
	//
	//	Реализация обёртки для конкретной функции.
	//
	///////////////////////////////////////////////////////////////////////////
	template <class FuncSignature>
	class FunctionWrapper;

	template <class ResultType, typename ...Args>
	class FunctionWrapper<ResultType(Args...)> : public IFunctionWrapper
	{
	public:
		// --------------------------------------------------------------------
		using FunctionType = ResultType(Args...);

		// --------------------------------------------------------------------
		FunctionWrapper(FunctionType* func);

		// --------------------------------------------------------------------
		size_t GetArgumentCount() const override;

		// --------------------------------------------------------------------
		std::vector<ValueType> GetArgumentTypes() const override;

		// --------------------------------------------------------------------
		ValueType GetResultType() const override;

		// --------------------------------------------------------------------
		IFunctionWrapper* Clone() const override;

		// --------------------------------------------------------------------
		Value Execute(std::vector<Value>& argValues) const override;

	private:
		FunctionType* m_function;
	};

	///////////////////////////////////////////////////////////////////////////

	// ------------------------------------------------------------------------
	template <class ResultType, typename ...Args>
	FunctionWrapper<ResultType(Args...)>::FunctionWrapper(FunctionType* func)
		: m_function(func)
	{}

	// --------------------------------------------------------------------
	template <class ResultType, typename ...Args>
	IFunctionWrapper* FunctionWrapper<ResultType(Args...)>::Clone() const
	{
		return new FunctionWrapper<ResultType(Args...)>(m_function);
	}

	// --------------------------------------------------------------------
	template <class ResultType, typename ...Args>
	size_t FunctionWrapper<ResultType(Args...)>::GetArgumentCount() const
	{
		return sizeof ... (Args);
	}

	// --------------------------------------------------------------------
	template <class ResultType, typename ...Args>
	std::vector<ValueType> FunctionWrapper<ResultType(Args...)>::GetArgumentTypes() const
	{
		std::vector<ValueType> argTypes(sizeof ... (Args));

		auto functor = [&argTypes](int index, ValueType type) { argTypes[index] = type; };
		tools::ForEach<decltype(functor), Args...>::Do(functor);

		return argTypes;
	}

	// --------------------------------------------------------------------
	template <class ResultType, typename ...Args>
	ValueType FunctionWrapper<ResultType(Args...)>::GetResultType() const
	{
		// Тут же мы отсеиваем типы, не конвертируемые в fuura-типы,
		// т.е. для которых нет соответствия в перечислении ValueType.
		return tools::GetValueType<ResultType>();
	}


	// --------------------------------------------------------------------
	template <class ResultType, typename ...Args>
	Value FunctionWrapper<ResultType(Args...)>::Execute(std::vector<Value>& argValues) const
	{
		if (argValues.size() != sizeof ... (Args))
			throw std::out_of_range("Неподходящее число аргументов при вызове функции.");

		return tools::UnpackAndCall<sizeof ... (Args), FunctionType*>::Do(m_function, argValues);
	}

	// --------------------------------------------------------------------
	inline std::string FunctionToString(IFunctionWrapper* func, std::string_view name = "")
	{
		std::string str = tools::ToString(func->GetResultType()) + ' ' + name.data() + '(';
		auto args = func->GetArgumentTypes();
		if (args.size())
		{
			str += tools::ToString(args[0]);
			for (size_t i = 1, size = args.size(); i < size; i++)
				str += ", " + tools::ToString(args[i]);
		}
		str += ')';
		return str;
	}

	// ------------------------------------------------------------------------
}
