#include <iostream>
#include <boost/assert.hpp>


//Integers modulo n class  -- Zn -- Z/modn
//represents one group element modulo n 
template <std::size_t N>
class cIntModNElem 
{
	typedef cIntModNElem<N> SelfType;

public:
	cIntModNElem()
		: m_Val(0)
	{};

	explicit cIntModNElem(std::size_t v) 
		: m_Val(v%N)
   	{};

	~cIntModNElem(){};

	cIntModNElem(const cIntModNElem& el)
	{
		m_Val = el.GetVal()%N;
	};

	SelfType& operator=(const SelfType& intmodn)
	{
		m_Val = intmodn.GetVal() % N;
		return *this;
	};
	


	SelfType GetInverse()const
	{


	};

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

	std::size_t GetVal()const
	{
		BOOST_ASSERT(N > m_Val);
		return m_Val;
	};

public:
	template <typename OP>
	static SelfType GetIdentity(OP BinaryOp)
	{
		if(BinaryOp::isAdditive)
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
