#ifndef SYMMETRIC_REP_
#define SYMMETRIC_REP_

#include <tr1/unordered_set>
#include <algorithm>
#include <iostream>
#include <boost/random.hpp>
#include <ctime>


//symmertric group internal representation
//used only from cGroup
template <typrename T>
class cSymmetricRep
{
	typename tr1::unordered_set<T>::iterator IteratorType;
public:
	//constructors
	cSymmetricRep()
		:m_GroupOrder(0)
	{};

	explicit cSymmetricRep(std::size_t group_order)
		:m_GroupOrder(group_order)
	{};
	
	cSymmetricRep(tr1::unordered_set<T> &generators_set)
		:m_GroupOrder(generators_set.size()),
		m_GeneratorsSet(generators_set)
	{
	};

	//copy constructor and assign operator
	
	

	~cSymmetricRep()
	{};


	ListElementsNaive()
	{

	};
	ListElementsDimino()
	{

	};

private:
	tr1::unordered_set<T> m_GeneratorsSet;
	std::size_t			  m_GroupOrder;
};

#endif

