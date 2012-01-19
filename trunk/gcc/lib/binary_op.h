/*
 * binary_op.h
 *
 *  Created on: Mar 30, 2010
 *      Author: andrei.milea
 */

#ifndef _BINARY_OP_H
#define _BINARY_OP_H


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
	};


	static const bool isAdditive = true;
	static const bool isMultiplicative = false;
	static const bool isComposition = false;
};

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
	};

	static const bool isAdditive = false;
	static const bool isMultiplicative = true;
	static const bool isComposition = false;
};


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
	};

	static const bool isAdditive = false;
	static const bool isMultiplicative = false;
	static const bool isComposition = true;
};

#endif /* BINARY_OP_H_ */
