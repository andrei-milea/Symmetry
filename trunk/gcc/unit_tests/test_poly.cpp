#include "../lib/univar_polynomial.h"

#define BOOST_TEST_MODULE "test_polynomial"

#include "boost/test/included/unit_test.hpp"

using namespace boost::unit_test;

BOOST_AUTO_TEST_CASE(test_division)
{
	//test1//////////////////////////////////////////////////////////
	cUnivarPolynomial<double> poly1({-1.0, 0.0, 3.0, 1.0});
	cUnivarPolynomial<double> poly2({0.0, 6.0, 3.0});
	cUnivarPolynomial<double> poly3 = poly1;

	poly1 /= poly2;
	poly3 %= poly2;

	cUnivarPolynomial<double> quotient({1.0/3.0, 1.0/3.0});
	cUnivarPolynomial<double> remainder({-1.0, -2.0});

	BOOST_CHECK(poly1 == quotient);
	BOOST_CHECK(poly3 == remainder);

	//test2///////////////////////////////////////////////////////////
	auto res_quotient = poly2 / poly2;
	std::vector<double> one_vec;
	one_vec.push_back(1.0);
	BOOST_CHECK(res_quotient == cUnivarPolynomial<double>(one_vec));

	cUnivarPolynomial<double> poly4({2.0, 4.0});
	std::vector<double> poly5_vec;
	poly5_vec.push_back(2.0);
	cUnivarPolynomial<double> poly5(poly5_vec);

	auto poly6 = poly4 / poly5;

	BOOST_CHECK(poly6 == cUnivarPolynomial<double>({1.0, 2.0}));

	//test3//////////////////////////////////////////////////////////
	cUnivarPolynomial<double> poly7({0.0, 0.0, -35.0, 21.0});
	cUnivarPolynomial<double> poly8({0.0, 7.0});

	auto poly9 = poly7 % poly8;
	auto poly10 = poly7 / poly8;

	BOOST_CHECK(poly10 == cUnivarPolynomial<double>({0.0, -5.0, 3.0}));
	BOOST_CHECK(poly9 == cUnivarPolynomial<double>::zero());

	//test4///////////////////////////////////////////////////////////
	poly7 =	cUnivarPolynomial<double>({-10.0, -9.0, 1.0});
	poly8 =	cUnivarPolynomial<double>({1.0, 1.0});
	BOOST_CHECK(poly7 / poly8 == cUnivarPolynomial<double>({-10.0, 1.0}));
	BOOST_CHECK(poly7 % poly8 == cUnivarPolynomial<double>::zero());

	//test5///////////////////////////////////////////////////////////
	poly7 =	cUnivarPolynomial<double>({-3.0, 10.0, -5.0, 3.0});
	poly8 =	cUnivarPolynomial<double>({1.0, 3.0});
	BOOST_CHECK(poly7 / poly8 == cUnivarPolynomial<double>({4.0, -2.0, 1.0}));
	std::vector<double> vec8;
	vec8.push_back(-7.0);
	BOOST_CHECK(poly7 % poly8 == cUnivarPolynomial<double>(vec8));

	//test6////////////////////////////////////////////////////////////
	poly7 =	cUnivarPolynomial<double>({2.0, 5.0, 0.0, 0.0, 0.0, 0.0, 3.0});
	poly8 =	cUnivarPolynomial<double>({1.0, 0.0, 2.0});
	BOOST_CHECK(poly7 / poly8 == cUnivarPolynomial<double>({3.0/8.0, 0.0, -3.0/4.0, 0.0, 3.0/2.0}));
	BOOST_CHECK(poly7 % poly8 == cUnivarPolynomial<double>({13.0/8.0, 5.0}));
}

BOOST_AUTO_TEST_CASE(test_derivative_and_integral)
{

	//test1
	cUnivarPolynomial<double> poly1({0.0, 7.0});
	std::vector<double> vec;
	vec.push_back(7.0);
	BOOST_CHECK(poly1.derivative() == cUnivarPolynomial<double>(vec));
	BOOST_CHECK(poly1.derivative().primitive() == poly1);


	//test2
	cUnivarPolynomial<double> poly2({3.0, 3.0, 3.0});
	BOOST_CHECK(poly2.derivative() == cUnivarPolynomial<double>({3.0, 6.0}));
	BOOST_CHECK(poly2.primitive().derivative() == poly2);


	//test3
	cUnivarPolynomial<double> poly3({3.0, 0.0, 3.0});
	BOOST_CHECK(poly3.derivative() == cUnivarPolynomial<double>({0.0, 6.0}));
	BOOST_CHECK(poly3.primitive().derivative() == poly3);


	//test4
	cUnivarPolynomial<double> poly4({0.1, 0.0, 3.0, 0.0, 9.0});
	BOOST_CHECK(poly4.derivative() == cUnivarPolynomial<double>({0.0, 6.0, 0.0, 36.0}));
	BOOST_CHECK(poly4.primitive().derivative() == poly4);
	
}


