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
	//	����������� �������.
	//
	///////////////////////////////////////////////////////////////////////////
	template <typename ResultType, typename ...Args>
	class Function <ResultType(Args...)> : public compilation::ISyntaxTreeContainer
	{
	public:
		// --------------------------------------------------------------------------
		//	argNames  -	����� ���������� ������� � ���� � ��� �� �������, � �������
		//				��� ����������� � ��������� �������.
		//	functionSource - ��� ����������� ������� �� ����� fuura.
		// --------------------------------------------------------------------------
		explicit Function(
			ArgumentNameList<sizeof ... (Args)>&& argNames,	// ����� ����������
			std::string_view functionSource,				// �������� ��� �������
			IParser& parser,								// ������, ������� ����������� �������� ��� ������� � ������ ICalculatable
			language::FuuraSemantics& semantics				// ��������� ��������� �����
		);

		// --------------------------------------------------------------------------
		// ��������� ������� �� ��������� ��������� ����������.
		// --------------------------------------------------------------------------
		ResultType operator () (Args... args);

		// --------------------------------------------------------------------------
		// ���������� ������ ��������������� ������ �������, ����� ��� ����������.
		// --------------------------------------------------------------------------
		language::ICalculatable* GetSyntaxTree() override;

	private:
		constexpr static std::size_t ARG_COUNT = sizeof ...(Args);

		// --------------------------------------------------------------------------
		// �� �������� ��� ����� ������� ����� ���� ������ ���������� � ����������
		// ��� ���������. ��� ����, ������, ���������� ������������� ������������
		// ���������� �������, � �.�. �� ������ ������� ����������.
		struct Data
		{
			// �������� �������� ����������.
			ArgumentSet<Args...> arguments;

			// ��������� ��������, ������� � ����������.
			std::unique_ptr<language::ICalculatable> root;

			Data(ArgumentNameList<sizeof ... (Args)>&& args)
				:arguments(std::move(args))
			{}
		};
		// --------------------------------------------------------------------------

		// shared ��� ����������� ���� ����������, ��� ����� ��� ������������� std::function.
		std::shared_ptr<Data> m_data;
	};

	///////////////////////////////////////////////////////////////////////////

	// ------------------------------------------------------------------------
	template <typename ResultType, typename ...Args>
	Function<ResultType(Args...)>::Function(
		ArgumentNameList<sizeof ... (Args)>&& argNames,	// ����� ����������
		std::string_view functionSource,				// �������� ��� �������
		IParser& parser,								// ������, ������� ����������� �������� ��� ������� � ������ ICalculatable
		language::FuuraSemantics& semantics				// ��������� ��������� �����
	)
	{
		// ������� ������ ����� ArgumentSet �� argNames.
		m_data = std::make_shared<Data>(std::move(argNames));

		// ����� ��������� ��������� ��������� � ������� �������������� ���������.
		semantics.UpdateArgumentSet(&m_data->arguments);

		// ����� ������ ���.
		m_data->root = parser.Parse(functionSource);

		// �������� ���� ����������:
		auto functionType = m_data->root->GetType();
		auto expectedType = tools::GetValueType<ResultType>();

		if (functionType != expectedType)
		{
			// ���� ���� �� ���������, �� ���������� ������� ��������������
			// �� ������� ����������� ���� � ���������, ���������� ���.
			m_data->root = semantics.GetImplicitTypeCastFactory().CreateTypeCast(std::move(m_data->root), expectedType);
			// � ������ ������� � ���� ����� m_data->root ���������� nullptr.
			if (m_data->root == nullptr)
			{
				// ���� ������ �������������� ��� - ��������� � �������.
				throw SyntaxError(std::string("��� ���������� ������� (") + tools::ToString(functionType) + ") �� ��������� � ��������� (" + tools::ToString(expectedType) + ")", 0, 0);
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