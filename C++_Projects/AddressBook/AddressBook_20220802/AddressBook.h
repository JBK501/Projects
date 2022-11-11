#ifndef _ADDRESSBOOK_H
#define _ADDRESSBOOK_H

#include "Array.h"
#include "Personal.h"
#include <string>

using namespace std;

class AddressBook{

	public:
		AddressBook(Long capacity = 100);
		AddressBook(const AddressBook & source);
		~AddressBook();
		
		Long Record(string name, string address, string telephoneNumber, string eMailAddress);
		void Find(string name, Long*(*indexes), Long *count);
		Long Correct(Long index, string address, string telephoneNumber, string eMailAddress);
		Long Erase(Long index);
		void Arrange();
		Personal & GetAt(Long index);
		
		AddressBook & operator=(const AddressBook & addressBook);
		Personal & operator[](Long index);
		Personal * operator+(Long index);

		Long GetCapacity() const;
		Long GetLength() const;

	private:
		Array<Personal> personals;
		Long capacity;
		Long length;
};

inline Long AddressBook::GetCapacity() const {
	return this->capacity;
}

inline Long AddressBook::GetLength() const {
	return this->length;
}

int CompareNames(void *one, void *other);
int ComparePersonals(void *one, void *other);

#endif // !_ADDRESSBOOK_H
