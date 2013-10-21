#ifndef HTML_PARSER_H
#define HTMLPARSER_H

#include <string>
#include "KeywordIndex.h"
#include "PageQueue.h" 
#include "PageHistory.h"
#include "URL.h"
#include "Page.h"
#include "HTMLTokenizer.h"


using namespace std;

/*
 * The HTMLParser class finds links to new pages, finds words and finds descriptions
 *
 */

class HTMLParser {

private:

	bool isLink(HTMLToken tok);
	bool hasHREF(HTMLToken tok);
	bool shouldAddToQueue(PageHistory * history, Page * newPage);
	bool isNotInHistory(PageHistory * history, Page * newPage);
	bool isValid(const URL & url,const URL & baseurl);
	string findFirst100Chars(string & siteContent);
	static string GetTestPageContentsFromFile(string & fileName);
	static bool isEqualCaseInsensitive(string string0, string string1);
	static bool bodyOrTitle(string & tempValue);
	static bool isHeaderTag(HTMLToken temp);
	static bool checkIfInsideHTML(HTMLToken temp, bool currentValue);
	static bool checkIfInsideTitle(HTMLToken temp, bool currentValue);
	HTMLToken & collectDescriptionInTag(HTMLToken & temp, string & closeTag, 
										HTMLTokenizer * tokenizer, string * Description);
	

public:
	
	/* 
	 * No-arg constructor
	 */
	 
	 HTMLParser();
	 
	// find the links 
	URL * findLinks(string & siteContent, Page * basePage);
	
	//Finds all the words in the contents of a site (in a string) and a KeywordIndex pointer. It will
	//add the words to the index. 
	void findWords(string & siteContent, KeywordIndex * index, Page * page);
	
	//Generate a description, using the contents of a site and return it in a string
	string findDescription(string & siteContent);

	//counts the number of links on a page
	int countLinks(string & siteContent);

	//Unit Tests
	static bool TestDescription(ostream & os);
	static bool TestGetWords(ostream & os);
	static bool TestGetLinks(ostream & os);
	
	  
};

#endif
