
#include "getdeterminant_command.h" 
#include "../lib/matrix.h"

namespace engine
{

void cGetDeterminantCommand::Execute()
{
	if((1 != m_Expression.terms.size()) || (1 != m_Expression.terms[0].factors.size()))
		throw std::runtime_error(CONTEXT_STR + " Invalid input. Provide a valid square matrix to compute the determinant.");
	cMatrix *mat = boost::get<cMatrix >(&(m_Expression.terms[0].factors[0].factor));
	if(nullptr == mat)
		throw std::runtime_error(CONTEXT_STR + " Invalid input. Provide a valid square matrix to compute the determinant.");

	double double_cols_no = mat->elements.size()/mat->rows_no;
	std::size_t cols_no = mat->elements.size()/mat->rows_no;
	if((double_cols_no != std::floor(double_cols_no)) || (cols_no != mat->rows_no))
		throw std::runtime_error(CONTEXT_STR + " Invalid input. Provide a valid square matrix to compute the determinant.");

	//add the matrix stored in row major order
	bnu::matrix<double> matrix(cols_no, cols_no);
	for(std::size_t rows_idx = 0; rows_idx < cols_no; rows_idx++)
		for(std::size_t cols_idx = 0; cols_idx < cols_no; cols_idx++)
			matrix(rows_idx, cols_idx) = mat->elements[cols_idx + rows_idx*cols_no];

	for(std::size_t cols_idx = 0; cols_idx < cols_no; cols_idx++)
		m_Trace += matrix(cols_idx, cols_idx);
	m_Result = get_determinant(matrix);
};

unsigned int cGetDeterminantCommand::EstimateRunTime(const cEstimator &estimator)const
{
	return 1;
};

}


