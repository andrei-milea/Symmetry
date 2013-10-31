/*
 * binary_op.h
 *
 *  Created on: Mar 30, 2010
 *      Author: andrei.milea
 */

#ifndef _BINARY_OP_H
#define _BINARY_OP_H

#include <ostream>

/*!
  class that represents the addition binary operation
  used also as a template policy
*/
class Addition
{
public:
	template<typename T>
	T operator()(const T &ob1, const T &ob2)const
	{
		T result = ob1 + ob2;
		return result;
	}

	bool operator==(const Addition &add)const
	{
		return true;
	}

	bool isCommutative()const
	{
		return true;
	}

	static const bool isAdditive = true;
	static const bool isMultiplicative = false;
	static const bool isComposition = false;
};
inline std::ostream& operator<<(std::ostream& out, const Addition& addition)
{
	out << " + ";
	return out;
}

/*!
  class that represents the multiplication binary operation
  used also as a template policy
*/
class Multiplication
{
public:
	template<typename T>
	T operator()(const T &ob1, const T &ob2)const
	{
		T result = ob1 * ob2;
		return result;
	}

	bool operator==(const Multiplication &mult)const
	{
		return true;
	}

	bool isCommutative()const
	{
		return true;
	}

	static const bool isAdditive = false;
	static const bool isMultiplicative = true;
	static const bool isComposition = false;
};
inline std::ostream& operator<<(std::ostream& out, const Multiplication& multiplication)
{
	out << " * ";
	return out;
}

/*!
  class that represents the composition binary operation
  used also as a template policy
*/
class Composition
{
public:
	template<typename T>
	T operator()(const T &ob1, const T &ob2)const
	{
		T result = ob1 * ob2;
		return result;
	}

	bool operator==(const Composition &comp)const
	{
		return true;
	}

	bool isCommutative()const
	{
		return false;
	}

	static const bool isAdditive = false;
	static const bool isMultiplicative = false;
	static const bool isComposition = true;
};
inline std::ostream& operator<<(std::ostream& out, const Composition& composition)
{
	out << " * ";
	return out;
}

/*!
  class that represents the subtraction binary operation
*/
class Subtraction
{
public:
	template<typename T>
	T operator()(const T &ob1, const T &ob2)const
	{
		T result = ob1 - ob2;
		return result;
	}

	bool operator==(const Subtraction &sub)const
	{
		return true;
	}
	
	bool isCommutative()const
	{
		return false;
	}
};
inline std::ostream& operator<<(std::ostream& out, const Subtraction& subtraction)
{
	out << " - ";
	return out;
}

/*!
  class that represents the division binary operation
*/
class Division
{
public:
	template<typename T>
	T operator()(const T &ob1, const T &ob2)const
	{
		T result = ob1 / ob2;
		return result;
	}

	bool operator==(const Division &div)const
	{
		return true;
	}

	bool isCommutative()const
	{
		return false;
	}
};
inline std::ostream& operator<<(std::ostream& out, const Division& division)
{
	out << " / ";
	return out;
}

/*!
  class that represents the power operation
*/
class Power
{
public:
	template<typename T>
	T operator()(const int power, const T &ob2)const
	{
		T result = 1.0;
		if(power != 0)
		{
			for(int idx = 0; idx <= std::abs(power); idx++)
				result *= ob2;
			if(power < 0)
				result *= -1.0; 
		}

		return result;
	}

	//hack: disable implicit conversion with linker ERROR
	template<typename T>
	T operator()(const double power, const T &ob2)const;

	bool operator==(const Power &pow)const
	{
		return true;
	}

	bool isCommutative()const
	{
		return false;
	}
};
inline std::ostream& operator<<(std::ostream& out, const Power& pow)
{
	out << " ^ ";
	return out;
}

struct NoOp
{
	bool operator==(const NoOp &no_op)const
	{
		return true;
	}

	bool isCommutative()const
	{
		return true;
	}
};


#endif /* BINARY_OP_H_ */
