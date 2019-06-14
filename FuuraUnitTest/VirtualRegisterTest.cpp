#include "stdafx.h"
#include "CppUnitTest.h"
#include "CppUnitTestAssert.h"

// ��������� ���� �����.
#include <VirtualRegister.h>
#include <Exception.h>

namespace Microsoft::VisualStudio::CppUnitTestFramework
{
	template<> inline std::wstring ToString<fuura::compilation::RegisterInt8>(const fuura::compilation::RegisterInt8& t) { RETURN_WIDE_STRING((int)t); }
	template<> inline std::wstring ToString<fuura::compilation::RegisterInt32>(const fuura::compilation::RegisterInt32& t) { RETURN_WIDE_STRING((int)t); }
	template<> inline std::wstring ToString<fuura::compilation::RegisterType>(const fuura::compilation::RegisterType& t) { RETURN_WIDE_STRING(char(t)); }
}

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace fuura::compilation
{
	TEST_CLASS(VirtualRegisterTest)
	{
	public:
		// --------------------------------------------------------------------------
		TEST_METHOD(Test_VirtualRegister_ChainLength)
		{
			VirtualRegisterManager vrm;

			auto reg1a = vrm.AllocateInt32();									// ����� �������� reg1a
			Assert::AreEqual(1, reg1a.GetChainLength());						// ����� ����� �������� ������� ������������� = 1
			Assert::IsFalse(reg1a.IsSet());										// ����� ����� �������� ������� �� ����������
			Assert::IsTrue(reg1a.IsActual());									// ������� ���� �� ���������

			auto reg1b = reg1a;													// ����� ������������� reg1a
			Assert::AreEqual(2, reg1a.GetChainLength());						// ����� ������������� ������� ������������� �� 1
			Assert::AreEqual(reg1b.GetChainLength(), reg1a.GetChainLength());	// ���� ������� �� ��� �������
			Assert::AreEqual(reg1a.GetUID(), reg1b.GetUID());					// ���� UID �� ��� �������
			Assert::IsTrue(reg1a.IsActual());									// ������� �� ��� �� ���������

			auto reg2 = vrm.AllocateInt32();									// ���������� ����� �������
			Assert::AreNotEqual(reg1a.GetUID(), reg2.GetUID());					// �� ����� � ���������� ������ ������
			Assert::AreEqual(1, reg2.GetChainLength());							// ���������� reg1a ��� ��������
			Assert::IsTrue(reg2.IsActual());									// ���������� reg1a ��� ��������

			auto reg1c = reg1a;													// ���������� reg1b = reg1a
			Assert::AreEqual(3, reg1a.GetChainLength());						// ����������
			Assert::AreEqual(3, reg1b.GetChainLength());						// ����������
			Assert::AreEqual(3, reg1c.GetChainLength());						// ����������
			Assert::IsTrue(reg1a.IsActual());									// ����������
			Assert::AreEqual(1, reg2.GetChainLength());							// ������� �� ������ ���� �� �����

			reg1a.EndChain();													// ��������� ������ �������
			Assert::IsFalse(reg1a.IsActual());									// � ���������, ��������� �� ��� ������
			Assert::IsFalse(reg1b.IsActual());									// �����������, � ������ �� �� ����� ������� ����������
			Assert::IsFalse(reg1c.IsActual());									// ��������� ���� � ��� ��

			Assert::IsTrue(reg2.IsActual());									// ������ ������� ��� ���������, ���� ������ ��� ���������
			reg2.EndChain();													// ��������� ������ �������
			Assert::IsFalse(reg2.IsActual());									// � ���������

			Assert::IsTrue(reg1a == reg1b && reg1b == reg1c);					// ��� �������� ����� ���� ��������� � ����� �������
			Assert::IsFalse(reg1a == reg2);										// � �� ����� � ���� ������
		}

		// --------------------------------------------------------------------------
		TEST_METHOD(Test_VirtualRegister_GetSetValue)
		{
			VirtualRegisterManager vrm;

			auto reg1a = vrm.AllocateInt32();
			Assert::IsFalse(reg1a.IsSet());							// ��� �������� �������� �� �����������

			Assert::ExpectException<RegisterValueIsNotSet>([&]() {	// ������� ������ ��, �������� �������� �� �����������
				reg1a.GetValueAsInt32();
			});

			Assert::ExpectException<RegisterTypeMismatch>([&]() {	// ������� ��������� � �� �������� ������� ����
				reg1a.SetValue(RegisterFloat64::ST0);
			});

			// ������������� �������� �� � ��������� ���������� ���������:
			reg1a.SetValue(RegisterInt32::EAX);
			Assert::IsTrue(reg1a.IsSet());
			Assert::AreEqual(RegisterInt32::EAX, reg1a.GetValueAsInt32());

			Assert::ExpectException<RegisterTypeMismatch>([&]() {	// ������� ������ �� �� �������� ������� ����
				reg1a.GetValueAsInt16();
			});

			// ��������� �� ���� �� ������� ����� �� �� ��������� � �������� ���������:
			auto reg1b = reg1a;
			Assert::IsTrue(reg1b.IsSet());
			Assert::AreEqual(reg1a.GetValueAsInt32(), reg1b.GetValueAsInt32());

			// � �� ����� ��� �� ������ ������� ����� �� ������� �� ������:
			auto reg2 = vrm.AllocateInt32();
			Assert::IsFalse(reg2.IsSet());
		}

		// --------------------------------------------------------------------------
		TEST_METHOD(Test_VirtualRegister_ManagerAccess)
		{
			VirtualRegisterManager vrm;
			auto regs = vrm.GetAllocatedRegisters();
			Assert::IsTrue(regs.empty());

			VirtualRegister reg1a = vrm.AllocateInt32();			// ������������: [vrd1:1] �������: vrd1 - ���������
			regs = vrm.GetAllocatedRegisters();						// ���������� ��������, �������� ������� ��� ���� ������������� �� ������
			Assert::AreEqual(size_t(1), regs.size());			
			Assert::AreEqual(1, regs[0].GetChainLength());			// ��������� ��� �� �����������
			Assert::AreEqual(RegisterType::DoubleWord, regs[0].GetType());
			Assert::IsFalse(regs[0].IsSet());

			VirtualRegister reg1b = reg1a;						// ������������: [vrd1:2] �������: vrd1 - �������������
			VirtualRegister reg2  = vrm.AllocateInt8();			// ������������: [vrd1:2, vrb2:1] �������: vrb2 - ���������
			regs = vrm.GetAllocatedRegisters();
			Assert::AreEqual(size_t(2), regs.size());
			Assert::AreEqual(RegisterType::DoubleWord, regs[0].GetType());
			Assert::AreEqual(RegisterType::Byte,       regs[1].GetType());
			Assert::IsFalse(regs[0].IsSet());
			Assert::IsFalse(regs[1].IsSet());
			Assert::AreEqual(2, regs[0].GetChainLength());
			Assert::AreEqual(1, regs[1].GetChainLength());

			reg1a.EndChain();									// ������������: [vrb2:1] �������: vrd1 - ���������� �������
			regs[1].SetValue(RegisterInt8::BH);					// ������������� �������� �� ����� ��������
			reg2.EndChain();									// ������������: [] �������: vrb2 - ���������� �������
			regs = vrm.GetAllocatedRegisters();
			Assert::AreEqual(size_t(2), regs.size());
			Assert::AreEqual(RegisterType::DoubleWord, regs[0].GetType());
			Assert::AreEqual(RegisterType::Byte, regs[1].GetType());
			Assert::IsFalse(regs[0].IsSet());
			Assert::IsTrue(regs[1].IsSet());
			Assert::AreEqual(2, regs[0].GetChainLength());
			Assert::AreEqual(1, regs[1].GetChainLength());
			Assert::AreEqual(RegisterInt8::BH, regs[1].GetValueAsInt8());	// ��������� ���������� ��������� ��������
			Assert::AreEqual(RegisterInt8::BH, reg2.GetValueAsInt8());		// ��������� ���������� ��������� ��������
		}

		// --------------------------------------------------------------------------
	};
}