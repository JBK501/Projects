#ifndef _INDEXCARD_H
#define _INDEXCARD_H

#include "Array.h"

typedef signed long int Long;
typedef struct _wordCard WordCard;

typedef struct _indexCard {

	char alphabat;
	Array wordCards;
	Long length;
	Long capacity;
}IndexCard;

void IndexCard_Create(IndexCard *indexCard, Long capacity);
Long IndexCard_TakeIn(IndexCard *indexCard, WordCard *wordCardIndex);
Long IndexCard_Find(IndexCard* indexCard, WordCard *wordCardIndex);
Long IndexCard_TakeOut(IndexCard* indexCard, Long index);
void IndexCard_Arrange(IndexCard* indexCard);
WordCard *IndexCard_GetAt(IndexCard* indexCard, Long index);
void IndexCard_Destroy(IndexCard* indexCard);
Long FindByWordCardMembers(IndexCard *indexCard, char(*spelling), char(*wordClass)); //추가
Long IndexCard_FindBySpellings(IndexCard *indexCard, char(*spelling));//추가

int CompareWordCardIndex(void *one, void *other);
int IndexCard_CompareSpellings(void *one, void *other);
int IndexCard_CompareWordCardMembers(void *one, void *other); //추가
int IndexCard_CompareWordCardSpellings(void *one, void *other);

#endif // !_INDEXCARD_H
