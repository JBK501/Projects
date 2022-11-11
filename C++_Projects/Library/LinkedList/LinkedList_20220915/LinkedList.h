#ifndef LINKEDLIST_H
#define LINKEDLIST_H

typedef signed long int Long;

template <typename T>
class LinkedList 
{
public:	//Nested Class
	class Node 
	{
		// ���Ḯ��Ʈ ���̺귯������ ��� ��� ���� ���
		friend class LinkedList;

	public:
		Node() 
		{
			this->previous = this;
			this->next = this;
		}
		Node(T object)
		{
			this->previous = this;
			this->object = object;
			this->next = this;
		}
		Node(Node *previous, T object) 
		{
			this->previous = previous;
			this->object = object;
			this->next = this;
		}
		Node(T object, Node *next)
		{
			this->previous = this;
			this->object = object;
			this->next = next;
		}
		Node(Node *previous, T object, Node *next) 
		{
			this->previous = previous;
			this->object = object;
			this->next = next;
		}
		Node(const Node &source) 
		{
			this->previous = source.previous;
			this->object = source.object;
			this->next = source.object;
		}
		~Node(){}
		
		Node& operator=(const Node &source) 
		{

			this->previous = source.previous;
			this->object = source.object;
			this->next = source.next;

			return *this;
		}

		T& GetObject() const 
		{
			return const_cast<T&>(this->object);
		}

	private:
		Node *previous;
		T object;
		Node *next;
	};

public:
	LinkedList();
	LinkedList(const LinkedList & source);
	~LinkedList();

	Node* InsertBefore(Node *index, T object);
	Node* InsertAfter(Node *index, T object);
	Node* AppendFromHead(T object);
	Node* AppendFromTail(T object);
	Node* Delete(Node *index);
	Node* DeleteFromHead();
	Node* DeleteFromTail();
	void DeleteAllItems();
	Node* LinearSearchUnique(void *key, int(*compare)(void*, void*));
	void LinearSearchDuplicate(void *key, Node* *(*indexes), Long *count, int(*compare)(void*, void*));
	Node* First();
	Node* Previous();
	Node* Next();
	Node* Last();
	Node* Move(Node *index);
	T& GetAt(Node *index);

	LinkedList& operator=(const LinkedList & source);
	T& operator[](Long index);

	Long GetLength() const;
	Node* GetCurrent() const;

private:
	Node *head;
	Node *tail;
	int length;
	Node *current;

};

template <typename T>
inline Long LinkedList<T>::GetLength() const
{
	return this->length;
}

template <typename T>
inline typename LinkedList<T>::Node * LinkedList<T>::GetCurrent() const
{
	return const_cast<Node*>(this->current);
}


template <typename T>
LinkedList<T>::LinkedList() 
{
	//���Ḯ��Ʈ�� �ʱ�ȭ �Ѵ�.
	this->head = 0;
	this->tail = 0;
	this->length = 0;
	this->current = 0;
}

template <typename T>
LinkedList<T>::LinkedList(const LinkedList &source)
{
	//(��尡 1���� ���� ���� ��� ����)
	// ù ��° ��带 �߰��Ѵ�. 
	Node *it = source.head;
	this->head = new Node(it->object);
	Node *index = this->head;

	// ������ ������ �߰��Ѵ�.
	Node *next = it->next;
	while (next != it)
	{
		this->current = new Node(index, next->object);	// ���� ��� �߰�
		index->next = this->current;	// ���� ��带 ������忡 ����
		index = index->next;

		it = next;
		next = next->next;
	}

	this->tail = index;
	this->length = source.length;

	// ���� ����� ��ġ�� ���Ѵ�.
	this->current = this->head;
	it = source.head;
	while (it != source.current)
	{
		this->current = this->current->next;
		it = it->next;
	}
}

template <typename T>
LinkedList<T>::~LinkedList() 
{
	//���Ḯ��Ʈ�� ��� ��带 �����Ѵ�.
	Node *previous = 0;
	this->current = this->head;
	while (previous != this->current)
	{
		this->head = this->current->next;
		
		previous = this->current;
		if (this->current != 0) 
		{
			delete this->current;
		}

		this->current = this->head;
	}
}

