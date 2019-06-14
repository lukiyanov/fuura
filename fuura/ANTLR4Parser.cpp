#include "stdafx.h"
#include "ANTLR4Parser.h"
#include "OperationFactory.h"
#include "Exception.h"

#include "ANTLR4\FuuraErrorListener.h"
#include "ANTLR4\ANTLR4-generated\FuuraLexer.h"
#include "ANTLR4\ANTLR4-generated\FuuraParser.h"

using namespace fuura::antlr::generated;
using namespace fuura::antlr;
using namespace fuura::language;
using namespace fuura;
using namespace std;
using namespace antlr4;

// ----------------------------------------------------------------------------
ANTLR4Parser::ANTLR4Parser(language::FuuraSemantics& pSemantics)
	: m_pSemantics(pSemantics)
{
}

// ----------------------------------------------------------------------------
unique_ptr<ICalculatable> ANTLR4Parser::Parse(string_view source)
{
	ANTLRInputStream input(source.data());
	FuuraLexer lexer(&input);
	lexer.removeErrorListeners();

	FuuraErrorListener listener;
	lexer.addErrorListener(&listener);

	CommonTokenStream tokens(&lexer);

	FuuraParser parser(&tokens);
	parser.removeErrorListeners();
	parser.addErrorListener(&listener);
	parser.m_semantics = &m_pSemantics;

	// ѕарсим. ѕолучаем синтезированные атрибуты, само дерево нас не интересует.
	auto* root = parser.root();
	if (!root || !root->node)
		throw std::exception("Ќе удалось произвести разбор строки парсером.");

	return move(root->node);
}

// ----------------------------------------------------------------------------
