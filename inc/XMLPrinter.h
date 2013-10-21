#ifndef XML_PRINTER_H
#define XML_PRINTER_H

#include <string>
#include "KeywordIndex.h"
#include "PageHistory.h"
#include "StopWords.h"

using namespace std;

/*
 * The XML Printer class takes a KeywordIndex and prints it in XML
 *
 */

class XMLPrinter{

private:

	void addPages(PageHistory * history,string & returnString);
	void addWords(KeywordIndex * index, string & returnString);
	void addOccurrences(KeywordPair & pair, string & returnString);
	StopWords * stopwords;
	

public:
	
	/* 
	 * No-arg constructor
	 */
	 
	 XMLPrinter();
	~XMLPrinter();
	 
	 //Format the Results in XML adn return a string
	 string print(KeywordIndex * index, string stopWordsFile, PageHistory * history);
	 
	 
	 
	
	  
};

#endif
