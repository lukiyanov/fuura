#pragma once

namespace fuura
{
	// ---------------------------------------------------------------------------
	// �������� ������ ��������� � ����� fuura ����� ���� ������ ����� ��
	// ������������� ����.
	// �� ���������� ���������� ��������� � ���������������� ������ ����� C++.
	// TYPE_COUNT ����������� ������ ���� ��������� ���������.
	// ---------------------------------------------------------------------------
	enum class ValueType { Bool, Int, Double, TYPE_COUNT };

	// ---------------------------------------------------------------------------
	// ������ �������� ���������. ��������������, ��� ����������� ��� �����,
	// �������� ������ ���� �������� ������ ������� ������.
	// ---------------------------------------------------------------------------
	union Value
	{
		double	doubleValue;
		int		intValue;
		bool	boolValue;

	public:
		Value() = default;
		Value(const Value&) = default;
		Value(Value&&) = default;

		Value& operator = (const Value& value) = default;

	// ��������� ��������� �������� ����� ���� ��������������� �����:
	public:
		Value(double value): doubleValue(value) {}
		Value(int    value): intValue(value) {}
		Value(bool   value): boolValue(value) {}

		operator double() { return doubleValue; }
		operator int()    { return intValue; }
		operator bool()   { return boolValue; }

		Value& operator = (const double value)
		{
			doubleValue = value;
			return *this;
		}

		Value& operator = (const int value)
		{
			intValue = value;
			return *this;
		}

		Value& operator = (const bool value)
		{
			boolValue = value;
			return *this;
		}
	};

	// ---------------------------------------------------------------------------
}