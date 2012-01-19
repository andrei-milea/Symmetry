#ifndef _INTMODN_H
#define _INTMODN_H

#include <iostream>
#include <boost/assert.hpp>


//Integers modulo n class  -- Zn -- Z/modn
//represents one group element modulo n
template <std::size_t N>
class cIntModNElem
{
	typedef cIntModNElem<N> SelfType;

public:

	//constructors
	cIntModNElem()
		: m_Val(0)
	{};
	explicit cIntModNElem(std::size_t v)
		: m_Val(v%N)
	{};


	//copy constructor and assign operator
	cIntModNElem(const cIntModNElem& el)
	{
		m_Val = el.GetVal()%N;
	};
	SelfType& operator=(const SelfType& intmodn)
	{
		m_Val = intmodn.GetVal() % N;
		return *this;
	};

	~cIntModNElem() {};

	//overloaded operators
	SelfType operator+(const SelfType &a)const
	{
		return SelfType((m_Val + a.GetVal()) % N);
	};
	SelfType operator*(const SelfType &a)const
	{
		return SelftType((a.GetVal() * m_Val) % N);
	};
	friend std::ostream& operator<<(std::ostream &of, const SelfType &intmodn)
	{
		BOOST_ASSERT(N > intmodn.GetVal());
		of<<intmodn.GetVal();
		return of;
	};

	SelfType GetInverse()const
	{


	};

	//getter , setter
	std::size_t GetVal()const
	{
		BOOST_ASSERT(N > m_Val);
		return m_Val;
	};
	void SetVal(std::size_t val)
	{
		m_Val = val;
		BOOST_ASSERT(N > m_Val);
	};

public:
	template <typename OP>
	static SelfType GetIdentity(OP BinaryOp)
	{
		if(OP::isAdditive)
		{
			return SelfType(0);
		}
		else
		{
			return SelfType(1);
		}
	};

private:
	std::size_t m_Val;
};


#endif

