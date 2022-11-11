#include "IndexCardBinder.h"
#include "IndexCard.h"
#include "WordCardBinder.h"

void IndexCardBinder_Create(IndexCardBinder *indexCardBinder) {

	BinaryTree_Create(&indexCardBinder->indexCards);
	indexCardBinder->length = 0;
}

IndexCard *IndexCardBinder_TakeIn(IndexCardBinder *indexCardBinder,
	WordCard *wordCardIndex) {

	IndexCard *indexCardIndex;
	IndexCard indexCard;
	BinaryNode *node;

	indexCard.alphabat = wordCardIndex->word.spelling[0];

	node = Search(&indexCardBinder->indexCards, &indexCard, sizeof(IndexCard),
		CompareIndexCards);

	if (node == NULL) {

		IndexCard_Create(&indexCard, 50);
		
		indexCard.alphabat = wordCardIndex->word.spelling[0];

		node = BinaryTree_Insert(&indexCardBinder->indexCards, &indexCard,
			sizeof(IndexCard), CompareIndexCards);
		indexCardBinder->length++;
	}
	indexCardIndex = (IndexCard*)(node + 1);

	IndexCard_TakeIn(indexCardIndex, wordCardIndex);

	return indexCardIndex;
}

IndexCard *IndexCardBinder_Find(IndexCardBinder *indexCardBinder, char alphabat) {

	IndexCard *indexCardIndex = NULL;
	IndexCard indexCard;
	BinaryNode *node;

	indexCard.alphabat = alphabat;

	node = Search(&indexCardBinder->indexCards, &indexCard, sizeof(IndexCard), CompareIndexCards);

	if (node != NULL) {
		indexCardIndex = (IndexCard*)(node + 1);
	}
	return indexCardIndex;
}

IndexCard *IndexCardBinder_TakeOut(IndexCardBinder *indexCardBinder,
	WordCard *wordCardIndex, char alphabat) {

	IndexCard *indexCardIndex;
	IndexCard indexCard;
	BinaryNode *node;
	Long index;

	indexCard.alphabat = alphabat;

	node = Search(&indexCardBinder->indexCards, &indexCard, sizeof(IndexCard), CompareIndexCards);

	indexCardIndex = (IndexCard*)(node + 1);
	
	index = IndexCard_Find(indexCardIndex, wordCardIndex);
	
	IndexCard_TakeOut(indexCardIndex, index);

	if (indexCardIndex->length == 0) {

		BinaryTree_Delete(&indexCardBinder->indexCards, indexCardIndex,
			sizeof(IndexCard), CompareIndexCards);
		indexCardBinder->length--;

		indexCardIndex = NULL;
	}
	return indexCardIndex;
}

void IndexCardBinder_MakeList(IndexCardBinder *indexCardBinder, IndexCard *(*indexCards),
	Long *count) {

	MakeKeys(&indexCardBinder->indexCards, indexCards, count, sizeof(IndexCard));
}

void IndexCardBinder_Arrange(IndexCardBinder *indexCardBinder) {

	IndexCardBinder_Node_Arrange(indexCardBinder->indexCards.root);
	MakeBalance(&indexCardBinder->indexCards, sizeof(IndexCard));
}
void IndexCardBinder_Node_Arrange(BinaryNode *node) {

	if (node != NULL) {
		
		IndexCard_Arrange((IndexCard*)(node + 1));
		IndexCardBinder_Node_Arrange(node->left);
		IndexCardBinder_Node_Arrange(node->right);
	}
}

void IndexCardBinder_Destroy(IndexCardBinder *indexCardBinder) {

	IndexCardBinder_Node_Destroy(indexCardBinder->indexCards.root);
	BinaryTree_Destroy(&indexCardBinder->indexCards);
}

void IndexCardBinder_Node_Destroy(BinaryNode *node) {

	if (node != NULL) {

		IndexCardBinder_Node_Destroy(node->left);
		IndexCardBinder_Node_Destroy(node->right);
		IndexCard_Destroy((IndexCard*)(node + 1));
	}
}

int CompareIndexCards(void *one, void *other) {

	int ret;
	IndexCard *one_ = (IndexCard*)one;
	IndexCard *other_ = (IndexCard*)other;

	if (one_->alphabat > other_->alphabat) {
		ret = 1;
	}
	else if (one_->alphabat == other_->alphabat) {
		ret = 0;
	}
	else if (one_->alphabat < other_->alphabat) {
		ret = -1;
	}
	return ret;
}
