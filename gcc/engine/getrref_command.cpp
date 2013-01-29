
#include "getrref_command.h"
#include "../lib/matrix.h"

namespace engine
{

void cGetRREFCommand::Execute()
{
	if((1 != m_Expression.terms.size()) || (1 != m_Expression.terms[0].factors.size()))
		throw std::runtime_error("Invalid input. Provide a valid matrix to compute the RREF.");
	cMatrix *mat = boost::get<cMatrix >(&(m_Expression.terms[0].factors[0].factor));
	if(nullptr == mat)
		throw std::runtime_error("Invalid input. Provide a valid matrix to compute the RREF.");

	double double_cols_no = mat->elements.size()/mat->rows_no;
	std::size_t cols_no = mat->elements.size()/mat->rows_no;
	if(double_cols_no != std::floor(double_cols_no))
		throw std::runtime_error("Invalid input. Provide a valid matrix to compute the RREF.");

	//add the matrix stored in row major order
	m_Result.resize(mat->rows_no, cols_no);
	for(std::size_t rows_idx = 0; rows_idx < mat->rows_no; rows_idx++)
		for(std::size_t cols_idx = 0; cols_idx < cols_no; cols_idx++)
			m_Result(rows_idx, cols_idx) = mat->elements[cols_idx + rows_idx*cols_no];

	rref(m_Result);
};

unsigned int cGetRREFCommand::EstimateRunTime(const cEstimator &estimator)const
{
	return 1;
};

}

