#ifndef _COMMAND_CREATOR_H
#define _COMMAND_CREATOR_H

#include "getelem_command.h"
#include "getcenter_command.h"
#include "getcgraph_command.h"
#include "getrel_command.h"
#include "linalg_parser.h"
#include "getmatexpr_command.h"

#include <boost/shared_ptr.hpp>

namespace engine
{

enum COMMAND_TYPE
{
    NULL_COMMAND = 0,
    GET_ELEMENTS,
    GET_CENTER,
    GET_CGRAPH,
	GET_RELATIONS,
	GET_NORM,
	GET_MAT_INVERSE,
	GET_MAT_DETERMINANT,
	GET_MAT_LU,
	GET_MAT_EXPR
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
		if(command <= GET_RELATIONS)	//is group command
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
		else if(command <= GET_MAT_EXPR)
		{
			cLinAlgParser LinAlgParamParser(param);
			LinAlgParamParser.ParseParams();
			if(GET_MAT_EXPR == command)
			{
				pcommand = new cGetMatExprCommand(LinAlgParamParser.GetLinExpression());
			}
		}

		return pcommand;
	};
};

}

#endif

