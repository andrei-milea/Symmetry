#ifndef _POLY_PARSER_H
#define _POLY_PARSER_H

#include "command.h"
#include "logger.h"

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>
#include <boost/spirit/include/classic_core.hpp>

#include <exception>

namespace engine
{

namespace qi = boost::spirit::qi;
namespace ascii = boost::spirit::ascii;
namespace phoenix = boost::phoenix;

class cPolyParser
{
public:
	cPolyParser(const std::string& params)
		:m_Params(params)
	{}

	const std::vector<double>& GetPolynomial()const
	{	return m_Polynomial;	}

	void ParseParams()
	{
		using qi::uint_;
		using qi::_1;
		using qi::string;
		using phoenix::push_back;
		using phoenix::ref;
		using ascii::char_;
		using boost::spirit::ascii::space;
		qi::double_type double_;

		std::string::iterator iter = m_Params.begin();

		BOOST_SPIRIT_DEBUG_GRAMMAR(expr_grammar);

		bool result = qi::phrase_parse(iter, m_Params.end(),
				//grammar
			 	(
				double_[push_back(phoenix::ref(m_Polynomial), _1)]
				>> *(',' >> double_[push_back(phoenix::ref(m_Polynomial), _1)])
				), 
				space);

		if((false == result) || (iter != m_Params.end()))
			throw std::runtime_error(CONTEXT_STR + " Failed to parse polynomial.");

		//remove trailing zeros
		int idx = m_Polynomial.size() - 1;
		while((idx >= 0) && (m_Polynomial[idx] == 0))
		{
			idx--;
		}
		if(-1 == idx)
			throw std::runtime_error(CONTEXT_STR + " Ivalid input: Zero polynomial provided.");

		m_Polynomial = std::vector<double>(m_Polynomial.begin(), m_Polynomial.begin() + idx + 1);
	}

private:
	std::string m_Params;
	std::vector<double> m_Polynomial;

};

}

#endif

