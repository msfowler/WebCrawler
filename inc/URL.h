#ifndef URL_H
#define URL_H

#include <string>
#include <ostream>

using namespace std;

/*
 * URL stores URLs and can be used to resolve URLs, and parse them into their components. 
 *
 */

class URL {

private:
    //all the componenets of a URL:
    string scheme;
    string net_loc;
	string query;
	string * path;
	int PathLength; 
	
	// The original URL is the relative URL given, the base URL is the site being crawled, and 
	// the Resolved URL is the absolute URL of teh URL
	string RelativeURL;
	string BaseURL;
	string ResolvedURL;
	string ResolvedURLWithoutQuery;
	
	//used by the constructor to resolve URLs
	void Resolve();
	
	//The following methods are used by the resolver method.
	void Parse(char * resolveBaseURL, char * resolveOriginalURL);
	void BuildURL(char * resolveRelativeURL);
	string stripQueriesAndFragments(string s);
	void expandPathArray();
	void expandResolvedURL();
	void addNet_LocIfNeeded();
	char * navigateToCorrectDirectory(char * resolveRelativeURL);

	void Free();
	void Copy(const URL & other);

public:
	//No Arg Constructor
	URL();


    /*
     * Constructor, makes a URL object, resolves it and parses it into its different parts. 
     *
     * base is the Base URL and url is the relative URL
     */
    URL(const string & base, const string & url);

	//Copy Constructor
	URL(const URL & other);

	//Assignment Operator
	URL & operator=(const URL & other);

	//Destructor
	~URL();

	//Unit Tests
	static bool TestBasic(ostream & os);
	static bool TestAdvanced(ostream & os);
	static bool TestCopying(ostream & os);

	//Accessor Methods
	string  GetScheme() const;
	string  GetNet_Loc() const;
	string * GetPath() const;
	int 	GetPathLength() const;

	string  GetRelativeURL() const;
	string  GetBaseURL() const;
	string  GetResolvedURL() const;
	string  GetResolvedURLWithoutQuery() const;
};

#endif
