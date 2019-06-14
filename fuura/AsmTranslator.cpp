#include "stdafx.h"
#include "AsmTranslator.h"
using namespace fuura::compilation;

#include <functional>

// ������� ��������� ������� ���������.
const byte SIZE_PREFIX = '\x66';

// ------------------------------------------------------------------------
void AsmTranslator::RestartBuilding()
{
	m_machineCode.Clear();
}

// ------------------------------------------------------------------------
// ������� �����������, �� ����� ����� ����-������ ��� �� ����� �� ������������.
std::vector<byte> AsmTranslator::GetCopyOfCurrentCode()
{
	const size_t size = m_machineCode.GetCodeSize();
	byte *beg = m_machineCode.GetCode();
	byte *end = beg + size;

	std::vector<byte> vct(size);
	vct.assign(beg, end);

	return vct;
}

// ----------------------------------------------------------------------------
bool AsmTranslator::CanBeReducedToByte(int32 constantToReduce) const
{
	// ���������� Microsoft ���������� "��������" �������,
	// ���� �������-��������� ��������� � ���������� (-129, 128),
	// � ���� ��� �� ������� "�������".
	// ������� �����.
	return -129 < constantToReduce && constantToReduce < 128;
}


///////////////////////////////////////////////////////////////////////////////
//
//	���������� ������.
//
///////////////////////////////////////////////////////////////////////////////

// ----------------------------------------------------------------------------
// NOP
// ----------------------------------------------------------------------------
/*
��������� �������:
	nop - ��� 90h
*/

void AsmTranslator::Nop()
{
	m_machineCode << '\x90';
}

// ----------------------------------------------------------------------------
// XOR
// ----------------------------------------------------------------------------
/*
��������� �������:
	xor reg32, reg32:
		33h 11b AAA BBB, ���:
			AAA - �������� ����� ������� ��������
			BBB - �������� ����� ������� ��������

	xor reg16, reg16:
		66h 33h 11b AAA BBB
			�.�. �� �� + ������� 66h � �������� ������� �����
		
	xor reg8, reg8:
		32h 11b AAA BBB
			�.�. �� ��, ������ ������ ���� 32h, � �� 33h
			(��� ������� � ����� �������, ���� �� �����)
*/

// ��������� ������������ ����� � ���������, ����� ����� ���� �� ���� �������.
// NB: ���� �������� ���� � �������� ������� ������������ �������� ������,
// ������� ��� ���������.
#pragma pack(push, 1)
struct XOR
{
	XOR(byte isOp8bit, byte reg1, byte reg2)
		: m_copFixed(0b0011001), m_mode(0b11), m_size(isOp8bit), m_reg1(reg1), m_reg2(reg2)
	{
	}

	union {
		struct {
			byte m_size : 1;
			byte m_copFixed : 7;
		};

		byte cop;
	};

	union {
		struct {
			byte m_reg2 : 3;
			byte m_reg1 : 3;
			byte m_mode : 2;
		};

		byte operands;
	};
};
#pragma pack(pop)

// ----------------------------------------------------------------------------
void AsmTranslator::Xor(RegisterInt32 reg1, RegisterInt32 reg2)
{
	XOR Xor(1, GetRegisterCode(reg1), GetRegisterCode(reg2));
	
	m_machineCode << Xor.cop << Xor.operands;
}

// ----------------------------------------------------------------------------
void AsmTranslator::Xor(RegisterInt16 reg1, RegisterInt16 reg2)
{
	XOR Xor(1, GetRegisterCode(reg1), GetRegisterCode(reg2));

	m_machineCode << SIZE_PREFIX << Xor.cop << Xor.operands;
}

// ----------------------------------------------------------------------------
void AsmTranslator::Xor(RegisterInt8  reg1, RegisterInt8  reg2)
{
	XOR Xor(0, GetRegisterCode(reg1), GetRegisterCode(reg2));

	m_machineCode << Xor.cop << Xor.operands;
}

