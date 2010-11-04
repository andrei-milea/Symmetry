#ifndef PERMUTATION_H_
#define PERMUTATION_H_ 

#include <vector>
#include <initializer_list>
#include<boost/lexical_cast.hpp>
#include <iostream>
#include <cassert>
#include "std_ex.h"
#include <algorithm>


	/*****************************************
	 * permutation element class 
	*****************************************/

class cPermElem
{
public:

	//constructors
	cPermElem()
		:m_PermArray(NULL),
			m_Size(0)
	{};

	cPermElem(std::size_t size)
		:m_PermArray(NULL),
		m_Size(size)
	{
		m_PermArray = new std::vector<std::size_t>(m_Size);
		for(std::size_t index = 0; index < size; index++)
		{
			(*m_PermArray)[index] = index + 1;
		}
	};

	cPermElem(std::vector<std::size_t> &permutation_array)
	{
		m_Size = permutation_array.size();
		m_PermArray = new std::vector<std::size_t>(m_Size);
		(*m_PermArray) = permutation_array;
	};
	
	cPermElem(std::vector<std::size_t> *permutation_array)
	{

		m_PermArray = permutation_array;
		m_Size = m_PermArray->size();
	};

	//cycle constructor
	cPermElem(std::size_t size, const std::initializer_list<std::size_t> &perm_sq)
		:m_PermArray(NULL)
	{
		m_Size = size;
		m_PermArray = new std::vector<std::size_t>(m_Size);
		for(std::size_t index = 0; index < m_Size; index++)
		{
			(*m_PermArray)[index] = index + 1;
		}
		for(std::initializer_list<std::size_t>::const_iterator iter = perm_sq.begin();
			  	iter != perm_sq.end()-1; iter++)
		{
			if(*iter <= m_Size && *iter != 0)
			{
				(*m_PermArray)[(*iter) - 1] = *(iter+1);
			}
		}
		(*m_PermArray)[(*(perm_sq.end()-1)) - 1] = *perm_sq.begin();
	};

	//image constructor
	cPermElem(const std::initializer_list<std::size_t> &perm_sq)
		:m_PermArray(NULL)
	{
		m_Size = perm_sq.size();
		m_PermArray = new std::vector<std::size_t>(m_Size);

		std::size_t index = 0;
		for(std::initializer_list<std::size_t>::const_iterator iter = perm_sq.begin();
			  	iter != perm_sq.end(); iter++)
		{
			(*m_PermArray)[index] = (*iter);
			index++;
		}
	};



	//copy constructor and assign operator
	cPermElem(const cPermElem &permutation)
	{
		m_Size = permutation.GetSize();
		m_PermArray = new std::vector<std::size_t>(m_Size);
		(*m_PermArray) = (*permutation.GetPermutationArray());
	};

	cPermElem& operator=(const cPermElem &permutation)
	{
		m_Size = permutation.GetSize(); 
		m_PermArray = new std::vector<std::size_t>(m_Size);
		(*m_PermArray) = (*permutation.GetPermutationArray());
		return *this;
	};

	~cPermElem()
	{
		if(m_PermArray)
			delete m_PermArray;
	};

	//getter
	std::vector<std::size_t>* GetPermutationArray()const
	{
		return m_PermArray;
	};

	//permutation mutiplication operator
	cPermElem operator*(const cPermElem &perm)const
	{
		assert(perm.GetSize() == m_Size);
		std::vector<std::size_t> temp_perm(m_Size);
		for(std::size_t index = 0; index < m_Size; index++)
		{
			temp_perm[index] = (*perm.GetPermutationArray())[(*m_PermArray)[index] - 1];
		}
		return cPermElem(temp_perm);
	};

	bool operator==(const cPermElem &perm)const
	{
		if(perm.GetSize() != m_Size)
			return false;
		for(std::size_t index = 0; index < m_Size; index++)
		{
			if((*m_PermArray)[index] != (*perm.GetPermutationArray())[index])
			{
				return false;
			}
		}
		return true;
	};

	bool operator!=(const cPermElem &perm)const
	{
		return !(perm == *this);
	};


	friend std::ostream& operator<<(std::ostream &of, const cPermElem &perm)
	{
		std::string perm_index;
		std::string perm_val;
		for(std::size_t index = 0; index < perm.m_Size; index++)
		{
			perm_index += boost::lexical_cast<std::string>(index+1) + " ";
			perm_val += boost::lexical_cast<std::string>((*perm.GetPermutationArray())[index]) + " ";
		}
		return std::cout<<perm_index<<"\n"<<perm_val;
	};

	std::size_t GetImage(const std::size_t set_element)const
	{
		return (*m_PermArray)[set_element - 1];
	};

	cPermElem GetMultInverse()const
	{
		std::vector<std::size_t> perm_array(m_Size);
		for(std::size_t index = 0; index < m_Size; index++) 
		{
			 perm_array[(*m_PermArray)[index] - 1] = index + 1;
		}
		return cPermElem(perm_array);
	};

	cPermElem GetAdInverse()const
	{
		return GetMultInverse();
	};

	std::size_t GetSize()const
	{
		return m_Size;
	};

	void SetSize(const std::size_t size)
	{
		m_Size = size;
	};

	template <typename BINOP>
	cPermElem GetIdentity(BINOP binop)const
	{
		return cPermElem(m_Size);
	};


private:
	std::vector<std::size_t> *m_PermArray;
	std::size_t m_Size;
};


#endif


