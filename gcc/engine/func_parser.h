#ifndef _FUNC_PARSER_H
#define _FUNC_PARSER_H

#include "command.h"
#include "logger.h"
#include "../lib/func_expr.h"

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>
#include <boost/spirit/include/phoenix_fusion.hpp>
#include <boost/spirit/include/classic_core.hpp>
#include <boost/variant/recursive_variant.hpp>
#include <boost/fusion/adapted/struct/adapt_struct.hpp>
#include <boost/fusion/include/adapt_struct.hpp>

#include <exception>

/*!
  structures used to represent the expression
*/

BOOST_FUSION_ADAPT_CLASS(cFuncExpr,
	(operation_type, operation_type, obj.getOperation(), obj.setOperation(val))
	(expr_type, expr_type, obj.getLHSExpression(), obj.setLHSExpression(val))
	(expr_type, expr_type, obj.getRHSExpression(), obj.setRHSExpression(val)));


namespace engine
{

/*!
 * grammar for parsing a functional expression 
*/
template <typename Iterator>
struct func_expr_grammar : qi::grammar<Iterator, sFuncExpression(), ascii::space_type>
{
	func_expr_grammar()
		:func_expr_grammar::base_type(expression)
	{
		using phoenix::at_c;
		using phoenix::push_back;
		using qi::lit;
		using qi::lexeme;
		using qi::eps;
		using boost::spirit::qi::_1;
		using namespace qi::labels;


		expression = 	term 						[at_c<0>(_val) = _1] >>		
							(lit('+') 					[at_c<1>(_val) = Addition()] >>
							term					[at_c<2>(_val) = _1]) 
							|(lit('-')					[at_c<1>(_val) = Subtraction()] >>
							term					[at_c<2>(_val) = _1])
							|(lit('*')					[at_c<1>(_val) = Multiplication()] >>
							term					[at_c<2>(_val) = _1])
							|(lit('/')					[at_c<1>(_val) = Division()] >>
							term					[at_c<2>(_val) = _1])
							|(lit('^')					[at_c<1>(_val) = Power()] >>
							term					[at_c<2>(_val) = _1])
							|term					[at_c<1>(_val) = Composition(), at_c<2>(_val) = _1];


		 term =			| double_					[_val = _1]
					   	| function 					[_val = _1]
		 				| char_('a', 'z')			[_val = cVariable(_1)]
						| expression
						|char_('(') >> expression >> char_(')');

		function =		lit("sin")					[_val = cSine<double>()]
						|lit("asin")				[_val = cAsine<double>()]
						|lit("sine")				[_val = cSine<double>()]
						|lit("asine")				[_val = cAsine<double>()]
						|lit("cos")					[_val = cCosine<double>()]
						|lit("acos")				[_val = cAcosine<double>()]
						|lit("cosine")				[_val = cCosine<double>()]
						|lit("acosine")				[_val = cAcosine<double>()]
						|lit("tan")					[_val = cTangent<double>()]
						|lit("atan")				[_val = cAtangent<double>()]
						|lit("tangent")				[_val = cTangent<double>()]
						|lit("atangent")			[_val = cAtangent<double>()]
						|lit("cotan")				[_val = cCotangent<double>()]
						|lit("acotan")				[_val = cAcotangent<double>()]
						|lit("cotangent")			[_val = cCotangent<double>()]
						|lit("acotangent")			[_val = cAcotangent<double>()]
						|lit('e')					[_val = cExponential<double>()]
						|lit("exp")					[_val = cExponential<double>()]
						|lit("log")					[_val = cLogarithm<double>()]
						|lit("abs")					[_val = cAbsVal<double>()];


		expression.name("expression");
		term.name("term");
		function.name("function");

//////////////debug info
/////////////////////////////
//		debug(expression);
//		debug(term);
//		debug(factor);
//		debug(matrix);
/////////////////////////////
/////////////////////////////
	};

	qi::rule<Iterator, cFuncExpr(), ascii::space_type> expression;
	qi::rule<Iterator, expr_type(), ascii::space_type> term;
	qi::rule<Iterator, operation_type(), ascii::space_type> operation;
	
};



class cFuncExprParser
{
public:
	cFuncExprParser(const std::string& params)
		:m_Params(params)
	{};

	const cFuncExpr& GetFuncExpr()const
	{
		return m_FuncExpr;	 
	};

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
		lin_expr_grammar<std::string::iterator> expr_grammar;

		BOOST_SPIRIT_DEBUG_GRAMMAR(expr_grammar);

		bool result = qi::phrase_parse(iter, m_Params.end(), expr_grammar, space, m_FuncExpr);

		if(false == result)
			throw std::runtime_error(CONTEXT_STR + " Failed to parse expression. Invalid function entered.");
	};

private:
	std::string m_Params;
	sFuncExpr m_FuncExpr;

};

}

#endif

