#ifndef PERMUTATION_H_
#define PERMUTATION_H_ 

#include <vector>
#include <initializer_list>
#include<boost/lexical_cast.hpp>
#include <iostream>
#include <cassert>
#include "std_ex.h"
#include <algorithm>

/*!
  class representing a permutation (element)
  permutation is represented internally using
  an array of ints
*/
class cPermElem
{
public:

	/*!
	  default constructor for empty permutation
	*/
	cPermElem()
		:m_PermArray(nullptr),
			m_Size(0)
	{};

	/*!
	  constructor for identity permutation
	*/
	cPermElem(std::size_t size)
		:m_PermArray(nullptr),
		m_Size(size)
	{
		m_PermArray = new std::vector<std::size_t>(m_Size);
		for(std::size_t index = 0; index < size; index++)
		{
			(*m_PermArray)[index] = index + 1;
		}
	};


	/*!
	 constructor for permutation given as a cycle
	 using initializer_list
	 ie. (3,{1,3,2}) means 1->3 3->2 2->1
	*/
	cPermElem(std::size_t size, const std::initializer_list<std::size_t> &perm_sq)
		:m_PermArray(nullptr)
	{
		m_Size = size;
		m_PermArray = new std::vector<std::size_t>(m_Size);
		for(std::size_t index = 0; index < m_Size; index++)
		{
			(*m_PermArray)[index] = index + 1;
		}
		for(auto iter = perm_sq.begin(); iter != perm_sq.end()-1; iter++)
		{
			if(*iter <= m_Size && *iter != 0)
			{
				(*m_PermArray)[(*iter) - 1] = *(iter+1);
			}
		}
		(*m_PermArray)[(*(perm_sq.end()-1)) - 1] = *perm_sq.begin();
	};


	/*!
	  constructor for permutation given as an image  
	  using initializer_list
	  ie. {2,3,1} means 1->2 2->3 3->1
	*/
	cPermElem(const std::initializer_list<std::size_t> &perm_sq)
		:m_PermArray(nullptr)
	{
		m_Size = perm_sq.size();
		m_PermArray = new std::vector<std::size_t>(m_Size);

		std::size_t index = 0;
		for(auto iter = perm_sq.begin(); iter != perm_sq.end(); iter++)
		{
			(*m_PermArray)[index] = (*iter);
			index++;
		}
	};

	/*!
	  constructor for permutation given as an image  
	  using a vector
	  ie. vector a = {2,3,1} is the permutation 1->2 2->3 3->1
	*/
	cPermElem(std::vector<std::size_t> &perm_sq)
		:m_PermArray(nullptr)
	{
		m_Size = perm_sq.size();
		m_PermArray = new std::vector<std::size_t>(m_Size);

		std::size_t index = 0;
		for(auto iter = perm_sq.begin(); iter != perm_sq.end(); iter++)
		{
			(*m_PermArray)[index] = (*iter);
			index++;
		}
	};
	


	/*!
	  copy constructor and assignment operator
	*/
	cPermElem(const cPermElem &permutation)
	{
		m_Size = permutation.GetSize(); 
		if(0 != m_Size)
		{
			if(nullptr != m_PermArray)
				delete m_PermArray;
			m_PermArray = new std::vector<std::size_t>(m_Size);
			(*m_PermArray) = (*permutation.GetPermutationArray());
		}
		else
		{
			m_PermArray = nullptr;
		}
	};
	cPermElem& operator=(const cPermElem &permutation)
	{
		m_Size = permutation.GetSize(); 
		if(0 != m_Size)
		{
			if(nullptr != m_PermArray)
				delete m_PermArray;
			m_PermArray = new std::vector<std::size_t>(m_Size);
			(*m_PermArray) = (*permutation.GetPermutationArray());
		}
		else
		{
			m_PermArray = nullptr;
		}
		return *this;
	};

	~cPermElem()
	{
		if(m_PermArray)
			delete m_PermArray;
	};

	/*!
	  get the underlying permutation array
	*/
	std::vector<std::size_t>* GetPermutationArray()const
	{
		return m_PermArray;
	};

	/*!
	  permutation mutiplication operator (doesn't work in the true mathematical
	  meaning of composition-- aplies the first permutation first: A*B(x) -> B(A(x)) )
	  Complexity: O(n)
	*/
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
		return of<<perm_index<<"\n"<<perm_val<<"\n";
	};

	/*!
	  get the image of an element under the action
	  of the permution
	*/
	std::size_t GetImage(const std::size_t set_element)const
	{
		return (*m_PermArray)[set_element - 1];
	};

	/*!
	  returns the permutation inverse
	  Complexity: O(n)
	*/
	cPermElem GetMultInverse()const
	{
		std::vector<std::size_t> perm_array(m_Size);
		for(std::size_t index = 0; index < m_Size; index++) 
		{
			 perm_array[(*m_PermArray)[index] - 1] = index + 1;
		}
		return cPermElem(perm_array);
	};

	/*!
	  the same as GetMultInverse -- defined for consistency
	*/
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

	/*!
	  returns the identity permutation with the
	  same size as the current permutation
	*/
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


