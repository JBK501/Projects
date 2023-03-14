#ifndef _LINKEDLIST_H
#define _LINKEDLIST_H

#include <stddef.h>

typedef signed long int Long;

typedef struct _node Node;

typedef struct _node{

	Node *previous;
	Node *next;
}Node;

typedef struct _linkedList {

	Node *head;
	Node *tail;
	Long length;
	Node *current;

}LinkedList;

void Create(LinkedList *linkedList);

//추가
Node *InsertBefore(LinkedList *linkedList, Node *index, void *object, size_t size);
Node *InsertAfter(LinkedList *linkedList, Node *index, void *object, size_t size);
Node *AppendFromHead(LinkedList *linkedList, void *object, size_t size);
Node *AppendFromTail(LinkedList *linkedList, void *object, size_t size);

//삭제
Node *Delete(LinkedList *linkedList, Node *index);
Node *DeleteFromHead(LinkedList *linkedList);
Node *DeleteFromTail(LinkedList *linkedList);
void DeleteAllItems(LinkedList *linkedList);

//검색
Node *LinearSearchUnique(LinkedList *linkedList, void *key, 
	size_t size, int(*compare)(void*, void*));
void LinearSearchDuplicate(LinkedList *linkedList, void *key, Node* *(*indexes),
	Long *count, size_t size, int(*compare)(void*, void*));

//이동
Node *First(LinkedList *linkedList);
Node *Previous(LinkedList *linkedList);
Node *Next(LinkedList *linkedList);
Node *Last(LinkedList *linkedList);
Node *Move(LinkedList *linkedList, Node *index);

void GetAt(LinkedList *linkedList, Node *index, void *object, size_t size);

void Destroy(LinkedList *linkedList);
#endif // !_LINKEDLIST_H
