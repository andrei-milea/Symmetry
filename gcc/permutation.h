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
		for(std::size_t index = 1; index <= N; index++)
		{
			m_PermutationArray[index] = index;
		}
	};
	cPermElem(std::array<std::size_t, N+1> &permutation_array)
		:m_PermutationArray(permutation_array)
	{};
	cPermElem(std::initializer_list<std::size_t> perm_sq)
	{
		cPermElem();
		for(std::initializer_list<std::size_t>::iterator iter = perm_sq.begin();
			   	iter < perm_sq.end()-1; iter++)
		{
			if(*iter < N && *iter != 0)
			{
				m_PermutationArray[(*iter)] = *(iter+1);
			}
			else
			{
				//error
				BOOST_ASSERT(0);
			}
		}
		m_PermutationArray[*(perm_sq.end()-1)] = *perm_sq.begin();
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
	std::array<std::size_t, N+1> GetPermutationArray()const
	{
		return m_PermutationArray;
	};
	void SetPermutationArray(std::array<std::size_t, N+1> permutation_array)
	{
		m_PermutationArray = permutation_array;
	};

	//permutation mutiplication operator
	SelfType operator*(SelfType &perm)const
	{
		std::array<std::size_t, N+1> temp_perm;
		for(std::size_t index = 1; index <= N; index++)
		{
			temp_perm[index] = perm.GetPermutationArray()[m_PermutationArray[index]];
		}
		return temp_perm;
	};

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

public:
	static SelfType GetIdentity()
	{
		return SelfType();
	};
	static const std::size_t GroupSize = 0;


private:
	std::array<std::size_t, N+1> m_PermutationArray;
};

#endif

