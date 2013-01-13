#ifndef _MATRIX_H
#define _MATRIX_H

#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <boost/numeric/ublas/lu.hpp>
#include <cassert>

namespace bnu = boost::numeric::ublas;

template <typename T>
T get_determinant(bnu::matrix<T>& matrix)
{
	assert(matrix.size1() == matrix.size2());
	bnu::permutation_matrix<T> perm_matrix(matrix.size1());
	T determinant = 1.0;
	if(bnu::lu_factorize(matrix, perm_matrix))
	{
		return 0.0;
	}
	else
	{
		for(std::size_t idx = 0; idx < matrix.size1(); idx++)
		{
			//multiply all the elements on the diagonal
			//and change sign for every transposition
			determinant *= matrix(idx, idx);
			if(idx != perm_matrix(idx))
				determinant *= -1.0;
		}
	}
	return determinant;
};

template <typename T>
bool get_inverse(bnu::matrix<T>& matrix, bnu::matrix<T>& inverse)
{
	assert(matrix.size1() == matrix.size2());
	bnu::permutation_matrix<T> perm_matrix(matrix.size1());
	if(bnu::lu_factorize(matrix, perm_matrix))
	{
		return false;
	}	
	inverse.assign(bnu::identity_matrix<T>(matrix.size1()));
	bnu::lu_substitute(matrix, perm_matrix, inverse);
	return true;
};


#endif

