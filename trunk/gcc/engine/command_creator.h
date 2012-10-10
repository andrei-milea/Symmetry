#ifndef _COMMAND_CREATOR_H
#define _COMMAND_CREATOR_H

#include "getelem_command.h"
#include "getcenter_command.h"
#include "getcgraph_command.h"
#include "getrel_command.h"

#include <boost/shared_ptr.hpp>

namespace engine
{

enum COMMAND_TYPE
{
    NULL_COMMAND = 0,
    GET_ELEMENTS,
    GET_CENTER,
    GET_CGRAPH,
	GET_RELATIONS
};

/*!
  implements the command creation using a variant of Factory method
*/
class cCommandCreator
{
public:
	static cCommand *GetCommand(COMMAND_TYPE command, const std::string& param)
	{
		cCommand *pcommand;
		if(cCommandCreator::isGroupCommand(command))
		{
			cParamGrpGenParser GenParamParser(param);
			GenParamParser.ParseParams();
			if(GET_ELEMENTS == command)
				pcommand = new cGetElemCommand(GenParamParser.GetGroupType(), GenParamParser.GetGenerators());
			else if(GET_CENTER == command)
				pcommand = new cGetCenterCommand(GenParamParser.GetGroupType(), GenParamParser.GetGenerators());
			else if(GET_CGRAPH == command)
				pcommand = new cGetCGraphCommand(GenParamParser.GetGroupType(), GenParamParser.GetGenerators());
			else if(GET_RELATIONS)
				pcommand = new cGetRelCommand(GenParamParser.GetGroupType(), GenParamParser.GetGenerators());
		}

		return pcommand;
	};
private:
	static bool isGroupCommand(COMMAND_TYPE command)
	{
		return (command>4) ? false : true;
	}
};

}

#endif

