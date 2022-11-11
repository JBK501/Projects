#include "Array.h"
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#pragma warning(disable:4996)

void Create(Array *array, Long capacity, size_t size) {

	array->front = calloc(capacity, size);
	array->capacity = capacity;
	array->length = 0;
}

void GetAt(Array *array, Long index, void *object, size_t size) {
	memcpy(object, ((char(*))array->front) + (index*size), size);
}

Long Store(Array *array, Long index, void *object, size_t size) {

	memcpy(((char(*))array->front) + (index*size), object, size);
	
	array->length++;

	return index;
}

Long Insert(Array *array, Long index, void *object, size_t size) {

	void(*front) = NULL;
	Long i = 0;
	Long j;

	front = calloc(array->capacity + 1, size);

	while (i < index) {

		memcpy(((char(*))front) + (i*size), 
			((char(*))array->front) + (i*size), size);
		i++;
	}

	j = index + 1;
	while (i < array->length) {

		memcpy(((char(*))front) + (j*size), 
			((char(*))array->front) + (i*size), size);
		j++;
		i++;
	}
	if (array->front != NULL) {
		free(array->front);
	}
	array->front = front;
	array->capacity++;

	memcpy(((char(*))array->front) + 
		(index*size), object, size);
	array->length++;

	return index;
}

Long AppendFromFront(Array *array, void *object, size_t size) {

	Long index = 0;
	void(*front);
	Long i = 0;
	Long j = 1;

	front = calloc(array->capacity + 1, size);

	while (i < array->length) {

		memcpy(((char(*))front) + (j*size), 
			((char(*))array->front) + (i*size), size);
		j++;
		i++;
	}

	if (array->front != NULL) {
		free(array->front);
	}
	array->front = front;
	array->capacity++;

	memcpy(((char(*))array->front) + (index*size) , 
		object, size);
	array->length++;

	return index;
}

Long AppendFromRear(Array *array, void *object, size_t size) {

	Long index;
	void(*front);
	Long i = 0;
	
	front = calloc(array->capacity + 1, size);
	
	while (i < array->length) {

		memcpy(((char(*))front) + (i*size),
			((char(*))array->front) + (i*size), size);
		i++;
	}

	if (array->front != NULL) {
		free(array->front);
	}
	array->front = front;
	array->capacity++;

	index = array->capacity - 1;
	memcpy(((char(*))array->front) + (index*size), 
		object, size);
	array->length++;

	return index;
}

Long Delete(Array *array, Long index, size_t size) {

	void(*front) = NULL;
	Long i = 0;
	Long j;

	if (array->capacity > 1) {
		front = calloc(array->capacity - 1, size);
	}

	while (i < index) {

		memcpy(((char(*))front) + (i*size), 
			((char(*))array->front) + (i*size), size);
		i++;
	}

	j = i;
	i++;
	while (i < array->length) {
		
		memcpy(((char(*))front) + (j*size),
			((char(*))array->front) + (i*size), size);
		j++;
		i++;
	}

	if (array->front != NULL) {
		
		free(array->front);
		array->front = NULL;
	}

	if (array->capacity > 1) {
		array->front = front;
	}
	array->capacity--;
	array->length--;

	index = -1;
	
	return index;
}

Long DeleteFromFront(Array *array, size_t size) {

	Long index;
	void(*front) = NULL;
	Long i = 1;
	Long j = 0;

	if (array->capacity > 1) {
		front = calloc(array->capacity - 1, size);
	}

	while (i < array->length) {

		memcpy(((char(*))front) + (j*size), 
			((char(*))array->front) + (i*size), size);
		j++;
		i++;
	}

	if (array->front != NULL) {
		
		free(array->front);
		array->front = NULL;
	}

	if (array->capacity > 1) {
		array->front = front;
	}
	array->capacity--;
	array->length--;

	index = -1;

	return index;
}

Long DeleteFromRear(Array *array, size_t size) {

	Long index;
	void(*front) = NULL;
	Long i = 0;

	if (array->capacity > 1) {
		front = calloc(array->capacity - 1, size);
	}

	while (i < array->capacity - 1) {

		memcpy(((char(*))front) + (i*size),
			((char(*))array->front) + (i*size), size);
		i++;
	}

	if (array->front != NULL) {

		free(array->front);
		array->front = NULL;
	}

	if (array->capacity > 1) {
		array->front = front;
	}
	array->capacity--;
	array->length--;

	index = -1;

	return index;
}

void Clear(Array *array) {

	if (array->front != NULL) {
		free(array->front);
		array->front = NULL;
	}
	array->capacity = 0;
	array->length = 0;
}

Long Modify(Array *array, Long index, void *object, size_t size) {

	memcpy(((char(*))array->front) + (index*size),
		object, size);

	return index;
}

Long LinearSearchUnique(Array *array, void *key, size_t size,
	int(*compare)(void*, void*)) {

	Long index = -1;
	Long i = 0;

	while (i < array->length &&
		compare(((char(*))array->front) + (i*size), key) != 0) {
		i++;
	}

	if (i < array->length) {
		index = i;
	}

	return index;
}

void LinearSearchDuplicate(Array *array, void *key,
	Long*(*indexes), Long *count, size_t size,
	int(*compare)(void*, void*)) {

	Long i = 0;
	Long j = 0;
	*count = 0;

	*indexes = (Long(*))calloc(array->length, sizeof(Long));

	while (i < array->length) {

		if (compare(((char(*))array->front) + (i*size), key) == 0) {
			(*indexes)[j] = i;
			j++;
			(*count)++;
		}
		i++;
	}
}

