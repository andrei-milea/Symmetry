#ifndef _GETPOLYPLOT_COMMAND_H
#define _GETPOLYPLOT_COMMAND_H

#include "command.h"
#include "poly_parser.h"

#include "../lib/univar_polynomial.h"

#include <vector>
#include <utility>

namespace engine
{

class cGetPolyPlotCommand : public cCommand
{
public:
	cGetPolyPlotCommand(const std::vector<double> &poly)
		:m_Poly(poly)
	{
	}
	~cGetPolyPlotCommand(){}
	
	void Execute();

	unsigned int EstimateRunTime(const cEstimator &estimator)const;

	const std::vector<std::pair<double,double> >& GetResult()const
	{
		return m_Result;
	}

private:
	cUnivarPolynomial<double> m_Poly;
	std::vector<std::pair<double,double> > m_Result;
};

}


#endif

