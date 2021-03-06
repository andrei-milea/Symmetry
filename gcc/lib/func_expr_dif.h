#ifndef _FUNC_EXPR_DIF_H
#define _FUNC_EXPR_DIF_H

#include "func_expr.h"

/*!
 * used to apply differentiation through boost visitor
*/
class cDiffVisitor : public boost::static_visitor<cFuncExpr>
{
public:
	cDiffVisitor(const cVariable& var, const expr_type* expr = nullptr)
		:m_Variable(var),
		m_Expr(expr)
	{}

	cDiffVisitor(const expr_type* expr = nullptr)
		:m_Variable(cVariable("n0n3")),
		m_Expr(expr)
	{}

	template<typename T>
	cFuncExpr operator()(const cSine<T>& fct)const
	{
		return cFuncExpr(Composition(), cCosine<T>(), *m_Expr);
	}

	template<typename T>
	cFuncExpr operator()(const cCosine<T>& fct)const
	{
		return cFuncExpr(Multiplication(), -1, cFuncExpr(Composition(), cSine<T>(), *m_Expr));
	}

	template<typename T>
	cFuncExpr operator()(const cTangent<T>& fct)const
	{
		return cFuncExpr(Division(), 1, cFuncExpr(Multiplication(), 
					cFuncExpr(Composition(), cCosine<T>(), *m_Expr), cFuncExpr(Composition(), cCosine<T>(), *m_Expr)));
	}

	template<typename T>
	cFuncExpr operator()(const cCotangent<T>& fct)const
	{
		return cFuncExpr(Division(), -1.0, cFuncExpr(Power(), cFuncExpr(Composition(), cSine<T>(), *m_Expr), 2.0));
	}

	template<typename T>
	cFuncExpr operator()(const cAsine<T>& fct)const
	{
		return cFuncExpr(Division(), 1.0, cFuncExpr(Power(),
				cFuncExpr(Subtraction(), 1.0, cFuncExpr(Power(), *m_Expr, 2.0)),
				0.5));
	}

	template<typename T>
	cFuncExpr operator()(const cAcosine<T>& fct)const
	{
		return cFuncExpr(Multiplication(), -1.0,
						cFuncExpr(Division(), 1.0, cFuncExpr(Power(),
							cFuncExpr(Subtraction(), 1.0, cFuncExpr(Power(), *m_Expr, 2.0)), 0.5)));
	}

	template<typename T>
	cFuncExpr operator()(const cAtangent<T>& fct)const
	{
		return cFuncExpr(Division(), 1, cFuncExpr(Addition(), 1.0, cFuncExpr(Power(), *m_Expr, 2.0)));
	}

	template<typename T>
	cFuncExpr operator()(const cAcotangent<T>& fct)const
	{
		return cFuncExpr(Multiplication(), -1.0,
				cFuncExpr(Division(), 1, cFuncExpr(Addition(), 1.0, cFuncExpr(Power(), *m_Expr, 2.0))));
	}

	template<typename T>
	cFuncExpr operator()(const cAbsVal<T>& fct)const
	{
		return cFuncExpr(Division(), *m_Expr, cFuncExpr(Composition(), cAbsVal<T>(), *m_Expr));
	}

	template<typename T>
	cFuncExpr operator()(const cExponential<T>& fct)const
	{
		if(fct.base() == boost::math::constants::e<T>())
			return cFuncExpr(Composition(), cExponential<T>(), *m_Expr);

		return cFuncExpr(Multiplication(), std::log(fct.base()), cFuncExpr(Composition(), cExponential<T>(), *m_Expr));
	}

	template<typename T>
	cFuncExpr operator()(const cUnivarPolynomial<T>& fct)const
	{
		return cFuncExpr(Composition(), fct.derivative(), *m_Expr);
	}

	template<typename T>
	cFuncExpr operator()(const cLogarithm<T>& fct)const
	{
		if(fct.base() == boost::math::constants::e<T>())
			return cFuncExpr(Division(), 1.0, *m_Expr);
		return cFuncExpr(Division(), 1.0, cFuncExpr(Multiplication(), std::log(fct.base()), *m_Expr));
	}

	template <typename T>
	cFuncExpr operator()(const T& fct)const
	{
		if(m_Variable == cVariable("n0n3"))
			return fct.derivative();
		else
			return fct.partial_derivative(m_Variable);
	}

private:
	const cVariable m_Variable;
	const expr_type* m_Expr;
};
//specialization for primitive types types

template<>
inline cFuncExpr cDiffVisitor::operator()(const double& val)const
{
	return cFuncExpr(0.0);
}

template<>
inline cFuncExpr cDiffVisitor::operator()(const cVariable& var)const
{
	if(var == m_Variable || m_Variable == cVariable("n0n3"))
		return cFuncExpr(1.0);
	else
		return cFuncExpr(0.0);
}

template<>
inline cFuncExpr cDiffVisitor::operator()(const cEmptyExpr& val)const
{
	throw std::logic_error("trying to differentiate empty expression");
	return cFuncExpr(0.0);
	
}

