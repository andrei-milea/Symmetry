#ifndef PERMUTATION_H_
#define PERMUTATION_H_ 

#include <array>
#include <initializer_list>
#include<boost/lexical_cast.hpp>
#include <iostream>
#include <boost/assert.hpp>
#include "factorial.h"

//namespace tr1 = std::tr1;


template <std::size_t N>
class cPermElem
{
public:
	typedef cPermElem<N> SelfType;

public:
	//constructors
	cPermElem()
	{
		for(std::size_t index = 1; index <= N; index++)
		{
			m_PermArray[index] = index;
		}
	};
	cPermElem(std::array<std::size_t, N+1> &permutation_array)
		:m_PermArray(permutation_array)
	{};
	cPermElem(std::initializer_list<std::size_t> perm_sq)
	{
		cPermElem();
		for(std::initializer_list<std::size_t>::iterator iter = perm_sq.begin();
			   	iter < perm_sq.end()-1; iter++)
		{
			if(*iter <= N && *iter != 0)
			{
				m_PermArray[(*iter)] = *(iter+1);
			}
			else
			{
				BOOST_ASSERT(false);
			}
		}
		m_PermArray[*(perm_sq.end()-1)] = *perm_sq.begin();
	};

	//copy constructor and assign operator
	cPermElem(const SelfType &permutation)
	{
		m_PermArray = permutation.GetPermutationArray();
	};
	SelfType operator=(const SelfType &permutation)
	{
		return m_PermArray = permutation.GetPermutationArray();
	};

	~cPermElem()
	{};


	//getter,setter
	std::array<std::size_t, N+1> GetPermutationArray()const
	{
		return m_PermArray;
	};
	void SetPermutationArray(std::array<std::size_t, N+1> permutation_array)
	{
		m_PermArray = permutation_array;
	};

	//permutation mutiplication operator
	SelfType operator*(const SelfType &perm)const
	{
		std::array<std::size_t, N+1> temp_perm;
		for(std::size_t index = 1; index <= N; index++)
		{
			temp_perm[index] = perm.GetPermutationArray()[m_PermArray[index]];
		}
		return temp_perm;
	};

	bool operator==(const SelfType &perm)
	{
		for(std::size_t index = 1; index <= N; index++)
		{
			if(m_PermArray[index] != perm.GetPermutationArray()[index])
			{
				return false;
			}
		}
		return true;
	}

	friend std::ostream& operator<<(std::ostream &of, const SelfType &perm)
	{
		std::string perm_index;
		std::string perm_val;
		for(std::size_t index = 1; index <= N; index++)
		{
			perm_index += boost::lexical_cast<std::string>(index) + " ";
			perm_val += boost::lexical_cast<std::string>(perm.GetPermutationArray()[index]) + " ";
		}
		return std::cout<<perm_index<<"\n"<<perm_val<<"\n";
	};

	std::size_t GetImage(const std::size_t set_element)const
	{
		return m_PermArray[set_element];
	};

public:
	static SelfType GetIdentity()
	{
		return SelfType();
	};

	//GroupSize = permutation_size!
	static const std::size_t GroupSize = Factorial<N>::value;


private:
	std::array<std::size_t, N+1> m_PermArray;
};

typedef cPermElem<1> cTransp;

#endif


