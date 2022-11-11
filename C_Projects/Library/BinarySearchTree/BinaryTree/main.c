#include "BinaryTree.h"
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#pragma warning (disable : 4996)

int Compare(void *one, void *other);
void GetAllKeys(BinaryTree *binaryTree, void *(*keys), Long *length, size_t size);
void Node_GetAllKeys(BinaryNode *node, void(*keys), Long *length,
	Long *index, size_t size);

int main(int argc, char*argv[]) {

	BinaryTree binaryTree;
	Long number;
	BinaryNode *index;
	Long ret;
	Long(*numbers);
	Long length;
	Long i;

	Create(&binaryTree);

	printf("[1]�����ϱ�\n");
	number = 100;
	index = Insert(&binaryTree, &number, sizeof(Long), Compare);
	GetAt(&binaryTree, index, &ret, sizeof(Long));
	printf("%d\t", ret);

	number = 50;
	index = Insert(&binaryTree, &number, sizeof(Long), Compare);
	GetAt(&binaryTree, index, &ret, sizeof(Long));
	printf("%d\t", ret);

	number = 30;
	index = Insert(&binaryTree, &number, sizeof(Long), Compare);
	GetAt(&binaryTree, index, &ret, sizeof(Long));
	printf("%d\t", ret);

	number = 40;
	index = Insert(&binaryTree, &number, sizeof(Long), Compare);
	GetAt(&binaryTree, index, &ret, sizeof(Long));
	printf("%d\t", ret);

	number = 150;
	index = Insert(&binaryTree, &number, sizeof(Long), Compare);
	GetAt(&binaryTree, index, &ret, sizeof(Long));
	printf("%d\t", ret);
	printf("\n������ : %d", binaryTree.balance);

	printf("\n\n[2]ã��\n");
	number = 30;
	index = Search(&binaryTree, &number, sizeof(Long), Compare);
	GetAt(&binaryTree, index, &ret, sizeof(Long));
	printf("%d\t", ret);


	number = 150;
	printf("\n\n[3]�����ϱ�\n");
	index = Delete(&binaryTree, &number, sizeof(Long), Compare);
	if (index == NULL) {
		printf("���������ϴ�.");
	}

	GetAllKeys(&binaryTree, &numbers, &length, sizeof(Long));
	i = 0;
	while (i < length) {
		printf("\t%d\t", numbers[i]);
		i++;
	}
	if (numbers != NULL) {
		free(numbers);
	}
	printf("\n������ : %d", binaryTree.balance);

	printf("\n\n[4]Ű���� �����\n");
	MakeKeys(&binaryTree, &numbers, &length, sizeof(Long));
	i = 0;
	while (i < length) {
		printf("%d\t", numbers[i]);
		i++;
	}

	printf("\n\n[5]��� ��� ����\n");
	DeleteAllItems(&binaryTree);

	printf("\n\n[6]Ʈ�� ����\n");
	MakeTree(&binaryTree, numbers, length, sizeof(Long));
	GetAllKeys(&binaryTree, &numbers, &length, sizeof(Long));
	i = 0;
	while (i < length) {
		printf("%d\t", numbers[i]);
		i++;
	}
	if (numbers != NULL) {
		free(numbers);
	}
	printf("\n������ : %d", binaryTree.balance);

	Destroy(&binaryTree);
}

int Compare(void *one, void *other) {

	Long ret;
	Long *one_ = (Long*)one;
	Long *other_ = (Long*)other;

	if (*one_ > *other_) {
		ret = 1;
	}
	else if (*one_ == *other_) {
		ret = 0;
	}
	else {
		ret = -1;
	}

	return ret;
}


void GetAllKeys(BinaryTree *binaryTree, void *(*keys), Long *length, size_t size) {

	Long index = 0;
	*length = 0;

	*keys = (BinaryNode*)calloc(binaryTree->length, size);
	Node_GetAllKeys(binaryTree->root, *keys, length, &index, size);
}

void Node_GetAllKeys(BinaryNode *node, void(*keys), Long *length,
	Long *index, size_t size) {

	if (node != NULL) {

		memcpy(((char(*))keys) + ((*index)*size), node + 1, size);
		(*index)++;
		(*length)++;
		
		Node_GetAllKeys(node->left, keys, length, index, size);
		Node_GetAllKeys(node->right, keys, length, index, size);
	}
}

