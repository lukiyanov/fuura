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
	//	Строит дерево ICalculatable, используя библиотеку ANTLR4.
	//
	///////////////////////////////////////////////////////////////////////////
	class ANTLR4Parser : public IParser
	{		
		language::FuuraSemantics& m_pSemantics;

	public:
		ANTLR4Parser(language::FuuraSemantics& pSemantics);

		// ----------------------------------------------------------------------------
		// Основная функция парсера, парсящая код source.
		// Использует при этом предопределённые имена из info.
		// ----------------------------------------------------------------------------
		std::unique_ptr<language::ICalculatable> Parse(std::string_view source) override;
	};

	///////////////////////////////////////////////////////////////////////////
}