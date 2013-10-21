#ifndef KEYWORD_INDEX_H
#define KEYWORD_INDEX_H

#include <string>
#include "KeywordPairBST.h"
#include "Page.h"


using namespace std;

/*
 * The Keyword Index keeps a BST with KeywordPair objects that keeps track of all the keywords 
 * found and a set of occurences on which they are found
 */
 

class KeywordIndex {

private:
	KeywordPairBST * Index; 

	int traverseTree(KeywordPair * allWords, KeywordPairBSTNode * currentNode, int idx);

public:
	
	/* 
	 * No-arg constructor
	 */
	 
	 KeywordIndex();

	//Destructor
	~KeywordIndex();
	 
	 //Adds a new word to the Index, if the word already exists, then it adds another occurance 
	 void add(string word, Page * page);

	 //returns the number of pairs in the index
	int getIndexSize();

	//returns an array containing the index, in no particular order
	KeywordPair * getIndex();
	
	static bool Test(ostream & os);
};
#endif