#ifndef _STD_EX_H
#define _STD_EX_H

#include <algorithm>
#include <iostream>

namespace std_ex
{

	/*****************************************
	* set operations 
	*****************************************/
	
//tests if set2 constains set1
template <typename SET_REP>
bool set_inclusion(SET_REP &set1, SET_REP &set2)	//set2 contains set1 ?
{
	for(typename SET_REP::const_iterator it = set1.begin(); it != set1.end(); it++)
	{
		if(find(set2.begin(), set2.end(), *it) != set2.end())
			continue;
		return false;
	}
	return true;
};

//test 2 sets for equality
template <typename SET_REP>
bool set_equality(const SET_REP &set1, const SET_REP &set2)
{
	if(set1.size() != set2.size())
		return false;
	for(typename SET_REP::const_iterator it = set1.begin(); it != set1.end(); it++)
	{
		if(find(set2.begin(), set2.end(), *it) != set2.end())
			continue;
		return false;
	}
	return true;
};

//set difference 
//returns the first set without the elements of the second set
template <typename SET_REP>
SET_REP& set_difference(SET_REP &set1, const SET_REP &set2)
{
	for(typename SET_REP::const_iterator it = set2.begin(); it != set2.end(); it++)
	{
		typename SET_REP::iterator found_iter = find(set1.begin(), set1.end(), *it);
		if(found_iter != set1.end())
			set1.erase(found_iter);
	}
	return set1;
};

//set intersection 
//returns a new constructed set with common elements
template <typename SET_REP>
SET_REP set_intersection(SET_REP &set1, const SET_REP &set2)
{
	SET_REP new_set;
	for(typename SET_REP::const_iterator it = set2.begin(); it != set2.end(); it++)
	{
		typename SET_REP::iterator found_iter = find(set1.begin(), set1.end(), *it);
		if(found_iter != set1.end())
			new_set.push_back(*found_iter);
	}
	return new_set;
};


template <typename T, template <typename ELEM, typename ALLOC = std::allocator<ELEM> >
   	class CONT>
void set_remove(CONT<T> &set1, const T &element)
{
	while(true)
	{
		typename CONT<T>::iterator found_iter = find(set1.begin(), set1.end(), element);
		if(found_iter != set1.end())
			set1.erase(found_iter);
		else
			return;
	}
};


	/***************************************** * print vector elements *****************************************/
template <typename T>
void print_vector(const std::vector<T>& vec)
{
	std::cout<<"Vector - Begin:\n";
	typename std::vector<T>::const_iterator it;
	for(it = vec.begin(); it != vec.end(); it++)
	{
		std::cout<<*it<<"\n\n";
	}
	std::cout<<"End\n";
};

};

#endif


