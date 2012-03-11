#ifndef BINARY_REP_H
#define BINARY_REP_H

#include <functional>

#include  "tree_common.h"
#include "binary_tree_iter.h"

namespace tree
{

/*!
  binary tree usual representation(left node pointing to the left subtree,
  right node pointing to the right subtree)
*/
template<typename T>
class cBinaryRep
{
private:
	

public:
	typedef btree_node<T> node_type;
	typedef btree_iterator<T, node_type> iterator;
	typedef btree_preorder_iterator<T, node_type > preorder_iterator;
	typedef btree_inorder_iterator<T, node_type > inorder_iterator;
	typedef btree_postorder_iterator<T, node_type > postorder_iterator;


protected:	//can't construct cBinaryRep object directly -- only through cBinaryTree
	cBinaryRep()
		:m_Root(nullptr)
	{};

	~cBinaryRep()
	{};

	cBinaryRep(const cBinaryRep &bin_rep)
	{};
	
	cBinaryRep& operator=(const cBinaryRep &bin_rep)
	{};

public:
	/*!
	  checks for equality -- !compares the data in every node of the tree for equality
	*/
	bool operator==(const cBinaryRep& bin_rep)
	{
		std::stack<node_type*> this_stack;
		std::stack<node_type*> other_stack;

		node_type *current_this_node = this.m_Root;
		node_type *current_other_node = bin_rep.m_Root;
		while(true)
		{
			if( (nullptr != current_this_node) || (nullptr != current_other_node) )
			{
				if( (nullptr == current_other_node) || (nullptr == current_this_node) )
					return false;
				this_stack.push(current_this_node);
				other_stack.push(current_other_node);
				current_this_node = current_this_node->left;
				current_other_node = current_other_node->left;
				continue;
			}
			if(!this_stack.empty() || !other_stack.empty())
			{
				if(other_stack.empty() || this_stack.empty())
					return false;
				current_this_node = this_stack.top();
				this_stack.pop();
				current_other_node = other_stack.top();
				other_stack.pop();
				if(current_this_node->data != current_other_node->data);
					return false;
				current_this_node = current_this_node->right;
				current_other_node = current_other_node->right;
			}
			else
			{
					return true;
			}
		}
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
		if(nullptr == iter.m_Current->left)
		{
			iter.m_Current->left = new node_type(data);
			return inorder_iterator(iter.m_Current->left);
		}
		else
		{
			node_type *node = iter.m_Current->left;
			iter.m_Current->left = new node_type(data);
			iter.m_Current->left->left = node;
			return inorder_iterator(iter.m_Current->left);
		}
	};

	/*!
	  inserts data as a right child of the node indicated by the iterator
	*/
	iterator insertRightChild(iterator iter, const T& data)
	{
		if(nullptr == iter.m_Current->right)
		{
			iter.m_Current->right = new node_type(data);
			return inorder_iterator(iter.m_Current->right);
		}
		else
		{
			node_type *node = iter.m_Current->right;
			iter.m_Current->right = new node_type(data);
			iter.m_Current->right->right = node;
			return inorder_iterator(iter.m_Current->right);
		}
	};

	iterator insertRoot(const T& data)
	{
		assert(nullptr == m_Root);
		m_Root = new node_type(data);
		inorder_iterator iter(m_Root);
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
		node_type *current_node = m_Root;
		std::stack<node_type*> stack;
		if(INORDER == traversal)
		{
			while(true)
			{
				if(nullptr != current_node)
				{
					stack.push(current_node);
					current_node = current_node->left;
					continue;
				}
				if(!stack.empty())
				{
					current_node = stack.top();
					stack.pop();
					visit(current_node->data);
					current_node = current_node->right;
				}
				else
					return;
			}
		}
		else if(PREORDER == traversal)
		{
			stack.push(current_node);
			while(!stack.empty())
			{
				current_node = stack.top();
				stack.pop();
				if(nullptr != current_node->right)
					stack.push(current_node->right);
				if(nullptr != current_node->left)
					stack.push(current_node->left);
				visit(current_node->data);
			}
		}
		else
		{
			assert(POSTORDER == traversal);
			while(true)
			{
				if(nullptr != current_node)
				{
					if(nullptr != current_node->right)
					{
						stack.push(current_node->right);
					}
					stack.push(current_node);
					current_node = current_node->left;
					continue;
				}

				if(!stack.empty())
				{
					current_node = stack.top();
					stack.pop();
					if( (nullptr != current_node->right) && !stack.empty() && (stack.top() == current_node->right) )
					{
						stack.pop();
						stack.push(current_node);
						current_node = current_node->right;
					}
					else
					{
						visit(current_node->data);
						current_node = nullptr;
					}
				}
				else
				{
					return;
				}

			}
		}
	};

private:
	node_type *m_Root;
};

};//namespace tree
#endif

