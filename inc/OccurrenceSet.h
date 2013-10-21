#ifndef OCCURRENCE_SET_H
#define OCCURRENCE_SET_H

#include <string>
#include "OcrBST.h"
#include "Occurrence.h"

using namespace std;

/*
 * The OccurrenceSet Class keeps a BST of all the Occurrences for a certain word.
 *
 */

class OccurrenceSet {

private:
	// the Occurrences
	OcrBST * occurrences; 

	
	//Used by AddOccurrence to see if an Occurrence is in teh set, returns true if exists

	void Copy(const OccurrenceSet & other);
	void Free();

	int traverseTree(Occurrence * allOccurrences, OcrBSTNode * currentNode, int idx);

public:
    /*
     * No-arg constructor
     */
    OccurrenceSet();
    
    /*
     * Constructor
     * 
     * Parameter: creates a new occurrence set with an occurrence
     */
    OccurrenceSet(const Occurrence & occ);    


	//copy constructor
	OccurrenceSet(const OccurrenceSet & other);

	//assignment Operator
	OccurrenceSet & operator=(const OccurrenceSet & other);
    
    /*
     * Destructor
     */
     ~OccurrenceSet();
    
    /*
     * GetNumberOfOccurrences, returns the number of Occurrences
     */
     int GetNumberOfOccurrences();
     
     /* 
      * AddOccurrence, adds a new Occurrence (or increments the count if the Occurrence exists
      */

     void AddOccurrence(const Occurrence & newOccurrence);      
      
	/*
	 * GetOccurrences, returns the Occurrences as an array of no particular order,
	 * note: the array is on the heap. If you call this, you are now the owner
	 * of that array and MUST CALL DELETE ON IT!
	 */

	Occurrence * GetOccurrences();

	//Unit Tests
	static bool Test(ostream & os);
	static bool TestAdvanced(ostream & os);

};

#endif