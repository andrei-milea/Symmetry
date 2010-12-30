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
//T = field element type
template <typename T,
std::size_t SIZE,
class ConcreteRep = boost_ubl::matrix<T> >
class cSqMatrixElement : public ConcreteRep
{
	typedef cSqMatrixElement<T, SIZE, ConcreteRep> SelfType;

public:

	//constructors
    cSqMatrixElement()
    	:ConcreteRep(SIZE,SIZE)
	{};
	cSqMatrixElement(ConcreteRep& matrix_rep)
		:ConcreteRep(matrix_rep)
	{};

    ~cSqMatrixElement()    {};

	//copy constructor and assign operator
	cSqMatrixElement(const cSqMatrixElement& mat)
	{
		ConcreteRep(static_cast<const ConcreteRep&>(mat));
	};
	SelfType &operator=(const SelfType &mat)
	{
		if(this != &mat)
		{
			ConcreteRep::operator=(mat);
		}
		return *this;
	};
	SelfType &operator=(const ConcreteRep &mat)
	{
		if(this != &mat)
		{
			ConcreteRep::operator=(mat);
		}
		return *this;
	};

	friend std::ostream& operator<<(std::ostream &out, SelfType const &mat)
	{
		return (out << static_cast<ConcreteRep const &> (mat));
	};

protected:
	SelfType GetInverse()const
	{

	};

public:
	template <typename OP>
	static ConcreteRep GetIdentity(OP BinaryOp)
	{
		if(OP::isAdditive)
		{
			return boost_ubl::zero_matrix<T>(SIZE, SIZE);
		}
		else
		{
			return boost_ubl::identity_matrix<T>(SIZE, SIZE);
		}
	};
};


#endif
