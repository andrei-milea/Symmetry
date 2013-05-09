#ifndef _UNIVAR_POLYNOMIAL_H
#define _UNIVAR_POLYNOMIAL_H

#include <boost/math/tools/polynomial.hpp>

namespace bmt = boost::math::tools;

/*!
 this is inherited from the BOOST polynomial class
*/
template <typename T>
class cUnivarPolynomial : public bmt::polynomial<T>
{
	using namespace bmt;
public:
	cUnivarPolynomial()	{};
	~cUnivarPolynomial() {};

	cUnivarPolynomial(std::vector<T> coefficients)
		: polynomial(coefficients.begin(), coefficients.size() - 1),
		m_Degree(coefficients.size())
	{};

	std::vector<T> getRealZeros()const
	{
		//TODO
	};

	std::vector<std::complex<T> > getComplexZeroes()const
	{
		//TODO
	};

	cUnivarPolynomial gcd(const cUnivarPolynomial& poly)const
	{
		//TODO
	};

	cUnivarPolynomial& operator/=(const cUnivarPolynomial& poly)
	{
		//TODO
		return *this;
	};
};


#endif