Long BinarySearchUnique(Array *array, void *key, size_t size,
	int(*compare)(void*, void*)) {

	Long index = -1;
	Long start = 0;
	Long end;
	Long middle;

	end = array->length - 1;
	middle = (start + end) / 2;
	while (start <= end &&
		compare(((char(*))array->front) + (middle*size), key) != 0) {

		if (compare(((char(*))array->front) + (middle*size), key) < 0) {
			start = middle + 1;
		}
		else {
			end = middle - 1;
		}
		middle = (start + end) / 2;
	}
	if (start <= end) {
		index = middle;
	}
	return index;
}

void BinarySearchDuplicate(Array *array, void *key,
	Long*(*indexes), Long *count, size_t size,
	int(*compare)(void*, void*)) {

	Long start = 0;
	Long end;
	Long middle;
	Long i;
	Long j = 0;
	*count = 0;

	*indexes = (Long(*))calloc(array->length, sizeof(Long));

	end = array->length - 1;
	middle = (start + end) / 2;
	while (start <= end &&
		compare(((char(*))array->front) + (middle*size), key) != 0) {

		if (compare(((char(*))array->front) + (middle*size), key) < 0){
			start = middle + 1;
		}
		else {
			end = middle - 1;
		}
		middle = (start + end) / 2;
	}

	i = middle - 1;
	while (i >= 0 &&
		compare(((char(*))array->front) + (i*size), key) == 0) {
		i--;
	}

	i++;
	while (i < array->length && 
		compare(((char(*))array->front) + (i*size), key) == 0) {
		
		(*indexes)[j] = i;
		(*count)++;
		j++;
		i++;
	}
}

void SelectionSort(Array *array, size_t size,
	int(*compare)(void*, void*)) {

	void *object = malloc(size);
	Long i = 0;
	Long j;
	Long index;

	while (i < array->length - 1) {

		index = i;

		j = i + 1;
		while (j < array->length) {

			if (compare(((char(*))array->front) + (index*size),
				((char(*))array->front) + (j*size)) > 0) {
				index = j;
			}
			j++;
		}
		memcpy(object, ((char(*))array->front) + 
			(i*size), size);
		memcpy(((char(*))array->front) + (i*size),
			((char(*))array->front) + (index*size), size);
		memcpy(((char(*))array->front) + (index*size), object, size);
		
		i++;
	}
	if (object != NULL) {
		free(object);
	}
}

void BubbleSort(Array *array, size_t size,
	int(*compare)(void*, void*)) {

	void*object = malloc(size);
	Long i;
	Long j;
	Long flag = 1;

	i = array->length - 1;
	while (i > 0 && flag == 1) {

		flag = 0;
		j = 0;

		while (j < i) {

			if (compare(((char(*))array->front) + (j*size),
				((char(*))array->front) + ((j + 1)*size)) > 0){

				memcpy(object, ((char(*))array->front) +
					(j*size), size);
				memcpy(((char(*))array->front) + (j*size),
					((char(*))array->front) + ((j + 1)*size), size);
				memcpy(((char(*))array->front) + ((j + 1)*size), object,size);
				
				flag = 1;
			}
			j++;
		}
		i--;
	}
	if (object != NULL) {
		free(object);
	}
}

void InsertionSort(Array *array, size_t size,
	int(*compare)(void*, void*)) {

	void *object=malloc(size);
	Long i = 1;
	Long j;

	while (i < array->length) {

		memcpy(object, 
			((char(*))array->front) + (i*size), size);
		
		j = i - 1;
		while(j >= 0 &&
			compare(((char(*))array->front) + (j*size), object) > 0) {

			memcpy(((char(*))array->front) + ((j + 1)*size),
				((char(*))array->front) + (j*size), size);
			j--;
		}
		memcpy(((char(*))array->front) + ((j+1)*size), 
			object, size);
		i++;
	}
	if (object != NULL) {
		free(object);
	}
}

void Merge(Array *array, Array *one, Array *other, size_t size,
	int(*compare)(void*, void*)) {

	Long capacity;
	Long i = 0;
	Long j = 0;
	Long k = 0;

	if (array->front != NULL) {
		free(array->front);
	}

	capacity = one->length + other->length;
	
	array->front = calloc(capacity, size);
	array->capacity = capacity;
	
	while (i < one->length && j < other->length) {

		if (compare(((char(*))one->front) + (i*size),
			((char(*))other->front) + (j*size)) <= 0) {

			memcpy(((char(*))array->front) + (k*size),
				((char(*))one->front) + (i*size), size);
			k++;
			i++;
		}
		else {

			memcpy(((char(*))array->front) + (k*size),
				((char(*))other->front) + (j*size), size);
			k++;
			j++;
		}
	}
	while (i < one->length) {

		memcpy(((char(*))array->front) + (k*size),
			((char(*))one->front) + (i*size), size);
		k++;
		i++;
	}
	while (j < other->length) {

		memcpy(((char(*))array->front) + (k*size),
			((char(*))other->front) + (j*size), size);
		k++;
		j++;
	}
	array->length = one->length + other->length;
}

void Destroy(Array *array) {

	if (array->front != NULL) {
		free(array->front);
	}
}