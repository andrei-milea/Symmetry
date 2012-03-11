#include "../lib/tree/binary_tree.h"

#define BOOST_TEST_MODULE "test_tree"
#include "boost/test/included/unit_test.hpp"
#include <string>

using namespace boost::unit_test;
using namespace std;
using namespace tree;

template <class TREE>
void test_binary_tree(TREE& binary_tree)
{
	vector<string> letters = {"A", "B", "C", "D", "E", "F", "G", "H", "J"};
	auto iter = binary_tree.insertRoot(letters[0]);
	auto left_iter = binary_tree.insertLeftChild(iter, letters[1]);
	binary_tree.insertLeftChild(left_iter, letters[3]);
	auto right_iter = binary_tree.insertRightChild(iter, letters[2]);
	binary_tree.insertRightChild(binary_tree.insertLeftChild(right_iter, letters[4]), letters[6]);
	right_iter = binary_tree.insertRightChild(right_iter, letters[5]);
	binary_tree.insertLeftChild(right_iter, letters[7]);
	binary_tree.insertRightChild(right_iter, letters[8]);

	class cAddStr 
	{
	public:
		cAddStr(string &str)
			:m_String(str)
		{};
		void operator()(string& str) 
		{
			m_String += str;
		};
	private:
		string &m_String;
	};

	////////////inorder tests
	string inorder_letters;
	for(auto it = binary_tree.begin_inorder(); it != binary_tree.end(); it++)
	{
		inorder_letters += *it;
	}
	BOOST_ASSERT("DBAEGCHFJ" == inorder_letters);

	inorder_letters = "";
	cAddStr add_str_in(inorder_letters);
	binary_tree.traverse(INORDER, add_str_in);
	BOOST_ASSERT("DBAEGCHFJ" == inorder_letters);


	////////////preorder tests
	string preorder_letters;
	for(auto it = binary_tree.begin_preorder(); it != binary_tree.end(); it++)
	{
		preorder_letters += *it;
	}
	BOOST_ASSERT("ABDCEGFHJ" == preorder_letters);

	preorder_letters = "";
	cAddStr add_str_pr(preorder_letters);
	binary_tree.traverse(PREORDER, add_str_pr);
	BOOST_ASSERT("ABDCEGFHJ" == preorder_letters);

	/////////////postorder tests
	string postorder_letters;
	for(auto it = binary_tree.begin_postorder(); it != binary_tree.end(); it++)
	{
		postorder_letters += *it;
	}
	BOOST_ASSERT("DBGEHJFCA" == postorder_letters);

	postorder_letters = "";
	cAddStr add_str_po(postorder_letters);
	binary_tree.traverse(POSTORDER, add_str_po);
	BOOST_ASSERT("DBGEHJFCA" == postorder_letters);


}

BOOST_AUTO_TEST_CASE(test_binary_tree_iterators_traversal)
{
	cBinaryTree<string, cBinaryRep> binary_tree;
	cBinaryTree<string, cThreadedRep> th_binary_tree;
	test_binary_tree(binary_tree);
	test_binary_tree(th_binary_tree);
};



