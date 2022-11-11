#ifndef _INDEXCARDBINDER_H
#define _INDEXCARDBINDER_H

#include "BinaryTree.h"

typedef signed long int Long;
typedef struct _wordCard WordCard;
typedef struct _indexCard IndexCard;

typedef struct _indexCardBinder {

	BinaryTree indexCards;
	Long length;
}IndexCardBinder;

void IndexCardBinder_Create(IndexCardBinder *indexCardBinder);
IndexCard *IndexCardBinder_TakeIn(IndexCardBinder *indexCardBinder,
	WordCard *wordCardIndex);
IndexCard *IndexCardBinder_Find(IndexCardBinder *indexCardBinder, char alphabat);
IndexCard *IndexCardBinder_TakeOut(IndexCardBinder *indexCardBinder,
	WordCard *wordCardIndex, char alphabat);
void IndexCardBinder_MakeList(IndexCardBinder *indexCardBinder, IndexCard *(*indexCards),
	Long *count);
void IndexCardBinder_Arrange(IndexCardBinder *indexCardBinder);
void IndexCardBinder_Node_Arrange(BinaryNode *node);
void IndexCardBinder_Destroy(IndexCardBinder *indexCardBinder);
void IndexCardBinder_Node_Destroy(BinaryNode *node);

int CompareIndexCards(void *one, void *other);

#endif // !_INDEXCARDBINDER_H
