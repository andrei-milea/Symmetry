
#ifndef _GETFUNCPLOT_COMMAND_H
#define _GETFUNCPLOT_COMMAND_H

#include "command.h"
#include "func_parser.h"

#include "../lib/func_expr.h"

#include <vector>
#include <utility>

namespace engine
{

class cGetFuncPlotCommand : public cCommand
{
public:
	cGetFuncPlotCommand(const std::vector<double> &poly)
		:m_Poly(poly)
	{
	}
	~cGetFuncPlotCommand(){}
	
	void Execute();

	unsigned int EstimateRunTime(const cEstimator &estimator)const;

	std::vector<std::tuple<double, double, double> >& GetResult()const
	{
		return m_Result;
	}

private:
	cFuncExpr m_Func;
	std::vector<std::tuple<double, double, double> > m_Result;
};

}


#endif
