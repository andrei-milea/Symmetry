
#include "func_expr.h"
#include "func_expr_visitor.h"
#include "func_expr_dif.h"
#include "func_expr_eval.h"

#include <utility>
#include <tuple>
#include <sstream>
#include <boost/numeric/ublas/vector.hpp>

using namespace boost::numeric;

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

	
std::vector<cVariable> cFuncExpr::getVariables()const
{
	static int levels = 0;
	levels++;
	std::vector<cVariable> vars;
	const cVariable *var_left = boost::get<cVariable>(&m_LHSExpr);
	const cVariable *var_right = boost::get<cVariable>(&m_RHSExpr);
	const cFuncExpr *fnc_left = boost::get<cFuncExpr>(&m_LHSExpr);
	const cFuncExpr *fnc_right = boost::get<cFuncExpr>(&m_RHSExpr);
	if(var_left)
	{
		vars.push_back(*var_left);
	}
	else if(fnc_left)
	{
		auto newvars = fnc_left->getVariables();
		vars.insert(vars.end(), newvars.begin(), newvars.end());
	}
	if(var_right)
	{
		vars.push_back(*var_right);
	}
	else if(fnc_right)
	{
		auto newvars = fnc_right->getVariables();
		vars.insert(vars.end(), newvars.begin(), newvars.end());
	}

	levels--;
	if(levels == 0)
	{
		//remove duplicates
		std::sort(vars.begin(), vars.end());
		vars.erase(std::unique(vars.begin(), vars.end()), vars.end());
	}
	return vars;
}

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

expr_type cFuncExpr::operator()(const cVariable &var, double arg)const
{
	cEvalExprlVisitor<double> eval_vis(m_LHSExpr, m_RHSExpr, var, arg);
	return boost::apply_visitor(eval_vis, m_Operation);
}

std::vector<std::tuple<double, double, double> > cFuncExpr::plotLine(std::size_t pos, double var, double min, double max,
	   																	double increment)const
{
	const double min_angle =  boost::math::constants::pi<double>() / 1.005;

	auto vars = getVariables();
	assert(vars.size() == 1);

	std::vector<std::tuple<double, double, double> > points;
	double val_iter = min;
	while(val_iter <= max)
	{
		double x1 = val_iter;
		double y1 = getValue(operator()(vars[0], x1));

		double x2 = x1 + increment;
		double y2 = getValue(operator()(vars[0], x2));

		double x3 = x2 + increment;
		double y3 = getValue(operator()(vars[0], x3));

		ublas::vector<double> ba(2);	ba(0) = x1-x2;	ba(1) = y1 - y2;
		ublas::vector<double> bc(2);	bc(0) = x3-x2;	bc(1) = y3 - y2;

		double angle = std::acos(ublas::inner_prod(ba, bc) / (ublas::norm_2(ba) * ublas::norm_2(bc)));

		if(std::abs(angle) < min_angle)
		{
			auto line = plotLine(pos, var, x1, x3, increment/2.0);
			points.insert(points.end(), line.begin(), line.end());
		}
		else
		{
			if(pos == 1)
			{
				points.push_back(std::tie(var, x1, y1));
				points.push_back(std::tie(var, x2, y2));
				points.push_back(std::tie(var, x3, y3));
			}
			if(pos == 2)
			{
				points.push_back(std::tie(x1, var, y1));
				points.push_back(std::tie(x2, var, y2));
				points.push_back(std::tie(x3, var, y3));
			}
			if(pos == 3)
			{
				points.push_back(std::tie(x1, y1, var));
				points.push_back(std::tie(x2, y2, var));
				points.push_back(std::tie(x3, y3, var));
			}
		}
		val_iter = x3 + increment;
	}

	return points;
}
	
std::vector<std::tuple<double, double, double> > cFuncExpr::plotPoints(double min, double max, double increment)const
{
	auto vars = getVariables();
	std::vector<std::tuple<double, double, double> > points;
	if(vars.size() == 1)
	{
		return plotLine(3, 0, min, max, increment);
	}
	else if(vars.size() == 2)
	{
		for(auto val_iter = min; val_iter < max; val_iter += increment)
		{
			auto temp_expr = operator()(vars[0], val_iter);
			cFuncExpr *temp_fnc = boost::get<cFuncExpr>(&temp_expr);
			assert(temp_fnc);
			auto line = temp_fnc->plotLine(1, val_iter, min, max, increment);
			points.insert(points.end(), line.begin(), line.end());
		}
		for(auto val_iter = min; val_iter < max; val_iter += increment)
		{
			auto temp_expr = operator()(vars[1], val_iter);
			cFuncExpr *temp_fnc = boost::get<cFuncExpr>(&temp_expr);
			assert(temp_fnc);
			auto line = temp_fnc->plotLine(2, val_iter, min, max, increment);
			points.insert(points.end(), line.begin(), line.end());
		}
	}
	else
	{
		throw std::runtime_error("can only provide graph for functions with 1 or 2 variables");
	}
	return points;
}

void cFuncExpr::printTree(const expr_type* root)const
{
	static int idx = 0;
	idx++;
	if(nullptr == root)
	{
		std::cout << "\n";
		printTree(&m_LHSExpr);
		std::cout << ":::::::";
		printOp();
		std::cout << ":::::::";
		printTree(&m_RHSExpr);
	}
	else if(const cFuncExpr *fnc_expr = boost::get<cFuncExpr>(root))
	{
		printTree(&fnc_expr->m_LHSExpr);
		fnc_expr->printOp();
		printTree(&fnc_expr->m_RHSExpr);
	}
	else
	{
		std::cout << root->type().name() << "--level:" << idx << "--";
	}
	idx--;
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


