#ifndef _FUNC_PARSER_H
#define _FUNC_PARSER_H

#include "command.h"
#include "logger.h"
#include "../lib/func_expr.h"

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_bind.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>
#include <boost/spirit/include/phoenix_fusion.hpp>
#include <boost/spirit/include/classic_core.hpp>
#include <boost/variant/recursive_variant.hpp>
#include <boost/spirit/include/karma.hpp>
#include <boost/fusion/adapted/adt/adapt_adt.hpp>
#include <boost/fusion/include/adapt_adt.hpp>
#include <boost/spirit/include/qi_char_.hpp>
#include <boost/lambda/construct.hpp>
#include <boost/lambda/bind.hpp>

#include <exception>

/*!
  structures used to represent the expression
*/

BOOST_FUSION_ADAPT_ADT(cFuncExpr,
	(operation_type, operation_type, obj.getOperation(), obj.setOperation(val))
	(expr_type, expr_type, obj.getLHSExpression(), obj.setLHSExpression(val))
	(expr_type, expr_type, obj.getRHSExpression(), obj.setRHSExpression(val)));


namespace engine
{

namespace qi = boost::spirit::qi;
namespace ascii = boost::spirit::ascii;
namespace phoenix = boost::phoenix;
using qi::debug;

cFuncExpr make_fnc_expr(operation_type op, cFuncExpr fnc1, cFuncExpr fnc2)
{
	return cFuncExpr(op, fnc1, fnc2);
}


/*!
 * grammar for parsing a functional expression 
*/
template <typename Iterator>
struct func_expr_grammar : qi::grammar<Iterator, cFuncExpr(), ascii::space_type>
{
	func_expr_grammar()
		:func_expr_grammar::base_type(expression)
	{
		using phoenix::at_c;
		using qi::lit;
		using qi::char_;
		using boost::spirit::qi::_1;
		using boost::spirit::qi::_2;
		using boost::spirit::karma::double_;
		using namespace qi::labels;

		expression = 	term						[_val = _1] >>		
						*((lit('+') > term			[_val = phoenix::bind(make_fnc_expr, Addition(), _val, _1)]) |
						(lit('-') > term			[_val = phoenix::bind(make_fnc_expr, Subtraction(), _val, _1)]));

		term = 			factor						[_val = _1] >>		
						*((lit('*') > factor)		[_val = phoenix::bind(make_fnc_expr, Multiplication(), _val, _1)] |
						(lit('/') > factor)			[_val = phoenix::bind(make_fnc_expr, Division(), _val, _1)] |
						(lit('^') > factor)			[_val = phoenix::bind(make_fnc_expr, Power(), _val, _1)]);


		factor =		function 					[_val = _1]
						|variable					[_val = _1]
						|double_					[_val = _1]
						|(lit('(') >
							  expression			[_val = _1] >
								  lit(')'));

		variable = 		char_('a', 'z')				[_val = _1];
		
		function =		(lit("sin")					[_val = cFuncExpr(Composition(), cSine<double>(), cEmptyExpr())]
						|lit("asin")				[_val = cFuncExpr(Composition(), cAsine<double>(), cEmptyExpr())]
						|lit("cos")					[_val = cFuncExpr(Composition(), cCosine<double>(), cEmptyExpr())]
						|lit("acos")				[_val = cFuncExpr(Composition(), cAcosine<double>(), cEmptyExpr())]
						|lit("tan")					[_val = cFuncExpr(Composition(), cTangent<double>(), cEmptyExpr())]
						|lit("atan")				[_val = cFuncExpr(Composition(), cAtangent<double>(), cEmptyExpr())]
						|lit("cotan")				[_val = cFuncExpr(Composition(), cCotangent<double>(), cEmptyExpr())]
						|lit("acotan")				[_val = cFuncExpr(Composition(), cAcotangent<double>(), cEmptyExpr())]
						|lit("exp")					[_val = cFuncExpr(Composition(), cExponential<double>(), cEmptyExpr())]
						|lit("log")					[_val = cFuncExpr(Composition(), cLogarithm<double>(), cEmptyExpr())]
						|lit("abs")					[_val = cFuncExpr(Composition(), cAbsVal<double>(), cEmptyExpr())]) >
						char_('(') > expression	[at_c<2>(_val) = _1] >> char_(')');

	};

	qi::rule<Iterator, cFuncExpr(), ascii::space_type> expression;
	qi::rule<Iterator, cFuncExpr(), ascii::space_type> term;
	qi::rule<Iterator, expr_type(), ascii::space_type> factor;
	qi::rule<Iterator, cFuncExpr(), ascii::space_type> function;
	qi::rule<Iterator, cVariable(), ascii::space_type> variable;
};



class cFuncExprParser
{
public:
	cFuncExprParser(const std::string& params)
		:m_Params(params)
	{}

	const cFuncExpr& GetFuncExpr()const
	{
		return m_FuncExpr;	 
	}

	void ParseParams()
	{
		using qi::uint_;
		using qi::_1;
		using qi::string;
		using phoenix::push_back;
		using phoenix::ref;
		using ascii::char_;
		using boost::spirit::ascii::space;


		std::string::iterator iter = m_Params.begin();
		func_expr_grammar<std::string::iterator> expr_grammar;

		BOOST_SPIRIT_DEBUG_GRAMMAR(expr_grammar);

		bool result = qi::phrase_parse(iter, m_Params.end(), expr_grammar, space, m_FuncExpr);

		if(false == result || iter != m_Params.end())
			throw std::runtime_error(CONTEXT_STR + " Failed to parse expression. Invalid function entered.");

		
		std::stringstream ss;
		std::stringstream redirectstream;
		std::streambuf* oldbuf = std::cout.rdbuf(redirectstream.rdbuf());
		std::string str;
		
		//m_FuncExpr.printTree();
		std::cout << m_FuncExpr;
		while(std::getline(redirectstream, str))
		{
			ss << str;
		}

		//put back the old stream buffer
		std::cout.rdbuf(oldbuf);

		std::string res = ss.str();

	}

private:
	std::string m_Params;
	cFuncExpr m_FuncExpr;

};

}

#endif

