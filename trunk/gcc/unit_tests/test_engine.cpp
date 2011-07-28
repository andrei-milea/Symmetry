
#include "../engine/session.h"
#include "../engine/getelem_command.h"
#include "../engine/getsubgrp_command.h"

#define BOOST_TEST_MODULE "test_engine"
#include "boost/test/included/unit_test.hpp"

using namespace boost::unit_test;

typedef cGroupElem< cPermElem, Multiplication> SymmetricGrpGen;

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

BOOST_FIXTURE_TEST_SUITE(test_session, cSessionFix)////////////////////////////////////////

BOOST_AUTO_TEST_CASE(ExecuteGetElemTest)
{
	std::string command_txt("SYMMETRIC_GROUP {1,2,3} {1,3,2} {3,2,1}");
	cGetElemCommand command(command_txt);
	//m_Session.RunCommand(&command);
};

BOOST_AUTO_TEST_SUITE_END()////////////////////////////////////////////////////


BOOST_AUTO_TEST_SUITE(test_infrastructure)/////////////////////////////////////

BOOST_AUTO_TEST_CASE(test_thread_pool_basic)
{
	cThreadPool	threadPool(20);
	BOOST_ASSERT(false == threadPool.isStarted());
	threadPool.StartPool();
	BOOST_ASSERT(true == threadPool.isStarted());
	threadPool.StopPool();
	BOOST_ASSERT(false == threadPool.isStarted());
}

BOOST_AUTO_TEST_SUITE_END()////////////////////////////////////////////////////


BOOST_AUTO_TEST_SUITE(test_command)////////////////////////////////////////////

BOOST_AUTO_TEST_CASE(test_command_getelem)
{
	std::string command_txt("SYMMETRIC_GROUP {1,2,3} {1,3,2} {3,2,1}");
	cGetElemCommand command(command_txt);
	//TODO
}

BOOST_AUTO_TEST_CASE(test_command_getsubgroup)
{
	std::string command_txt("SYMMETRIC_GROUP {1,2,3} {1,3,2} {3,2,1}");
	//cGetSubgroupCommand command(command_txt)
	//TODO
}

BOOST_AUTO_TEST_CASE(test_command_parsing)
{
	cPermElem s1({1,2,3});
	cPermElem s2({1,3,2});
	cPermElem s3({3,2,1});
	cGroupElem< cPermElem, Multiplication> elem1(s1);
	cGroupElem< cPermElem, Multiplication> elem2(s2);
	cGroupElem< cPermElem, Multiplication> elem3(s3);
	std::vector< SymmetricGrpGen >  generators;
	generators.push_back(elem1);
	generators.push_back(elem2);
	generators.push_back(elem3);

	std::string command_txt("SYMMETRIC_GROUP {1,2,3} {1,3,2} {3,2,1}");
	cGetElemCommand command(command_txt);
	std::vector<boost::any> parsed_generators = command.GetGenerators();

	BOOST_ASSERT(SYMMETRIC_GROUP == command.GetGroupType());
	for(unsigned int i = 0; i < parsed_generators.size(); i++)
	{
		SymmetricGrpGen generator = boost::any_cast<SymmetricGrpGen>(parsed_generators[i]);
		BOOST_ASSERT(generator == generators[i]);
	}
}

BOOST_AUTO_TEST_SUITE_END()//////////////////////////////////////////////////


