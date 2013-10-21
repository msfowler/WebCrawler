#include "OccurrenceSet.h"
#include "UnitTest.h"
#include "Page.h"
#include "URL.h"
#include <iostream>

OccurrenceSet::OccurrenceSet()
{
	occurrences = new OcrBST();
}

OccurrenceSet::OccurrenceSet(const Occurrence & occ)
{
	occurrences = new OcrBST; 
	AddOccurrence(occ);
	
}

OccurrenceSet::OccurrenceSet(const OccurrenceSet & other)
{
	Copy(other);
}

OccurrenceSet & OccurrenceSet::operator=(const OccurrenceSet & other)
{

	if(&other != this)
	{
		Free();
		Copy(other);
	}

	return *this;
}

OccurrenceSet::~OccurrenceSet()
{
	Free();
}

void OccurrenceSet::Copy(const OccurrenceSet & other)
{
	occurrences = new OcrBST(*(other.occurrences));
}

void OccurrenceSet::Free()
{
	delete occurrences;
}

int OccurrenceSet::GetNumberOfOccurrences()
{
	return occurrences->GetSize();
}

void OccurrenceSet::AddOccurrence(const Occurrence & newOccurrence)
{
	OcrBSTNode * temp = occurrences->Insert(newOccurrence);

	if(temp == NULL)
	{
		occurrences->Find(newOccurrence)->GetValue().IncrementCount(); 
	}

}

Occurrence * OccurrenceSet::GetOccurrences()
{

	//make an array on the heap 
	Occurrence * allOccurrences = new Occurrence[occurrences->GetSize()];
	
	//recursively traverse the tree adding to the array 
	
	int idx = 0; 
	if(occurrences->GetRoot() != NULL)
	{
		traverseTree(allOccurrences, occurrences->GetRoot(), idx);	
	}

	return allOccurrences;

}

int OccurrenceSet::traverseTree(Occurrence * allOccurrences, OcrBSTNode * currentNode, int idx)
{
	if(currentNode != NULL)
	{
		allOccurrences[idx]  = currentNode->GetValue();
		idx++;
	}

	if(currentNode->GetLeft() != NULL)
	{
		idx = traverseTree(allOccurrences, currentNode->GetLeft(), idx);
	}
	
	if(currentNode->GetRight() != NULL)
	{
		idx = traverseTree(allOccurrences, currentNode->GetRight(), idx);
	}
	
	return idx; 

}

bool OccurrenceSet::Test(ostream & os)
{
	bool success = true;

	OccurrenceSet test0;
	
	TEST(test0.GetNumberOfOccurrences() == 0);              

	URL url0("www.giraffesarecool.com","");
	string desc0("This is an awesome website");
	Page page0(desc0,url0);

	Occurrence occ0(&page0);

	test0.AddOccurrence(occ0);
	TEST(test0.GetNumberOfOccurrences() == 1);
	Occurrence * testArray1 = test0.GetOccurrences();
	TEST(testArray1[0].GetPage()->compare(&page0) == 0);
	delete [] testArray1;

	test0.AddOccurrence(occ0);
	TEST(test0.GetNumberOfOccurrences() == 1);
	Occurrence * testArray2 = test0.GetOccurrences();
	TEST(testArray2[0].GetCount() == 2);
	delete [] testArray2;


	test0.AddOccurrence(occ0);
	TEST(test0.GetNumberOfOccurrences() == 1);
	Occurrence * testArray3 = test0.GetOccurrences();
	TEST(testArray3[0].GetCount() == 3);
	delete [] testArray3;

	return success;
}

bool OccurrenceSet::TestAdvanced(ostream & os)
{
	bool success = true;
	OccurrenceSet test0;
	URL url0("www.giraffesarecool.com","");
	string desc0("This is an awesome website");
	Page page0(desc0,url0);

	Occurrence occ0(&page0);
	test0.AddOccurrence(occ0);
	//make a whole bunch of test occurrences
	
	Page page1(desc0,URL("http://www.1.com",""));
	Page page2(desc0,URL("http://www.2.com",""));
	Page page3(desc0,URL("http://www.3.com",""));
	Page page4(desc0,URL("http://www.4.com",""));
	Page page5(desc0,URL("http://www.5.com",""));
	Page page10(desc0,URL("http://www.10.com",""));
	Page page11(desc0,URL("http://www.11.com",""));
	Page page12(desc0,URL("http://www.12.com",""));

	Occurrence occ1(&page1);
	Occurrence occ2(&page2);
	Occurrence occ3(&page3);
	Occurrence occ4(&page4);
	Occurrence occ5(&page5);
	Occurrence occ10(&page10);
	Occurrence occ11(&page11);
	Occurrence occ12(&page12);
	
	test0.AddOccurrence(occ1);
	test0.AddOccurrence(occ2);
	test0.AddOccurrence(occ3);
	test0.AddOccurrence(occ4);
	test0.AddOccurrence(occ5);
	test0.AddOccurrence(occ10);

	Occurrence * testArray = test0.GetOccurrences();

	TEST(test0.GetNumberOfOccurrences() == 7);
	TEST(testArray[0].GetPage()->compare(&page0) == 0);
	TEST(testArray[1].GetPage()->compare(&page1) == 0);
	TEST(testArray[2].GetPage()->compare(&page2) == 0);
	TEST(testArray[3].GetPage()->compare(&page10) == 0);
	TEST(testArray[4].GetPage()->compare(&page3) == 0);
	TEST(testArray[5].GetPage()->compare(&page4) == 0);
	TEST(testArray[6].GetPage()->compare(&page5) == 0);

	//test copy constructor & = operator
	OccurrenceSet test1 = test0;

	TEST(test1.GetNumberOfOccurrences() == test0.GetNumberOfOccurrences());
	test0.AddOccurrence(occ11);
	TEST(test1.GetNumberOfOccurrences() == 7);

	OccurrenceSet test2(test0);
	TEST(test2.GetNumberOfOccurrences() == test0.GetNumberOfOccurrences());
	test0.AddOccurrence(occ12);
	TEST(test2.GetNumberOfOccurrences() == 8);

	delete [] testArray;
	return success;

}
