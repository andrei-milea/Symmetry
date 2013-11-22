#include "univar_polynomial.h"

#include "func_expr.h"

#include <stack>
#include <deque>
#include <utility>
#include <functional>
#include <algorithm>

template<typename T>
cUnivarPolynomial<T> cUnivarPolynomial<T>::derivative()const
{
	assert(m_PolyImpl[degree()] != 0);

	if(size() == 0)
		return *this;
	if(degree() == 0)
		return cUnivarPolynomial<T>::zero();

	std::vector<T> poly_coefs;
	poly_coefs.reserve(size());
	for(std::size_t idx = 1; idx <= degree(); idx++)	
	{
		poly_coefs.push_back(m_PolyImpl[idx] * idx);
	}
	return cUnivarPolynomial<T>(poly_coefs);
}

template<typename T>
cUnivarPolynomial<T> cUnivarPolynomial<T>::primitive()const
{
	assert(m_PolyImpl[degree()] != 0);

	if(size() == 0)
		return *this;
	std::vector<T> poly_coefs;
	poly_coefs.reserve(size() + 1);
	poly_coefs.push_back(0);
	for(std::size_t idx = 0; idx <= degree(); idx++)
	{
		poly_coefs.push_back(m_PolyImpl[idx] / (idx + 1));
	}
	return cUnivarPolynomial<T>(poly_coefs);
}

template<typename T>
cUnivarPolynomial<T> cUnivarPolynomial<T>::inverse()const
{
	//TODO
	return *this;
}

template<typename T>
std::vector<double> cUnivarPolynomial<T>::realZeros()const
{
	std::vector<double> zeros;
	if((0 == m_PolyImpl.size()) || (1 == m_PolyImpl.size()))
		return zeros;
	zeros.reserve(degree());

	assert(m_PolyImpl[degree()] != 0);

	//TODO - add preprocessing to remove trivial zeros

	//handle special cases with closed forms: degree < 4
	if(degree() <= 2)
		return solveRQuadratic(zeros);
	else if(3 == degree())
		return solveRCubic(zeros);

	//handle general case using Sturm sequences	in the interval [a, b]
	//to separate the roots and the bisection method to compute them
	double a = -1.0 * std::numeric_limits<double>::max();
	double b = std::numeric_limits<double>::max();
	//holds the intervals to be processed - eliminate recursion
	std::stack<std::pair<double, double> > int_stack;
	//holds the number of iterations - abort search when MAX_ITERATIONS is reached
	size_t idx = 0;
	
	const size_t MAX_ITERATIONS = std::numeric_limits<size_t>::max();
	while(degree() > zeros.size() || idx > MAX_ITERATIONS)
	{
		double c = (a + b) / 2;
		int sa = sturmSignsNo(a);
		int sb = sturmSignsNo(b);
		int sc = sturmSignsNo(c);

		if(sa - sb <= 0 || a > b)
		{
			if(!int_stack.empty())
			{
				auto interval = int_stack.top();
				a = interval.first;
				b = interval.second;
				int_stack.pop();
			}
			else
			{
				return zeros;
			}
		}
		else if(sa - sc >= 1)
		{
			if(sc - sb >= 1)
				int_stack.push(std::make_pair(c, b));

			if(sa - sc == 1)
			{
				if(m_Tolerance(a, c) || 0 == m_PolyImpl.evaluate(c))
				{
					zeros.push_back(c);
					a = c + 2.0 * std::numeric_limits<double>::epsilon();
				}
				else
					b = c;
			}
			else
				b = c;	
		}
		else
		{
			a = c;
		}
		
	}
	return zeros;
}

template<typename T>
std::vector<std::pair<double, double> > cUnivarPolynomial<T>::plotPoints()const
{
	std::vector<std::pair<double, double> > points;

	double min = -100.0;
	const double max = 100.0;
	const double increment = 0.2;

	//add bounds
	points.push_back(std::make_pair(min, operator()(min)));
	points.push_back(std::make_pair(max, operator()(max)));

	//add rest of the points
	while(min < max)
	{
		min += increment;
		points.push_back(std::make_pair(min, operator()(min)));
	}


	//add roots
	auto zeros = realZeros();
	std::for_each(zeros.begin(), zeros.end(), [&] (double zero)
			{	points.push_back(std::make_pair(zero, 0.0));		});

	//add critical points
	auto _derivative = derivative();
	auto critical_pts = _derivative.realZeros();
	std::for_each(critical_pts.begin(), critical_pts.end(), [&] (double zero)
					{	points.push_back(std::make_pair(zero, operator()(zero)));	});

	//add inflection points
	auto inflection_pts = _derivative.derivative().realZeros();
	std::for_each(inflection_pts.begin(), inflection_pts.end(), [&] (double zero)
					{	points.push_back(std::make_pair(zero, operator()(zero)));	});

	std::sort(points.begin(), points.end(), [](const std::pair<double,double>& lhs, const std::pair<double,double>& rhs)
				{
					return lhs.first < rhs.first;
				});

	return points;
}

