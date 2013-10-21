#include "Occurrence.h"
#include "URL.h"
#include "UnitTest.h"
#include <iostream>

Occurrence::Occurrence()
{
	return;
}


Occurrence::Occurrence(Page * p)
{
	page = p;
	count = 1; 
}

Occurrence::Occurrence(const Occurrence & other)
{
	Copy(other);
}

Occurrence & Occurrence::operator=(const Occurrence & other)
{
	if(&other != this)
	{
		//no need to call destructor, since it doesn't do anything
		Copy(other);
	}

	return *this;
}

bool Occurrence::operator ==(const Occurrence & other) const 
{
	if(page->compare(other.page) == 0)
		return true;
	else
		return false; 
}

int Occurrence::compare(const Occurrence & v) const
{
	return page->compare(v.GetPage());
}

Occurrence::~Occurrence()
{
	return;
}

void Occurrence::Copy(const Occurrence & other)
{
	count = other.GetCount();
	page = other.GetPage();
}

int Occurrence::GetCount() const
{
	return count;
}

int Occurrence::IncrementCount()
{
	count++;
	return count;
}

Page * Occurrence::GetPage() const
{
	return page;
}

bool Occurrence::Test(ostream & os)
{
	bool success = true;
	
	URL testURL("www.example.com","");
	string testDesc("This is a dummy page");
	Page testPage1(testDesc, testURL);

	URL testURL2("www.slashdot.com","");
	string testDesc2("woot");
	Page testPage2(testDesc2, testURL2);
	
	Occurrence test0(&testPage1);
	Occurrence test1(test0);

	TEST(test0.GetCount() == 1);
	TEST(test0.GetPage()->compare(&testPage1) == 0);
	TEST(test0.IncrementCount() == 2);
	TEST(test0.IncrementCount() == 3);
	
	//Test copy constructor
	TEST(test1.GetPage()->compare(test0.GetPage()) == 0);
	TEST(test0.count != test1.count);

	//Test Assignment Operator & == operator & compare
	Occurrence test2 = test0;
	TEST(test2.page->compare(test0.page) == 0);
	TEST(test2.count == test0.count);
	TEST(test2 == test0);
	TEST(test2.compare(test0) == 0);
	
	test2.IncrementCount();
	TEST(test2.count != test0.count);

	return success;
}
