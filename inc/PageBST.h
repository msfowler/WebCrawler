#ifndef PAGE_BST_H
#define	PAGE_BST_H

#include <string>
#include <iostream>
#include "Page.h"


//!  BSTNode implements a binary search tree node
class PageBSTNode 
{
		friend class PageBST;   //!< BST can access private members of BSTNodePageBST

	public:

		//!  Constructor
		PageBSTNode(Page * v) :
		  value(v), left(NULL), right(NULL)
		{
		}

		//! Copy Constructor

		PageBSTNode(const PageBSTNode & other) : 
			value(other.value),left(other.left),right(other.right)
		{
		}


		//!  Read-only public methods for use by clients of the PageBST class
		Page * GetValue() 
		{
		  return value;
		}
 
		PageBSTNode * GetLeft() const
		{
		  return left;
		}


		PageBSTNode * GetRight() const
		{ 
		  return right;
		}



		//! Assignment operator

		PageBSTNode & operator=(const PageBSTNode & other)

		{

			if(this!=&other)

			{
				value=other.value;
				left=other.left;

				right=other.right;

			}
			return *this;
		}

	private:
		Page * value;  //!< value stored in the node
		PageBSTNode * left;     //!< pointer to the node's left child
		PageBSTNode * right;    //!< pointer to the node's right child
};


//!  PageBST implements a binary search tree
class PageBST 
{

	public:

		//!  No-arg constructor.  Initializes an empty PageBST
		PageBST();


		//!  Copy constructor.  Makes a complete copy of its argument
		PageBST(const PageBST & other);


		//!  Destructor
		~PageBST();


		//!  Assignment operator.  Makes a complete copy of its argument
		//!  @return Reference to oneself
		PageBST& operator =(const PageBST & other);


		//!  @return a pointer to the root node of the tree, or NULL if the tree is empty.
		//!  @note This is useful for PageBST clients that need to traverse the tree.)
		PageBSTNode * GetRoot()const;
  

		//!  @return the number of values in the PageBST
		int GetSize() const;


		//!  Inserts value v into the PageBST
		//!
		//!  @param v The new value being inserted
		//!
		//!  @return a pointer to the newly inserted node, or NULL if v was already
		//!          in the tree (i.e., NULL is used to indicate a duplicate insertion)
		PageBSTNode * Insert(Page * v);


		//!  Searches the tree for value v
		//!
		//!  @param v The new value being searched for
		//!
		//!  @return a pointer to the node containing v, or NULL if v is not in the tree
		PageBSTNode * Find(Page * v) const;


		//! @NOTE: YOU ARE NOT REQUIRED TO IMPLEMENT THE Remove METHOD BELOW
		//!        (BUT YOU CAN IF YOU WANT TO)
		//!
		//!  Removes value v from the tree
		//!
		//!  @param v The value being removed from the tree
		//!
		//!  @return true if v was removed from the tree, or false if v was not in the tree
		//bool Remove(const Occurrence & v);

	private:
	PageBSTNode * root;
	int size;
	PageBSTNode * returnValue;
	void recursive_delete_node(PageBSTNode * current_node);
	void recursive_insert(PageBSTNode * current_node, Page * v);
	PageBSTNode * recursive_find(PageBSTNode * current_node, Page * v) const;
	PageBSTNode * recursive_copy(PageBSTNode * current_node) const;

};

#endif	

