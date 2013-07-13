#include "../lib/func_expr.h"
#include "../lib/trig_funcs.h"

#define BOOST_TEST_MODULE "test_functions"

#include "boost/test/included/unit_test.hpp"

using namespace boost::unit_test;

BOOST_AUTO_TEST_CASE(test_func_expr_derivative_trig)
{
	cVariable x("x");
	cFuncExpr sine_expr(Composition(), cSine<double>(), x);
	cFuncExpr cosine_expr(Composition(), cCosine<double>(), x);
	cFuncExpr function_expr(Addition(), sine_expr, cosine_expr);

	BOOST_CHECK(function_expr.derivative() == cFuncExpr(Addition(), cosine_expr,
							cFuncExpr(Multiplication(), -1.0, sine_expr)));

	cFuncExpr sine_factor(Multiplication(), 3.0, sine_expr);
	BOOST_CHECK(sine_factor.derivative() == cFuncExpr(Multiplication(), cFuncExpr(NoOp(), 3, cEmptyExpr()), cosine_expr));
	
}

BOOST_AUTO_TEST_CASE(test_func_expr_derivative_poly)
{
	cVariable y("y");
	cUnivarPolynomial<double> poly({0.1, 0.0, 3.0, 0.0, 9.0});
	cUnivarPolynomial<double> poly_deriv({0.0, 6.0, 0.0, 36.0});
	cFuncExpr poly_expr(Composition(), poly, y);
	BOOST_CHECK(poly_expr.derivative() == cFuncExpr(Composition(), poly_deriv, y));
}

BOOST_AUTO_TEST_CASE(test_func_expr_derivative_mixed)
{
}


