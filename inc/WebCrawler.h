#ifndef WEB_CRAWLER_H
#define WEB_CRAWLER_H

#include <string>
#include "PageQueue.h"
#include "URL.h"
#include "PageHistory.h"
#include "PageDownloader.h"
#include "KeywordIndex.h"
#include "XMLPrinter.h"
#include "HTMLValidator.h"
#include "HTMLParser.h"
#include "URL.h"


using namespace std;

/*
 * Crawls a webpage (really just calls all the other classes)
 */
 

class WebCrawler {

private:
	PageQueue * queue;
	Page * currentPage;
	PageHistory * history;
	PageDownloader * downloader;
	HTMLParser * parser;
	HTMLValidator * validator;
	KeywordIndex * index; 
	XMLPrinter * xmlPrinter;
	
	void processNewLinks(URL * newURLstoCrawl,int numOfURLs, URL & startURL);

public:
	
	/* 
	 * No-arg constructor
	 */
	 
	 WebCrawler();
	 
	//Destructor
	~WebCrawler();	

	//crawls the webpage and returns a string with the final XML output
	string crawl(string & webpage, string & stopWordsFile);

};
#endif
