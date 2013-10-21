#ifndef PAGE_QUEUE_H
#define PAGE_QUEUE_H

#include <string>
#include "Page.h"
#include "PageLinkedList.h"

using namespace std;

/*
 * The PageQueue Class stores all the pages that need to be processed.
 *
 */

class PageQueue {

private:
    PageLinkedList * Queue;

	void Copy(const PageQueue & other);
	void Free();
public:
	
	/* 
	 * No-arg constructor
	 */
	 
	 PageQueue();
	 

	//Copy Constructor
	PageQueue(const PageQueue & other);
	
	// = operator
	PageQueue & operator=(const PageQueue & other); 
	 
	//Destructor
	 ~PageQueue();
	 
	//Gets the next page in the index 
	Page * GetNext();

	//HasNext: if queue is empty returns NO, else returns YES	
	bool HasNext();  

	//adds a page to the queue
	void AddPage(Page * newPage);

	//Unit Tests
	static bool Test(ostream & os);
	  
};

#endif
