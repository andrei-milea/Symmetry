#ifndef _MULTIVAR_POLYNOMIAL_H
#define _MULTIVAR_POLYNOMIAL_H

#include <vector>
#include <utility>


/*!
class for multivariate polynomials 
TODO
*/
template <typename T>
class cMultivarPolynomial
{
public:
	cMultivarPolynomial();
	cMultivarPolynomial(std::vector<std::vector<std::pair<size_t, T> > > & poly);

private:
	std::vector<std::vector<std::pair<size_t, T> > > m_Polynomial;
};


#endif



