/*
 * matrix.cpp
 *
 *  Created on: Apr 1, 2010
 *      Author: andrei.milea
 */
#ifndef _SQMATRIX_H
#define _SQMATRIX_H

#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>
#include "binary_op.h"


namespace boost_ubl = boost::numeric::ublas;

//squared matrix element representation
template <typename T,
std::size_t SIZE,
class BinaryOp,
class ConcreteRep = boost_ubl::matrix<T> >
class cSqMatrixElement : public ConcreteRep
{
	typedef cSqMatrixElement<T,SIZE,BinaryOp,ConcreteRep> SelfType;
public:
    cSqMatrixElement()
    	:ConcreteRep(SIZE,SIZE)
	{};
    
    virtual ~cSqMatrixElement()    {};

	std::size_t GetOrder()
    {
		std::size_t size = 0;
		SelfType temp = (*this);
        while(temp != cSqMatrixElement::GetIdentity())
        {
            temp = BinaryOp::BinOp(temp,(*this));
			size++;
        }
		return size;
    };

	std::size_t GetOrder(std::size_t group_order);

	SelfType GetNthPower(std::size_t n)
	{
		SelfType temp = cSqMatrixElement::GetIdentity();
		if(n%2 == 1)
		{
			(*this) = (*this) * temp;
		}
		while(n > 1)
		{
			(*this) = (*this)^2;
			n = n / 2;
			if(n%2 == 1)
			{
				temp =  temp * (*this);
			}
		}
		return temp;
	};

	friend std::ostream& operator<<(std::ostream &out, SelfType const &mat)
	{
		return (out << static_cast<ConcreteRep const &> (mat));
	};


public:
	static ConcreteRep GetIdentity()
	{
		if(BinaryOp::isAdditive)
			return boost_ubl::zero_matrix<T>(SIZE, SIZE);
		else
			return boost_ubl::identity_matrix<T>(SIZE, SIZE);
	};
};


#endif
