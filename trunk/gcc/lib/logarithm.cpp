
#include "logarithm.h"

template <typename T>
bool cLogarithm<T>::operator==(const cLogarithm& log)const;
{
	return m_Base == log.m_Base;
}

template <typename T>
cFuncExpr cLogarithm<T>::derivative(const cVariable& var)const
{

}

template <typename T>
cFuncExpr cLogarithm<T>::integral(const cVariable& var)const
{

}


template <typename T>
cExponential cLogarithm<T>::inverse()const
{

}

