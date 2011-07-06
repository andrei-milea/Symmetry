
#include "../engine/session.h"
#include "../engine/getelem_command.h"
#include "../engine/getsubgrp_command.h"

#define BOOST_TEST_MODULE "test_engine"
#include "boost/test/included/unit_test.hpp"

using namespace boost::unit_test;

class cSessionFix
{
public:
	cSessionFix()
	{
		
	};
	~cSessionFix()
	{

	};

protected:
	cSession m_Session;
};

BOOST_FIXTURE_TEST_SUITE( test_session, cSessionFix)

BOOST_AUTO_TEST_CASE( ExecuteGetElemTest )
{
	std::string command_txt("SYMMETRIC_GROUP {1,2,3} {1,3,2} {3,2,1}");
	cGetElemCommand command(command_txt);
	m_Session.RunCommand(command);
};

BOOST_AUTO_TEST_SUITE_END()



