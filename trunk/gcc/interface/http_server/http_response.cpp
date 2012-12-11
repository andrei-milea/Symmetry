#include "http_response.h"

namespace http_server
{

std::map<STATUS_CODE, std::string> cResponse::s_StatusCodes = boost::assign::map_list_of
        (OK,"200 OK")
        (ACCEPTED, "202 Accepted")
        (BAD_REQUEST, "400 Bad Request")
        (NOT_FOUND, "404 Not Found")
        (NOT_IMPLEMENTED, "501 Not Implemented");

cResponse::cResponse(boost::asio::streambuf& buffer)
	:m_ResponseStream(&buffer)
{

};

void cResponse::BuildResponse(STATUS_CODE status_code, const std::string &resource_body, const std::string resource_type)
{
	//add status line
	m_ResponseStream << HTTP_VER1 << cResponse::s_StatusCodes[status_code] << "\r\n";
	switch(status_code)
	{
	case OK:
		//add header
		m_ResponseStream << "Content-Type:";
		m_ResponseStream << resource_type << "\r\n";
		m_ResponseStream << (resource_body.empty() ? "" : "Content-Length:");
		m_ResponseStream << resource_body.length() << "\r\n";
		//add body
		m_ResponseStream << "\r\n" << resource_body;
		break;
	case ACCEPTED:

	case NOT_FOUND:
		m_ResponseStream << resource_body.length() << "Error\r\n";
		break;
	case NOT_IMPLEMENTED:
	default:
		break;

		//
	}
};


}

