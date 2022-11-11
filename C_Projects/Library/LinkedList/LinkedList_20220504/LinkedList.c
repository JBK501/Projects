#include "LinkedList.h"
#include <stdlib.h>
#include <memory.h>

void Create(LinkedList *linkedList) {

	linkedList->head = NULL;
	linkedList->tail = NULL;
	linkedList->length = 0;
	linkedList->current = NULL;
}

Node *InsertBefore(LinkedList *linkedList, Node *index, void *object, size_t size) {

	//노드와 객체 생성 후 할당
	linkedList->current = (Node*)malloc(sizeof(Node) + size);
	memcpy(linkedList->current + 1, object, size);

	//관계 설정
	linkedList->current->next = index;

	if (linkedList->head != index) {

		linkedList->current->previous = index->previous;
		index->previous->next = linkedList->current;
	}
	else {

		linkedList->current->previous = linkedList->current;
		linkedList->head = linkedList->current;
	}
	index->previous = linkedList->current;
	linkedList->length++;

	return linkedList->current;
}

Node *InsertAfter(LinkedList *linkedList, Node *index, void *object, size_t size) {

	//노드와 객체 생성 후 할당
	linkedList->current = (Node*)malloc(sizeof(Node) + size);
	memcpy(linkedList->current + 1, object, size);

	//관계 설정
	linkedList->current->previous = index;

	if (linkedList->tail != index) {

		linkedList->current->next = index->next;
		index->next->previous = linkedList->current;
	}
	else {

		linkedList->current->next = linkedList->current;
		linkedList->tail = linkedList->current;
	}
	index->next = linkedList->current;
	linkedList->length++;

	return linkedList->current;
}

Node *AppendFromHead(LinkedList *linkedList, void *object, size_t size) {

	//노드와 객체 생성 후 할당
	linkedList->current = (Node*)malloc(sizeof(Node) + size);
	memcpy(linkedList->current + 1, object, size);

	//관계 설정
	linkedList->current->previous = linkedList->current;

	if (linkedList->head != NULL) {

		linkedList->current->next = linkedList->head;
		linkedList->head->previous = linkedList->current;
	}
	else{

		linkedList->current->next = linkedList->current;
		linkedList->tail = linkedList->current;
	}
	linkedList->head = linkedList->current;
	linkedList->length++;

	return linkedList->current;
}

Node *AppendFromTail(LinkedList *linkedList, void *object, size_t size) {

	//노드와 객체 생성 후 할당
	linkedList->current = (Node*)malloc(sizeof(Node) + size);
	memcpy(linkedList->current + 1, object, size);

	//관계 설정
	linkedList->current->next = linkedList->current;
	
	if (linkedList->tail != NULL) {

		linkedList->current->previous = linkedList->tail;
		linkedList->tail->next = linkedList->current;
	}
	else {

		linkedList->current->previous = linkedList->current;
		linkedList->head = linkedList->current;
	}
	linkedList->tail = linkedList->current;
	linkedList->length++;

	return linkedList->current;
}

Node *Delete(LinkedList *linkedList, Node *index) {

	//중간노드 삭제
	if (linkedList->head != index && linkedList->tail != index) {

		index->previous->next = index->next;
		index->next->previous = index->previous;
		linkedList->current = index->next;
	}
	//마지막 노드 삭제
	else if (linkedList->head != index && linkedList->tail == index) {

		index->previous->next = index->previous;
		linkedList->tail = index->previous;
		linkedList->current = index->previous;
	}
	//처음 노드 삭제
	else if (linkedList->head == index && linkedList->tail != index) {

		index->next->previous = index->next;
		linkedList->head = index->next;
		linkedList->current = index->next;
	}
	//노드가 1개일 때 삭제
	else {

		linkedList->head = NULL;
		linkedList->tail = NULL;
		linkedList->current = NULL;
	}

	if (index != NULL) {
		free(index);
		index = NULL;
	}
	linkedList->length--;

	return index;
}

Node *DeleteFromHead(LinkedList *linkedList) {

	Node  *index = linkedList->head;

	if (linkedList->tail != index) {	//노드가 2개이상일 때

		index->next->previous = index->next;
		linkedList->head = index->next;
		linkedList->current = index->next;
	}
	else {	//노드가 1개일 때

		linkedList->head = NULL;
		linkedList->tail = NULL;
		linkedList->current = NULL;
	}
	if (index != NULL) {
		free(index);
		index = NULL;
	}
	linkedList->length--;

	return index;
}

Node *DeleteFromTail(LinkedList *linkedList) {

	Node  *index = linkedList->tail;

	if (linkedList->head != index) {	//노드가 2개이상일 때

		index->previous->next = index->previous;
		linkedList->tail = index->previous;
		linkedList->current = index->previous;
	}
	else {	//노드가 1개일 때

		linkedList->head = NULL;
		linkedList->tail = NULL;
		linkedList->current = NULL;
	}
	if (index != NULL) {
		free(index);
		index = NULL;
	}
	linkedList->length--;

	return index;
}

void DeleteAllItems(LinkedList *linkedList) {

	Node *previous = NULL;

	linkedList->current = linkedList->head;
	while (linkedList->current != previous) {

		linkedList->head = linkedList->current->next;
		previous = linkedList->current;

		if (linkedList->current != NULL) {
			free(linkedList->current);
		}
		linkedList->current = linkedList->head;
	}
	linkedList->head = NULL;
	linkedList->tail = NULL;
	linkedList->current = NULL;
	linkedList->length = 0;
}

Node *LinearSearchUnique(LinkedList *linkedList, void *key,
	size_t size, int(*compare)(void*, void*)) {

	Node *index = NULL;
	Node *previous = NULL;
	Node *it;

	it = linkedList->head;
	while (it != previous && compare(it + 1, key) != 0) {
		
		previous = it;
		it = it->next;
	}

	if (it != previous) {
		index = it;
	}

	return index;
}

void LinearSearchDuplicate(LinkedList *linkedList, void *key, Node* *(*indexes),
	Long *count, size_t size, int(*compare)(void*, void*)) {

	Node *previous = NULL;
	Node *it;
	Long i = 0;

	*count = 0;
	*indexes = (Node*(*))calloc(linkedList->length, sizeof(Node*));

	it = linkedList->head;
	while (it != previous) {

		if (compare(it + 1, key) == 0) {
			
			(*indexes)[i] = it;
			i++;
			(*count)++;
		}

		previous = it;
		it = it->next;
	}
}

Node *First(LinkedList *linkedList) {

	linkedList->current = linkedList->head;
	
	return linkedList->current;
}
Node *Previous(LinkedList *linkedList) {

	linkedList->current = linkedList->current->previous;

	return linkedList->current;
}
Node *Next(LinkedList *linkedList) {

	linkedList->current = linkedList->current->next;

	return linkedList->current;
}
Node *Last(LinkedList *linkedList) {

	linkedList->current = linkedList->tail;

	return linkedList->current;
}
Node *Move(LinkedList *linkedList, Node *index) {

	linkedList->current = index;

	return linkedList->current;
}

void GetAt(LinkedList *linkedList, Node *index, void *object, size_t size) {

	memcpy(object, index + 1, size);
}

void Destroy(LinkedList *linkedList) {

	Node *previous = NULL;

	linkedList->current = linkedList->head;
	while (linkedList->current != previous) {

		linkedList->head = linkedList->current->next;
		previous = linkedList->current;
		
		if (linkedList->current!= NULL) {
			free(linkedList->current);
		}
		linkedList->current = linkedList->head;
	}
}




