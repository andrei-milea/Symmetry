
#include "getinverse_command.h" 
#include "../lib/matrix.h"

namespace engine
{

void cGetInverseCommand::Execute()
{
	if((1 != m_Expression.terms.size()) || (1 != m_Expression.terms[0].factors.size()))
		throw std::runtime_error("Invalid input. Provide a valid square matrix to compute the inverse.");
	cMatrix *mat = boost::get<cMatrix >(&(m_Expression.terms[0].factors[0].factor));
	if(nullptr == mat)
		throw std::runtime_error("Invalid input. Provide a valid square matrix to compute the inverse.");

	double double_cols_no = mat->elements.size()/mat->rows_no;
	std::size_t cols_no = mat->elements.size()/mat->rows_no;
	if((double_cols_no != std::floor(double_cols_no)) || (cols_no != mat->rows_no))
		throw std::runtime_error("Invalid input. Provide a valid square matrix to compute the inverse.");

	//add the matrix stored in row major order
	bnu::matrix<double> input_matrix(cols_no, cols_no);
	for(std::size_t rows_idx = 0; rows_idx < cols_no; rows_idx++)
		for(std::size_t cols_idx = 0; cols_idx < cols_no; cols_idx++)
			input_matrix(rows_idx, cols_idx) = mat->elements[cols_idx + rows_idx*cols_no];

	bool res = get_inverse(input_matrix, m_Result);
	if(false == res)
		throw std::runtime_error("Invalid input. Matrix not invertible.");
};

unsigned int cGetInverseCommand::EstimateRunTime(const cEstimator &estimator)const
{
	return 1;
};

}
