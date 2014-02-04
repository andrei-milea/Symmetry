#include "getpolyzeros_command.h"
#include<sstream>

namespace engine
{


void cGetPolyZerosCommand::Execute()
{
	if(0 == m_Poly.size())
		throw std::runtime_error("Invalid input: zero polynomial.");
	m_Result = m_Poly.realZeros();
}


std::string cGetPolyZerosCommand::GetResultStr()const
{
	std::string result_str;
	std::stringstream ss;
	ss.precision(std::numeric_limits<double>::digits10);

	if(m_Result.size() == 0)
	{
		result_str = "no real solution found";
	}
	else
	{
		result_str = "roots: $";
		for(auto root : m_Result)
		{
			ss.str("");
			ss << root;
			result_str += ss.str() + "; ";
		}
		result_str += "$";
	}
	return result_str;
}

unsigned int cGetPolyZerosCommand::EstimateRunTime(const cEstimator &estimator)const
{
	return 1;
}



}
