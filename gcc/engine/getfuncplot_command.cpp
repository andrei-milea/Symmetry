#include "getfuncplot_command.h"
#include <sstream>

namespace engine
{


void cGetFuncPlotCommand::Execute()
{
	m_Result = m_FuncExpr.plotPoints(-8.0, 8.0, 0.2);
}

std::string cGetFuncPlotCommand::GetResultStr()const
{
	std::string result_str;
	std::stringstream ss;
	ss.precision(std::numeric_limits<double>::digits10);

	result_str = "plot: ";
	if(isSurface())
	{
		for(auto points : m_Result)
		{
			ss.str("");
			ss << std::fixed << std::setprecision(2) << std::get<0>(points) << "," << std::get<1>(points) << "," << std::get<2>(points);
			result_str += ss.str() + ";";
		}
	}
	else
	{
		for(auto points : m_Result)
		{
			ss.str("");
			ss << std::fixed << std::setprecision(2) << std::get<0>(points) << "," << std::get<1>(points);
			result_str += ss.str() + ";";
		}
	}
	return result_str;
}

unsigned int cGetFuncPlotCommand::EstimateRunTime(const cEstimator &estimator)const
{
	return 1;
}



}