template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::InsertBefore(Node *index, T object)
{
	// ���ο� ��� ���� ����
	if (this->head != index)
	{
		// �޾ƿ� ��ġ�� ó����ġ�� �ƴ� ��
		this->current = new Node(index->previous, object, index);
	}
	else
	{
		// �޾ƿ� ��ġ�� ó����ġ �� ��
		this->current = new Node(object, index);
	}
	// ������ ���� ����
	if (this->head != index)
	{
		index->previous->next = this->current;
	}
	else
	{
		this->head = this->current;
	}

	index->previous = this->current;
	this->length++;

	return this->current;
}

template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::InsertAfter(Node *index, T object)
{
	// ���ο� ��� ���� ����
	if (this->tail != index)
	{
		// �޾ƿ� ��ġ�� �������� �ƴ� ��
		this->current = new Node(index, object, index->next);
	}
	else
	{
		// �޾ƿ� ��ġ�� �������� ��
		this->current = new Node(index, object);
	}

	// ������ ���� ����
	if (this->tail != index)
	{
		index->next->previous = this->current;
	}
	else
	{
		this->tail = this->current;
	}

	index->next = this->current;
	this->length++;

	return this->current;

}


template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::AppendFromHead(T object) 
{

	// ���ο� ��� ���� ����
	if (this->head != 0) 
	{
		// ���Ḯ��Ʈ�� ��尡 ���� ��
		// ���ο� ��带 �� �� ���� �����Ѵ�.
		this->current = new Node(object, this->head);
	}
	else
	{
		// ���Ḯ��Ʈ�� ��尡 ���� ��
		this->current = new Node(object);
	}

	// ������ ���� ����
	if (this->head != 0) 
	{
		// ���Ḯ��Ʈ�� ��尡 ���� �� 
		// ������ �� �ճ�带 ���ο� ��忡 �����Ѵ�.
		this->head->previous = this->current;
	}
	else
	{
		// ���Ḯ��Ʈ�� ��尡 ���� ��
		this->tail = this->current;
	}

	this->head = this->current;
	this->length++;
	
	return this->current;
}

template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::AppendFromTail(T object)
{
	// ���ο� ��� ���� ����
	if (this->tail != 0)
	{
		// ���Ḯ��Ʈ�� ��尡 ���� ��
		this->current = new Node(this->tail, object);
	}
	else
	{
		// ���Ḯ��Ʈ�� ��尡 ���� ��
		this->current = new Node(object);
	}

	// ������ ���� ����
	if (this->tail != 0)
	{
		this->tail->next = this->current;
	}
	else
	{
		this->head = this->current;
	}

	this->tail = this->current;
	this->length++;

	return this->current;
}

template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::Delete(Node *index)
{

	if (this->head != index && this->tail != index)
	{
		// ���Ḯ��Ʈ���� �߰��� �ִ� ��带 ������ ��
		index->previous->next = index->next;
		index->next->previous = index->previous;
		this->current = index->next;
	}
	else if (this->head != index && this->tail == index)
	{
		// ���Ḯ��Ʈ���� ������ ��带 ������ ��
		index->previous->next = index->previous;
		this->tail = index->previous;
		this->current = index->previous;
	}
	else if (this->head == index && this->tail != index)
	{
		// ���Ḯ��Ʈ���� ó�� ��带 ������ ��
		index->next->previous = index;
		this->head = index->next;
		this->current = index->next;
	}
	else
	{
		// ���Ḯ��Ʈ���� ������ 1�� ���� ��带 ������ ��
		this->head = 0;
		this->tail = 0;
		this->current = 0;
	}

	// �Է¹��� ��ġ�� ��带 �����Ѵ�.
	if (index != 0)
	{
		delete index;
		index = 0;
	}
	this->length--;

	return index;
}


template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::DeleteFromHead()
{
	Node *index = this->head;
	
	if (this->tail != index)	// ��尡 ������ ���� ��
	{
		// ���� �� ���� ��� ���� ����
		index->next->previous = index->next;	
		this->head = index->next;	
		this->current = index->next;
	}
	else // ��尡 1�� �� ��
	{
		this->head = 0;
		this->tail = 0;
		this->current = 0;
	}

	// �� �� ��带 �����Ѵ�.
	if (index != 0)
	{
		delete index;
		index = 0;
	}
	this->length--;
	
	return index;
}


template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::DeleteFromTail()
{
	Node *index = this->tail;

	if (this->head != index)	// ��尡 ������ ���� ��
	{
		index->previous->next = index->previous;
		this->tail = index->previous;
		this->current = index->previous;
	}
	else // ��尡 1���� ���� ��
	{
		this->head = 0;
		this->tail = 0;
		this->current = 0;
	}

	// ��带 �����Ѵ�.
	if (index != 0)
	{
		delete index;
		index = 0;
	}
	this->length--;

	return index;
}

