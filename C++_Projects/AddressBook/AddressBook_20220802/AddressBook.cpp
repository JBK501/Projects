#include "AddressBook.h"

AddressBook::AddressBook(Long capacity) :personals(capacity){

	this->capacity = capacity;
	this->length = 0;
}

AddressBook::AddressBook(const AddressBook & source) :personals(source.personals){

	this->capacity = source.capacity;
	this->length = source.length;
}

AddressBook::~AddressBook(){
}

Long AddressBook::Record(string name, string address, string telephoneNumber, string eMailAddress) {
	
	Long index; 

	Personal personal(name, address, telephoneNumber, eMailAddress);

	if (this->length < this->capacity) {	//��뷮�� �Ҵ緮���� ���� ��
		index = this->personals.Store(this->length, personal);
	}
	else {
		//��뷮�� �Ҵ緮�� ���� ��
		index = this->personals.AppendFromRear(personal);
		this->capacity++;
	}
	this->length++;

	return index;
}

void AddressBook::Find(string name, Long*(*indexes), Long *count) {
	this->personals.LinearSearchDuplicate(&name, indexes, count,CompareNames);
}

Long AddressBook::Correct(Long index, string address, string telephoneNumber, string eMailAddress) {

	//������ ��ü�� �����´�.
	Personal temp = this->personals.GetAt(index);
	
	//�����Ѵ�.
	Personal personal(temp.GetName(), address, telephoneNumber, eMailAddress);
	index = this->personals.Modify(index, personal);

	return index;
}

Long AddressBook::Erase(Long index) {

	index = this->personals.Delete(index);

	this->capacity--;
	this->length--;

	return index;
}


void AddressBook::Arrange() {
	this->personals.SelectionSort(ComparePersonals);
}


Personal & AddressBook::GetAt(Long index) {
	return this->personals.GetAt(index);
}

AddressBook & AddressBook::operator=(const AddressBook & source) {

	this->personals = source.personals;
	this->capacity = source.capacity;
	this->length = source.length;

	return *this;
}


Personal & AddressBook::operator[](Long index) {
	return this->personals[index];
}

Personal * AddressBook::operator+(Long index) {
	return this->personals + index;
}


int CompareNames(void *one, void *other) {
	return static_cast<Personal*>(one)->GetName().compare(*(static_cast<string*>(other)));
}

int ComparePersonals(void *one, void *other) {
	return static_cast<Personal*>(one)->GetName().compare(static_cast<Personal*>(other)->GetName());
}


#include<iostream>
using namespace std;

int main(int argc, char* argv[]) {

	AddressBook addressBook(3);
	Personal personal;
	Long index;
	Long(*indexes);
	Long count;
	Long i;


	cout << "Record" << endl;
	index = addressBook.Record("ȫ�浿", "����� ������", "01012345678", "hong@naver.com");
	personal = addressBook.GetAt(index);
	cout << personal.GetName() << "\t" << personal.GetAddress() << "\t" << personal.GetTelephoneNumber()
		<< "\t" << personal.GetEMailAddress() << endl;
	index = addressBook.Record("�ڱ浿", "����� ��걸", "01018394678", "park@naver.com");
	personal = addressBook.GetAt(index);
	cout << personal.GetName() << "\t" << personal.GetAddress() << "\t" << personal.GetTelephoneNumber()
		<< "\t" << personal.GetEMailAddress() << endl;
	index = addressBook.Record("ȫ�浿", "����� �߱�", "01093045648", "hong@google.com");
	personal = addressBook.GetAt(index);
	cout << personal.GetName() << "\t" << personal.GetAddress() << "\t" << personal.GetTelephoneNumber()
		<< "\t" << personal.GetEMailAddress() << endl;

	cout << endl;
	cout << "Find" << endl;

	addressBook.Find("ȫ�浿", &indexes, &count);
	i = 0;
	while (i < count) {

		cout << addressBook[indexes[i]].GetName() << "\t" << addressBook[indexes[i]].GetAddress() << "\t"
			<< addressBook[indexes[i]].GetTelephoneNumber() << "\t"
			<< addressBook[indexes[i]].GetEMailAddress() << endl;

		i++;
	}
	if (indexes != 0) {
		delete[] indexes;
	}

	cout << endl;
	cout << "Correct" << endl;
	index = addressBook.Correct(2, "����� ���빮��", "01099883344", "hong@google.com");
	personal = addressBook.GetAt(index);
	cout << personal.GetName() << "\t" << personal.GetAddress() << "\t" << personal.GetTelephoneNumber()
		<< "\t" << personal.GetEMailAddress() << endl;

	cout << endl;
	cout << "Arrange" << endl;
	
	addressBook.Arrange();
	
	i = 0;
	while (i < addressBook.GetLength()) {

		personal = addressBook.GetAt(i);

		cout << personal.GetName() << "\t" << personal.GetAddress() << "\t"<< 
			personal.GetTelephoneNumber() << personal.GetEMailAddress() << endl;
		i++;
	}

	cout << endl;
	cout << "Second AddressBook" << endl;
	
	AddressBook addressBook_(addressBook);
	i = 0;
	while (i < addressBook_.GetLength()) {

		personal = addressBook.GetAt(i);
		cout << personal.GetName() << "\t" << personal.GetAddress() << "\t" <<
			personal.GetTelephoneNumber() << personal.GetEMailAddress() << endl;
		i++;
	}


	cout << endl;
	cout << "Erase" << endl;
	
	index = addressBook_.Erase(2);
	if (index == -1) {
		cout << "���������ϴ�." << endl;
	}
	i = 0;
	while (i < addressBook_.GetLength()) {

		personal = addressBook.GetAt(i);
		cout << personal.GetName() << "\t" << personal.GetAddress() << "\t" <<
			personal.GetTelephoneNumber() << personal.GetEMailAddress() << endl;
		i++;
	}

	cout << endl;
	cout << "Third addressBook" << endl;

	AddressBook addressBook__ = addressBook;
	i = 0;
	while (i < addressBook__.GetLength()) {

		personal = addressBook__.GetAt(i);
		cout << personal.GetName() << "\t" << personal.GetAddress() << "\t" <<
			personal.GetTelephoneNumber() << personal.GetEMailAddress() << endl;
		i++;
	}

	return 0;
}
