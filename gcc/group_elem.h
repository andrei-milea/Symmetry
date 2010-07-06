#ifndef _GROUP_ELEM
#define _GROUP_ELEM

#include "sqmatrix.h"
#include "intmodn.h"
#include "permutation.h"

template <typename T, typename BinaryOp, std::size_t SIZE = T::GroupSize>
class cGroupElem : public T
{
	typedef typename cGroupElem<T, BinaryOp, SIZE> SelfType;
public:

	//constructors
	cGroupElem()
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

/////PROPERTIES//////
	bool CommutesWith(const SelfType &element)const
	{
		return( m_BinOp((*this), element) == m_BinOp(element, (*this)) );
	};

	bool IsCentralizer(const SelfType & element)const
	{
		return m_BinOp( m_BinOp((*this), element),  GetInverse()) == element;
	};
	bool IsNormalizer(const cGroup<T> &group)const
	{
		vector<T> &elements = group.GetElementsDimino();
		bool is = true;
		std::for_each(elements.begin(), elements.end(), [&elements, this, &is](std::vetor<T>::iterator it)
		{
			T element = m_BinOp( m_BinOp(*this, *it),  GetInverse());
			if(std::find(elemenets.begin(), elements.end(), element) == elements.end())
			{
				is = false;	
				return is;
			}

		});
		return is;
	};

private:
	BinaryOp m_BinOp;
	
public:
	const static std::size_t GroupOrder = SIZE;
};


#endif

