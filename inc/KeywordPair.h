    #ifndef KEYWORD_PAIR_H
#define KEYWORD_PAIR_H

#include <string>
#include "Occurrence.h"
#include "OccurrenceSet.h"


using namespace std;

/*
 * The Keyword Pair object is used to store key value pairs, 
 * with the key bing a word (string) 
 * and the value being a set of occurances
 *
 */

class KeywordPair {

private:
	string word;
	OccurrenceSet * occurrences;
	
	void Copy(const KeywordPair & other);
	void Free();

public:
	
	/* 
	 * No-arg constructor
	 */
	 
	KeywordPair();

	//Constructor, makes a new one with a word adn occurance
	KeywordPair(const string keyword, const Occurrence & occur);

	//Copy Constructor
	KeywordPair(const KeywordPair & other);

	//Assignment Operator
	KeywordPair & operator=(const KeywordPair & other);

	//Destructor
	~KeywordPair();
	
	//Returns Keyword
	const string & getKeyword() const;
	
	//returns occurance set
	OccurrenceSet * getOccurrences() const;
	
	//adds an occurance
	void addOccurrence(const Occurrence & occur);
};

#endif
