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
	cGetDeterminantCommand(const sLinExpression &expr, bool is_lu_command = false)
		:m_Expression(expr),
		m_Result(0.0),
		isLuCmd(is_lu_command)
	{};
	~cGetDeterminantCommand()	{};

	void Execute();

	unsigned int EstimateRunTime(const cEstimator &estimator)const;

	double GetResult()const
	{	return m_Result;	};

	bool isLuCommand()const
	{	return isLuCmd;	};

	const bnu::matrix<double>& GetLUMatrix()const
	{	return m_LuMatrix;	};

private:
	sLinExpression m_Expression;
	bnu::matrix<double> m_LuMatrix;
	double m_Result;
	bool isLuCmd;
};

}

#endif



