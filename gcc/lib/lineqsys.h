#ifndef _LINEQSYS_H
#define _LINEQSYS_H

#include "matrix.h"

#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/lu.hpp>
#include <boost/numeric/ublas/io.hpp>

namespace bnu = boost::numeric::ublas;

/*!
 solves a system of linear equations given as an augmented matrix
*/
template <typename T>
class cLinEqSys
{
public:
	cLinEqSys(const T **elems, std::size_t rows, std::size_t cols)
	{
		//init coefficients matrix
		m_CoeffMatrix.resize(rows,cols);
		for(std::size_t row = 0; row < rows; row++)	
		{
			for(std::size_t col = 0; col < cols - 1; col++)
			{
				assert(elems[row][col]);
				m_CoeffMatrix(row,col) = elems[row][col];
			}
		}

		//init vector of constant terms
		m_ConstantTermVec.resize(rows);
		for(std::size_t row = 0; row < rows; row++)	
			m_ConstantTermVec(row) = elems[row][cols - 1];
	};

	cLinEqSys(bnu::matrix<T>& mat)
	{
		//init coefficients matrix
		m_CoeffMatrix.resize(mat.size1(),mat.size2() - 1);
		for(std::size_t row = 0; row < mat.size1(); row++)	
			for(std::size_t col = 0; col < mat.size2() - 1; col++)
				m_CoeffMatrix(row, col) = mat(row, col);

		//init right hand side
		m_ConstantTermVec.resize(mat.size1());
		for(std::size_t row = 0; row < mat.size1(); row++)	
			m_ConstantTermVec(row) = mat(row, mat.size2() - 1);
	};

	~cLinEqSys()
	{
	};

	/*!
	 solve the linear system when there is a unique solution
	 uses LUP factorization followed by back substitution
	*/
	bnu::vector<T>& SolveUnique()
	{
		if(m_CoeffMatrix.size1() != m_CoeffMatrix.size2())
			throw std::logic_error("underdetermined or overdetermined system");
		bnu::permutation_matrix<T> pmMat(m_CoeffMatrix.size1());
		if(0 != lu_factorize(m_CoeffMatrix, pmMat))
			throw std::logic_error("no solution, singular matrix");
		bnu::lu_substitute(m_CoeffMatrix, pmMat, m_ConstantTermVec);
		return m_ConstantTermVec;
	};

	/*!
	 solve an overdetermined linear system
	 by solving the least squares problem we get an approximate solution
	 x = (trans(A) * A)^-1 * A * y
	 TODO -- improve on complexity - this is overkill
	*/
	bnu::vector<T> SolveOverdetermined()
	{
		if(m_CoeffMatrix.size1() < m_CoeffMatrix.size2())
			throw std::logic_error("underdetermined system");
		bnu::matrix<T> inverse;
		bnu::matrix<T> temp = bnu::prod(bnu::trans(m_CoeffMatrix), m_CoeffMatrix);
		if(false == get_inverse(temp, inverse))
			throw std::logic_error("no solution, trans(A) * A should not be singular");
		bnu::matrix<T> temp1 = bnu::prod(inverse, bnu::trans(m_CoeffMatrix));
		return bnu::prod(temp1, m_ConstantTermVec);
	};

	/*!
	 solve an underdetermined linear system 
	 using Singular Value Decomposition
	*/
	bool SolveUnderdetermined(std::vector<T>& solution)
	{
		assert(m_CoeffMatrix.size1() > m_CoeffMatrix.size2());
		//TODO
	};

private:
	bnu::matrix<T> m_CoeffMatrix;
	bnu::vector<T> m_ConstantTermVec;
};


#endif

