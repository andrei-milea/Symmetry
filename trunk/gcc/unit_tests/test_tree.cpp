#include "../lib/tree/binary_tree.h"

#define BOOST_TEST_MODULE "test_tree"
#include "boost/test/included/unit_test.hpp"
#include <string>

using namespace boost::unit_test;
using namespace std;


BOOST_AUTO_TEST_CASE(test_binary_tree)
{
	tree::cBinaryTree<string, tree::cBinaryRep> binary_tree;
	tree::cBinaryTree<string, tree::cBinaryRep>::iterator inorder_iter= binary_tree.begin_inorder();
	binary_tree.insertLeft

	BOOST_ASSERT(1);
};