template<typename T>
std::vector<std::complex<T> > cUnivarPolynomial<T>::complexZeroes()const
{
	//TODO - use companion matrix
	std::vector<std::complex<T> > vec;
	return vec;
}

template<typename T>
cUnivarPolynomial<T>& cUnivarPolynomial<T>::operator%=(const cUnivarPolynomial& poly)
{
	assert(m_PolyImpl[degree()] != 0);
	if(0 == poly.size())
		throw std::invalid_argument("polynomial divide-by-0 error");
	if(0 == size() || size() < poly.size())
		return *this;
	
	if(0 == poly.degree())
	{
		*this = cUnivarPolynomial<T>::zero();
		return *this;
	}

	T quotient_coeff = 0;
	bool isZero = false;
	size_t degree_dif = degree() - poly.degree();
	size_t k = 0;
	for( ; k <= degree() - poly.degree(); k++)
	{
		quotient_coeff = m_PolyImpl[degree() - k] / poly.m_PolyImpl[poly.degree()];
		isZero = true;
		for(size_t j = degree_dif; j <= degree() - k - 1; j++)
		{
			m_PolyImpl[j] = m_PolyImpl[j] - quotient_coeff * poly.m_PolyImpl[j - degree_dif];
			if(m_PolyImpl[j] != 0.0)
				isZero = false;
		}
		degree_dif--;
	}
	if(isZero)
		*this = cUnivarPolynomial<T>::zero();
	else
		m_PolyImpl = bmt::polynomial<T>(&m_PolyImpl[0], degree() - k);

	return *this;
}

template<typename T>
cUnivarPolynomial<T>& cUnivarPolynomial<T>::operator*=(const cUnivarPolynomial& poly)
{
	if(0 == poly.size())
	{
		*this = cUnivarPolynomial<T>::zero();
		return *this;
	}
	if(0 == size())
		return *this;

	m_PolyImpl *= poly.m_PolyImpl;	

	return *this;
}

template<typename T>
cUnivarPolynomial<T>& cUnivarPolynomial<T>::operator*=(T num)
{
	if(0 == size())
		return *this;

	m_PolyImpl *= num;	

	return *this;
}

template<typename T>
cUnivarPolynomial<T>& cUnivarPolynomial<T>::operator/=(const cUnivarPolynomial& poly)
{
	if(0 == poly.size())
		throw std::invalid_argument("polynomial divide-by-0 error");
	if(0 == size())
		return *this;

	if(degree() < poly.degree())
	{
		*this = cUnivarPolynomial<T>::zero();
		return *this;
	}

	if(0 == poly.degree())
	{
		*this /= poly.m_PolyImpl[0];
	}
	else
	{

		std::deque<T> quotient;
		size_t degree_dif = degree() - poly.degree();
		for(size_t k = 0; k <= degree() - poly.degree(); k++)
		{
			quotient.push_front(m_PolyImpl[degree() - k] / poly.m_PolyImpl[poly.degree()]);
			for(size_t j = degree_dif ; j <= degree() - k - 1; j++)
				m_PolyImpl[j] = m_PolyImpl[j] - quotient[0] * poly.m_PolyImpl[j - degree_dif];
			degree_dif--;
		}
		m_PolyImpl = bmt::polynomial<T>(&quotient[0], quotient.size() - 1);
	}
	return *this;
}

template<typename T>
cUnivarPolynomial<T>& cUnivarPolynomial<T>::operator/=(T divisor)
{
	if(0 == divisor)
		throw std::invalid_argument("polynomial divide-by-0 error");

	if(0 == size())
		return *this;

	for(size_t idx = 0; idx < size(); idx++)
		m_PolyImpl[idx] /= divisor;
	return *this;
}

template <typename T>
bool cUnivarPolynomial<T>::operator==(const cUnivarPolynomial& poly)const
{
	if(poly.size() != size())
		return false;

	for(size_t idx = 0; idx < size(); idx++)
	{
		if(false == m_Tolerance(poly.m_PolyImpl[idx], m_PolyImpl[idx]))
			return false;
	}

	return true;
}

