
#include "getpolyzeros_command.h"

namespace engine
{


void cGetPolyZerosCommand::Execute()
{
	if(0 == m_Poly.size())
		throw std::runtime_error("Invalid input: zero polynomial.");
	m_Result = m_Poly.realZeros();
}

unsigned int cGetPolyZerosCommand::EstimateRunTime(const cEstimator &estimator)const
{
	return 1;
}



}
