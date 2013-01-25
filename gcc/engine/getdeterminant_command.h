#ifndef _GETDETERMINANT_COMMAND_H
#define _GETDETERMINANT_COMMAND_H

#include "command.h"
#include "linalg_parser.h"

#include <boost/numeric/ublas/matrix.hpp>

namespace bnu = boost::numeric::ublas;

namespace engine
{

class cGetDeterminantCommand : public cCommand
{
public:
	cGetDeterminantCommand(const sLinExpression &expr)
		:m_Expression(expr),
		m_Result(0.0),
		m_Trace(0.0)
	{};
	~cGetDeterminantCommand()	{};

	void Execute();

	unsigned int EstimateRunTime(const cEstimator &estimator)const;

	double GetResult()const
	{	return m_Result;	};

	double GetTrace()const
	{	return m_Trace;	};

private:
	sLinExpression m_Expression;
	double m_Result;
	double m_Trace;
};

}

#endif



