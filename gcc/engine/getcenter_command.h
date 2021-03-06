#ifndef _GETCENTER_COMMAND_H
#define _GETCENTER_COMMAND_H

#include "groupgen_command.h"

namespace engine
{

class cEstimator;

/*!
  command that obtains the center of the group
*/
class cGetCenterCommand : public cGroupGenCommand
{
public:
	cGetCenterCommand(GROUP_TYPE group_type, const std::vector<boost::any> &generators);
	virtual ~cGetCenterCommand();

	void Execute();
	unsigned int EstimateRunTime(const cEstimator &estimator)const;
};

}

#endif

