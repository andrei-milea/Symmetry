#include "session.h"
#include "../engine/getelem_command.h"
#include "../engine/getsubgrp_command.h"


int main()
{
	cSession Session;
	std::string command_txt("SYMMETRIC_GROUP {1,2,3} {1,3,2} {3,2,1}");
	cGetElemCommand command(command_txt);
	Session.RunCommand(command);

};
