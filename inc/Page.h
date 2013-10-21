#ifndef PAGE_H
#define PAGE_H

#include <string>
#include "URL.h"

using namespace std;

/*
 * Page is a class that defines the Page Object. Page Objects hold the description of a page, and 
 * the URL of the page.
 *
 */

class Page {

private:
    string description;
    URL page_URL;

	void Copy(const Page & other); 

public:

    /*
     * No-arg constructor
     */
    Page();

    /*
     * Constructor, creates a new page object
     *
     * Parameters: 
     * desc - contains the description
     * url - contains the URL
     * 
     */
     
    Page(const string & desc, const URL & url);

	/*
	 * Copy Constructor
	 */
	Page(const Page & other);

	// = operator
	Page & operator=(const Page & other); 
    
    /* 
     * Destructor
     */
     
    ~Page();
    
    /* 
     * GetDescription, returns the description
     * 
     */
     
     string GetDescription() const;
     
    /* 
     * GetURL, returns the URL
     * 
     */
     
     const URL & GetURL() const;
	
	/*
	 *	SetURL, Sets the URL
	 */
	void SetURL(const URL & url);
	
	/*
	 * SetDescription, Sets the Description
	 */
	
	void SetDescription(const string & desc);
	
	// Compares v to see if it is equal to this object. 
	int compare(Page * v) const;

	//Unit Tests
	static bool Test(ostream & os);

};

#endif
