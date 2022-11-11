#ifndef _ARRAY_H
#define _ARRAY_H

typedef signed long int Long;

template <typename T>
class Array{

public:
	Array(Long capacity = 126); //����Ʈ ������ // �Ű������� ������ ������
	Array(const Array & source); //���� ������
	~Array();

	Long GetCapacity() const;
	Long GetLength() const;

	T & GetAt(Long index);
	Long Store(Long index, T object);
	Long Insert(Long index, T object);
	Long AppendFromFront(T object);
	Long AppendFromRear(T object);
	Long Delete(Long index);
	Long DeleteFromFront();
	Long DeleteFromRear();
	void Clear();
	Long Modify(Long index, T object);
	Long LinearSearchUnique(void *key, int(*compare)(void*, void*));
	void LinearSearchDuplicate(void *key, Long *(*indexes), Long *count, int(*compare)(void*, void*));
	Long BinarySearchUnique(void *key, int(*compare)(void*, void*));
	void BinarySearchDuplicate(void *key, Long *(*indexes), Long *count, int(*compare)(void*, void*));
	void SelectionSort(int(*compare)(void*,void*));
	void BubbleSort(int(*compare)(void*, void*));
	void InsertionSort(int(*compare)(void*, void*));
	void Merge(const Array & one, const Array & other);
	


	T & operator[](Long index);
	T * operator+(Long index);
	Array<T> & operator=(const Array & source);

private:
	T(*front);
	Long capacity;
	Long length;
};

template <typename T>
Array<T>::Array(Long capacity){
	
	this->front = new T[capacity];
	this->capacity = capacity;
	this->length = 0;
}

template <typename T>
Array<T>::Array(const Array & source) {

	this->front = new T[source.capacity];
	
	Long i = 0;
	while (i < source.length) {
		
		this->front[i] = source.front[i];
		i++;
	}

	this->capacity = source.capacity;
	this->length = source.length;
}

template <typename T>
Array<T>::~Array(){

	if (this->front != 0) {
		delete[] this->front;
	}
}

template <typename T>
inline Long Array<T>::GetCapacity() const {
	return this->capacity;
}

template <typename T>
inline Long Array<T>::GetLength() const {
	return this->length;
}

template <typename T>
T & Array<T>::GetAt(Long index) {
	return this->front[index];
}

template <typename T>
Long Array<T>::Store(Long index, T object) {

	this->front[index] = object;
	this->length++;

	return index;
}

template <typename T>
Long Array<T>::Insert(Long index, T object) {

	T(*front) = new T[this->capacity + 1]; //1�� ū �迭 ����
	Long i = 0;
	Long j = 0;

	//������ ������ �ű��.
	while (i < index) {
		front[j] = this->front[i];
		j++;
		i++;
	}
	j++;
	while (i < this->length) {
		front[j] = this->front[i];
		j++;
		i++;
	}

	//������ �迭�� ��ü�Ѵ�.
	if (this->front != 0) {
		delete[] this->front;
	}

	this->front = front;
	this->capacity++;
	
	//���� �����Ѵ�.
	this->front[index] = object;
	this->length++;

	return index;
}

template <typename T>
Long Array<T>::AppendFromFront(T object) {

	T(*front) = new T[this->capacity + 1];	//1�� ū �迭 ����
	Long i = 0;
	Long j = 1;
	Long index = 0;

	//���� ������ �ű��.
	while (i < this->length) {

		front[j] = this->front[i];
		j++;
		i++;
	}

	//�������� ��ü�Ѵ�.
	if (this->front != 0) {
		delete[] this->front;
	}

	this->front = front;
	this->capacity++;

	//�迭�� �� �տ� ���ο� ���� �����Ѵ�.
	this->front[index] = object;
	this->length++;

	return index;
}

template <typename T>
Long Array<T>::AppendFromRear(T object) {

	T(*front) = new T[this->capacity + 1]; //1�� ū �迭 ����
	Long index;
	
	//������ ������ �ű��.
	Long i = 0;
	while (i < this->length) {
		front[i] = this->front[i];
		i++;
	}

	//������ �迭�� ��ü�Ѵ�.
	if (this->front != 0) {
		delete[] this->front;
	}

	this->front = front;
	this->capacity++;

	//�迭�� �� �ڿ� ���ο� ���� �����Ѵ�.
	index = this->capacity - 1;

	this->front[index] = object;
	this->length++;

	return index;
}

