#ifndef TREE_COMMON_H
#define TREE_COMMON_H

namespace tree
{

/*!
  tree traversal orders
  inorder -- left, root, right
  preorder -- root, left, right
  postorder -- left, right, root
*/
enum tree_traversal
{
	INORDER = 0,
	PREORDER,
	POSTORDER
};

/*!
  node type used by the binary tree internally
*/
template <typename T>
struct btree_node
{
	btree_node()
		:left(nullptr),
		right(nullptr)
	{};
	btree_node(T &_info)
		:info(_info),
		left(nullptr),
		right(nullptr)
	{};

	T info;
	btree_node *left;
	btree_node *right;
};

};

#endif

