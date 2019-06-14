#pragma once
#include <memory>
#include <string>
#include <string_view>
#include <cmath>
#include <vector>

#include "ICalculatable.h"
#include "IArgumentSet.h"
#include "Convert.h"
#include "GetValueType.h"
#include "Token.h"

//#include "Dependencies.h" (TODO: удалить весь закомментированный код в файле после рефракторинга)

namespace fuura::language
{
	// ------------------------------------------------------------------------
	//  онстанта простого типа, заданна€ в коде.
	template <typename T>
	class Constant : public ICalculatable
	{
		const Value m_value;

	public:

		Constant(const std::string& source)
			: m_value(tools::StrToType<T>(source))
		{}

		Value Calculate() const override
		{
			return m_value;
		}

		ValueType GetType() const override
		{
			return fuura::tools::GetValueType<T>();
		}

		//compilation::IRegisterPlaceholder* GenerateFlow(compilation::ExecutionFlow& executionFlow, compilation::VirtualRegisterManager& tempValues) const override;

		/*
		{
			using namespace compilation;

			IAsmInstruction* dep = new compilation::Constant<T>(tempValues, Calculate());
			executionFlow.PushBack(std::unique_ptr<IAsmInstruction>(dep));
			return dep->GetResult();
		}*/
	};

	// ------------------------------------------------------------------------
	// јргумент (переменна€)
	class Argument : public ICalculatable
	{
		Value*      m_value;
		ValueType   m_type;
		std::string m_name;

	public:
		Argument(std::string_view name, IArgumentSet& args, antlr4::Token* tokenInfo)
			: m_name(name.data())
		{
			auto info = args.GetArgumentInfo(name, tokenInfo);
			m_value = info.pointerToValue;
			m_type = info.type;
		}

		Value Calculate() const override
		{
			return *m_value;
		}

		ValueType GetType() const override
		{
			return m_type;
		}
	};

	// ------------------------------------------------------------------------
	// -a
	template <typename ArgType>
	class Invert : public ICalculatable
	{
		std::unique_ptr<ICalculatable> m_arg;
	public:
		Invert(std::unique_ptr<ICalculatable> arg)
			: m_arg(std::move(arg))
		{
		}

		Value Calculate() const override
		{
			const ArgType arg = m_arg->Calculate();
			const auto result = -arg;
			return result;
		}

		ValueType GetType() const override
		{
			return fuura::tools::GetValueType<decltype(-ArgType())>();
		}
	};

	// ------------------------------------------------------------------------
	// not a
	class Not : public ICalculatable
	{
		std::unique_ptr<ICalculatable> m_arg;
	public:
		Not(std::unique_ptr<ICalculatable> arg)
			: m_arg(std::move(arg))
		{
		}

		Value Calculate() const override
		{
			const bool arg = m_arg->Calculate();
			const auto result = !arg;
			return result;
		}

		ValueType GetType() const override
		{
			return fuura::tools::GetValueType<bool>();
		}
	};

	// ------------------------------------------------------------------------
	// a + b
	template <typename ArgType>
	class Add : public ICalculatable
	{
		std::unique_ptr<ICalculatable> m_first, m_second;
	public:
		Add(std::unique_ptr<ICalculatable> first, std::unique_ptr<ICalculatable> second)
			: m_first(std::move(first)), m_second(std::move(second))
		{
		}

		Value Calculate() const override
		{
			const ArgType a = m_first->Calculate();
			const ArgType b = m_second->Calculate();
			const auto result = a + b;
			return result;
		}

		ValueType GetType() const override
		{
			return fuura::tools::GetValueType<ArgType>();
		}

		/*
	compilation::IRegisterPlaceholder* GenerateFlow(compilation::ExecutionFlow& executionFlow, compilation::VirtualRegisterManager& tempValues) const override
		{
			using namespace compilation;

			auto firstReg  = m_first->GenerateFlow(executionFlow, tempValues);
			auto secondReg = m_second->GenerateFlow(executionFlow, tempValues);
			IAsmInstruction* depAdd = new compilation::Add<ArgType>(tempValues, firstReg, secondReg);
			executionFlow.PushBack(std::unique_ptr<IAsmInstruction>(depAdd));
			return depAdd->GetResult();
		}
			*/
		};

	// ------------------------------------------------------------------------
	// a - b
	template <typename ArgType>
	class Subtract : public ICalculatable
	{
		std::unique_ptr<ICalculatable> m_first, m_second;
	public:
		Subtract(std::unique_ptr<ICalculatable> first, std::unique_ptr<ICalculatable> second)
			: m_first(std::move(first)), m_second(std::move(second))
		{
		}

		Value Calculate() const override
		{
			const ArgType a = m_first->Calculate();
			const ArgType b = m_second->Calculate();
			const auto result = a - b;
			return result;
		}

