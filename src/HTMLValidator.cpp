#include "HTMLValidator.h"
#include <iostream>
#include <string.h>
#include "UnitTest.h"

bool HTMLValidator::isValid(const URL & url)
{

	string resolvedURL = url.GetResolvedURLWithoutQuery();

	if(resolvedURL == "")
		return false;

	char path[resolvedURL.size()];
	strcpy(path, resolvedURL.c_str());

	char * pathBeg = path;
	pathBeg+=7; //remove http:// or file://
	pathBeg += url.GetNet_Loc().size();  //remove net loc
	
	//remove all subdirectories

	char * pathPtr = strtok(pathBeg, "/");
	char * previousPathPtr = NULL;

	while(pathPtr != NULL)
	{
		previousPathPtr = pathPtr;
  		pathPtr = strtok(NULL, "/"); 
	}


	//condition 1
	if(previousPathPtr == NULL)
	{
		return true;
	}	
	else
	{
		char * fileExtension = strtok(previousPathPtr, ".");
		fileExtension = strtok(NULL,".");

		if(fileExtension == NULL)
		{
			return true;
		}
		else
		{
			return checkValidExtensions(fileExtension);
		}
	}
	

}

bool HTMLValidator::checkValidExtensions(char * ext)
{
	if(strcmp(ext,"html")==0) return true;
	if(strcmp(ext,"htm")==0) return true;
	if(strcmp(ext,"shtml")==0) return true;
	if(strcmp(ext,"cgi")==0) return true;
	if(strcmp(ext,"jsp")==0) return true;

	return checkAdditionalValidExtensions(ext);

}
	
bool HTMLValidator::checkAdditionalValidExtensions(char * ext)
{
	//Note: this function really could be combined with checkValidExtenstions
	//but checkstyle says 11 if statements are too many for one function.

	if(strcmp(ext,"asp")==0) return true;
	if(strcmp(ext,"aspx")==0) return true;
	if(strcmp(ext,"php")==0) return true;
	if(strcmp(ext,"pl")==0) return true;
	if(strcmp(ext,"cfm")==0) return true;
	
	return false;

}

bool HTMLValidator::isInScope(const URL & url, const URL & startURL)
{
	size_t scope = startURL.GetResolvedURL().find_last_of('/');

	string urlString = url.GetResolvedURL();
	string startURLstring = startURL.GetResolvedURL();

	for(size_t I=0; I<scope; I++)
    {
		if(urlString[I] != startURLstring[I])
			return false;
	}

	return true;

}

bool HTMLValidator::Test(ostream & os) 
{
	bool success = true;
	//Check isValid
	URL u0("","");
	URL u1("http://www.google.com","");
	URL u2("http://www.amazon.com/","");
	URL u3("http://www.ebay.com/stuff/words/thisisjunk","");
	URL u4("http://www.slashdot.org/stuff/words/thisisjunk/","");
	URL u5("http://www.facebook.com/stuff/words/thisisjunk.html","");
	URL u6("file:///stuff/words/thisisjunk.htm","");
	URL u7("http://www.facebook.com/stuff/words/thisisjunk.shtml","");
	URL u8("http://www.facebook.com/stuff/words/thisisjunk.cgi","");
	URL u9("http://www.facebook.com/stuff/words/thisisjunk.jsp?query=woot","");
	URL u10("http://www.facebook.com/stuff/words/thisisjunk.asp","");
	URL u11("http://www.facebook.com/stuff/words/thisisjunk.pl","");
	URL u12("http://www.facebook.com/stuff/words/thisisjunk.cfm","");
	URL u13("http://www.stuff.com/file.bogus","");

	TEST(isValid(u0)== false);
	TEST(isValid(u1)== true);
	TEST(isValid(u2)== true);
	TEST(isValid(u3)== true);
	TEST(isValid(u4)== true);
	TEST(isValid(u5)== true);
	TEST(isValid(u6)== true);
	TEST(isValid(u7)== true);
	TEST(isValid(u8)== true);
	TEST(isValid(u9)== true);
	TEST(isValid(u10)== true);
	TEST(isValid(u11)== true);
	TEST(isValid(u12)== true);
	TEST(isValid(u13)== false);
	TEST(checkValidExtensions("bogus") == false);

	//Check is in scope


	return success;
}
