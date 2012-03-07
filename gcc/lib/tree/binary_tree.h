#ifndef _BINARY_TREE_H
#define _BINARY_TREE_H

#include "binary_rep.h"
//#include "threaded_rep.h"

namespace tree
{

/*!
  class that represents a binary tree (interface common to all 
  binary tree representations: binary_rep, threaded_rep)
*/
template<typename T, template <typename> class REP>
class cBinaryTree : public REP<T>
{
public:
	
};

};//namespace tree


#endif