template <typename T>
void LinkedList<T>::DeleteAllItems()
{
	//���Ḯ��Ʈ�� ��� ��带 �����Ѵ�.
	Node *previous = 0;
	this->current = this->head;
	while (previous != this->current)
	{
		this->head = this->current->next;

		previous = this->current;
		if (this->current != 0)
		{
			delete this->current;
		}

		this->current = this->head;
	}

	this->head = 0;
	this->tail = 0;
	this->current = 0;
	this->length = 0;
}

template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::LinearSearchUnique(void *key, int(*compare)(void*, void*)) 
{
	Node *index = 0;
	
	Node *previous = 0;
	Node *it = this->head;

	// Ű�� ã�´�.
	while (previous != it && compare((&it->object), key) != 0)
	{
		previous = it;
		it = it->next;
	}

	// ã������ ��ġ�� �����Ѵ�.
	if (it != previous)
	{
		index = it;
	}
	
	return index;
}

template <typename T>
void LinkedList<T>::LinearSearchDuplicate(void *key,
	Node* *(*indexes), Long *count, int(*compare)(void*, void*))
{
	// ���Ḯ��Ʈ�� ��뷮 ��ŭ ����� ��ġ�� ������ �迭�� �����.
	*indexes = new Node*[this->length];
	*count = 0;
	Long i = 0;

	// ���Ḯ��Ʈ���� ã�´�.
	Node *previous = 0;
	Node *it = this->head;
	
	while (previous != it)
	{
		
		if (compare(&(it->object), key) == 0) // ã������
		{
			
			(*indexes)[i] = it; // ��ġ�� �����Ѵ�.
			i++;
			(*count)++; //������ �ø���.
		}
	
		previous = it;
		it = it->next;
	}
}

template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::First()
{
	// ���Ḯ��Ʈ���� ó�� ���� �̵��Ѵ�.
	this->current = this->head;
	return this->current;
}

template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::Previous()
{
	// ���Ḯ��Ʈ���� ���� ���� �̵��Ѵ�.
	this->current = this->current->previous;
	return this->current;
}

template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::Next()
{
	// ���Ḯ��Ʈ���� ���� ���� �̵��Ѵ�.
	this->current = this->current->next;
	return this->current;
}

template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::Last()
{
	// ���Ḯ��Ʈ���� ������ ���� �̵��Ѵ�.
	this->current = this->tail;
	return this->current;
}

template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::Move(Node *index)
{
	// ���Ḯ��Ʈ���� �Է� ���� ��ġ�� ���� �̵��Ѵ�.
	this->current = index;
	return this->current;
}

template<typename T>
T& LinkedList<T>::GetAt(Node *index)
{
	// �Է� ���� ����� ���� �����´�.
	return index->object;
}

template<typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList & source)
{
	// ������ ������ �����Ѵ�.
	Node *previous = 0;
	this->current = this->head;
	while (previous != this->current)
	{
		this->head = this->current->next;

		previous = this->current;
		if (this->current != 0)
		{
			delete this->current;
		}

		this->current = this->head;
	}

	//(��尡 1���� ���� ���� ��� ����)
	// ù ��° ��带 �߰��Ѵ�. 
	Node *it = source.head;
	this->head = new Node(it->object);
	Node *index = this->head;

	// ������ ������ �߰��Ѵ�.
	Node *next = it->next;
	while (next != it)
	{
		this->current = new Node(index, next->object);	// ���� ��� �߰�
		index->next = this->current;	// ���� ��带 ������忡 ����
		index = index->next;

		it = next;
		next = next->next;
	}

	this->tail = index;
	this->length = source.length;

	// ���� ����� ��ġ�� ���Ѵ�.
	this->current = this->head;
	it = source.head;
	while (it != source.current)
	{
		this->current = this->current->next;
		it = it->next;
	}
	return *this;
}

template <typename T>
T& LinkedList<T>::operator[](Long index)
{
	// �ش� ��ġ�� �̵��Ѵ�.
	this->current = this->head;
	
	Long i = 0;
	while (i < index)
	{
		this->current = this->current->next;
		i++;
	}

	// �ش� ��ġ�� ��带 ����Ѵ�
	return this->current->object;
}

#endif // !LINKEDLIST_H
