#include "stdafx.h"
#include "CppUnitTest.h"
#include "CppUnitTestAssert.h"
#include <Translator.h>

// Тестируем этот класс.
#include <JITCompiler.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace fuura::compilation
{
	TEST_CLASS(JITCompilerTest)
	{
	public:
		// --------------------------------------------------------------------------
		TEST_METHOD(Test_JITCompiler)	// Пока ничего реально не компилируется
		{
			fuura::Translator translator;
			auto source = "134 + 166 - 3"; // "x + 14 * (x + 1) + 2 * y"; // TODO: усложнить функцию
			auto func = translator.MakeFunction<int(int, int)>({ "x", "y" }, source);

			JITCompiler compiler;
			compiler.Compile(func);	//, traceOut);
			//throw "TODO: trace out";
			// TODO: проверить корректность работы функции
		}

		// --------------------------------------------------------------------------
	};
}