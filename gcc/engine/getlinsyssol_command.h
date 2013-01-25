#ifndef _GETLINSYSSOL_COMMAND_H
#define _GETLINSYSSOL_COMMAND_H

#include "command.h"
#include "linalg_parser.h"

#include <boost/numeric/ublas/matrix.hpp>

namespace bnu = boost::numeric::ublas;

namespace engine
{

class cGetLinSysSolCommand : public cCommand
{
public:
	cGetLinSysSolCommand(const sLinExpression &expr, COMMAND_TYPE command)
		:m_Expression(expr),
		m_CommandType(command)
	{};
	~cGetLinSysSolCommand()	{};

	void Execute();

	unsigned int EstimateRunTime(const cEstimator &estimator)const;

	const bnu::matrix<double>& GetResult()const
	{	return m_Result;	};

private:
	sLinExpression m_Expression;
	bnu::matrix<double> m_Result;
	COMMAND_TYPE m_CommandType;
};

}

#endif


