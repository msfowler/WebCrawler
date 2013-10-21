#ifndef WORD_PARSER_H
#define WORD_PARSER_H

#include <string>



using namespace std;

/*
 * The WordParser class takes strings and breaks them into words. It  can also 
*  say if a given strign is a valid word. 
 *
 */

class WordParser {

private:



public:
	
	/* 
	 * No-arg constructor
	 */
	 
	 WordParser();
	
	//Destructor
	~WordParser();	 
	 
	 //parseWords: returns an array of strings (pointer points to array on the heap) containing 
	 // the  words found in the parameter string s, the words are returned with all their 
	 // characters lower cased
	string * ParseWords(string & s);

	//Returns the number of words in a string
	int CountWords(string & s);

	//stringIsWord: returns TRUE/FALSE if string s is a valid word
	bool stringIsWord(string & s);

	bool isWordChar(char * c);

	static bool TestCount(ostream & os);
	static bool TestParse(ostream & os);
	  
};

#endif
