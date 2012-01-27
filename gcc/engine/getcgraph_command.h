#ifndef _GETCGRAPH_COMMAND_H
#define _GETCGRAPH_COMMAND_H

#include "groupgen_command.h"

namespace engine
{

class cEstimator;

/*!
  command that obtains Cayley graph of the group
*/
class cGetCGraphCommand : public cGroupGenCommand
{
public:
	cGetCGraphCommand(const std::string &params, cResult *result);
	virtual ~cGetCGraphCommand();

	void Execute();
	unsigned int EstimateRunTime(const cEstimator &estimator)const;
};

}

#endif

