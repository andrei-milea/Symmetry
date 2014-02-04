#include "getpolyplot_command.h"
#include <sstream>

namespace engine
{


void cGetPolyPlotCommand::Execute()
{
	if(0 == m_Poly.size())
		throw std::runtime_error("Invalid input: zero polynomial.");

	m_Result = m_Poly.plotPoints(-1000.0, 1000.0, 0.1);
}

std::string cGetPolyPlotCommand::GetResultStr()const
{
	std::string result_str;
	std::stringstream ss;
	ss.precision(std::numeric_limits<double>::digits10);

	result_str = "plot: ";
	for(auto points : m_Result)
	{
		ss.str("");
		ss << std::fixed << std::setprecision(2) << points.first << "," << points.second;
		result_str += ss.str() + ";";
	}
	return result_str;
}

unsigned int cGetPolyPlotCommand::EstimateRunTime(const cEstimator &estimator)const
{
	return 1;
}



}
