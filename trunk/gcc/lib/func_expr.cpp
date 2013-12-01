
#include "func_expr.h"
#include "func_expr_visitor.h"
#include "func_expr_dif.h"
#include "func_expr_eval.h"

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
	std::ostringstream stream;
	std::streambuf* buf = std::cout.rdbuf(stream.rdbuf());
	std::cout << *this;
	std::string str1 = stream.str();
	stream.str("");
	stream.clear();
	std::cout << fnc_expr;
	std::string str2 = stream.str();
	std::cout.rdbuf(buf);

	std::cout << "str1 " << str1 << "str2 " << str2 << "\n";

	return str1 == str2;
}

expr_type cFuncExpr::operator()(const cVariable &var, const double arg)const
{
	cEvalExprlVisitor<double> eval_vis(m_LHSExpr, m_RHSExpr, var, arg);
	return boost::apply_visitor(eval_vis, m_Operation);
}

void cFuncExpr::printTree(const expr_type* root)const
{
	if(nullptr == root)
	{
		std::cout << "\n";
		printTree(&m_LHSExpr);
		std::cout << ":::::::";
		printOp();
		std::cout << ":::::::";
		printTree(&m_RHSExpr);

		return;
	}

	if(const cFuncExpr *fnc_expr = boost::get<cFuncExpr>(root))
	{
		printTree(&fnc_expr->m_LHSExpr);
		fnc_expr->printOp();
		printTree(&fnc_expr->m_RHSExpr);

		return;
	}
	
	std::cout << root->type().name() << "-";

}

void cFuncExpr::printOp()const
{
	std::cout << m_Operation.type().name() << "-";
}

void cFuncExpr::simplify()
{
	cSimplifyVisitor simplify_vis(m_LHSExpr, m_RHSExpr, m_Operation);
	boost::apply_visitor(simplify_vis, m_Operation);
}

cFuncExpr cFuncExpr::derivative()const
{
	cFuncExpr new_expr;
	cExprDiffVisitor diff_visitor(new_expr, m_LHSExpr, m_RHSExpr);
	boost::apply_visitor(diff_visitor, m_Operation);
	new_expr.simplify();
	return new_expr;
}


cFuncExpr cFuncExpr::partial_derivative(const cVariable& var)const
{
	cFuncExpr new_expr;
	cExprPartDiffVisitor part_diff_visitor(new_expr, m_LHSExpr, m_RHSExpr, var);
	boost::apply_visitor(part_diff_visitor, m_Operation);
	new_expr.simplify();
	return new_expr;
}

cFuncExpr cFuncExpr::primitive()const
{
	//TODO
	return cFuncExpr();
}

void cFuncExpr::substitute(const cVariable& var1, const cVariable& var2)
{
	cVariable* var_left = boost::get<cVariable>(&m_LHSExpr);
	cFuncExpr* fnc_left = boost::get<cFuncExpr>(&m_LHSExpr);
	cVariable* var_right = boost::get<cVariable>(&m_RHSExpr);
	cFuncExpr* fnc_right = boost::get<cFuncExpr>(&m_RHSExpr);
	if(var_left)
	{
		if(*var_left == var1)
			*var_left = var2;
	}
	else if(fnc_left)
	{
		fnc_left->substitute(var1, var2);
	}
	if(var_right)
	{
		if(*var_right == var1)
			*var_right = var2;
	}
	else if(fnc_right)
	{
		fnc_right->substitute(var1, var2);
	}
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

	const cFuncExpr *left_expr = boost::get<cFuncExpr>(&func_expr.m_LHSExpr);
	const NoOp* no_op = boost::get<NoOp>(&func_expr.m_Operation);
	const NoOp* left_no_op = boost::get<NoOp>(&left_expr->m_Operation);

	if(!no_op && !left_no_op && !composition && left_expr && !(func_expr.m_Operation == left_expr->m_Operation))
	{
		out << "(";
		boost::apply_visitor(cOutputVisitor(), func_expr.m_LHSExpr);
		out << ")";
	}
	else
	{
		boost::apply_visitor(cOutputVisitor(), func_expr.m_LHSExpr);
	}
	
	if(composition)
		out << "(";
	else
		boost::apply_visitor(cOutputVisitor(), func_expr.m_Operation);

	const cFuncExpr *right_expr = boost::get<cFuncExpr>(&func_expr.m_RHSExpr);
	const NoOp* right_no_op = boost::get<NoOp>(&right_expr->m_Operation);
	if(!no_op && !right_no_op && !composition && right_expr && !(func_expr.m_Operation == right_expr->m_Operation))
	{
		out << "(";
		boost::apply_visitor(cOutputVisitor(), func_expr.m_RHSExpr);
		out << ")";
	}
	else
	{
		boost::apply_visitor(cOutputVisitor(), func_expr.m_RHSExpr);
	}

	if(composition)
		out << ")";
	return out;
}


