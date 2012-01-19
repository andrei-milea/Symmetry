#ifndef _HTTP_REQUEST
#define _HTTP_REQUEST

#include <string>
#include "http_header.h"
#include "../../engine/command_creator.h"


#include <boost/spirit/include/support_multi_pass.hpp>

namespace http_server
{

using namespace engine;

enum REQ_METHOD
{
    INDETERMINATE_M = 0,
    GET_M,
    POST_M,
    HEAD_M,
    PUT_M,
    OPTIONS_M,
    DELETE_M,
    TRACE_M,
    CONNECT_M
};



class cRequest
{
	typedef std::istreambuf_iterator<char> base_iterator_type;
	typedef boost::spirit::multi_pass<base_iterator_type> forward_iterator_type;

public:
	cRequest(std::istream &stream);
	~cRequest() {};

	bool ParseRequest();
	bool ParseResource();
	std::vector<cHeader*> ParseHeaders();

	REQ_METHOD				GetMethod()const
	{
		return m_Method;
	};

	const std::string&		GetResource()const
	{
		return m_Resource;
	};

	const std::string&		GetVersion()const
	{
		return m_Version;
	};

	COMMAND_TYPE			GetCommandId()const
	{
		return m_CommandId;
	}

	const std::string&		GetParam()const
	{
		return m_Param;
	}

	const unsigned int		GetSessionId()const
	{
		return m_SessionId;
	};


private:
	REQ_METHOD                      m_Method;
	std::string                     m_Resource;
	std::string                     m_Version;
	std::string                     m_Headers;
	COMMAND_TYPE					m_CommandId;
	std::string						m_Param;
	unsigned int					m_SessionId;

	//stream iterators
	forward_iterator_type           m_Fwd_begin;
	forward_iterator_type           m_Fwd_end;

};

}

#endif
