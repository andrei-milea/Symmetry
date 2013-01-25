#ifndef _MATRIX_H
#define _MATRIX_H

#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <boost/numeric/ublas/lu.hpp>
#include <cassert>

namespace bnu = boost::numeric::ublas;

/*!
 computes the determinant by performing LUP factorization
 and multiplying the diagonal
*/
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

/*!
 computes the inverse by performing LUP factorization
 and back substitution
*/
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
	//solve AX=I
	bnu::lu_substitute(matrix, perm_matrix, inverse);
	return true;
};

/*!
 computes the row reduced echelon form by performing Gauss-Jordan elimination
 with partial pivoting and replaces the input matrix with it
*/
template <typename T>
void rref(bnu::matrix<T>& matrix)
{
	std::size_t pivot_col = 0;

	for(std::size_t rows_idx = 0; rows_idx < matrix.size1(); rows_idx++)
	{
		if(pivot_col >= matrix.size2())
			return;

		//search for a pivot if needed
		std::size_t rows1_idx = rows_idx;
		while(matrix(rows1_idx, pivot_col) == 0.0)
		{
			rows1_idx++;
			if(rows1_idx >= matrix.size1())
			{
				rows1_idx = rows_idx;
				pivot_col++;
				if(pivot_col >= matrix.size2())
					return;
			}
		}

		//swap rows if necessary
		if(rows_idx != rows1_idx)
		{
			bnu::vector<T> temp = bnu::row(matrix, rows_idx);
			bnu::row(matrix, rows_idx) = bnu::row(matrix, rows1_idx);
			bnu::row(matrix, rows1_idx) = temp;
		}

		//divide the row by the pivot
		T pivot = matrix(rows_idx, pivot_col);
		for(std::size_t cols_idx = 0; cols_idx < matrix.size2(); cols_idx++)
		{
			assert(pivot != 0.0);
			if(pivot != 1.0)
				matrix(rows_idx, cols_idx) /= pivot;
		}

		//elimination
		for(std::size_t rows2_idx = 0; rows2_idx < matrix.size1(); rows2_idx++)
		{
			if(rows2_idx != rows_idx)
			{
				T piv_elim = matrix(rows2_idx, pivot_col);
				for(std::size_t cols_idx = 0; cols_idx < matrix.size2(); cols_idx++)
				{
					matrix(rows2_idx, cols_idx) -= piv_elim * matrix(rows_idx, cols_idx);
				}
			}
		}
		//std::cout<<matrix<<"\n";
		pivot_col++;
	}
};

#endif

