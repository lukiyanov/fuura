#pragma once
#include <exception>
#include <string>
#include <BaseErrorListener.h>
#include "..\Exception.h"

namespace fuura::antlr
{
	///////////////////////////////////////////////////////////////////////////
	//
	//	��������� �� �������������� ������ ��� ������� ������.
	//	�� ����, ������ ���������� ���������� ������ SyntaxError.
	//
	///////////////////////////////////////////////////////////////////////////
	class FuuraErrorListener : public antlr4::BaseErrorListener {
	public:
		void syntaxError(antlr4::Recognizer *recognizer, antlr4::Token * offendingSymbol,
			size_t line, size_t charPositionInLine,
			const std::string &msg, std::exception_ptr e)
		{
			throw SyntaxError(msg, line, charPositionInLine);
		}
	};

	///////////////////////////////////////////////////////////////////////////
}