/*!
 * class used to implement the rules for 
 * differentiation with respect to each operation
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

	void operator()(const Power& power)
	{
		m_ResExpr.m_Operation = Multiplication();
		const double *exp_dbl = boost::get<double>(&m_RHSExpr);
		const int *exp_int = boost::get<int>(&m_RHSExpr);
		if(exp_dbl || exp_int)
		{
			auto exp = (exp_dbl ? *exp_dbl : *exp_int);
			m_ResExpr.m_LHSExpr = cFuncExpr(Multiplication(), exp, cFuncExpr(Power(), m_LHSExpr, exp -1));
			m_ResExpr.m_RHSExpr = boost::apply_visitor(cDiffVisitor(), m_LHSExpr);
		}
		else	//we have f(x)^g(x)
		{
			//use logarithmic differentiation
			cFuncExpr f_x = cFuncExpr(Power(), m_LHSExpr, m_RHSExpr);
			cFuncExpr g_x_log_x = cFuncExpr(Multiplication(), m_RHSExpr,
				  cFuncExpr(Composition(), cLogarithm<double>(), m_LHSExpr));
			m_ResExpr.m_LHSExpr = f_x;
			m_ResExpr.m_RHSExpr = g_x_log_x.derivative();
		}
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
		m_ResExpr.m_Operation = Multiplication();
		m_ResExpr.m_LHSExpr = boost::apply_visitor(cDiffVisitor(&m_RHSExpr), m_LHSExpr);
		m_ResExpr.m_RHSExpr = boost::apply_visitor(cDiffVisitor(), m_RHSExpr);
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

/*!
 * class used to implement the rules for 
 * partial differentiation with respect to each operation
*/
class cExprPartDiffVisitor : public boost::static_visitor<>
{
public:
	cExprPartDiffVisitor(cFuncExpr& res_expr, const expr_type& lhs_expr, const expr_type& rhs_expr, const cVariable& var)
		:m_ResExpr(res_expr),
		m_LHSExpr(lhs_expr),
		m_RHSExpr(rhs_expr),
		m_Variable(var)
	{}

	void operator()(const Addition& addition)
	{
		m_ResExpr.m_Operation = addition;
		m_ResExpr.m_LHSExpr = boost::apply_visitor(cDiffVisitor(m_Variable), m_LHSExpr);
		m_ResExpr.m_RHSExpr = boost::apply_visitor(cDiffVisitor(m_Variable), m_RHSExpr);
	}

	void operator()(const Multiplication& multiplication)
	{
		m_ResExpr.m_Operation = Addition();
		cFuncExpr lhs_diff = boost::apply_visitor(cDiffVisitor(m_Variable), m_LHSExpr);
		cFuncExpr rhs_diff = boost::apply_visitor(cDiffVisitor(m_Variable), m_RHSExpr);
		m_ResExpr.m_LHSExpr = cFuncExpr(Multiplication(), m_RHSExpr, lhs_diff);
		m_ResExpr.m_RHSExpr = cFuncExpr(Multiplication(), m_LHSExpr, rhs_diff);

	}

	void operator()(const Power& power)
	{
		m_ResExpr.m_Operation = Multiplication();
		const double *exp_dbl = boost::get<double>(&m_RHSExpr);
		const int *exp_int = boost::get<int>(&m_RHSExpr);
		if(exp_dbl || exp_int)
		{
			auto exp = (exp_dbl ? *exp_dbl : *exp_int);
			m_ResExpr.m_LHSExpr = cFuncExpr(Multiplication(), exp, cFuncExpr(Power(), m_LHSExpr, exp -1));
			m_ResExpr.m_RHSExpr = boost::apply_visitor(cDiffVisitor(m_Variable), m_LHSExpr);
		}
		else	//we have f(x)^g(x)
		{
			//use logarithmic differentiation
			cFuncExpr f_x = cFuncExpr(Power(), m_LHSExpr, m_RHSExpr);
			cFuncExpr g_x_log_x = cFuncExpr(Multiplication(), m_RHSExpr,
				  cFuncExpr(Composition(), cLogarithm<double>(), m_LHSExpr));
			m_ResExpr.m_LHSExpr = f_x;
			m_ResExpr.m_RHSExpr = g_x_log_x.partial_derivative(m_Variable);
		}
	}

	void operator()(const Subtraction& subtraction)
	{
		m_ResExpr.m_Operation = subtraction;
		m_ResExpr.m_LHSExpr = boost::apply_visitor(cDiffVisitor(m_Variable), m_LHSExpr);
		m_ResExpr.m_RHSExpr = boost::apply_visitor(cDiffVisitor(m_Variable), m_RHSExpr);
	}
	void operator()(const Division& division)
	{
		m_ResExpr.m_Operation = Division();
		cFuncExpr lhs_diff = boost::apply_visitor(cDiffVisitor(m_Variable), m_LHSExpr);
		cFuncExpr rhs_diff = boost::apply_visitor(cDiffVisitor(m_Variable), m_RHSExpr);
		m_ResExpr.m_LHSExpr = cFuncExpr(Subtraction(), cFuncExpr(Multiplication(), m_RHSExpr, lhs_diff),
								cFuncExpr(Multiplication(), m_LHSExpr, rhs_diff));
		m_ResExpr.m_RHSExpr = cFuncExpr(Multiplication(), m_RHSExpr, m_RHSExpr);
	}

	void operator()(const Composition& composition)
	{
		m_ResExpr.m_Operation = Multiplication();
		m_ResExpr.m_LHSExpr = boost::apply_visitor(cDiffVisitor(m_Variable, &m_RHSExpr), m_LHSExpr);
		m_ResExpr.m_RHSExpr = boost::apply_visitor(cDiffVisitor(m_Variable), m_RHSExpr);
	}

	void operator()(const NoOp& no_op)
	{
		m_ResExpr.m_Operation = NoOp();
		m_ResExpr.m_LHSExpr = boost::apply_visitor(cDiffVisitor(m_Variable), m_LHSExpr);
		m_ResExpr.m_RHSExpr = cEmptyExpr();
	}

private:
	cFuncExpr& m_ResExpr;
	const expr_type&  m_LHSExpr;
	const expr_type& m_RHSExpr;
	const cVariable m_Variable;
};




#endif


