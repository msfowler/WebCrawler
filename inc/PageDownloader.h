#ifndef PAGE_DOWNLOADER_H
#define PAGE_DOWNLOADER_H

#include <string>
#include "URL.h"



using namespace std;

/*
 * The Page Downloader downloads a page (using the utils)
 *
 */

class PageDownloader {

private:


public:

	//Download a page and return a string of its contents
	static string download(URL & url);

	static bool Test(ostream & os);
};

#endif