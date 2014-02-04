#ifndef _GETRREF_COMMAND_H
#define _GETRREF_COMMAND_H

#include "command.h"
#include "linalg_parser.h"

#include <boost/numeric/ublas/matrix.hpp>

namespace bnu = boost::numeric::ublas;

namespace engine
{

class cGetRREFCommand : public cCommand
{
public:
	cGetRREFCommand(const sLinExpression &expr)
		:m_Expression(expr)
	{};
	~cGetRREFCommand()	{};

	void Execute();

	unsigned int EstimateRunTime(const cEstimator &estimator)const;

	std::string GetResultStr()const;

private:
	sLinExpression m_Expression;
	bnu::matrix<double> m_Result;
};

}

#endif


