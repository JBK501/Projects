#ifndef _BUSINESSCARDBINDER_H
#define _BUSINESSCARDBINDER_H

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

typedef struct _businessCard BusinessCard;

typedef struct _businessCard {

	Personal personal;
	Company company;
	BusinessCard *next;
}BusinessCard;

typedef struct _businessCardBinder {

	BusinessCard *first;
	Long length;
	BusinessCard *current;
}BusinessCardBinder;

void Create(BusinessCardBinder *businessCardBinder);
Long Load(BusinessCardBinder *businessCardBinder);
BusinessCard *TakeIn(BusinessCardBinder *businessCardBinder,
	BusinessCard businessCard);
void Find(BusinessCardBinder *businessCardBinder, char(*name),
	BusinessCard* *(*indexes), Long *count);
BusinessCard *FindByCompanyName(BusinessCardBinder *businessCardBinder,
	char(*companyName));
BusinessCard TakeOut(BusinessCardBinder *businessCardBinder,
	BusinessCard *index);
void Arrange(BusinessCardBinder *businessCardBinder);
BusinessCard *First(BusinessCardBinder *businessCardBinder);
BusinessCard *Previous(BusinessCardBinder *businessCardBinder);
BusinessCard *Next(BusinessCardBinder *businessCardBinder);
BusinessCard *Last(BusinessCardBinder *businessCardBinder);
BusinessCard *Move(BusinessCardBinder *businessCardBinder, BusinessCard *index);
Long Save(BusinessCardBinder *businessCardBinder);
void Destroy(BusinessCardBinder *businessCardBinder);

#endif // !_BUSINESSCARDBINDER_H
