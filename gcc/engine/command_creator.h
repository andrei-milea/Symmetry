#ifndef _COMMAND_CREATOR_H
#define _COMMAND_CREATOR_H

#include "getelem_command.h"
#include "getcenter_command.h"
#include "getcgraph_command.h"

#include <boost/shared_ptr.hpp>

namespace engine
{

enum COMMAND_TYPE
{
    NULL_COMMAND = 0,
    GET_ELEMENTS,
    GET_CENTER,
    GET_CGRAPH
};


/*!
  implements the default command creation strategy
*/
class cCreator
{
public:
	static cCommand *GetCommand(COMMAND_TYPE command, const std::string& param, cResult& result)
	{
		cCommand *pcommand;
		if(GET_ELEMENTS == command)
			pcommand = new cGetElemCommand(param, result);
		else if(GET_CENTER == command)
			pcommand = new cGetCenterCommand(param, result);
		else if(GET_CGRAPH == command)
			pcommand = new cGetCGraphCommand(param, result);
		//result->SetCommand(pcommand);

		return pcommand;
	};
};

//TODO
//class cPoolCreator
//{
//
//};

/*!
  instantiates a given command (builder pattern)
  using different creation policies(strategy pattern)
  by default should be instantiated with cCreator class
*/
template <typename CREATOR>
class cCommandCreator : CREATOR
{
public:
	static cCommand* GetCommand(COMMAND_TYPE command, const std::string &param, cResult &result)
	{
		return CREATOR::GetCommand(command, param, result);
	};
};

}

#endif

