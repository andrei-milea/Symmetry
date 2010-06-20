#ifndef PERMUTATION_H_
#define PERMUTATION_H_ 

#include <array>

template <std::size_t N>
class cPermutationElem
{
public:
	typedef cIntModNElem<N> SelfType;

public:
	//constructors
	cPermutationElem()
	{};
	cPermutationElem(std::array<std::size_t, N> &permutation_array)
		m_PermutationArray(permutation_array)
	{};

	//copy constructor and assign operator
	cPermutationElem(const SelfType &permutation)
	{
		m_PermutationArray = permutation.GetPermutationArray();
	};
	SelfType operator=(const SelfType &permutation)
	{
		return m_PermutationArray = permutation.GetPermutationArray();
	};

	~cPermutationElem()
	{};


	//getter,setter
	std::array<std::size_t, N> GetPermutationArray()const
	{
		return m_PermutationArray;
	};
	void SetPermutationArray(std::array<std::size_t> permutation_array)
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


private:
	std::array<std::size_t, N> m_PermutationArray;
};

#endif

