#include "KeywordIndex.h"
#include "Occurrence.h"
#include "OccurrenceSet.h"
#include <iostream>
#include "UnitTest.h"


KeywordIndex::KeywordIndex()
{
	Index = new KeywordPairBST();
}


KeywordIndex::~KeywordIndex()
{
	delete Index;
}
	 
void KeywordIndex::add(string word, Page * page)
{
	KeywordPairBSTNode * existingWord = Index->Find(word);
	Occurrence occr(page);

	if(existingWord == NULL)
	{
		
		KeywordPair kwp(word, occr);
		Index->Insert(kwp);
	}
	else
	{
		Index->Find(word)->addOccurrence(occr);
	}
}

int KeywordIndex::getIndexSize()
{
	return Index->GetSize();
}


KeywordPair * KeywordIndex::getIndex()
{
	//make an Array on the heap
	KeywordPair * allWords = new KeywordPair[Index->GetSize()];

	//recursively traverse tree adding to array
	int idx = 0;
	if(Index->GetRoot() != NULL)
	{
		traverseTree(allWords, Index->GetRoot(), idx);
	}

	return allWords;

}

int KeywordIndex::traverseTree(KeywordPair * allWords, KeywordPairBSTNode * currentNode, int idx)
{
	if(currentNode != NULL)
	{
		allWords[idx]  = currentNode->GetValue();
		idx++;
	}

	if(currentNode->GetLeft() != NULL)
	{
		idx = traverseTree(allWords, currentNode->GetLeft(), idx);
	}
	
	if(currentNode->GetRight() != NULL)
	{
		idx = traverseTree(allWords, currentNode->GetRight(), idx);
	}
	
	return idx; 

}

bool KeywordIndex::Test(ostream & os)
{
	bool success = true;

	KeywordIndex test0;
	TEST(test0.getIndexSize() == 0 );

	//make some test pages and words
	string s0("This is a dummy Page");
	Page p0(s0, URL("www.bogus.com",""));
	Page p1(s0, URL("www.slashdot.org",""));
	Page p2(s0, URL("www.amazon.com",""));

	//try adding the same word from the same page twice 
	test0.add(string("lion"), &p0);
	TEST(test0.getIndexSize() == 1);
	test0.add(string("lion"), &p0);
	TEST(test0.getIndexSize() == 1);

	//now add the same word to another page 
	test0.add(string("lion"), &p1);
	TEST(test0.getIndexSize() == 1);

	//add a different word to both pages
	test0.add(string("elephant"), &p0);
	test0.add(string("elephant"), &p1);
	TEST(test0.getIndexSize() == 2);

	//add some more words
	for(int I=0; I<6; I++)
		test0.add(string("tiger"), &p2);

	test0.add(string("elephant"), &p1);
	test0.add(string("elephant"), &p0);

	//now there should be three words in the index.
	// - lion should have 2 occurrences (count 2 on p0 and count 1 on p1)
	// - elephant should have 2 occurrences (count 2 on p0 and count 2 on p1)
	// - tiger should have 1 occurrence (count 6 on p2); 

	KeywordPair * index0 = test0.getIndex();
	
	TEST(index0[0].getKeyword() == "lion");
	OccurrenceSet * occSet0 = index0[0].getOccurrences();
	TEST(occSet0->GetNumberOfOccurrences() == 2);
	Occurrence * occ0 = occSet0->GetOccurrences();
	TEST(occ0[0].GetPage()->compare(&p0)== 0);
	TEST(occ0[1].GetPage()->compare(&p1)==0);
	TEST(occ0[0].GetCount() == 2);
	TEST(occ0[1].GetCount() == 1);

	TEST(index0[1].getKeyword() == "elephant");
	OccurrenceSet * occSet1 = index0[1].getOccurrences();
	TEST(occSet1->GetNumberOfOccurrences() == 2);
	Occurrence * occ1 = occSet1->GetOccurrences();
	TEST(occ1[0].GetPage()->compare(&p0)== 0);
	TEST(occ1[1].GetPage()->compare(&p1)==0);
	TEST(occ1[0].GetCount() == 2);
	TEST(occ1[1].GetCount() == 2);

	TEST(index0[2].getKeyword() == "tiger");
	OccurrenceSet * occSet2 = index0[2].getOccurrences();
	TEST(occSet2->GetNumberOfOccurrences() == 1);
	Occurrence * occ2 = occSet2->GetOccurrences();
	TEST(occ2[0].GetPage()->compare(&p2)== 0);
	TEST(occ2[0].GetCount() == 6);

	delete [] index0;
	delete [] occ0;
	delete [] occ1;
	delete [] occ2;	

	return success;
}
