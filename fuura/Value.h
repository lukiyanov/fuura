#pragma once

namespace fuura
{
	// ---------------------------------------------------------------------------
	// Значение любого выражения в языке fuura может быть только одним из
	// перечисленных ниже.
	// Их внутреннее устройство совпадает с соответствующими типами языка C++.
	// TYPE_COUNT обязательно должен быть последним элементом.
	// ---------------------------------------------------------------------------
	enum class ValueType { Bool, Int, Double, TYPE_COUNT };

	// ---------------------------------------------------------------------------
	// Хранит значение выражения. Предполагается, что потребитель сам знает,
	// значение какого типа содержит объект данного класса.
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

	// Поддержка установки значения через поля соответствующих типов:
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