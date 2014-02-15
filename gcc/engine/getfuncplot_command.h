
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
	cGetFuncPlotCommand(const cFuncExpr &fnc_expr)
		:m_FuncExpr(fnc_expr)
	{
	}

	cGetFuncPlotCommand(cFuncExpr &&fnc_expr)
		:m_FuncExpr(std::move(fnc_expr))
	{
	}
	~cGetFuncPlotCommand(){}
	
	void Execute();

	unsigned int EstimateRunTime(const cEstimator &estimator)const;

	std::string GetResultStr()const;

	bool isSurface()const
	{	return	(m_FuncExpr.getVariables().size() == 2);	}

private:
	cFuncExpr m_FuncExpr;
	std::vector<std::tuple<double, double, double> > m_Result;
};

}


#endif
