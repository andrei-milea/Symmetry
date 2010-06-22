#ifndef PERMUTATION_H_
#define PERMUTATION_H_ 

#include <array>
#include <initializer_list>
#include<boost/lexical_cast.hpp>

namespace tr1 = std::tr1;

template <std::size_t N>
class cPermElem
{
public:
	typedef cPermElem<N> SelfType;

public:
	//constructors
	cPermElem()
	{
		for(std::size_t index = 0; index < N; index++)
		{
			m_PermutationArray[index] = index;
		}
	};
	cPermElem(std::array<std::size_t, N> &permutation_array)
		:m_PermutationArray(permutation_array)
	{};
	cPermElem(std::initializer_list<std::size_t> perm_sq)
	{
		cPermElem();
		for(std::initializer_list<std::size_t>::iterator iter = perm_sq.begin();
			   	iter != perm_sq.end(); iter++)
		{
			if(*iter -1 < N)
			{
				m_PermutationArray[(*iter) -1] = *(iter+1);
			}
			else
			{
				//error
			}
			m_PermutationArray[*iter - 1] = *perm_sq.begin();
		}
	};

	//copy constructor and assign operator
	cPermElem(const SelfType &permutation)
	{
		m_PermutationArray = permutation.GetPermutationArray();
	};
	SelfType operator=(const SelfType &permutation)
	{
		return m_PermutationArray = permutation.GetPermutationArray();
	};

	~cPermElem()
	{};


	//getter,setter
	std::array<std::size_t, N> GetPermutationArray()const
	{
		return m_PermutationArray;
	};
	void SetPermutationArray(std::array<std::size_t, N> permutation_array)
	{
		m_PermutationArray = permutation_array;
	};

	//permutation mutiplication operator
	SelfType operator*(SelfType &perm)const
	{
		std::array<std::size_t, N> temp_perm;
		for(std::size_t index = 0; index < N; index++)
		{
			temp_perm[index] = perm.GetPermutationArray()[m_PermutationArray[index]];
		}
		return temp_perm;
	};

	friend std::ostream& operator<<(std::ostream &of, const SelfType &perm)
	{
		std::string perm_index;
		std::string perm_val;
		for(std::size_t index = 0; index < N; index++)
		{
			perm_index += boost::lexical_cast<std::string>(index + 1) + " ";
			perm_val += boost::lexical_cast<std::string>(perm.GetPermutationArray()[index]) + " ";
		}
		return std::cout<<perm_index<<"\n"<<perm_val<<"\n";
	};


private:
	std::array<std::size_t, N> m_PermutationArray;
};

#endif

