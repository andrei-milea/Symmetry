#ifndef THREADED_REP_H
#define THREADED_REP_H

namespace tree
{

/*!
  threaded binary tree representation
  !only inorder iterators and traversal
*/
template <typename T>
class cThreadedRep
{
public:
	typedef btree_threaded_node<T> node_type;
	typedef btree_iterator<T, node_type> iterator;
	typedef btree_inorder_iterator<T, node_type > inorder_iterator;

protected:	//can't construct cBinaryRep object directly -- only through cBinaryTree
	cThreadedRep()
		:m_Root(nullptr)
	{};

	~cThreadedRep()
	{};

	cThreadedRep(const cThreadedRep &bin_rep)
	{
		//TODO
	};
	
	cThreadedRep& operator=(const cThreadedRep &bin_rep)
	{
		//TODO
	};

public:
	/*!
	  checks for equality -- !compares the data in every node of the tree for equality
	*/
	bool operator==(const cThreadedRep& bin_rep)
	{
		inorder_iterator it = begin_inorder();
		inorder_iterator it_other = bin_rep.begin_inorder();
		while(it != end())
		{
			if(it != it_other)
				return false;
			it++;
			it_other++;
		}
		if(it_other == bin_rep.end())
			return true;
		else
			return false;
	};

	/*!
	  returns an iterator to the beginning of the tree for inorder traversal
	*/
	inorder_iterator begin_inorder()
	{
		node_type *node = m_Root;
		inorder_iterator inorder_it(node, m_Root);
		inorder_it++;
		return inorder_it;
	};

	/*!
	  returns an empty iterator signifying the end of the tree
	  ! used in constructs like for(iterator it = tree.begin(); it != tree.end(); it++)
	*/
	inorder_iterator end()
	{
		return inorder_iterator(m_Root, m_Root);
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
			inorder_iterator _iter(node, m_Root);
			_iter--;
			_iter.m_Current->right = node;
		}
		return inorder_iterator(node, m_Root);
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
			inorder_iterator _iter(node, m_Root);
			_iter++;
			_iter.m_Current->left = node;
		}
		return inorder_iterator(node, m_Root);
	};

	iterator insertRoot(const T& data)
	{
		assert(nullptr == m_Root);
		m_Root = new node_type(data);
		m_Root->right = m_Root;
		m_Root->left = new node_type(data);
		m_Root->left->left = m_Root;
		m_Root->left->right = m_Root;
		m_Root->left->rTag = true;
		m_Root->left->lTag = true;
		m_Root->rTag = false;
		m_Root->lTag = false;
		inorder_iterator iter(m_Root->left, m_Root);
		return iter;
	};

	/*!
	  traverse the binary tree in the given tree_traversal order 
	  takes a function object as a parameter, which must implement operator(T)
	*/
	template <typename FUNC>
	void traverse(FUNC& visit)
	{
		if(nullptr == m_Root)
			throw std::out_of_range("cThreadedRep.traverse -- invalid root node");
		node_type *current_node = m_Root;
		do
		{
			if(true == current_node->rTag)
			{
				current_node = current_node->right;
				if(m_Root != current_node)
					visit(current_node->data);
				else
					return;
				continue;
			}
			else
			{
				current_node = current_node->right;
			}
			while(false == current_node->lTag)
				current_node = current_node->left;
			visit(current_node->data);
		}
		while(m_Root != current_node);
	};

private:
	node_type *m_Root;
};

};//namespace tree

#endif

