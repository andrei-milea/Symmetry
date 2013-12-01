#ifndef _EXPONENTIAL_H
#define _EXPONENTIAL_H

#include <tgmath.h>
#include <boost/math/constants/constants.hpp>
#include <stdexcept>

template<typename T>
class cLogarithm;

template <typename T>
class cExponential
{
public:
	cExponential()
		:m_Base(boost::math::constants::e<T>())
	{}

	cExponential(const T &base)
		:m_Base(base)
	{
		if(m_Base == 0.0)
			throw std::invalid_argument("0 not allowed as base for exponential function");
	}

	T operator()(const T &value)const
	{
		return std::pow(m_Base, value);
	}

	bool operator==(const cExponential& exp)const
	{
		return m_Base == exp.m_Base;
	}

	cLogarithm<T> inverse()const
	{
		return cLogarithm<T>(m_Base);
	}

	T base()const
	{	return m_Base;	}

private:
	T m_Base;

template <typename Y>
friend std::ostream& operator<<(std::ostream& out, const cExponential<Y>& exp);
};

template <typename T>
inline std::ostream& operator<<(std::ostream& out, const cExponential<T>& exp)
{
	if(exp.m_Base != boost::math::constants::e<T>())
		out << exp.m_Base << "^";
	else
		out << "e^";
	return out;
}

#endif


