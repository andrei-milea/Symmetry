#ifndef _UNIVAR_FUNC_H
#define _UNIVAR_FUNC_H

#include <boost/variant/static_visitor.hpp>

/*!
 * generic functions common to all elementary 
 * single variable functions, and function expressions
*/

template <typename RET, typename FCT>
RET differentiate(const FCT &func)
{
	return func.derivative();
}

template <typename RET, typename FCT>
RET integrate(const FCT& func)
{
	return func.primitive();
}

template <typename RET, typename FCT>
RET invert(const FCT &func)
{
	return func.inverse();
}

template <typename T, typename FCT>
T eval(const FCT& func, const T& value)
{
	return func.operator()(value);
}


#endif


