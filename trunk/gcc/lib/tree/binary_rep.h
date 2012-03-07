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
	typedef btree_iterator<T, node_type > iterator;

	cBinaryRep()
	{};
	~cBinaryRep()
	{};

	/*!
	  copy constructor -- copies the whole tree
	*/
	cBinaryRep(const cBinaryRep &bin_rep)
	{
		//TODO			
	};
	
	/*!
	  assignment operator -- copies the whole tree
	*/
	cBinaryRep& operator=(const cBinaryRep &bin_rep)
	{
		//TODO	
	};

	/*!
	  checks for equality -- !compares the data in every node of the tree for equality
	*/
	bool operator==(const cBinaryRep& bin_rep)
	{
		//TODO
	};

	/*!
	  returns an iterator to the beginning of the tree for inorder traversal
	*/
	iterator begin_inorder()
	{
		return iterator(&m_Root, INORDER);
	};

	/*!
	  returns an iterator to the beginning of the tree for preorder traversal
	*/
	iterator begin_preorder()
	{
		return iterator(&m_Root, PREORDER);
	};

	/*!
	  returns an iterator to the beginning of the tree for postorder traversal
	*/
	iterator begin_postorder()
	{
		return iterator(&m_Root, POSTORDER);
	};

	/*!
	  returns an empty iterator signifying the end of the tree
	  ! used in constructs like for(iterator it = tree.begin(); it != tree.end(); it++)
	*/
	iterator end()
	{
		return iterator();
	};

	/*!
	  inserts data as a left child of the node indicated by the iterator
	*/
	iterator& insertLeft(iterator &iter, T &data)
	{
		assert(nullptr == iter.m_Current);
		iter.m_Current->left = new node_type(data);
		iter.m_Current = iter.m_Current->left;
		return iter;
	};

	/*!
	  inserts data as a right child of the node indicated by the iterator
	*/
	iterator& insertRight(iterator &iter, T &data)
	{
		assert(nullptr == iter.m_Current);
		iter.m_Current->right = new node_type(data);
		iter.m_Current = iter.m_Current->right;
		return iter;
	};

	iterator& insert(tree_traversal)
	{
		//TODO
	}

	/*!
	  traverse the binary tree in the given tree_traversal order 
	  a std::unary_function<T, void> must be also given as a parameter
	  it calls the unary_function for the data in every node of the tree
	*/
	void traverse(tree_traversal traversal, std::unary_function<T, void> visit)
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
					current_node = stack.pop_back();
					visit(current_node->info);
					current_node = current_node->right;
				}
				else
					return;
			}
		}
		else if(PREORDER == traversal)
		{
			stack.push_back(current_node);
			while(!stack.empty())
			{
				current_node = stack.pop_back();
				if(nullptr != current_node->right)
					stack.push_back(current_node->right);
				if(nullptr != current_node->left)
					stack.push_back(current_node->left);
				visit(current_node->info);
			}
		}
		else
		{
			assert(POSTORDER == traversal);
		}
	};

private:
	node_type m_Root;
};

};//namespace tree
#endif

