#ifndef _GETINVERSE_COMMAND_H
#define _GETINVERSE_COMMAND_H

#include "command.h"
#include "linalg_parser.h"

#include <boost/numeric/ublas/matrix.hpp>

namespace bnu = boost::numeric::ublas;

namespace engine
{

class cGetInverseCommand : public cCommand
{
public:
	cGetInverseCommand(const sLinExpression &expr)
		:m_Expression(expr)
	{};
	~cGetInverseCommand()	{};

	void Execute();

	unsigned int EstimateRunTime(const cEstimator &estimator)const;

	const bnu::matrix<double>& GetResult()const
	{	return m_Result;	};

private:
	sLinExpression m_Expression;
	bnu::matrix<double> m_Result;
};

}

#endif


