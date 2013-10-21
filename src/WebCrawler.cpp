#include "WebCrawler.h"
#include "CS240Exception.h"


WebCrawler::WebCrawler()
{
	queue = new PageQueue();
	downloader = new PageDownloader();	
	history = new PageHistory();
	parser = new HTMLParser();
	index = new KeywordIndex();
	xmlPrinter = new XMLPrinter();
}

WebCrawler::~WebCrawler()
{
	delete queue; 
	delete index;
	delete xmlPrinter;
	delete downloader;
	delete parser;
	
	//delete all the page objects on the heap
	Page ** hist = history->getHistory();
	int size = history->getHistorySize();
	
	for(int I=0; I<size; I++)
	{
		delete hist[I];
	}
	
	delete [] hist;
	delete history;
}



string WebCrawler::crawl(string & webpage, string & stopWordsFile)
{


	
	URL startURL(webpage,"");
	
	string currentPageContents;
	
	try
	{
		currentPageContents = downloader->download(startURL); 
	}
	catch(CS240Exception &e)
	{
		string newString = e.GetMessage();
		newString += " Invalid Start URL";
		CS240Exception newE(newString);
		throw newE;
	}

	cout << "Crawling ... " << endl;
	string currentPageDescription = parser->findDescription(currentPageContents);
	
    currentPage = new Page(currentPageDescription, startURL);
				
	queue->AddPage(currentPage);
	history->AddPage(currentPage);


	while (queue->HasNext()) 
	{
		currentPage = queue->GetNext();
		URL currentURL(currentPage->GetURL());
		currentPageContents = downloader->download(currentURL);
		cout <<"  Crawling: "<<currentURL.GetResolvedURL() << endl;
		
		//Note: findLinks adds all the links in currentPageContents to the queue, if they 
		// are not already in the history. If a page is added to the queue, it is also
		// added to the history. 
		URL * newURLstoCrawl = parser->findLinks(currentPageContents,currentPage);
		int numOfURLs = parser->countLinks(currentPageContents);	

		processNewLinks(newURLstoCrawl, numOfURLs, startURL);
		
		delete [] newURLstoCrawl;		

		//Note: findWords, finds words and adds them to the index.
		parser->findWords(currentPageContents, index, currentPage);
		
		
	}
	
	//Note: the xmlPrinter will not print words that are in the stop word file.
	cout << "Generating Output File..." << endl;


	return xmlPrinter->print(index, stopWordsFile, history);


}


void WebCrawler::processNewLinks(URL * newURLstoCrawl,int numOfURLs, URL & startURL)
{

		for(int I=0; I<numOfURLs; I++)
		{
			bool addToQueue = true;
			URL * newURL = new URL(newURLstoCrawl[I]); 
			if(!validator->isValid(newURLstoCrawl[I]))
				addToQueue = false;

			if(!validator->isInScope(newURLstoCrawl[I],startURL))
				addToQueue = false;

			string newContents; 

			try
			{
				newContents = downloader->download(newURLstoCrawl[I]);
			}
			catch(CS240Exception &e)
			{
				//skip the bad URL 
				delete newURL;
				continue;
			}
	
			
			Page dummyPage= Page("",newURLstoCrawl[I]);
			if(history->CheckHistory(&dummyPage))
				addToQueue = false;

			if(addToQueue == true)
			{
				string newDesc = parser->findDescription(newContents);
				Page * realPage = new Page(newDesc, newURLstoCrawl[I]);
				history->AddPage(realPage);
				queue->AddPage(realPage);
			}
			delete newURL;
		}

}
