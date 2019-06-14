#pragma once
#include <memory>
#include <optional>
#include "MachineCodeContainer.h"
#include "CompiledFunction.h"
#include "SimpleExecutableMemoryManager.h"

namespace fuura::compilation
{
	///////////////////////////////////////////////////////////////////////////
	//
	//	Самый низкоуровневый класс в иерархии компилирования, просто создаёт
	//	указанный машинный код. Не имеет никакого понятия о дереве операций и
	//	каких-либо абстракциях вообще, относящимся к другим частям библиотеки.
	//
	///////////////////////////////////////////////////////////////////////////
	class AsmTranslator
	{
	public:
		AsmTranslator() = default;

	public:
		// --------------------------------------------------------------------------
		// Создаёт новый блок кода, в который будут последовательно дописываться
		// выбранные команды. Если старый при этом существовал, то он уничтожается.
		// --------------------------------------------------------------------------
		void RestartBuilding();

		// --------------------------------------------------------------------
		// Возвращает функциональный объект, выполняющий код, содержащийся в
		// компиляторе в момент вызова. Буфер откомпилированного кода при этом
		// сбрасывается.
		// Пользователь класса сам ответственен за то, чтобы сигнатура
		// получаемого оператора () соответствовала откомпилированной функции.
		// --------------------------------------------------------------------
		template <typename ...FunctionSignature>
		CompiledFunction<FunctionSignature...> GetFunction();

	public:
		void Nop();															// nop

		void Xor(RegisterInt32 reg1, RegisterInt32 reg2);					// xor eax, ebx
		void Xor(RegisterInt16 reg1, RegisterInt16 reg2);					// xor ax, bx
		void Xor(RegisterInt8  reg1, RegisterInt8  reg2);					// xor al, bh

		void Ret();															// ret
		void Ret(word popByteCount);										// ret 123

		void Call(RegisterInt32 address);									// call eax
		// TODO: call [123]

		void Push(int32 value);												// push 123
		void Push(RegisterInt32 source);									// push eax
		void Pop(RegisterInt32 dest);										// pop eax

		void Mov(RegisterInt32 to, int32 value);							// mov eax, 123
		void Mov(RegisterInt32 to, RegisterInt32 from);						// mov eax, ebx
		void Mov(RegisterInt32Indirect to, int32 value);					// mov [eax], 123
		void Mov(RegisterInt32PlusConstantIndirect to, int32 value);		// mov [eax + 123], 456
		void Mov(RegisterInt32Indirect to, RegisterInt32 from);				// mov [eax], ebx
		void Mov(RegisterInt32 to, RegisterInt32Indirect from);				// mov eax, [ebx]
		void Mov(RegisterInt32PlusConstantIndirect to, RegisterInt32 from);	// mov [eax + 123], ebx
		void Mov(RegisterInt32 to, RegisterInt32PlusConstantIndirect from);	// mov eax, [ebx + 123]

		void Lea();

		void Inc(RegisterInt32 reg);										// inc eax
		void Inc(RegisterInt16 reg);										// inc ax
		void Inc(RegisterInt8  reg);										// inc al
		void Dec(RegisterInt32 reg);										// dec eax
		void Dec(RegisterInt16 reg);										// dec ax
		void Dec(RegisterInt8  reg);										// dec al

		void Neg();
		void Add();
		void Sub();
		void Mul();
		void Div();

		void Cmp();
		void Je();
		void Jne();
		void Jz();
		void Jnz();

		void Jmp();

		//	+ Косвенную адресацию не забывать.
		//	+ Сопроцессор.

	public:
		// Объявления макросов, реализующих более сложные действия:

		// ...

	public:
		// --------------------------------------------------------------------
		// Нужна для тестирования, в релизном коде лучше не использовать.
		// --------------------------------------------------------------------
		std::vector<byte> GetCopyOfCurrentCode();

	private:
		// --------------------------------------------------------------------
		// Даёт true, если параметр должен быть обрезан до байта в командах,
		// которые это допускают. Учитывает знак числа.
		// Например, 0x00000003 или 0xFFFFFF26 допускают это, а 0x00000123 или 0xFFFFFA26 - уже нет.
		// --------------------------------------------------------------------
		bool CanBeReducedToByte(int32 constantToReduce) const;

		// --------------------------------------------------------------------
		// Реализует режимы адресации:
		//		- Косвенная базовая адресация, т.е. [eax]
		//		- Косвенная базовая адресация со смещением, т.е. [eax+123]
		// Остальные пока не нужны.
		// --------------------------------------------------------------------
		void MovImplementationIndirect(RegisterInt32 indirectRegister, RegisterInt32 directRegister, byte indirectOperandNum, std::optional<int32> offsetFromIndirectRegister);

	private:
		// Хранит текущий откомпилированный код.
		MachineCodeContainer m_machineCode;

		// Менеджер памяти под откомпилированные функции.
		memory::SimpleExecutableMemoryManager m_memoryManager;
	};

	///////////////////////////////////////////////////////////////////////////

	// ------------------------------------------------------------------------
	template <typename ...FunctionSignature>
	CompiledFunction<FunctionSignature...> AsmTranslator::GetFunction()
	{
		auto code = m_memoryManager.PlaceToExecutableMemory(m_machineCode.GetCode(), m_machineCode.GetCodeSize());
		m_machineCode.Clear();

		return CompiledFunction<FunctionSignature...>(code);
	}

	// ------------------------------------------------------------------------
}