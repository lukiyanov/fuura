#pragma once
#include <Token.h>

class MockToken : public antlr4::Token
{
public:
	virtual std::string getText() const { throw 0; }
	virtual size_t getType() const { throw 0; }
	virtual size_t getLine() const { return 123; }
	virtual size_t getCharPositionInLine() const { return 456; }
	virtual size_t getChannel() const { throw 0; }
	virtual size_t getTokenIndex() const { throw 0; }
	virtual size_t getStartIndex() const { throw 0; }
	virtual size_t getStopIndex() const { throw 0; }
	virtual antlr4::TokenSource *getTokenSource() const { throw 0; }
	virtual antlr4::CharStream *getInputStream() const { throw 0; }
	virtual std::string toString() const { throw 0; }
};