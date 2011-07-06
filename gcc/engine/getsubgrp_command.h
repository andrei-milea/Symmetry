#ifndef _GETSUBGRP_COMMAND_H
#define _GETSUBGRP_COMMAND_H

#include "groupgen_command.h"

class cEstimator;

class cGetSubgrpCommand : public cGroupGenCommand
{
public:
	cGetSubgrpCommand(std::string &params);
	virtual ~cGetSubgrpCommand();

	std::string Execute();
	unsigned int EstimateRunTime(const cEstimator &estimator)const;
};

#endif