template <typename T>
Long Array<T>::Delete(Long index) {

	T(*front) = 0;
	Long i = 0;
	Long j = 0;

	//���� �迭 �Ҵ緮�� 2�� �̻��̸� 
	if (this->capacity > 1) {
		//1�� ���� �迭�� �����Ѵ�.
		front = new T[this->capacity - 1];
	}

	//������ ��ġ�� ������ ������ ������ �ű��.
	while (i < index) {

		front[j] = this->front[i];
		j++;
		i++;
	}
	i++;
	while (i < this->length) {
		front[j] = this->front[i];
		j++;
		i++;
	}

	//������ �迭�� ���ش�.
	if (this->front != 0) {

		delete[] this->front;
		this->front = 0;
	}

	//���� �迭�� �Ҵ緮�� 2���̻��̸� ������ �迭�� ��ü�Ѵ�.
	if (this->capacity > 1) {
		this->front = front;
	}
	this->capacity--;
	this->length--;

	index = -1;

	return index;
}

template <typename T>
Long Array<T>::DeleteFromFront() {

	Long index;
	T(*front) = 0;
	Long i = 1;
	Long j = 0;

	//������ �迭�� �Ҵ緮�� 2�� �̻��̸�
	if (this->capacity > 1) {
		//�Ҵ緮�� 1�� ���� �迭�� �����Ѵ�.
		front = new T[this->capacity - 1];
	}

	//2��° �� ���� �ű��.
	while (i < this->length) {
		
		front[j] = this->front[i];
		j++;
		i++;
	}

	//������ �迭�� ���ش�.
	if (this->front != 0) {
		
		delete[] this->front;
		this->front = 0;
	}

	//������ �迭�� �Ҵ緮�� 2�� �̻��̸�
	if (this->capacity > 1) {
		//������ �迭�� ��ü�Ѵ�.
		this->front = front;
	}

	this->capacity--;
	this->length--;

	index = -1;

	return index;
}

template <typename T>
Long Array<T>::DeleteFromRear() {

	Long index;
	T(*front) = 0;
	Long i = 0;

	//������ �迭�� �Ҵ緮�� 2�� �̻��̸� 
	if (this->capacity > 1) {
		//�Ҵ緮�� 1�� ���� �迭�� �����Ѵ�.
		front = new T[this->capacity - 1];
	}

	//������ ���� ������ ������ �ű��.
	while (i < this->capacity - 1) {
		
		front[i] = this->front[i];
		i++;
	}

	//���� �迭�� ���ش�.
	if (this->front != 0) {

		delete[] this->front;
		this->front = 0;
	}

	//������ �迭�� �Ҵ緮�� 2�� �̻��̸�
	if(this->capacity>1){
		this->front = front;
	}
	this->capacity--;
	this->length--;

	index = -1;

	return index;
}

template <typename T>
void Array<T>::Clear() {

	if (this->front != 0) {
		
		delete[] this->front;
		this->front = 0;
	}
	this->capacity = 0;
	this->length = 0;
}

template <typename T>
Long Array<T>::Modify(Long index, T object) {

	this->front[index] = object;
	
	return index;
}

template <typename T>
Long Array<T>::LinearSearchUnique(void *key, int(*compare)(void*, void*)) {

	Long index = -1;
	Long i = 0;

	//�迭���� ã�´�.
	while (i < this->length && compare(this->front + i, key) != 0) {
		i++;
	}
	//ã������ ��ġ�� ���´�
	if (i < this->length) {
		index = i;
	}

	return index;
}

template<typename T>
void Array<T>::LinearSearchDuplicate(void *key, Long *(*indexes), Long *count, int(*compare)(void*, void*)) {

	Long i = 0;
	Long j = 0;
	
	*count = 0;
	*indexes = new Long[this->length];	//ã�� ��ġ�� ������ �迭

	while (i < this->length) {
		
		if (compare(this->front + i, key) == 0) {
			(*indexes)[j] = i;
			j++;
			(*count)++;
		}
		i++;
	}
}

