#include "stdafx.h"
#include "SimpleExecutableMemoryManager.h"
using namespace fuura::compilation::memory;

#include <Windows.h>

std::shared_ptr<void> SimpleExecutableMemoryManager::PlaceToExecutableMemory(const void* shellCode, size_t codeSizeInBytes)
{
	auto allocatedMemory = new char[codeSizeInBytes];
	memcpy(allocatedMemory, shellCode, codeSizeInBytes);
	
	// �������� �� 32-������ ���������� ��������� ������ � ������ �������� � 0x1000 ����.
	auto pageBegin = (LPVOID)((reinterpret_cast<unsigned>(allocatedMemory)) & 0xFFFFF000u);
	DWORD unused;
	auto result = VirtualProtect(pageBegin, 0x1000, PAGE_EXECUTE_READWRITE, &unused);
	if (!result)
		throw std::bad_alloc();	// TODO

	return std::shared_ptr<void>(allocatedMemory, [](void* p) { delete[] p; });
}
