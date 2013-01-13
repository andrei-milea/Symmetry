
#include "getmatexpr_command.h"

#include <cmath>
#include <boost/numeric/ublas/io.hpp>

namespace engine
{

using namespace boost::numeric::ublas;

void cGetMatExprCommand::Execute()
{
	m_MatrixResult = ComputeExpression(m_Expression);
};

matrix<double> cGetMatExprCommand::ComputeExpression(const sLinExpression &expression)
{
	if((expression.terms.size() != 1) && (expression.terms.size() != expression.operations.size() + 1))
			throw std::runtime_error(CONTEXT_STR + " Failed to parse expression. Invalid terms.");

	if(1 == expression.terms.size())
	{
		return EvalTerm(expression.terms[0]);
	}

	matrix<double> MatrixResult = EvalTerm(expression.terms[0]);	
	for(std::size_t idx = 0; idx < expression.operations.size(); idx++)	
	{
		if(ADDITION == expression.operations[idx])	
		{
			 MatrixResult += EvalTerm(expression.terms[idx + 1]);
		}
		else if(SUBTRACTION == expression.operations[idx])	
		{		
			MatrixResult -= EvalTerm(expression.terms[idx + 1]);
		}
	}
	return MatrixResult;
};

matrix<double> cGetMatExprCommand::EvalTerm(const sLinTerm& term)
{
	if((term.factors.size() != 1) && (term.factors.size() != term.operations.size() + 1))
		throw std::runtime_error(CONTEXT_STR + " Failed to parse expression. Invalid terms.");
	if(1 == term.factors.size())
	{
		boost::variant<matrix<double>, double> factor = EvalFactor(term.factors[0]);
		matrix<double>* mat = boost::get<matrix<double> >(&factor);
		if(nullptr == mat)
			throw std::runtime_error(CONTEXT_STR + " Failed to parse expression. Invalid term.");
		return *mat;
	}
	
	boost::variant<matrix<double>, double> result_factor = EvalFactor(term.factors[0]);
	matrix<double> *MatrixResult = boost::get<matrix<double> >(&result_factor);
	std::size_t res_idx = 0;

	//must have a matrix to begin the multiplication of factors
	//if we have a scalar => exchange it with the first matrix in
	//the list of factors
	while(nullptr == MatrixResult)
	{
		result_factor = EvalFactor(term.factors[res_idx]);
		MatrixResult = boost::get<matrix<double> > (&result_factor);
		res_idx++;
		if(res_idx == term.factors.size())
			throw std::runtime_error(CONTEXT_STR + " Failed to parse expression. Invalid terms.");
	}
	if(res_idx != 0)
	{
		sLinTerm* non_const_term = const_cast<sLinTerm*> (&term);
		non_const_term->factors[res_idx] = non_const_term->factors[0];
	}

	for(std::size_t idx = 0; idx < term.operations.size(); idx++)	
	{
		assert(MULTIPLICATION == term.operations[idx]);
		boost::variant<matrix<double>, double> factor = EvalFactor(term.factors[idx + 1]);
		if(double* scalar = boost::get<double>(&factor))
			*MatrixResult *= *scalar;
		else if(matrix<double>* mat = boost::get<matrix<double> >(&factor))
			*MatrixResult = prod(*MatrixResult, *mat);
	}

	return *MatrixResult;
};

boost::variant<matrix<double>, double> cGetMatExprCommand::EvalFactor(const sLinFactor& factor)
{
	if(const double* scalar = boost::get<double>(&factor.factor))		
	{
		return *scalar;
	}
	else if(const cMatrix* mat = boost::get<cMatrix>(&factor.factor))		
	{
		double double_cols_no = mat->elements.size()/mat->rows_no;
		std::size_t cols_no = mat->elements.size()/mat->rows_no;
		if(double_cols_no != std::floor(double_cols_no))
			throw std::runtime_error(CONTEXT_STR + " Failed to parse expression. Invalid matrix.");

		//add the matrix stored in row major order
		matrix<double> ResultMatrix(mat->rows_no, cols_no);
		for(std::size_t rows_idx = 0; rows_idx < mat->rows_no; rows_idx++)
			for(std::size_t cols_idx = 0; cols_idx < cols_no; cols_idx++)
				ResultMatrix(rows_idx, cols_idx) = mat->elements[cols_idx + rows_idx*cols_no];

		return ResultMatrix;
	}
	else
	{
		const sLinExpression *expression = boost::get<sLinExpression>(&factor.factor);
		assert(expression);
		return ComputeExpression(*expression);
	}
};

unsigned int cGetMatExprCommand::EstimateRunTime(const cEstimator &estimator)const
{
	return 0;
};

}



