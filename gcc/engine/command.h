#ifndef _COMMAND_H
#define _COMMAND_H

#include <string>
#include "estimate.h"
#include "result.h"

//COMMAND_TYPE = GET_ELEMENTS | GET_NORMALIZER | GET_CENTER | GET_CENTRALIZER


class cCommand
{
public:
	virtual ~cCommand()
	{
	};

	virtual void Execute()=0;
	virtual unsigned int EstimateRunTime(const cEstimator &estimator)const=0;

protected://methods
	cCommand(const std::string& params, cResult* result)
	: m_Result(result)
	{
		m_Params = params;
	};
	virtual bool ParseParams()=0;

protected://members
	cResult *m_Result;
	std::string m_Params;
};


#endif


