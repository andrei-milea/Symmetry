#ifndef _GETMATEXPR_COMMAND_H
#define _GETMATEXPR_COMMAND_H

#include "command.h"
#include "linalg_parser.h"

#include <boost/numeric/ublas/matrix.hpp>

namespace engine
{

class cGetMatExprCommand : public cCommand
{
public:
	cGetMatExprCommand(const sLinExpression &expr)
		:m_Expression(expr)
	{};
	~cGetMatExprCommand(){};
	
	void Execute();

	unsigned int EstimateRunTime(const cEstimator &estimator)const;

	const boost::numeric::ublas::matrix<double>& GetResult()const
	{
		return m_MatrixResult;
	};
	

private:
	boost::numeric::ublas::matrix<double> ComputeExpression(const sLinExpression &expression);
	boost::numeric::ublas::matrix<double> EvalTerm(const sLinTerm& term);
	boost::variant<boost::numeric::ublas::matrix<double>, double> EvalFactor(const sLinFactor& factor);

private:
	boost::numeric::ublas::matrix<double> m_MatrixResult;
	sLinExpression m_Expression;
};

}

#endif

