#include "URL.h"
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include "StringUtil.h"
#include "UnitTest.h"

//c++ automatically calls constructors on all objs inside
URL::URL()
{
	scheme = "";
	net_loc = "";
	path = NULL;
	PathLength = 0;
	RelativeURL = "";
	BaseURL = "";
	ResolvedURL = "";

}



URL::URL(const string & base, const string & url) 
{
	BaseURL = stripQueriesAndFragments(base);
	RelativeURL = stripQueriesAndFragments(url);
	path = new string[100]; //this is automatically expanded if needed. 
	PathLength = 0; 
	
	Resolve();
	
}


URL::URL(const URL & other)
{
	Copy(other);	
}

URL & URL::operator=(const URL & other)
{

	if(&other != this)
	{
		Free();
		Copy(other);
	}

	return *this;
}

void URL::Free()
{

	delete [] path;


}

void URL::Copy(const URL & other)
{
	scheme = other.GetScheme();
	net_loc = other.GetNet_Loc();
	PathLength = other.GetPathLength();
	path = new string[PathLength];
	
	for(int I=0; I<PathLength; I++)
	{
		path[I] =other.GetPath()[I];
	}
	
	RelativeURL = other.GetRelativeURL();
	BaseURL = other.GetBaseURL();
	ResolvedURL = other.GetResolvedURL();
	ResolvedURLWithoutQuery = other.GetResolvedURLWithoutQuery();
}


URL::~URL()
{
	Free();
}

void URL::Resolve()
{

   //convert to cstrings so that I can use some of the standard cstring functions 
	char * resolveBaseURL;
	char * resolveOriginalBaseURL;
	char * resolveRelativeURL;


	resolveBaseURL = new char [BaseURL.size()+1];
	resolveOriginalBaseURL = new char [BaseURL.size()+1];
	resolveRelativeURL = new char[RelativeURL.size()+1];
	

	strcpy(resolveBaseURL, BaseURL.c_str());
	strcpy(resolveOriginalBaseURL, BaseURL.c_str());
	strcpy(resolveRelativeURL, RelativeURL.c_str());
	
	
	if(strcmp(resolveBaseURL, "")!=0)
	{	
		Parse(resolveBaseURL, resolveOriginalBaseURL);
		BuildURL(resolveRelativeURL);
		ResolvedURLWithoutQuery = ResolvedURL;
		ResolvedURL+=query;
	}

	delete [] resolveBaseURL;
	delete [] resolveOriginalBaseURL;
	delete [] resolveRelativeURL;

}

void URL::Parse(char * resolveBaseURL, char * resolveOriginalURL)
{

  	char * pathPtr;
	
	//put the scheme in lowercase
	for(int I=0; I < 4; I++)
	{
		resolveBaseURL[I] = tolower(resolveBaseURL[I]);
	}


  	if(!strncmp(resolveBaseURL, "http", 4))
  	{
    	scheme = "http";
    	resolveBaseURL+=7;
    	//get net loc
    	pathPtr = strtok(resolveBaseURL, "/");
    	net_loc = pathPtr;  
    	pathPtr = strtok(NULL, "/"); 

		//put net loc in lowercase since it is case insensitive
		StringUtil::ToLower(net_loc);    

  	}
  	else
  	{
    	scheme = "file"; 
    	resolveBaseURL+=7;
    	pathPtr = strtok(resolveBaseURL, "/");
  	} 
   	
  	//parse the rest of the path, by tokenizing. 
  	while(pathPtr != NULL)
  	{
		if(PathLength == 100)
		{
			expandPathArray();
		}
		path[PathLength] = pathPtr;
  		pathPtr = strtok(NULL, "/"); 
  		PathLength++;
  	}
 


}

void URL::BuildURL(char * resolveRelativeURL)
{

	ResolvedURL = scheme; 
	
	
	ResolvedURL+="://";

	//build the URL 
	switch(resolveRelativeURL[0])
	{
			  
    case '/' : 
			 addNet_LocIfNeeded();
  			 ResolvedURL+=resolveRelativeURL;
  			 break;
  			 
  case '.' : 
			resolveRelativeURL = navigateToCorrectDirectory(resolveRelativeURL);
  			 
  			 addNet_LocIfNeeded();
			 
  			 
			 for(int I = 0; I<PathLength; I++)
			 {
			  	ResolvedURL+="/";
			  	ResolvedURL+=path[I];
		     }  	
		     ResolvedURL+="/";
			 ResolvedURL+=resolveRelativeURL;
			 break;
  case NULL : 
			addNet_LocIfNeeded();
  
  			for(int I=0; I<PathLength; I++)
             {
               ResolvedURL+="/";
			   ResolvedURL+=path[I];
             }
	 		break;
  default :  

			addNet_LocIfNeeded();
  
  			for(int I=0; I<(PathLength-1); I++)
             {
               ResolvedURL+="/";
			   ResolvedURL+=path[I];
             }

             
			 ResolvedURL+= "/";
			 ResolvedURL+=resolveRelativeURL;

	}

}