		ValueType GetType() const override
		{
			return fuura::tools::GetValueType<ArgType>();
		}

		/*
		compilation::IRegisterPlaceholder* GenerateFlow(compilation::ExecutionFlow& executionFlow, compilation::VirtualRegisterManager& tempValues) const override
		{
			using namespace compilation;

			auto firstReg = m_first->GenerateFlow(executionFlow, tempValues);
			auto secondReg = m_second->GenerateFlow(executionFlow, tempValues);
			IAsmInstruction* depAdd = new compilation::Sub<ArgType>(tempValues, firstReg, secondReg);
			executionFlow.PushBack(std::unique_ptr<IAsmInstruction>(depAdd));
			return depAdd->GetResult();
		}*/
	};

	// ------------------------------------------------------------------------
	// a * b
	template <typename ArgType>
	class Multiply : public ICalculatable
	{
		std::unique_ptr<ICalculatable> m_first, m_second;
	public:
		Multiply(std::unique_ptr<ICalculatable> first, std::unique_ptr<ICalculatable> second)
			: m_first(std::move(first)), m_second(std::move(second))
		{
		}

		Value Calculate() const override
		{
			const ArgType a = m_first->Calculate();
			const ArgType b = m_second->Calculate();
			const auto result = a * b;
			return result;
		}

		ValueType GetType() const override
		{
			return fuura::tools::GetValueType<ArgType>();
		}
	};

	// ------------------------------------------------------------------------
	// a / b, вещественное деление, т.е. результат всегда вещественен независимо от операндов.
	template <typename ArgType>
	class RealDivide : public ICalculatable
	{
		std::unique_ptr<ICalculatable> m_first, m_second;
	public:
		RealDivide(std::unique_ptr<ICalculatable> first, std::unique_ptr<ICalculatable> second)
			: m_first(std::move(first)), m_second(std::move(second))
		{
		}

		Value Calculate() const override
		{
			const double a = (ArgType)m_first->Calculate();
			const double b = (ArgType)m_second->Calculate();
			const double result = a / b;
			return result;
		}

		ValueType GetType() const override
		{
			return fuura::tools::GetValueType<double>();
		}
	};

	// ------------------------------------------------------------------------
	// a div b, целочисленное деление.
	class IntegerDivide : public ICalculatable
	{
		std::unique_ptr<ICalculatable> m_first, m_second;
	public:
		IntegerDivide(std::unique_ptr<ICalculatable> first, std::unique_ptr<ICalculatable> second)
			: m_first(std::move(first)), m_second(std::move(second))
		{
		}

		Value Calculate() const override
		{
			const int a = m_first->Calculate();
			const int b = m_second->Calculate();
			const int result = a / b;
			return result;
		}

		ValueType GetType() const override
		{
			return fuura::tools::GetValueType<int>();
		}
	};

	// ------------------------------------------------------------------------
	// a % b, остаток при целочисленном делении.
	class GetDivRemainder : public ICalculatable
	{
		std::unique_ptr<ICalculatable> m_first, m_second;
	public:
		GetDivRemainder(std::unique_ptr<ICalculatable> first, std::unique_ptr<ICalculatable> second)
			: m_first(std::move(first)), m_second(std::move(second))
		{
		}

		Value Calculate() const override
		{
			const int a = m_first->Calculate();
			const int b = m_second->Calculate();
			const int result = a % b;
			return result;
		}

		ValueType GetType() const override
		{
			return fuura::tools::GetValueType<int>();
		}
	};

	// ------------------------------------------------------------------------
	// a ^ b
	template <typename ArgType>
	class RaiseToPower : public ICalculatable
	{
		std::unique_ptr<ICalculatable> m_first, m_second;
	public:
		RaiseToPower(std::unique_ptr<ICalculatable> first, std::unique_ptr<ICalculatable> second)
			: m_first(std::move(first)), m_second(std::move(second))
		{
		}

		Value Calculate() const override
		{
			const ArgType a = m_first->Calculate();
			const ArgType b = m_second->Calculate();
			const double result = std::pow(a, b);
			return result;
		}

		ValueType GetType() const override
		{
			return fuura::tools::GetValueType<double>();
		}
	};

	// ------------------------------------------------------------------------
	// a = b
	template <typename ArgType>
	class Equal : public ICalculatable
	{
		std::unique_ptr<ICalculatable> m_first, m_second;
	public:
		Equal(std::unique_ptr<ICalculatable> first, std::unique_ptr<ICalculatable> second)
			: m_first(std::move(first)), m_second(std::move(second))
		{
		}

		Value Calculate() const override
		{
			const ArgType a = m_first->Calculate();
			const ArgType b = m_second->Calculate();
			const bool result = (a == b);
			return result;
		}

