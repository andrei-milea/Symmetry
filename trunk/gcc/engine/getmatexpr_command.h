#ifndef _GETMATEXPR_COMMAND_H
#define _GETMATEXPR_COMMAND_H

#include "linalg_command.h"
#include "linalg_parser.h"

namespace engine
{

class cGetMatExprCommand : public cLinAlgCommand
{
public:
	cGetMatExprCommand(const sLinExpression &expr)
		:m_Expression(expr)
	{};
	~cGetMatExprCommand(){};
	
	void Execute();

	unsigned int EstimateRunTime(const cEstimator &estimator)const;

	

private:
	boost::numeric::ublas::matrix<double> ComputeExpression(const sLinExpression &expression);
	boost::numeric::ublas::matrix<double> EvalTerm(const sLinTerm& term);
	boost::variant<boost::numeric::ublas::matrix<double>, double> EvalFactor(const sLinFactor& factor);

private:
	sLinExpression m_Expression;
};

}

#endif

