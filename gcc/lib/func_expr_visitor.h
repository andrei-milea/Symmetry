#ifndef _FUNC_EXPR_VISITOR_H
#define _FUNC_EXPR_VISITOR_H

#include "func_expr.h"

#include <iostream>

/*!
 * used to apply simplification rules through boost visitor
*/
class cSimplifyVisitor : public boost::static_visitor<>
{
public:
	cSimplifyVisitor(expr_type& lhs_expr, expr_type& rhs_expr, operation_type& operation)
		:m_LHSExpr(lhs_expr),
		m_RHSExpr(rhs_expr),
		m_Operation(operation)
	{}

	void operator()(Addition& add)
	{
		simplify_subtrees();

		if(isZero(m_LHSExpr))
		{
			m_LHSExpr = m_RHSExpr;
			m_Operation = NoOp();
		}
		else if(isZero(m_RHSExpr))
		{
			m_RHSExpr = m_LHSExpr;
			m_Operation = NoOp();
		}
	}

	void operator()(Subtraction& sub)
	{
		simplify_subtrees();
	}

	void operator()(Composition& comp)
	{
		simplify_subtrees();
	}

	void operator()(NoOp& no_op)
	{
	}

	void operator()(Multiplication& mult)
	{
		simplify_subtrees();
	
		if(isZero(m_LHSExpr) || isZero(m_RHSExpr))
		{
			m_LHSExpr = 0.0;
			m_Operation = NoOp();	
			m_RHSExpr = cEmptyExpr();
		}
		else if(isOne(m_LHSExpr))
		{
			m_Operation = NoOp();
			m_LHSExpr = m_RHSExpr;
			m_RHSExpr = cEmptyExpr();
		}
		else if(isOne(m_RHSExpr))
		{
			m_Operation = NoOp();
			m_RHSExpr = cEmptyExpr();
		}
	}

	void operator()(Division& div)
	{
		simplify_subtrees();
		if(isZero(m_LHSExpr))
		{
			m_LHSExpr = 0.0;		
			m_Operation = NoOp();
			m_RHSExpr = cEmptyExpr();
		}
		else if(isOne(m_RHSExpr))
		{
			m_Operation = NoOp();
			m_RHSExpr = cEmptyExpr();
		}
	}

private:

	bool isOne(const expr_type& fnc_expr)const
	{
		
		auto num = boost::get<double>(&fnc_expr);
		if(num && *num == 1.0)
			return true;

		auto fnc = boost::get<cFuncExpr>(&fnc_expr);
		if(fnc)
		{
			auto op = boost::get<NoOp>(&fnc->m_Operation);
			auto left_num = boost::get<double>(&fnc->m_LHSExpr);
			if(op && left_num && *left_num == 1.0)
				return true;
		}

		return false;
	}

	bool isZero(const expr_type& fnc_expr)const
	{
		
		auto num = boost::get<double>(&fnc_expr);
		if(num && *num == 0.0)
			return true;

		auto fnc = boost::get<cFuncExpr>(&fnc_expr);
		if(fnc)
		{
			auto op = boost::get<NoOp>(&fnc->m_Operation);
			auto left_num = boost::get<double>(&fnc->m_LHSExpr);
			if(op && left_num && *left_num == 0.0)
				return true;
		}

		return false;
	}

	void simplify_subtrees()
	{
		if(cFuncExpr *fnc_expr = boost::get<cFuncExpr>(&m_LHSExpr))
		{
			fnc_expr->simplify();
		}
		if(cFuncExpr *fnc_expr = boost::get<cFuncExpr>(&m_RHSExpr))
		{
			fnc_expr->simplify();
		}
	}

private:
	expr_type&  m_LHSExpr;
	expr_type& m_RHSExpr;
	operation_type &m_Operation;
};

/*!
 * used to apply differentiation through boost visitor
*/
class cDiffVisitor : public boost::static_visitor<cFuncExpr>
{
public:
	cDiffVisitor()
		:m_Variable(nullptr)
	{}
	cDiffVisitor(const cVariable* var)
		:m_Variable(var)
	{}

	template < typename T, template <typename> class F>
	cFuncExpr operator()(const F<T>& fct)const
	{
		assert(m_Variable);
		return cFuncExpr(fct.derivative(*m_Variable));
	}

	template <typename T>
	cFuncExpr operator()(const T& fct)const
	{
		return fct.derivative_impl();
	}

private:
	const cVariable* m_Variable;
};
//specialization for primitive types
template<>
inline cFuncExpr cDiffVisitor::operator()(const double& val)const
{
	return cFuncExpr(0.0);
}
template<>
inline cFuncExpr cDiffVisitor::operator()(const cVariable& val)const
{
	return cFuncExpr(1.0);
}
template<>
inline cFuncExpr cDiffVisitor::operator()(const cEmptyExpr& val)const
{
	throw std::logic_error("trying to differentiate empty expression");
	return cFuncExpr(0.0);
	
}

