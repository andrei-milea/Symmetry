/*
 * binary_op.h
 *
 *  Created on: Mar 30, 2010
 *      Author: andrei.milea
 */

#ifndef _BINARY_OP_H
#define _BINARY_OP_H
// Group operation policies


class Addition
{
public:
	template<typename T>	
	T operator()(T &ob1, T &ob2)
	{
		T result = ob1 + ob2;
		return result;
	};

	static const bool isAdditive = true;
	static const bool isMultiplicative = false;
	static const bool isComposition = false;
};

class Multiplication
{
public:
	template<typename T>	
	T operator()(T &ob1, T &ob2)
	{
		T result = ob1 * ob2;
		return result;
	};

	static const bool isAdditive = false;
	static const bool isMultiplicative = true;
	static const bool isComposition = false;
};

class Composition
{
public:
	template<typename T>	
	static T BinOp(T &ob1, T &ob2)
	{
		T result = ob1 * ob2;
		return result;
	};

	static const bool isAdditive = false;
	static const bool isMultiplicative = false;
	static const bool isComposition = true;
};

#endif /* BINARY_OP_H_ */
