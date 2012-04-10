#ifndef _GETREL_COMMAND_H
#define _GETREL_COMMAND_H

#include "groupgen_command.h"

namespace engine
{

class cEstimator;

/*!
  command that obtains Cayley graph of the group
*/
class cGetRelCommand : public cGroupGenCommand
{
public:
	cGetRelCommand(const std::string &params, cResult &result);
	virtual ~cGetRelCommand();

	void Execute();
	unsigned int EstimateRunTime(const cEstimator &estimator)const;
};

}

#endif