template <typename T>
Long Array<T>::BinarySearchUnique(void *key, int(*compare)(void*, void*)) {

	Long index = -1;
	Long start = 0;
	Long end = this->length - 1;
	Long middle = (start + end) / 2;

	while (start <= end && compare(this->front + middle, key) != 0) {

		if (compare(this->front + middle, key) < 0) {
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

template <typename T>
void Array<T>::BinarySearchDuplicate(void *key, Long *(*indexes), Long *count, int(*compare)(void*, void*)) {

	Long start = 0;
	Long end = this->length - 1;
	Long middle = (start + end) / 2;
	Long i;
	Long j = 0;

	*count = 0;
	*indexes = new Long[this->length];	//ã�� ��ġ�� ������ �迭 ����

	while (start <= end && compare(this->front + middle, key) != 0) {

		if (compare(this->front + middle, key) < 0) {
			start = middle + 1;
		}
		else {
			end = middle - 1;
		}
		middle = (start + end) / 2;
	}
	
	//ã�� ���� ó����ġ�� �̵��Ѵ�.
	i = middle - 1;
	while (i >= 0 && compare(this->front + i, key) == 0) {
		i--;
	}

	//ã�� ���� ó����ġ���� �����Ѵ�.
	i++;
	while (i < this->length && compare(this->front + i, key) == 0) {
	
		(*indexes)[j] = i;
		j++;
		(*count)++;
		
		i++;
	}
}

template <typename T>
void Array<T>::SelectionSort(int(*compare)(void*,void*)) {

	T object;
	Long i = 0;
	Long j;
	Long index;

	while (i < this->length - 1) {

		index = i;
		
		j = i + 1;
		while (j < this->length) {

			if (compare(this->front + index, this->front + j) > 0) {
				index = j;
			}
			j++;
		}
		object = this->front[i];
		this->front[i] = this->front[index];
		this->front[index] = object;

		i++;
	}
}

template <typename T>
void Array<T>::BubbleSort(int(*compare)(void*, void*)) {

	T object;
	Long i = this->length - 1;
	Long j;
	Long flag = 1;

	while (i > 0 && flag == 1) {

		flag = 0;
		
		j = 0;
		while (j < i) {

			if (compare(this->front + i, this->front + (j + 1)) > 0) {
				
				object = this->front[j];
				this->front[j] = this->front[j + 1];
				this->front[j + 1] = object;
				
				flag = 1;
			}
			j++;
		}
		i--;
	}
}

template <typename T>
void Array<T>::InsertionSort(int(*compare)(void*, void*)) {

	T object;
	Long i = 1;
	Long j;

	while (i < this->length) {
		
		object = this->front[i];
		j = i - 1;
		while (j >= 0 && compare(this->front + j, &object) > 0) {

			this->front[j + 1] = this->front[j];
			j--;
		}
		
		this->front[j + 1] = object;
		i++;
	}
}

template <typename T>
void Array<T>::Merge(const Array & one, const Array & other) {

	Long capacity = one.length + other.length;
	Long i = 0;
	Long j = 0;
	Long k = 0;

	//������ �迭�� �����Ѵ�.
	if (this->front != 0) {
		delete[] this->front;
	}

	//������ �迭�� �����Ѵ�.
	this->front = new T[capacity];
	this->capacity = capacity;
	this->length = 0;

	while (i < one.length && j < other.length) {

		if (one.front[i] <= other.front[j]) {

			this->front[k] = one.front[i];
			k++;
			i++;
		}
		else {

			this->front[k] = other.front[j];
			k++;
			j++;
		}
	}
	while (i < one.length) {

		this->front[k] = one.front[i];
		k++;
		i++;
	}
	while (j < other.length) {

		this->front[k] = other.front[j];
		k++;
		j++;
	}
	this->length = one.length + other.length;
}

template <typename T>
T & Array<T>::operator[](Long index) {
	return this->front[index];
}

template <typename T>
T * Array<T>::operator+(Long index) {
	return this->front + index;
}

template <typename T>
Array<T> & Array<T>::operator=(const Array & source) {

	Long i = 0;

	if (this->front != 0) {
		delete[] this->front;
	}

	this->front = new T[source.capacity];
	this->capacity = source.capacity;
	this->length = 0;

	while (i < source.length) {

		this->front[i] = source.front[i];
		i++;
	}
	this->length = source.length;

	return *this;
}
#endif // !_ARRAY_H