void URL::addNet_LocIfNeeded()
{
	 if(scheme[0] == 'h')
  	 {
  	     ResolvedURL+=net_loc;
  	 } 
}

char * URL::navigateToCorrectDirectory(char * resolveRelativeURL)
{
	int count;
	count = 0;
  	PathLength--; //remove the file
  			
  	//go through each ./ and ../ handling as needed.
  	while(count >= 0 )
  	{
  		if(resolveRelativeURL[count] == '.' && resolveRelativeURL[count+1] == '.')
  		{
  			PathLength--;
  			count+= 2;
  		}
  		else if (resolveRelativeURL[count] == '.' && resolveRelativeURL[count+1] == '/')
  		{
  			count++;
  		}
  		else if (resolveRelativeURL[count] != '.' && resolveRelativeURL[count] != '/')
  		{
  			resolveRelativeURL += count; 
  			count = -2; //stop the loop. 
  		}
  			count++;
  		}

	return resolveRelativeURL;
}

string URL::stripQueriesAndFragments(string s)
{
	
	size_t foundQuery = s.find("?");
	size_t foundFragment = s.find("#");

	if(foundFragment != string::npos )
		s.erase(foundFragment);

	if(foundQuery != string::npos)
	{
		query = "";
		for(size_t I=foundQuery; I<s.size(); I++)
		{
			query+=s[I];
		}
		s.erase(foundQuery);
	}
	
	return s;

}

void URL::expandPathArray()
{

	string * newPath = new string[PathLength+100];
	
	for(int I=0; I<PathLength; I++)
	{
		newPath[I] = path[I];
	}

	delete [] path;
	path = newPath;
}



//Accessor Methods
string URL::GetScheme() const
{
	return scheme; 
}

string URL::GetNet_Loc() const
{
	return net_loc; 
}

string * URL::GetPath() const
{
	return path; 
}

int URL::GetPathLength() const
{
	return PathLength; 
}

string URL::GetRelativeURL() const
{
	return RelativeURL;
}

string URL::GetBaseURL() const
{
	return BaseURL; 
}

string URL::GetResolvedURL() const
{
	return ResolvedURL; 
}

string URL::GetResolvedURLWithoutQuery() const
{
	return ResolvedURLWithoutQuery;
}

bool URL::TestBasic(ostream & os) 
{
	bool success = true; 
	//Note:testing the path and path lenght are irrelevent because they are only used internally
    // for parsing
	
	//RELATIVE URL BEGINS WITH / , also testing Parse
	URL testurl("http://www.cnn.com/news/financial/index.html", "/images/nasdaq.jpg");
	TEST(testurl.GetScheme() == "http");
	TEST(testurl.GetNet_Loc() == "www.cnn.com");
	TEST(testurl.GetResolvedURL() == "http://www.cnn.com/images/nasdaq.jpg");
	TEST(testurl.GetRelativeURL() == "/images/nasdaq.jpg");
	TEST(testurl.GetBaseURL() == "http://www.cnn.com/news/financial/index.html");

	//RELATIVE URL (file) BEGINS WITH / also testing Parse
	URL testurl2("file:///news/financial/index.html","/images/nasdaq.jpg");
	TEST(testurl2.GetScheme() == "file");
	TEST(testurl2.GetNet_Loc() == "");
	TEST(testurl2.GetResolvedURL() == "file:///images/nasdaq.jpg");
	TEST(testurl2.GetRelativeURL() == "/images/nasdaq.jpg");
	TEST(testurl2.GetBaseURL() == "file:///news/financial/index.html");	
	//RELATIVE URL BEGINS WITH ./

	URL testurl3("http://www.cnn.com/news/financial/index.html","./images/nasdaq.jpg");
	TEST(testurl3.GetResolvedURL() == "http://www.cnn.com/news/financial/images/nasdaq.jpg");
	
	URL testurl4("file:///news/financial/index.html","./images/nasdaq.jpg");
	TEST(testurl4.GetResolvedURL() == "file:///news/financial/images/nasdaq.jpg");

	//RELATIVE URL BEGINS WITH ../
	URL testurl5("http://www.cnn.com/news/financial/index.html","../images/nasdaq.jpg");
	TEST(testurl5.GetResolvedURL() == "http://www.cnn.com/news/images/nasdaq.jpg");

	URL testurl6("file:///news/financial/index.html","../images/nasdaq.jpg");
	TEST(testurl6.GetResolvedURL() == "file:///news/images/nasdaq.jpg");

	// COMBINATIONS OF ./ and ../
	URL testurl1("http://www.melyssa.com/a/b/c/d/e/f.html", "../././../../word.html");
	TEST(testurl1.GetResolvedURL() == "http://www.melyssa.com/a/b/word.html");

	//RELATIVE URL BEGINS WITH # (shouldn't be added)
	
	URL testurl7("http://www.cnn.com/news/index.html","#HEADLINES");
	TEST(testurl7.GetResolvedURL() == "http://www.cnn.com/news/index.html");
	

	//NORMAL with different uppercase lower case in net loc and scheme
	URL testurl8("HTTP://www.cNn.com/news/financial/index.html","images/nasdaq.jpg");
	TEST(testurl8.GetResolvedURL() == "http://www.cnn.com/news/financial/images/nasdaq.jpg");

	URL testurl20("","");
	TEST(testurl20.GetResolvedURL() == "");

	URL testurl21;
	TEST(testurl21.GetResolvedURL() == "");
	
	return success;

}

