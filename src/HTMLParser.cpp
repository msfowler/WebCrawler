#include "HTMLParser.h"
#include "HTMLTokenizer.h"
#include "HTMLValidator.h"
#include "WordParser.h"
#include "StringUtil.h"
#include <ctype.h>
#include <iostream>
#include <fstream>
#include "UnitTest.h"
#include "FileSystem.h"

HTMLParser::HTMLParser()
{
	return;
}


URL * HTMLParser::findLinks(string & siteContent, Page * basePage)
{
	HTMLTokenizer tokenizer(siteContent);

	bool insideHTML = false;
	bool insideScript = false;

	int size = countLinks(siteContent);		
	URL * allLinks = new URL[size];
	int idx = 0;	

	while (tokenizer.HasNextToken()==true)
	{
		HTMLToken temp = tokenizer.GetNextToken();
		string tempValue = temp.GetValue();
		string newURLstr;
		

		if(temp.GetType() == TAG_START && isEqualCaseInsensitive(tempValue,string("html")))
			insideHTML = true;
				

		if(temp.GetType() == TAG_END && isEqualCaseInsensitive(tempValue,string("html")))
			insideHTML = false;

		if(temp.GetType() == TAG_START && isEqualCaseInsensitive(tempValue,string("script")))
			insideScript = true;
				

		if(temp.GetType() == TAG_END && isEqualCaseInsensitive(tempValue,string("script")))
			insideScript = false;

		if(insideHTML && !insideScript && isLink(temp) && hasHREF(temp))
		{

			newURLstr = temp.GetAttribute("href");
			URL newURLObj;		
			
			if(StringUtil::IsPrefix(StringUtil::ToLowerCopy(newURLstr),"http://") ||
				StringUtil::IsPrefix(StringUtil::ToLowerCopy(newURLstr),"file://"))
			{
				newURLObj = URL(newURLstr,"");
			}
			else
			{
				newURLObj = URL(basePage->GetURL().GetResolvedURL(), newURLstr);
			}	
			
			allLinks[idx] = newURLObj;
			idx++;		
					
		}
	}
	
	return allLinks;

}


string HTMLParser::findDescription(string & siteContent)
{
	string Description; 
	bool headerTags = false;
	bool insideHTML = false; 
	bool insideTitle = false;
	HTMLTokenizer tokenizer(siteContent);

	while (tokenizer.HasNextToken()==true)
	{
		HTMLToken temp = tokenizer.GetNextToken();
		string tempValue = temp.GetValue();
		
		insideHTML = checkIfInsideHTML(temp, insideHTML);
		insideTitle = checkIfInsideTitle(temp, insideTitle); 

		//Rule 1: title tags always get first priority
		if(insideHTML && insideTitle)
		{
			if(temp.GetType() == TEXT && tempValue != "")
			{
				string titleDescription(tempValue);
				temp = tokenizer.GetNextToken();
				tempValue = temp.GetValue();
				string title("title");
				temp = this->collectDescriptionInTag(temp,title,&tokenizer, &titleDescription);
				tempValue = temp.GetValue();
				return titleDescription;
			}
			
		}
		
		//Rule 2: then Header tags
		if(insideHTML && !headerTags && isHeaderTag(temp))
		{
			string headerValue = temp.GetValue();
			Description = "";
			temp = this->collectDescriptionInTag(temp, headerValue, &tokenizer, &Description);
			tempValue = temp.GetValue();
			if(Description != "")
			{
				headerTags = true;
			}
		}
		
		
	}
	
	if(headerTags == true)
	{
		return Description;
	}
	else 
	{

		return findFirst100Chars(siteContent);

	}

}


void HTMLParser::findWords(string & siteContent, KeywordIndex * index, Page * page)
{

	bool shouldParse = false;
	bool canParseAgainAfterScript = false; 
	bool insideHTML = false;
	HTMLTokenizer tokenizer(siteContent);
	WordParser wordParser;
	
	
	while(tokenizer.HasNextToken())
	{
		HTMLToken token = tokenizer.GetNextToken();
		string tempValue = token.GetValue();

		insideHTML = checkIfInsideHTML(token, insideHTML);
		
		if(insideHTML && token.GetType() == TAG_START && bodyOrTitle(tempValue))
		{
			shouldParse = true; 
			canParseAgainAfterScript = true;
		}
		
		if(token.GetType() == TAG_START && isEqualCaseInsensitive(tempValue,string("script")))
		{ 
			shouldParse = false; 
		}
		
		if(insideHTML && token.GetType() == TAG_END && isEqualCaseInsensitive(tempValue,string("script")))
		{
			if(canParseAgainAfterScript)
				shouldParse = true; 
		}

		if(token.GetType() == TAG_END && bodyOrTitle(tempValue))
		{
			shouldParse = false; 
			canParseAgainAfterScript = false;
		}		

		if(token.GetType() == TEXT && shouldParse)
		{
			string tempText = token.GetValue();
			string * words = wordParser.ParseWords(tempText);
			int WordCount = wordParser.CountWords(tempText);
			
			for(int I=0; I<WordCount; I++)
			{
				index->add(words[I], page);
			}
			delete [] words;
		}
		
	}

}


