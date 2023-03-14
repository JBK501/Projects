#ifndef _BUSINESSCARDBINDER_H
#define _BUSINESSCARDBINDER_H

#include "LinkedList.h"

typedef signed long int Long;

typedef struct _personal {

	char name[16];
	char position[16];
	char cellphoneNumber[16];
	char eMailAddress[128];
}Personal;

typedef struct _company {

	char name[32];
	char address[64];
	char telephoneNumber[16];
	char paxNumber[16];
	char url[128];
}Company;


typedef struct _businessCard {

	Personal personal;
	Company company;
}BusinessCard;

typedef struct _businessCardBinder {

	LinkedList businessCards;
	Long length;
	BusinessCard *current;
}BusinessCardBinder;

int CompareNames(void *one, void *other);
int CompareCompanyNames(void *one, void *other);
int CompareIndexes(void *one, void *other);

void BusinessCardBinder_Create(BusinessCardBinder *businessCardBinder);
Long Load(BusinessCardBinder *businessCardBinder);
BusinessCard *TakeIn(BusinessCardBinder *businessCardBinder, BusinessCard businessCard);
void Find(BusinessCardBinder *businessCardBinder, char(*name),
	BusinessCard* *(*indexes), Long *count);
BusinessCard *FindByCompanyName(BusinessCardBinder *businessCardBinder,
	char(*companyName));
BusinessCard TakeOut(BusinessCardBinder *businessCardBinder, BusinessCard *index);
//void Arrange(BusinessCardBinder *businessCardBinder);
BusinessCard *BusinessCardBinder_First(BusinessCardBinder *businessCardBinder);
BusinessCard *BusinessCardBinder_Previous(BusinessCardBinder *businessCardBinder);
BusinessCard *BusinessCardBinder_Next(BusinessCardBinder *businessCardBinder);
BusinessCard *BusinessCardBinder_Last(BusinessCardBinder *businessCardBinder);
BusinessCard *BusinessCardBinder_Move(BusinessCardBinder *businessCardBinder, 
	BusinessCard *index);
Long Save(BusinessCardBinder *businessCardBinder);
void BusinessCardBinder_Destroy(BusinessCardBinder *businessCardBinder);

#endif // !_BUSINESSCARDBINDER_H
