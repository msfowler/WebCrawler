#ifndef HTML_VALIDATOR_H
#define HTML_VALIDATOR_H

#include <string>
#include "URL.h"


using namespace std;

/*
 * The HTMLValidator makes sure that a give URL is valid HTML to be crawled, and is in scope
 */

class HTMLValidator{

private:

	static bool checkValidExtensions(char * ext);
	static bool checkAdditionalValidExtensions(char * ext);

public: 
	 
	 //Returns YES/NO if it is valid page to be crawled
	static bool isValid(const URL & url);
	//Returns YES/NO if it is in scope 
	static bool isInScope(const URL & url,const URL & startURL); 

	static bool Test(ostream & os);
	  
};

#endif
