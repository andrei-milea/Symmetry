#ifndef _TRIG_FUNCS_H
#define _TRIG_FUNCS_H

#include <tgmath.h>
#include <ostream>
#include <stdexcept>

//////////////////////////////////////////////////////////////
/////////////////////trig functions///////////////////////////
//////////////////////////////////////////////////////////////
////////////////////////////////////////////////
////////////forward declarations////////////////

template<typename T>
class cAsine;

template<typename T>
class cAcosine;

template<typename T>
class cAtangent;

template<typename T>
class cAcotangent;
////////////////////////////////////////////////

template <typename T>
class cSine
{
public:
	constexpr cAsine<T> inverse()const
	{
		return cAsine<T>();
	}

	T operator()(const T &value)const
	{
		return std::sin(value);
	}

	constexpr bool operator==(const cSine &sine)const
	{
		return true;
	}
};

template <typename T>
class cCosine
{
public:
	constexpr cAcosine<T> inverse()const
	{
		return cAcosine<T>();
	}

	T operator()(const T &value)const
	{
		return std::cos(value);
	}

	constexpr bool operator==(const cCosine &cosine)const
	{
		return true;
	}
};

template <typename T>
class cTangent
{
public:
	constexpr cAtangent<T> inverse()const
	{
		return cAtangent<T>();
	}

	T operator()(const T &value)const
	{
		if(0.0 == std::cos(value))
			throw std::domain_error("tangent undefined for values where cos is 0");

		return std::sin(value)/std::cos(value);
	}

	constexpr bool operator==(const cTangent &tangent)const
	{
		return true;
	}
};

template <typename T>
class cCotangent
{
public:
	constexpr cAcotangent<T> inverse()const
	{
		return cAcotangent<T>();
	}

	T operator()(const T &value)const
	{
		T sin_val = std::sin(value);
		if(0.0 == sin_val)
			throw std::domain_error("cotangent undefined for values where sin is 0");

		return std::cos(value)/sin_val;
	}

	constexpr bool operator==(const cCotangent &cotangent)const
	{
		return true;
	}
};

template <typename T>
class cAsine
{
public:
	constexpr cSine<T> inverse()const
	{
		return cSine<T>();
	}

	T operator()(const T &value)const
	{
		if(std::abs(value) > 1.0)
			throw std::domain_error("arcsine function is not defined outside of [-1, 1]");

		return std::asin(value);
	}

	constexpr bool operator==(const cAsine &asine)const
	{
		return true;
	}
};

template <typename T>
class cAcosine
{
public:
	constexpr cCosine<T> inverse()const
	{
		return cCosine<T>();
	}

	T operator()(const T &value)const
	{
		if(std::abs(value) > 1.0)
			throw std::domain_error("arccosine function is not defined outside of [-1, 1]");

		return std::acos(value);
	}
	
	constexpr bool operator==(const cAcosine &acosine)const
	{
		return true;
	}
};

template <typename T>
class cAtangent
{
public:
	constexpr cTangent<T> inverse()const
	{
		return cTangent<T>();
	}

	T operator()(const T &value)const
	{
		return std::atan(value);
	}

	constexpr bool operator==(const cAtangent &atangent)const
	{
		return true;
	}
};

template <typename T>
class cAcotangent
{
public:
	constexpr cCotangent<T> inverse()const
	{
		return cCotangent<T>();
	}

	T operator()(const T &value)const
	{
		if(value == 0)
			throw std::domain_error("arccotangent function is not defined in 0");

		return std::atan(1.0/value);
	}

	constexpr bool operator==(const cAcotangent &acotangent)const
	{
		return true;
	}
};

///////output overloaded operators
template <class T>
inline std::ostream& operator<<(std::ostream& out, const cSine<T>& sine)
{
	out << "sin";
	return out;
}

template <class T>
inline std::ostream& operator<<(std::ostream& out, const cCosine<T>& cosine)
{
	out << "cos";
	return out;
}

template <class T>
inline std::ostream& operator<<(std::ostream& out, const cTangent<T>& tangent)
{
	out << "tan";
	return out;
}

template <class T>
inline std::ostream& operator<<(std::ostream& out, const cCotangent<T>& cotangent)
{
	out << "cotan";
	return out;
}

template <class T>
inline std::ostream& operator<<(std::ostream& out, const cAsine<T>& asine)
{
	out << "arcsin";
	return out;
}

template <class T>
inline std::ostream& operator<<(std::ostream& out, const cAcosine<T>& acosine)
{
	out << "arccos";
	return out;
}

template <class T>
inline std::ostream& operator<<(std::ostream& out, const cAtangent<T>& atangent)
{
	out << "arctan";
	return out;
}

template <class T>
inline std::ostream& operator<<(std::ostream& out, const cAcotangent<T>& acotangent)
{
	out << "arccotan";
	return out;
}

#endif


