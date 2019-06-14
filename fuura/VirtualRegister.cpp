#include "stdafx.h"
#include "VirtualRegister.h"
#include "Exception.h"

using namespace fuura;
using namespace fuura::compilation;

///////////////////////////////////////////////////////////////////////////////
//
//	VirtualRegisterManager
//
///////////////////////////////////////////////////////////////////////////////

// ----------------------------------------------------------------------------
inline VirtualRegister VirtualRegisterManager::Allocate(RegisterType type)
{
	m_registerData.push_back(VRData(type, static_cast<int>(m_registerData.size())));

	// Здесь намеренно дважды создаётся VirtualRegister чтобы избежать копирования,
	// увеличивающего длину цепочки.
	auto vrData = &m_registerData.back();
	m_registerCopies.push_back(VirtualRegister(vrData));
	return VirtualRegister(vrData);
}

// ----------------------------------------------------------------------------
VirtualRegister VirtualRegisterManager::AllocateInt8()
{
	return Allocate(RegisterType::Byte);
}

// ----------------------------------------------------------------------------
VirtualRegister VirtualRegisterManager::AllocateInt16()
{
	return Allocate(RegisterType::Word);
}

// ----------------------------------------------------------------------------
VirtualRegister VirtualRegisterManager::AllocateInt32()
{
	return Allocate(RegisterType::DoubleWord);
}

// ----------------------------------------------------------------------------
VirtualRegister VirtualRegisterManager::AllocateFloat64()
{
	return Allocate(RegisterType::DoubleFloat);
}

// ----------------------------------------------------------------------------
const std::vector<VirtualRegisterProxy>& VirtualRegisterManager::GetAllocatedRegisters() const
{
	return m_registerCopies;
}

///////////////////////////////////////////////////////////////////////////////
//
//	VirtualRegister
//
///////////////////////////////////////////////////////////////////////////////

// ----------------------------------------------------------------------------
VirtualRegister::VirtualRegister(VirtualRegisterManager::VRData* data)
	: m_data(data)
{
}

// ----------------------------------------------------------------------------
VirtualRegister::VirtualRegister(const VirtualRegister& source)
	: m_data(source.m_data)
{
	m_data->chainLength++;
}

// ----------------------------------------------------------------------------
bool VirtualRegister::operator == (const VirtualRegister& reg) const
{
	return m_data == reg.m_data;
}

// ----------------------------------------------------------------------------
bool VirtualRegister::operator != (const VirtualRegister& reg) const
{
	return m_data != reg.m_data;
}

// ----------------------------------------------------------------------------
int VirtualRegister::GetUID() const
{
	return m_data->uid;
}

// ----------------------------------------------------------------------------
RegisterType VirtualRegister::GetType() const
{
	return m_data->type;
}

// ----------------------------------------------------------------------------
bool VirtualRegister::IsSet() const
{
	return m_data->isSet;
}

// ----------------------------------------------------------------------------
template <class RegisterTypeT>
inline void VirtualRegister::CheckTypes() const
{
	RegisterType expectedType = RegisterType::FromRegister<RegisterTypeT>();
	RegisterType actualType   = m_data->type;
	if (expectedType != actualType)
		throw RegisterTypeMismatch(m_data->uid, expectedType, actualType);
}

// ----------------------------------------------------------------------------
inline void VirtualRegister::CheckSet() const
{
	if (!IsSet())
		throw RegisterValueIsNotSet(m_data->uid);
}

// ----------------------------------------------------------------------------
template <class RegisterTypeT>
inline void VirtualRegister::SetValue(RegisterTypeT reg)
{
	CheckTypes<RegisterTypeT>();

	m_data->value = int(reg);
	m_data->isSet = true;
}

// ----------------------------------------------------------------------------
void VirtualRegister::SetValue(RegisterInt8 reg)
{
	SetValue<RegisterInt8>(reg);
}

// ----------------------------------------------------------------------------
void VirtualRegister::SetValue(RegisterInt16 reg)
{
	SetValue<RegisterInt16>(reg);
}

// ----------------------------------------------------------------------------
void VirtualRegister::SetValue(RegisterInt32 reg)
{
	SetValue<RegisterInt32>(reg);
}

// ----------------------------------------------------------------------------
void VirtualRegister::SetValue(RegisterFloat64 reg)
{
	SetValue<RegisterFloat64>(reg);
}

// ----------------------------------------------------------------------------
template <class RegisterTypeT>
inline RegisterTypeT VirtualRegister::GetValueAs() const
{
	CheckTypes<RegisterTypeT>();
	CheckSet();

	return RegisterTypeT(m_data->value);
}

// ----------------------------------------------------------------------------
RegisterInt8 VirtualRegister::GetValueAsInt8() const
{
	return GetValueAs<RegisterInt8>();
}

// ----------------------------------------------------------------------------
RegisterInt16 VirtualRegister::GetValueAsInt16() const
{
	return GetValueAs<RegisterInt16>();
}

// ----------------------------------------------------------------------------
RegisterInt32 VirtualRegister::GetValueAsInt32() const
{
	return GetValueAs<RegisterInt32>();
}

// ----------------------------------------------------------------------------
RegisterFloat64 VirtualRegister::GetValueAsFloat64() const
{
	return GetValueAs<RegisterFloat64>();
}

// ----------------------------------------------------------------------------
int VirtualRegister::GetChainLength() const
{
	return m_data->chainLength;
}

// ----------------------------------------------------------------------------
void VirtualRegister::EndChain()
{
	m_data->isActual = false;
}

// ----------------------------------------------------------------------------
bool VirtualRegister::IsActual() const
{
	return m_data->isActual;
}


///////////////////////////////////////////////////////////////////////////////
//
//	VirtualRegisterProxy
//
///////////////////////////////////////////////////////////////////////////////

// ----------------------------------------------------------------------------
VirtualRegisterProxy::VirtualRegisterProxy(const VirtualRegister& source)
	: VirtualRegister(source.m_data)
{
}

// ----------------------------------------------------------------------------
VirtualRegisterProxy::VirtualRegisterProxy(const VirtualRegisterProxy& source)
	: VirtualRegister(source.m_data)
{
}

VirtualRegisterProxy& VirtualRegisterProxy::operator = (VirtualRegisterProxy& source)
{
	m_data = source.m_data;
	return *this;
}


///////////////////////////////////////////////////////////////////////////////



// ----------------------------------------------------------------------------
std::ostream& fuura::compilation::operator << (std::ostream& out, const VirtualRegister& vr)
{
	out << "vr" << char(vr.GetType()) << vr.GetUID();
	return out;
}

// ----------------------------------------------------------------------------
std::ostream & fuura::compilation::operator<<(std::ostream & out, const VirtualRegisterManager & vrm)
{
	const auto& regs = vrm.GetAllocatedRegisters();
	out << '[';

	bool first = true;
	for (auto i = regs.cbegin(), end = regs.cend(); i != end; i++)
	{
		if (!(*i).IsActual())
			continue;

		if (first)
			first = false;
		else
			out << ", ";

		out << *i << ':' << (*i).GetChainLength();
	}

	out << ']';
	return out;
}

// ----------------------------------------------------------------------------
