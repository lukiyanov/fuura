#include "stdafx.h"
#include <sstream>
#include "IAsmInstruction.h"

using namespace std;
using namespace fuura::compilation;

// ----------------------------------------------------------------------------
fuura::compilation::IAsmInstruction::operator std::string()
{
	ostringstream strbuf;
	strbuf << *this;
	return strbuf.str();
}

// ----------------------------------------------------------------------------
std::ostream& fuura::compilation::operator<<(std::ostream& out, const IAsmInstruction& instruction)
{
	out << *instruction.GetResult() << " = " << instruction.GetName();

	// Аргументы.
	auto args = instruction.GetArguments();
	if (args.size())
	{
		auto iter = args.begin();
		out << " (" << **iter;

		++iter;
		for (auto end = args.end(); iter != end; ++iter)
			out << ", " << **iter;

		out << ')';
	}

	return out;
}

// ----------------------------------------------------------------------------
