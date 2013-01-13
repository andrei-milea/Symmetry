#ifndef _GETNORM_COMMAND_H
#define  _GETNORM_COMMAND_H

#include "command.h"
#include "linalg_parser.h"

namespace engine
{

class cGetNormCommand : public cCommand
{
public:
	cGetNormCommand(const sLinExpression &expr)
		:m_Expression(expr),
		m_Result(0.0)
	{};
	~cGetNormCommand(){};
	
	void Execute();

	unsigned int EstimateRunTime(const cEstimator &estimator)const;

	const double GetResult()const
	{
		return m_Result;
	};

private:
	sLinExpression m_Expression;
	double m_Result;
};

}


#endif

