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
	cGetElemCommand(GROUP_TYPE group_type, const std::vector<boost::any> &generators);
	virtual ~cGetElemCommand();

	void Execute();
	unsigned int EstimateRunTime(const cEstimator &estimator)const;
};

}

#endif


