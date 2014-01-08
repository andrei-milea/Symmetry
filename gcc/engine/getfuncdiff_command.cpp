#include "getfuncdiff_command.h"

namespace engine
{

void cGetFuncDiffCommand::Execute()
{
	std::stringstream redirectstream;
	std::streambuf* oldbuf = std::cout.rdbuf(redirectstream.rdbuf());
	auto vars = m_FuncExpr.getVariables();
	if(vars.size() <= 1)
	{
		m_Result = "derivative: <br/>";
		cFuncExpr derivative = m_FuncExpr.derivative();
		std::cout << "$ " << derivative << " $";
		m_Result += redirectstream.str();
	}
	else
	{
		m_Result = "partial derivatives: <br/>";
		for(auto var : vars)
		{
			cFuncExpr part_deriv = m_FuncExpr.partial_derivative(var);
			std::cout << "$ \\frac{\\partial f}{\\partial " << var <<"} = " << part_deriv << " $" << "<br/>";
		}
		m_Result += redirectstream.str();
	}

	//put back the old stream buffer
	std::cout.rdbuf(oldbuf);
}

unsigned int cGetFuncDiffCommand::EstimateRunTime(const cEstimator &estimator)const
{
	return 1;
}


}
