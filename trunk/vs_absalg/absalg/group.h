#ifndef _GROUP_H
#define _GROUP_H

#define INFINITE_ORDER  0

#include <boost/intrusive/set.hpp>
#include "subgroup.h"



template <typename type, template <typename element,typename el> class CONT = boost::intrusive::set>
class cGroup
{
public:
	cGroup()
	    :m_Order(m_Set.size())
	{};

    cGroup(size_t size)
        :m_Order(size)
    {};
    virtual ~cGroup()   {};

    cSubGroup<type>& GetKernel();
    cSubGroup<type>& GetImage();
	
private:
	CONT<type> m_Set;
	unsigned int m_Order;
};
				


#endif
