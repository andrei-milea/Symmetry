#ifndef _ABS_VAL_H
#define _ABS_VAL_H

#include <tgmath.h>
#include <iostream>

class cFuncExpr;
class cVariable;

template <typename T>
class cAbsVal
{
public:

	cAbsVal()
	{}

	T operator()(T &value)const
	{
		return std::abs(value);
	}

	bool operator==(const cAbsVal& exp)const
	{
		return true;
	}

	cAbsVal<T> inverse()const
	{
		return cAbsVal<T>();
	}

template <typename Y>
friend std::ostream& operator<<(std::ostream& out, const cAbsVal<Y>& abs);
};

template <typename T>
inline std::ostream& operator<<(std::ostream& out, const cAbsVal<T>& abs)
{
	out << "abs";
	return out;
}

#endif

