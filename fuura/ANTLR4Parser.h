#pragma once
#include "IParser.h"
#include "FuuraSemantics.h"

namespace fuura::language
{
	class OperationFactory;
}

namespace fuura::antlr
{
	///////////////////////////////////////////////////////////////////////////
	//
	//	������ ������ ICalculatable, ��������� ���������� ANTLR4.
	//
	///////////////////////////////////////////////////////////////////////////
	class ANTLR4Parser : public IParser
	{		
		language::FuuraSemantics& m_pSemantics;

	public:
		ANTLR4Parser(language::FuuraSemantics& pSemantics);

		// ----------------------------------------------------------------------------
		// �������� ������� �������, �������� ��� source.
		// ���������� ��� ���� ��������������� ����� �� info.
		// ----------------------------------------------------------------------------
		std::unique_ptr<language::ICalculatable> Parse(std::string_view source) override;
	};

	///////////////////////////////////////////////////////////////////////////
}