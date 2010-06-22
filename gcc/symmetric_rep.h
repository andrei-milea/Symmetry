#ifndef SYMMETRIC_REP_
#define SYMMETRIC_REP_

#include <tr1/unordered_set>
#include <algorithm>
#include <iostream>
#include <boost/random.hpp>
#include <ctime>


//symmertric group internal representation
//used only from cGroup
template <typename T, std::size_t ORDER>
class cSymmetricRep
{
public:
	typename tr1::unordered_set<T>::iterator IteratorType;
	typename cSymmetricRep<T, ORDER> SelfType;

public:
	//constructors
	cSymmetricRep()
	{};

	cSymmetricRep(tr1::unordered_set<T> &generators_set)
		:m_GeneratorsSet(generators_set)
	{
	};

	//copy constructor and assign operator
	cSymmetricRep(const SelfType &sym_rep)		
	{
		m_GeneratorsSet = sym_rep.GetGeneratorsSet();
	};
	cSymmetricRep& operator=(const SelfType& sym_rep)
	{
		m_GeneratorsSet = sym_rep.GetGeneratorsSet();
	};
	

	~cSymmetricRep()
	{};


	ListElementsNaive()
	{
		
	};
	ListElementsDimino()
	{

	};


	//getter, setter
	tr1::unorder_set<T> &GetGeneratorsSet()const
	{
		return m_GeneratorsSet;
	};
	void SetGeneratorsSet(tr1::unorder_set<T> &gen_set)
	{
		m_GeneratorsSet = gen_set;
	};

private:
	tr1::unordered_set<T> m_GeneratorsSet;
};

#endif

