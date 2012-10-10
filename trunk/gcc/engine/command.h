#ifndef _COMMAND_H
#define _COMMAND_H

#include <string>
#include "estimate.h"


/*!
 base class for commands (Command design pattern)
*/
namespace engine
{

class cCommand
{
public:
	virtual ~cCommand()
	{
	};

	virtual void Execute()=0;

	/*!
	  uses the visitor based on cEstimator to return a rough estimation
	  of the running time of a given command
	*/
	virtual unsigned int EstimateRunTime(const cEstimator &estimator)const=0;
};

}

#endif


