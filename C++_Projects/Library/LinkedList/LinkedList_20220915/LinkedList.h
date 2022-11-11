#ifndef LINKEDLIST_H
#define LINKEDLIST_H

typedef signed long int Long;

template <typename T>
class LinkedList 
{
public:	//Nested Class
	class Node 
	{
		// 연결리스트 라이브러리에서 노드 멤버 접근 허용
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
	//연결리스트를 초기화 한다.
	this->head = 0;
	this->tail = 0;
	this->length = 0;
	this->current = 0;
}

template <typename T>
LinkedList<T>::LinkedList(const LinkedList &source)
{
	//(노드가 1개도 없을 경우는 사용 못함)
	// 첫 번째 노드를 추가한다. 
	Node *it = source.head;
	this->head = new Node(it->object);
	Node *index = this->head;

	// 나머지 노드들을 추가한다.
	Node *next = it->next;
	while (next != it)
	{
		this->current = new Node(index, next->object);	// 다음 노드 추가
		index->next = this->current;	// 이전 노드를 다음노드에 연결
		index = index->next;

		it = next;
		next = next->next;
	}

	this->tail = index;
	this->length = source.length;

	// 현재 노드의 위치를 구한다.
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
	//연결리스트의 모든 노드를 삭제한다.
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
	// 새로운 노드 관계 설정
	if (this->head != index)
	{
		// 받아온 위치가 처음위치가 아닐 때
		this->current = new Node(index->previous, object, index);
	}
	else
	{
		// 받아온 위치가 처음위치 일 때
		this->current = new Node(object, index);
	}
	// 나머지 관계 설정
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
	// 새로운 노드 관계 설정
	if (this->tail != index)
	{
		// 받아온 위치가 마지막이 아닐 때
		this->current = new Node(index, object, index->next);
	}
	else
	{
		// 받아온 위치가 마지막일 때
		this->current = new Node(index, object);
	}

	// 나머지 관계 설정
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

	// 새로운 노드 관계 설정
	if (this->head != 0) 
	{
		// 연결리스트에 노드가 있을 때
		// 새로운 노드를 맨 앞 노드와 연결한다.
		this->current = new Node(object, this->head);
	}
	else
	{
		// 연결리스트에 노드가 없을 때
		this->current = new Node(object);
	}

	// 나머지 관계 설정
	if (this->head != 0) 
	{
		// 연결리스트에 노드가 있을 때 
		// 기존의 맨 앞노드를 새로운 노드에 연결한다.
		this->head->previous = this->current;
	}
	else
	{
		// 연결리스트에 노드가 없을 때
		this->tail = this->current;
	}

	this->head = this->current;
	this->length++;
	
	return this->current;
}

template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::AppendFromTail(T object)
{
	// 새로운 노드 관계 설정
	if (this->tail != 0)
	{
		// 연결리스트에 노드가 있을 때
		this->current = new Node(this->tail, object);
	}
	else
	{
		// 연결리스트에 노드가 없을 때
		this->current = new Node(object);
	}

	// 나머지 관계 설정
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
		// 연결리스트에서 중간에 있는 노드를 삭제할 때
		index->previous->next = index->next;
		index->next->previous = index->previous;
		this->current = index->next;
	}
	else if (this->head != index && this->tail == index)
	{
		// 연결리스트에서 마지막 노드를 삭제할 때
		index->previous->next = index->previous;
		this->tail = index->previous;
		this->current = index->previous;
	}
	else if (this->head == index && this->tail != index)
	{
		// 연결리스트에서 처음 노드를 삭제할 때
		index->next->previous = index;
		this->head = index->next;
		this->current = index->next;
	}
	else
	{
		// 연결리스트에서 마지막 1개 남은 노드를 삭제할 때
		this->head = 0;
		this->tail = 0;
		this->current = 0;
	}

	// 입력받은 위치의 노드를 삭제한다.
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
	
	if (this->tail != index)	// 노드가 여러개 있을 때
	{
		// 삭제 할 이후 노드 관계 설정
		index->next->previous = index->next;	
		this->head = index->next;	
		this->current = index->next;
	}
	else // 노드가 1개 일 때
	{
		this->head = 0;
		this->tail = 0;
		this->current = 0;
	}

	// 맨 앞 노드를 삭제한다.
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

	if (this->head != index)	// 노드가 여러개 있을 때
	{
		index->previous->next = index->previous;
		this->tail = index->previous;
		this->current = index->previous;
	}
	else // 노드가 1개만 있을 때
	{
		this->head = 0;
		this->tail = 0;
		this->current = 0;
	}

	// 노드를 삭제한다.
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
	//연결리스트의 모든 노드를 삭제한다.
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

	// 키를 찾는다.
	while (previous != it && compare((&it->object), key) != 0)
	{
		previous = it;
		it = it->next;
	}

	// 찾았으면 위치를 저장한다.
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
	// 연결리스트의 사용량 만큼 노드의 위치를 저장할 배열을 만든다.
	*indexes = new Node*[this->length];
	*count = 0;
	Long i = 0;

	// 연결리스트에서 찾는다.
	Node *previous = 0;
	Node *it = this->head;
	
	while (previous != it)
	{
		
		if (compare(&(it->object), key) == 0) // 찾았으면
		{
			
			(*indexes)[i] = it; // 위치를 저장한다.
			i++;
			(*count)++; //개수를 늘린다.
		}
	
		previous = it;
		it = it->next;
	}
}

template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::First()
{
	// 연결리스트에서 처음 노드로 이동한다.
	this->current = this->head;
	return this->current;
}

template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::Previous()
{
	// 연결리스트에서 이전 노드로 이동한다.
	this->current = this->current->previous;
	return this->current;
}

template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::Next()
{
	// 연결리스트에서 다음 노드로 이동한다.
	this->current = this->current->next;
	return this->current;
}

template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::Last()
{
	// 연결리스트에서 마지막 노드로 이동한다.
	this->current = this->tail;
	return this->current;
}

template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::Move(Node *index)
{
	// 연결리스트에서 입력 받은 위치의 노드로 이동한다.
	this->current = index;
	return this->current;
}

template<typename T>
T& LinkedList<T>::GetAt(Node *index)
{
	// 입력 받은 노드의 값를 가져온다.
	return index->object;
}

template<typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList & source)
{
	// 이전의 노드들을 삭제한다.
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

	//(노드가 1개도 없을 경우는 사용 못함)
	// 첫 번째 노드를 추가한다. 
	Node *it = source.head;
	this->head = new Node(it->object);
	Node *index = this->head;

	// 나머지 노드들을 추가한다.
	Node *next = it->next;
	while (next != it)
	{
		this->current = new Node(index, next->object);	// 다음 노드 추가
		index->next = this->current;	// 이전 노드를 다음노드에 연결
		index = index->next;

		it = next;
		next = next->next;
	}

	this->tail = index;
	this->length = source.length;

	// 현재 노드의 위치를 구한다.
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
	// 해당 위치로 이동한다.
	this->current = this->head;
	
	Long i = 0;
	while (i < index)
	{
		this->current = this->current->next;
		i++;
	}

	// 해당 위치의 노드를 출력한다
	return this->current->object;
}

#endif // !LINKEDLIST_H
