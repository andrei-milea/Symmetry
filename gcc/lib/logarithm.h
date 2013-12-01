#ifndef _LOGARITHM_H
#define _LOGARITHM_H

#include <tgmath.h>
#include <stdexcept>
#include <boost/math/constants/constants.hpp>

template <typename T>
class cExponential;


template <typename T>
class cLogarithm
{
public:

	cLogarithm()
		:m_Base(boost::math::constants::e<T>())
	{}

	cLogarithm(const T& base)
		:m_Base(base)
	{
		if(base <= 0.0 || base == 1.0)
			throw std::invalid_argument("base for the logarithm should be greater than 0 and not 1");
	}

	T operator()(const T &value)const
	{
		if(value <= 0)
			throw std::domain_error("domain of logarithms is (0, +inf)");

		if(m_Base == boost::math::constants::e<T>())
			return std::log(value);

		return std::log(value)/std::log(m_Base);
	}

	bool operator==(const cLogarithm& log)const
	{
		return m_Base == log.m_Base;
	}

	cExponential<T> inverse()const
	{
		return cExponential<T>(m_Base);
	}

	T base()const
	{	return m_Base;	}

private:
	T m_Base;

template <typename Y>
friend std::ostream& operator<<(std::ostream& out, const cLogarithm<Y>& log);
};

template <typename T>
inline std::ostream& operator<<(std::ostream& out, const cLogarithm<T>& log)
{
	if(log.m_Base != boost::math::constants::e<T>())
		out << "log_" << log.m_Base;
	else
		out << "log";
	return out;
}

#endif

