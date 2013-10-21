#include "WordParser.h"
#include <ctype.h>
#include <iostream>
#include "string.h"
#include "UnitTest.h"
#include "StringUtil.h"

WordParser::WordParser()
{
	return;
}

WordParser::~WordParser()
{
	return;
}

string * WordParser::ParseWords(string & s)
{
	int count = CountWords(s);
	string * returnPtr = new string[count];

	if(count == 0)
		return returnPtr;

	char cstr[s.size()+1];
	strcpy(cstr, s.c_str());
	char * ptrBegin = cstr;
	char * ptrEnd   = cstr;
	char * ptrStop  = cstr + s.size();

	int idx = 0; 

	while(ptrEnd <= ptrStop)
	{
		if(isalpha(*ptrBegin) && (!isWordChar(ptrEnd) || ptrEnd == ptrStop))
		{
			size_t size = strlen(ptrBegin) - strlen(ptrEnd);
			returnPtr[idx] = string();	
			for(size_t I=0; I<size; I++)
			{
				returnPtr[idx] += (ptrBegin[I]);
			}
			
			StringUtil::ToLower(returnPtr[idx]);

			ptrBegin = ++ptrEnd;
			idx++;
		}
		else if(!isalpha(*ptrBegin) && (!isWordChar(ptrEnd) || ptrEnd == ptrStop))
		{
			ptrBegin = ++ptrEnd;
		}
		else 
		{
			ptrEnd++;
		}
	}

	return returnPtr;


}

int WordParser::CountWords(string & s)
{
	if(s.size() == 0)
		return 0;

	char cstr[s.size()+1];
	strcpy(cstr, s.c_str());
	char * ptrBegin = cstr;
	char * ptrEnd   = cstr;
	char * ptrStop  = cstr + s.size();

	int count = 0; 

	while(ptrEnd < ptrStop)
	{


		if(isalpha(*ptrBegin) && (!isWordChar(ptrEnd) || ptrEnd == (ptrStop-1)))
		{
			count++; 
			ptrBegin = ++ptrEnd;
		}
		else if(!isalpha(*ptrBegin) && (!isWordChar(ptrEnd) || ptrEnd == (ptrStop-1)))
		{
			ptrBegin = ++ptrEnd;
		}
		else 
		{
			ptrEnd++;
		}
	}

	return count;
}

bool WordParser::stringIsWord(string & s)
{
	if(s.size() == 0)
		return false;

	if(!isalpha(s[0]))
		return false; 

	for(unsigned I=0; I<s.size(); I++)
	{
		if(!isWordChar(&(s[I])))
		{
		    return false; 
		}
	}

	return true;

}

bool WordParser::isWordChar(char * c)
{
	return (isalnum(*c) || *c == '-' || *c == '_');
}


bool WordParser::TestCount(ostream & os)
{
	bool success = true;

	// test isWordChar
	WordParser test0;
	char badChars[5] = {'$',' ','\n','\0','~'};
	char goodChars[5] = {'a','A','_','-','1'};
	
	for(int I=0; I<5; I++)
	{
		TEST(test0.isWordChar(badChars+I) == false);
		TEST(test0.isWordChar(goodChars+I));
	}
	
	string s0("");	  
	string s1("this-is_one_big_w0rd");										
	string s2("two 2words e");				
	string s3("what's up? 3words");				
	string s4("I*\nhave@$\t\tfour(*&#words*(3decoy!&");
	string s5("This is an easy one 5words");  
	string s6("$*&$sixwords ar'e in this*str1ng!");

	TEST(test0.CountWords(s0) == 0);
	TEST(test0.CountWords(s1) == 1);	
	TEST(test0.CountWords(s2) == 2);
	TEST(test0.CountWords(s3) == 3);
	TEST(test0.CountWords(s4) == 4);
	TEST(test0.CountWords(s5) == 5);
	TEST(test0.CountWords(s6) == 6);

	return success;
}

bool WordParser::TestParse(ostream & os)
{
	bool success = true;

	WordParser test0;

	string s0("");	  
	string s1("this-is_one_big_w0rd");										
	string s2("two 2words e");				
	string s3("what's up? 3words");				
	string s4("I*\nhave@$\t\tfour(*&#words*(3decoy!&");
	string s5("This is an easy one 5words");  
	string s6("$*&$sixwords ar'e in this*str1ng!");

	string * arr1 = test0.ParseWords(s1);
	TEST(arr1[0] == "this-is_one_big_w0rd");

	string *arr2 = test0.ParseWords(s2);
	TEST(arr2[0] == "two");
	TEST(arr2[1] == "e");
	
	string *arr3 = test0.ParseWords(s3);
	TEST(arr3[0] == "what");
	TEST(arr3[1] == "s");
	TEST(arr3[2] == "up");	

	string *arr4 = test0.ParseWords(s4);
	TEST(arr4[0] == "i");
	TEST(arr4[1] == "have");
	TEST(arr4[2] == "four");
	TEST(arr4[3] == "words");

	string *arr5 = test0.ParseWords(s5);
	TEST(arr5[0] == "this");
	TEST(arr5[1] == "is");
	TEST(arr5[2] == "an");
	TEST(arr5[3] == "easy");
	TEST(arr5[4] == "one");

	string *arr6 = test0.ParseWords(s6);
	TEST(arr6[0] == "sixwords");
	TEST(arr6[1] == "ar");
	TEST(arr6[2] == "e");
	TEST(arr6[3] == "in");
	TEST(arr6[4] == "this");
	TEST(arr6[5] == "str1ng");

	delete [] arr1;
	delete [] arr2;
	delete [] arr3;
	delete [] arr4;
	delete [] arr5;
    delete [] arr6;

	return success;
}

