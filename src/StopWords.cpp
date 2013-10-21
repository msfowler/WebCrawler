#include "StopWords.h"
#include "FileSystem.h"
#include "FileInputStream.h"
#include "CS240Exception.h"
#include "StringUtil.h"
#include "UnitTest.h"



StopWords::StopWords()
{
	stop_words = NULL;
}

StopWords::StopWords(const StopWords & other)
{
	Copy(other);
}
	
StopWords & StopWords::operator=(const StopWords & other)
{
	if(&other != this)
	{
		Free();
		Copy(other);
	}
	
	return *this;
}

StopWords::~StopWords()
{
	Free();
}

void StopWords::Free()
{
	if(stop_words != NULL)
	{
		delete [] stop_words;
	}
}

void StopWords::Copy(const StopWords & other)
{
	throw CS240Exception("StopWords copy should never be called!");
}

bool StopWords::LoadFile(const string & fileName)
{
	if(FileSystem::FileExists(fileName) == false)
	{
		return false; 
	}	

	//count number of words in the file
	ifstream infileCount(fileName.c_str());
	char temp[1000];
	
	count = 0;	

	infileCount.getline(temp, 1000);
	while( !infileCount.eof())
	{
		if(strcmp(temp, "\0" ) != 0) //skip blank lines
		{
			count++;
		}
		infileCount.getline(temp, 1000);
	}
	
	infileCount.close();
	
	
	// initialize the array
	stop_words = new string[count];

	char tempRead[1000]; 
	int I=0;

	

	//read in the entire file 	
	ifstream readStream(fileName.c_str());
	readStream.getline(tempRead, 1000);
	
	while(!readStream.eof())
	{
		if(strcmp(tempRead, "\0") != 0)
		{
		    stop_words[I] = tempRead;
		    StringUtil::ToLower(stop_words[I]);
		    I++;
		}
	     readStream.getline(tempRead, 1000);
	}
	readStream.close();
	
	return true;
}




bool StopWords::contains(string & word)
{
	int lowIndex = 0;
	int highIndex = count - 1;
	int midIndex = 0;
	StringUtil::ToLower(word);

	while(lowIndex <= highIndex)
	{

		midIndex = (lowIndex + highIndex)/2; 
		if(stop_words[midIndex].compare(word) == 0) //found a match!
		{
			return true;
		}
		else if(stop_words[midIndex].compare(word) < 0)
		{
			lowIndex = midIndex + 1;
		}
		else 
		{	
			highIndex = midIndex - 1;
		}

	}

	return false;
}

bool StopWords::Test(ostream & os) 
{
	bool success = true;

	//test constructor/destructor
	StopWords * test0 = new StopWords();
	delete test0;

	StopWords test1; 

	test1.LoadFile("/users/guest/m/melyssas/cs240/WebCrawler/test/stopword1.txt");
	TEST(test1.count == 104); 
	
	//Test some words to make sure they are correct.
	TEST(test1.stop_words[3].compare("also") == 0);
	TEST(test1.stop_words[94].compare("wentworth") == 0);
	TEST(test1.stop_words[103].compare("z") == 0);
	TEST(test1.stop_words[0].compare("a") == 0);

	string s0("got");
	string s1("thisisabogusword");
	string s2("a");
	string s3("z");
	string s4("into");
	//Now test the actual contains method
	TEST(test1.contains(s0) == true);
	TEST(test1.contains(s1) == false);
	TEST(test1.contains(s2) == true);
	TEST(test1.contains(s3) == true);
	TEST(test1.contains(s4) == true); //exactly middle word

	string s5("123");
	string s6("too");
	string s7("THEIR");
	//test different cases (UPPER vs. lower)
	TEST(test1.contains(s5) == false);
	TEST(test1.contains(s6) == true);
	TEST(test1.contains(s7) == true);

	//Test a file with blank lines
	StopWords test2;

	test2.LoadFile("/users/guest/m/melyssas/cs240/WebCrawler/test/stopwordBlank.txt");
	TEST(test2.count == 104);
	return success;
}
