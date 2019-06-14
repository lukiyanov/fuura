#include "stdafx.h"
#include "CppUnitTest.h"
#include "CppUnitTestAssert.h"
#include <Translator.h>

// ��������� ���� �����.
#include <JITCompiler.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace fuura::compilation
{
	TEST_CLASS(JITCompilerTest)
	{
	public:
		// --------------------------------------------------------------------------
		TEST_METHOD(Test_JITCompiler)	// ���� ������ ������� �� �������������
		{
			fuura::Translator translator;
			auto source = "134 + 166 - 3"; // "x + 14 * (x + 1) + 2 * y"; // TODO: ��������� �������
			auto func = translator.MakeFunction<int(int, int)>({ "x", "y" }, source);

			JITCompiler compiler;
			compiler.Compile(func);	//, traceOut);
			//throw "TODO: trace out";
			// TODO: ��������� ������������ ������ �������
		}

		// --------------------------------------------------------------------------
	};
}