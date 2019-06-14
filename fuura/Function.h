#pragma once
#include <memory>
#include "ArgumentNameList.h"
#include "ArgumentSet.h"
#include "FuuraSemantics.h"

#include "IParser.h"
#include "ICalculatable.h"

#include "GetValueType.h"
#include "ToString.h"
#include "Exception.h"

#include "ISyntaxTreeContainer.h"

namespace fuura
{
	template <typename ...FunctionSignature> class Function;

	///////////////////////////////////////////////////////////////////////////
	//
	//	Выполняемая функция.
	//
	///////////////////////////////////////////////////////////////////////////
	template <typename ResultType, typename ...Args>
	class Function <ResultType(Args...)> : public compilation::ISyntaxTreeContainer
	{
	public:
		// --------------------------------------------------------------------------
		//	argNames  -	имена аргументов функции в коде в том же порядке, в котором
		//				они перечислены в сигнатуре функции.
		//	functionSource - код создаваемой функции на языке fuura.
		// --------------------------------------------------------------------------
		explicit Function(
			ArgumentNameList<sizeof ... (Args)>&& argNames,	// Имена аргументов
			std::string_view functionSource,				// Исходный код функции
			IParser& parser,								// Парсер, который преобразует исходный код функции в дерево ICalculatable
			language::FuuraSemantics& semantics				// Настройки семантики языка
		);

		// --------------------------------------------------------------------------
		// Выполняет функцию на указанных значениях аргументов.
		// --------------------------------------------------------------------------
		ResultType operator () (Args... args);

		// --------------------------------------------------------------------------
		// Возвращает корень синтаксического дерева функции, нужен для компиляции.
		// --------------------------------------------------------------------------
		language::ICalculatable* GetSyntaxTree() override;

	private:
		constexpr static std::size_t ARG_COUNT = sizeof ...(Args);

		// --------------------------------------------------------------------------
		// Всё устроено так чтобы объекты можно было быстро копировать и передавать
		// как аргументы. При этом, правда, невозможно одновременное параллельное
		// выполнение функции, в т.ч. на разных наборах аргументов.
		struct Data
		{
			// Содержит значения аргументов.
			ArgumentSet<Args...> arguments;

			// Результат парсинга, готовый к выполнению.
			std::unique_ptr<language::ICalculatable> root;

			Data(ArgumentNameList<sizeof ... (Args)>&& args)
				:arguments(std::move(args))
			{}
		};
		// --------------------------------------------------------------------------

		// shared для возможности быть копируемым, что нужно для использования std::function.
		std::shared_ptr<Data> m_data;
	};

	///////////////////////////////////////////////////////////////////////////

	// ------------------------------------------------------------------------
	template <typename ResultType, typename ...Args>
	Function<ResultType(Args...)>::Function(
		ArgumentNameList<sizeof ... (Args)>&& argNames,	// Имена аргументов
		std::string_view functionSource,				// Исходный код функции
		IParser& parser,								// Парсер, который преобразует исходный код функции в дерево ICalculatable
		language::FuuraSemantics& semantics				// Настройки семантики языка
	)
	{
		// Сначала создаём имена ArgumentSet из argNames.
		m_data = std::make_shared<Data>(std::move(argNames));

		// Затем обновляем аргументы алгоритма в объекте семантического контекста.
		semantics.UpdateArgumentSet(&m_data->arguments);

		// Затем парсим код.
		m_data->root = parser.Parse(functionSource);

		// Проверка типа результата:
		auto functionType = m_data->root->GetType();
		auto expectedType = tools::GetValueType<ResultType>();

		if (functionType != expectedType)
		{
			// Если типы не совпадают, но существует неявное преобразование
			// из реально полученного типа в ожидаемый, навешиваем его.
			m_data->root = semantics.GetImplicitTypeCastFactory().CreateTypeCast(std::move(m_data->root), expectedType);
			// В случае неудачи в этом месте m_data->root становится nullptr.
			if (m_data->root == nullptr)
			{
				// Если такого преобразования нет - завершаем с ошибкой.
				throw SyntaxError(std::string("Тип результата функции (") + tools::ToString(functionType) + ") не совпадает с ожидаемым (" + tools::ToString(expectedType) + ")", 0, 0);
			}
		}
	}

	// ------------------------------------------------------------------------
	template <typename ResultType, typename ...Args>
	ResultType Function<ResultType(Args...)>::operator () (Args... args)
	{
		m_data->arguments.SetArgumentValues(args...);
		return m_data->root->Calculate();
	}
	
	// ------------------------------------------------------------------------
	template <typename ResultType, typename ...Args>
	language::ICalculatable* Function<ResultType(Args...)>::GetSyntaxTree()
	{
		return m_data->root.get();
	}

	// ------------------------------------------------------------------------
}