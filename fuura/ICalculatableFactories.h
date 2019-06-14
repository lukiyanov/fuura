#pragma once
#include <memory>
#include "ICalculatable.h"

namespace fuura::language
{
	//////////////////////////////////////////////////////////////////////////////
	// Фабрика для одного унарного оператора с определённым параметром.
	//////////////////////////////////////////////////////////////////////////////
	class IUnaryOperationFactory
	{
	public:
		virtual std::unique_ptr<ICalculatable> Create(std::unique_ptr<ICalculatable> arg) = 0;
		virtual std::unique_ptr<IUnaryOperationFactory> Clone() = 0;
	};

	//////////////////////////////////////////////////////////////////////////////
	// Фабрика для одного бинарного оператора с одной определённой
	// комбинацией параметров.
	//////////////////////////////////////////////////////////////////////////////
	class IBinaryOperationFactory
	{
	public:
		virtual std::unique_ptr<ICalculatable> Create(std::unique_ptr<ICalculatable> first, std::unique_ptr<ICalculatable> second) = 0;
		virtual std::unique_ptr<IBinaryOperationFactory> Clone() = 0;
	};

	//////////////////////////////////////////////////////////////////////////////
	// Создаёт указанную унарную операцию.
	template <typename T>
	class UnaryOperationFactory : public IUnaryOperationFactory
	{
	public:
		std::unique_ptr<ICalculatable> Create(std::unique_ptr<ICalculatable> arg) override
		{
			return std::make_unique<T>(std::move(arg));
		}

		std::unique_ptr<IUnaryOperationFactory> Clone() override
		{
			return std::make_unique<UnaryOperationFactory<T>>();
		}
	};

	//////////////////////////////////////////////////////////////////////////////
	// Создаёт указанную бинарную операцию.
	template <typename T>
	class BinaryOperationFactory : public IBinaryOperationFactory
	{
	public:
		std::unique_ptr<ICalculatable> Create(std::unique_ptr<ICalculatable> first, std::unique_ptr<ICalculatable> second) override
		{
			return std::make_unique<T>(std::move(first), std::move(second));
		}

		std::unique_ptr<IBinaryOperationFactory> Clone() override
		{
			return std::make_unique<BinaryOperationFactory<T>>();
		}
	};

	//////////////////////////////////////////////////////////////////////////////
}