/*
 *  Page.cpp
 *  
 *
 */

#include "Page.h"
#include "UnitTest.h"
#include <iostream>

Page::Page()
{
}

Page::Page(const string & desc, const URL & url) : description(desc), page_URL(url)
{
}

Page::Page(const Page & other) 
{
	Copy(other);
}

Page & Page::operator=(const Page & other)
{

	if(&other != this)
	{
		//no need to call destructor since it doesn't do anything. 
		Copy(other);
	}

	return *this;
}

Page::~Page()
{ 
}

void Page::Copy(const Page & other)
{
	description = other.GetDescription();
	page_URL = other.GetURL();

}

string Page::GetDescription() const
{
	return description; 
}

const URL & Page::GetURL() const
{
	return page_URL; 
}

void Page::SetURL(const URL & url)
{
	page_URL = url;
}

void Page::SetDescription(const string & desc)
{
	description = desc; 
}

int Page::compare(Page * v) const
{ 
	string myURLstring = page_URL.GetResolvedURL();
	string hisURLstring = v->GetURL().GetResolvedURL();
	int result = myURLstring.compare(hisURLstring);

	return result;
}

bool Page::Test(ostream & os)
{
	bool success = true;

	URL testURL("http://www.example.com", "");
	URL testURL2("http://www.slashdot.org",""); 
	URL testURL3("http://www.amazon.com","");
	URL testURL4("http://WWW.WRONG.COM","");
	string testString("This is a dummy Page");
	string testString2("News for Nerds");
	string testString3("This is where I buy my books");

	Page test0(testString, testURL);
	Page test1(testString3, testURL3); 

	TEST(test0.GetDescription() == "This is a dummy Page");
	TEST(test0.GetURL().GetResolvedURL() == "http://www.example.com");
	
	test0.SetURL(testURL2);
	TEST(test0.GetURL().GetResolvedURL() == "http://www.slashdot.org");
	
	test0.SetDescription(testString2);
	TEST(test0.GetDescription() == "News for Nerds");

	TEST(test1.compare(&test0) != 0 && test0.compare(&test1) != 0);
	
	//Test Copy Constructor
	Page test2(test1);
	
	TEST(test2.compare(&test1) == 0 && test1.compare(&test2) == 0);
	
	test2.SetDescription("DUMMY");
	test2.SetURL(testURL4);

	TEST(test2.compare(&test1) != 0 && test1.compare(&test2) != 0);

	//Test Assignment Operator

	test2 = test1;

	TEST(test2.compare(&test1) == 0 && test1.compare(&test2) == 0);
	
	test2.SetDescription("DUMMY");
	test2.SetURL(testURL4);

	TEST(test2.compare(&test1) != 0 && test1.compare(&test2) != 0);
	
	return success;
}

//string & desc = page.GetDescription(); //doesn't copy
//string desc = page.GetDescription(); //copies (GetDesc returns &)
