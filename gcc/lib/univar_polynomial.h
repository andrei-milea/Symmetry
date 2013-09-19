#ifndef _UNIVAR_POLYNOMIAL_H
#define _UNIVAR_POLYNOMIAL_H

#include <boost/math/special_functions/fpclassify.hpp>
#include <boost/math/special_functions/cbrt.hpp>
#include <boost/math/special_functions/sign.hpp>
#include <boost/math/tools/polynomial.hpp>
#include <boost/math/tools/roots.hpp>

#include <utility>

namespace bmt = boost::math::tools;
namespace bmp = boost::math::policies;
namespace bm = boost::math;

class cVariable;

/*!
 * implements common operations on polynomials
 * on top of BOOST polynomial class
 * ! poly[0] is the free term
 * ! poly[degree] can't be zero - the zero polynomial is the empty vector
*/
template <typename T>
class cUnivarPolynomial
{
public:
	explicit cUnivarPolynomial(std::size_t tolerance = std::numeric_limits<T>::digits)
		:m_Tolerance(tolerance)
	{}

	cUnivarPolynomial(const std::vector<T>& coefficients, std::size_t tolerance = std::numeric_limits<T>::digits)
		:m_PolyImpl(&coefficients[0], coefficients.size() - 1),
		 m_Tolerance(tolerance)
	{
		assert(m_PolyImpl[degree()] != 0);
	}

	cUnivarPolynomial(const T* data, std::size_t degree, std::size_t tolerance = std::numeric_limits<T>::digits)
		:m_PolyImpl(data, degree),
		 m_Tolerance(tolerance)
	{
		assert(m_PolyImpl[degree] != 0);
	}

	~cUnivarPolynomial() {}

	size_t size()const
	{
		return m_PolyImpl.size();
	}

	size_t degree()const
	{
		if(m_PolyImpl.size() == 0)
			return 0;
		return m_PolyImpl.size() - 1;
	}

	static cUnivarPolynomial<T> zero()
	{
		return cUnivarPolynomial<T>();
	}

	/*!
	 *returns the derivative as a new polynomial
	*/
	cUnivarPolynomial<T> derivative()const;

	cUnivarPolynomial<T> primitive()const;

	cUnivarPolynomial<T> inverse()const;

	/*!
	 *returns the real zeros (double) of the polynomial
	*/
	std::vector<double> realZeros()const;

	/*!
	 * returns a list of points used to plot a graph of the polynomial
	*/
	std::vector<std::pair<double, double> > plotPoints()const;

	std::vector<std::complex<T> > complexZeroes()const;

	/*!
	 overload operator % to compute the polynomial division remainder
	 implements the algorithm from Knuth vol2
	*/
	cUnivarPolynomial<T>& operator%=(const cUnivarPolynomial& poly);

	/*!
	 *overload operator * to compute the polynomial multiplication
	*/
	cUnivarPolynomial<T>& operator*=(const cUnivarPolynomial& poly);

	cUnivarPolynomial<T>& operator*=(T num);

	/*!
	 *overload operator / to compute the polynomial division quotient
	 *implements the algorithm from Knuth vol2
	*/
	cUnivarPolynomial<T>& operator/=(const cUnivarPolynomial& poly);

	cUnivarPolynomial<T>& operator/=(T divisor);

	/*!
	 *overload operator () to evaluate the polynomial
	*/
	template <typename Y>
	T operator()(Y value)const
	{
		if(0 == size())
			return 0;

		if(degree() == 0)
			return m_PolyImpl[0];

		return m_PolyImpl.evaluate(value);
	}

	/*!
	 *overload operator == to compute the polynomial equality
	*/
	bool operator==(const cUnivarPolynomial& poly)const;

	/*!
	 *returns the Sturm sequence corresponding to the polynomial
	 *used to compute real zeros
	*/
	std::vector< cUnivarPolynomial<T> > sturmSequence()const;

private:
	/*!
	 get real zeros when the function has the degree smaller or equal to 2
	*/
	std::vector<double> &solveRQuadratic(std::vector<double> &zeros)const;

	/*!
	 get real zeros when the polynomial is cubic - using Cardano's formula
	*/
	std::vector<double>& solveRCubic(std::vector<double> &zeros)const;

	/*!
	 get the number of sign changes of the sturm sequence in the point x0
	*/
	int sturmSignsNo(double x0)const;

	template <class Y>
	friend std::ostream& operator<<(std::ostream& out, const cUnivarPolynomial<Y>& poly);

	template <class Y>
	friend std::ostream& operator<<(std::ostream& out, const std::pair<cUnivarPolynomial<Y>, cVariable>& poly);

private:
	//polynomial[size-1] has the highest power
	bmt::polynomial<T> m_PolyImpl;
	//functor equality comparation with specified degree of accuracy
	mutable bmt::eps_tolerance<T> m_Tolerance;
};

template <class T>
inline cUnivarPolynomial<T> gcd(const cUnivarPolynomial<T>& a, const cUnivarPolynomial<T>& b)
{
	return a;
	//TODO
}

template <class T>
inline cUnivarPolynomial<T> operator*(const cUnivarPolynomial<T>& a, const cUnivarPolynomial<T>& b)
{
	cUnivarPolynomial<T> result(a);
	result *= b;
	return result;
}

template <class T>
inline cUnivarPolynomial<T> operator%(const cUnivarPolynomial<T>& a, const cUnivarPolynomial<T>& b)
{
	cUnivarPolynomial<T> result(a);
	result %= b;
	return result;
}

template <class T>
inline cUnivarPolynomial<T> operator/(const cUnivarPolynomial<T>& a, const cUnivarPolynomial<T>& b)
{
	cUnivarPolynomial<T> result(a);
	result /= b;
	return result;
}

template <class T>
inline std::ostream& operator<<(std::ostream& out, const cUnivarPolynomial<T>& poly)
{
	size_t idx = poly.size();
	for( ; idx > 0; idx--)
	{
		if(poly.m_PolyImpl[idx - 1] != 0.0)
		{
			if(idx - 1 != poly.size() - 1)
				out << " + ";
			out << poly.m_PolyImpl[idx - 1];
			if(idx - 1 != 0)
				out<< "x^" << idx - 1;
		}
	}
	return out;
}

//print polynomial with respect to variable
template <class T>
inline std::ostream& operator<<(std::ostream& out, const std::pair<cUnivarPolynomial<T>, cVariable>& poly)
{
	size_t idx = poly.first.size();
	for( ; idx > 0; idx--)
	{
		if(poly.first.m_PolyImpl[idx - 1] != 0.0)
		{
			if(idx - 1 != poly.first.size() - 1)
				out << " + ";
			out << poly.first.m_PolyImpl[idx - 1];
			if(idx - 1 != 0)
				out	<< poly.second << "^" << idx - 1;
		}
	}
	return out;
}

#endif


