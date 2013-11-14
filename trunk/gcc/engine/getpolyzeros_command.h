#ifndef _GETPOLYZEROS_COMMAND_H
#define _GETPOLYZEROS_COMMAND_H

#include "command.h"
#include "poly_parser.h"

#include "../lib/univar_polynomial.h"

#include <vector>

namespace engine
{

class cGetPolyZerosCommand : public cCommand
{
public:
	cGetPolyZerosCommand(const std::vector<double> &poly)
		:m_Poly(poly)
	{
	}
	~cGetPolyZerosCommand(){}
	
	void Execute();

	unsigned int EstimateRunTime(const cEstimator &estimator)const;

	const std::vector<double>& GetResult()const
	{
		return m_Result;
	}

private:
	cUnivarPolynomial<double> m_Poly;
	std::vector<double> m_Result;
};

}


#endif

