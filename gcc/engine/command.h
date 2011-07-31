#ifndef _COMMAND_H
#define _COMMAND_H

#include <string>
#include "estimate.h"

#define PROGRESS_START 1 
#define PROGRESS_END 1000


class cCommand
{
public:
	virtual ~cCommand()
	{
	};

	virtual void Execute()=0;
	virtual unsigned int EstimateRunTime(const cEstimator &estimator)const=0;

protected://methods
	cCommand(const std::string& params, std::string* result)
	: m_Result(result)
	{
		m_Params = params;
	};
	virtual bool ParseParams()=0;

protected://members
	std::string *m_Result;
	std::string m_Params;
};


#endif


