#ifndef _LOGARITHM_H
#define _LOGARITHM_H

#include <tgmath.h>

class cFuncExpr;

template <typename T>
class cExponential;


template <typename T>
class cLogarithm
{
public:
	cLogarithm(const T& base)
		:m_Base(base)
	{}

	T operator()(T &value)const
	{
		return value;
	}

	bool operator==(const cLogarithm& exp)const;

	cFuncExpr derivative(const cVariable& var)const;

	cFuncExpr integral(const cVariable& var)const;

	cExponential inverse()const;

private:
	T m_Base;

friend std::ostream& operator<<(std::ostream& out, const cLogarithm& log);
};

inline std::ostream& operator<<(std::ostream& out, const cLogarithm& log)
{
	out << exp.m_Base << "log_" << log.m_Base;
	return out;
}

#endif

