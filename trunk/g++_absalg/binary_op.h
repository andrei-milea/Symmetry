/*
 * binary_op.h
 *
 *  Created on: Mar 30, 2010
 *      Author: andrei.milea
 */

#ifndef _BINARY_OP_H
#define _BINARY_OP_H

class Addition
{
public:
	template<typename T>	
	T BinOp(T &ob1, T &ob2)
	{
		T result = ob1 + ob2;
		return result;
	};
	
};
class Multiplication
{
public:
	template<typename T>	
	T BinOp(T &ob1, T &ob2)
	{
		T result = ob1 * ob2;
		return result;
	};

};

class Composition
{

};

#endif /* BINARY_OP_H_ */
