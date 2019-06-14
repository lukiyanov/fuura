#include "stdafx.h"
#include "Exception.h"
#include "ToString.h"

using namespace fuura;
using namespace fuura::tools;

// --------------------------------------------------------------------
SyntaxError::SyntaxError(const std::string& message, size_t line, size_t charPositionInLine)
	: std::exception((std::string("������ � ���������, ������ ") + ToString(line)
		+ ", ������ " + ToString(charPositionInLine)
		+ ": " + message).c_str()),
	m_line(line),
	m_charPositionInLine(charPositionInLine),
	m_message(message)
{}

// --------------------------------------------------------------------
size_t SyntaxError::GetLine() const
{
	return m_line;
}

// --------------------------------------------------------------------
size_t SyntaxError::GetCharPositionInLine() const
{
	return m_charPositionInLine;
}

// --------------------------------------------------------------------
const std::string& SyntaxError::GetMessage() const
{
	return m_message;
}

// --------------------------------------------------------------------
RegisterTypeMismatch::RegisterTypeMismatch(int uid, char expected, char actual)
	: std::exception((std::string("�������������� ����� �������� #" + ToString(uid) + ", ��������� ") + expected
		+ ", ���������� " + actual).c_str())
{
}

// --------------------------------------------------------------------
RegisterValueIsNotSet::RegisterValueIsNotSet(int uid)
	: std::exception((std::string("�������� �������� #") + ToString(uid) + " �� ���� �����������, ������ ���� ���������").c_str())
{
}

// --------------------------------------------------------------------
