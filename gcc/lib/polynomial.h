#ifndef _POLYNOMIAL_H
#define  _POLYNOMIAL_H

#include "univar_polynomail.h"
#include "multivar_polynomail.h"

/*!
  selector class - chooses the polynomial underlying implementation
  based on the specified traits
*/
template <typename T, class VARS, POLY_REP>
struct polynomial_impl { };

//traits
struct univariate {};
struct multivariate {};
struct coeff_list {};
struct point_value {};


template <typename T>
struct polynomial_impl<T, univariate, coeff_list>
{
	typedef cUnivarPolynomial<T> type;
};

template <typename T>
struct polynomial_impl<T, multivariate, coeff_list>
{
	typedef cMultivarPolynomial<T> type;
};

template <typename T>
struct polynomial_impl<T, univariate, point_value>
{
	typedef cPVUnivarPolynomial<T> type;
};

template <typename T>
struct polynomial_impl<T, multivariate, point_value>
{
	typedef cPVMultivarPolynomial<T> type;
};


/*!
  traits for the polynomial class
*/
template <typename T, class VARS, POLY_REP>
struct polynomial_traits
{
	typedef typename polynomial_impl<T, VARS, POLY_REP>::type polynomial_impl;
}


/*!
 class that represents a polynomial - parameter T gives the coefficients type
 the polynomial class can be customized with the following traits:
 VAR - which can be univariate or multivariate 
 POLY_REP - which can be coeff_list (the classic way of representing a polynomial - array of coefficients)
 or point_value ( list of points and corresponding values {(x_1, y_1), ..., (x_n, y_n) / P(x_k) = y_k} )
 TODO
*/
template <typename T, class VARS, class POLY_REP>
class cPolynomial
{
public:
	cPolynomial()
	{
	};
	~cPolynomial()
	{
	};
};

#endif

