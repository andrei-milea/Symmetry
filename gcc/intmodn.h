#include <iostream>

//Integers modulo n class  -- Zn -- Z/modn
//represents one group element modulo n 
template <std::size_t N>
class cIntModNElem 
{
	typedef cIntModNElem<N> SelfType;

public:
	cIntModNElem()
		: m_val(0)
	{};

	explicit cIntModNElem(std::size_t v) 
		: m_val(v%N)
   	{};

	~cIntModNElem(){};

	SelfType operator+(const SelfType &a)const
	{
		return SelfType((m_val + a.GetVal()) % N);
	};

	
	SelfType operator*(const SelfType &a)const
	{
		 return SelftType((a.GetVal() * m_val) % N);
	};

	SelfType& operator=(const SelfType& intmodn)
	{
		m_val = intmodn.GetVal();
		return *this;
	};
	
	friend std::ostream& operator<<(std::ostream &of, const SelfType &intmodn)
	{
		of<<intmodn.GetVal();
		return of;
	};

	std::size_t GetVal()const
	{
		return m_val;
	};

private:
	std::size_t m_val;
};
