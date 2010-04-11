/*
 * matrix.cpp
 *
 *  Created on: Apr 1, 2010
 *      Author: andrei.milea
 */
#ifndef _SQMATRIX_H
#define _SQMATRIX_H

#include "element.h"
#include <boost/numeric/ublas/matrix.hpp>


using namespace boost::numeric::ublas;

template <typename type, size_t SIZE, typename BinaryOp>
class cSqMatrix : public matrix<type>
{
public:
    cSqMatrix()
    	:matrix<type>(SIZE, SIZE)
	{};
    
    virtual ~cSqMatrix()    {};
};

template <typename type,size_t SIZE>
class cSqMatrix<type, SIZE, Addition> : public matrix<type>
{
public:
	static const matrix<type> Identity = zero_matrix<type>(SIZE);
};

template <typename type,size_t SIZE>
class cSqMatrix<type, SIZE, Multiplication> : public matrix<type>
{
public:
	static const matrix<type> Identity = identity_matrix<type>(SIZE);
};


#endif
