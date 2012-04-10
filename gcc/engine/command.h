#ifndef _COMMAND_H
#define _COMMAND_H

#include <string>
#include "estimate.h"


/*!
 base class for commands (Command design pattern)
 COMMAND_TYPE = GET_ELEMENTS | GET_CENTER | GET_CGRAPH | GET_RELATIONS
*/
namespace engine
{

class cResult;

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

protected://methods
	cCommand(const std::string& params, cResult& result)
		: m_Result(result)
	{
		m_Params = params;
	};


	/*!
	  parses the command parameters using BOOST SPIRIT
	*/
	virtual bool ParseParams()=0;

protected://members
	cResult &m_Result;
	std::string m_Params;
};

}

#endif


