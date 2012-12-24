#ifndef _LINEQSYS_H
#define _LINEQSYS_H

#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>


/*!
 solves a system of linear equations given as an augmented matrix
*/
template <typename T>
class cLinEqSys
{
	using namespace boost::numeric::ublas;
public:
	explicit cLinEqSys(const T **elems, std::size_t rows, std::size_t cols = rows)
		m_Rows(rows),
		m_Cols(cols)
	{
		//init coefficients matrix
		for(std::size_t row = 0; row < rows; row++)	
		{
			for(std::size_t col = 0; col < cols - 1; col++)
			{
				assert(elems[row][col]);
				m_CoeffMatrix(row,col) = elems[row][col];
			}
		}

		//init vector of constant terms
		for(std::size_t row = 0; row < rows; row++)	
		{
			m_ConstantTermVec(row) = elems[row][cols - 1];
		}
	};

	~cLinEqSys()
	{
	};

	bool Solve(std::vector<T>& solution)
	{
		bool singular = false;
		//TODO -- change this to use LAPACK or implement LU
		if(m_Rows == m_Cols)
		{
			permutation_matrix<T> pmMat(m_Rows);
			singular = lu_factorize(m_CoeffMatrix, pmMat);
			if(singular)
				return false;
			lu_substitute(m_CoeffMatrix, pmMat, m_ConstantTermVec);
		}
		else if(m_Rows < m_Cols)
		{
			//singular value decomposition
		}
		else
		{
			//least square problem
		}
		//copy the m_ConstantTermVec in the solution std vector
		return singular;
	};

	/*!
	 singular value decomposition
	*/
	bool SVD();

private:
	std::size_t m_Rows;
	std::size_t m_Cols;
	matrix<T> m_CoeffMatrix;
	vector<T> m_ConstantTermVec;
};


#endif

