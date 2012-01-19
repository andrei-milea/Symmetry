#ifndef _HTTP_RESPONSE
#define _HTTP_RESPONSE

#include <string>
#include <map>
#include <boost/assign/list_of.hpp>
#include <boost/asio.hpp>

namespace http_server
{

#define HTTP_VER0 "HTTP/1.0"
#define HTTP_VER1 "HTTP/1.1"

enum STATUS_CODE
{
    OK = 200,
    ACCEPTED = 202,
    BAD_REQUEST = 400,
    NOT_FOUND = 404,
    NOT_IMPLEMENTED = 501
};

class cResponse
{
public:
	cResponse(boost::asio::streambuf& buffer);

	~cResponse()    {};

	void BuildResponse(STATUS_CODE status_code, const std::string &resource_body);

private:
	std::ostream m_ResponseStream;

public:
	static std::map<STATUS_CODE, std::string> s_StatusCodes;
};

}


#endif
