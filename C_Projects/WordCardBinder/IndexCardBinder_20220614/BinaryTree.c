#include "BinaryTree.h"
#include <stdlib.h>
#include <memory.h>


void BinaryTree_Create(BinaryTree *binaryTree) {

	binaryTree->root = NULL;
	binaryTree->length = 0;
	binaryTree->balance = 0;
}

BinaryNode *BinaryTree_Insert(BinaryTree *binaryTree, void *key, size_t size,
	int(*compare)(void*, void*)) {

	BinaryNode *index;
	BinaryNode *parent = NULL;
	BinaryNode *child = binaryTree->root;

	while (child != NULL) {

		parent = child;

		// ���� ��ġ�� ã�´�.
		if (compare(parent + 1, key) > 0) {
			
			child = parent->left;
		}
		else {
			child = parent->right;
		}
	}

	//��带 �����.
	index = (BinaryNode*)malloc(sizeof(BinaryNode) + size);
	memcpy(index + 1, key, size);
	index->left = NULL;
	index->right = NULL;

	if (parent != NULL) {

		//key�� �ִ´�.
		if (compare(parent + 1, key) > 0) {
			
			parent->left = index;
		}
		else {

			parent->right = index;
		}

		//���踦 �����Ѵ�.
		if (compare(binaryTree->root + 1, key) < 0) {
			
			binaryTree->balance++;
		}
		else {
			binaryTree->balance--;
		}
	}
	//��尡 �ϳ��� ���� ��
	else {

		//��Ʈ����̴�.
		binaryTree->root = index;
	}
	binaryTree->length++;

	return index;
}

BinaryNode *Search(BinaryTree *binaryTree, void *key, size_t size,
	int(*compare)(void*, void*)) {

	BinaryNode *index = binaryTree->root;

	while (index != NULL && compare(index + 1, key) != 0) {

		if (compare(index + 1, key) > 0) {
			index = index->left;
		}
		else {
			index = index->right;
		}
	}
	return index;
}

BinaryNode *BinaryTree_Delete(BinaryTree *binaryTree, void *key, size_t size,
	int(*compare)(void*, void*)) {

	BinaryNode *index = binaryTree->root;
	BinaryNode *parent = NULL;
	BinaryNode *replaceParent = NULL;
	BinaryNode *replace = NULL;
	BinaryNode *it;

	//������ ���� ������ �θ��带 ã�´�.
	while (index != NULL && compare(index + 1, key) != 0) {

		parent = index;

		if (compare(parent + 1, key) > 0) {
			index = parent->left;
		}
		else {
			index = parent->right;
		}
	}

	//��ü�� ���� ��ü�� �θ��带 ã�´�.
	
	//���� �� ��� ���� �����ʿ��� ���� ���� ���
	it = index->right;
	if (it != NULL) {
		replace = it;
	}
	else {
		replace = index->left;
	}

	while (it != NULL && it->left != NULL) {

		replaceParent = replace;
		replace = replaceParent->left;
		it = it->left;
	}

	//���� �� ��� ���� ������ ��尡 ���� ��� ���ʿ��� ���� ū ���
	it = index->left;
	while (index->right == NULL && it != NULL && it->right != NULL) {

		replaceParent = replace;
		replace = replaceParent->right;
		it = it->right;
	}

	//��ü�ϱ� �� ��ü �� �θ��� ���輳��
	if (replaceParent != NULL) {

		if (compare(replace + 1, key) > 0) {
			replaceParent->left = replace->right;
		}
		else {
			replaceParent->right = replace->left;
		}
	}
	

	//��ü�ϱ�
	if (replace != NULL) {

		if (index->left != replace) {
			replace->left = index->left;
		}
		if (index->right != replace) {
			replace->right = index->right;
		}
	}

	if (parent != NULL) {

		if (compare(parent + 1, key) > 0) {
			parent->left = replace;
		}
		else {
			parent->right = replace;
		}

		if (compare(binaryTree->root + 1, key) > 0) {
			binaryTree->balance++;
		}
		else {
			binaryTree->balance--;
		}
	}
	else {

		binaryTree->root = replace;
		
		if (index->right != NULL) {
			binaryTree->balance--;
		}
		else if (index->left != NULL) {
			binaryTree->balance++;
		}
	}

	//�����Ѵ�.
	if (index != NULL) {
		
		free(index);
		index = NULL;
	}
	binaryTree->length--;

	return index;
}

void MakeKeys(BinaryTree *binaryTree, void*(*keys), Long*length, size_t size) {

	Long index = 0;
	*length = 0;

	*keys = (void(*))calloc(binaryTree->length, size);
	Node_MakeKeys(binaryTree->root, *keys, length, &index, size);
}

void Node_MakeKeys(BinaryNode *node, void(*keys), Long *length, Long *index, size_t size) {

	if (node != NULL) {

		Node_MakeKeys(node->left, keys, length, index, size);
		
		memcpy(((char(*))keys) + ((*index)*size), node + 1, size);
		(*index)++;
		(*length)++;

		Node_MakeKeys(node->right, keys, length, index, size);
	}
}

void BinaryTree_DeleteAllItems(BinaryTree *binaryTree) {

	Node_DeleteAllItems(binaryTree->root);
	
	binaryTree->root = NULL;
	binaryTree->balance = 0;
	binaryTree->length = 0;
}
void Node_DeleteAllItems(BinaryNode *node) {

	if (node != NULL) {

		Node_DeleteAllItems(node->left);
		Node_DeleteAllItems(node->right);

		if (node != NULL) {
			free(node);
		}
	}
}

void MakeBalance(BinaryTree *binaryTree, size_t size) {

	void(*keys);
	Long length;

	MakeKeys(binaryTree, &keys, &length, size);
	BinaryTree_DeleteAllItems(binaryTree);
	MakeTree(binaryTree, keys, length, size);

	if (keys != NULL) {
		free(keys);
	}
}

BinaryNode *MakeTree(BinaryTree *binaryTree, void(*keys), Long length, size_t size) {

	Long low = 0;
	Long high = length - 1;
	Long remainder;

	binaryTree->root = Node_MakeTree(keys, low, high, size);
	binaryTree->length = length;
	
	remainder = length % 2;
	if (remainder == 0) {
		binaryTree->balance++;
	}
	
	return binaryTree->root;
}

BinaryNode *Node_MakeTree(void(*keys), Long low, Long high, size_t size) {

	BinaryNode *node = NULL;
	Long middle;

	if (low <= high) {

		middle = (low + high) / 2;
		
		node = (BinaryNode*)malloc(sizeof(BinaryNode) + size);
		memcpy(node + 1, (((char(*))keys) + (middle*size)), size);

		node->left = Node_MakeTree(keys, low, middle - 1, size);
		node->right = Node_MakeTree(keys, middle + 1, high, size);
	}
	return node;
}

void BinaryTree_GetAt(BinaryTree *binaryTree, BinaryNode *index, void *key, size_t size) {

	memcpy(key, index + 1, size);
}

void BinaryTree_Destroy(BinaryTree *binaryTree) {

	Node_Destroy(binaryTree->root);
}

void Node_Destroy(BinaryNode *node) {

	if (node != NULL) {

		Node_Destroy(node->left);
		Node_Destroy(node->right);
		
		if (node != NULL) {
			free(node);
		}
	}
}