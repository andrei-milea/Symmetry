#include "session.h"
#include "getelem_command.h"
#include "getsubgrp_command.h"
#include "serializer.h"


int main()
{
	try
	{
		cSerializer<SymmGrpElem> symm_grp_serializer;

		//basic test with s3
		SymmGrpElem elem1({1,2,3});
		SymmGrpElem elem2({1,3,2});
		SymmGrpElem elem3({3,2,1});
		std::string generators_str1;
		generators_str1 += symm_grp_serializer.Stringify(elem1);
		generators_str1 += symm_grp_serializer.Stringify(elem2);
		generators_str1 += symm_grp_serializer.Stringify(elem3);
		std::vector< SymmGrpElem >  generators;
		generators.push_back(elem1);
		generators.push_back(elem2);
		generators.push_back(elem3);
		std::string generators_str = symm_grp_serializer.Stringify(generators);

		std::string generator_str_hardcoded;

		generator_str_hardcoded += "\n1 2 3\n";
		generator_str_hardcoded += "1 2 3\n\n";

		generator_str_hardcoded += "1 2 3\n";
		generator_str_hardcoded += "1 3 2\n\n";

		generator_str_hardcoded += "1 2 3\n";
		generator_str_hardcoded += "3 2 1\n";



		std::cout<<"Generators: "<<generators_str<<"\n";
		std::cout<<"Generator 1by1: "<<generators_str<<"\n";
		std::cout<<"Generators hardcoded: "<<generator_str_hardcoded<<"\n";
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