		ValueType GetType() const override
		{
			return fuura::tools::GetValueType<bool>();
		}
	};

	// ------------------------------------------------------------------------
	// a != b
	template <typename ArgType>
	class NotEqual : public ICalculatable
	{
		std::unique_ptr<ICalculatable> m_first, m_second;
	public:
		NotEqual(std::unique_ptr<ICalculatable> first, std::unique_ptr<ICalculatable> second)
			: m_first(std::move(first)), m_second(std::move(second))
		{
		}

		Value Calculate() const override
		{
			const ArgType a = m_first->Calculate();
			const ArgType b = m_second->Calculate();
			const bool result = (a != b);
			return result;
		}

		ValueType GetType() const override
		{
			return fuura::tools::GetValueType<bool>();
		}
	};

	// ------------------------------------------------------------------------
	// a < b
	template <typename ArgType>
	class Less : public ICalculatable
	{
		std::unique_ptr<ICalculatable> m_first, m_second;
	public:
		Less(std::unique_ptr<ICalculatable> first, std::unique_ptr<ICalculatable> second)
			: m_first(std::move(first)), m_second(std::move(second))
		{
		}

		Value Calculate() const override
		{
			const ArgType a = m_first->Calculate();
			const ArgType b = m_second->Calculate();
			const bool result = (a < b);
			return result;
		}

		ValueType GetType() const override
		{
			return fuura::tools::GetValueType<bool>();
		}
	};

	// ------------------------------------------------------------------------
	// a > b
	template <typename ArgType>
	class Greater : public ICalculatable
	{
		std::unique_ptr<ICalculatable> m_first, m_second;
	public:
		Greater(std::unique_ptr<ICalculatable> first, std::unique_ptr<ICalculatable> second)
			: m_first(std::move(first)), m_second(std::move(second))
		{
		}

		Value Calculate() const override
		{
			const ArgType a = m_first->Calculate();
			const ArgType b = m_second->Calculate();
			const bool result = (a > b);
			return result;
		}

		ValueType GetType() const override
		{
			return fuura::tools::GetValueType<bool>();
		}
	};

	// ------------------------------------------------------------------------
	// a <= b
	template <typename ArgType>
	class LessOrEqual : public ICalculatable
	{
		std::unique_ptr<ICalculatable> m_first, m_second;
	public:
		LessOrEqual(std::unique_ptr<ICalculatable> first, std::unique_ptr<ICalculatable> second)
			: m_first(std::move(first)), m_second(std::move(second))
		{
		}

		Value Calculate() const override
		{
			const ArgType a = m_first->Calculate();
			const ArgType b = m_second->Calculate();
			const bool result = (a <= b);
			return result;
		}

		ValueType GetType() const override
		{
			return fuura::tools::GetValueType<bool>();
		}
	};

	// ------------------------------------------------------------------------
	// a >= b
	template <typename ArgType>
	class GreaterOrEqual : public ICalculatable
	{
		std::unique_ptr<ICalculatable> m_first, m_second;
	public:
		GreaterOrEqual(std::unique_ptr<ICalculatable> first, std::unique_ptr<ICalculatable> second)
			: m_first(std::move(first)), m_second(std::move(second))
		{
		}

		Value Calculate() const override
		{
			const ArgType a = m_first->Calculate();
			const ArgType b = m_second->Calculate();
			const bool result = (a >= b);
			return result;
		}

		ValueType GetType() const override
		{
			return fuura::tools::GetValueType<bool>();
		}
	};

	// ------------------------------------------------------------------------
	// a or b
	class Or : public ICalculatable
	{
		std::unique_ptr<ICalculatable> m_first, m_second;
	public:
		Or(std::unique_ptr<ICalculatable> first, std::unique_ptr<ICalculatable> second)
			: m_first(std::move(first)), m_second(std::move(second))
		{
		}

		Value Calculate() const override
		{
			const bool a = m_first->Calculate();
			const bool b = m_second->Calculate();
			const bool result = (a || b);
			return result;
		}

		ValueType GetType() const override
		{
			return fuura::tools::GetValueType<bool>();
		}
	};

	// ------------------------------------------------------------------------
	// a and b
	class And : public ICalculatable
	{
		std::unique_ptr<ICalculatable> m_first, m_second;
	public:
		And(std::unique_ptr<ICalculatable> first, std::unique_ptr<ICalculatable> second)
			: m_first(std::move(first)), m_second(std::move(second))
		{
		}

		Value Calculate() const override
		{
			const bool a = m_first->Calculate();
			const bool b = m_second->Calculate();
			const bool result = (a && b);
			return result;
		}

		ValueType GetType() const override
		{
			return fuura::tools::GetValueType<bool>();
		}
	};

	// ------------------------------------------------------------------------
}