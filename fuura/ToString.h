#pragma once
#include <string>
#include <sstream>
#include "Value.h"
#include "Operation.h"

namespace fuura::tools
{
	// ---------------------------------------------------------------------------
	// ���������� ��������� ������������� int.
	// ---------------------------------------------------------------------------
	template <typename T>
	inline std::string ToString(T value)
	{
		std::ostringstream oss;
		oss << value;
		return oss.str();
	}

	// ---------------------------------------------------------------------------
	// ���������� ��������� ������������� bool.
	// ---------------------------------------------------------------------------
	template <>
	inline std::string ToString(bool value)
	{
		std::ostringstream oss;
		oss << (value ? "true" : "false");
		return oss.str();
	}

	// ---------------------------------------------------------------------------
	// ���������� ��� ���� type.
	// ---------------------------------------------------------------------------
	template <>
	inline std::string ToString(ValueType type)
	{
		std::ostringstream oss;

		switch (type)
		{
		case fuura::ValueType::Bool:
			oss << "boolean";
			break;
		case fuura::ValueType::Int:
			oss << "integer";
			break;
		case fuura::ValueType::Double:
			oss << "double";
			break;
		default:
			throw std::out_of_range("��������� ����������� ��� ValueType.");
		}

		return oss.str();
	}

	// ---------------------------------------------------------------------------
	// ���������� ��������� ����������� ������� ��������.
	// ---------------------------------------------------------------------------
	template <>
	inline std::string ToString(language::UnaryOperation op)
	{
		std::ostringstream oss;

		switch (op)
		{
		case fuura::language::UnaryOperation::Invert:
			oss << "-";
			break;
		case fuura::language::UnaryOperation::Not:
			oss << "not";
			break;
		default:
			throw std::out_of_range("��������� ����������� ��� UnaryOperation.");
		}

		return oss.str();
	}

	// ---------------------------------------------------------------------------
	// ���������� ��������� ����������� �������� ��������.
	// ---------------------------------------------------------------------------
	template <>
	inline std::string ToString(language::BinaryOperation op)
	{
		std::ostringstream oss;

		switch (op)
		{
		case fuura::language::BinaryOperation::Add:
			oss << "+";
			break;
		case fuura::language::BinaryOperation::Subtract:
			oss << "-";
			break;
		case fuura::language::BinaryOperation::Multiply:
			oss << "*";
			break;
		case fuura::language::BinaryOperation::RealDivide:
			oss << "/";
			break;
		case fuura::language::BinaryOperation::IntegerDivide:
			oss << "div";
			break;
		case fuura::language::BinaryOperation::GetDivRemainder:
			oss << "%";
			break;
		case fuura::language::BinaryOperation::RaiseToPower:
			oss << "^";
			break;
		case fuura::language::BinaryOperation::Equal:
			oss << "=";
			break;
		case fuura::language::BinaryOperation::NotEqual:
			oss << "!=";
			break;
		case fuura::language::BinaryOperation::Greater:
			oss << ">";
			break;
		case fuura::language::BinaryOperation::Less:
			oss << "<";
			break;
		case fuura::language::BinaryOperation::GreaterOrEqual:
			oss << ">=";
			break;
		case fuura::language::BinaryOperation::LessOrEqual:
			oss << "<=";
			break;
		case fuura::language::BinaryOperation::Or:
			oss << "or";
			break;
		case fuura::language::BinaryOperation::And:
			oss << "and";
			break;
		default:
			throw std::out_of_range("��������� ����������� ��� BinaryOperation.");
		}

		return oss.str();
	}

	// ---------------------------------------------------------------------------
}