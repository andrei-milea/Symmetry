#include "../lib/func_expr.h"
#include "../lib/trig_funcs.h"

#define BOOST_TEST_MODULE "test_functions"

#include "boost/test/included/unit_test.hpp"

using namespace boost::unit_test;

BOOST_AUTO_TEST_CASE(test_func_expr_derivative_single_var)
{
	cVariable x("x");
	cVariable y("y");

	//////////////trig functions//////////////////
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
	BOOST_CHECK(comp_sin_cos.derivative() == cFuncExpr(Multiplication(),
				cFuncExpr(Composition(), cCosine<double>(),
				cFuncExpr(Composition(), cCosine<double>(), x)),
				cFuncExpr(Multiplication(), -1.0, 
				cFuncExpr(Composition(), cSine<double>(), x))));

	//polynomial
	cUnivarPolynomial<double> poly({0.1, 0.0, 3.0, 0.0, 9.0});
	cUnivarPolynomial<double> poly_deriv({0.0, 6.0, 0.0, 36.0});
	cFuncExpr poly_expr(Composition(), poly, y);
	BOOST_CHECK(poly_expr.derivative() == cFuncExpr(Composition(), poly_deriv, y));

	//e^x
	cFuncExpr exp(Composition(), cExponential<double>(), x);
	BOOST_CHECK(exp.derivative() == exp);

	//e^(3x+2)
	cFuncExpr exp_poly(Composition(), cExponential<double>(),cFuncExpr(Addition(), cFuncExpr(Multiplication(), 3.0, x), 2.0));
	BOOST_CHECK(exp_poly.derivative() == cFuncExpr(Multiplication(), exp_poly, 3.0));

	//e^tanx
	cFuncExpr tan_x(Composition(), cTangent<double>(), x);
	cFuncExpr cos_x(Composition(), cCosine<double>(), x);
	cFuncExpr exp_tan_x(Composition(), cExponential<double>(), tan_x);
	BOOST_CHECK(exp_tan_x.derivative() == cFuncExpr(Multiplication(), cFuncExpr(Composition(), cExponential<double>(), tan_x),
				cFuncExpr(Division(), 1.0, cFuncExpr(Multiplication(), cos_x, cos_x))));
	
	//test logarithmic differentiation -- x^(sqrt(x))
	cFuncExpr sqrt_x(Power(), x, 1.0/2.0);
	cFuncExpr min_sqrt_x(Power(), x, -1.0/2.0);
	cFuncExpr exp_sqrt(Power(), x, sqrt_x);
	BOOST_CHECK(exp_sqrt.derivative() == cFuncExpr(Multiplication(), exp_sqrt,
				cFuncExpr(Addition(), cFuncExpr(Multiplication(), cFuncExpr(Composition(), cLogarithm<double>(), x), 
						cFuncExpr(Multiplication(), 0.5, min_sqrt_x)), cFuncExpr(Multiplication(), sqrt_x,
							cFuncExpr(Division(), 1.0, x)))));
}

BOOST_AUTO_TEST_CASE(test_func_expr_derivative_multi_var)
{
	cVariable x("x");
	cVariable y("y");

	//x*y
	cFuncExpr x_y(Multiplication(), x, y);
	BOOST_CHECK(x_y.partial_derivative(x) == cFuncExpr(NoOp(), y, cEmptyExpr()));

	//sin(x) + cos(y)
	cFuncExpr sin_x(Composition(), cSine<double>(), x);
	cFuncExpr cos_y(Composition(), cCosine<double>(), y);
	cFuncExpr func(Addition(), sin_x, cos_y);
	BOOST_CHECK(func.partial_derivative(x) == cFuncExpr(Composition(), cCosine<double>(), x));
	BOOST_CHECK(func.partial_derivative(y) == cFuncExpr(Multiplication(), -1.0, cFuncExpr(Composition(), cSine<double>(), y)));

	//sin(x/(1+y))
	cFuncExpr sine(Composition(), cSine<double>(), cFuncExpr(Division(), x, cFuncExpr(Addition(), 1.0, y)));
	BOOST_CHECK(sine.partial_derivative(x) == cFuncExpr(Multiplication(),
			  		 	cFuncExpr(Composition(), cCosine<double>(), cFuncExpr(Division(), x, cFuncExpr(Addition(), 1.0, y))),
						cFuncExpr(Division(), cFuncExpr(Addition(), 1.0, y),
									cFuncExpr(Multiplication(), cFuncExpr(Addition(), 1.0, y), cFuncExpr(Addition(), 1.0, y)))));

	//e^x * syn(y)
	cFuncExpr exp(Multiplication(), cFuncExpr(Composition(), cExponential<double>(), x), 
					cFuncExpr(Composition(), cSine<double>(), y));
	BOOST_CHECK(exp.partial_derivative(x) == cFuncExpr(Multiplication(), cFuncExpr(Composition(), cSine<double>(), y), 
					cFuncExpr(Composition(), cExponential<double>(), x)));

}



