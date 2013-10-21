#ifndef PAGE_HISTORY_H
#define PAGE_HISTORY_H

#include <string>
#include "Page.h"
#include "PageBST.h"

using namespace std;

/*
 * The PageHistory Class stores a history of all the pages that have been processed
 *
 */

class PageHistory {

private:
    PageBST History;

	int traverseTree(Page ** allPages, PageBSTNode * currentNode, int idx);

public:
	
	/* 
	 * No-arg constructor
	 */
	 
	 PageHistory();
	 
	 
	 /*
	  * Destructor
	  */ 
	  
	 ~PageHistory();
	 
	 /*
	  *  AddPage: Adds a page to the history
	  */
	  
	  void AddPage(Page * page);
	  
	  /*
	  *  CheckHistory: Checks the history to see if page is there, returns true if it is
	  */
	  
	  bool CheckHistory(Page * page);


	 // GetStartPage: returns the start Page, that we started crawling on
	  Page * GetStartPage();


	//Get the number of pages you have in your history
	  int getHistorySize();

	//returns an array with the entire history in it. (no particular order)
	  Page ** getHistory(); 

	static bool Test(ostream & os);
	  
};

#endif
