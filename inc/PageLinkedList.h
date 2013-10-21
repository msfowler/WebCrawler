#ifndef PAGE_LINKEDLIST_H
#define	PAGE_LINKEDLIST_H

#include <string>
#include "Page.h"

//! LLNode implements a doubly-linked list node
class PageLLNode 
{
		friend class PageLinkedList; 
	public:

		//!  Constructor
		PageLLNode(Page * v, PageLLNode * p, PageLLNode * n) :
		  value(v), prev(p), next(n)
		{
		}

		//! Copy Constructor
		PageLLNode(const PageLLNode & other) :
		   value(other.value),prev(other.prev),next(other.next)
		{
		}

		Page * GetValue() const
		{
		  return value;
		}


		PageLLNode * GetPrevious()const
		{
		  return prev;
		}


		PageLLNode * GetNext()const
		{
		  return next;
		}

		//! Assignment operator
		PageLLNode & operator=(const PageLLNode & other)
		{
			if(this!=&other)
			{
				value=other.value;
				prev=other.prev;
				next=other.next;
			}
			return *this;
		}

	private:
		Page * value;        //!< value stored in the node
		PageLLNode * prev;            //!< pointer to previous node in the list
		PageLLNode * next;            //!< pointer to next node in the list
};



class PageLinkedList
{
	public:

		//!  No-arg constructor.  Initializes an empty linked list
		PageLinkedList();


		//!  Copy constructor.  Makes a complete copy of its argument
		PageLinkedList(const PageLinkedList & other);


		//!  Destructor
		~PageLinkedList();


		//! Assignment operator.  Makes a complete copy of its argument
		//! @return A reference to oneself
		PageLinkedList& operator =(const PageLinkedList & other);


		//!  @return true if the list is empty, or false if the list is not empty
		bool IsEmpty() const;


		//!  Removes all values from the list
		void Clear();


		//!  @return the number of values in the list
		int GetSize() const;



		//!  @return a pointer to the first node in the list, or NULL if the list is empty
		PageLLNode * GetFirst()const;



		//!  @returns a pointer to the last node in the list, or NULL if the list is empty
		PageLLNode * GetLast()const;


		//!  Inserts value v into the list after node n
		//!
		//!  @param v The new value being inserted
		//!  @param n A node that is already in the list after which the new node should
		//!      be inserted.
		//!      If n is NULL, the new node should be inserted at the beginning of the list.
		//!
		//!  @return a pointer to the newly inserted node
		PageLLNode * Insert(Page * v, PageLLNode * n);


		//! Searches for the first occurrence of value v that appears in the list
		//!   after node n
		//!
		//!  @param v The value being searched for
		//!  @param n The node in the list after which the search should begin.
		//!      If n is NULL, the list should be searched from the beginning.
		//!
		//!  @return a pointer to the node containing v, or NULL if v is not found
		PageLLNode * Find(Page * v, PageLLNode * n) const;


		//!  Removes node n from the list
		//!
		//!  @param n The node being removed from the list
		void Remove(PageLLNode * n);

	private:
	PageLLNode * first;
	PageLLNode * last;
	int size;

	void double_link(PageLLNode * current_node);
	PageLLNode * recursive_find(PageLLNode * start_point, Page * v) const;
	void recursive_delete(PageLLNode * current_node);
	PageLLNode * recursive_copy(PageLLNode * current_node);
	void Copy(const PageLinkedList & other);
	void Free();
};

#endif	/* _LINKEDLIST_H */

