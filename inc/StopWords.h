#ifndef STOP_WORDS_H
#define STOP_WORDS_H

#include <string>
#include <iostream>
#include <string.h>
#include <fstream>
#include <stdlib.h>
#include <cstdlib>



using namespace std;

/*
 * StopWords keeps track of the list of common words that do not need to be indexed. These words
 * are loaded into an array from a file (the file must be alphabatized). 
 *
 */

class StopWords {

private:
    // array of stop words
    string * stop_words; //Array of strings
	int count; //number of stop words.

	void Copy(const StopWords & other);
	void Free(); 

public:
    /*
     * No-arg constructor  
     */
    StopWords();

	//Copy Constructor
	StopWords(const StopWords & other);
	
	//Assignment Operator
	StopWords & operator=(const StopWords & other);

	//Destructor
	~StopWords();


    /*
     * Loads the stop words from the specified file into the array
     *
     * Parameters:
     * filename - Name of the stop words file to be loaded
     *
     * Returns:
     * true If the file was successfully loaded, false
     * if the file could not be loaded or was invalid
	 *
     */
    bool LoadFile(const string & fileName);

    /*
     * Checks if the word is a stop word.
     *
     * Parameters:
     * word - the word to be checked
     *
     * Returns:
     * A boolean, True if a stop word, else false
     *
     */
   	bool contains(string & word);
	
	//Unit Test
	static bool Test(ostream & os);
};

#endif
