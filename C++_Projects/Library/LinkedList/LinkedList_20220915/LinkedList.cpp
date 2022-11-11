#include "LinkedList.h"
#include <iostream>
using namespace std;

int Compare(void *one, void *other);

int main(int argc, char *argv[]) 
{
	LinkedList<Long> linkedList;

	cout << "맨 앞에 추가" << endl;
	LinkedList<Long>::Node *index = linkedList.AppendFromHead(100);
	Long number = linkedList.GetAt(index);
	cout << number << endl;

	cout << endl;
	cout << "앞에 추가" << endl;
	index = linkedList.InsertBefore(index,52);
	cout << index->GetObject() << endl;

	cout << endl;
	cout << "맨 뒤에 추가" << endl;
	index = linkedList.AppendFromTail(150);
	cout << index->GetObject() << endl;

	cout << endl;
	cout << "뒤에 추가" << endl;
	index = linkedList.InsertAfter(index, 100);
	cout << index->GetObject() << endl;

	cout << endl;
	cout << "이전 이동" << endl;
	index = linkedList.Previous();
	cout << index->GetObject() << endl;

	cout << endl;
	cout << "처음 이동" << endl;
	index = linkedList.First();
	LinkedList<Long>::Node * head = index;
	cout << index->GetObject() << endl;

	cout << endl;
	cout << "다음 이동" << endl;
	index = linkedList.Next();
	cout << index->GetObject() << endl;

	cout << endl;
	cout << "마지막 이동" << endl;
	index = linkedList.Last();
	cout << index->GetObject() << endl;

	cout << endl;
	cout << "이동하기(처음)" << endl;
	index = linkedList.Move(head);
	cout << index->GetObject() << endl;

	index = linkedList.Delete(index);
	if (index == 0)
	{
		cout << "지워졌습니다." << endl;
	}

	cout << endl;
	cout << "1개 찾기" << endl;
	number = 150;
	index = linkedList.LinearSearchUnique(&number, Compare);
	cout << index->GetObject() << endl;

	cout << endl;
	cout << "여러개 찾기" << endl;
	LinkedList<Long>::Node *(*indexes);
	Long count;
	number = 100;
	linkedList.LinearSearchDuplicate(&number, &indexes, &count, Compare);

	Long i = 0;
	while (i < count)
	{
		number = linkedList.GetAt(indexes[i]);
		cout << number << endl;
		i++;
	}
	if (indexes != 0)
	{
		delete[] indexes;
	}


	cout << endl;
	cout << "확인" << endl;
	LinkedList<Long>::Node *previous = 0;
	LinkedList<Long>::Node *it = linkedList.First();
	while (previous != it)
	{
		cout << it->GetObject() << endl;
		previous = it;
		it = linkedList.Next();
	}

	cout << endl;
	cout << "복사 생성자" << endl;
	LinkedList<Long> one(linkedList);
	
	previous = 0;
	it = one.First();
	while (previous != it)
	{
		cout << it->GetObject() << endl;
		previous = it;
		it = one.Next();
	}

	cout << endl;
	cout << "헤드 확인" << endl;
	head = linkedList.First();
	cout << head->GetObject() << endl;

	cout << endl;
	cout << "맨 앞 노드 삭제" << endl;
	index = linkedList.DeleteFromHead();
	if (index == 0)
	{
		cout << "맨 앞 노드가 삭제되었습니다." << endl;
	}

	previous = 0;
	it = linkedList.First();
	while (previous != it)
	{
		cout << it->GetObject() << endl;
		previous = it;
		it = linkedList.Next();
	}

	cout << endl;
	cout << "맨 뒤 노드 삭제" << endl;
	index = linkedList.DeleteFromTail();
	if (index == 0)
	{
		cout << "맨 뒤 노드가 삭제되었습니다." << endl;
	}

	previous = 0;
	it = linkedList.First();
	while (previous != it)
	{
		cout << it->GetObject() << endl;
		previous = it;
		it = linkedList.Next();
	}

	cout << endl;
	cout << "모든 노드 삭제" << endl;
	linkedList.DeleteAllItems();
	previous = 0;
	it = linkedList.First();
	while (previous != it)
	{
		cout << it->GetObject() << endl;
		previous = it;
		it = linkedList.Next();
	}

	cout << endl;
	cout << "치환 연산자" << endl;
	LinkedList<Long> other;
	other = one;
	previous = 0;
	it = one.First();
	while (previous != it)
	{
		cout << it->GetObject() << endl;
		previous = it;
		it = one.Next();
	}

	cout << endl;
	cout << "첨자 연산자" << endl;
	number = one[1];
	cout << number << endl;

	cout << endl;
	cout << "사용량" << endl;
	Long length = one.GetLength();
	cout << length << endl;

	cout << endl;
	cout << "현재 노드" << endl;
	index = one.GetCurrent();
	cout << index->GetObject() << endl;

	return 0;
}

int Compare(void *one, void *other)
{
	int *one_ = (int*)one;
	int *other_ = (int*)other; 
	int ret;

	if (*one_ > *other_)
	{
		ret = 1;
	}
	else if (*one_ == *other_)
	{
		ret = 0;
	}
	else if (*one_ < *other_)
	{
		ret = -1;
	}
	return ret;
}