bool URL::TestCopying(ostream & os)
{
		bool success = true;
	//test copy constructor
	URL testurl8("http://www.cnn.com/news/financial/index.html","images/nasdaq.jpg");
	URL testurl9(testurl8);
	TEST(testurl8.GetScheme() == testurl9.GetScheme());
	TEST(testurl8.GetNet_Loc() == testurl9.GetNet_Loc());
	TEST(testurl8.GetResolvedURL() == testurl9.GetResolvedURL());
	TEST(testurl8.GetRelativeURL() == testurl9.GetRelativeURL());
	TEST(testurl8.GetBaseURL() == testurl9.GetBaseURL());
	for(int I=0; I<testurl8.GetPathLength(); I++)
	{
		TEST(testurl8.path[I] == testurl9.path[I]);
	}
	TEST(testurl8.GetPathLength() == testurl9.GetPathLength());
	TEST(testurl8.GetPath()[1] == testurl9.GetPath()[1]);
	//test assignment operator
	URL testurl0 = testurl8;
	TEST(testurl0.GetScheme() == testurl8.GetScheme());
	TEST(testurl0.GetNet_Loc() == testurl8.GetNet_Loc());
	TEST(testurl0.GetResolvedURL() == testurl8.GetResolvedURL());
	TEST(testurl0.GetRelativeURL() == testurl8.GetRelativeURL());
	TEST(testurl0.GetBaseURL() == testurl8.GetBaseURL());
	for(int I=0; I<testurl8.GetPathLength(); I++)
	{
		TEST(testurl0.path[I] == testurl8.path[I]);
	}
	TEST(testurl0.GetPathLength() == testurl8.GetPathLength());
	TEST(testurl0.GetPath()[1] == testurl8.GetPath()[1]);
	//change the original one to make sure it doesn't change the one copied. 
	testurl8.scheme = "BOGUS";
	testurl8.net_loc = "BOGUS";
	for(int I=0; I<testurl8.GetPathLength(); I++)
	{
		testurl8.path[I] = "BOGUS";
	}
	testurl8.PathLength--;
	testurl8.RelativeURL = "BOGUS";
	testurl8.BaseURL = "BOGUS";
	testurl8.ResolvedURL = "BOGUS";
	TEST(testurl0.GetScheme() != testurl8.GetScheme());
	TEST(testurl0.GetNet_Loc() != testurl8.GetNet_Loc());
	TEST(testurl0.GetResolvedURL() != testurl8.GetResolvedURL());
	TEST(testurl0.GetRelativeURL() != testurl8.GetRelativeURL());
	TEST(testurl0.GetBaseURL() != testurl8.GetBaseURL());
	for(int I=0; I<testurl8.GetPathLength(); I++)
	{
		TEST(testurl0.path[I] != testurl8.path[I]);
	}
	TEST(testurl0.GetPathLength() != testurl8.GetPathLength());
	TEST(testurl0.GetPath()[1] != testurl8.GetPath()[1]);
	return success;
}
bool URL::TestAdvanced(ostream & os) 
{

	bool success = true;
     
	//test that fragments and queries are properly stripped
	URL testurl10("http://www.melyssa.com/index.html?test=woot","./page.html");
	TEST(testurl10.GetResolvedURL()=="http://www.melyssa.com/page.html?test=woot");

	URL testurl11("http://www.melyssa.com/index.html?test=woot#awesome","page.html");
	TEST(testurl11.GetResolvedURL()=="http://www.melyssa.com/page.html?test=woot");

	URL testurl12("http://www.melyssa.com/index.html","page.html?word=hello");
	TEST(testurl12.query == "?word=hello");
	TEST(testurl12.GetResolvedURL()=="http://www.melyssa.com/page.html?word=hello");
	TEST(testurl12.GetResolvedURLWithoutQuery() =="http://www.melyssa.com/page.html");

	//test that if a path is > 100 elements long, the path array will expand accordingly

	char reallyLongURL[1000];
	char reallyLongAnswer[1000];

	strcpy(reallyLongURL,"http://hi.com");
	for(int I=0; I<150; I++)
	{
		strcat(reallyLongURL,"/a");
	}

	strcpy(reallyLongAnswer, reallyLongURL);
	strcat(reallyLongAnswer, "/index.html");
	strcat(reallyLongURL, "/a.html");
	

	string reallyLongStringURL = string(reallyLongURL);
	string reallyLongStringAnswer = string(reallyLongAnswer);

	URL testurl13(reallyLongURL, "index.html"); 
    TEST(testurl13.GetResolvedURL() == reallyLongStringAnswer);
	TEST(testurl13.GetPathLength() == 151);

	
	return success;

}
