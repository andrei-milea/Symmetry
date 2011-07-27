#include "session.h"
#include "../engine/getelem_command.h"
#include "../engine/getsubgrp_command.h"


int main()
{
	try
	{
		typedef cGroupElem< cPermElem, Multiplication> SymmetricGrpGen;
		std::string command_txt("SYMMETRIC_GROUP {1,2,3} {1,3,2}");
		cGetElemCommand command(command_txt);
		std::vector<boost::any> generators = command.GetGenerators();
		if(SYMMETRIC_GROUP == command.GetGroupType())
		{
			for(unsigned int i = 0; i < generators.size(); i++)
			{
				SymmetricGrpGen generator = boost::any_cast<SymmetricGrpGen>(generators[i]);
				std::cout<<generator;
			}
		}
		std::cout<<"great successs\n";
	}
	catch(std::exception& ex)
	{
		cLogger log(LOG_SEV_ERROR);
		log<<ex.what();
	}

//	cSession Session;
//	std::string command_txt("SYMMETRIC_GROUP {1,2,3} {1,3,2} {3,2,1}");
//	cGetElemCommand command(command_txt);
//	Session.RunCommand(command);

	return 1;
};
