
#include "../engine/session.h"
#include "../engine/command_creator.h"

#define BOOST_TEST_MODULE "test_engine"
#include "boost/test/included/unit_test.hpp"

using namespace boost::unit_test;
using namespace engine;

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
	std::string command_txt("SYMMETRIC_GROUP(1,2,3)(1,3,2)(3,2,1)");

	boost::shared_ptr<cCommand> command(cCommandCreator::GetCommand(
									GET_ELEMENTS, command_txt));
	command->Execute();
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

BOOST_AUTO_TEST_CASE(test_command_queue)
{
	cCommandQueue commad_queue;
	BOOST_ASSERT(commad_queue.Empty());
	for(unsigned int i = 1; i<= 100; i++)
	{
		boost::shared_ptr<cCommand> command(cCommandCreator::GetCommand(
									GET_ELEMENTS, "SYMMETRIC_GROUP(1,2,3)(1,3,2)(3,2,1)"));
		commad_queue.Put(command);
		BOOST_ASSERT(commad_queue.GetSize() == i);
	}
	BOOST_ASSERT(!commad_queue.Empty());

	for(unsigned int i = 1; i<= 100; i++)
	{
		commad_queue.Remove();
		BOOST_ASSERT(commad_queue.GetSize() == 100 - i);
	}
	BOOST_ASSERT(commad_queue.Empty());
}

BOOST_AUTO_TEST_SUITE_END()////////////////////////////////////////////////////


BOOST_AUTO_TEST_SUITE(test_command)////////////////////////////////////////////

BOOST_AUTO_TEST_CASE(test_command_getelem)
{
	boost::shared_ptr<cGroupGenCommand> command(reinterpret_cast<cGroupGenCommand*>(cCommandCreator::GetCommand(
									GET_ELEMENTS, "SYMMETRIC_GROUP(1,2,3)(1,3,2)(3,2,1)")));
	command->Execute();

	std::vector<SymmGrpElem> elements = command->GetResult();
	BOOST_ASSERT(6 == elements.size());

}

BOOST_AUTO_TEST_CASE(test_command_center)
{
	boost::shared_ptr<cCommand> command(cCommandCreator::GetCommand(
									GET_CENTER, "SYMMETRIC_GROUP(1,2,3)(1,3,2)(3,2,1)"));
	//TODO
}

BOOST_AUTO_TEST_CASE(test_command_parsing)
{
	SymmGrpElem elem1( {1,2,3});
	SymmGrpElem elem2( {1,3,2});
	SymmGrpElem elem3( {3,2,1});
	std::vector<SymmGrpElem>  generators;
	generators.push_back(elem1);
	generators.push_back(elem2);
	generators.push_back(elem3);

	boost::shared_ptr<cGroupGenCommand> command(reinterpret_cast<cGroupGenCommand*>(cCommandCreator::GetCommand(
									GET_ELEMENTS, "SYMMETRIC_GROUP(1,2,3)(1,3,2)(3,2,1)")));
	std::vector<boost::any> parsed_generators = command->GetGenerators();

	BOOST_ASSERT(SYMMETRIC_GROUP == command->GetGroupType());
	for(unsigned int i = 0; i < parsed_generators.size(); i++)
	{
		SymmetricGrpGen generator = boost::any_cast<SymmetricGrpGen>(parsed_generators[i]);
		BOOST_ASSERT(generator == generators[i]);
	}
}

BOOST_AUTO_TEST_SUITE_END()//////////////////////////////////////////////////


