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
	typedef typename std::vector<T>::iterator Iter;
	typedef cSymmetricRep<T> SelfType;
	typedef typename T ElementType;

public:
	//constructors
	cSymmetricRep()
	{};

	cSymmetricRep(std::vector<T> &generators_set)
		:m_GenSet(generators_set)
	{
	};
	cSymmetricRep(std::initializer_list<T> perm_list)
	{

	};

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


	std::vector<T> GetElementstNaive()const
	{
		std::vector<T> elements;
		elements.push_back(T::GetIdentity());
		std::for_each(elements.begin(),elements.end(), [&m_GenSet,&elements]
			(typename std::vector<T>::Iter it)
			{
				for(std::vector<T> set_iter = m_GenSet.begin();
					set_iter != m_GenSet.end(); set_iter++)
				{
					T element = (*set_iter) * (*it);
					if(elements.find(element) == elements.end())
					{
						elements.push_back(element);
					}
				}

			});
	};

	std::vector<T> GetElementsDimino()const
	{
		//generate cyclic group of the first generator	
		std::vector<T> elements = GetCyclicGroup(*m_GenSet.begin());

		//inductive step
		for(Iter it = m_GenSet.begin(); it != m_GenSet.end(); it++)
		{
			if(find(elements.begin(),elements.end(),*it) == elements.end())
			{
				AddCoset(elements,*it);

				std::size_t new_order = 0;
				while(new_order < elements.size())
				{
					new_order = elements.size() + 1;
					for(Iter it1 = m_GenSet.begin(); it1 != m_GenSet.end(); it1++)
					{
						element = *it * elements[new_order];
						if(find(elements.begin(), elements.end(), element) == elements.end())
						{
							AddCoset(elements, element)	;
						}
					}
					new_order += elements.size();
				}
			}
		}
	};

	void SetElements()
	{
		m_Elements = GetElementsDimino();
	};

	std::vector<std::size_t> GetOrbit(const std::size_t &set_element)const
	{
		typename std::vector<std::size_t>::iterator _Iter;
		std::vector<std::size_t> orbit;
		orbit.push_back(set_element);
		std::for_each(orbit.begin(), orbit.end(), [&m_GenSet, &orbit](_Iter it)
				{
					for(Iter it1 = m_GenSet.begin(); it1 != m_GenSet.end(); it1++)
					{
						std::size_t image = it1->GetImage(*it);
						if(find(orbit.begin(), orbit.end(), image) == orbit.end())
						{
							orbit.push_back(image);
						}
					}
				})
	};

	void InsertElement(const T& element)
	{
		m_Elements.push_back(element);
	};


private:
	void AddCoset(std::vector<T>& elements, const T& element)
	{
		std::size_t order = elements.end();
		for(std::size_t index = 0; index < order; index++)
		{
			elements.push_back(element * elements[index]);
		}
	};

	std::vector<T> GetCyclicGroup(T& element)const
	{
		std::vector<T> cyclic_group = T::GetIdentity();
		while(element != T::GetIdentity())
		{
			cyclic_group.push_back(element);
			element = element * element;
		}
		return cyclic_group;
	};

	//getter, setter
	std::vector<T> &GetGeneratorsSet()const
	{
		return m_GenSet;
	};
	void SetGeneratorsSet(std::vector<T> &gen_set)
	{
		m_GenSet = gen_set;
	};

private:
	std::vector<T> m_GenSet;
	std::vector<T> m_Elements;
};

#endif