/*!
 * class used to implement the rules for 
 * differentiation with respect each operation
*/
class cExprDiffVisitor : public boost::static_visitor<>
{
public:
	cExprDiffVisitor(cFuncExpr& res_expr, const expr_type& lhs_expr, const expr_type& rhs_expr)
		:m_ResExpr(res_expr),
		m_LHSExpr(lhs_expr),
		m_RHSExpr(rhs_expr)
	{}

	void operator()(const Addition& addition)
	{
		m_ResExpr.m_Operation = addition;
		m_ResExpr.m_LHSExpr = boost::apply_visitor(cDiffVisitor(), m_LHSExpr);
		m_ResExpr.m_RHSExpr = boost::apply_visitor(cDiffVisitor(), m_RHSExpr);
	}

	void operator()(const Multiplication& multiplication)
	{
		m_ResExpr.m_Operation = Addition();
		cFuncExpr lhs_diff = boost::apply_visitor(cDiffVisitor(), m_LHSExpr);
		cFuncExpr rhs_diff = boost::apply_visitor(cDiffVisitor(), m_RHSExpr);
		m_ResExpr.m_LHSExpr = cFuncExpr(Multiplication(), m_RHSExpr, lhs_diff);
		m_ResExpr.m_RHSExpr = cFuncExpr(Multiplication(), m_LHSExpr, rhs_diff);

	}

	void operator()(const Subtraction& subtraction)
	{
		m_ResExpr.m_Operation = subtraction;
		m_ResExpr.m_LHSExpr = boost::apply_visitor(cDiffVisitor(), m_LHSExpr);
		m_ResExpr.m_RHSExpr = boost::apply_visitor(cDiffVisitor(), m_RHSExpr);
	}
	void operator()(const Division& division)
	{
		m_ResExpr.m_Operation = Division();
		cFuncExpr lhs_diff = boost::apply_visitor(cDiffVisitor(), m_LHSExpr);
		cFuncExpr rhs_diff = boost::apply_visitor(cDiffVisitor(), m_RHSExpr);
		m_ResExpr.m_LHSExpr = cFuncExpr(Subtraction(), cFuncExpr(Multiplication(), m_RHSExpr, lhs_diff),
								cFuncExpr(Multiplication(), m_LHSExpr, rhs_diff));
		m_ResExpr.m_RHSExpr = cFuncExpr(Multiplication(), m_RHSExpr, m_RHSExpr);
	}

	void operator()(const Composition& composition)
	{
		if(const cVariable *var = boost::get<cVariable>(&m_RHSExpr))
		{
			assert(nullptr == boost::get<cFuncExpr>(&m_LHSExpr));
			m_ResExpr = boost::apply_visitor(cDiffVisitor(var), m_LHSExpr);
		}
		else	
		{
			m_ResExpr.m_Operation = Multiplication();
			m_ResExpr.m_LHSExpr = cFuncExpr(Composition(), boost::apply_visitor(cDiffVisitor(), m_LHSExpr), m_RHSExpr);
			m_ResExpr.m_RHSExpr = boost::apply_visitor(cDiffVisitor(), m_RHSExpr);
		}
	}

	void operator()(const NoOp& no_op)
	{
		m_ResExpr.m_Operation = NoOp();
		m_ResExpr.m_LHSExpr = boost::apply_visitor(cDiffVisitor(), m_LHSExpr);
		m_ResExpr.m_RHSExpr = cEmptyExpr();
	}

private:
	cFuncExpr& m_ResExpr;
	const expr_type&  m_LHSExpr;
	const expr_type& m_RHSExpr;
};

////////////////////////////////////////////////////////////
///////////////overloaded output operator///////////////////
////////////////////////////////////////////////////////////

/*!
 * class used to print an elementary function 
*/ 
class cOutputVisitor : public boost::static_visitor<>
{
public:
	template < typename T, template <typename> class F>
	void operator()(const F<T>& fct)const
	{
		std::cout << fct;
	}

	template <typename T>
	void operator()(const T& fct)const
	{
		std::cout << fct;
	}
	
};

template<>
inline void cOutputVisitor::operator()(const cEmptyExpr& val)const
{
	assert(false);
	std::cout << "error: empty expression";
}
template<>
inline void cOutputVisitor::operator()(const NoOp& val)const
{
	assert(false);
	std::cout << "error: trying to print no_op";
}

#endif

