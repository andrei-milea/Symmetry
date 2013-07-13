#ifndef _TRIG_FUNCS_H
#define _TRIG_FUNCS_H

#include "variable.h"

#include <tgmath.h>
#include <ostream>

//////////////////////////////////////////////////////////////
/////////////////////trig functions///////////////////////////
//////////////////////////////////////////////////////////////
////////////////////////////////////////////////
////////////forward declarations////////////////
class cFuncExpr;

template<typename T>
class cCosine;

template<typename T>
class cAsine;

template<typename T>
class cTangent;

template<typename T>
class cAcosine;

template<typename T>
class cAtangent;
////////////////////////////////////////////////

template <typename T>
class cSine
{
public:
	cFuncExpr derivative(const cVariable &var)const;

	cFuncExpr primitive(const cVariable &var)const;

	cAsine<T> inverse()const;

	T operator()(T &value)const
	{
		return std::sin(value);
	}

	bool operator==(const cSine &sine)const
	{
		return true;
	}
};

template <typename T>
class cCosine
{
public:
	cFuncExpr derivative(const cVariable &var)const;

	cFuncExpr primitive(const cVariable &var)const;

	cAcosine<T> inverse()const;

	T operator()(T &value)const
	{
		return std::cos(value);
	}

	bool operator==(const cCosine &cosine)const
	{
		return true;
	}
};

template <typename T>
class cTangent
{
public:
	cFuncExpr derivative(const cVariable &var)const;

	cFuncExpr primitive(const cVariable &var)const;

	cAtangent<T> inverse()const;

	T operator()(T &value)const
	{
		//TODO
		return std::sin(value);
	}

	bool operator==(const cTangent &tangent)const
	{
		return true;
	}
};

template <typename T>
class cAsine
{
public:
	cFuncExpr derivative(const cVariable &var)const;

	cFuncExpr primitive(const cVariable &var)const;

	cSine<T> inverse()const;

	T operator()(T &value)const
	{
		//TODO
		return std::sin(value);
	}

	bool operator==(const cAsine &asine)const
	{
		return true;
	}
};

template <typename T>
class cAcosine
{
public:
	cFuncExpr derivative(const cVariable &var)const;

	cFuncExpr primitive(const cVariable &var)const;

	cCosine<T> inverse()const;

	T operator()(T &value)const
	{
		//TODO
		return std::sin(value);
	}
	
	bool operator==(const cAcosine &acosine)const
	{
		return true;
	}
};

template <typename T>
class cAtangent
{
public:
	cFuncExpr derivative(const cVariable &var)const;

	cFuncExpr primitive(const cVariable &var)const;

	cTangent<T> inverse()const;

	T operator()(T &value)const
	{
		//TODO
		return std::sin(value);
	}

	bool operator==(const cAtangent &atangent)const
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
inline std::ostream& operator<<(std::ostream& out, const cAsine<T>& asine)
{
	out << "asin";
	return out;
}

template <class T>
inline std::ostream& operator<<(std::ostream& out, const cAcosine<T>& acosine)
{
	out << "acos";
	return out;
}

template <class T>
inline std::ostream& operator<<(std::ostream& out, const cAtangent<T>& atangent)
{
	out << "atan";
	return out;
}

#endif


