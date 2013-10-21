#ifndef KEYWORD_PAIR_BST_H
#define	KEYWORD_PAIR_BST_H

#include <string>
#include <iostream>
#include "KeywordPair.h"
#include "Occurrence.h"


//!  BSTNode implements a binary search tree node
class KeywordPairBSTNode 
{
		friend class KeywordPairBST;   //!< BST can access private members of BSTNodeKeywordPairBST

	public:

		//!  Constructor
		KeywordPairBSTNode(const KeywordPair & v) :
		  value(v), left(NULL), right(NULL)
		{
		}

		//! Copy Constructor

		KeywordPairBSTNode(const KeywordPairBSTNode & other) :

		value(other.value),left(other.left),right(other.right)

		{

		}


		//!  Read-only public methods for use by clients of the KeywordPairBST class
		KeywordPair & GetValue() 
		{
		  return value;
		}

		void addOccurrence(const Occurrence & occr)
		{
			value.addOccurrence(occr);
		}

		KeywordPairBSTNode * GetLeft()const
		{
		  return left;
		}


		KeywordPairBSTNode * GetRight()const
		{
		  return right;
		}

		//! Assignment operator

		KeywordPairBSTNode & operator=(const KeywordPairBSTNode & other)

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
		KeywordPair value;  //!< value stored in the node
		KeywordPairBSTNode * left;     //!< pointer to the node's left child
		KeywordPairBSTNode * right;    //!< pointer to the node's right child
};


//!  KeywordPairBST implements a binary search tree
class KeywordPairBST 
{

	public:

		//!  No-arg constructor.  Initializes an empty KeywordPairBST
		KeywordPairBST();


		//!  Copy constructor.  Makes a complete copy of its argument
		KeywordPairBST(const KeywordPairBST & other);


		//!  Destructor
		~KeywordPairBST();


		//!  Assignment operator.  Makes a complete copy of its argument
		//!  @return Reference to oneself
		KeywordPairBST& operator =(const KeywordPairBST & other);


		//!  @return a pointer to the root node of the tree, or NULL if the tree is empty.
		//!  @note This is useful for KeywordPairBST clients that need to traverse the tree.)
		KeywordPairBSTNode * GetRoot()const;
  

		//!  @return the number of values in the KeywordPairBST
		int GetSize() const;


		//!  Inserts value v into the KeywordPairBST
		//!
		//!  @param v The new value being inserted
		//!
		//!  @return a pointer to the newly inserted node, or NULL if v was already
		//!          in the tree (i.e., NULL is used to indicate a duplicate insertion)
		KeywordPairBSTNode * Insert(const KeywordPair & v);


		//!  Searches the tree for value v
		//!
		//!  @param v The new value being searched for
		//!
		//!  @return a pointer to the node containing v, or NULL if v is not in the tree
		KeywordPairBSTNode * Find(const string & v) const;


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
	KeywordPairBSTNode * root;
	int size;
	KeywordPairBSTNode * returnValue;
	void recursive_delete_node(KeywordPairBSTNode * current_node);
	void recursive_insert(KeywordPairBSTNode * current_node, const KeywordPair & v);
	KeywordPairBSTNode * recursive_find(KeywordPairBSTNode * current_node, const string & v) const;
	KeywordPairBSTNode * recursive_copy(KeywordPairBSTNode * current_node) const;

};

#endif	