bool HTMLParser::isLink(HTMLToken tok)
{
	return (tok.GetType() == TAG_START && isEqualCaseInsensitive(tok.GetValue(), string("a")));
}

HTMLToken & HTMLParser::collectDescriptionInTag(HTMLToken & temp, string & closeTag, 
												HTMLTokenizer * tokenizer, string * Description)
{
	string tempValue = temp.GetValue();

	while(!(temp.GetType() == TAG_END && isEqualCaseInsensitive(temp.GetValue(),closeTag)))
	{
		if(temp.GetType() == TEXT)
			(*Description) += tempValue;

			temp = tokenizer->GetNextToken();
			tempValue = temp.GetValue();
		}
	return temp;

}


bool HTMLParser::bodyOrTitle(string & tempValue)
{
	bool returnValue = (isEqualCaseInsensitive(tempValue,string("title")) 
						|| isEqualCaseInsensitive(tempValue,string("body")));
	return returnValue;
}

bool HTMLParser::hasHREF(HTMLToken tok)
{
	return (tok.AttributeExists("href")== true && tok.GetAttribute("href") != "");

}

bool HTMLParser::isHeaderTag(HTMLToken temp)
{
	string tempValue = temp.GetValue();

	return (temp.GetType() == TAG_START && tempValue.size() > 1 
		   && tolower(tempValue[0]) == 'h'
		   && isdigit(tempValue[1]));
}

bool HTMLParser::shouldAddToQueue(PageHistory * history, Page * newPage)
{

	
	return (isNotInHistory(history, newPage) 
			&& isValid(newPage->GetURL(),history->GetStartPage()->GetURL()));
}

bool HTMLParser::checkIfInsideHTML(HTMLToken temp, bool currentValue)
{
	bool insideHTML = currentValue; 
	string tempValue = temp.GetValue();
	if(!insideHTML && temp.GetType() == TAG_START 
		&& isEqualCaseInsensitive(tempValue,string("html")))
		insideHTML = true;
		
	if(insideHTML && temp.GetType() == TAG_END 
		&& isEqualCaseInsensitive(tempValue,string("html")))
		insideHTML = false;
	
	return insideHTML;

}

bool HTMLParser::checkIfInsideTitle(HTMLToken temp, bool currentValue)
{
	bool insideTitle = currentValue; 
	string tempValue = temp.GetValue();
	if(!insideTitle && temp.GetType() == TAG_START 
		&& isEqualCaseInsensitive(tempValue,string("title")))
		insideTitle = true;
		
	if(insideTitle && temp.GetType() == TAG_END 
		&& isEqualCaseInsensitive(tempValue,string("title")))
		insideTitle = false;
	
	return insideTitle;

}

bool HTMLParser::isNotInHistory(PageHistory * history, Page * newPage)
{
	return (history->CheckHistory(newPage)==false);
}

bool HTMLParser::isValid(const URL & url, const URL & baseurl)
{
	HTMLValidator validator;
	return (validator.isValid(url) && validator.isInScope(url, baseurl));
}

bool HTMLParser::isEqualCaseInsensitive(string string0, string string1)
{
	//TODO: could use the cs240 string utils here if you want
	string s0(string0);
	string s1(string1);
	
	for(unsigned I=0; I<s0.size(); I++)
		s0[I] = tolower(s0[I]);

	for(unsigned I=0; I<s1.size(); I++)
		s1[I] = tolower(s1[I]);

	return s0 == s1;
}
			
string HTMLParser::findFirst100Chars(string & siteContent)
{
	int charCount = 0; 
	bool insideBody = false;
	bool insideHTML = false;
	HTMLTokenizer tokenizer(siteContent);
	string Description("");
	
	while(tokenizer.HasNextToken() && charCount < 100)
	{
		HTMLToken tok = tokenizer.GetNextToken();
				
		if(!insideHTML && tok.GetType() == TAG_START && isEqualCaseInsensitive(tok.GetValue(),"html"))
		{
			insideHTML = true;
		}
		
		if(insideHTML && tok.GetType() == TAG_END && isEqualCaseInsensitive(tok.GetValue(),"html"))
		{
			insideHTML = false;
		}		


		if(!insideBody && tok.GetType() == TAG_START && isEqualCaseInsensitive(tok.GetValue(),"body"))
		{
			insideBody = true;
		}
		
		if(insideBody && tok.GetType() == TAG_END && isEqualCaseInsensitive(tok.GetValue(),"body"))
		{
			insideBody = false;
		}
		
		if(insideHTML && insideBody && tok.GetType() == TEXT)
		{
			string val = tok.GetValue();

			for(unsigned I=0; I < val.size(); I++)
			{
				if(charCount < 100)
				{

					Description += val[I];
				
					if(!isspace(val[I]))
					{
						charCount++;
					}
				}
			} 
		}
		
	}
	
	return Description; 	
}

