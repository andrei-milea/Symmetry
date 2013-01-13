
#include "getnorm_command.h"

#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/matrix.hpp>

namespace engine
{

using namespace boost::numeric::ublas;

void cGetNormCommand::Execute()
{
	if((1 != m_Expression.terms.size()) || (1 != m_Expression.terms[0].factors.size()))
		throw std::runtime_error(CONTEXT_STR + " Invalid input. Please provide a valid vector for the euclidean norm.");
	cMatrix *mat = boost::get<cMatrix >(&(m_Expression.terms[0].factors[0].factor));
	if(nullptr == mat || (mat->rows_no != mat->elements.size()))
		throw std::runtime_error(CONTEXT_STR + " Invalid input. Please provide a valid vector for the euclidean norm.");

	vector<double> vec(mat->rows_no);
	for(std::size_t idx = 0; idx < mat->rows_no; idx++)
		vec(idx) = mat->elements[idx];
	m_Result = norm_2(vec);
};

unsigned int cGetNormCommand::EstimateRunTime(const cEstimator &estimator)const
{
	return 1;
};



}
