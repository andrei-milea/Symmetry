#define BOOST_TEST_MODULE "test_engine"
#include "boost/test/included/unit_test.hpp"

#include "../interface/http_server/http_request.h"
#include <sstream>

using namespace boost::unit_test;
using namespace http_server;


BOOST_AUTO_TEST_SUITE(test_server)/////////////////////////////////////

BOOST_AUTO_TEST_CASE(test_start_stop)
{
	//TODO -- death test
}

BOOST_AUTO_TEST_CASE(test_request)
{
	std::string command("GET /id=12command=GET_ELEMENTSparam=SYMMETRIC_GROUP{1,2,3}{2,3,1} HTTP/1.1\r\nHEADERS");
	std::stringstream input_stream(command);
	cRequest request(input_stream);
	BOOST_CHECK(request.ParseRequest());
	BOOST_CHECK(request.ParseResource());
	BOOST_CHECK(12 == request.GetSessionId());
	BOOST_CHECK(GET_ELEMENTS == request.GetCommandId());
	BOOST_CHECK("HTTP/1.1" == request.GetVersion());
}

BOOST_AUTO_TEST_SUITE_END()////////////////////////////////////////////////////


