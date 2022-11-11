#include "Array.h"
#include <iostream>
using namespace std;

int Compare(void *one, void *other);

int main(int argc, char *argv[]) {

	Array<int> array(3);

	cout << "array" << endl;

	Long index = array.Store(0, 17);
	int object = array.GetAt(index);
	cout << object << endl;

	index = array.Store(1, 15);
	object = array.GetAt(index);
	cout << object << endl;

	index = array.Store(2, 17);
	object = array.GetAt(index);
	cout << object << endl;
	
	index = array.Insert(1, 23);
	object = array.GetAt(index);
	cout << object << endl;

	index = array.AppendFromFront(21);
	object = array.GetAt(index);
	cout << object << endl;

	index = array.AppendFromRear(37);
	object = array.GetAt(index);
	cout << object << endl;

	cout << endl;
	index = array.Delete(2);
	if (index == -1) {
		cout << "3번째 값이 삭제되었습니다." << endl;
	}

	index = 0;
	index = array.DeleteFromFront();
	if (index == -1) {
		cout << "맨 앞 값이 삭제되었습니다." << endl;
	}

	index = 0;
	index = array.DeleteFromRear();
	if (index == -1) {
		cout << "맨 뒤 값이 삭제되었습니다." << endl;
	}

	cout << endl;
	index = array.Modify(0, 10);
	object = array.GetAt(index);
	cout << object << endl;

	Long key = 15;
	index = array.LinearSearchUnique(&key, Compare);
	object = array.GetAt(index);
	cout << object << endl;

	index = array.AppendFromFront(17);
	object = array.GetAt(index);
	cout << object << endl;

	cout << endl;
	Long(*indexes);
	Long count;
	key = 17;

	cout << "선형탐색" << endl;
	array.LinearSearchDuplicate(&key, &indexes, &count, Compare);
	Long i = 0;
	while (i < count) {

		object = array.GetAt(indexes[i]);
		cout << object << endl;

		i++;
	}
	if (indexes != 0) {
		delete[] indexes;
	}

	cout << endl;
	cout << "선택정렬" << endl;
	array.SelectionSort(Compare);
	Long length = array.GetLength();
	i = 0;
	while (i < length) {

		object = array.GetAt(i);
		cout << object << endl;
		i++;
	}

	cout << endl;
	cout << "이진 탐색" << endl;
	array.BinarySearchDuplicate(&key, &indexes, &count, Compare);
	
	i = 0;
	while (i < count) {

		object = array.GetAt(indexes[i]);
		cout << object << endl;

		i++;
	}
	if (indexes != 0) {
		delete[] indexes;
	}

	index = array.DeleteFromRear();
	if (index == -1) {
		cout << "맨뒤 삭제" << endl;
	}

	cout << endl;
	cout << "10 찾기" << endl;
	key = 10;
	index = array.BinarySearchUnique(&key, Compare);
	cout << array[index] << endl;

	array.Clear();

	cout << endl;
	cout << "one 배열" << endl;
	Array<int> one(3);

	index = one.Store(0, 33);
	cout << one[index] << endl;

	index = one.Store(1, 24);
	cout << one[index] << endl;

	index = one.Store(2, 37);
	cout << one[index] << endl;

	cout << "버블정렬" << endl;
	one.BubbleSort(Compare);
	length = one.GetLength();

	i = 0;
	while (i < length) {

		cout << one[i] << endl;
		i++;
	}


	cout << endl;
	cout << "other 배열" << endl;
	Array<int> other(4);

	index = other.Store(0, 5);
	cout << other[index] << endl;
	index = other.Store(1, 97);
	cout << other[index] << endl;
	index = other.Store(2, 54);
	cout << other[index] << endl;
	index = other.Store(3, 34);
	cout << other[index] << endl;
	
	cout << "삽입정렬" << endl;
	other.InsertionSort(Compare);
	length = other.GetLength();
	i = 0;
	while (i < length) {

		cout << other[i] << endl;
		i++;
	}

	cout << endl;
	cout << "array에 병합하기" << endl;
	array.Merge(one, other);
	length = array.GetLength();
	i = 0;
	while (i < length) {

		cout << array[i] << endl;
		i++;
	}

	cout << endl;
	cout << "복사 생성자 Test" << endl;
	Array<int> one_(one);
	length = one_.GetLength();
	i = 0;
	while (i < length) {

		cout << one_[i] << endl;
		i++;
	}

	cout << endl;
	cout << "치환 연산자 Test" << endl;
	Array<int> other_ = other;
	length = other_.GetLength();
	i = 0;
	while (i < length) {

		cout << other_[i] << endl;
		i++;
	}

	return 0;
}

int Compare(void*one, void* other) {

	int *one_ = (int *)one;
	int *other_ = (int *)other;
	int ret;

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