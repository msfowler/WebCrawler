#include "PageQueue.h"
#include <iostream>
#include "UnitTest.h"
#include "URL.h"

PageQueue::PageQueue()
{
	Queue = new PageLinkedList();
}

PageQueue::PageQueue(const PageQueue & other) 
{
	Copy(other);
}

PageQueue & PageQueue::operator=(const PageQueue & other)
{
	if(&other != this)
	{
		Free();
		Copy(other);
	}

	return *this;
}

PageQueue::~PageQueue()
{
	Free();
}

void PageQueue::Copy(const PageQueue & other)
{
	Queue = new PageLinkedList(*(other.Queue));
}

void PageQueue::Free()
{
	delete Queue;
}

Page * PageQueue::GetNext()
{
	if (Queue->IsEmpty() == true)
	{
		return NULL;
	}
	else 
	{
		PageLLNode * first = Queue->GetFirst();
		Page * returnPage = first->GetValue(); 
		Queue->Remove(first);
		return returnPage;
	}

}

bool PageQueue::HasNext()
{
	return !(Queue->IsEmpty());
}

void PageQueue::AddPage(Page * newPage)
{
	PageLLNode * last = Queue->GetLast();
	Queue->Insert(newPage, last);

}

bool PageQueue::Test(ostream & os)
{
	bool success = true;

	PageQueue test0;

	TEST(test0.HasNext() == false);
	TEST(test0.GetNext() == NULL);

	URL u0("www.example.com", "");
	URL u1("www.slashdot.org",""); 
	URL u2("www.amazon.com","");
	URL u3("www.byu.edu","");
	string s0("This is a dummy Page");
	string s1("News for Nerds");
	string s2("This is where I buy my books");
	string s3("Brigham Young University");
	Page p0(s0, u0);
	Page p1(s1, u1);
	Page p2(s2, u2);
	Page p3(s3, u3);

	test0.AddPage(&p0);
	TEST(test0.HasNext() == true);
	Page * p4 = test0.GetNext();
	TEST(p4->compare(&p0) == 0);
	TEST(test0.HasNext() == false);

	test0.AddPage(&p0);
	test0.AddPage(&p1);
	test0.AddPage(&p2);
	test0.AddPage(&p3);

	//get them all off
	TEST(test0.HasNext() == true);
	p4 = test0.GetNext();
	TEST(p4->compare(&p0) == 0);

	TEST(test0.HasNext() == true);
	p4 = test0.GetNext();
	TEST(p4->compare(&p1) == 0);

	TEST(test0.HasNext() == true);
	p4 = test0.GetNext();
	p4 = test0.GetNext();
	TEST(p4->compare(&p3) == 0);

	TEST(test0.HasNext() == false);
	
	test0.AddPage(&p0);
	test0.AddPage(&p1);
	p4 = test0.GetNext();
	TEST(p4->compare(&p0) == 0);
	TEST(test0.HasNext() == true);
	test0.AddPage(&p2);
	p4 = test0.GetNext();
	TEST(p4->compare(&p1) == 0);
	p4 = test0.GetNext();
	TEST(p4->compare(&p2) == 0);
	TEST(test0.HasNext() == false);	

	return success;
}