int HTMLParser::countLinks(string & siteContent)
{
	HTMLTokenizer tokenizer(siteContent);

	bool insideHTML = false;
	bool insideScript = false;
	int count = 0;

	while (tokenizer.HasNextToken()==true)
	{
		HTMLToken temp = tokenizer.GetNextToken();
		string tempValue = temp.GetValue();
		string newURLstr;
		
		if(temp.GetType() == TAG_START && isEqualCaseInsensitive(tempValue,string("html")))
			insideHTML = true;
		
		if(temp.GetType() == TAG_END && isEqualCaseInsensitive(tempValue,string("html")))
			insideHTML = false;

		if(temp.GetType() == TAG_START && isEqualCaseInsensitive(tempValue,string("script")))
			insideScript = true;
		
		if(temp.GetType() == TAG_END && isEqualCaseInsensitive(tempValue,string("script")))
			insideScript = false;

		if(insideHTML && !insideScript && isLink(temp) && hasHREF(temp))
		{
			count ++;				
		}
	}
	return count;
}


bool HTMLParser::TestDescription(ostream & os)
{
	bool success = true;

	string f0("/users/guest/m/melyssas/cs240/WebCrawler/test/descTest0.html");	
	string f1("/users/guest/m/melyssas/cs240/WebCrawler/test/descTest1.html");
	string f2("/users/guest/m/melyssas/cs240/WebCrawler/test/descTest2.html");
	string f3("/users/guest/m/melyssas/cs240/WebCrawler/test/blank.html");
	string f0cont = GetTestPageContentsFromFile(f0);
	string f1cont = GetTestPageContentsFromFile(f1);
	string f2cont = GetTestPageContentsFromFile(f2);
	string f3cont = GetTestPageContentsFromFile(f3);
	
	HTMLParser test0;
	string d0 = test0.findDescription(f0cont);
	string d1 = test0.findDescription(f1cont);
	string d2 = test0.findDescription(f2cont);
	string d3 = test0.findDescription(f3cont);
	string longString = "The hard thing about testing the first hundred words is";
	longString +=  " that there's no way that we can fake you out. Maybe if we were to use";
	TEST(d0 == "A Description of an included page");
	TEST(d1 == "This is the description");
	TEST(d2 == longString);
	TEST(d3 == "");


	return success;
}

bool HTMLParser::TestGetWords(ostream & os)
{
	bool success = true;
	
	HTMLParser test0;
	URL u0("file:///users/guest/m/melyssas/cs240/WebCrawler/test/wordTest0.html","");
	Page p0("practice",u0);
	KeywordIndex * index0 = new KeywordIndex();
	string s0("/users/guest/m/melyssas/cs240/WebCrawler/test/wordTest0.html");
	string contents = GetTestPageContentsFromFile(s0);

	test0.findWords(contents,index0,&p0);
	KeywordPair * indexArr = index0->getIndex();
	
	for(int I=0; I < index0->getIndexSize(); I++)
	{
		Occurrence * occrSet = indexArr[I].getOccurrences()->GetOccurrences();
		delete [] occrSet;
	}
	
	delete [] indexArr;
	delete index0; 

	return success;
}

bool HTMLParser::TestGetLinks(ostream & os)
{
	bool success = true;
	
	HTMLParser test0;
	URL u0("file:///users/guest/m/melyssas/cs240/WebCrawler/test/linkTest0.html","");
	Page p0("practice",u0);
	string s0("/users/guest/m/melyssas/cs240/WebCrawler/test/linkTest0.html");
	string contents = GetTestPageContentsFromFile(s0);

	TEST(test0.countLinks(contents)== 12);
	URL * allLinks = test0.findLinks(contents,&p0);
	

	delete [] allLinks;

	return success;
}

string HTMLParser::GetTestPageContentsFromFile(string & fileName)
{
	string content;
	if(FileSystem::FileExists(fileName) == false)
	{
		return content; 
	}

	
	ifstream infileCount(fileName.c_str());
	char temp[1000];	

!	infileCount.getline(temp, 1000);
	content = temp;
	while( !infileCount.eof())
	{
		infileCount.getline(temp, 1000);
		content += temp;
	}
	
	infileCount.close();
	
	return content;

}


