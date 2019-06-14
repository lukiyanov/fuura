#include "stdafx.h"
#include "CppUnitTest.h"
#include "CppUnitTestAssert.h"

// ��������� ���� �����.
#include <MachineCodeContainer.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace fuura::compilation
{
	TEST_CLASS(MachineCodeContainerTest)
	{
	public:
		// --------------------------------------------------------------------------
		TEST_METHOD(Test_Container)
		{
			MachineCodeContainer codeContainer;

			// ����� ����� �������� ��������� ����.
			Assert::AreEqual(size_t(0), codeContainer.GetCodeSize());

			// �������� << ��������� ������ � ����� ����������.
			// � ��������� ����� �������� ����- � �����- �������� �������.
			// �������� �� ������ � ��� �������� ���������.
			const char testChars[] = { '\x01', '\x02', '\x03' };
			codeContainer << testChars[0] << testChars[1] << byte(testChars[2]);

			// ������������ �������� ������������� � �������� ������� ������.
			// �� ���� 0x1234 ����� ������� �� 0x12 0x34 � �������� � ��������� ��� (..., 0x34, 0x12, ...).
			// ������� ����� ������������� �������� ��� ���� �����������.
			codeContainer << short(0x1234) << unsigned short(0x5678) << 0x12345678L << byte(0xC0) << 0xF9ABCDEFUL << char(0x33);

			// �.�. ����� ���� � ��������� ���� ��������� ���������:
			const char codeExpected[] = {
				testChars[0], testChars[1], testChars[2],

				'\x34', '\x12',					// 0x1234
				'\x78', '\x56',					// 0x5678
				'\x78', '\x56', '\x34', '\x12',	// 0x12345678
				'\xC0',							// 0xC0
				'\xEF', '\xCD', '\xAB', '\xF9',	// 0xF9ABCDEF
				'\x33'							// 0x33
			};
			
			// ���������, ��� �� ���:
			auto code = codeContainer.GetCode();
			for (int i = 0; i < sizeof(codeExpected); i++)
				Assert::AreEqual(codeExpected[i], char(code[i]));

			// ������ ���������� - ���������� ���� ������ ����.
			Assert::AreEqual(sizeof(codeExpected), codeContainer.GetCodeSize());

			// ������� ���������.
			codeContainer.Clear();
			// ����� ������� ��������� ����.
			Assert::AreEqual(size_t(0), codeContainer.GetCodeSize());
			// ������� ��������� ��������� �� ��� ������� ���������� ������� � ����������.
			Assert::ExpectException<std::out_of_range>([&codeContainer]() { codeContainer.GetCode(); });
		}

		// --------------------------------------------------------------------------
	};
}