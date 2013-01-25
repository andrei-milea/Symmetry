#include "getlinsyssol_command.h"
#include "../lib/lineqsys.h"

namespace engine
{

void cGetLinSysSolCommand::Execute()
{
	if((1 != m_Expression.terms.size()) || (1 != m_Expression.terms[0].factors.size()))
		throw std::runtime_error(CONTEXT_STR + " Invalid input. Provide a valid linear system.");
	cMatrix *mat = boost::get<cMatrix >(&(m_Expression.terms[0].factors[0].factor));
	if(nullptr == mat)
		throw std::runtime_error(CONTEXT_STR + " Invalid input. Provide a valid linear system.");

	double double_cols_no = mat->elements.size()/mat->rows_no;
	std::size_t cols_no = mat->elements.size()/mat->rows_no;
	if(double_cols_no != std::floor(double_cols_no))
		throw std::runtime_error(CONTEXT_STR + " Invalid input. Provide a valid linear system.");

	//add the matrix stored in row major order
	m_Result.resize(mat->rows_no, cols_no);
	for(std::size_t rows_idx = 0; rows_idx < mat->rows_no; rows_idx++)
		for(std::size_t cols_idx = 0; cols_idx < cols_no; cols_idx++)
			m_Result(rows_idx, cols_idx) = mat->elements[cols_idx + rows_idx*cols_no];

	cLinEqSys<double> lin_eq_sys(m_Result);
	if(SOLVE_LINEQ_SYS == m_CommandType || SOLVEG_LINEQ_SYS == m_CommandType)
	{
		bnu::vector<double> result = lin_eq_sys.SolveUnique();
		m_Result.resize(result.size(),1);
		for(std::size_t idx = 0; idx < result.size(); idx++)
			m_Result(idx,0) = result(idx);
	}
	else
	{
		assert(m_CommandType == APPROX_LINEQ_SYS);
		//m_Result = lin_eq_sys.SolveUnderdetermined();
	}
};

unsigned int cGetLinSysSolCommand::EstimateRunTime(const cEstimator &estimator)const
{
	return 1;
};

}


