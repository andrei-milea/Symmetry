#ifndef _EXPONENTIAL_H
#define _EXPONENTIAL_H

#include <tgmath.h>

class cFuncExpr;

template<typename T>
class cLogarithm;

template <typename T>
class cExponential
{
public:
	cExponential(const T &base)
		:m_Base(base)
	{}

	T operator()(T &value)const
	{
		return std::pow(m_Base, value);
	}

	bool operator==(const cExponential& exp)const;

	cFuncExpr derivative(const cVariable& var)const;

	cFuncExpr integral(const cVariable& var)const;

	cLogarithm inverse()const;

private:
	T m_Base;

friend std::ostream& operator<<(std::ostream& out, const cExponential& exp);
};

inline std::ostream& operator<<(std::ostream& out, const cExponential& exp)
{
	out << exp.m_Base << "^";
	return out;
}

#endif