BOOST_AUTO_TEST_CASE(test_first_deg_roots)
{
	std::vector<double> p1_coeff = {3.0, 2.0};
	cUnivarPolynomial<double> poly1(p1_coeff);
	std::vector<double> roots = poly1.realZeros();
	BOOST_REQUIRE_MESSAGE(roots.size() == 1, "number of real roots is " << roots.size());
	BOOST_CHECK_MESSAGE(roots[0] == -3.0/2.0, "the root is " << roots[0]);

	std::vector<double> p2_coeff = {0.0, 0.0, 0.0, 5.0};
	cUnivarPolynomial<double> poly2(p2_coeff);
	std::vector<double> roots2 = poly2.realZeros();
	BOOST_REQUIRE_MESSAGE(roots2.size() == 3, "number of real roots is " << roots2.size());
	BOOST_CHECK_MESSAGE(roots2[0] == 0.0, "the root is " << roots2[0]);

}

BOOST_AUTO_TEST_CASE(test_second_deg_roots)
{
	//delta < 0 (only complex roots) test -> 3x^2 + 2x + 1
	std::vector<double> p1_coeff = {1.0, 2.0, 3.0};
	cUnivarPolynomial<double> poly1(p1_coeff);
	std::vector<double> roots = poly1.realZeros();
	BOOST_CHECK_MESSAGE(roots.size() == 0, "number of real roots is " << roots.size());

	//2x^2 + 3x + 1
	std::vector<double> p2_coeff = {1.0, 3.0, 2.0};
	cUnivarPolynomial<double> poly2(p2_coeff);
	std::vector<double> roots2 = poly2.realZeros();
	BOOST_REQUIRE_MESSAGE(roots2.size() == 2, "number of real roots is " << roots2.size());
	BOOST_CHECK_MESSAGE(roots2[0] == -1.0 && roots2[1] == -1.0/2.0, "the root is " << roots2[0]);

	// c = 0 test -> 2x^2 + 3x
	std::vector<double> p3_coeff = {0.0, 3.0, 2.0};
	cUnivarPolynomial<double> poly3(p3_coeff);
	std::vector<double> roots3 = poly3.realZeros();
	BOOST_REQUIRE_MESSAGE(roots3.size() == 2, "number of real roots is " << roots3.size());
	BOOST_CHECK_MESSAGE(roots3[0] == -3.0/2.0 && roots3[1] == 0.0, "the root is " << roots3[0]);

	//delta = 0 test -> 2x^2 + 4x + 2
	std::vector<double> p4_coeff = {2.0, 4.0, 2.0};
	cUnivarPolynomial<double> poly4(p4_coeff);
	std::vector<double> roots4 = poly4.realZeros();
	BOOST_REQUIRE_MESSAGE(roots4.size() == 2, "number of real roots is " << roots4.size());
	BOOST_CHECK_MESSAGE(roots4[0] == -1.0 && roots4[1] == -1.0, "the root is " << roots4[0]);
}

BOOST_AUTO_TEST_CASE(test_cubic_roots)
{
	//delta < 0 - irreducible case -> y^3 - 7y - 7
	std::vector<double> p1_coeff = {-7.0, -7.0, 0.0, 1.0};
	cUnivarPolynomial<double> poly1(p1_coeff);
	std::vector<double> roots1 = poly1.realZeros();
	BOOST_CHECK_MESSAGE(roots1.size() == 3, "number of real roots is " << roots1.size());
	const double eps = 0.001;
	BOOST_CHECK_CLOSE(roots1[0], 3.04892, eps);
	BOOST_CHECK_CLOSE(roots1[1], -1.35689, eps);
   	BOOST_CHECK_CLOSE(roots1[2], -1.69202, eps);

	//delta > 0 - one real root and 2 complex -> x^3 - 0.1x^2 - 0.1x - 1.1
	std::vector<double> p2_coeff = {-1.1, -0.1, -0.1, 1.0};
	cUnivarPolynomial<double> poly2(p2_coeff);
	std::vector<double> roots2 = poly2.realZeros();
	BOOST_CHECK_MESSAGE(roots2.size() == 1, "number of real roots is " << roots2.size());
	BOOST_CHECK_CLOSE(roots2[0], 1.1, eps);

	//TODO - test for delta = 0
}


BOOST_AUTO_TEST_CASE(test_roots)
{
	const double eps = 0.001;
	cUnivarPolynomial<double> poly1({-1.0, -1.0, 0.0, 1.0, 1.0});
	auto sturm_seq = poly1.sturmSequence();
	auto roots = poly1.realZeros();
	BOOST_CHECK_MESSAGE(roots.size() == 2, "number of real roots is " << roots.size());
	BOOST_CHECK_CLOSE(roots[0], -1.0, eps);
	BOOST_CHECK_CLOSE(roots[1], 1.0, eps);
}

