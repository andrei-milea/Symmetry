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
  binary tree iterator base class 
  uses boost::iterator_facade to implement the iterator
*/
template <typename T, typename N>
class btree_iterator : public boost::iterator_facade<btree_iterator<T, N>, T, boost::forward_traversal_tag>
{
protected:
	btree_iterator()
		:m_Current(nullptr)
	{};
	explicit btree_iterator(N* node)
		:m_Current(node)
	{};

    friend class boost::iterator_core_access;
	template <typename> friend class cBinaryRep;

	bool equal(const btree_iterator<T, N>& other)const
	{
		return m_Current == other.m_Current;
	};

    T& dereference()const
	{
		return m_Current->data;
	};
	virtual void increment()
	{
	};

protected:
	N *m_Current;
};


/*!
  traverses the tree in preorder(root, left, right)
  using a stack
*/
template <typename T, typename N>
class btree_preorder_iterator : public btree_iterator<T, N> 
{
public:
	btree_preorder_iterator()
		:btree_iterator<T, N>(),
		m_NextNode(this->m_Current)
	{};

	explicit btree_preorder_iterator(N* node)
		:btree_iterator<T, N>(node),
		m_NextNode(this->m_Current)
	{
		m_Stack.push(m_NextNode);
	};

	void increment()
	{
		if(nullptr == this->m_Current)
			return;
		if(!m_Stack.empty())
		{
			m_NextNode = m_Stack.top();
			m_Stack.pop();
			if(nullptr != m_NextNode->right)
				m_Stack.push(m_NextNode->right);
			if(nullptr != m_NextNode->left)
				m_Stack.push(m_NextNode->left);
			this->m_Current = m_NextNode;
		}
		else
		{
			this->m_Current = nullptr;
		}
	};

private:
	N *m_NextNode;
	std::stack<N*> m_Stack;
};

/*!
  traverses the tree in inorder(symmetric order -- left, root, right)
  using a stack
*/
template <typename T, typename N>
class btree_inorder_iterator : public btree_iterator<T, N> 
{
public:
	btree_inorder_iterator()
		:btree_iterator<T, N>(),
		m_NextNode(this->m_Current)
	{};
	explicit btree_inorder_iterator(N* node)
		:btree_iterator<T, N>(node),
		m_NextNode(this->m_Current)
	{};

	void increment()
	{
		if(nullptr == this->m_Current)
			return;
		while(nullptr != m_NextNode)
		{
			m_Stack.push(m_NextNode);
			m_NextNode = m_NextNode->left;
		}
		if(!m_Stack.empty())
		{
			m_NextNode = m_Stack.top();
			m_Stack.pop();
			this->m_Current = m_NextNode;
			m_NextNode = m_NextNode->right;
		}
		else
			this->m_Current = nullptr;
	}

private:
	N *m_NextNode;
	std::stack<N*> m_Stack;
};

/*!
  traverses the tree in postorder(left, right, root)
  using a stack
*/
template <typename T, typename N>
class btree_postorder_iterator : public btree_iterator<T, N> 
{
public:
	btree_postorder_iterator()
		:btree_iterator<T, N>(),
		m_NextNode(this->m_Current)
	{};
	explicit btree_postorder_iterator(N* node)
		:btree_iterator<T, N>(node),
		m_NextNode(this->m_Current)
	{};

	void increment()
	{
		if(nullptr == this->m_Current)
			return;
		while(true)
		{
			if(nullptr != m_NextNode)
			{
				if(nullptr != m_NextNode->right)
				{
					m_Stack.push(m_NextNode->right);
				}
				m_Stack.push(m_NextNode);
				m_NextNode = m_NextNode->left;
				continue;
			}

			if(!m_Stack.empty())
			{
				m_NextNode = m_Stack.top();
				m_Stack.pop();
				if( (nullptr != m_NextNode->right) && !m_Stack.empty() && (m_Stack.top() == m_NextNode->right) )
				{
					m_Stack.pop();
					m_Stack.push(m_NextNode);
					m_NextNode = m_NextNode->right;
				}
				else
				{
					this->m_Current = m_NextNode;
					m_NextNode = nullptr;
					return;
				}
			}
			else
			{
				this->m_Current = nullptr;
				return;
			}
		}
	}

private:
	N *m_NextNode;
	std::stack<N*> m_Stack;
};


///////////////////////////////////////////////////////////////////////////////////
///partial specialization for iterators in a threaded binary tree representation///
///////////////////////////////////////////////////////////////////////////////////

/*!
  binary tree iterator base class 
  uses boost::iterator_facade to implement the iterator
  !the threaded tree iterators are bidirectional
*/
template <typename T>
class btree_iterator<T, btree_threaded_node<T> >: public boost::iterator_facade<btree_iterator<T, btree_threaded_node<T> >, T, boost::bidirectional_traversal_tag>
{
protected:
	typedef btree_threaded_node<T> N;
	btree_iterator()
		:m_Current(nullptr),
		m_Root(nullptr)
	{};
	explicit btree_iterator(N* node, N* root)
		:m_Current(node),
		m_Root(root)
	{};

    friend class boost::iterator_core_access;
	template <typename> friend class cThreadedRep;

	bool equal(const btree_iterator<T, N>& other)const
	{
		return (m_Current == other.m_Current) && (m_Root == other.m_Root);
	};

    T& dereference()const
	{
		return m_Current->data;
	};
	virtual void increment()
	{};
	virtual void decrement()
	{};

protected:
	N *m_Current;
	N *m_Root;
};

/*!
  traverses the tree in inorder(symmetric order -- left, root, right)
  without using an auxiliary stack
*/
template <typename T>
class btree_inorder_iterator<T, btree_threaded_node<T> > : public btree_iterator<T, btree_threaded_node<T> > 
{
	typedef btree_threaded_node<T> N;
public:
	btree_inorder_iterator()
		:btree_iterator<T, N>()
	{};
	explicit btree_inorder_iterator(N* node, N* root)
		:btree_iterator<T, N>(node, root)
	{};

	void increment()
	{
		if(nullptr == this->m_Current)
			return;
		if(true == this->m_Current->rTag)
		{
			this->m_Current = this->m_Current->right;
			return;
		}
		else
		{
			this->m_Current = this->m_Current->right;
		}
		while(false == this->m_Current->lTag)
			this->m_Current = this->m_Current->left;

	};

	void decrement()
	{
		if(nullptr == this->m_Current || this->m_Current == this->m_Root)
			return;
	
		while(this->m_Current->lTag != false)
		{
			this->m_Current = this->m_Current->left;
		}
		this->m_Current = this->m_Current->left;
	};
};

};//namespace tree

#endif

