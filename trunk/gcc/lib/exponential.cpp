
#include "exponential.h"
#include "func_expr.h"


template <typename T>
bool cExponential<T>::operator==(const cExponential& exp)const;
{
	return m_Base == exp.m_Base;
}

template <typename T>
cFuncExpr cExponential<T>::derivative(const cVariable& var)const
{
	return ;
}

template <typename T>
cFuncExpr cExponential<T>::integral(const cVariable& var)const
{

}


template <typename T>
cLogarithm cExponential<T>::inverse()const
{

}

