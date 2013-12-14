#include "getfuncplot_command.h"

namespace engine
{


void cGetFuncPlotCommand::Execute()
{
	m_Result = m_FuncExpr.plotPoints(-1000.0, 1000.0, 0.1);
}

unsigned int cGetFuncPlotCommand::EstimateRunTime(const cEstimator &estimator)const
{
	return 1;
}



}