template <typename T>
std::vector< cUnivarPolynomial<T> > cUnivarPolynomial<T>::sturmSequence()const
{
	std::vector< cUnivarPolynomial<T> > sequence;
	if(0 == degree())
	{
		sequence.push_back(*this);
		return sequence;
	}

	cUnivarPolynomial<T> p0 = *this;
	cUnivarPolynomial<T> p1 = derivative();
	sequence.push_back(*this);
	sequence.push_back(p1);

	if(0 == p1.degree())
		return sequence;

	p0 %= p1; 
	while(p0.degree() >= 1)
	{
		p0 *= -1.0;
		sequence.push_back(p0);
		auto temp = p0;
		p0 = p1 % p0;	
		p1 = temp;
	}
	p0 *= -1.0;
	sequence.push_back(p0);
	return sequence;
}

template <typename T>
std::vector<double>& cUnivarPolynomial<T>::solveRQuadratic(std::vector<double> &zeros)const
{
	if(1 == degree())	
	{
		zeros.push_back(-1.0 * m_PolyImpl[0]/m_PolyImpl[degree()]);
		return zeros;
	}
	else
	{
		assert(2 == degree());
		double a = m_PolyImpl[degree()], b = m_PolyImpl[1], c = m_PolyImpl[0];	//coefficients
		double delta = b * b - 4 * a * c;

		if(delta < 0.0)			//delta < 0 -> only complex roots
		{
			return zeros;
		}
		if(0 == delta)
		{
			double x = -1.0 * b / (2.0 * a);
			zeros.push_back(x);
			zeros.push_back(x);
			return zeros;
		}
		double sign = (b < 0.0) ? 1.0 : -1.0;
		double x1 = (-1.0 * b + sign * std::sqrt(delta)) / (2 * a);
		zeros.push_back(x1);
		if(0 != x1)
			zeros.push_back(c / (a * x1));	//x2
	}
	return zeros;
}

template <typename T>
std::vector<double>& cUnivarPolynomial<T>::solveRCubic(std::vector<double> &zeros)const
{
	assert(4 == size() && degree() == 3);

	//get normal form x^3 + Ax^2 + Bx + C = 0
	T A = m_PolyImpl[2] / m_PolyImpl[degree()];
	T B = m_PolyImpl[1] / m_PolyImpl[degree()];
	T C = m_PolyImpl[0] / m_PolyImpl[degree()];

	//eliminate quadratic term -> y^3 + Py + Q = 0
	T A_sq = A * A;
	T P = 1.0 / 3 * (-1.0 / 3 * A_sq + B);
	T Q = 1.0 / 2 * (2.0 / 27 * A * A_sq - 1.0 / 3 * A * B + C);

	//cardano formula
	T P_cube = P * P * P;
	T delta = Q * Q + P_cube;

	if(0 == delta)	//all roots are real
	{
		if (0 == Q)
		{
			zeros.push_back(-1.0 / 3 * A);
			zeros.push_back(-1.0 / 3 * A);
			zeros.push_back(-1.0 / 3 * A);
		}
		else
		{
			double Q_cube_rt = boost::math::cbrt(-Q);
			zeros.push_back(2 * Q_cube_rt - 1.0 / 3 * A);
			zeros.push_back(-Q_cube_rt - 1.0 / 3 * A);
			zeros.push_back(-Q_cube_rt - 1.0 / 3 * A);
		}
	}	
	else if(delta < 0.0)	//all real solutions - irreducible case
	{
		double phi = 1.0 / 3 * acos(-Q / std::sqrt(-P_cube));
		double t = 2 * std::sqrt(-P);
		zeros.push_back(t * std::cos(phi) - 1.0 / 3 * A);
		zeros.push_back(-t * std::cos(phi + boost::math::constants::pi<double>() / 3) - 1.0 / 3 * A);
		zeros.push_back(-t * std::cos(phi - boost::math::constants::pi<double>() / 3) - 1.0 / 3 * A);
	}
	else	//delta > 0 -> one real root and 2 complex roots
	{
		assert(delta > 0.0);
		double D_sqrt = std::sqrt(delta);
		double u = boost::math::cbrt(D_sqrt - Q);
		double v = boost::math::cbrt(D_sqrt + Q);
		zeros.push_back(u - v - 1.0 / 3 * A);
	}
	return zeros;
}

template <typename T>
int cUnivarPolynomial<T>::sturmSignsNo(double x0)const
{
	auto sturm_seq = sturmSequence();
	if(sturm_seq.size() <= 1)
		return 0;

	int sign_changes = 0;
	for(auto it = sturm_seq.begin() + 1; it != sturm_seq.end(); it++)
	{
		if(bm::sign((*(it-1))(x0)) * bm::sign((*(it))(x0)) < 0)
			sign_changes++;
	}
	return sign_changes;
}




//instantiations
template class cUnivarPolynomial<double>;



