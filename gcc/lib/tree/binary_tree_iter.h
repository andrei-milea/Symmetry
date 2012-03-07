#ifndef BINARY_TREE_ITER_H
#define BINARY_TREE_ITER_H

#include <stack>
#include <cassert>
#include <stdexcept>
#include <boost/iterator/iterator_facade.hpp>

#include "tree_common.h"

namespace tree
{

/*!
  binary tree iterator class 
  uses boost::iterator_facade to implement the iterator
  the tree_traversal order must be specified in the constructor
*/
template <typename T, typename N>
class btree_iterator : public boost::iterator_facade<btree_iterator<T, N>, T, boost::forward_traversal_tag>
{
public:
	btree_iterator(tree_traversal traversal = INORDER)
		:m_Current(nullptr),
		m_NextNode(nullptr),
		m_Traversal(traversal)
	{};
	explicit btree_iterator(N* node, tree_traversal traversal = INORDER)
		:m_Current(node),
		m_NextNode(node),
		m_Traversal(traversal)
	{};

private:
    friend class boost::iterator_core_access;

	void increment()
	{
		if(nullptr == m_Current)
			throw std::out_of_range("btree_iterator.increment -- invalid current node");
		if(INORDER == m_Traversal)
		{
			while(nullptr != m_NextNode)
			{
				m_Stack.push_back(m_NextNode);
				m_NextNode = m_NextNode->left;
			}
			if(!m_Stack.empty())
			{
				m_NextNode = m_Stack.pop_back();
				m_Current = m_NextNode;
				m_NextNode = m_NextNode->right;
			}
			else
				m_Current = nullptr;
		}
		else if(PREORDER == m_Traversal)
		{
			if(m_NextNode == m_Current)
				m_Stack.push_back(m_NextNode);
			if(!m_Stack.empty())
			{
				m_NextNode = m_Stack.pop_back();
				if(nullptr != m_NextNode->right)
					m_Stack.push_back(m_NextNode->right);
				if(nullptr != m_NextNode->left)
					m_Stack.push_back(m_NextNode->left);
				m_Current = m_NextNode;
			}
			else
			{
				m_Current = nullptr;
			}
		}
		else
		{
			assert(POSTORDER == m_Traversal);
		}
	};

	bool equal(const btree_iterator<T, N>& other)const
	{
		return this->m_Current == other.m_Current;
	};

    T& dereference()const
	{
		return m_Current->info;
	};

private:
	N *m_Current;
	N *m_NextNode;
	tree_traversal m_Traversal;
	std::stack<N*> m_Stack;

};

};//namespace tree

#endif

