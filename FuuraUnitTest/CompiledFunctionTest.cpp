#include "stdafx.h"
#include "CppUnitTest.h"
#include "CppUnitTestAssert.h"

// Тестируем этот класс.
#include <CompiledFunction.h>
#include <AsmTranslator.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace fuura::compilation
{
	const auto eax = RegisterInt32::EAX;
	const auto ebx = RegisterInt32::EBX;
	const auto esp = RegisterInt32::ESP;

	TEST_CLASS(CompiledFunctionTest)
	{
	public:
		// --------------------------------------------------------------------------
		TEST_METHOD(Test_ExecuteVoidFunctionWithoutParams)
		{
			AsmTranslator translator;
			translator.Ret();
			auto func = translator.GetFunction<void()>();

			func(); // Никаких исключений и ошибок
		}

		// --------------------------------------------------------------------------
		TEST_METHOD(Test_ExecuteFunctionWithoutParams)
		{
			AsmTranslator translator;
			translator.Mov(eax, 123);	// mov eax, 123
			translator.Ret();			// ret
			auto func = translator.GetFunction<int()>();

			Assert::AreEqual(123, func());
		}

		// --------------------------------------------------------------------------
		TEST_METHOD(Test_ExecuteFunctionWith1Param)
		{
			AsmTranslator translator;
			translator.Mov(eax, I[esp + 4]);	// mov eax, [esp + 4] // Передаваемый параметр
			translator.Inc(eax);				// inc eax
			translator.Ret();					// ret
			auto func = translator.GetFunction<int(int)>();

			Assert::AreEqual(123 + 1, func(123));
		}

		// --------------------------------------------------------------------------
		/*
		TEST_METHOD(Test_ExecuteFunctionWith2Params)
		{
			Compiler translator;
			translator.Mov(eax, I[esp + 4]);	// mov eax, [esp + 4] // Первый параметр
			translator.Add(eax, I[esp + 8]);	// add eax, [esp + 8] // Второй параметр // TODO: компиляция "add" пока не реализована
			translator.Dec(eax);				// dec eax
			translator.Ret();					// ret
			auto func = translator.GetFunction<int(int, int)>();

			Assert::AreEqual(123 + 456 - 1, func(123, 456));
		}*/

		// --------------------------------------------------------------------------
	};
}