#ifndef WORDBOOK_H
#define WORDBOOK_H

#include "Array.h"
#include "Word.h"
#include <string>

using namespace std;

typedef signed long int Long;

class WordBook {

public:
	WordBook(Long capacity = 128);
	WordBook(const WordBook & source);
	~WordBook();

	Long Record(string spelling, string meaning, string wordClass, string exampleSentence);
	void FindBySpelling(string spelling, Long*(*indexes), Long *count);
	void FindByMeaning(string meaning, Long*(*indexes), Long *count);
	Long Correct(Long index, string meaning, string wordClass, string exampleSentence);
	Long Erase(Long index);
	void Arrange();
	Word & GetAt(Long index);

	WordBook & operator=(const WordBook & source);
	Word & operator[](Long index);
	Word * operator+(Long index);

	Long GetCapacity() const;
	Long GetLength() const;

	
private:
	Array<Word> words;
	Long capacity;
	Long length;
};

inline Long WordBook::GetCapacity() const{
	return this->capacity;
}

inline Long WordBook::GetLength() const {
	return this->length;
}

int CompareSpellings(void *one, void *other);
int CompareMeanings(void *one, void *other);
int CompareWords(void *one, void *other);

#endif // !WORDBOOK_H
