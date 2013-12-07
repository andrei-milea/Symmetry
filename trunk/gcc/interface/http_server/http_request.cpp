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
#define DBL_CRLF "\r\n\r\n"

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
		("GET_CENTER", GET_CENTER)
		("GET_CGRAPH", GET_CGRAPH)
		("GET_RELATIONS", GET_RELATIONS)
		("GET_NORM", GET_NORM)
		("GET_MAT_INVERSE", GET_MAT_INVERSE)
		("GET_MAT_DETERMINANT", GET_MAT_DETERMINANT)
		("GET_MAT_RREF", GET_MAT_RREF)
		("GET_MAT_EXPR", GET_MAT_EXPR)
		("SOLVE_LINEQ_SYS", SOLVE_LINEQ_SYS)
		("APPROX_LINEQ_SYS", APPROX_LINEQ_SYS)
		("SOLVEG_LINEQ_SYS", SOLVEG_LINEQ_SYS)
		("GET_POLY_PLOT", GET_POLY_PLOT)
		("GET_POLY_ZEROS", GET_POLY_ZEROS)
		("GET_FNC_PLOT", GET_FNC_PLOT);
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

bool cRequest::ParseHeaders()
{
	std::string first_part;
	bool result =  parse(m_Headers.begin(), m_Headers.end(),
				 //grammar
				 (

	                (*(boost::spirit::ascii::char_ - lit(DBL_CRLF))
					>>DBL_CRLF>>
					*(boost::spirit::ascii::char_))
				 )
				 ///////
				 ,
				 first_part,
				 m_Command
				);
	return result;
};

bool cRequest::ParseCommand()
{
	short command_type;
	bool result =  parse(m_Command.begin(), m_Command.end(),
	                     //grammar
	                     (
	                         lit("id=")
	                         >> int_
	                         >>lit("command=") > command
	                         >>lit("param=")
	                         >(+boost::spirit::ascii::char_)
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
