#include "stdafx.h"
#include "CppUnitTest.h"
#include "CppUnitTestAssert.h"

// Тестируем этот класс.
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

			auto reg1a = vrm.AllocateInt32();									// точка создания reg1a
			Assert::AreEqual(1, reg1a.GetChainLength());						// сразу после создания счётчик использований = 1
			Assert::IsFalse(reg1a.IsSet());										// сразу после создания регистр не установлен
			Assert::IsTrue(reg1a.IsActual());									// цепочка пока не завершена

			auto reg1b = reg1a;													// точка использования reg1a
			Assert::AreEqual(2, reg1a.GetChainLength());						// после использования счётчик увеличивается на 1
			Assert::AreEqual(reg1b.GetChainLength(), reg1a.GetChainLength());	// один счётчик на всю цепочку
			Assert::AreEqual(reg1a.GetUID(), reg1b.GetUID());					// один UID на всю цепочку
			Assert::IsTrue(reg1a.IsActual());									// цепочка всё ещё не завершена

			auto reg2 = vrm.AllocateInt32();									// совершенно новая цепочка
			Assert::AreNotEqual(reg1a.GetUID(), reg2.GetUID());					// не имеет с предыдущей ничего общего
			Assert::AreEqual(1, reg2.GetChainLength());							// аналогично reg1a при создании
			Assert::IsTrue(reg2.IsActual());									// аналогично reg1a при создании

			auto reg1c = reg1a;													// аналогично reg1b = reg1a
			Assert::AreEqual(3, reg1a.GetChainLength());						// аналогично
			Assert::AreEqual(3, reg1b.GetChainLength());						// аналогично
			Assert::AreEqual(3, reg1c.GetChainLength());						// аналогично
			Assert::IsTrue(reg1a.IsActual());									// аналогично
			Assert::AreEqual(1, reg2.GetChainLength());							// цепочки не влияют друг на друга

			reg1a.EndChain();													// завершаем первую цепочку
			Assert::IsFalse(reg1a.IsActual());									// и проверяем, завершена ли она теперь
			Assert::IsFalse(reg1b.IsActual());									// безразлично, к какому из ВР одной цепочки обращаться
			Assert::IsFalse(reg1c.IsActual());									// результат один и тот же

			Assert::IsTrue(reg2.IsActual());									// вторая цепочка ещё актуальна, хотя первая уже завершена
			reg2.EndChain();													// завершаем вторую цепочку
			Assert::IsFalse(reg2.IsActual());									// и проверяем

			Assert::IsTrue(reg1a == reg1b && reg1b == reg1c);					// два регистра равны если относятся к одной цепочке
			Assert::IsFalse(reg1a == reg2);										// и не равны в ином случае
		}

		// --------------------------------------------------------------------------
		TEST_METHOD(Test_VirtualRegister_GetSetValue)
		{
			VirtualRegisterManager vrm;

			auto reg1a = vrm.AllocateInt32();
			Assert::IsFalse(reg1a.IsSet());							// при создании значение не установлено

			Assert::ExpectException<RegisterValueIsNotSet>([&]() {	// попытка чтения ВР, значение которого не установлено
				reg1a.GetValueAsInt32();
			});

			Assert::ExpectException<RegisterTypeMismatch>([&]() {	// попытка установки в ВР значения другого типа
				reg1a.SetValue(RegisterFloat64::ST0);
			});

			// Устанавливаем значение ВР и проверяем успешность установки:
			reg1a.SetValue(RegisterInt32::EAX);
			Assert::IsTrue(reg1a.IsSet());
			Assert::AreEqual(RegisterInt32::EAX, reg1a.GetValueAsInt32());

			Assert::ExpectException<RegisterTypeMismatch>([&]() {	// попытка чтения из ВР значения другого типа
				reg1a.GetValueAsInt16();
			});

			// Остальные ВР этой же цепочки имеют те же параметры и меняются синхронно:
			auto reg1b = reg1a;
			Assert::IsTrue(reg1b.IsSet());
			Assert::AreEqual(reg1a.GetValueAsInt32(), reg1b.GetValueAsInt32());

			// В то время как ВР других цепочек никак не зависят от данной:
			auto reg2 = vrm.AllocateInt32();
			Assert::IsFalse(reg2.IsSet());
		}

		// --------------------------------------------------------------------------
		TEST_METHOD(Test_VirtualRegister_ManagerAccess)
		{
			VirtualRegisterManager vrm;
			auto regs = vrm.GetAllocatedRegisters();
			Assert::IsTrue(regs.empty());

			VirtualRegister reg1a = vrm.AllocateInt32();			// используются: [vrd1:1] события: vrd1 - аллокация
			regs = vrm.GetAllocatedRegisters();						// специально копируем, счётчики цепочек при этом увеличиваться не должны
			Assert::AreEqual(size_t(1), regs.size());			
			Assert::AreEqual(1, regs[0].GetChainLength());			// проверяем что не увеличились
			Assert::AreEqual(RegisterType::DoubleWord, regs[0].GetType());
			Assert::IsFalse(regs[0].IsSet());

			VirtualRegister reg1b = reg1a;						// используются: [vrd1:2] события: vrd1 - использование
			VirtualRegister reg2  = vrm.AllocateInt8();			// используются: [vrd1:2, vrb2:1] события: vrb2 - аллокация
			regs = vrm.GetAllocatedRegisters();
			Assert::AreEqual(size_t(2), regs.size());
			Assert::AreEqual(RegisterType::DoubleWord, regs[0].GetType());
			Assert::AreEqual(RegisterType::Byte,       regs[1].GetType());
			Assert::IsFalse(regs[0].IsSet());
			Assert::IsFalse(regs[1].IsSet());
			Assert::AreEqual(2, regs[0].GetChainLength());
			Assert::AreEqual(1, regs[1].GetChainLength());

			reg1a.EndChain();									// используются: [vrb2:1] события: vrd1 - завершение цепочки
			regs[1].SetValue(RegisterInt8::BH);					// устанавливаем значение ВР через менеджер
			reg2.EndChain();									// используются: [] события: vrb2 - завершение цепочки
			regs = vrm.GetAllocatedRegisters();
			Assert::AreEqual(size_t(2), regs.size());
			Assert::AreEqual(RegisterType::DoubleWord, regs[0].GetType());
			Assert::AreEqual(RegisterType::Byte, regs[1].GetType());
			Assert::IsFalse(regs[0].IsSet());
			Assert::IsTrue(regs[1].IsSet());
			Assert::AreEqual(2, regs[0].GetChainLength());
			Assert::AreEqual(1, regs[1].GetChainLength());
			Assert::AreEqual(RegisterInt8::BH, regs[1].GetValueAsInt8());	// проверяем успешность установки значения
			Assert::AreEqual(RegisterInt8::BH, reg2.GetValueAsInt8());		// проверяем успешность установки значения
		}

		// --------------------------------------------------------------------------
	};
}