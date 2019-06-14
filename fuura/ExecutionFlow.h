#pragma once
#include "IAsmInstruction.h"
#include <list>
#include <ostream>
#include <string>

namespace fuura::compilation
{
	///////////////////////////////////////////////////////////////////////////
	//
	//	����� ����������, �������� ������� IAsmInstruction �� ������� �� ����������.
	//
	///////////////////////////////////////////////////////////////////////////
	class ExecutionFlow
	{
		/*
		// ����������, ����������� ������� �� ������� + �������������� ����������
		// ��� ������� �������� ����������.
		std::list<std::pair<std::unique_ptr<IAsmInstruction>, std::string>> m_flow;

	public:
		// --------------------------------------------------------------------
		void PushBack(std::unique_ptr<IAsmInstruction> dependency)
		{
			m_flow.push_back(std::pair(std::move(dependency), std::string()));
		}

		// --------------------------------------------------------------------
		*/
		/*
		operator std::string()
		{
			std::ostringstream oss;


			return oss.str();
		}*/

		// --------------------------------------------------------------------
		//friend std::ostream& operator << (std::ostream& out, const ExecutionFlow& flow);
	};

	///////////////////////////////////////////////////////////////////////////
	/*
	inline std::ostream& operator << (std::ostream& out, const ExecutionFlow& flow)
	{
		// ������� ������� ����� ����� ������� �������.
		size_t maxLength = 0;
		for (auto& iter : flow.m_flow)
			if (auto len = ((std::string)*iter.first).length(); len > maxLength)
				maxLength = len;

		// � ����� ��� ������ ��������� ��� ������� �� ���� ����� + 4 (������ ����� ���������) ���������.
		// � ���� ����� ������� "//". ����� ��� ����� ��� "//" ���� ��������� ������ ���������.
		const auto commentPos = maxLength + 4;	// ������� "//"
		for (auto& iter : flow.m_flow)
		{
			std::string strCommand = *iter.first;
			auto spaceCount = commentPos - strCommand.length();
			out << strCommand << std::string(spaceCount, ' ') << "// " << iter.second << "\n";
		}

		// TODO: ������ �� ��� ��������� ����� "=".

		return out;
	}*/

	///////////////////////////////////////////////////////////////////////////
}