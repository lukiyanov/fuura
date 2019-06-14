#pragma once
#include "IAsmInstruction.h"
#include "ToString.h"
#include "ProcessorTypes.h"
#include "RegisterPlaceholder.h"

namespace fuura::compilation
{
	///////////////////////////////////////////////////////////////////////////
	class MovI32 : public IAsmInstruction
	{
		//RegisterPlaceholder<RegisterInt32> m_register;
		int32 m_value;

	public:
		/*
		MovI32(compilation::VirtualRegisterManager& vrm, int32 value)
			: m_value(value), m_register(vrm.AllocateRegister<RegisterInt32>())
		{
		}*/

		std::string GetName() const override
		{
			return "mov";	//std::string("mov ") + "reg" + ", " + tools::ToString(m_value);
		}
	};

	///////////////////////////////////////////////////////////////////////////
}