#include "stdafx.h"
#include "AsmTranslator.h"
using namespace fuura::compilation;

#include <functional>

// Префикс изменения размера операндов.
const byte SIZE_PREFIX = '\x66';

// ------------------------------------------------------------------------
void AsmTranslator::RestartBuilding()
{
	m_machineCode.Clear();
}

// ------------------------------------------------------------------------
// Немного тяжеловесно, но нигде кроме юнит-тестов это всё равно не используется.
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
	// Компилятор Microsoft использует "короткие" команды,
	// если операнд-константа находится в промежутке (-129, 128),
	// а если нет то генерит "длинные".
	// Сделаем также.
	return -129 < constantToReduce && constantToReduce < 128;
}


///////////////////////////////////////////////////////////////////////////////
//
//	Реализации команд.
//
///////////////////////////////////////////////////////////////////////////////

// ----------------------------------------------------------------------------
// NOP
// ----------------------------------------------------------------------------
/*
Структура команды:
	nop - это 90h
*/

void AsmTranslator::Nop()
{
	m_machineCode << '\x90';
}

// ----------------------------------------------------------------------------
// XOR
// ----------------------------------------------------------------------------
/*
Структура команды:
	xor reg32, reg32:
		33h 11b AAA BBB, где:
			AAA - двоичный номер первого операнда
			BBB - двоичный номер второго операнда

	xor reg16, reg16:
		66h 33h 11b AAA BBB
			Т.е. то же + префикс 66h в качестве первого байта
		
	xor reg8, reg8:
		32h 11b AAA BBB
			Т.е. то же, только первый байт 32h, а не 33h
			(это связано с битом размера, судя по всему)
*/

// Отключаем выравнивание полей у структуры, чтобы между ними не было зазоров.
// NB: поля структур идут в обратном порядке относительно участков команд,
// которые они реализуют.
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
В JIT-компилируемом коде корректно работает только near-версия, поэтому всё что ниже - это про неё.

ret:
	C3	- без аргументов

ret i16:
	C2h A1 A0, где:
		A1 A0 - константа-аргумент i16 = A0A1h в обратном порядке байтов
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
		AAA - двоичный номер регистра
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
		AAA - двоичный номер регистра

push i32:
	6Ah A0
		если i32 имеет вид 000000A0h или FFFFFFA0h
		
	68h A3 A2 A1 A0
		A0 A1 A2 A3 h - i32

pop reg32:
	01011b AAA
		AAA - двоичный номер регистра
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
		AAA - двоичный номер регистра

inc reg16:
	66h 01000b AAA
		AAA - двоичный номер регистра

inc reg8:
	FEh 11000b AAA
		AAA - двоичный номер регистра


dec reg32:
	01001b AAA
		AAA - двоичный номер регистра

dec reg16:
	66h 01001b AAA
		AAA - двоичный номер регистра

dec reg8:
	FEh 11001b AAA
		AAA - двоичный номер регистра
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
		AAA - двоичный номер первого операнда
		BBB - двоичный номер второго операнда

mov reg32, i32:
	10111b AAA A3 A2 A1 A0
		AAA - двоичный номер первого операнда
		A3 A2 A1 A0 - i32

mov [reg32 + i32], reg32:
mov reg32, [reg32 + i32]:
	В целом:
		100010b x y  uv AAA BBB [24h] CONST
			x     - бит, 0 означает что "[... + i32]" у левого аргумента, 1 что у правого
			y     - бит размера, для х32 всегда установлен в 1
			uv    - два бита:
				01 значит что операнд i32 имеет размер в байт
				10 - что 4 байта
				00 - что операнд-константа отсутствует
			AAA   - двоичный номер ПРАВОГО (второго) операнда-регистра
			BBB   - двоичный номер ЛЕВОГО (первого) операнда-регистра
			CONST - константа i32, причём:
				C0          - 1 байт,  если uv=01
				C3 C2 C1 C0 - 4 байта, если uv=10

			Также для случая [esp + Const]: именно для этого регистра
			компилятор MS вставляет перед константой 24h в случае "длинного"
			формата записи, т.е. когда константа записывается в 4 байта.
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
	// Формат команды: [100010x1][uv AAA BBB][24h][CONST]

	// Проставляем флаг направления x (indirectOperandNum).
	// indirectOperandNum содержит:
	//		0 если команда имеет вид "mov [eax + 123], ebx"
	//		1 если команда имеет вид "mov ebx, [eax + 123]"
	// Т.е. содержит номер операнда, к которому относится косвенная адресация.
	m_machineCode << byte(0b100010'0'1 | indirectOperandNum << 1);

	// 00AAABBB
	const byte registers = GetRegisterCode(directRegister) << 3 | GetRegisterCode(indirectRegister);

	// Специальный случай для esp.
	// Если регистр по которому происходит косвенная адресация (содержащий адрес) - esp, то
	// после байта с параметрами-регистрами (но до операнда-константы, если он есть) вставляется 24h.
	std::function<void()> processEsp = []() {};
	if (indirectRegister == RegisterInt32::ESP)
		processEsp = [mcc = &m_machineCode]() { (*mcc) << '\x24';};

	// Специальный случай для ebp.
	// По каким-то причинам параметр [ebp] всегда транслируется как [ebp + 0].
	if (indirectRegister == RegisterInt32::EBP && !offsetFromIndirectRegister.has_value())
		offsetFromIndirectRegister = 0;

	// Проставляем смещение в косвенной адресации [register + offset]:
	// uv=01 - sizeof(offset) == byte
	// uv=10 - sizeof(offset) == dword
	// uv=00 - смещения нет вообще
	const bool offsetIsAbsent = !offsetFromIndirectRegister.has_value();

	if (offsetIsAbsent)
	{
		// Косвенная базовая адресация без смещения.
		m_machineCode << byte(0b00'000'000 | registers);
		processEsp();
		return;
	}

	// Косвенная базовая адресация со смещением.
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
	А - байт:
		C7 01000xxx [24] A0 B0 B1 B2 B3
	A - двойное слово:
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
