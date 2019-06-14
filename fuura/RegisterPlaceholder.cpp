#include "stdafx.h"
//#include "RegisterPlaceholder.h"
#include <sstream>

using namespace fuura::compilation;
using namespace std;


// ----------------------------------------------------------------------------
IRegisterPlaceholder::operator std::string() const
{
	std::ostringstream strbuf;
	strbuf << *this;
	return strbuf.str();
}

// ----------------------------------------------------------------------------
std::ostream& fuura::compilation::operator<<(std::ostream & out, const IRegisterPlaceholder & rp)
{
	out << "tmp-" << rp.GetID() << '-' << char(rp.GetType());
	return out;
}

// ----------------------------------------------------------------------------