// ----------------------------------------------------------------------------
// RET
// ----------------------------------------------------------------------------
/*
� JIT-������������� ���� ��������� �������� ������ near-������, ������� �� ��� ���� - ��� ��� ��.

ret:
	C3	- ��� ����������

ret i16:
	C2h A1 A0, ���:
		A1 A0 - ���������-�������� i16 = A0A1h � �������� ������� ������
*/

// ----------------------------------------------------------------------------
void AsmTranslator::Ret()
{
	m_machineCode << '\xC3';
}

// ----------------------------------------------------------------------------
void AsmTranslator::Ret(word popByteCount)
{
	m_machineCode << '\xC2' << popByteCount;
}

// ----------------------------------------------------------------------------
// RET
// ----------------------------------------------------------------------------
/*
call reg32:
	FFh 11010b AAA
		AAA - �������� ����� ��������
*/

// ----------------------------------------------------------------------------
void AsmTranslator::Call(RegisterInt32 address)
{
	m_machineCode << '\xFF' << byte(0b11010'000 | GetRegisterCode(address));
}

// ----------------------------------------------------------------------------
// PUSH / POP
// ----------------------------------------------------------------------------
/*
push reg32:
	01010b AAA
		AAA - �������� ����� ��������

push i32:
	6Ah A0
		���� i32 ����� ��� 000000A0h ��� FFFFFFA0h
		
	68h A3 A2 A1 A0
		A0 A1 A2 A3 h - i32

pop reg32:
	01011b AAA
		AAA - �������� ����� ��������
*/

// ----------------------------------------------------------------------------
void AsmTranslator::Push(RegisterInt32 source)
{
	m_machineCode << byte(0b01010'000 | GetRegisterCode(source));
}

// ----------------------------------------------------------------------------
void AsmTranslator::Push(int32 value)
{
	const byte PUSH_OPCODE_BYTE  = '\x6A';
	const byte PUSH_OPCODE_DWORD = '\x68';

	if (CanBeReducedToByte(value))
		m_machineCode << PUSH_OPCODE_BYTE << GetByte<3>(value);
	else
		m_machineCode << PUSH_OPCODE_DWORD << value;
}

// ----------------------------------------------------------------------------
void AsmTranslator::Pop(RegisterInt32 dest)
{
	m_machineCode << byte(0b01011'000 | GetRegisterCode(dest));
}

// ----------------------------------------------------------------------------
// INC / DEC
// ----------------------------------------------------------------------------
/*
inc reg32:
	01000b AAA
		AAA - �������� ����� ��������

inc reg16:
	66h 01000b AAA
		AAA - �������� ����� ��������

inc reg8:
	FEh 11000b AAA
		AAA - �������� ����� ��������


dec reg32:
	01001b AAA
		AAA - �������� ����� ��������

dec reg16:
	66h 01001b AAA
		AAA - �������� ����� ��������

dec reg8:
	FEh 11001b AAA
		AAA - �������� ����� ��������
*/

// ----------------------------------------------------------------------------
void AsmTranslator::Inc(RegisterInt32 reg)
{
	m_machineCode << byte(0b01000'000 | GetRegisterCode(reg));
}

// ----------------------------------------------------------------------------
void AsmTranslator::Inc(RegisterInt16 reg)
{
	m_machineCode << SIZE_PREFIX << byte(0b01000'000 | GetRegisterCode(reg));
}

// ----------------------------------------------------------------------------
void AsmTranslator::Inc(RegisterInt8 reg)
{
	m_machineCode << '\xFE' << byte(0b11000'000 | GetRegisterCode(reg));
}

// ----------------------------------------------------------------------------
void AsmTranslator::Dec(RegisterInt32 reg)
{
	m_machineCode << byte(0b01001'000 | GetRegisterCode(reg));
}

// ----------------------------------------------------------------------------
void AsmTranslator::Dec(RegisterInt16 reg)
{
	m_machineCode << SIZE_PREFIX << byte(0b01001'000 | GetRegisterCode(reg));
}

// ----------------------------------------------------------------------------
void AsmTranslator::Dec(RegisterInt8 reg)
{
	m_machineCode << '\xFE' << byte(0b11001'000 | GetRegisterCode(reg));
}

// ----------------------------------------------------------------------------
// MOV
// ----------------------------------------------------------------------------
/*
mov reg32, reg32:
	8Bh 11b AAA BBB
		AAA - �������� ����� ������� ��������
		BBB - �������� ����� ������� ��������

mov reg32, i32:
	10111b AAA A3 A2 A1 A0
		AAA - �������� ����� ������� ��������
		A3 A2 A1 A0 - i32

mov [reg32 + i32], reg32:
mov reg32, [reg32 + i32]:
	� �����:
		100010b x y  uv AAA BBB [24h] CONST
			x     - ���, 0 �������� ��� "[... + i32]" � ������ ���������, 1 ��� � �������
			y     - ��� �������, ��� �32 ������ ���������� � 1
			uv    - ��� ����:
				01 ������ ��� ������� i32 ����� ������ � ����
				10 - ��� 4 �����
				00 - ��� �������-��������� �����������
			AAA   - �������� ����� ������� (�������) ��������-��������
			BBB   - �������� ����� ������ (�������) ��������-��������
			CONST - ��������� i32, ������:
				C0          - 1 ����,  ���� uv=01
				C3 C2 C1 C0 - 4 �����, ���� uv=10

			����� ��� ������ [esp + Const]: ������ ��� ����� ��������
			���������� MS ��������� ����� ���������� 24h � ������ "��������"
			������� ������, �.�. ����� ��������� ������������ � 4 �����.
*/

// ----------------------------------------------------------------------------
void AsmTranslator::Mov(RegisterInt32 to, RegisterInt32 from)
{
	// 8Bh 11b AAA BBB
	m_machineCode << '\x8B' << byte(0b11'000'000 | GetRegisterCode(to) << 3 | GetRegisterCode(from));
}

// ----------------------------------------------------------------------------
void AsmTranslator::Mov(RegisterInt32 to, int32 value)
{
	// 10111b AAA A3 A2 A1 A0
	m_machineCode << byte(0b10111'000 | GetRegisterCode(to)) << value;
}

// ----------------------------------------------------------------------------
inline void AsmTranslator::MovImplementationIndirect(
	RegisterInt32 indirectRegister,
	RegisterInt32 directRegister,
	byte indirectOperandNum,
	std::optional<int32> offsetFromIndirectRegister)
{
	// ������ �������: [100010x1][uv AAA BBB][24h][CONST]

	// ����������� ���� ����������� x (indirectOperandNum).
	// indirectOperandNum ��������:
	//		0 ���� ������� ����� ��� "mov [eax + 123], ebx"
	//		1 ���� ������� ����� ��� "mov ebx, [eax + 123]"
	// �.�. �������� ����� ��������, � �������� ��������� ��������� ���������.
	m_machineCode << byte(0b100010'0'1 | indirectOperandNum << 1);

	// 00AAABBB
	const byte registers = GetRegisterCode(directRegister) << 3 | GetRegisterCode(indirectRegister);

	// ����������� ������ ��� esp.
	// ���� ������� �� �������� ���������� ��������� ��������� (���������� �����) - esp, ��
	// ����� ����� � �����������-���������� (�� �� ��������-���������, ���� �� ����) ����������� 24h.
	std::function<void()> processEsp = []() {};
	if (indirectRegister == RegisterInt32::ESP)
		processEsp = [mcc = &m_machineCode]() { (*mcc) << '\x24';};

	// ����������� ������ ��� ebp.
	// �� �����-�� �������� �������� [ebp] ������ ������������� ��� [ebp + 0].
	if (indirectRegister == RegisterInt32::EBP && !offsetFromIndirectRegister.has_value())
		offsetFromIndirectRegister = 0;

	// ����������� �������� � ��������� ��������� [register + offset]:
	// uv=01 - sizeof(offset) == byte
	// uv=10 - sizeof(offset) == dword
	// uv=00 - �������� ��� ������
	const bool offsetIsAbsent = !offsetFromIndirectRegister.has_value();

	if (offsetIsAbsent)
	{
		// ��������� ������� ��������� ��� ��������.
		m_machineCode << byte(0b00'000'000 | registers);
		processEsp();
		return;
	}

	// ��������� ������� ��������� �� ���������.
	auto offset = offsetFromIndirectRegister.value();
	if (CanBeReducedToByte(offset))
	{
		m_machineCode << byte(0b01'000'000 | registers);
		processEsp();
		m_machineCode << GetByte<3>(offset);
	}
	else
	{
		m_machineCode << byte(0b10'000'000 | registers);
		processEsp();
		m_machineCode << offset;
	}
}

// ----------------------------------------------------------------------------
void AsmTranslator::Mov(RegisterInt32PlusConstantIndirect to, RegisterInt32 from)
{
	MovImplementationIndirect(to.Register, from, 0, to.Constant);
}

// ----------------------------------------------------------------------------
void AsmTranslator::Mov(RegisterInt32 to, RegisterInt32PlusConstantIndirect from)
{
	MovImplementationIndirect(from.Register, to, 1, from.Constant);
}

// ----------------------------------------------------------------------------
void AsmTranslator::Mov(RegisterInt32Indirect to, RegisterInt32 from)
{
	MovImplementationIndirect(to.Register, from, 0, std::nullopt);
}

// ----------------------------------------------------------------------------
void AsmTranslator::Mov(RegisterInt32 to, RegisterInt32Indirect from)
{
	MovImplementationIndirect(from.Register, to, 1, std::nullopt);
}

// ----------------------------------------------------------------------------

/*
	mov [xxx + A], B:
	� - ����:
		C7 01000xxx [24] A0 B0 B1 B2 B3
	A - ������� �����:
		C7 10000xxx [24] A0 A1 A2 A3  B0 B1 B2 B3
*/

void AsmTranslator::Mov(RegisterInt32PlusConstantIndirect to, int32 value)
{
	const bool offsetIsByte = CanBeReducedToByte(to.Constant);
	const byte params = (offsetIsByte ? 0b01000'000 : 0b10000'000);
	m_machineCode << '\xC7' << byte(params | GetRegisterCode(to.Register));

	if (to.Register == RegisterInt32::ESP)
		m_machineCode << '\x24';

	if (offsetIsByte)
		m_machineCode << GetByte<3>(to.Constant);
	else
		m_machineCode << to.Constant;

	m_machineCode << value;
}

// ----------------------------------------------------------------------------

/*
	C7 00     C0 D4 01 00   mov dword ptr [eax],1D4C0h
	C7 01     C0 D4 01 00   mov dword ptr [ecx],1D4C0h
	C7 02     C0 D4 01 00   mov dword ptr [edx],1D4C0h
	C7 03     C0 D4 01 00   mov dword ptr [ebx],1D4C0h
	C7 04 24  C0 D4 01 00   mov dword ptr [esp],1D4C0h
	C7 45 00  C0 D4 01 00   mov dword ptr [ebp],1D4C0h
	C7 06     C0 D4 01 00   mov dword ptr [esi],1D4C0h
	C7 07     C0 D4 01 00   mov dword ptr [edi],1D4C0h
*/

void AsmTranslator::Mov(RegisterInt32Indirect to, int32 value)
{
	m_machineCode << '\xC7';

	if (to.Register == RegisterInt32::EBP)
		m_machineCode << '\x45' << '\x00';
	else
		m_machineCode << GetRegisterCode(to.Register);

	if (to.Register == RegisterInt32::ESP)
		m_machineCode << '\x24';

	m_machineCode << value;
}

// ----------------------------------------------------------------------------
