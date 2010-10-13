#ifndef _STD_EX_H
#define _STD_EX_H

#include <iostream>

namespace std_ex
{

	/*****************************************
	* set operations 
	*****************************************/
	
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

template <typename SET_REP>
bool set_equality(SET_REP &set1, SET_REP &set2)
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

	/*****************************************
	* overloaded operator for printing a 
	* STL sequece (vector, array, list, etc)
	*****************************************/
template <typename T>
std::ostream& operator<<(std::ostream& out, const std::vector<T>& vec)
{
	out<<"Vector - Begin:\n";
	typename std::vector<T>::const_iterator it;
	for(it = vec.begin(); it != vec.end(); it++)
	{
		out<<*it;
		out<<"\n";
	}
	out<<"End\n";
	return out;
};

};


#endif

