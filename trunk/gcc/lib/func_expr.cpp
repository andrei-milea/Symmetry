
#include "func_expr.h"
#include "func_expr_visitor.h"

#include <utility>
#include <sstream>

static struct NoOp no_op;
static struct cEmptyExpr empty_expr;


cFuncExpr::cFuncExpr()
	:m_Operation(no_op),
	m_LHSExpr(empty_expr),
	m_RHSExpr(empty_expr)
{
}

cFuncExpr::cFuncExpr(expr_type univar_func)
	:m_Operation(no_op),
	m_LHSExpr(univar_func),
	m_RHSExpr(empty_expr)
{
}


cFuncExpr::cFuncExpr(operation_type operation, expr_type univar_func1, expr_type univar_func2)
	:m_Operation(operation),
	m_LHSExpr(univar_func1),
	m_RHSExpr(univar_func2)
{
}

cFuncExpr::cFuncExpr(const cFuncExpr &func_expr)
{
	m_Operation = func_expr.m_Operation;
	m_LHSExpr = func_expr.m_LHSExpr;
	m_RHSExpr = func_expr.m_RHSExpr;	
}

cFuncExpr& cFuncExpr::operator=(const cFuncExpr& func_expr)
{
	if(&func_expr != this)
	{
		m_Operation = func_expr.m_Operation;
		m_LHSExpr = func_expr.m_LHSExpr;
		m_RHSExpr = func_expr.m_RHSExpr;
		
	}
	return *this;
}

cFuncExpr::~cFuncExpr()
{}

bool cFuncExpr::operator==(const cFuncExpr& fnc_expr)const
{
//	bool aaa = m_Operation == fnc_expr.m_Operation;
//	boost::apply_visitor(cOutputVisitor(), fnc_expr.m_Operation);
//	boost::apply_visitor(cOutputVisitor(), m_Operation);
//	aaa = m_LHSExpr == fnc_expr.m_LHSExpr;
//	aaa = m_RHSExpr == fnc_expr.m_RHSExpr;
//	if(m_Operation == fnc_expr.m_Operation && m_LHSExpr == fnc_expr.m_LHSExpr && m_RHSExpr == fnc_expr.m_RHSExpr)	
//		return true;
	
	std::stringstream ss_this;
	std::stringstream ss_that;
	ss_this << *this;
	ss_that << fnc_expr;
//	std::cout << ss_this.str();
//	std::cout << ss_that.str();
	return ss_this.str() == ss_that.str();
}

void cFuncExpr::simplify()
{
	cSimplifyVisitor simplify_vis(m_LHSExpr, m_RHSExpr, m_Operation);
	boost::apply_visitor(simplify_vis, m_Operation);
}

cFuncExpr cFuncExpr::derivative()const
{
	cFuncExpr fnc = derivative_impl();
	fnc.simplify();
	return fnc;
}

cFuncExpr cFuncExpr::derivative_impl()const
{
	cFuncExpr new_expr;
	cExprDiffVisitor diff_visitor(new_expr, m_LHSExpr, m_RHSExpr);
	boost::apply_visitor(diff_visitor, m_Operation);
	return new_expr;
}

cFuncExpr cFuncExpr::primitive()const
{

}

std::ostream& operator<<(std::ostream& out, const cFuncExpr& func_expr)
{
	const Composition* composition = boost::get<Composition>(&func_expr.m_Operation);
	auto poly = boost::get<cUnivarPolynomial<double> >(&func_expr.m_LHSExpr);
	auto var = boost::get<cVariable>(&func_expr.m_RHSExpr);
	if(composition && poly && var)
	{
		out << std::make_pair(*poly, *var);
		return out;
	}
	boost::apply_visitor(cOutputVisitor(), func_expr.m_LHSExpr);
	const NoOp* no_op = boost::get<NoOp>(&func_expr.m_Operation);
	if(no_op)
		return out;

	if(composition)
		out << "(";
	else
		boost::apply_visitor(cOutputVisitor(), func_expr.m_Operation);

	boost::apply_visitor(cOutputVisitor(), func_expr.m_RHSExpr);

	if(composition)
		out << ")";
	return out;
}


