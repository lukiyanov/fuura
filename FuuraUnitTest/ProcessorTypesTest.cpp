#include "stdafx.h"
#include "CppUnitTest.h"
#include "CppUnitTestAssert.h"

// Тестируем этот файл.
#include <ProcessorTypes.h>

namespace Microsoft::VisualStudio::CppUnitTestFramework
{
	template<> inline std::wstring ToString<fuura::compilation::RegisterInt32>
		(const fuura::compilation::RegisterInt32& v) { RETURN_WIDE_STRING(static_cast<int>(v)); }
}

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace fuura::compilation
{
	TEST_CLASS(ProcessorTypesTest)
	{
	public:
		// --------------------------------------------------------------------------
		TEST_METHOD(Test_GetRegisterCode)
		{
			// Коды регистров жёстко завязаны на указанные ниже значения.

			Assert::AreEqual(byte(0), GetRegisterCode(RegisterInt32::EAX));
			Assert::AreEqual(byte(1), GetRegisterCode(RegisterInt32::ECX));
			Assert::AreEqual(byte(2), GetRegisterCode(RegisterInt32::EDX));
			Assert::AreEqual(byte(3), GetRegisterCode(RegisterInt32::EBX));
			Assert::AreEqual(byte(4), GetRegisterCode(RegisterInt32::ESP));
			Assert::AreEqual(byte(5), GetRegisterCode(RegisterInt32::EBP));
			Assert::AreEqual(byte(6), GetRegisterCode(RegisterInt32::ESI));
			Assert::AreEqual(byte(7), GetRegisterCode(RegisterInt32::EDI));

			Assert::AreEqual(byte(0), GetRegisterCode(RegisterInt16::AX));
			Assert::AreEqual(byte(1), GetRegisterCode(RegisterInt16::CX));
			Assert::AreEqual(byte(2), GetRegisterCode(RegisterInt16::DX));
			Assert::AreEqual(byte(3), GetRegisterCode(RegisterInt16::BX));
			Assert::AreEqual(byte(4), GetRegisterCode(RegisterInt16::SP));
			Assert::AreEqual(byte(5), GetRegisterCode(RegisterInt16::BP));
			Assert::AreEqual(byte(6), GetRegisterCode(RegisterInt16::SI));
			Assert::AreEqual(byte(7), GetRegisterCode(RegisterInt16::DI));

			Assert::AreEqual(byte(0), GetRegisterCode(RegisterInt8::AL));
			Assert::AreEqual(byte(1), GetRegisterCode(RegisterInt8::CL));
			Assert::AreEqual(byte(2), GetRegisterCode(RegisterInt8::DL));
			Assert::AreEqual(byte(3), GetRegisterCode(RegisterInt8::BL));
			Assert::AreEqual(byte(4), GetRegisterCode(RegisterInt8::AH));
			Assert::AreEqual(byte(5), GetRegisterCode(RegisterInt8::CH));
			Assert::AreEqual(byte(6), GetRegisterCode(RegisterInt8::DH));
			Assert::AreEqual(byte(7), GetRegisterCode(RegisterInt8::BH));
		}

		// --------------------------------------------------------------------------
		TEST_METHOD(Test_GetByte)
		{
			// GetByte<N> N =   0    1    2    3
			// 0x12345678 -> 0x12 0x34 0x56 0x78

			Assert::AreEqual(byte(0xFE), GetByte<0>(char(0xFE)));

			Assert::AreEqual(byte(0xFE), GetByte<0>(byte(0xFE)));
 
			Assert::AreEqual(byte(0xFE), GetByte<0>(word(0xFEDC)));
			Assert::AreEqual(byte(0xDC), GetByte<1>(word(0xFEDC)));

			Assert::AreEqual(byte(0xFE), GetByte<0>(int16(0xFEDC)));
			Assert::AreEqual(byte(0xDC), GetByte<1>(int16(0xFEDC)));

			Assert::AreEqual(byte(0xFE), GetByte<0>(dword(0xFEDCBA98)));
			Assert::AreEqual(byte(0xDC), GetByte<1>(dword(0xFEDCBA98)));
			Assert::AreEqual(byte(0xBA), GetByte<2>(dword(0xFEDCBA98)));
			Assert::AreEqual(byte(0x98), GetByte<3>(dword(0xFEDCBA98)));

			Assert::AreEqual(byte(0xFE), GetByte<0>(int32(0xFEDCBA98)));
			Assert::AreEqual(byte(0xDC), GetByte<1>(int32(0xFEDCBA98)));
			Assert::AreEqual(byte(0xBA), GetByte<2>(int32(0xFEDCBA98)));
			Assert::AreEqual(byte(0x98), GetByte<3>(int32(0xFEDCBA98)));

			// Не скомпилируется, т.к. байт №4 выходит за пределы типа int32:
			// Assert::AreEqual(GetByte<4>(byte(0x98), int32(0xFEDCBA98)));
		}

		// --------------------------------------------------------------------------
		TEST_METHOD(Test_Indirect)
		{
			const int32 constant = 1'234'567'891;
			const auto reg = RegisterInt32::EDX;

			const auto reg_plus_c = reg + constant;
			Assert::AreEqual(constant, reg_plus_c.Constant);
			Assert::AreEqual(reg, reg_plus_c.Register);

			const auto reg_minus_c = reg - constant;
			Assert::AreEqual(constant, -reg_minus_c.Constant);
			Assert::AreEqual(reg, reg_minus_c.Register);

			const auto indirect_reg = I[reg];
			Assert::AreEqual(reg, indirect_reg.Register);

			const auto indirect_reg_plus_c = I[reg + constant];
			Assert::AreEqual(constant, indirect_reg_plus_c.Constant);
			Assert::AreEqual(reg, indirect_reg_plus_c.Register);

			const auto indirect_reg_minus_c = I[reg - constant];
			Assert::AreEqual(constant, -indirect_reg_minus_c.Constant);
			Assert::AreEqual(reg, indirect_reg_minus_c.Register);
		}

		// --------------------------------------------------------------------------
	};
}