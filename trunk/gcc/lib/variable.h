#ifndef _VARIABLE_H
#define _VARIABLE_H

#include <string>
#include <ostream>

class cVariable
{
public:
	cVariable(const std::string& str)
		:m_Str(str)
	{}
	
	const std::string getStr()const
	{
		return m_Str;
	}

	bool operator==(const cVariable& var)const
	{
		return m_Str == var.m_Str;
	}

private:
	std::string m_Str;
};

inline std::ostream& operator<<(std::ostream& out, const cVariable& var)
{
	out << var.getStr();
	return out;
}

#endif

