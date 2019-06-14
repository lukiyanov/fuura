#include "stdafx.h"
#include "Translator.h"
#include "ANTLR4Parser.h"
using namespace fuura;
using namespace fuura::antlr;

// ----------------------------------------------------------------------------
Translator::Translator()
	: m_parser (std::make_unique<ANTLR4Parser>(m_fuuraSemantics))
{
}

// ----------------------------------------------------------------------------
