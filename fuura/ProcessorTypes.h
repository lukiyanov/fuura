#pragma once

// ----------------------------------------------------------------------------
// ���� �������� ����������� ����� � ��������� 32-���������� ���������� Intel.
// ----------------------------------------------------------------------------
namespace fuura::compilation
{
	using byte  = unsigned char;
	using word  = unsigned short int;
	using dword = unsigned long int;
	using int8  = signed char;
	using int16 = signed short int;
	using int32 = signed long int;

	// ----------------------------------------------------------------------------

	enum class RegisterInt32 {
		EAX = 0,
		ECX = 1,
		EDX = 2,
		EBX = 3,
		ESP = 4,
		EBP = 5,
		ESI = 6,
		EDI = 7
	};

	enum class RegisterInt16 {
		AX = 0,
		CX = 1,
		DX = 2,
		BX = 3,
		SP = 4,
		BP = 5,
		SI = 6,
		DI = 7
	};

	enum class RegisterInt8 {
		AL = 0,
		CL = 1,
		DL = 2,
		BL = 3,
		AH = 4,
		CH = 5,
		DH = 6,
		BH = 7
	};

	enum class RegisterFloat64
	{
		ST0,
		ST1,
		ST2,
		ST3,
		ST4,
		ST5,
		ST6,
		ST7
	};

	// ----------------------------------------------------------------------------

	/*
		� �������� ����������� Intel ������� �������� ������������� ���� �����.
		������������� ����� ������� ���������� ���� �����.
		��� ������������� ��������� ��� ��� ����.
	*/

	// ----------------------------------------------------------------------------
	inline byte GetRegisterCode(RegisterInt32 reg)
	{
		return static_cast<byte>(reg);
	}

	// ----------------------------------------------------------------------------
	inline byte GetRegisterCode(RegisterInt16 reg)
	{
		return static_cast<byte>(reg);
	}

	// ----------------------------------------------------------------------------
	inline byte GetRegisterCode(RegisterInt8 reg)
	{
		return static_cast<byte>(reg);
	}

	// ----------------------------------------------------------------------------
	// ���������� ���� � ����� �����, ������� ����� N ��� ����� �����.
	// ��������� ������ � ����. ������:
	// 0x1234     => 0x12 0x34           => B0 B1
	// 0x12345678 => 0x12 0x34 0x56 0x78 => B0 B1 B2 B3
	// B# - ���� ����� #, �.�. �� ��� ����� ������ ������� � ��������� �������.
	template <size_t N, typename T> constexpr byte GetByte(T value)
	{
		static_assert(N < sizeof(T), "GetByte: N cannot be more than sizeof(T)");
		return static_cast<byte>(value >> (8 * (sizeof(T) - N - 1)));
	}

	//////////////////////////////////////////////////////////////////////////////
	//
	//	��������� ���������.
	//
	//////////////////////////////////////////////////////////////////////////////

	// ---------------------------------------------------------------------------
	// ����������� ���� eax + 123
	// ---------------------------------------------------------------------------
	struct RegisterInt32PlusConstant
	{
		const RegisterInt32 Register;
		const int32         Constant;

		constexpr RegisterInt32PlusConstant(const RegisterInt32 reg, const int32 constant)
			: Register(reg), Constant(constant)
		{}
	};

	inline constexpr RegisterInt32PlusConstant operator + (const RegisterInt32 reg, const int32 constant)
	{
		return RegisterInt32PlusConstant(reg, constant);
	}

	inline constexpr RegisterInt32PlusConstant operator - (const RegisterInt32 reg, const int32 constant)
	{
		return RegisterInt32PlusConstant(reg, -constant);
	}

	// ---------------------------------------------------------------------------
	// ����������� ���� [eax]
	// ---------------------------------------------------------------------------
	struct RegisterInt32Indirect
	{
		const RegisterInt32 Register;

		constexpr RegisterInt32Indirect(const RegisterInt32 reg)
			: Register(reg)
		{}
	};

	// ---------------------------------------------------------------------------
	// ����������� ���� [eax + 123]
	// ---------------------------------------------------------------------------
	struct RegisterInt32PlusConstantIndirect
	{
		const RegisterInt32 Register;
		const int32         Constant;

		constexpr RegisterInt32PlusConstantIndirect(const RegisterInt32PlusConstant expr)
			: Register(expr.Register), Constant(expr.Constant)
		{}
	};

	// ---------------------------------------------------------------------------
	//	�����, ��������� ������� ��� ��������� ���������.
	//	�� ����, ����� ������ ��� ������������ ������-������ I,
	//	�.�. �������� �������������� �� ����� ���� �����������.
	// ---------------------------------------------------------------------------
	struct IndirectAccess
	{
		constexpr IndirectAccess() {}

		constexpr RegisterInt32Indirect operator [] (RegisterInt32 reg) const
		{
			return RegisterInt32Indirect(reg);
		}

		constexpr RegisterInt32PlusConstantIndirect operator [] (RegisterInt32PlusConstant expression) const
		{
			return RegisterInt32PlusConstantIndirect(expression);
		}
	};

	// ����� ���� ������ ��������� ������� ��������� ���������, ��������:
	// I[eax]
	// I[eax + 1]
	inline constexpr IndirectAccess I;

	// ----------------------------------------------------------------------------
}