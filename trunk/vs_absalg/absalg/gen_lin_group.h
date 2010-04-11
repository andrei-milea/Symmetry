#ifndef _GEN_LIN_GROUP
#define _GEN_LIN_GROUP

#include "group.h"

template <typename type>
class cGLGroup : public cGroup<type>
{
public:
    cGLGroup(unsigned int size);
    virtual ~cGLGroup();

};


#endif