#ifndef _LINALG_PARSER_H
#define _LINALG_PARSER_H

#include "command.h"
#include "logger.h"

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

namespace engine
{

namespace qi = boost::spirit::qi;
namespace ascii = boost::spirit::ascii;
namespace phoenix = boost::phoenix;
using qi::debug;

enum Operation
{
	ADDITION = 0,
	SUBTRACTION,
	MULTIPLICATION
};


/*!
  structures used to represent the expression
*/

struct sLinExpression;


struct cMatrix
{
	std::vector<double> elements;
	std::size_t rows_no;
};

typedef boost::variant<cMatrix, double, boost::recursive_wrapper<sLinExpression> > FactorVariant;

struct sLinFactor
{
	FactorVariant factor;
};

struct sLinTerm
{
	std::vector<sLinFactor> factors;
	std::vector<Operation> operations;
};

struct sLinExpression
{
	std::vector<sLinTerm> terms;
	std::vector<Operation> operations;
};

}

BOOST_FUSION_ADAPT_STRUCT(
						engine::cMatrix,
						(std::vector<double>, elements)
						(std::size_t, rows_no));

BOOST_FUSION_ADAPT_STRUCT(
						engine::sLinFactor,
						(engine::FactorVariant, factor));

BOOST_FUSION_ADAPT_STRUCT(
						engine::sLinTerm,
						(std::vector<engine::sLinFactor>, factors)
						(std::vector<engine::Operation>, operations));

BOOST_FUSION_ADAPT_STRUCT(
						engine::sLinExpression, 
						(std::vector<engine::sLinTerm>, terms)
						(std::vector<engine::Operation>, operations));

namespace engine
{

/*!
  matrix expression(linear combination) grammar
*/
template <typename Iterator>
struct lin_expr_grammar : qi::grammar<Iterator, sLinExpression(), ascii::space_type>
{
	lin_expr_grammar()
		:lin_expr_grammar::base_type(expression)
	{
		using phoenix::at_c;
		using phoenix::push_back;
		using qi::lit;
		using qi::lexeme;
		using qi::eps;
		using boost::spirit::qi::_1;
		using namespace qi::labels;

		qi::double_type double_;

		expression = 	term 						[push_back(at_c<0>(_val), _1)] >>		
						*( 	(lit('+') 					[push_back(at_c<1>(_val), ADDITION)] >>
							term					[push_back(at_c<0>(_val), _1)]) 
							|(lit('-')					[push_back(at_c<1>(_val), SUBTRACTION)] >>
							term					[push_back(at_c<0>(_val), _1)])
						 );


		term = 			factor  					[push_back(at_c<0>(_val), _1)] >>
						*(	(lit('*')					[push_back(at_c<1>(_val), MULTIPLICATION)] >>
						factor						[push_back(at_c<0>(_val), _1)])
						);


		factor = 		matrix						[at_c<0>(_val) = _1]
						| double_					[at_c<0>(_val) = _1]
						| lit("\\left(") >> 
						expression					[at_c<0>(_val) = _1] >>
						lit("\\right)");


		matrix =		lit("\\begin{bmatrix}") 		[_a = 1] >>
						*(	
							double_						[push_back(at_c<0>(_val), _1)]		
							|('&' >> double_			[push_back(at_c<0>(_val), _1)])
							|(lit("\\\\")				[_a++] >>
							double_						[push_back(at_c<0>(_val), _1)])) >>
						lit("\\end{bmatrix}")			[at_c<1>(_val) = _a];

		expression.name("expression");
		term.name("term");
		factor.name("factor");
		matrix.name("matrix");

//////////////debug info
/////////////////////////////
//		debug(expression);
//		debug(term);
//		debug(factor);
//		debug(matrix);
/////////////////////////////
/////////////////////////////
	};

	qi::rule<Iterator, sLinExpression(), ascii::space_type> expression;
	qi::rule<Iterator, sLinTerm(), ascii::space_type> term;
	qi::rule<Iterator, sLinFactor(), ascii::space_type> factor;
	qi::rule<Iterator, cMatrix(), qi::locals<std::size_t>, ascii::space_type> matrix;
	
};



class cLinAlgParser
{
public:
	cLinAlgParser(const std::string& params)
		:m_Params(params)
	{};

	const sLinExpression& GetLinExpression()const
	{	return m_LinExpression;	 };

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

		bool result = qi::phrase_parse(iter, m_Params.end(), expr_grammar, space, m_LinExpression);

		if(false == result)
			throw std::runtime_error(CONTEXT_STR + " Failed to parse expression. Invalid latex syntax.");
	};

private:
	std::string m_Params;
	sLinExpression m_LinExpression;

};

}

#endif

