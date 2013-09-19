




//template <typename T>
//cFuncExpr cSine<T>::primitive(const cVariable &var)const
//{
//	return cFuncExpr(Multiplication(), -1, cFuncExpr(Composition(), cCosine<T>(), var));
//}
//
////template <typename T>
//cFuncExpr cCosine<T>::primitive(const cVariable &var)const
//{
//	return cFuncExpr(Composition(), cSine<T>(), var);
//}
//
//template <typename T>
//cFuncExpr cTangent<T>::primitive(const cVariable &var)const
//{
//	return cFuncExpr(Multiplication(), -1.0, cFuncExpr(Composition(), cLogarithm<T>(), 
//					cFuncExpr(Composition(), cAbsVal<T>(), cFuncExpr(Composition(), cCosine<T>(), var))));
//}
//
//template <typename T>
//cFuncExpr cCotangent<T>::primitive(const cVariable &var)const
//{
//	return cFuncExpr(Composition(), cLogarithm<T>(), cFuncExpr(Composition(), cAbsVal<T>(), 
//				cFuncExpr(Composition(), cSine<T>(), var)));
//}
//
//template <typename T>
//cFuncExpr cAsine<T>::primitive(const cVariable &var)const
//{
//	return cFuncExpr(Addition(), cFuncExpr(Multiplication(), var, cFuncExpr(Composition(), cAsine<T>(), var)), 
//						cFuncExpr(Subtraction(), 1.0, cFuncExpr(Power(), var, 2.0)));
//}
//
//template <typename T>
//cFuncExpr cAcosine<T>::primitive(const cVariable &var)const
//{
//	return cFuncExpr(Subtraction(), cFuncExpr(Multiplication(), var, cFuncExpr(Composition(), cAcosine<T>(), var)), 
//						cFuncExpr(Subtraction(), 1.0, cFuncExpr(Power(), var, 2.0)));
//}
//
//template <typename T>
//cFuncExpr cAtangent<T>::primitive(const cVariable &var)const
//{
//	return cFuncExpr(Subtraction(), cFuncExpr(Multiplication(), var, cFuncExpr(Composition(), cAtangent<T>(), var)),
//			cFuncExpr(Multiplication(), 0.5, cFuncExpr(Composition(), cLogarithm<T>(), 
//				cFuncExpr(Addition(), 1.0, cFuncExpr(Power(), var, 2.0)))));
//}
//
//template <typename T>
//cFuncExpr cAcotangent<T>::primitive(const cVariable &var)const
//{
//	return cFuncExpr(Addition(), cFuncExpr(Multiplication(), var, cFuncExpr(Composition(), /*TODO*/cSine<T>(), var)),
//			cFuncExpr(Multiplication(), 0.5, cFuncExpr(Composition(), cLogarithm<T>(), 
//				cFuncExpr(Addition(), 1.0, cFuncExpr(Power(), var, 2.0)))));
//}
//
//template <typename T>
//cFuncExpr cExponential<T>::integral(const cVariable& var)const
//{
//	if(m_Base == boost::math::constants::e<T>())
//		return cFuncExpr(Composition(), cExponential<T>(), var);
//
//	return cFuncExpr(Multiplication(), 1/std::log(m_Base), cFuncExpr(Composition(), cExponential<T>(), var));
//}
//
//template <typename T>
//cFuncExpr cLogarithm<T>::integral(const cVariable& var)const
//{
//	if(m_Base == boost::math::constants::e<T>())	
//		return cFuncExpr(Subtraction(), cFuncExpr(Multiplication(), var, cFuncExpr(Composition(), cLogarithm<T>(), var)), var);
//
//	return cFuncExpr(Multiplication(), 1/std::log(m_Base), 
//			cFuncExpr(Subtraction(), cFuncExpr(Multiplication(), var, cFuncExpr(Composition(), cLogarithm<T>(), var)), var));
//}
//
//template <typename T>
//cFuncExpr cAbsVal<T>::integral(const cVariable& var)const
//{
//	return cFuncExpr(Division(), cFuncExpr(Multiplication(), var, cFuncExpr(Composition(), cAbsVal<T>(), var)), 2.0);
//}


