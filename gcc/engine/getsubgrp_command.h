#ifndef _GETSUBGRP_COMMAND_H
#define _GETSUBGRP_COMMAND_H

#include "groupgen_command.h"

namespace engine
{

class cEstimator;

/*!
  command that obtains a subgroup of the group based on the received parameters
  i.e. GetCenter
*/
class cGetSubgrpCommand : public cGroupGenCommand
{
public:
	cGetSubgrpCommand(const std::string &params, cResult *result);
	virtual ~cGetSubgrpCommand();

	void Execute();
	unsigned int EstimateRunTime(const cEstimator &estimator)const;
};

}

#endif

