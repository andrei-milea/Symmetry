#include "../lib/func_expr.h"
#include "../lib/trig_funcs.h"

#define BOOST_TEST_MODULE "test_functions"

#include "boost/test/included/unit_test.hpp"

using namespace boost::unit_test;

BOOST_AUTO_TEST_CASE(test_func_expr_derivative_trig)
{

	//////////////single variable//////////////////
	cVariable x("x");
	cFuncExpr sine_expr(Composition(), cSine<double>(), x);
	cFuncExpr cosine_expr(Composition(), cCosine<double>(), x);
	cFuncExpr function_expr(Addition(), sine_expr, cosine_expr);

	BOOST_CHECK(function_expr.derivative() == cFuncExpr(Addition(), cosine_expr,
							cFuncExpr(Multiplication(), -1.0, sine_expr)));
	
	cFuncExpr sine_factor(Multiplication(), 3.0, sine_expr);
	BOOST_CHECK(sine_factor.derivative() == cFuncExpr(Multiplication(), cFuncExpr(NoOp(), 3, cEmptyExpr()), cosine_expr));

	cFuncExpr power_sum(Power(), sine_factor, 5);
	BOOST_CHECK(power_sum.derivative() == cFuncExpr(Multiplication(),
			   	cFuncExpr(Multiplication(), 5, cFuncExpr(Power(), sine_factor, 4)),
			   	cFuncExpr(Multiplication(), 3, cosine_expr)));

	cFuncExpr comp_sin_cos(Composition(), cSine<double>(), cFuncExpr(Composition(), cCosine<double>(), x));
	comp_sin_cos.derivative();

//	cFuncExpr tan1(Division(), sine_expr, cosine_expr);
//	cFuncExpr tan2(Composition(), cTangent<double>(), x);
//	std::cout << "\naaa\n";
//	BOOST_CHECK(tan1.derivative() == tan2.derivative());


//	cFuncExpr tan_expr(Composition(), cTangent<double>(), x);
//	cFuncExpr fct(Division(), cFuncExpr(Division(), 1.0, cosine_expr), cFuncExpr(Addition(), 1.0, tan_expr));
//	std::cout << "\n derivata: " << fct.derivative() << " end";

//	fct.derivative().printTree();
//	std::cout << "\ntangent1 deriv " << tan1.derivative() << " end";
//	std::cout << "\ntangent2 deriv " << tan2.derivative() << " end";

/////////////////////////////////////////////////////////////////////

}

BOOST_AUTO_TEST_CASE(test_func_expr_derivative_poly)
{
	cVariable y("y");
	cUnivarPolynomial<double> poly({0.1, 0.0, 3.0, 0.0, 9.0});
	cUnivarPolynomial<double> poly_deriv({0.0, 6.0, 0.0, 36.0});
	cFuncExpr poly_expr(Composition(), poly, y);
	BOOST_CHECK(poly_expr.derivative() == cFuncExpr(Composition(), poly_deriv, y));
}

BOOST_AUTO_TEST_CASE(test_func_expr_derivative_log)
{
	cVariable x("x");

	cFuncExpr exp(Composition(), cExponential<double>(), x);
	BOOST_CHECK(exp.derivative() == exp);

	cFuncExpr poly(Addition(), cFuncExpr(Multiplication(), 3.0, x), 2.0);
	cFuncExpr exp_poly(Composition(), cExponential<double>(), poly);
	BOOST_CHECK(exp_poly.derivative() == cFuncExpr(Multiplication(), exp_poly, 3.0));
}

BOOST_AUTO_TEST_CASE(test_func_expr_derivative_mixed)
{
}


