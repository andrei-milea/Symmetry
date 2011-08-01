#ifndef _GROUP_ELEM
#define _GROUP_ELEM

#include "sqmatrix.h"
#include "intmodn.h"
#include "permutation.h"

/*****************************************
 * class for group element representation
*****************************************/

template <typename T, typename BinaryOp>
class cGroupElem : public T
{
public:
	typedef cGroupElem<T, BinaryOp> SelfType;
	typedef T ConcreteElType;

public:
	cGroupElem()
		:T()
	{};
	cGroupElem(T &concrete_obj)
		:T(concrete_obj)
	{
	};

	cGroupElem(const T &concrete_obj)
		:T(concrete_obj)
	{
	};

	//////////////TODO remove this when constructor inheritance
	//becomes available in c++ 0x
	//used to build cPermElem base class
	///////////////////////////////////////////////////////////
	cGroupElem(const std::initializer_list<std::size_t> &perm_sq)
		:ConcreteElType(perm_sq)
	{};
	cGroupElem(std::size_t size, const std::initializer_list<std::size_t> &perm_sq)
		:ConcreteElType(size, perm_sq)
	{};
	////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////

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
        while(temp != GetIdentity())
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
				if(GetNthPower(d)==GetIdentity())
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
		return GetNthPower(n,*this);
	};

/////PROPERTIES//////
	bool CommutesWith(const SelfType &element)const
	{
		return( m_BinOp((*this), element) == m_BinOp(element, (*this)) );
	};

	bool IsNormalizer(const std::vector<SelfType> &elements)const
	{
		for(std::size_t index = 0; index < elements.size(); index++)
		{
			SelfType element = m_BinOp( m_BinOp((*this), elements[index]), GetInverse());
			if(std::find(elements.begin(), elements.end(), element) == elements.end())
			{
				return false;
			}

		}
		return true;
	};

	SelfType GetIdentity()const
	{
		BinaryOp _BinOp;
		return SelfType(ConcreteElType::GetIdentity(_BinOp));
	};

	BinaryOp GetBinaryOp()const
	{
		return m_BinOp;
	};

private:
	SelfType GetNthPower(std::size_t n, const SelfType &element)const
	{
		if(0 == n)
			return GetIdentity();
		if(1 == n)
			return *this;
		if(0 == n % 2 )
			return m_BinOp(GetNthPower(n/2, element),GetNthPower(n/2, element));
		else
			return m_BinOp(m_BinOp(GetNthPower(n/2, element), GetNthPower(n/2, element)),
				   element);
	};

private:
	BinaryOp m_BinOp;
};

typedef cGroupElem< cPermElem, Multiplication> SymmGrpElem;

#endif

