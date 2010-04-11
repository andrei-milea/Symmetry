
#ifndef _ELEMENT_H
#define _ELEMENT_H

#include "binary_op.h"
#include <cstring>
using namespace std;




template <typename T, typename BinaryOp>
class cElement
{
public:
    cElement(){};
	size_t GetOrder()
    {
		size_t size = 0;
		T temp = m_Value;
        while(temp != T::Identity)
        {
            temp = BinaryOp::BinOp(temp,m_Value);
			size++;
        }
		return size;
    };

	size_t GetOrder(size_t group_order)= 0;
private:
	T m_Value;
};

#endif
