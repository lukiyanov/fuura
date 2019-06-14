#include "stdafx.h"
#include "CppUnitTest.h"
#include "CppUnitTestAssert.h"

// Тестируем этот класс.
#include <AsmTranslator.h>

// Предупреждение #4731.
// "Регистр указателя фрейма "ebp" изменен встроенным кодом на языке ассемблера".
// На самом деле ebp нигде не меняется: все подобные инструкции обходятся через jmp,
// а ассемблерный код используется только как эталон для тестов и реально не выполняется.
#pragma warning (push)
#pragma warning (disable:4731)

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace fuura::compilation
{
	auto eax = RegisterInt32::EAX;
	auto ebx = RegisterInt32::EBX;
	auto ecx = RegisterInt32::ECX;
	auto edx = RegisterInt32::EDX;
	auto esi = RegisterInt32::ESI;
	auto edi = RegisterInt32::EDI;
	auto esp = RegisterInt32::ESP;
	auto ebp = RegisterInt32::EBP;

	auto ax = RegisterInt16::AX;
	auto bx = RegisterInt16::BX;
	auto cx = RegisterInt16::CX;
	auto dx = RegisterInt16::DX;
	auto si = RegisterInt16::SI;
	auto di = RegisterInt16::DI;
	auto sp = RegisterInt16::SP;
	auto bp = RegisterInt16::BP;

	auto al = RegisterInt8::AL;
	auto bl = RegisterInt8::BL;
	auto cl = RegisterInt8::CL;
	auto dl = RegisterInt8::DL;
	auto ah = RegisterInt8::AH;
	auto bh = RegisterInt8::BH;
	auto ch = RegisterInt8::CH;
	auto dh = RegisterInt8::DH;

	TEST_CLASS(AsmTranslatorTest)
	{
	private:

		// --------------------------------------------------------------------------
		// Проверяет, совпадает ли сгенерированный компилятором код с оригиналом.
		void CheckCodeEquality(AsmTranslator& translator, byte* original)
		{
			int num = 0;
			for (byte b : translator.GetCopyOfCurrentCode())
			{
				Assert::AreEqual(*original, b, ToString(num).c_str());
				original++;
				num++;
			}

			Assert::AreEqual(byte('\xCC'), *original, L"Остался код ассемблерной вставки, не покрытый тестом");
		}

		// --------------------------------------------------------------------------

	public:
		// --------------------------------------------------------------------------
		TEST_METHOD(Test_NOP)
		{
			byte* original;
			__asm call l_original		// Адрес следующей инструкции заносим в стек.
			__asm l_original:
			__asm jmp l_exit			// Пропускаем "правильный" код. Сам jmp имеет размер 2 байта.
			// Правильный вариант трансляции
			__asm nop
			// Конец правильного варианта трансляции
			__asm int 03h				// Пометка конца правильного кода, её достижение проверяется
			__asm l_exit:
			__asm pop original			// original = адрес jmp + 2 = адрес правильного варианта кода
			original += 2;

			// Тестируемый код.
			AsmTranslator translator;
			translator.Nop();

			// Проверка результата.
			CheckCodeEquality(translator, original);
		}

		// --------------------------------------------------------------------------
		TEST_METHOD(Test_RET)
		{
			byte* original;
			__asm call l_original		// Адрес следующей инструкции заносим в стек.
			__asm l_original:
			__asm jmp l_exit			// Пропускаем "правильный" код. Сам jmp имеет размер 2 байта.
			// Правильный вариант трансляции
			__asm ret
			__asm ret 123
			// Конец правильного варианта трансляции
			__asm int 03h				// Пометка конца правильного кода, её достижение проверяется
			__asm l_exit:
			__asm pop original			// original = адрес jmp + 2 = адрес правильного варианта кода
			original += 2;

			// Тестируемый код.
			AsmTranslator translator;
			translator.Ret();
			translator.Ret(123);

			// Проверка результата.
			CheckCodeEquality(translator, original);
		}

		// --------------------------------------------------------------------------
		TEST_METHOD(Test_XOR)
		{
			byte* original;
			__asm call l_original		// Адрес следующей инструкции заносим в стек.
			__asm l_original:
			__asm jmp l_exit			// Пропускаем "правильный" код. Сам jmp имеет размер 2 байта.
			// Правильный вариант трансляции
			__asm xor eax, ebx
			__asm xor ecx, edx
			__asm xor esp, ebp
			__asm xor esi, edi

			__asm xor ax, sp
			__asm xor bx, bp
			__asm xor cx, si
			__asm xor dx, di

			__asm xor al, ah
			__asm xor bl, bh
			__asm xor cl, ch
			__asm xor dl, dh
			// Конец правильного варианта трансляции
			__asm int 03h				// Пометка конца правильного кода, её достижение проверяется
			__asm l_exit:
			__asm pop original			// original = адрес jmp + 2 = адрес правильного варианта кода
			original += 2;

			// Тестируемый код.
			AsmTranslator translator;
			translator.Xor(eax, ebx);
			translator.Xor(ecx, edx);
			translator.Xor(esp, ebp);
			translator.Xor(esi, edi);

			translator.Xor(ax, sp);
			translator.Xor(bx, bp);
			translator.Xor(cx, si);
			translator.Xor(dx, di);

			translator.Xor(al, ah);
			translator.Xor(bl, bh);
			translator.Xor(cl, ch);
			translator.Xor(dl, dh);

			// Проверка результата.
			CheckCodeEquality(translator, original);
		}

		// --------------------------------------------------------------------------
		TEST_METHOD(Test_CALL)
		{
			byte* original;
			__asm call l_original		// Адрес следующей инструкции заносим в стек.
			__asm l_original:
			__asm jmp l_exit			// Пропускаем "правильный" код. Сам jmp имеет размер 2 байта.
			// Правильный вариант трансляции
			__asm call eax
			__asm call ecx
			__asm call edx
			__asm call ebx
			__asm call esp
			__asm call ebp
			__asm call esi
			__asm call edi
			// Конец правильного варианта трансляции
			__asm int 03h				// Пометка конца правильного кода, её достижение проверяется
			__asm l_exit:
			__asm pop original			// original = адрес jmp + 2 = адрес правильного варианта кода
			original += 2;

			// Тестируемый код.
			AsmTranslator translator;
			translator.Call(eax);
			translator.Call(ecx);
			translator.Call(edx);
			translator.Call(ebx);
			translator.Call(esp);
			translator.Call(ebp);
			translator.Call(esi);
			translator.Call(edi);

			// Проверка результата.
			CheckCodeEquality(translator, original);
		}

		// --------------------------------------------------------------------------
		TEST_METHOD(Test_PUSH_POP)
		{
			byte* original;
			__asm call l_original		// Адрес следующей инструкции заносим в стек.
			__asm l_original:
			__asm jmp l_exit			// Пропускаем "правильный" код. Сам jmp имеет размер 2 байта.
			// Правильный вариант трансляции
			__asm push eax
			__asm push ecx
			__asm push edx
			__asm push ebx
			__asm push esp
			__asm push ebp
			__asm push esi
			__asm push edi

			__asm push 0
			__asm push 0x1
			__asm push 0x12
			__asm push 0x123
			__asm push 0x127
			__asm push 0x128
			__asm push 0x129
			__asm push 0x130
			__asm push 0x1234
			__asm push 0x12345
			__asm push 0x123456
			__asm push 0x12345678

			__asm push -0x1
			__asm push -0x12
			__asm push -0x123
			__asm push -0x127
			__asm push -0x128
			__asm push -0x129
			__asm push -0x130
			__asm push -0x1234
			__asm push -0x12345
			__asm push -0x123456
			__asm push -0x12345678

			__asm pop eax
			__asm pop ecx
			__asm pop edx
			__asm pop ebx
			__asm pop esp
			__asm pop ebp
			__asm pop esi
			__asm pop edi
			// Конец правильного варианта трансляции
			__asm int 03h				// Пометка конца правильного кода, её достижение проверяется
			__asm l_exit:
			__asm pop original			// original = адрес jmp + 2 = адрес правильного варианта кода
			original += 2;

			// Тестируемый код.
			AsmTranslator translator;
			translator.Push(eax);
			translator.Push(ecx);
			translator.Push(edx);
			translator.Push(ebx);
			translator.Push(esp);
			translator.Push(ebp);
			translator.Push(esi);
			translator.Push(edi);

			translator.Push(0);
			translator.Push(0x1);
			translator.Push(0x12);
			translator.Push(0x123);
			translator.Push(0x127);
			translator.Push(0x128);
			translator.Push(0x129);
			translator.Push(0x130);
			translator.Push(0x1234);
			translator.Push(0x12345);
			translator.Push(0x123456);
			translator.Push(0x12345678);

			translator.Push(-0x1);
			translator.Push(-0x12);
			translator.Push(-0x123);
			translator.Push(-0x127);
			translator.Push(-0x128);
			translator.Push(-0x129);
			translator.Push(-0x130);
			translator.Push(-0x1234);
			translator.Push(-0x12345);
			translator.Push(-0x123456);
			translator.Push(-0x12345678);

			translator.Pop(eax);
			translator.Pop(ecx);
			translator.Pop(edx);
			translator.Pop(ebx);
			translator.Pop(esp);
			translator.Pop(ebp);
			translator.Pop(esi);
			translator.Pop(edi);

			// Проверка результата.
			CheckCodeEquality(translator, original);
		}

		// --------------------------------------------------------------------------
		TEST_METHOD(Test_INC)
		{
			byte* original;
			__asm call l_original		// Адрес следующей инструкции заносим в стек.
			__asm l_original:
			__asm jmp l_exit			// Пропускаем "правильный" код. Сам jmp имеет размер 2 байта.
			// Правильный вариант трансляции
			__asm inc eax
			__asm inc ecx
			__asm inc edx
			__asm inc ebx
			__asm inc esp
			__asm inc ebp
			__asm inc esi
			__asm inc edi

			__asm inc ax
			__asm inc cx
			__asm inc dx
			__asm inc bx
			__asm inc sp
			__asm inc bp
			__asm inc si
			__asm inc di

			__asm inc al
			__asm inc cl
			__asm inc dl
			__asm inc bl
			__asm inc ah
			__asm inc ch
			__asm inc dh
			__asm inc bh
			// Конец правильного варианта трансляции
			__asm int 03h				// Пометка конца правильного кода, её достижение проверяется
			__asm l_exit:
			__asm pop original			// original = адрес jmp + 2 = адрес правильного варианта кода
			original += 2;

			// Тестируемый код.
			AsmTranslator translator;
			translator.Inc(eax);
			translator.Inc(ecx);
			translator.Inc(edx);
			translator.Inc(ebx);
			translator.Inc(esp);
			translator.Inc(ebp);
			translator.Inc(esi);
			translator.Inc(edi);

			translator.Inc(ax);
			translator.Inc(cx);
			translator.Inc(dx);
			translator.Inc(bx);
			translator.Inc(sp);
			translator.Inc(bp);
			translator.Inc(si);
			translator.Inc(di);

			translator.Inc(al);
			translator.Inc(cl);
			translator.Inc(dl);
			translator.Inc(bl);
			translator.Inc(ah);
			translator.Inc(ch);
			translator.Inc(dh);
			translator.Inc(bh);

			// Проверка результата.
			CheckCodeEquality(translator, original);
		}

		// --------------------------------------------------------------------------
		TEST_METHOD(Test_DEC)
		{
			byte* original;
			__asm call l_original		// Адрес следующей инструкции заносим в стек.
			__asm l_original:
			__asm jmp l_exit			// Пропускаем "правильный" код. Сам jmp имеет размер 2 байта.
			// Правильный вариант трансляции
			__asm dec eax
			__asm dec ecx
			__asm dec edx
			__asm dec ebx
			__asm dec esp
			__asm dec ebp
			__asm dec esi
			__asm dec edi

			__asm dec ax
			__asm dec cx
			__asm dec dx
			__asm dec bx
			__asm dec sp
			__asm dec bp
			__asm dec si
			__asm dec di

			__asm dec al
			__asm dec cl
			__asm dec dl
			__asm dec bl
			__asm dec ah
			__asm dec ch
			__asm dec dh
			__asm dec bh
			// Конец правильного варианта трансляции
			__asm int 03h				// Пометка конца правильного кода, её достижение проверяется
			__asm l_exit:
			__asm pop original			// original = адрес jmp + 2 = адрес правильного варианта кода
			original += 2;

			// Тестируемый код.
			AsmTranslator translator;
			translator.Dec(eax);
			translator.Dec(ecx);
			translator.Dec(edx);
			translator.Dec(ebx);
			translator.Dec(esp);
			translator.Dec(ebp);
			translator.Dec(esi);
			translator.Dec(edi);

			translator.Dec(ax);
			translator.Dec(cx);
			translator.Dec(dx);
			translator.Dec(bx);
			translator.Dec(sp);
			translator.Dec(bp);
			translator.Dec(si);
			translator.Dec(di);

			translator.Dec(al);
			translator.Dec(cl);
			translator.Dec(dl);
			translator.Dec(bl);
			translator.Dec(ah);
			translator.Dec(ch);
			translator.Dec(dh);
			translator.Dec(bh);

			// Проверка результата.
			CheckCodeEquality(translator, original);
		}

		// --------------------------------------------------------------------------
		TEST_METHOD(Test_MOV_REG_REG)
		{
			byte* original;
			__asm {
				call l_original		// Адрес следующей инструкции заносим в стек.
				l_original:
				jmp l_exit			// Пропускаем "правильный" код. Сам jmp имеет размер 2 байта.
			// Правильный вариант трансляции
				mov eax, esi
				mov ebx, edi
				mov ecx, esp
				mov edx, ebp
			// Конец правильного варианта трансляции
				int 03h				// Пометка конца правильного кода, её достижение проверяется
				l_exit:
				pop original			// original = адрес jmp + 2 = адрес правильного варианта кода
			}
			original += 2;

			// Тестируемый код.
			AsmTranslator translator;
			translator.Mov(eax, esi);
			translator.Mov(ebx, edi);
			translator.Mov(ecx, esp);
			translator.Mov(edx, ebp);

			// Проверка результата.
			CheckCodeEquality(translator, original);
		}

		// --------------------------------------------------------------------------
		TEST_METHOD(Test_MOV_REG_CONST)
		{
			byte* original;
			__asm {
				call l_original		// Адрес следующей инструкции заносим в стек.
				l_original:
				jmp l_exit			// Пропускаем "правильный" код. Сам jmp имеет размер 2 байта.
			// Правильный вариант трансляции
				mov eax, 0
				mov eax, 1
				mov eax, 20
				mov eax, 100
				mov eax, 127
				mov eax, 128
				mov eax, 129
				mov eax, 130
				mov eax, 10000
				mov eax, 0x12345678
				mov eax, -1
				mov eax, -20
				mov eax, -100
				mov eax, -127
				mov eax, -128
				mov eax, -129
				mov eax, -130
				mov eax, -10000
				mov eax, -0x12345678
			// Конец правильного варианта трансляции
				int 03h				// Пометка конца правильного кода, её достижение проверяется
				l_exit:
				pop original			// original = адрес jmp + 2 = адрес правильного варианта кода
			}
			original += 2;

			// Тестируемый код.
			AsmTranslator translator;

			translator.Mov(eax, 0);
			translator.Mov(eax, 1);
			translator.Mov(eax, 20);
			translator.Mov(eax, 100);
			translator.Mov(eax, 127);
			translator.Mov(eax, 128);
			translator.Mov(eax, 129);
			translator.Mov(eax, 130);
			translator.Mov(eax, 10000);
			translator.Mov(eax, 0x12345678);

			translator.Mov(eax, -1);
			translator.Mov(eax, -20);
			translator.Mov(eax, -100);
			translator.Mov(eax, -127);
			translator.Mov(eax, -128);
			translator.Mov(eax, -129);
			translator.Mov(eax, -130);
			translator.Mov(eax, -10000);
			translator.Mov(eax, -0x12345678);

			// Проверка результата.
			CheckCodeEquality(translator, original);
		}

		// --------------------------------------------------------------------------
		TEST_METHOD(Test_MOV_REGpC_REG)	// [REG + Const], REG
		{
			byte* original;
			__asm {
				call l_original		// Адрес следующей инструкции заносим в стек.
				l_original:
				jmp l_exit			// Пропускаем "правильный" код. Сам jmp тут имеет размер 5 байта, т.к. "эталонный" код ниже в 2 не укладывается.
			// Правильный вариант трансляции
				mov[esi + 1], eax
				mov[ebx + 10], ebx
				mov[ebx + 127], ebx
				mov[ebx + 128], ebx
				mov[ebx + 129], ebx
				mov[ebx + 130], ebx
				mov[eax + 1000], ecx
				mov[ecx + 0x12345678], edi

				mov[esi - 1], eax
				mov[ebx - 10], ebx
				mov[ebx - 127], ebx
				mov[ebx - 128], ebx
				mov[ebx - 129], ebx
				mov[ebx - 130], ebx
				mov[eax - 1000], ecx
				mov[ecx - 0x12345678], edi

				// С esp - отдельные причуды.
				mov[esp + 127], edi
				mov[esp + 128], edi
				mov[esp + 129], edi
				mov[esp + 130], edi
				mov[esp - 127], edi
				mov[esp - 128], edi
				mov[esp - 129], edi
				mov[esp - 130], edi

				mov[eax - 0xEFEFEF], edi
				mov[ecx - 0xEFEFEF], edi
				mov[edx - 0xEFEFEF], edi
				mov[ebx - 0xEFEFEF], edi
				mov[esp - 0xEFEFEF], edi
				mov[ebp - 0xEFEFEF], edi
				mov[esi - 0xEFEFEF], edi
				mov[edi - 0xEFEFEF], edi

				mov[eax - 0x12345678], edi
				mov[ecx - 0x12345678], edi
				mov[edx - 0x12345678], edi
				mov[ebx - 0x12345678], edi
				mov[esp - 0x12345678], edi
				mov[ebp - 0x12345678], edi
				mov[esi - 0x12345678], edi
				mov[edi - 0x12345678], edi

				mov[eax + 0xFEFEFEF9], ebp
				mov[ecx + 0xFEFEFEF9], ebp
				mov[edx + 0xFEFEFEF9], esi
				mov[ebx + 0xFEFEFEF9], esi
				mov[esp + 0xFEFEFEF9], esi
				mov[ebp + 0xFEFEFEF9], edi
				mov[esi + 0xFEFEFEF9], esp
				mov[edi + 0xFEFEFEF9], esp

			// Конец правильного варианта трансляции
				int 03h				// Пометка конца правильного кода, её достижение проверяется
				l_exit:
				pop original			// original = адрес jmp + 5 = адрес правильного варианта кода
			}
			original += 5;

			// Тестируемый код.
			AsmTranslator translator;

			translator.Mov(I[esi + 1], eax);
			translator.Mov(I[ebx +10], ebx);
			translator.Mov(I[ebx + 127], ebx);
			translator.Mov(I[ebx + 128], ebx);
			translator.Mov(I[ebx + 129], ebx);
			translator.Mov(I[ebx + 130], ebx);
			translator.Mov(I[eax + 1000], ecx);
			translator.Mov(I[ecx + 0x12345678], edi);

			translator.Mov(I[esi - 1], eax);
			translator.Mov(I[ebx - 10], ebx);
			translator.Mov(I[ebx - 127], ebx);
			translator.Mov(I[ebx - 128], ebx);
			translator.Mov(I[ebx - 129], ebx);
			translator.Mov(I[ebx - 130], ebx);
			translator.Mov(I[eax - 1000], ecx);
			translator.Mov(I[ecx - 0x12345678], edi);

			translator.Mov(I[esp + 127], edi);
			translator.Mov(I[esp + 128], edi);
			translator.Mov(I[esp + 129], edi);
			translator.Mov(I[esp + 130], edi);
			translator.Mov(I[esp - 127], edi);
			translator.Mov(I[esp - 128], edi);
			translator.Mov(I[esp - 129], edi);
			translator.Mov(I[esp - 130], edi);
   
			translator.Mov(I[eax - 0xEFEFEF], edi);
			translator.Mov(I[ecx - 0xEFEFEF], edi);
			translator.Mov(I[edx - 0xEFEFEF], edi);
			translator.Mov(I[ebx - 0xEFEFEF], edi);
			translator.Mov(I[esp - 0xEFEFEF], edi);
			translator.Mov(I[ebp - 0xEFEFEF], edi);
			translator.Mov(I[esi - 0xEFEFEF], edi);
			translator.Mov(I[edi - 0xEFEFEF], edi);

			translator.Mov(I[eax - 0x12345678], edi);
			translator.Mov(I[ecx - 0x12345678], edi);
			translator.Mov(I[edx - 0x12345678], edi);
			translator.Mov(I[ebx - 0x12345678], edi);
			translator.Mov(I[esp - 0x12345678], edi);
			translator.Mov(I[ebp - 0x12345678], edi);
			translator.Mov(I[esi - 0x12345678], edi);
			translator.Mov(I[edi - 0x12345678], edi);

			translator.Mov(I[eax + 0xFEFEFEF9], ebp);
			translator.Mov(I[ecx + 0xFEFEFEF9], ebp);
			translator.Mov(I[edx + 0xFEFEFEF9], esi);
			translator.Mov(I[ebx + 0xFEFEFEF9], esi);
			translator.Mov(I[esp + 0xFEFEFEF9], esi);
			translator.Mov(I[ebp + 0xFEFEFEF9], edi);
			translator.Mov(I[esi + 0xFEFEFEF9], esp);
			translator.Mov(I[edi + 0xFEFEFEF9], esp);

			// Проверка результата.
			CheckCodeEquality(translator, original);
		}

		// --------------------------------------------------------------------------
		TEST_METHOD(Test_MOV_REG_REGpC)	// REG, [REG + Const]
		{
			byte* original;
			__asm {
				call l_original		// Адрес следующей инструкции заносим в стек.
				l_original:
				jmp l_exit			// Пропускаем "правильный" код. Сам jmp тут имеет размер 5 байта, т.к. "эталонный" код ниже в 2 не укладывается.
			// Правильный вариант трансляции
				mov eax, [esi + 1]
				mov ebx, [ebx + 10]
				mov ebx, [ebx + 127]
				mov ebx, [ebx + 128]
				mov ebx, [ebx + 129]
				mov ebx, [ebx + 130]
				mov ecx, [eax + 1000]
				mov edi, [ecx + 0x12345678]

				mov eax, [esi - 1]
				mov ebx, [ebx - 10]
				mov ebx, [ebx - 127]
				mov ebx, [ebx - 128]
				mov ebx, [ebx - 129]
				mov ebx, [ebx - 130]
				mov ecx, [eax - 1000]
				mov edi, [ecx - 0x12345678]

				mov edi, [esp + 127]
				mov edi, [esp + 128]
				mov edi, [esp + 129]
				mov edi, [esp + 130]
				mov edi, [esp - 127]
				mov edi, [esp - 128]
				mov edi, [esp - 129]
				mov edi, [esp - 130]

				mov edi, [eax - 0xEFEFEF]
				mov edi, [ecx - 0xEFEFEF]
				mov edi, [edx - 0xEFEFEF]
				mov edi, [ebx - 0xEFEFEF]
				mov edi, [esp - 0xEFEFEF]
				mov edi, [ebp - 0xEFEFEF]
				mov edi, [esi - 0xEFEFEF]
				mov edi, [edi - 0xEFEFEF]

				mov edi, [eax - 0x12345678]
				mov edi, [ecx - 0x12345678]
				mov edi, [edx - 0x12345678]
				mov edi, [ebx - 0x12345678]
				mov edi, [esp - 0x12345678]
				mov edi, [ebp - 0x12345678]
				mov edi, [esi - 0x12345678]
				mov edi, [edi - 0x12345678]

				mov ebp, [eax + 0xFEFEFEF9]
				mov ebp, [ecx + 0xFEFEFEF9]
				mov esi, [edx + 0xFEFEFEF9]
				mov esi, [ebx + 0xFEFEFEF9]
				mov esi, [esp + 0xFEFEFEF9]
				mov edi, [ebp + 0xFEFEFEF9]
				mov esp, [esi + 0xFEFEFEF9]
				mov esp, [edi + 0xFEFEFEF9]

			// Конец правильного варианта трансляции
				int 03h				// Пометка конца правильного кода, её достижение проверяется
				l_exit:
				pop original			// original = адрес jmp + 5 = адрес правильного варианта кода
			}
			original += 5;

			// Тестируемый код.
			AsmTranslator translator;

			translator.Mov(eax, I[esi + 1]);
			translator.Mov(ebx, I[ebx + 10]);
			translator.Mov(ebx, I[ebx + 127]);
			translator.Mov(ebx, I[ebx + 128]);
			translator.Mov(ebx, I[ebx + 129]);
			translator.Mov(ebx, I[ebx + 130]);
			translator.Mov(ecx, I[eax + 1000]);
			translator.Mov(edi, I[ecx + 0x12345678]);

			translator.Mov(eax, I[esi - 1]);
			translator.Mov(ebx, I[ebx - 10]);
			translator.Mov(ebx, I[ebx - 127]);
			translator.Mov(ebx, I[ebx - 128]);
			translator.Mov(ebx, I[ebx - 129]);
			translator.Mov(ebx, I[ebx - 130]);
			translator.Mov(ecx, I[eax - 1000]);
			translator.Mov(edi, I[ecx - 0x12345678]);
			
			translator.Mov(edi, I[esp + 127]);
			translator.Mov(edi, I[esp + 128]);
			translator.Mov(edi, I[esp + 129]);
			translator.Mov(edi, I[esp + 130]);
			translator.Mov(edi, I[esp - 127]);
			translator.Mov(edi, I[esp - 128]);
			translator.Mov(edi, I[esp - 129]);
			translator.Mov(edi, I[esp - 130]);

			translator.Mov(edi, I[eax - 0xEFEFEF]);
			translator.Mov(edi, I[ecx - 0xEFEFEF]);
			translator.Mov(edi, I[edx - 0xEFEFEF]);
			translator.Mov(edi, I[ebx - 0xEFEFEF]);
			translator.Mov(edi, I[esp - 0xEFEFEF]);
			translator.Mov(edi, I[ebp - 0xEFEFEF]);
			translator.Mov(edi, I[esi - 0xEFEFEF]);
			translator.Mov(edi, I[edi - 0xEFEFEF]);

			translator.Mov(edi, I[eax - 0x12345678]);
			translator.Mov(edi, I[ecx - 0x12345678]);
			translator.Mov(edi, I[edx - 0x12345678]);
			translator.Mov(edi, I[ebx - 0x12345678]);
			translator.Mov(edi, I[esp - 0x12345678]);
			translator.Mov(edi, I[ebp - 0x12345678]);
			translator.Mov(edi, I[esi - 0x12345678]);
			translator.Mov(edi, I[edi - 0x12345678]);

			translator.Mov(ebp, I[eax + 0xFEFEFEF9]);
			translator.Mov(ebp, I[ecx + 0xFEFEFEF9]);
			translator.Mov(esi, I[edx + 0xFEFEFEF9]);
			translator.Mov(esi, I[ebx + 0xFEFEFEF9]);
			translator.Mov(esi, I[esp + 0xFEFEFEF9]);
			translator.Mov(edi, I[ebp + 0xFEFEFEF9]);
			translator.Mov(esp, I[esi + 0xFEFEFEF9]);
			translator.Mov(esp, I[edi + 0xFEFEFEF9]);

			// Проверка результата.
			CheckCodeEquality(translator, original);
		}

		// --------------------------------------------------------------------------
		TEST_METHOD(Test_MOV_REGp_REG)	// [REG], REG
		{
			byte* original;
			__asm {
				call l_original		// Адрес следующей инструкции заносим в стек.
				l_original :
				jmp l_exit			// Пропускаем "правильный" код. Сам jmp тут имеет размер 5 байта, т.к. "эталонный" код ниже в 2 не укладывается.
									// Правильный вариант трансляции

				mov [eax], eax
				mov [ecx], eax
				mov [edx], eax
				mov [ebx], eax
				mov [esp], eax
				mov [ebp], eax
				mov [esi], eax
				mov [edi], eax
				    
				mov [eax], ecx
				mov [ecx], ecx
				mov [edx], ecx
				mov [ebx], ecx
				mov [esp], ecx
				mov [ebp], ecx
				mov [esi], ecx
				mov [edi], ecx
				    
				mov [eax], edx
				mov [ecx], edx
				mov [edx], edx
				mov [ebx], edx
				mov [esp], edx
				mov [ebp], edx
				mov [esi], edx
				mov [edi], edx
				    
				mov [eax], ebx
				mov [ecx], ebx
				mov [edx], ebx
				mov [ebx], ebx
				mov [esp], ebx
				mov [ebp], ebx
				mov [esi], ebx
				mov [edi], ebx
				    
				mov [eax], esi
				mov [ecx], esi
				mov [edx], esi
				mov [ebx], esi
				mov [esp], esi
				mov [ebp], esi
				mov [esi], esi
				mov [edi], esi
				    
				mov [eax], edi
				mov [ecx], edi
				mov [edx], edi
				mov [ebx], edi
				mov [esp], edi
				mov [ebp], edi
				mov [esi], edi
				mov [edi], edi
				    
				mov [eax], esp
				mov [ecx], esp
				mov [edx], esp
				mov [ebx], esp
				mov [esp], esp
				mov [ebp], esp
				mov [esi], esp
				mov [edi], esp
				    
				mov [eax], ebp
				mov [ecx], ebp
				mov [edx], ebp
				mov [ebx], ebp
				mov [esp], ebp
				mov [ebp], ebp
				mov [esi], ebp
				mov [edi], ebp

				// Конец правильного варианта трансляции
				int 03h				// Пометка конца правильного кода, её достижение проверяется
				l_exit :
				pop original			// original = адрес jmp + 5 = адрес правильного варианта кода
			}
			original += 5;

			// Тестируемый код.
			AsmTranslator translator;

			translator.Mov(I[eax], eax);
			translator.Mov(I[ecx], eax);
			translator.Mov(I[edx], eax);
			translator.Mov(I[ebx], eax);
			translator.Mov(I[esp], eax);
			translator.Mov(I[ebp], eax);
			translator.Mov(I[esi], eax);
			translator.Mov(I[edi], eax);

			translator.Mov(I[eax], ecx);
			translator.Mov(I[ecx], ecx);
			translator.Mov(I[edx], ecx);
			translator.Mov(I[ebx], ecx);
			translator.Mov(I[esp], ecx);
			translator.Mov(I[ebp], ecx);
			translator.Mov(I[esi], ecx);
			translator.Mov(I[edi], ecx);

			translator.Mov(I[eax], edx);
			translator.Mov(I[ecx], edx);
			translator.Mov(I[edx], edx);
			translator.Mov(I[ebx], edx);
			translator.Mov(I[esp], edx);
			translator.Mov(I[ebp], edx);
			translator.Mov(I[esi], edx);
			translator.Mov(I[edi], edx);

			translator.Mov(I[eax], ebx);
			translator.Mov(I[ecx], ebx);
			translator.Mov(I[edx], ebx);
			translator.Mov(I[ebx], ebx);
			translator.Mov(I[esp], ebx);
			translator.Mov(I[ebp], ebx);
			translator.Mov(I[esi], ebx);
			translator.Mov(I[edi], ebx);

			translator.Mov(I[eax], esi);
			translator.Mov(I[ecx], esi);
			translator.Mov(I[edx], esi);
			translator.Mov(I[ebx], esi);
			translator.Mov(I[esp], esi);
			translator.Mov(I[ebp], esi);
			translator.Mov(I[esi], esi);
			translator.Mov(I[edi], esi);

			translator.Mov(I[eax], edi);
			translator.Mov(I[ecx], edi);
			translator.Mov(I[edx], edi);
			translator.Mov(I[ebx], edi);
			translator.Mov(I[esp], edi);
			translator.Mov(I[ebp], edi);
			translator.Mov(I[esi], edi);
			translator.Mov(I[edi], edi);

			translator.Mov(I[eax], esp);
			translator.Mov(I[ecx], esp);
			translator.Mov(I[edx], esp);
			translator.Mov(I[ebx], esp);
			translator.Mov(I[esp], esp);
			translator.Mov(I[ebp], esp);
			translator.Mov(I[esi], esp);
			translator.Mov(I[edi], esp);

			translator.Mov(I[eax], ebp);
			translator.Mov(I[ecx], ebp);
			translator.Mov(I[edx], ebp);
			translator.Mov(I[ebx], ebp);
			translator.Mov(I[esp], ebp);
			translator.Mov(I[ebp], ebp);
			translator.Mov(I[esi], ebp);
			translator.Mov(I[edi], ebp);

			// Проверка результата.
			CheckCodeEquality(translator, original);
		}

		// --------------------------------------------------------------------------
		TEST_METHOD(Test_MOV_REG_REGp)	// REG, [REG]
		{
			byte* original;
			__asm {
				call l_original		// Адрес следующей инструкции заносим в стек.
				l_original :
				jmp l_exit			// Пропускаем "правильный" код. Сам jmp тут имеет размер 5 байта, т.к. "эталонный" код ниже в 2 не укладывается.
									// Правильный вариант трансляции

					mov eax, [eax]
					mov eax, [ecx]
					mov eax, [edx]
					mov eax, [ebx]
					mov eax, [esp]
					mov eax, [ebp]
					mov eax, [esi]
					mov eax, [edi]

					mov ecx, [eax]
					mov ecx, [ecx]
					mov ecx, [edx]
					mov ecx, [ebx]
					mov ecx, [esp]
					mov ecx, [ebp]
					mov ecx, [esi]
					mov ecx, [edi]

					mov edx, [eax]
					mov edx, [ecx]
					mov edx, [edx]
					mov edx, [ebx]
					mov edx, [esp]
					mov edx, [ebp]
					mov edx, [esi]
					mov edx, [edi]

					mov ebx, [eax]
					mov ebx, [ecx]
					mov ebx, [edx]
					mov ebx, [ebx]
					mov ebx, [esp]
					mov ebx, [ebp]
					mov ebx, [esi]
					mov ebx, [edi]

					mov esi, [eax]
					mov esi, [ecx]
					mov esi, [edx]
					mov esi, [ebx]
					mov esi, [esp]
					mov esi, [ebp]
					mov esi, [esi]
					mov esi, [edi]

					mov edi, [eax]
					mov edi, [ecx]
					mov edi, [edx]
					mov edi, [ebx]
					mov edi, [esp]
					mov edi, [ebp]
					mov edi, [esi]
					mov edi, [edi]

					mov esp, [eax]
					mov esp, [ecx]
					mov esp, [edx]
					mov esp, [ebx]
					mov esp, [esp]
					mov esp, [ebp]
					mov esp, [esi]
					mov esp, [edi]

					mov ebp, [eax]
					mov ebp, [ecx]
					mov ebp, [edx]
					mov ebp, [ebx]
					mov ebp, [esp]
					mov ebp, [ebp]
					mov ebp, [esi]
					mov ebp, [edi]

					// Конец правильного варианта трансляции
					int 03h				// Пометка конца правильного кода, её достижение проверяется
					l_exit :
				pop original			// original = адрес jmp + 5 = адрес правильного варианта кода
			}
			original += 5;

			// Тестируемый код.
			AsmTranslator translator;

			translator.Mov(eax, I[eax]);
			translator.Mov(eax, I[ecx]);
			translator.Mov(eax, I[edx]);
			translator.Mov(eax, I[ebx]);
			translator.Mov(eax, I[esp]);
			translator.Mov(eax, I[ebp]);
			translator.Mov(eax, I[esi]);
			translator.Mov(eax, I[edi]);

			translator.Mov(ecx, I[eax]);
			translator.Mov(ecx, I[ecx]);
			translator.Mov(ecx, I[edx]);
			translator.Mov(ecx, I[ebx]);
			translator.Mov(ecx, I[esp]);
			translator.Mov(ecx, I[ebp]);
			translator.Mov(ecx, I[esi]);
			translator.Mov(ecx, I[edi]);

			translator.Mov(edx, I[eax]);
			translator.Mov(edx, I[ecx]);
			translator.Mov(edx, I[edx]);
			translator.Mov(edx, I[ebx]);
			translator.Mov(edx, I[esp]);
			translator.Mov(edx, I[ebp]);
			translator.Mov(edx, I[esi]);
			translator.Mov(edx, I[edi]);
			
			translator.Mov(ebx, I[eax]);
			translator.Mov(ebx, I[ecx]);
			translator.Mov(ebx, I[edx]);
			translator.Mov(ebx, I[ebx]);
			translator.Mov(ebx, I[esp]);
			translator.Mov(ebx, I[ebp]);
			translator.Mov(ebx, I[esi]);
			translator.Mov(ebx, I[edi]);
			
			translator.Mov(esi, I[eax]);
			translator.Mov(esi, I[ecx]);
			translator.Mov(esi, I[edx]);
			translator.Mov(esi, I[ebx]);
			translator.Mov(esi, I[esp]);
			translator.Mov(esi, I[ebp]);
			translator.Mov(esi, I[esi]);
			translator.Mov(esi, I[edi]);
			
			translator.Mov(edi, I[eax]);
			translator.Mov(edi, I[ecx]);
			translator.Mov(edi, I[edx]);
			translator.Mov(edi, I[ebx]);
			translator.Mov(edi, I[esp]);
			translator.Mov(edi, I[ebp]);
			translator.Mov(edi, I[esi]);
			translator.Mov(edi, I[edi]);
			
			translator.Mov(esp, I[eax]);
			translator.Mov(esp, I[ecx]);
			translator.Mov(esp, I[edx]);
			translator.Mov(esp, I[ebx]);
			translator.Mov(esp, I[esp]);
			translator.Mov(esp, I[ebp]);
			translator.Mov(esp, I[esi]);
			translator.Mov(esp, I[edi]);
			
			translator.Mov(ebp, I[eax]);
			translator.Mov(ebp, I[ecx]);
			translator.Mov(ebp, I[edx]);
			translator.Mov(ebp, I[ebx]);
			translator.Mov(ebp, I[esp]);
			translator.Mov(ebp, I[ebp]);
			translator.Mov(ebp, I[esi]);
			translator.Mov(ebp, I[edi]);

			// Проверка результата.
			CheckCodeEquality(translator, original);
		}

		// --------------------------------------------------------------------------
		TEST_METHOD(Test_MOV_REGp_C)	// [REG], 123
		{
			byte* original;
			__asm {
				call l_original		// Адрес следующей инструкции заносим в стек.
				l_original :
				jmp l_exit			// Пропускаем "правильный" код. Сам jmp тут имеет размер 5 байта, т.к. "эталонный" код ниже в 2 не укладывается.
				// Правильный вариант трансляции
				mov dword ptr[eax], 222
				mov dword ptr[ecx], 222
				mov dword ptr[edx], 222
				mov dword ptr[ebx], 222
				mov dword ptr[esp], 222
				mov dword ptr[ebp], 222
				mov dword ptr[esi], 222
				mov dword ptr[edi], 222

				mov dword ptr[eax], 0x12345678
				mov dword ptr[ecx], 0x12345678
				mov dword ptr[edx], 0x12345678
				mov dword ptr[ebx], 0x12345678
				mov dword ptr[esp], 0x12345678
				mov dword ptr[ebp], 0x12345678
				mov dword ptr[esi], 0x12345678
				mov dword ptr[edi], 0x12345678

				mov dword ptr[eax], -200000
				mov dword ptr[ecx], -200000
				mov dword ptr[edx], -200000
				mov dword ptr[ebx], -200000
				mov dword ptr[esp], -200000
				mov dword ptr[ebp], -200000
				mov dword ptr[esi], -200000
				mov dword ptr[edi], -200000
				// Конец правильного варианта трансляции
				int 03h				// Пометка конца правильного кода, её достижение проверяется
				l_exit :
				pop original			// original = адрес jmp + 5 = адрес правильного варианта кода
			}
			original += 5;

			// Тестируемый код.
			AsmTranslator translator;

			translator.Mov(I[eax], 222);
			translator.Mov(I[ecx], 222);
			translator.Mov(I[edx], 222);
			translator.Mov(I[ebx], 222);
			translator.Mov(I[esp], 222);
			translator.Mov(I[ebp], 222);
			translator.Mov(I[esi], 222);
			translator.Mov(I[edi], 222);

			translator.Mov(I[eax], 0x12345678);
			translator.Mov(I[ecx], 0x12345678);
			translator.Mov(I[edx], 0x12345678);
			translator.Mov(I[ebx], 0x12345678);
			translator.Mov(I[esp], 0x12345678);
			translator.Mov(I[ebp], 0x12345678);
			translator.Mov(I[esi], 0x12345678);
			translator.Mov(I[edi], 0x12345678);

			translator.Mov(I[eax], -200000);
			translator.Mov(I[ecx], -200000);
			translator.Mov(I[edx], -200000);
			translator.Mov(I[ebx], -200000);
			translator.Mov(I[esp], -200000);
			translator.Mov(I[ebp], -200000);
			translator.Mov(I[esi], -200000);
			translator.Mov(I[edi], -200000);

			// Проверка результата.
			CheckCodeEquality(translator, original);
		}

		// --------------------------------------------------------------------------
		TEST_METHOD(Test_MOV_REGpC_C)	// [REG + 123], 456
		{
			byte* original;
			__asm {
				call l_original		// Адрес следующей инструкции заносим в стек.
				l_original :
				jmp l_exit			// Пропускаем "правильный" код. Сам jmp тут имеет размер 5 байта, т.к. "эталонный" код ниже в 2 не укладывается.
				// Правильный вариант трансляции
				mov dword ptr[eax + 123], 222
				mov dword ptr[ecx + 123], 222
				mov dword ptr[edx + 123], 222
				mov dword ptr[ebx + 123], 222
				mov dword ptr[esp + 123], 222
				mov dword ptr[ebp + 123], 222
				mov dword ptr[esi + 123], 222
				mov dword ptr[edi + 123], 222

				mov dword ptr[eax + 123], 0x12345678
				mov dword ptr[ecx + 123], 0x12345678
				mov dword ptr[edx + 123], 0x12345678
				mov dword ptr[ebx + 123], 0x12345678
				mov dword ptr[esp + 123], 0x12345678
				mov dword ptr[ebp + 123], 0x12345678
				mov dword ptr[esi + 123], 0x12345678
				mov dword ptr[edi + 123], 0x12345678

				mov dword ptr[eax + 0x12345678], 222
				mov dword ptr[ecx + 0x12345678], 222
				mov dword ptr[edx + 0x12345678], 222
				mov dword ptr[ebx + 0x12345678], 222
				mov dword ptr[esp + 0x12345678], 222
				mov dword ptr[ebp + 0x12345678], 222
				mov dword ptr[esi + 0x12345678], 222
				mov dword ptr[edi + 0x12345678], 222

				mov dword ptr[eax + 0x12345678], 0xABCDEF09
				mov dword ptr[ecx + 0x12345678], 0xABCDEF09
				mov dword ptr[edx + 0x12345678], 0xABCDEF09
				mov dword ptr[ebx + 0x12345678], 0xABCDEF09
				mov dword ptr[esp + 0x12345678], 0xABCDEF09
				mov dword ptr[ebp + 0x12345678], 0xABCDEF09
				mov dword ptr[esi + 0x12345678], 0xABCDEF09
				mov dword ptr[edi + 0x12345678], 0xABCDEF09

				mov dword ptr[eax - 123], 222
				mov dword ptr[ecx - 123], 222
				mov dword ptr[edx - 123], 222
				mov dword ptr[ebx - 123], 222
				mov dword ptr[esp - 123], 222
				mov dword ptr[ebp - 123], 222
				mov dword ptr[esi - 123], 222
				mov dword ptr[edi - 123], 222

				mov dword ptr[eax - 123], 0x12345678
				mov dword ptr[ecx - 123], 0x12345678
				mov dword ptr[edx - 123], 0x12345678
				mov dword ptr[ebx - 123], 0x12345678
				mov dword ptr[esp - 123], 0x12345678
				mov dword ptr[ebp - 123], 0x12345678
				mov dword ptr[esi - 123], 0x12345678
				mov dword ptr[edi - 123], 0x12345678

				mov dword ptr[eax - 0x12345678], 222
				mov dword ptr[ecx - 0x12345678], 222
				mov dword ptr[edx - 0x12345678], 222
				mov dword ptr[ebx - 0x12345678], 222
				mov dword ptr[esp - 0x12345678], 222
				mov dword ptr[ebp - 0x12345678], 222
				mov dword ptr[esi - 0x12345678], 222
				mov dword ptr[edi - 0x12345678], 222

				mov dword ptr[eax - 0x12345678], 0xABCDEF09
				mov dword ptr[ecx - 0x12345678], 0xABCDEF09
				mov dword ptr[edx - 0x12345678], 0xABCDEF09
				mov dword ptr[ebx - 0x12345678], 0xABCDEF09
				mov dword ptr[esp - 0x12345678], 0xABCDEF09
				mov dword ptr[ebp - 0x12345678], 0xABCDEF09
				mov dword ptr[esi - 0x12345678], 0xABCDEF09
				mov dword ptr[edi - 0x12345678], 0xABCDEF09

				mov dword ptr[eax - 0x12345678], -200000
				mov dword ptr[ecx - 0x12345678], -200000
				mov dword ptr[edx - 0x12345678], -200000
				mov dword ptr[ebx - 0x12345678], -200000
				mov dword ptr[esp - 0x12345678], -200000
				mov dword ptr[ebp - 0x12345678], -200000
				mov dword ptr[esi - 0x12345678], -200000
				mov dword ptr[edi - 0x12345678], -200000

				// Конец правильного варианта трансляции
				int 03h				// Пометка конца правильного кода, её достижение проверяется
				l_exit :
				pop original			// original = адрес jmp + 5 = адрес правильного варианта кода
			}
			original += 5;

			// Тестируемый код.
			AsmTranslator translator;

			translator.Mov(I[eax + 123], 222);
			translator.Mov(I[ecx + 123], 222);
			translator.Mov(I[edx + 123], 222);
			translator.Mov(I[ebx + 123], 222);
			translator.Mov(I[esp + 123], 222);
			translator.Mov(I[ebp + 123], 222);
			translator.Mov(I[esi + 123], 222);
			translator.Mov(I[edi + 123], 222);
			
			translator.Mov(I[eax + 123], 0x12345678);
			translator.Mov(I[ecx + 123], 0x12345678);
			translator.Mov(I[edx + 123], 0x12345678);
			translator.Mov(I[ebx + 123], 0x12345678);
			translator.Mov(I[esp + 123], 0x12345678);
			translator.Mov(I[ebp + 123], 0x12345678);
			translator.Mov(I[esi + 123], 0x12345678);
			translator.Mov(I[edi + 123], 0x12345678);
			
			translator.Mov(I[eax + 0x12345678], 222);
			translator.Mov(I[ecx + 0x12345678], 222);
			translator.Mov(I[edx + 0x12345678], 222);
			translator.Mov(I[ebx + 0x12345678], 222);
			translator.Mov(I[esp + 0x12345678], 222);
			translator.Mov(I[ebp + 0x12345678], 222);
			translator.Mov(I[esi + 0x12345678], 222);
			translator.Mov(I[edi + 0x12345678], 222);
			
			translator.Mov(I[eax + 0x12345678], 0xABCDEF09);
			translator.Mov(I[ecx + 0x12345678], 0xABCDEF09);
			translator.Mov(I[edx + 0x12345678], 0xABCDEF09);
			translator.Mov(I[ebx + 0x12345678], 0xABCDEF09);
			translator.Mov(I[esp + 0x12345678], 0xABCDEF09);
			translator.Mov(I[ebp + 0x12345678], 0xABCDEF09);
			translator.Mov(I[esi + 0x12345678], 0xABCDEF09);
			translator.Mov(I[edi + 0x12345678], 0xABCDEF09);
			
			translator.Mov(I[eax - 123], 222);
			translator.Mov(I[ecx - 123], 222);
			translator.Mov(I[edx - 123], 222);
			translator.Mov(I[ebx - 123], 222);
			translator.Mov(I[esp - 123], 222);
			translator.Mov(I[ebp - 123], 222);
			translator.Mov(I[esi - 123], 222);
			translator.Mov(I[edi - 123], 222);
			
			translator.Mov(I[eax - 123], 0x12345678);
			translator.Mov(I[ecx - 123], 0x12345678);
			translator.Mov(I[edx - 123], 0x12345678);
			translator.Mov(I[ebx - 123], 0x12345678);
			translator.Mov(I[esp - 123], 0x12345678);
			translator.Mov(I[ebp - 123], 0x12345678);
			translator.Mov(I[esi - 123], 0x12345678);
			translator.Mov(I[edi - 123], 0x12345678);
			
			translator.Mov(I[eax - 0x12345678], 222);
			translator.Mov(I[ecx - 0x12345678], 222);
			translator.Mov(I[edx - 0x12345678], 222);
			translator.Mov(I[ebx - 0x12345678], 222);
			translator.Mov(I[esp - 0x12345678], 222);
			translator.Mov(I[ebp - 0x12345678], 222);
			translator.Mov(I[esi - 0x12345678], 222);
			translator.Mov(I[edi - 0x12345678], 222);
			
			translator.Mov(I[eax - 0x12345678], 0xABCDEF09);
			translator.Mov(I[ecx - 0x12345678], 0xABCDEF09);
			translator.Mov(I[edx - 0x12345678], 0xABCDEF09);
			translator.Mov(I[ebx - 0x12345678], 0xABCDEF09);
			translator.Mov(I[esp - 0x12345678], 0xABCDEF09);
			translator.Mov(I[ebp - 0x12345678], 0xABCDEF09);
			translator.Mov(I[esi - 0x12345678], 0xABCDEF09);
			translator.Mov(I[edi - 0x12345678], 0xABCDEF09);

			translator.Mov(I[eax - 0x12345678], -200000);
			translator.Mov(I[ecx - 0x12345678], -200000);
			translator.Mov(I[edx - 0x12345678], -200000);
			translator.Mov(I[ebx - 0x12345678], -200000);
			translator.Mov(I[esp - 0x12345678], -200000);
			translator.Mov(I[ebp - 0x12345678], -200000);
			translator.Mov(I[esi - 0x12345678], -200000);
			translator.Mov(I[edi - 0x12345678], -200000);

			// Проверка результата.
			CheckCodeEquality(translator, original);
		}

		// --------------------------------------------------------------------------
	};
}

#pragma warning (pop)