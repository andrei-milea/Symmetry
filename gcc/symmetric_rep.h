#ifndef SYMMETRIC_REP_
#define SYMMETRIC_REP_

#include <list>
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
	typedef typename std::vector<T>::const_iterator Iter;
	typedef cSymmetricRep<T> SelfType;

public:
	//constructors
	cSymmetricRep()
	{};

	cSymmetricRep(std::vector<T> &generators_set)
		:m_GenSet(generators_set)
	{
	};

	//gcc bug?
	/*cSymmetricRep(std::initializer_list<T> perm_list)
	{
		for(std::initializer_list<std::size_t>::iterator iter = perm_list.begin();
			   	iter < perm_list.end()-1; iter++)
		{
			m_GenSet.insert(m_GenSet.end(),(*iter));
		}
	};*/

	//copy constructor and assign operator
	cSymmetricRep(const SelfType &sym_rep)		
	{
		m_GenSet = sym_rep.GetGeneratorsSet();
	};
	cSymmetricRep& operator=(const SelfType& sym_rep)
	{
		m_GenSet = sym_rep.GetGeneratorsSet();
	};
	
	~cSymmetricRep()
	{};


	bool Contains(T &element)const
	{
		std::vector<T> elements = GetElementsDimino();
		return (std::find(elements, element) != elements.end());
	};

	std::vector<T> GetElementsNaive()const
	{
		std::vector<T> elements;
		elements.push_back(T::GetIdentity());
		for( std::size_t index = 0; index < elements.size(); index++)
		{
			for(Iter set_iter = m_GenSet.begin();
				set_iter != m_GenSet.end(); set_iter++)
			{
				T element = (*set_iter) * elements[index];
				if(find(elements.begin(), elements.end(), element) == elements.end())
				{
					elements.push_back(element);
				}
			}

		}
		return elements;
	};

	std::vector<T> GetElementsDimino()const
	{
		//generate cyclic group of the first generator	
		std::vector<T> elements = GetCyclicSubgroup(*m_GenSet.begin());
	
		//inductive step
		for(Iter it = m_GenSet.begin(); it != m_GenSet.end(); it++)
		{
			if(find(elements.begin(),elements.end(),*it) == elements.end())
			{
				std::size_t new_order = elements.size() + 1;
				AddCoset(elements,*it);

				while(new_order < elements.size())
				{
					for(Iter it1 = m_GenSet.begin(); it1 != m_GenSet.end(); it1++)
					{
						T element = *it1 * elements[new_order];
						if(find(elements.begin(), elements.end(), element) == elements.end())
						{
							AddCoset(elements, element)	;
						}
					}
					new_order += elements.size();
				}
			}
		}
		return elements;
	};

	std::vector<std::size_t> GetOrbit(const std::size_t &set_element)const
	{
		std::vector<std::size_t> orbit;
		orbit.push_back(set_element);
		std::vector<T> elements = GetElementsDimino();

		for(std::size_t index = 0; index < orbit.size(); index++)
		{
			for(Iter it1 = elements.begin(); it1 != elements.end(); it1++)
			{
				std::size_t image = it1->GetImage(orbit[index]);
				if(find(orbit.begin(), orbit.end(), image) == orbit.end())
				{
					orbit.push_back(image);
				}
			}
		}
		return orbit;
	};

	//getter, setter
	const std::vector<T> &GetGeneratorsSet()const
	{
		return m_GenSet;
	};
	
	void SetGeneratorsSet(const std::vector<T> &gen_set)
	{
		m_GenSet = gen_set;
	};

	void AddGenerator(const T &element)
	{
		m_GenSet.push_back(element);
	};

	bool operator==(const SelfType &symgrp)const
	{
		return m_GenSet == symgrp.GetGeneratorsSet();
	};

	bool operator!=(const SelfType &symgrp)const
	{
		return !(*this == symgrp);
	};

	T GetIdentity()const
	{
		return T::GetIdentity();
	};

	std::vector<T> GetCyclicSubgroup(const T& element)const
	{
		T temp_el = element;
		std::vector<T> cyclic_group;
	    cyclic_group.push_back(T::GetIdentity());
		while(temp_el != T::GetIdentity())
		{
			cyclic_group.push_back(temp_el);
			temp_el = temp_el * element;
		}
		return cyclic_group;
	};


	void AddCoset(std::vector<T>& elements, const T& element)const
	{
		std::size_t order = elements.size();
		for(std::size_t index = 0; index < order; index++)
		{
			T el = element * elements[index];
			if(find(elements.begin(), elements.end(), el) == elements.end())
			{
				elements.push_back(el);
			}
		}
	};

private:
	std::vector<T> m_GenSet;
};

#endif

