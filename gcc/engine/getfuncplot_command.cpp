#include "getfuncplot_command.h"

namespace engine
{


void cGetFuncPlotCommand::Execute()
{
	m_Result = m_FuncExpr.plotPoints(-8.0, 8.0, 0.2);
}

unsigned int cGetFuncPlotCommand::EstimateRunTime(const cEstimator &estimator)const
{
	return 1;
}



}
