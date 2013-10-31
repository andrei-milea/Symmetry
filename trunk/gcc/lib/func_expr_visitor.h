#ifndef _FUNC_EXPR_VISITOR_H
#define _FUNC_EXPR_VISITOR_H

#include "func_expr.h"

#include <iostream>

/*!
 * used to get commutativity from operations
*/
struct cCommuteVisitor : public boost::static_visitor<bool>
{
	template<typename T>
	bool operator()(const T& op)const
	{
		return op.isCommutative();
	}
};

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
			m_RHSExpr = cEmptyExpr();
		}
		else if(isZero(m_RHSExpr))
		{
			m_Operation = NoOp();
			m_RHSExpr = cEmptyExpr();
		}
	}

	void operator()(Subtraction& sub)
	{
		simplify_subtrees();
		if(isZero(m_RHSExpr))
		{
			m_Operation = NoOp();
			m_RHSExpr = cEmptyExpr();
		}

//		if(m_LHSExpr == m_RHSExpr)
//		{
//			m_LHSExpr = 0.0;
//			m_Operation = NoOp();
//			m_RHSExpr = cEmptyExpr();
//		}
	}

	void operator()(Composition& comp)
	{
		simplify_subtrees();
	}

	void operator()(Power& comp)
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
//		else if((!boost::get<cFuncExpr*>(&m_LHSExpr) && !boost::get<cFuncExpr*>(&m_RHSExpr)) && (m_RHSExpr == m_LHSExpr))
//		{
//			m_LHSExpr = 1.0;
//			m_RHSExpr = cEmptyExpr();
//			m_Operation = NoOp();
//		}
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
			if(boost::get<NoOp>(&fnc_expr->m_Operation))	
			{
				if(boost::get<cEmptyExpr>(&fnc_expr->m_RHSExpr))
				{
					expr_type expr = fnc_expr->m_LHSExpr;
					m_LHSExpr = expr;
				}
				else if(boost::get<cEmptyExpr>(&fnc_expr->m_LHSExpr))
				{
					expr_type expr = fnc_expr->m_RHSExpr;
					m_LHSExpr = expr;
				}
			}
		}
		if(cFuncExpr *fnc_expr = boost::get<cFuncExpr>(&m_RHSExpr))
		{
			fnc_expr->simplify();
			if(boost::get<NoOp>(&fnc_expr->m_Operation))	
			{
				if(boost::get<cEmptyExpr>(&fnc_expr->m_RHSExpr))
				{
					expr_type expr = fnc_expr->m_LHSExpr;
					m_RHSExpr = expr;
				}
				else if(boost::get<cEmptyExpr>(&fnc_expr->m_LHSExpr))
				{
					expr_type expr = fnc_expr->m_RHSExpr;
					m_RHSExpr = expr;
				}
			}
		}
	}

private:
	expr_type&  m_LHSExpr;
	expr_type& m_RHSExpr;
	operation_type &m_Operation;
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
}

template<>
inline void cOutputVisitor::operator()(const NoOp& val)const
{
}

#endif

