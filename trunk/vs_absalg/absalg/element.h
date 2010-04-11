
#ifndef _ELEMENT_H
#define _ELEMENT_H


template <typename type> class cElement
{
   public:
    cElement(){};
    virtual size_t GetOrder()= 0;
};

#endif
