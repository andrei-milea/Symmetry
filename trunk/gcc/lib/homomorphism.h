#ifndef _HOMOMORPHISM_H
#define _HOMOMORPHISM_H

#include <vector>
#include <boost/tuple/tuple.hpp>

template <typename G1, typename G2>
class cHomomorphism
{
	typedef (G2::ElementType)(*f)(G1::ElementType) FunctionType;
public:
	cHomomorphism(G1 &group, G2 &group,FunctionType map)
		:m_Map(map)
	{};

	~cHomomorphism()
	{};

	void Compute();
	void Display();

	cSubgroup<G1> GetKernel()const;
	cSubgroup<G2> GetImage()const;
	BOOL isIsomorphism()const;

private:
	std::vector< tuple<G1::ElementType, G2::ElementType> >;
	FunctionType m_Map;
};

#endif

