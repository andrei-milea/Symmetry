#ifndef GROUP_ELEM_
#define GROUP_ELEM_

#include "sqmatrix.h"

template <typename T, typename BinaryOp, std::size_t SIZE>
class cGroupElem : public T
{
	typedef cGroupElem<T, BinaryOp, SIZE> SelfType;
public:
	cGroupElem()
	{
	};

	~cGroupElem()
	{
	};

	SelfType &operator=(const SelfType &elem)
	{
		if(this != &elem)
		{
			T::operator=(elem);
		}
		return *this;
	};
	
	std::size_t GetOrder()const
    {
		std::size_t size = 0;
		SelfType temp = (*this);
        while(temp != T::GetIdentity(m_BinOp))
        {
            temp = m_BinOp(temp,(*this));
			size++;
        }
		return size;
    };

	std::size_t GetOrder(std::size_t group_order)const
	{
		for(unsigned int d=1; d<=group_order; d++)
		{
			if(group_order%d==0) 
			{
				if(GetNthPower(d)==T::GetIdentity(m_BinOp))
				{
					return d;
				}
			}
		}
	};

	SelfType GetInverse()const
	{
		if(BinaryOp::isAdditive)
		{
			return T::GetAdInverse();
		}
		else
		{
			return T::GetMultInverse();
		}
	};

	SelfType GetNthPower(std::size_t n)const
	{
		SelfType temp = T::GetIdentity(m_BinOp);
		if(n%2 == 1)
		{
			(*this) = m_BinOp(*this, temp);
		}
		while(n > 1)
		{
			(*this) = m_BinOp (*this, *this);
			n = n / 2;
			if(n%2 == 1)
			{
				temp =  m_BinOp(temp, *this);
			}
		}
		return temp;
	};

private:
	BinaryOp m_BinOp;
	
public:
	const static std::size_t GroupOrder = SIZE;
};


#endif

