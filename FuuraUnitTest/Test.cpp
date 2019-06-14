#include "stdafx.h"
#include "CppUnitTest.h"
#include "CppUnitTestAssert.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace deleteme
{
	TEST_CLASS(TestTest)
	{
	public:

		TEST_METHOD(Test_Test)
		{
			__asm
			{
				// “ест дл€ вс€кой временной ерунды, например чтобы узнавать опкоды команд
				jmp endl
				mov dword ptr [ebp + 0x12345678], 0xABCDEFEF

				mov dword ptr [eax], 120000
				mov dword ptr [ecx], 120000
				mov dword ptr [edx], 120000
				mov dword ptr [ebx], 120000
				mov dword ptr [esp], 120000
				mov dword ptr [ebp], 120000
				mov dword ptr [esi], 120000
				mov dword ptr [edi], 120000
				mov dword ptr [eax], 12
				mov dword ptr [eax], 12
				mov dword ptr [eax], 120000
				mov dword ptr [eax], 0x12345678

				endl:
			}
		}
	};
}