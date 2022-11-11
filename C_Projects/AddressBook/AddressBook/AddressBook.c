#include "AddressBook.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#pragma warning(disable:4996)

#if 0

int main(int argc, char*argv[]) {

	AddressBook addressBook;
	Personal personal;
	Long index;
	Long(*indexes);
	Long count;
	Long i;

	AddressBook_Create(&addressBook, 2);
	
	count = Load(&addressBook);
	i = 0;
	while (i < count) {

		personal = AddressBook_GetAt(&addressBook, i);
		printf("%s\t%s\t%s\t%s\n", personal.name, personal.address,
			personal.telephoneNumber, personal.eMailAddress);
		i++;
	}
	printf("\n\n");

	index = Record(&addressBook, "홍길동", "서울시 마포구", 
		"01012345678", "hong@naver.com");
	personal = AddressBook_GetAt(&addressBook, index);
	printf("%s\t%s\t%s\t%s\n", personal.name, personal.address,
		personal.telephoneNumber, personal.eMailAddress);

	index = Record(&addressBook, "박길동", "서울시 용산구",
		"01099876055", "park@naver.com");
	personal = AddressBook_GetAt(&addressBook, index);
	printf("%s\t%s\t%s\t%s\n", personal.name, personal.address,
		personal.telephoneNumber, personal.eMailAddress);

	index = Record(&addressBook, "홍길동", "서울시 은평구",
		"01077872895", "hong@google.com");
	personal = AddressBook_GetAt(&addressBook, index);
	printf("%s\t%s\t%s\t%s\n", personal.name, personal.address,
		personal.telephoneNumber, personal.eMailAddress);

	printf("\n\n");

	Find(&addressBook, "홍길동", &indexes, &count);
	i = 0;
	while (i < count) {
		
		personal = AddressBook_GetAt(&addressBook, indexes[i]);
		printf("%s\t%s\t%s\t%s\n", personal.name, personal.address,
			personal.telephoneNumber, personal.eMailAddress);
		i++;
	}
	if (indexes != NULL) {
		free(indexes);
	}

	printf("\n\n");
	index = Correct(&addressBook, 2, "서울시 서대문구", 
		"01069547865", "hong@google.com");
	personal = AddressBook_GetAt(&addressBook, index);
	printf("%s\t%s\t%s\t%s\n", personal.name, personal.address,
		personal.telephoneNumber, personal.eMailAddress);

	printf("\n\n");
	index = Erase(&addressBook, 2);
	if (index == -1) {
		printf("지워졌습니다.");
	}

	printf("\n\n");
	Arrange(&addressBook);
	i = 0;
	while (i < addressBook.length) {

		personal = AddressBook_GetAt(&addressBook,i);
		printf("%s\t%s\t%s\t%s\n", personal.name, personal.address,
			personal.telephoneNumber, personal.eMailAddress);
		i++;
	}

	Save(&addressBook);

	AddressBook_Destroy(&addressBook);

	return 0;
}
#endif

void AddressBook_Create(AddressBook*addressBook, Long capacity) {

	Create(&addressBook->personals, capacity, sizeof(Personal));
	addressBook->capacity = capacity;
	addressBook->length = 0;
}

Long Load(AddressBook*addressBook) {

	Personal personal;
	size_t flag;
	FILE *file;

	file = fopen("Personals.dat", "rb");
	
	if (file != NULL) {

		flag = fread(&personal, sizeof(Personal), 1, file);
		
		while (!feof(file) && flag != 0) {

			if (addressBook->length < addressBook->capacity) {

				Store(&addressBook->personals, addressBook->length,
					&personal, sizeof(Personal));
			}
			else {

				AppendFromRear(&addressBook->personals, &personal,
					sizeof(Personal));
				addressBook->capacity++;
			}
			addressBook->length++;

			flag = fread(&personal, sizeof(Personal), 1, file);
		}
		fclose(file);
	}
	return addressBook->length;
}

Personal AddressBook_GetAt(AddressBook*addressBook, Long index) {

	Personal personal;
	
	GetAt(&addressBook->personals, index, &personal, sizeof(Personal));
	
	return personal;
}

Long Record(AddressBook*addressBook, char(*name), char(*address),
	char(*telephoneNumber), char(*eMailAddress)) {

	Long index;
	Personal personal;

	strcpy(personal.name, name);
	strcpy(personal.address, address);
	strcpy(personal.telephoneNumber, telephoneNumber);
	strcpy(personal.eMailAddress, eMailAddress);

	if (addressBook->length < addressBook->capacity) {
		
		index = Store(&addressBook->personals, addressBook->length,
			&personal, sizeof(Personal));
	}
	else {

		index = AppendFromRear(&addressBook->personals, 
			&personal, sizeof(Personal));
		addressBook->capacity++;
	}
	addressBook->length++;
	
	return index;
}

void Find(AddressBook*addressBook, char(*name), Long*(*indexes),
	Long*count) {

	LinearSearchDuplicate(&addressBook->personals, name, indexes,
		count, sizeof(Personal), CompareNames);
}

Long Correct(AddressBook*addressBook, Long index, char(*address),
	char(*telephoneNumber), char(*eMailAddress)) {

	Personal personal;

	GetAt(&addressBook->personals, index, &personal, sizeof(Personal));

	strcpy(personal.address, address);
	strcpy(personal.telephoneNumber, telephoneNumber);
	strcpy(personal.eMailAddress, eMailAddress);

	index = Modify(&addressBook->personals, index,
		&personal, sizeof(Personal));

	return index;
}

Long Erase(AddressBook*addressBook, Long index) {

	index = Delete(&addressBook->personals, index,
		sizeof(Personal));

	addressBook->capacity--;
	addressBook->length--;

	return index;
}

void Arrange(AddressBook*addressBook) {
	SelectionSort(&addressBook->personals, sizeof(Personal),
		ComparePersonals);
}

Long Save(AddressBook*addressBook) {

	Personal personal;
	Long i = 0;
	FILE *file;

	file = fopen("Personals.dat", "wb");

	if (file != NULL) {

		while (i < addressBook->length) {

			GetAt(&addressBook->personals, i, &personal,
				sizeof(Personal));
			fwrite(&personal, sizeof(Personal), 1, file);
			i++;
		}
		fclose(file);
	}
	return addressBook->length;
}

void AddressBook_Destroy(AddressBook*addressBook) {
	Destroy(&addressBook->personals);
}

int CompareNames(void*one, void*other) {

	Personal*one_ = (Personal*)one;
	char(*other_) = (char*)other;

	return strcmp(one_->name, other_);
}
int ComparePersonals(void*one, void*other) {


	Personal*one_ = (Personal*)one;
	Personal*other_ = (Personal*)other;

	return strcmp(one_->name, other_->name);
}