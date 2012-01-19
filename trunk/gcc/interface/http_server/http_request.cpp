#include "http_request.h"

/************************************************************/
/********************REQUEST PARSER TOOLS********************/
/************************************************************/

#include <boost/asio.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>

namespace http_server
{

using boost::spirit::qi::parse;
using namespace boost::spirit;
using namespace boost::spirit::qi;
using namespace boost::spirit::ascii;

/**************http request grammar rules**************/
//METHOD_TYPE	= GET | POST | HEAD | PUT | OPTIONS
//				| DELETE | TRACE | CONNECT
//
//
//HTTP_REQUEST	= METHOD_TYPE >> " " >> RESOURCE >>
//				>> " " >> VERSION >> "\r" >> HEADER >>
//				>> "\r\n" ;

#define CRLF "\r\n"

//parsing symbol table
struct method_: symbols<char, short>
{
	method_()
	{
		add
		("GET", GET_M)
		("POST", POST_M)
		("HEAD", HEAD_M)
		("PUT", PUT_M)
		("OPTIONS", OPTIONS_M)
		("DELETE", DELETE_M)
		("TRACE", TRACE_M)
		("CONNECT", CONNECT_M);

	}
} method;

struct command_: symbols<char, short>
{
	command_()
	{
		add
		("GET_ELEMENTS", GET_ELEMENTS)
		("GET_NORMALIZER", GET_NORMALIZER)
		("GET_CENTER", GET_CENTER)
		("GET_CENTRALIZER", GET_CENTRALIZER);
	}
} command;
/************************************************************/
/************************************************************/
/************************************************************/

cRequest::cRequest(std::istream &stream)
	:m_Method(INDETERMINATE_M)
{
	base_iterator_type in_begin(stream);
	// convert input iterator to forward iterator, usable by spirit parser
	m_Fwd_begin = make_default_multi_pass(in_begin);
};

bool cRequest::ParseRequest()
{
	bool result = false;
	short method_;
	result = parse(m_Fwd_begin, m_Fwd_end,
	               /////grammar
	               (
	                   method
	                   >>' '
	                   >>(+~boost::spirit::ascii::char_(' '))
	                   >>' '
	                   >>(+~boost::spirit::ascii::char_('\r'))
	                   >>lit(CRLF)
	                   >>(*(boost::spirit::ascii::char_)))
	               //////
	               ,
	               method_,
	               m_Resource,
	               m_Version,
	               m_Headers
	              );
	m_Method = (REQ_METHOD)method_;
	return result;
};


bool cRequest::ParseResource()
{
	short command_type;
	bool result =  parse(m_Resource.begin(), m_Resource.end(),
	                     //gramar
	                     (
	                         lit("/id=")
	                         >> int_
	                         >>lit("command=") > command
	                         >>lit("param=")
	                         >(+~boost::spirit::ascii::char_(' '))
	                     )
	                     ///////
	                     ,
	                     m_SessionId,
	                     command_type,
	                     m_Param
	                    );
	m_CommandId = (COMMAND_TYPE)command_type;
	return result;
};

}
