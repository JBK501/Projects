#include "LinkedList.h"
#include <stdio.h>
#include <stdlib.h>

#pragma warning(disable :4996)

int Compare(void *one, void *other);

int main(int argc, char *argv[]) {

	LinkedList linkedList;
	Node *index;
	Node *(*indexes);
	Long count;
	Long number;
	Long ret;
	Long i;
	Node *previous;
	Node *it;
	

	Create(&linkedList);

	printf("맨 앞에 추가하다.\n");
	number = 100;
	index = AppendFromHead(&linkedList, &number, sizeof(Long));
	GetAt(&linkedList, index, &ret, sizeof(Long));
	printf("%d\n", ret);

	printf("\n앞에서 삽입하다.\n");
	number = 52;
	index = InsertBefore(&linkedList, index, &number, sizeof(Long));
	GetAt(&linkedList, index, &ret, sizeof(Long));
	printf("%d\n", ret);

	printf("\n맨 뒤에 추가하다.\n");
	number = 150;
	index = AppendFromTail(&linkedList, &number, sizeof(Long));
	GetAt(&linkedList, index, &ret, sizeof(Long));
	printf("%d\n", ret);

	printf("\n뒤에서 삽입하다.\n");
	number = 75;
	index = InsertAfter(&linkedList, index, &number, sizeof(Long));
	GetAt(&linkedList, index, &ret, sizeof(Long));
	printf("%d\n", ret);

	printf("\n확인\n");
	previous = NULL;
	it = linkedList.head;
	while (it != previous) {

		GetAt(&linkedList, it, &ret, sizeof(Long));
		printf("%d\t", ret);
		previous = it;
		it = it->next;
	}

	printf("\n\n이전 노드로 이동하다.\n");
	index = Previous(&linkedList);
	GetAt(&linkedList, index, &ret, sizeof(Long));
	printf("%d", ret);

	printf("\n\n처음 노드로 이동하다.\n");
	index = First(&linkedList);
	GetAt(&linkedList, index, &ret, sizeof(Long));
	printf("%d", ret);

	printf("\n\n다음 노드로 이동하다.\n");
	index = Next(&linkedList);
	GetAt(&linkedList, index, &ret, sizeof(Long));
	printf("%d", ret);

	printf("\n\n마지막 노드로 이동하다.\n");
	index = Last(&linkedList);
	GetAt(&linkedList, index, &ret, sizeof(Long));
	printf("%d", ret);

	printf("\n\n처음 노드로 이동하다.(Move)\n");
	index = Move(&linkedList,linkedList.head);
	GetAt(&linkedList, index, &ret, sizeof(Long));
	printf("%d", ret);

	index = Delete(&linkedList, index);
	if (index == NULL) {
		printf("\n\n삭제되었습니다.\n");
	}

	printf("\n확인\n");
	previous = NULL;
	it = linkedList.head;
	while (it != previous) {

		GetAt(&linkedList, it, &ret, sizeof(Long));
		printf("%d\t", ret);
		previous = it;
		it = it->next;
	}

	printf("\n\n찾기\n");
	number = 150;
	index = LinearSearchUnique(&linkedList, &number, sizeof(Long), Compare);
	GetAt(&linkedList, index, &ret, sizeof(Long));
	printf("%d", ret);

	printf("\n\n맨 뒤에 추가하다.\n");
	number = 100;
	index = AppendFromTail(&linkedList, &number, sizeof(Long));
	GetAt(&linkedList, index, &ret, sizeof(Long));
	printf("%d\n", ret);

	printf("\n\n찾기(복수)\n");
	LinearSearchDuplicate(&linkedList, &number, &indexes, &count, sizeof(Long), Compare);
	i = 0;
	while (i < count) {

		GetAt(&linkedList, indexes[i], &ret, sizeof(Long));
		printf("%d\t", ret);
		i++;
	}
	if (indexes != NULL) {
		free(indexes);
	}

	index = DeleteFromHead(&linkedList);
	if (index == NULL) {
		printf("\n\n맨 앞 노드가 삭제되었습니다.");
	}
	printf("\n\n확인\n");
	previous = NULL;
	it = linkedList.head;
	while (it != previous) {

		GetAt(&linkedList, it, &ret, sizeof(Long));
		printf("%d\t", ret);
		previous = it;
		it = it->next;
	}

	index = DeleteFromTail(&linkedList);
	if (index == NULL) {
		printf("\n\n맨 뒤 노드가 삭제되었습니다.");
	}
	printf("\n\n확인\n");
	previous = NULL;
	it = linkedList.head;
	while (it != previous) {

		GetAt(&linkedList, it, &ret, sizeof(Long));
		printf("%d\t", ret);
		previous = it;
		it = it->next;
	}

	DeleteAllItems(&linkedList);
	if (linkedList.length == 0) {
		printf("\n\n모든 노드가 삭제되었습니다.\n");
	}

	printf("\n\n확인\n");
	previous = NULL;
	it = linkedList.head;
	while (it != previous) {

		GetAt(&linkedList, it, &ret, sizeof(Long));
		printf("%d\t", ret);
		previous = it;
		it = it->next;
	}

	Destroy(&linkedList);

	return 0;
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
	else if (*one_ < *other_) {
		ret = -1;
	}

	return ret;
}
