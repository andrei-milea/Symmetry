/*
 * matrix.cpp
 *
 *  Created on: Apr 1, 2010
 *      Author: andrei.milea
 */
#ifndef _SQMATRIX_H
#define _SQMATRIX_H

#include <boost/numeric/ublas/matrix.hpp>
#include "binary_op.h"


using namespace boost::numeric::ublas;

//squared matrix element representation
template <typename T,
std::size_t SIZE,
class BinaryOp,
class ConcreteRep = matrix<T> >
class cSqMatrixElement : public ConcreteRep
{
public:
    cSqMatrixElement()
    	:ConcreteRep(SIZE,SIZE)
	{};
    
    virtual ~cSqMatrixElement()    {};

	std::size_t GetOrder()
    {
		std::size_t size = 0;
		ConcreteRep temp = (*this);
        while(temp != cSqMatrixElement::GetIdentity())
        {
            temp = BinaryOp::BinOp(temp,(*this));
			size++;
        }
		return size;
    };

	std::size_t GetOrder(std::size_t group_order);

	ElementType GetNthPower(std::size_t n)
	{
		ElementType temp = cSqMatrixElement::GetIdentity();
		if(n%2 == 1)
		{
			this = this * temp;
		}
		while(n > 1)
		{
			this = this^2;
			n = n / 2;
			if(n%2 == 1)
			{
				temp =  temp * this;
			}
		}
		return temp;
	};

private:
	static ConcreteRep GetIdentity()
	{
		if(BinaryOp::isAdditive)
			return zero_matrix<T>(SIZE, SIZE);
		else
			return identity_matrix<T>(SIZE, SIZE);
	};
};


#endif
