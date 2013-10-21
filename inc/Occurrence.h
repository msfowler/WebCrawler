#ifndef OCCURRENCE_H
#define OCCURRENCE_H

#include <string>
#include "Page.h"


using namespace std;

/*
 * An Occurrence Object contains a Page on which an occurrence is found,
 * and a count of how many times it has been found
 *
 */

class Occurrence {

private:
    // The page on which the occurrence appears (unique ID of the pair)
    Page * page;
	// teh number of occurrences
	int count; 
	
	void Copy(const Occurrence & other);


public:
    /*
     * No-arg constructor
     */
    Occurrence();
    
    /*
     * Constructor
     * 
     * Parameter: p: sets the page
     */
    Occurrence(Page * p);    
    
	//copy constructor
	Occurrence(const Occurrence & other);

	// = operator
	Occurrence & operator=(const Occurrence & other); 

	bool operator ==(const Occurrence & other) const;

    /*
     * Destructor
     */
     ~Occurrence();
    
    /*
     * Get Count, returns the number of occurrences
     */
     int GetCount() const;
     
     /* 
      * Increment Count: increments the count and returns the number of occurrences
      */
      int IncrementCount();

	//compares two occurrences (based on page)
	int compare(const Occurrence & v) const;

	//returns the page;
	Page * GetPage() const;

	//Unit tests
	static bool Test(ostream & os);
      
};

#endif
