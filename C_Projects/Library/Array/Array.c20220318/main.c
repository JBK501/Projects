#include "Array.h"
#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)

int Compare(void *one, void *other);

int main(int argc, char*argv[]) {
	
	Array array;
	Long index;
	Long number;
	Long(*indexes);
	Long count;
	Array one;
	Array other;
	Long ret;
	Long i;

	Create(&array, 3, sizeof(Long));
	
	number = 17;
	index = Store(&array, 0, &number, sizeof(Long));
	GetAt(&array, index, &ret, sizeof(Long));
	printf("%d\n", ret);

	number = 15;
	index = Store(&array, 1, &number, sizeof(Long));
	GetAt(&array, index, &ret, sizeof(Long));
	printf("%d\n", ret);

	number = 17;
	index = Store(&array, 2, &number, sizeof(Long));
	GetAt(&array, index, &ret, sizeof(Long));
	printf("%d\n", ret);

	number = 23;
	index = Insert(&array, 1, &number, sizeof(Long));
	GetAt(&array, index, &ret, sizeof(Long));
	printf("%d\n", ret);
	
	number = 21;
	index = AppendFromFront(&array, &number, sizeof(Long));
	GetAt(&array, index, &ret, sizeof(Long));
	printf("%d\n", ret);

	number = 37;
	index = AppendFromRear(&array, &number, sizeof(Long));
	GetAt(&array, index, &ret, sizeof(Long));
	printf("%d\n", ret);

	index = Delete(&array, 2, sizeof(Long));
	if (index == -1) {
		printf("지워졌습니다.\n");
	}

	index = DeleteFromFront(&array, sizeof(Long));
	if (index == -1) {
		printf("맨 앞에서 지워졌습니다.\n");
	}

	index = DeleteFromRear(&array, sizeof(Long));
	if (index == -1) {
		printf("맨 뒤에서 지워졌습니다.\n");
	}

	number = 10;
	index = Modify(&array, 0, &number, sizeof(Long));
	GetAt(&array, index, &ret, sizeof(Long));
	printf("%d\n", ret);

	number = 15;
	index = LinearSearchUnique(&array, &number, sizeof(Long), Compare);
	GetAt(&array, index, &ret, sizeof(Long));
	printf("%d\n", ret);

	number = 17;
	index = AppendFromFront(&array, &number, sizeof(Long));
	GetAt(&array, index, &ret, sizeof(Long));
	printf("%d\n", ret);

	LinearSearchDuplicate(&array, &number, &indexes, &count, sizeof(Long), Compare);
	i = 0;
	while (i < count) {
		
		GetAt(&array, indexes[i], &ret, sizeof(Long));
		printf("%d\t", ret);
		i++;
	}
	if (indexes != NULL) {

		free(indexes);
		indexes = NULL;
	}
	printf("\n\n");
	

	SelectionSort(&array, sizeof(Long), Compare);
	i = 0;
	while (i < array.length) {
		
		GetAt(&array, i, &ret, sizeof(Long));
		printf("%d\t", ret);
		i++;
	}
	printf("\n");

	BinarySearchDuplicate(&array, &number, &indexes, 
		&count, sizeof(Long), Compare);

	i = 0;
	while (i < count) {

		GetAt(&array, indexes[i], &ret, sizeof(Long));
		printf("%d\t", ret);
		i++;
	}
	if (indexes != NULL) {

		free(indexes);
		indexes = NULL;
	}
	printf("\n\n");

	index = DeleteFromRear(&array, sizeof(Long));
	if (index == -1) {
		printf("맨 뒤에서 지워졌습니다.\n");
	}

	number = 10;
	index = BinarySearchUnique(&array, &number, sizeof(Long), Compare);
	GetAt(&array, index, &ret, sizeof(Long));
	printf("%d\n", ret);

	printf("\n");
	Clear(&array);
	printf("%d", array.capacity);
	printf("\n\n");

	//병합을 위한 one생성
	Create(&one, 3, sizeof(Long));

	number = 33;
	index = Store(&one, 0, &number, sizeof(Long));
	GetAt(&one, index, &ret, sizeof(Long));
	printf("%d\n", ret);

	number = 24;
	index = Store(&one, 1, &number, sizeof(Long));
	GetAt(&one, index, &ret, sizeof(Long));
	printf("%d\n", ret);

	number = 37;
	index = Store(&one, 2, &number, sizeof(Long));
	GetAt(&one, index, &ret, sizeof(Long));
	printf("%d\n", ret);

	BubbleSort(&one, sizeof(Long), Compare);
	i = 0;
	while (i < one.length) {

		GetAt(&one, i, &ret, sizeof(Long));
		printf("%d\t", ret);
		i++;
	}
	printf("\n\n");

	Create(&other, 4, sizeof(Long));

	number = 5;
	index = Store(&other, 0, &number, sizeof(Long));
	GetAt(&other, index, &ret, sizeof(Long));
	printf("%d\n", ret);

	number = 97;
	index = Store(&other, 1, &number, sizeof(Long));
	GetAt(&other, index, &ret, sizeof(Long));
	printf("%d\n", ret);

	number = 54;
	index = Store(&other, 2, &number, sizeof(Long));
	GetAt(&other, index, &ret, sizeof(Long));
	printf("%d\n", ret);

	number = 34;
	index = Store(&other, 3, &number, sizeof(Long));
	GetAt(&other, index, &ret, sizeof(Long));
	printf("%d\n", ret);

	InsertionSort(&other, sizeof(Long), Compare);
	i = 0;
	while (i < other.length) {

		GetAt(&other, i, &ret, sizeof(Long));
		printf("%d\t", ret);
		i++;
	}
	printf("\n\n");

	Merge(&array, &one, &other, sizeof(Long), Compare);
	i = 0;
	while (i < array.length) {

		GetAt(&array, i, &ret, sizeof(Long));
		printf("%d\t", ret);
		i++;
	}
	printf("\n");

	Destroy(&one);
	Destroy(&other);
	Destroy(&array);

	return 0;
}

int Compare(void *one, void *other) {
	
	Long *one_ = (Long*)one;
	Long *other_ = (Long*)other;
	Long ret;

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