#include <iostream>
#include <fstream>
#include "WebCrawler.h"
#include "CS240Exception.h"
#include "FileSystem.h"

using namespace std;

bool checkArgCount(int argc);

int main(int argc, char* argv[])
{
	
	if(checkArgCount(argc)==false)	
		return 0;

	WebCrawler * wc = new WebCrawler();

	try
	{

		string outputFile = argv[argc-2];
		string stopwordFile = argv[argc-1];
		string startURL = argv[argc-3];

	

		if(!FileSystem::FileExists(stopwordFile))
		{
			cout << "ERROR: Selected Stopwords file does not exist" << endl;
			delete wc;
			return 0; 
		}

 		string output = wc->crawl(startURL, stopwordFile); 

		//output to file
		ofstream outputFileStream;
		outputFileStream.open(outputFile.c_str());
		if(outputFileStream.is_open())
		{
			outputFileStream << output;
			outputFileStream.close();
		}
		else
		{
			cout << "ERROR: could not open output file" << endl;
		}
		
	} 
	catch(CS240Exception &e)
	{
		cout << "ERROR: " << e.GetMessage() << endl;
		delete wc;
		return 0;
	}
	catch(std::exception &e)
	{
		cout << "ERROR: " << e.what() << endl;
		delete wc;
		return 0;
	}
	catch(...)
	{
		cout << "ERROR: Unknown" << endl;
		delete wc;
		return 0;
	}

	cout << "DONE" << endl;
 
	delete wc;
  	return 0;
}

bool checkArgCount(int argc)
{
	if(argc != 4)
	{	
	 	cout << "USAGE: crawler <start-url> <output-file> <stopword-file>" << endl;
		return false;
  	}
	return true;
}
