#include "IndexCard.h"
#include "WordCardBinder.h"
#include <string.h>
#pragma warning (disable : 4996)

void IndexCard_Create(IndexCard *indexCard, Long capacity) {

	Array_Create(&indexCard->wordCards, capacity, sizeof(WordCard*));
	indexCard->alphabat = ' ';
	indexCard->capacity = capacity;
	indexCard->length = 0;
}

Long IndexCard_TakeIn(IndexCard *indexCard, WordCard *wordCardIndex) {

	Long index;

	if (indexCard->length < indexCard->capacity) {
		index = Store(&indexCard->wordCards, indexCard->length, &wordCardIndex, sizeof(WordCard*));
	}
	else {
		
		index = AppendFromRear(&indexCard->wordCards, &wordCardIndex, sizeof(WordCard*));
		indexCard->capacity++;
	}
	indexCard->length++;

	return index;
}

Long IndexCard_Find(IndexCard* indexCard, WordCard *wordCardIndex) {

	Long index;

	index = Array_LinearSearchUnique(&indexCard->wordCards, wordCardIndex,
		sizeof(WordCard*), CompareWordCardIndex);

	return index;
}

Long IndexCard_TakeOut(IndexCard* indexCard, Long index) {

	index = Array_Delete(&indexCard->wordCards, index, sizeof(WordCard*));
	indexCard->capacity--;
	indexCard->length--;

	return index;
}

void IndexCard_Arrange(IndexCard* indexCard) {

	SelectionSort(&indexCard->wordCards, sizeof(WordCard*), IndexCard_CompareSpellings);
}


WordCard *IndexCard_GetAt(IndexCard* indexCard, Long index) {

	WordCard *wordCardIndex;
	
	Array_GetAt(&indexCard->wordCards, index, &wordCardIndex, sizeof(WordCard*));

	return wordCardIndex;
}


void IndexCard_Destroy(IndexCard* indexCard) {

	Array_Destroy(&indexCard->wordCards);
}

//추가
Long FindByWordCardMembers(IndexCard *indexCard, char(*spelling), char(*wordClass)) {

	WordCard wordCard;
	Long index;
	
	strcpy(wordCard.word.spelling, spelling);
	strcpy(wordCard.word.wordClass, wordClass);

	index = Array_LinearSearchUnique(&indexCard->wordCards, &wordCard,
		sizeof(WordCard*), IndexCard_CompareWordCardMembers);

	return index;
}

//추가
Long IndexCard_FindBySpellings(IndexCard *indexCard, char(*spelling)) {

	WordCard wordCard;
	Long index;

	strcpy(wordCard.word.spelling, spelling);
	index = Array_LinearSearchUnique(&indexCard->wordCards, &wordCard,
		sizeof(WordCard*), IndexCard_CompareWordCardSpellings);

	return index;
}


int CompareWordCardIndex(void *one, void *other) {
	
	int ret;
	WordCard **one_ = (WordCard**)one;

	if (*one_ == other) {
		ret = 0;
	}
	else {
		ret = -1;
	}
	return ret;
}

int IndexCard_CompareSpellings(void *one, void *other) {

	WordCard **one_ = (WordCard**)one;
	WordCard **other_ = (WordCard**)other;

	return strcmp((*one_)->word.spelling, (*other_)->word.spelling);
}

//추가
int IndexCard_CompareWordCardMembers(void *one, void *other) {

	WordCard **one_ = (WordCard**)one;
	WordCard *other_ = (WordCard*)other;
	int ret;

	if (strcmp((*one_)->word.spelling, other_->word.spelling) == 0 &&
		strcmp((*one_)->word.wordClass, other_->word.wordClass)==0) {
		
		ret = 0;
	}
	else {
		ret = -1;
	}
	
	return ret;
}

//추가
int IndexCard_CompareWordCardSpellings(void *one, void *other) {

	WordCard **one_ = (WordCard**)one;
	WordCard *other_ = (WordCard*)other;
	
	return strcmp((*one_)->word.spelling, other_->word.spelling);
}

