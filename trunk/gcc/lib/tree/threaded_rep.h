#ifndef THREADED_REP_H
#define THREADED_REP_H

namespace tree
{

template <typename T>
class cThreadedRep
{
public:
	typedef btree_threaded_node<T> node_type;
	typedef btree_iterator<T, node_type> iterator;
	typedef btree_preorder_iterator<T, node_type > preorder_iterator;
	typedef btree_inorder_iterator<T, node_type > inorder_iterator;
	typedef btree_postorder_iterator<T, node_type > postorder_iterator;

protected:	//can't construct cBinaryRep object directly -- only through cBinaryTree
	cThreadedRep()
		:m_Root(nullptr)
	{};

	~cThreadedRep()
	{};

	cThreadedRep(const cThreadedRep &bin_rep)
	{};
	
	cThreadedRep& operator=(const cThreadedRep &bin_rep)
	{};

public:
	/*!
	  checks for equality -- !compares the data in every node of the tree for equality
	*/
	bool operator==(const cThreadedRep& bin_rep)
	{
		return true;
	};

	/*!
	  returns an iterator to the beginning of the tree for inorder traversal
	*/
	inorder_iterator begin_inorder()
	{
		inorder_iterator inorder_it(m_Root);
		inorder_it++;
		return inorder_it;
	};

	/*!
	  returns an iterator to the beginning of the tree for preorder traversal
	*/
	preorder_iterator begin_preorder()
	{
		preorder_iterator preorder_it(m_Root);
		preorder_it++;
		return preorder_it;
	};

	/*!
	  returns an iterator to the beginning of the tree for postorder traversal
	*/
	postorder_iterator begin_postorder()
	{
		postorder_iterator postorder_it(m_Root);
		postorder_it++;
		return postorder_it;
	};

	/*!
	  returns an empty iterator signifying the end of the tree
	  ! used in constructs like for(iterator it = tree.begin(); it != tree.end(); it++)
	*/
	preorder_iterator end()
	{
		return preorder_iterator();
	};

	/*!
	  inserts data as a left child of the node indicated by the iterator
	*/
	iterator insertLeftChild(iterator iter, const T& data)
	{
		node_type *node = new node_type(data);
		node->left = iter.m_Current->left;
		node->lTag = iter.m_Current->lTag;
		node->right = iter.m_Current;
		node->rTag = true;
		iter.m_Current->left = node;
		iter.m_Current->lTag = false;
		if(false == node->lTag)
		{
			inorder_iterator _iter(node);
			_iter--;
			_iter.m_Current->right = node;
		}
		return inorder_iterator(iter.m_Current->left);
	};

	/*!
	  inserts data as a right child of the node indicated by the iterator
	*/
	iterator insertRightChild(iterator iter, const T& data)
	{
		node_type *node = new node_type(data);
		node->right = iter.m_Current->right;
		node->rTag = iter.m_Current->rTag;
		node->left = iter.m_Current;
		node->lTag = true;
		iter.m_Current->right = node;
		iter.m_Current->rTag = false;
		if(false == node->rTag)
		{
			inorder_iterator _iter(node);
			_iter++;
			_iter.m_Current->left = node;
		}
		return inorder_iterator(iter.m_Current->left);
	};

	iterator insertRoot(const T& data)
	{
		assert(nullptr == m_Root);
		m_Root = new node_type(data);
		m_Root->right = m_Root;
		m_Root->left = new node_type(data);
		m_Root->left->left = m_Root;
		m_Root->rTag = false;
		m_Root->lTag = false;
		inorder_iterator iter(m_Root->left);
		return iter;
	};

	/*!
	  traverse the binary tree in the given tree_traversal order 
	  takes a function object as a parameter, which must implement operator(T)
	*/
	template <typename FUNC>
	void traverse(tree_traversal traversal, FUNC& visit)
	{
		if(nullptr == m_Root)
			throw std::out_of_range("cBinaryRep.traverse -- invalid root node");
		//node_type *current_node = m_Root;
		std::stack<node_type*> stack;
		if(INORDER == traversal)
		{
		}
		else if(PREORDER == traversal)
		{
		}
		else
		{
			assert(POSTORDER == traversal);
		}
	};

private:
	node_type *m_Root;
};

};//namespace tree

#endif

