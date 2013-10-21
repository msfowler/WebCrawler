#include <iostream>
#include "URL.h"
#include "Page.h"
#include "Occurrence.h"
#include "OccurrenceSet.h"
#include "StopWords.h"
#include "WordParser.h"
#include "HTMLValidator.h"
#include "PageDownloader.h"
#include "PageQueue.h"
#include "PageHistory.h"
#include "KeywordIndex.h"
#include "HTMLParser.h"

using namespace std;

bool testBasicObjects(bool success);
bool testUtilities(bool success);
bool testDataStructures(bool success);
bool testMainAlgorithms(bool success);

int main()
{
	bool success = true;

	success = testBasicObjects(success);
	
	success = testUtilities(success);

	success = testDataStructures(success);
	
	success = testMainAlgorithms(success);

	if(success)
	{
		cout << "ALL TESTS PASSED!" <<endl;
	}
	else 
	{
		cout << "TESTS FAILED!" <<endl;
	}

	return 0; 
}

bool testBasicObjects(bool success)
{

	cout << "Testing URL class" << endl;
	if(!URL::TestBasic(cout)) success = false;
	if(!URL::TestCopying(cout)) success = false;
	if(!URL::TestAdvanced(cout)) success = false;

	cout << "Testing Page Class" << endl;
	if(!Page::Test(cout)) success = false;

	cout << "Testing Occurrence Class" << endl;
	if(!Occurrence::Test(cout)) success = false;
	
	return success;
}

bool testUtilities(bool success)
{
	cout << "Testing Stop Words" << endl;
	if(!StopWords::Test(cout)) success = false;

	cout << "Testing WordParser" << endl;
	if(!WordParser::TestCount(cout)) success = false; 
	if(!WordParser::TestParse(cout)) success = false;
	
	cout << "Testing HTMLValidator" <<endl;
	if(!HTMLValidator::Test(cout)) success = false;

	cout << "Testing PageDownloader" << endl;
	if(!PageDownloader::Test(cout)) success = false;

	return success;

}

bool testDataStructures(bool success)
{
	cout << "Testing OccurrenceSet Class" <<endl;
	if(!OccurrenceSet::Test(cout)) success = false;
	if(!OccurrenceSet::TestAdvanced(cout)) success = false;

	cout << "Testing PageQueue" << endl;
	if(!PageQueue::Test(cout)) success = false;

	cout << "Testing PageHistory" << endl;
	if(!PageHistory::Test(cout)) success = false;

	cout << "Testing KeywordIndex" << endl;
	if(!KeywordIndex::Test(cout)) success = false;

	return success;
}

bool testMainAlgorithms(bool success)
{
	cout << "Testing HTMLParser" << endl;
	if(!HTMLParser::TestDescription(cout)) success = false;
	if(!HTMLParser::TestGetWords(cout)) success = false;
	if(!HTMLParser::TestGetLinks(cout)) success = false;

	return success;
}
