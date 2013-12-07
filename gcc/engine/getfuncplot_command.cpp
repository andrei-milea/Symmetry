#include "getfuncplot_command.h"

namespace engine
{


void cGetFuncPlotCommand::Execute()
{
	if(0 == m_Poly.size())
		throw std::runtime_error("Invalid input: zero polynomial.");

	m_Result = m_Poly.plotPoints(-1000.0, 1000.0, 0.1);
}

unsigned int cGetFuncPlotCommand::EstimateRunTime(const cEstimator &estimator)const
{
	return 1;
}



}
