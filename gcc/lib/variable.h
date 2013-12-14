#ifndef _VARIABLE_H
#define _VARIABLE_H

#include <string>
#include <ostream>

class cVariable
{
public:
	cVariable(const std::string& str = "")
		:m_Str(str)
	{}
	cVariable(char var)
		:m_Str(1, var)
	{}

	const cVariable& operator=(char var)
	{
		m_Str = std::string(1, var);
		return *this;
	}
	
	const std::string getStr()const
	{
		return m_Str;
	}

	bool operator==(const cVariable& var)const
	{
		return m_Str == var.m_Str;
	}

	bool operator==(const std::string& var_str)const
	{
		return m_Str == var_str;
	}

private:
	std::string m_Str;

friend std::ostream& operator<<(std::ostream& out, const cVariable& var);
friend bool operator<(const cVariable& var1, const cVariable& var2);
};

inline std::ostream& operator<<(std::ostream& out, const cVariable& var)
{
	out << var.getStr();
	return out;
}

inline bool operator<(const cVariable& var1, const cVariable& var2)
{
	return var1.m_Str < var2.m_Str;
}

#endif

