#include "PageHistory.h"
#include <iostream>
#include "UnitTest.h"
	 
PageHistory::PageHistory()
{
}
	 

PageHistory::~PageHistory()
{
}

void PageHistory::AddPage(Page * page)
{
	History.Insert(page);
}
	  
bool PageHistory::CheckHistory(Page * page)
{
	if(History.Find(page) != NULL)
		return true;
	else
		return false;
}

Page * PageHistory::GetStartPage()
{
	PageBSTNode * node = History.GetRoot();
	return node->GetValue();
}

int PageHistory::getHistorySize()
{
	return History.GetSize();
}


Page ** PageHistory::getHistory()
{
	//Make an Array on the heap
	Page ** allPages = new Page*[History.GetSize()]; 

	//recursively traverse tree adding to array

	int idx = 0;
	if(History.GetRoot() != NULL)
	{
		traverseTree(allPages, History.GetRoot(), idx);
	}

	return allPages;
}

int PageHistory::traverseTree(Page ** allPages, PageBSTNode * currentNode, int idx)
{
	if(currentNode != NULL)
	{
		allPages[idx]  = currentNode->GetValue();
		idx++;
	}

	if(currentNode->GetLeft() != NULL)
	{
		idx = traverseTree(allPages, currentNode->GetLeft(), idx);
	}
	
	if(currentNode->GetRight() != NULL)
	{
		idx = traverseTree(allPages, currentNode->GetRight(), idx);
	}
	
	return idx; 

}

bool PageHistory::Test(ostream & os)
{
	bool success = true;
	PageHistory test0;

	TEST(test0.getHistorySize() == 0);
	
	//Some pages for testing
	URL u0("http://www.example.com", "");
	URL u1("http://www.slashdot.org",""); 
	URL u2("http://www.amazon.com","");
	URL u3("http://www.byu.edu","");
	string s0("This is a dummy Page");
	string s1("News for Nerds");
	string s2("This is where I buy my books");
	string s3("Brigham Young University");
	Page p0(s0, u0);
	Page p1(s1, u1);
	Page p2(s2, u2);
	Page p3(s3, u3);

	test0.AddPage(&p0);
	TEST(test0.getHistorySize() == 1);

	Page ** testHist0 = test0.getHistory();
	TEST(testHist0[0]->compare(&p0) ==0 );
	TEST(test0.GetStartPage()->compare(&p0) == 0);

	test0.AddPage(&p1);
	test0.AddPage(&p2);
	test0.AddPage(&p3);
	TEST(test0.GetStartPage()->compare(&p0) == 0);
	TEST(test0.getHistorySize() == 4);
	
	delete [] testHist0;


	Page ** testHist1 = test0.getHistory();
	
	TEST(test0.GetStartPage()->compare(&p0) == 0);
	TEST(testHist1[0]->compare(&p0) ==0 );
	TEST(testHist1[1]->compare(&p2) ==0 );
	TEST(testHist1[2]->compare(&p3) ==0 );
	TEST(testHist1[3]->compare(&p1) ==0 );

	delete [] testHist1;

	return success;
}
