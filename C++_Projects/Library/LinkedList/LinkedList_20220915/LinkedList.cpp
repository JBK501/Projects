#include "LinkedList.h"
#include <iostream>
using namespace std;

int Compare(void *one, void *other);

int main(int argc, char *argv[]) 
{
	LinkedList<Long> linkedList;

	cout << "�� �տ� �߰�" << endl;
	LinkedList<Long>::Node *index = linkedList.AppendFromHead(100);
	Long number = linkedList.GetAt(index);
	cout << number << endl;

	cout << endl;
	cout << "�տ� �߰�" << endl;
	index = linkedList.InsertBefore(index,52);
	cout << index->GetObject() << endl;

	cout << endl;
	cout << "�� �ڿ� �߰�" << endl;
	index = linkedList.AppendFromTail(150);
	cout << index->GetObject() << endl;

	cout << endl;
	cout << "�ڿ� �߰�" << endl;
	index = linkedList.InsertAfter(index, 100);
	cout << index->GetObject() << endl;

	cout << endl;
	cout << "���� �̵�" << endl;
	index = linkedList.Previous();
	cout << index->GetObject() << endl;

	cout << endl;
	cout << "ó�� �̵�" << endl;
	index = linkedList.First();
	LinkedList<Long>::Node * head = index;
	cout << index->GetObject() << endl;

	cout << endl;
	cout << "���� �̵�" << endl;
	index = linkedList.Next();
	cout << index->GetObject() << endl;

	cout << endl;
	cout << "������ �̵�" << endl;
	index = linkedList.Last();
	cout << index->GetObject() << endl;

	cout << endl;
	cout << "�̵��ϱ�(ó��)" << endl;
	index = linkedList.Move(head);
	cout << index->GetObject() << endl;

	index = linkedList.Delete(index);
	if (index == 0)
	{
		cout << "���������ϴ�." << endl;
	}

	cout << endl;
	cout << "1�� ã��" << endl;
	number = 150;
	index = linkedList.LinearSearchUnique(&number, Compare);
	cout << index->GetObject() << endl;

	cout << endl;
	cout << "������ ã��" << endl;
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
	cout << "Ȯ��" << endl;
	LinkedList<Long>::Node *previous = 0;
	LinkedList<Long>::Node *it = linkedList.First();
	while (previous != it)
	{
		cout << it->GetObject() << endl;
		previous = it;
		it = linkedList.Next();
	}

	cout << endl;
	cout << "���� ������" << endl;
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
	cout << "��� Ȯ��" << endl;
	head = linkedList.First();
	cout << head->GetObject() << endl;

	cout << endl;
	cout << "�� �� ��� ����" << endl;
	index = linkedList.DeleteFromHead();
	if (index == 0)
	{
		cout << "�� �� ��尡 �����Ǿ����ϴ�." << endl;
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
	cout << "�� �� ��� ����" << endl;
	index = linkedList.DeleteFromTail();
	if (index == 0)
	{
		cout << "�� �� ��尡 �����Ǿ����ϴ�." << endl;
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
	cout << "��� ��� ����" << endl;
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
	cout << "ġȯ ������" << endl;
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
	cout << "÷�� ������" << endl;
	number = one[1];
	cout << number << endl;

	cout << endl;
	cout << "��뷮" << endl;
	Long length = one.GetLength();
	cout << length << endl;

	cout << endl;
	cout << "���� ���" << endl;
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