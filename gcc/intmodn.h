
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
		: m_val(v)
   	{};

	~cIntModNElem(){};

	SelfType& operator+(const SelfType &a)
	{
		this->m_val = (this->m_val + a.m_val) % N;
		return *this;
	};

	
	SelfType& operator*(const SelfType &a)
	{
		this->m_val = (a.m_val * this->m_val) % N;
		return *this;
	};

	SelfType& operator=(const SelfType& intmodn)
	{
		this->m_val = intmodn.GetVal();
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
