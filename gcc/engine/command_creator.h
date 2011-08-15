#ifndef _COMMAND_CREATOR_H
#define _COMMAND_CREATOR_H

#include "getelem_command.h"
#include "getsubgrp_command.h"

#include <boost/shared_ptr.hpp>

namespace engine
{

enum COMMAND_TYPE
{
	NULL_COMMAND = 0,
	GET_ELEMENTS,
	GET_NORMALIZER,
	GET_CENTER,
	GET_CENTRALIZER
};


class cCreator
{
public:
	static cCommand *GetCommand(COMMAND_TYPE command, const std::string& param, cResult* result)
	{
		if(GET_ELEMENTS == command)
			return new cGetElemCommand(param, result);
		else if(GET_NORMALIZER == command)
			return new cGetSubgrpCommand(param, result);
		return NULL;
	};
};

//TODO
//class cPoolCreator
//{
//
//};

template <typename CREATOR>
class cCommandCreator : CREATOR
{
public:
	static cCommand* GetCommand(COMMAND_TYPE command, const std::string &param, cResult *result)
	{
		return CREATOR::GetCommand(command, param, result);
	};
};

}

#endif

