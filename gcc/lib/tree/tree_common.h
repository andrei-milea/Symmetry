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
	btree_node(const T &_data)
		:data(_data),
		left(nullptr),
		right(nullptr)
	{};

	T data;
	btree_node *left;
	btree_node *right;
};

/*!
  node type used by the binary tree threaded representation
  rTag = false -> right points to child
  rTag = true -> right points to the inorder predecesor
  lTag = false -> left points to a child 
  lTag = true -> left points to the inorder successor
*/
template <typename T>
struct btree_threaded_node
{
	btree_threaded_node()
		:left(nullptr),
		right(nullptr),
		rTag(0),
		lTag(0)
	{};
	btree_threaded_node(const T &_data)
		:data(_data),
		left(nullptr),
		right(nullptr),
		rTag(0),
		lTag(0)
	{};

	T data;
	btree_threaded_node *left;
	btree_threaded_node *right;
	bool rTag;
	bool lTag;
};

};

#endif

