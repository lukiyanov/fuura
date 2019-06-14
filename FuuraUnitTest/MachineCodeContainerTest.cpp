#include "stdafx.h"
#include "CppUnitTest.h"
#include "CppUnitTestAssert.h"

// “естируем этот класс.
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

			// —разу после создани€ контейнер пуст.
			Assert::AreEqual(size_t(0), codeContainer.GetCodeSize());

			// ќператор << добавл€ет данные в конец контейнера.
			// ¬ контейнер можно положить одно- и много- байтовые значни€.
			// «начени€ со знаком и без хран€тс€ одинаково.
			const char testChars[] = { '\x01', '\x02', '\x03' };
			codeContainer << testChars[0] << testChars[1] << byte(testChars[2]);

			// ћногобайтные значени€ закладываютс€ в обратном пор€дке байтов.
			// “о есть 0x1234 будет разбито на 0x12 0x34 и заложено в контейнер как (..., 0x34, 0x12, ...).
			// ѕор€док самих закладываемых констант при этом сохран€етс€.
			codeContainer << short(0x1234) << unsigned short(0x5678) << 0x12345678L << byte(0xC0) << 0xF9ABCDEFUL << char(0x33);

			// “.е. кодом выше в контейнер было добавлено следующее:
			const char codeExpected[] = {
				testChars[0], testChars[1], testChars[2],

				'\x34', '\x12',					// 0x1234
				'\x78', '\x56',					// 0x5678
				'\x78', '\x56', '\x34', '\x12',	// 0x12345678
				'\xC0',							// 0xC0
				'\xEF', '\xCD', '\xAB', '\xF9',	// 0xF9ABCDEF
				'\x33'							// 0x33
			};
			
			// ѕровер€ем, так ли оно:
			auto code = codeContainer.GetCode();
			for (int i = 0; i < sizeof(codeExpected); i++)
				Assert::AreEqual(codeExpected[i], char(code[i]));

			// –азмер контейнера - количество байт внутри него.
			Assert::AreEqual(sizeof(codeExpected), codeContainer.GetCodeSize());

			// ќчищаем контейнер.
			codeContainer.Clear();
			// ѕосле очистки контейнер пуст.
			Assert::AreEqual(size_t(0), codeContainer.GetCodeSize());
			// ѕопытка получени€ указател€ на код пустого контейнера приведЄт к исключению.
			Assert::ExpectException<std::out_of_range>([&codeContainer]() { codeContainer.GetCode(); });
		}

		// --------------------------------------------------------------------------
	};
}