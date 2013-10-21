#include "KeywordPair.h"

KeywordPair::KeywordPair()
{
	occurrences = new OccurrenceSet();
}

KeywordPair::KeywordPair(const string keyword, const Occurrence & occur): word(keyword)
{
	
	occurrences = new OccurrenceSet();
	occurrences->AddOccurrence(occur);

}

KeywordPair::KeywordPair(const KeywordPair & other)
{
	Copy(other);
}

KeywordPair::~KeywordPair()
{
	Free();
}

KeywordPair & KeywordPair::operator=(const KeywordPair & other)
{
	if(&other != this)
	{
		Free();
		Copy(other);
	}

	return *this;
}

void KeywordPair::Copy(const KeywordPair & other)
{
	word = other.getKeyword();
	occurrences = new OccurrenceSet(*(other.getOccurrences()));

}

void KeywordPair::Free()
{
	delete occurrences;
}

const string & KeywordPair::getKeyword() const
{
	return word;
}

OccurrenceSet * KeywordPair::getOccurrences() const
{
	return occurrences;
}

void KeywordPair::addOccurrence(const Occurrence & occur)
{
	occurrences->AddOccurrence(occur);
}

