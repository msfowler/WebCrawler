#include "XMLPrinter.h"
#include "StringUtil.h"
#include "KeywordIndex.h"
#include "Occurrence.h"
#include "OccurrenceSet.h"
#include "StopWords.h"
#include "CS240Exception.h"

XMLPrinter::XMLPrinter()
{
	stopwords = new StopWords();
}

XMLPrinter::~XMLPrinter()
{
	delete stopwords;
}

string XMLPrinter::print(KeywordIndex * index, string stopWordsFile, PageHistory * history)
{

	if(stopwords->LoadFile(stopWordsFile) == false)
	{
		CS240Exception e("Stopwords File does not exist");
		throw e;
	}
	string returnString;
	string startURL = history->GetStartPage()->GetURL().GetResolvedURL();
	
	//Add Beginning Stuff
	returnString = "<website>\n\t<start-url>";
	StringUtil::EncodeToXml(startURL);
	returnString += startURL;
	returnString += "</start-url>";
	

	addPages(history, returnString);
	addWords(index, returnString);
	
	//Add Ending Stuff
	returnString +="\n</website>";

	return returnString;

}

void XMLPrinter::addPages(PageHistory * history,string & returnString)
{
	int historySize = history->getHistorySize();
	Page ** allPages = history->getHistory();
	
	returnString+="\n\t<pages>";
	
	for(int I=0; I<historySize; I++)
	{
		returnString+="\n\t\t<page>";
		returnString+="\n\t\t\t<url>";

		string tempURL = allPages[I]->GetURL().GetResolvedURL();
		StringUtil::EncodeToXml(tempURL);

		returnString+=tempURL;
		returnString+="</url>";
		returnString+="\n\t\t\t<description>";

		string tempDescription = allPages[I]->GetDescription();
		StringUtil::EncodeToXml(tempDescription);

		returnString+=tempDescription;
		returnString+="</description>";
		returnString+="\n\t\t</page>";
	}

	returnString+="\n\t</pages>";
	delete [] allPages;
}

void XMLPrinter::addWords(KeywordIndex * index, string & returnString)
{
	int indexSize = index->getIndexSize();
	KeywordPair * allWords = index->getIndex();
	
	returnString+="\n\t<index>";
	
	for(int I=0; I<indexSize; I++)
	{
		string keyword(allWords[I].getKeyword());
		if(!stopwords->contains(keyword))
		{
			returnString+="\n\t\t<word>";
			returnString+="\n\t\t\t<value>";
			string tempWord = keyword;
			StringUtil::EncodeToXml(tempWord);
			returnString+= tempWord;
			returnString+="</value>";
			addOccurrences(allWords[I],returnString); 
			returnString+="\n\t\t</word>";
		}
	}
	
	returnString+="\n\t</index>";
	delete [] allWords;
}

void XMLPrinter::addOccurrences(KeywordPair & pair, string & returnString)
{
	int numberOfOccurrences = pair.getOccurrences()->GetNumberOfOccurrences();
	Occurrence * allOccurrences = pair.getOccurrences()->GetOccurrences();
	
	for(int I=0; I<numberOfOccurrences; I++)
	{
		returnString+="\n\t\t\t\t<occurrence>";
		returnString+="\n\t\t\t\t\t<url>";
		string tempURL = allOccurrences[I].GetPage()->GetURL().GetResolvedURL();
		StringUtil::EncodeToXml(tempURL);
		returnString+=tempURL;
		returnString+="</url>";
		returnString+="\n\t\t\t\t\t<count>";
		int c = allOccurrences[I].GetCount();
		char tempCount[100];
		sprintf(tempCount, "%d", c);
		returnString+= tempCount;
		returnString+="</count>";
		returnString+="\n\t\t\t\t</occurrence>";
											  
	}
	delete [] allOccurrences; 
}
