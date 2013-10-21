#ifndef OCR_BST_H
#define	OCR_BST_H

#include <string>
#include <iostream>
#include "Occurrence.h"


//!  BSTNode implements a binary search tree node
class OcrBSTNode 
{
		friend class OcrBST;   //!< BST can access private members of BSTNodeOcrBST

	public:

		//!  Constructor
		OcrBSTNode(const Occurrence & v) :
		  value(v), left(NULL), right(NULL)
		{
		}

		//! Copy Constructor

		OcrBSTNode(const OcrBSTNode & other) :

		value(other.value),left(other.left),right(other.right)

		{

		}


		//!  Read-only public methods for use by clients of the OcrBST class
		Occurrence & GetValue() 
		{
		  return value;
		}

		void IncrementOccurrence()
		{
			value.IncrementCount();
			
		}

		OcrBSTNode * GetLeft()const
		{
		  return left;
		}


		OcrBSTNode * GetRight()const
		{
		  return right;
		}



		//! Assignment operator

		OcrBSTNode & operator=(const OcrBSTNode & other)

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
		Occurrence value;  //!< value stored in the node
		OcrBSTNode * left;     //!< pointer to the node's left child
		OcrBSTNode * right;    //!< pointer to the node's right child
};


//!  OcrBST implements a binary search tree
class OcrBST 
{

	public:

		//!  No-arg constructor.  Initializes an empty OcrBST
		OcrBST();


		//!  Copy constructor.  Makes a complete copy of its argument
		OcrBST(const OcrBST & other);


		//!  Destructor
		~OcrBST();


		//!  Assignment operator.  Makes a complete copy of its argument
		//!  @return Reference to oneself
		OcrBST& operator =(const OcrBST & other);


		//!  @return a pointer to the root node of the tree, or NULL if the tree is empty.
		//!  @note This is useful for OcrBST clients that need to traverse the tree.)
		OcrBSTNode * GetRoot()const;
  

		//!  @return the number of values in the OcrBST
		int GetSize() const;


		//!  Inserts value v into the OcrBST
		//!
		//!  @param v The new value being inserted
		//!
		//!  @return a pointer to the newly inserted node, or NULL if v was already
		//!          in the tree (i.e., NULL is used to indicate a duplicate insertion)
		OcrBSTNode * Insert(const Occurrence & v);


		//!  Searches the tree for value v
		//!
		//!  @param v The new value being searched for
		//!
		//!  @return a pointer to the node containing v, or NULL if v is not in the tree
		OcrBSTNode * Find(const Occurrence & v) const;


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
	OcrBSTNode * root;
	int size;
	OcrBSTNode * returnValue;
	void recursive_delete_node(OcrBSTNode * current_node);
	void recursive_insert(OcrBSTNode * current_node, const Occurrence & v);
	OcrBSTNode * recursive_find(OcrBSTNode * current_node, const Occurrence & v) const;
	OcrBSTNode * recursive_copy(OcrBSTNode * current_node) const;

};

#endif	

