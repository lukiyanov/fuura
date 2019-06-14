#pragma once
#include "ProcessorTypes.h"

namespace fuura::compilation
{
	///////////////////////////////////////////////////////////////////////////
	class RegisterType
	{
	public:
		static const RegisterType Byte;
		static const RegisterType Word;
		static const RegisterType DoubleWord;
		static const RegisterType Float;
		static const RegisterType DoubleFloat;

	public:
		// --------------------------------------------------------------------
		RegisterType(const RegisterType& reg) = default;
		RegisterType& operator = (RegisterType& reg) = default;

		// --------------------------------------------------------------------
		constexpr operator char() const
		{
			return static_cast<char>(m_value);
		}

		// --------------------------------------------------------------------
		inline bool operator == (RegisterType type)
		{
			return type.m_value == m_value;
		}

		// --------------------------------------------------------------------
		inline bool operator != (RegisterType type)
		{
			return type.m_value != m_value;
		}

		// --------------------------------------------------------------------
		template<typename RegisterT>
		static constexpr RegisterType FromRegister();

		// --------------------------------------------------------------------
		template<>
		static constexpr RegisterType FromRegister<RegisterInt32>()
		{
			return DoubleWord;
		}

		// --------------------------------------------------------------------
		template<>
		static constexpr RegisterType FromRegister<RegisterInt16>()
		{
			return Word;
		}

		// --------------------------------------------------------------------
		template<>
		static constexpr RegisterType FromRegister<RegisterInt8>()
		{
			return Byte;
		}

		// --------------------------------------------------------------------
		template<>
		static constexpr RegisterType FromRegister<RegisterFloat64>()
		{
			return DoubleFloat;
		}

		// --------------------------------------------------------------------


	private:

		enum class RegisterTypeEnum : char {
			// Типы процессора:
			Byte       = 'b',
			Word       = 'w',
			DoubleWord = 'd',
			//QuadWord = 'q',	// Пока ограничимся 32х битной архитектурой.

			// Типы сопроцессора:
			Float       = 'F',
			DoubleFloat = 'D'

			// Тип не определён:
			//Unknown = '#'
		};

		RegisterTypeEnum m_value;

	private:
		constexpr RegisterType(const RegisterTypeEnum& reg)
			: m_value (reg)
		{
		}
	};

	///////////////////////////////////////////////////////////////////////////
}