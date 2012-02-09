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
		:m_PermArray(nullptr)
	{};

	/*!
	  constructor for identity permutation
	*/
	cPermElem(std::size_t size)
		:m_PermArray(nullptr)
	{
		m_PermArray = new std::vector<std::size_t>(size);
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
		m_PermArray = new std::vector<std::size_t>(size);
		for(std::size_t index = 0; index < size; index++)
		{
			(*m_PermArray)[index] = index + 1;
		}
		for(auto iter = perm_sq.begin(); iter != perm_sq.end()-1; iter++)
		{
			if(*iter <= size && *iter != 0)
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
		m_PermArray = new std::vector<std::size_t>(perm_sq.size());

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
		m_PermArray = new std::vector<std::size_t>(perm_sq.size());

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
		if(this != &permutation && 0 != permutation.GetSize())
		{
			m_PermArray = new std::vector<std::size_t>(permutation.GetSize());
			(*m_PermArray) = (*permutation.GetPermutationArray());
		}
		else
		{
			m_PermArray = nullptr;
		}
	};
	cPermElem& operator=(const cPermElem &permutation)
	{
		if(this != &permutation && 0 != permutation.GetSize())
		{
			if(nullptr != m_PermArray)
				delete m_PermArray;
			m_PermArray = new std::vector<std::size_t>(permutation.GetSize());
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
		if(nullptr != m_PermArray)
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
		assert(perm.GetSize() == m_PermArray->size());
		std::vector<std::size_t> temp_perm(m_PermArray->size());
		for(std::size_t index = 0; index < m_PermArray->size(); index++)
		{
			temp_perm[index] = (*perm.GetPermutationArray())[(*m_PermArray)[index] - 1];
		}
		return cPermElem(temp_perm);
	};

	bool operator==(const cPermElem &perm)const
	{
		if(nullptr == m_PermArray || perm.GetSize() != m_PermArray->size())
			return false;
		for(std::size_t index = 0; index < m_PermArray->size(); index++)
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
		for(std::size_t index = 0; index < perm.GetSize(); index++)
		{
			perm_index += boost::lexical_cast<std::string>(index+1) + " ";
			perm_val += boost::lexical_cast<std::string>((*perm.GetPermutationArray())[index]) + " ";
		}
		return of<<perm_index<<"\n"<<perm_val<<"\n";
	};

	/*!
	  rotate the elements of the array to the left
	  represents a rotation of the regular polygon with n(size) sides
	  !!!used to compute the cyclic and dihedral group
	*/
	void rotateLeft()
	{
		std::size_t first_value = m_PermArray->at(0);
		std::size_t index = 0;
		for(index = 0; index < m_PermArray->size()-1; index++)
		{
			m_PermArray->at(index) = m_PermArray->at(index+1);
		}
		m_PermArray->at(index) = first_value;
	}

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
		std::vector<std::size_t> perm_array(m_PermArray->size());
		for(std::size_t index = 0; index < m_PermArray->size(); index++)
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
		if(nullptr != m_PermArray)
			return m_PermArray->size();
		else
			return 0;
	};

	/*!
	  returns the identity permutation with the
	  same size as the current permutation
	*/
	template <typename BINOP>
	cPermElem GetIdentity(BINOP binop)const
	{
		return cPermElem(m_PermArray->size());
	};

	/*!
	  returns the number of inverses: "inverse" if i < j and A[i] > A[j]
	  modified merge sort => Complexity: O(nlgn)
	  see Cormen chapter 2 - exercises
	*/
	std::size_t GetInversions()const
	{
		std::size_t inversions = 0;
		std::vector<std::size_t> temp = *m_PermArray;
		CountInversions(temp.begin(), temp.end(), inversions);
		return inversions;
	};

private:
	/*!
	  helper function for GetInversions -- modified merge sort
	  Complexity: O(nlgn)
	*/
	void CountInversions(std::vector<std::size_t>::iterator begin, std::vector<std::size_t>::iterator end,
	                     std::size_t &inversions)const
	{
		std::size_t size = end - begin;
		if(size < 2)
			return;
		std::vector<std::size_t>::iterator begin_right = begin + size/2;
		CountInversions(begin, begin_right, inversions);
		CountInversions(begin_right, end, inversions);
		MergeInversions(begin, begin_right, end, inversions);
	};

	/*!
	  equivalent to merge procedure from merge sort
	  Complexity: O(n)
	*/
	void MergeInversions(std::vector<std::size_t>::iterator begin, std::vector<std::size_t>::iterator begin_right,
	                     std::vector<std::size_t>::iterator end, std::size_t &inversions)const
	{
		std::size_t size_left = begin_right - begin;
		std::vector<std::size_t> leftArray(begin, begin_right);
		leftArray.push_back(INT_MAX);	//sentinel
		std::vector<std::size_t> rightArray(begin_right, end);
		rightArray.push_back(INT_MAX);	//sentinel

		int i = 0, j = 0;
		bool counted = false;
		while(begin != end)
		{
			if( (false == counted) && (rightArray[j] < leftArray[i]) )
			{
				inversions += size_left - i;
				counted = true;
			}
			if(leftArray[i] <= rightArray[j])
			{
				*begin = leftArray[i];
				i++;
			}
			else
			{
				*begin = rightArray[j];
				j++;
				counted = false;
			}
			begin++;
		}
	};


private:
	std::vector<std::size_t> *m_PermArray;
};


#endif


