#ifndef _GETELEM_COMMAND_H
#define _GETELEM_COMMAND_H

#include "groupgen_command.h"

namespace engine
{

class cEstimator;

/*!
  implements the Get Group Elements command
  by default uses the Dimino algorithm
*/
class cGetElemCommand : public cGroupGenCommand
{
public:
	cGetElemCommand(const std::string &params, cResult* result);
	virtual ~cGetElemCommand();

	void Execute();
	unsigned int EstimateRunTime(const cEstimator &estimator)const;
};

}

#endif


