#ifndef _FUNC_EXPR_H
#define _FUNC_EXPR_H

#include "logarithm.h"
#include "exponential.h"
#include "abs_val.h"
#include "trig_funcs.h"
#include "univar_polynomial.h"
#include "univar_func.h"
#include "binary_op.h"
#include "variable.h"

#include <boost/variant.hpp>
#include <boost/variant/recursive_wrapper.hpp>

struct cEmptyExpr
{
	bool operator==(const cEmptyExpr &expr)const
	{
		return true;
	}

};

inline std::ostream& operator<<(std::ostream& out, const cEmptyExpr& expr)
{
	out << "empty_expr";
	return out;
}

//suppported functions
typedef boost::variant<cSine<double>,
					cCosine<double>,
					cTangent<double>,
					cCotangent<double>,
					cAcotangent<double>,
					cAsine<double>,
					cAcosine<double>,
					cAtangent<double>,
					cUnivarPolynomial<double>,
					cExponential<double>,
					cLogarithm<double>,
					cAbsVal<double>,
					boost::recursive_wrapper<cFuncExpr>,
					cVariable,
					cEmptyExpr,
					double > expr_type;

//suppported operations
typedef boost::variant< Addition,
					Multiplication,
					Division,
					Subtraction,
					Composition,
					Power,
					NoOp > operation_type;


/*!
 * holds a compound function expression (i.e. (sin(x) + e^x)*cos(x))
 * implements the 'symbolic' functionality
*/
class cFuncExpr
{
public:
	cFuncExpr();

	cFuncExpr(expr_type univar_func);

	cFuncExpr(operation_type operation, expr_type univar_func1, expr_type univar_func2);

	cFuncExpr(const cFuncExpr &func_expr);

	cFuncExpr &operator=(const cFuncExpr& func_expr);
	
	bool operator==(const cFuncExpr& fnc_expr)const;

	~cFuncExpr();

	/*!
	 * setters and getters
	*/
	operation_type getOperation()const
	{	return m_Operation;		}
	expr_type getLHSExpression()const
	{	return m_LHSExpr;		}
	expr_type getRHSExpression()const
	{	return m_RHSExpr;		}
	void setOperation(const operation_type &op)
	{	m_Operation = op;		}
	void setLHSExpression(const expr_type &expr)
	{	m_LHSExpr = expr;		}
	void setRHSExpression(const expr_type &expr)
	{	m_RHSExpr = expr;		}
	

	/*!
	 * returns a vector containing all the variables used in expression
	*/
	std::vector<cVariable> getVariables()const;

	/*!
	 * siplifies the expression by partially evaluating subexpressions
	*/
	void simplify();

	/*!
	 * siplifies the expression by matching trigonometric identities
	*/
	void trig_simplify();

	/*!
	 * expand multiplications and powers removing paranthesis
	*/
	void expand();

	/*!
	 * try to factor expression
	*/
	void factor();

	cFuncExpr derivative()const;

	/*!
	 * compute the partial derivative with respect to the given variable
	*/
	cFuncExpr partial_derivative(const cVariable& var)const;

	cFuncExpr primitive()const;

	/*!
	 * substitute var1 with var2 in expression recursively
	*/
	void substitute(const cVariable& var1, const cVariable& var2);

	/*!
	 * evaluates the expression by substituting the variable with the given value
	 * an exception is thrown if the substitution fails
	*/
	expr_type operator()(const cVariable &var,double arg)const;

	/*!
	 * plots the functional expression using the plotLine function
	 * can be used only for expressions with one or two variables
	*/
	std::vector<std::tuple<double, double, double> > plotPoints(double min, double max, double increment)const;

	/*!
	 * prints func expr as tree structure --for debugging purposes
	*/
	void printTree(const expr_type* root = nullptr)const;
	void printOp()const;

private:
	/*!
	 * returns the graph if the function has only 1 variable
	 * the first and second argument specify which variable 
	 * is already computed and its value -- used in plotPoints
	*/
	std::vector<std::tuple<double, double, double> > plotLine(std::size_t pos, double var, double min, double max,
		   															double increment, bool fixed = false)const;
	double getValue(const expr_type &expr)const
	{
		const double *val = boost::get<double>(&expr);
		if(val == nullptr)
			throw std::runtime_error("failed to get value, the expression doesn't contain a value");
		return *val;
	}

private:
operation_type m_Operation;
expr_type m_LHSExpr;
expr_type m_RHSExpr;

//friend classes
friend class cExprDiffVisitor;
friend class cExprPartDiffVisitor;
friend class cDiffVisitor;
friend class cSimplifyVisitor;
template <typename T> friend class cEvalExprlVisitor;
template <typename T> friend class cEvalVisitor;
friend std::ostream& operator<<(std::ostream& out, const cFuncExpr& func_expr);
};


std::ostream& operator<<(std::ostream& out, const cFuncExpr& func_expr);

#endif

