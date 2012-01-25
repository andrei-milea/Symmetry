#ifndef _SERIALIZER_H
#define _SERIALIZER_H

#include "group_factory.h"

#include <sstream>

/*!
 uses boost spirit karma to generate output for the http_server
*/
template <typename T, template <typename, class> class CONT = std::vector>
class cSerializer;

template<template <typename, class> class CONT>
class cSerializer<SymmGrpElem, CONT>
{
public:
	cSerializer()
	{};
	~cSerializer()
	{};

	const std::string Stringify(const SymmGrpElem &element)const
	{
		std::stringstream ss;
		ss<<element;
		return ss.str();
	};

	const std::string Stringify(const CONT<SymmGrpElem, std::allocator<SymmGrpElem> >& elements)const
	{
		std::string result;
		for(unsigned int index = 0; index < elements.size(); index++)
		{
			result += Stringify(elements[index]);
		}
		return result;
	};

};


#endif

