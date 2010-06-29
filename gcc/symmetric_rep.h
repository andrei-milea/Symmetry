#ifndef SYMMETRIC_REP_
#define SYMMETRIC_REP_

#include <tr1/unordered_set>
#include <algorithm>
#include <iostream>
#include <boost/random.hpp>
#include <ctime>
#include <initializer_list>


//symmertric group internal representation
//used only from cGroup
template <typename T>
class cSymmetricRep
{
public:
	typename tr1::unordered_set<T>::iterator IteratorType;
	typedef cSymmetricRep<T> SelfType;

public:
	//constructors
	cSymmetricRep()
	{};

	cSymmetricRep(tr1::unordered_set<T> &generators_set)
		:m_GeneratorsSet(generators_set)
	{
	};
	cSymmetricRep(std::initializer_list<T> perm_list)
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


	tr1::unordered_set<T> GetElementstNaive()const
	{
		tr1::unordered_set<T> elements;
		elements.insert(T::GetIdentity());
		std::for_each(elements.begin(),elements.end(), [&m_GeneratorsSet,&elements]
			(typename tr1::unordered_set<T>::iterator it)
			{
				for(tr1::unordered_set<T> set_iter = m_GeneratorsSet.begin();
					set_iter != m_GeneratorsSet.end(); set_iter++)
				{
					T element = (*set_iter) * (*it);
					if(elements.find(element) == elements.end())
					{
						elements.insert(element);
					}
				}

			});
	};

	tr1::unordered_set<T> GetElementsDimino()const
	{
		//generate cyclic group of the first generator	
		tr1::unordered_set<T> elements = GetCyclicGroup(*m_GeneratorsSet.begin());
		

	};


	tr1::unordered_set<T> GetCyclicGroup(T& element)const
	{
		tr1::unordered_set<T> cyclic_group;
		while(element != T::GetIdentity())
		{
			cyclic_group.insert(element);
			element = element * element;
		}
	};


	//getter, setter
	tr1::unordered_set<T> &GetGeneratorsSet()const
	{
		return m_GeneratorsSet;
	};
	void SetGeneratorsSet(tr1::unordered_set<T> &gen_set)
	{
		m_GeneratorsSet = gen_set;
	};

private:
	tr1::unordered_set<T> m_GeneratorsSet;
};

#endif

