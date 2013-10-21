#ifndef LINK_PROCESSOR_H
#define LINK_PROCESSOR_H

#include <string>
#include URL.h


using namespace std;

/*
 * The Link Processor Class checks if a link is in the scope of the page, and checks if it is 
 * html and should be indexed.
 */
 

class LinkProcessor {

private:
	URL site;  // The site being crawled

public:
	
	/* 
	 * No-arg constructor
	 */
	 
	 LinkProcessor();
	 
	 /*
	  * This construction initialized the URL. The URL is for the site being crawled
	  */
	 

	// This checks url agains site and sees if the url is in the scope of the site
	// and returns TRUE if it is in scope
	bool inScope(URL & url);
	
	//This checks if url is HTML and should be crawled, and returns TRUE if it should
	bool isHTML(URL & url);

#endif