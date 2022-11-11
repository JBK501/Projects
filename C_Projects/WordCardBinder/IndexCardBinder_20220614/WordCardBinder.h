#ifndef _WORDCARDBINDER_H
#define _WORDCARDBINDER_H

#include "LinkedList.h"

typedef signed long int Long;

typedef struct _word {

	char spelling[32];
	char meaning[128];
	char wordClass[16];
	char exampleSentence[256];
}Word;

typedef struct _wordCard {
	
	Word word;
	Long tryCount;
	Long successfulCount;
}WordCard;

typedef struct _wordCardBinder {

	LinkedList wordCards;
	Long length;
	WordCard *current;
}WordCardBinder;

void WordCardBinder_Create(WordCardBinder *wordCardBinder);
Long Load(WordCardBinder *wordCardBinder);
WordCard *TakeIn(WordCardBinder *wordCardBinder, WordCard wordCard);
void FindBySpelling(WordCardBinder *wordCardBinder, char(*spelling),
	WordCard* *(*indexes), Long *count);
void FindByMeaning(WordCardBinder *wordCardBinder, char(*meaning),
	WordCard* *(*indexes), Long *count);
WordCard TakeOut(WordCardBinder *wordCardBinder, WordCard *index);
//void Arrange(WordCardBinder *wordCardBinder);
WordCard *WordCardBinder_First(WordCardBinder *wordCardBinder);
WordCard *WordCardBinder_Previous(WordCardBinder *wordCardBinder);
WordCard *WordCardBinder_Next(WordCardBinder *wordCardBinder);
WordCard *WordCardBinder_Last(WordCardBinder *wordCardBinder);
WordCard *WordCardBinder_Move(WordCardBinder *wordCardBinder, WordCard *index);
Long Save(WordCardBinder *wordCardBinder);
void WordCardBinder_Destroy(WordCardBinder *wordCardBinder);

int CompareSpellings(void *one, void *other);
int CompareMeanings(void *one, void *other);
int CompareIndexes(void *one, void *other);

#endif // !_WORDCARDBINDER_H
