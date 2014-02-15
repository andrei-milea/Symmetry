#ifndef _FUNC_EXPR_EVAL_H
#define _FUNC_EXPR_EVAL_H

#include "func_expr.h"

//forward declaration
template <typename T> 
class cEvalExprlVisitor;

template <typename T>
class cEvalVisitor : public boost::static_visitor<expr_type>
{
public:
	cEvalVisitor(const cVariable& var, const T& arg)
		:m_Variable(var),
		m_Arg(arg)
	{}

	cEvalVisitor(const T& arg)
		:m_Arg(arg)
	{}

	template<template <typename> class FCT>
	expr_type operator()(const FCT<T>& fct)const
	{
		if(m_Variable == "")
			return fct(m_Arg);
		else
			return fct;
	}

	expr_type operator()(const cFuncExpr& fnc_expr)const
	{
		assert(!(m_Variable == ""));
		return fnc_expr(m_Variable, m_Arg);
	}

	expr_type operator()(const cVariable& var)const
	{
		if(m_Variable == var)
			return m_Arg;
		else
			return var;
	}
	constexpr expr_type operator()(const cEmptyExpr& expr)const
	{
		return expr;
	}

	constexpr expr_type operator()(const T& val)const
	{
		return val;
	}
private:
	cVariable m_Variable;
	T m_Arg;
};

/*!
 * used to evaluate expression through boost visitor
*/
template <typename T>
class cEvalExprlVisitor : public boost::static_visitor<expr_type>
{
public:
	cEvalExprlVisitor(const expr_type& lhs_expr, const expr_type& rhs_expr, const cVariable& var, const T& arg)
		:m_Variable(var),
		m_Arg(arg)
	{
		m_LHSExpr = boost::apply_visitor(cEvalVisitor<T>(m_Variable, m_Arg), lhs_expr);
		m_RHSExpr = boost::apply_visitor(cEvalVisitor<T>(m_Variable, m_Arg), rhs_expr);
	}

	expr_type operator()(const Addition& add)
	{
		T *lval = boost::get<T>(&m_LHSExpr);
		T *rval = boost::get<T>(&m_RHSExpr);
		if(lval && rval)
			return *lval + *rval;
		else
			return cFuncExpr(add, m_LHSExpr, m_RHSExpr);

	}

	expr_type operator()(const Subtraction& sub)
	{
		T *lval = boost::get<T>(&m_LHSExpr);
		T *rval = boost::get<T>(&m_RHSExpr);
		if(lval && rval)
			return *lval - *rval;
		else
			return cFuncExpr(sub, m_LHSExpr, m_RHSExpr);
	}

	expr_type operator()(const Composition& comp)
	{
		T *rval = boost::get<T>(&m_RHSExpr);
		if(rval)
			return boost::apply_visitor(cEvalVisitor<T>(*rval), m_LHSExpr);

		return cFuncExpr(comp, m_LHSExpr, m_RHSExpr);
	}

	expr_type operator()(const Power& pow)
	{
		T *lval = boost::get<T>(&m_LHSExpr);
		T *rval = boost::get<T>(&m_RHSExpr);
		if(lval && rval)
			return std::pow(*lval, *rval);
		else
			return cFuncExpr(pow, m_LHSExpr, m_RHSExpr);
	}

	expr_type operator()(const NoOp& no_op)
	{
		T *lval = boost::get<T>(&m_LHSExpr);
		return lval ? *lval : m_LHSExpr;
	}

	expr_type operator()(const Multiplication& mult)
	{
		T *lval = boost::get<T>(&m_LHSExpr);
		T *rval = boost::get<T>(&m_RHSExpr);
		if(lval && rval)
			return (*lval) * (*rval);
		else
			return cFuncExpr(mult, m_LHSExpr, m_RHSExpr);
	}

	expr_type operator()(const Division& div)
	{
		T *lval = boost::get<T>(&m_LHSExpr);
		T *rval = boost::get<T>(&m_RHSExpr);
		if(lval && rval)
			return (*lval) / (*rval);
		else
			return cFuncExpr(div, m_LHSExpr, m_RHSExpr);
	}

private:
	expr_type  m_LHSExpr;
	expr_type m_RHSExpr;
	cVariable m_Variable;
	T m_Arg;
	cFuncExpr debug;
};

#endif




