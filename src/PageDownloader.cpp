#include "PageDownloader.h"
#include "URLInputStream.h"
#include "CS240Exception.h"
#include <iostream>
#include "UnitTest.h"


string PageDownloader::download(URL & url)
{
	string urlString(url.GetResolvedURL());
	string returnString;


	try
	{
		URLInputStream stream(urlString);
		
		while(!stream.IsDone())
		{
			returnString += stream.Read();
		}
	}
	catch (std::exception &e)
	{
		throw e; 
	}
	catch (CS240Exception &e)
	{
		throw e;
	}

	return returnString; 

}

bool PageDownloader::Test(ostream & os)
{
	bool success = true;
	
	URL u0("http://thomasandmelyssa.son.org/cs240.html","");
	URL u1("http://thomasandmelyssa.son.org/BOGUS","");
	URL u2("file:///users/guest/m/melyssas/cs240/WebCrawler/test/testpage.html","");

	string s0 = download(u0);
	string s2 = download(u2);

	TEST(s0 == "this is a test for my cs project\n");
	TEST(s2 == "oh hai!\n");

	bool exceptionCaught = false; 

	try
	{
		string s1 = download(u1);
	}
	catch(CS240Exception &e)
	{
		exceptionCaught = true;
	}

	TEST(exceptionCaught);
	return success;
}
