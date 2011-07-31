#ifndef _GETELEM_COMMAND_H
#define _GETELEM_COMMAND_H

#include "groupgen_command.h"

class cEstimator;

class cGetElemCommand : public cGroupGenCommand 
{
public:
	cGetElemCommand(const std::string &params, std::string* result);
	virtual ~cGetElemCommand();

	void Execute();
	unsigned int EstimateRunTime(const cEstimator &estimator)const;
};


#endif


