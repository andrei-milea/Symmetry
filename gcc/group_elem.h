#ifndef _GROUP_ELEM
#define _GROUP_ELEM

#include "sqmatrix.h"
#include "intmodn.h"
#include "permutation.h"


template <typename T, typename BinaryOp, std::size_t SIZE = T::GroupSize>
class cGroupElem : public T
{
public:
	typedef cGroupElem<T, BinaryOp, SIZE> SelfType;
	typedef T ConcreteElType;
public:

	//constructors
	cGroupElem()
	{
	};
	cGroupElem(T &concrete_obj)
		:T(concrete_obj)
	{
	};

	cGroupElem(const T &concrete_obj)
		:T(concrete_obj)
	{
	};
	//copy constructor and assign operator
	cGroupElem(const SelfType &group_elem)
	{
		T::operator=(group_elem);
	};
	SelfType &operator=(const SelfType &elem)
	{
		if(this != &elem)
		{
			T::operator=(elem);
		}
		return *this;
	};
	
	~cGroupElem()
	{
	};

	std::size_t GetOrder()const
    {
		std::size_t size = 1;
		SelfType temp = (*this);
        while(temp != ConcreteElType::GetIdentity(m_BinOp))
        {
            temp = m_BinOp(temp,(*this));
			size++;
        }
		return size;
    };

	std::size_t GetOrder(std::size_t group_order)//const
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
		return 0;
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
		SelfType temp = SelfType(T::GetIdentity(m_BinOp));
		while(n > 2)
		{
			if(n%2 == 1)
			{
				temp =  m_BinOp(temp, *this);
				n--;
			}
			else
			{
				temp = m_BinOp (temp, temp);
				n = n / 2;
			}			
		}
		return temp;
	};

/////PROPERTIES//////
	bool CommutesWith(const SelfType &element)const
	{
		return( m_BinOp((*this), element) == m_BinOp(element, (*this)) );
	};

	bool IsCentralizer(const SelfType & element)const
	{
		return m_BinOp( m_BinOp((*this), element),  GetInverse()) == element;
	};
	bool IsNormalizer(const std::vector<T> &elements)const
	{
		bool is = true;
		std::for_each(elements.begin(), elements.end(),
			   [&, m_BinOp](typename std::vector<T>::iterator it)
		{
			T element = m_BinOp( m_BinOp((*this), (*it)),  GetInverse());
			if(std::find(elements.begin(), elements.end(), element) == elements.end())
			{
				is = false;	
				return is;
			}

		});
		return is;
	};

	BinaryOp GetBinaryOp()const
	{
		return m_BinOp;
	};

private:
	BinaryOp m_BinOp;
	
public:
	const static std::size_t GroupOrder = SIZE;
};


#endif

