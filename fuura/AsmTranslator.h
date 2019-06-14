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
	//	����� �������������� ����� � �������� ��������������, ������ ������
	//	��������� �������� ���. �� ����� �������� ������� � ������ �������� �
	//	�����-���� ����������� ������, ����������� � ������ ������ ����������.
	//
	///////////////////////////////////////////////////////////////////////////
	class AsmTranslator
	{
	public:
		AsmTranslator() = default;

	public:
		// --------------------------------------------------------------------------
		// ������ ����� ���� ����, � ������� ����� ��������������� ������������
		// ��������� �������. ���� ������ ��� ���� �����������, �� �� ������������.
		// --------------------------------------------------------------------------
		void RestartBuilding();

		// --------------------------------------------------------------------
		// ���������� �������������� ������, ����������� ���, ������������ �
		// ����������� � ������ ������. ����� ������������������ ���� ��� ����
		// ������������.
		// ������������ ������ ��� ������������ �� ��, ����� ���������
		// ����������� ��������� () ��������������� ����������������� �������.
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

		//	+ ��������� ��������� �� ��������.
		//	+ �����������.

	public:
		// ���������� ��������, ����������� ����� ������� ��������:

		// ...

	public:
		// --------------------------------------------------------------------
		// ����� ��� ������������, � �������� ���� ����� �� ������������.
		// --------------------------------------------------------------------
		std::vector<byte> GetCopyOfCurrentCode();

	private:
		// --------------------------------------------------------------------
		// ��� true, ���� �������� ������ ���� ������� �� ����� � ��������,
		// ������� ��� ���������. ��������� ���� �����.
		// ��������, 0x00000003 ��� 0xFFFFFF26 ��������� ���, � 0x00000123 ��� 0xFFFFFA26 - ��� ���.
		// --------------------------------------------------------------------
		bool CanBeReducedToByte(int32 constantToReduce) const;

		// --------------------------------------------------------------------
		// ��������� ������ ���������:
		//		- ��������� ������� ���������, �.�. [eax]
		//		- ��������� ������� ��������� �� ���������, �.�. [eax+123]
		// ��������� ���� �� �����.
		// --------------------------------------------------------------------
		void MovImplementationIndirect(RegisterInt32 indirectRegister, RegisterInt32 directRegister, byte indirectOperandNum, std::optional<int32> offsetFromIndirectRegister);

	private:
		// ������ ������� ����������������� ���.
		MachineCodeContainer m_machineCode;

		// �������� ������ ��� ����������������� �������.
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