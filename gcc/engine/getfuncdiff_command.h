
#ifndef _GETFUNCDIFF_COMMAND_H
#define _GETFUNCDIFF_COMMAND_H

#include "command.h"
#include "func_parser.h"
#include "../lib/func_expr.h"

#include <string>

namespace engine
{

class cGetFuncDiffCommand : public cCommand
{
public:
	cGetFuncDiffCommand(const cFuncExpr &fnc_expr)
		:m_FuncExpr(fnc_expr)
	{
	}
	~cGetFuncDiffCommand(){}
	
	void Execute();

	unsigned int EstimateRunTime(const cEstimator &estimator)const;

	std::string GetResultStr()const
	{	return m_Result;	}

private:
	cFuncExpr m_FuncExpr;
	std::string m_Result;
};

}


#endif

