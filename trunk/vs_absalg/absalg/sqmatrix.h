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

template <typename type>
class cSqMatrixEl : public boost::numeric::ublas::matrix<type>, public cElement<type>
{
public:
    cSqMatrixEl(size_t size)
    :matrix<type>(size,size),
    cElement<type>()
    {};
       
    
    virtual ~cSqMatrixEl()    {};


    size_t GetOrder()
    {
        while((*this) != cSqMatrixEl<type>::ZeroMatrix)
        {
            this *= this;
        }
    };


    //optimized get order   -- check size
    size_t GetOrder(size_t group_order)
    {
        if(matrix<type>.size1() == 1 || group_order == 1)
        {
            return 1;
        }
        //TODO


    };

private:
    static const identity_matrix<type>  IdentityMat = identity_matrix<type>(size);
    static const zero_matrix<type>      ZeroMatrix = zero_matrix<type>(size);
};

typedef cSqMatrixEl<int> cIntSqMatrix;

#endif