#include "BusinessCardBinder.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#pragma warning (disable :4996)

#if 0
int main(int argc, char*argv[]) {

	BusinessCardBinder businessCardBinder;
	BusinessCard businessCard1 = { {"홍길동","대리","01012345678","hong@naver.com"},
	{"삼성","수원시 영통구","021234567","0501123456","www.samsung.com"} };
	BusinessCard businessCard2 = { {"김길동","주임","01022345678","kim@naver.com"},
	{"네이버","성남시 분당구","022345678","0501433458","www.naver.com"} };
	BusinessCard businessCard3 = { {"홍길동","사원","01042345878","hong@google.com"},
	{"LG","서울시 영등포구","024345688","0501432158","www.lg.com"} };
	BusinessCard businessCard4 = { {"이길동","과장","01045309878","lee@google.com"},
	{"LG","서울시 영등포구","024345688","0501432158","www.lg.com"} };
	BusinessCard *previous;
	BusinessCard *index;
	BusinessCard *(*indexes);
	Long count;
	BusinessCard businessCard;
	Long i;
	
	BusinessCardBinder_Create(&businessCardBinder);

	printf("적재하기\n");
	count = Load(&businessCardBinder);
	
	if (count != 0) {

		previous = NULL;
		index = BusinessCardBinder_First(&businessCardBinder);
		while (index != previous) {

			printf("%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n", index->personal.name,
				index->personal.position, index->personal.cellphoneNumber,
				index->personal.eMailAddress, index->company.name,
				index->company.address, index->company.telephoneNumber,
				index->company.paxNumber, index->company.url);

			previous = index;
			index = BusinessCardBinder_Next(&businessCardBinder);
		}
	}

	printf("\n\n기재하기\n");
	index = TakeIn(&businessCardBinder, businessCard1);
	printf("%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n", index->personal.name,
		index->personal.position, index->personal.cellphoneNumber,
		index->personal.eMailAddress, index->company.name,
		index->company.address, index->company.telephoneNumber,
		index->company.paxNumber, index->company.url);
	index = TakeIn(&businessCardBinder, businessCard2);
	printf("%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n", index->personal.name,
		index->personal.position, index->personal.cellphoneNumber,
		index->personal.eMailAddress, index->company.name,
		index->company.address, index->company.telephoneNumber,
		index->company.paxNumber, index->company.url);
	index = TakeIn(&businessCardBinder, businessCard3);
	printf("%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n", index->personal.name,
		index->personal.position, index->personal.cellphoneNumber,
		index->personal.eMailAddress, index->company.name,
		index->company.address, index->company.telephoneNumber,
		index->company.paxNumber, index->company.url);
	index = TakeIn(&businessCardBinder, businessCard4);
	printf("%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n", index->personal.name,
		index->personal.position, index->personal.cellphoneNumber,
		index->personal.eMailAddress, index->company.name,
		index->company.address, index->company.telephoneNumber,
		index->company.paxNumber, index->company.url);

	printf("\n\n찾기\n");
	Find(&businessCardBinder, "홍길동", &indexes, &count);
	i = 0;
	while (i < count) {

		printf("%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n", indexes[i]->personal.name,
			indexes[i]->personal.position, indexes[i]->personal.cellphoneNumber,
			indexes[i]->personal.eMailAddress, indexes[i]->company.name,
			indexes[i]->company.address, indexes[i]->company.telephoneNumber,
			indexes[i]->company.paxNumber, indexes[i]->company.url);
		i++;
	}
	if (indexes != NULL) {
		free(indexes);
	}

	printf("\n\n상호로 찾기\n");
	index = FindByCompanyName(&businessCardBinder, "네이버");
	if (index != NULL) {
		printf("%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n", index->personal.name,
			index->personal.position, index->personal.cellphoneNumber,
			index->personal.eMailAddress, index->company.name,
			index->company.address, index->company.telephoneNumber,
			index->company.paxNumber, index->company.url);
	}

	printf("\n\n첫 번째 명함으로 이동\n");
	index = BusinessCardBinder_First(&businessCardBinder);
	printf("%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n", index->personal.name,
		index->personal.position, index->personal.cellphoneNumber,
		index->personal.eMailAddress, index->company.name,
		index->company.address, index->company.telephoneNumber,
		index->company.paxNumber, index->company.url);

	printf("\n\n다음 명함으로 이동\n");
	index = BusinessCardBinder_Next(&businessCardBinder);
	printf("%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n", index->personal.name,
		index->personal.position, index->personal.cellphoneNumber,
		index->personal.eMailAddress, index->company.name,
		index->company.address, index->company.telephoneNumber,
		index->company.paxNumber, index->company.url);

	printf("\n\n이전 명함으로 이동\n");
	index = BusinessCardBinder_Previous(&businessCardBinder);
	printf("%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n", index->personal.name,
		index->personal.position, index->personal.cellphoneNumber,
		index->personal.eMailAddress, index->company.name,
		index->company.address, index->company.telephoneNumber,
		index->company.paxNumber, index->company.url);

	printf("\n\n마지막 명함으로 이동\n");
	index = BusinessCardBinder_Last(&businessCardBinder);
	printf("%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n", index->personal.name,
		index->personal.position, index->personal.cellphoneNumber,
		index->personal.eMailAddress, index->company.name,
		index->company.address, index->company.telephoneNumber,
		index->company.paxNumber, index->company.url);

	index = BusinessCardBinder_First(&businessCardBinder);
	printf("\n\n첫 번째 명함으로 이동(Move)\n");
	index = BusinessCardBinder_Move(&businessCardBinder,index);
	printf("%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n", index->personal.name,
		index->personal.position, index->personal.cellphoneNumber,
		index->personal.eMailAddress, index->company.name,
		index->company.address, index->company.telephoneNumber,
		index->company.paxNumber, index->company.url);

	printf("\n\n첫 번째 명함 꺼내기\n");
	businessCard = TakeOut(&businessCardBinder, index);
	printf("%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n", businessCard.personal.name,
		businessCard.personal.position, businessCard.personal.cellphoneNumber,
		businessCard.personal.eMailAddress, businessCard.company.name,
		businessCard.company.address, businessCard.company.telephoneNumber,
		businessCard.company.paxNumber, businessCard.company.url);

	printf("\n\n최종 결과\n");
	index = BusinessCardBinder_First(&businessCardBinder);
	i = 0;
	while (i < businessCardBinder.length) {

		printf("%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n", index->personal.name,
			index->personal.position, index->personal.cellphoneNumber,
			index->personal.eMailAddress, index->company.name,
			index->company.address, index->company.telephoneNumber,
			index->company.paxNumber, index->company.url);
		index = BusinessCardBinder_Next(&businessCardBinder);
		i++;
	}

	Save(&businessCardBinder);

	BusinessCardBinder_Destroy(&businessCardBinder);

	return 0;
}
#endif

int CompareNames(void *one, void *other) {

	BusinessCard *one_ = (BusinessCard*)one;
	char *other_ = (char*)other;

	return strcmp(one_->personal.name, other_);
}

int CompareCompanyNames(void *one, void *other) {

	BusinessCard *one_ = (BusinessCard*)one;
	char *other_ = (char*)other;

	return strcmp(one_->company.name, other_);
}

int CompareIndexes(void *one, void *other) {
	
	BusinessCard *one_ = (BusinessCard*)one;
	BusinessCard *other_ = (BusinessCard*)other;
	Long ret;

	if (one_ == other_) {
		ret = 0;
	}
	else {
		ret = -1;
	}
	
	return ret;
}

void BusinessCardBinder_Create(BusinessCardBinder *businessCardBinder) {

	Create(&businessCardBinder->businessCards);

	businessCardBinder->length = 0;
	businessCardBinder->current = NULL;
}

Long Load(BusinessCardBinder *businessCardBinder) {

	BusinessCard businessCard;
	Long index;
	Node *node;
	FILE *personalsFile;
	FILE *companiesFile;
	size_t flag;
	Long i;

	personalsFile = fopen("Personals.dat", "rb");
	companiesFile = fopen("Companies.dat", "rb");

	if (personalsFile != NULL && companiesFile != NULL) {

		fread(&index, sizeof(Long), 1, personalsFile);
		flag = fread(&businessCard.personal, sizeof(Personal), 1, personalsFile);
		while (!feof(personalsFile) && flag != 0) {

			i = 1;
			//회사 파일의 처음부터
			fseek(companiesFile, 0L, SEEK_SET);

			//개인 파일에서 받아온 위치에 해당하는 회사를 가져온다.
			flag = fread(&businessCard.company, sizeof(Company), 1, companiesFile);
			while (!feof(companiesFile) && flag != 0 && i < index) {

				i++;
				flag = fread(&businessCard.company, sizeof(Company), 1, companiesFile);
			}
			
			//명함철에 넣는다.
			node = AppendFromTail(&businessCardBinder->businessCards, &businessCard,
				sizeof(BusinessCard));
			businessCardBinder->current = (BusinessCard*)(node + 1);
			businessCardBinder->length++;

			fread(&index, sizeof(Long), 1, personalsFile);
			flag = fread(&businessCard.personal, sizeof(Personal), 1, personalsFile);
		}
		fclose(personalsFile);
		fclose(companiesFile);
	}
	return businessCardBinder->length;
}

BusinessCard *TakeIn(BusinessCardBinder *businessCardBinder, BusinessCard businessCard) {

	Node *node;

	node = 
		AppendFromTail(&businessCardBinder->businessCards, &businessCard, sizeof(BusinessCard));

	businessCardBinder->current = (BusinessCard*)(node + 1);
	businessCardBinder->length++;

	return businessCardBinder->current;

}

void Find(BusinessCardBinder *businessCardBinder, char(*name),
	BusinessCard* *(*indexes), Long *count) {

	Node *(*nodes);
	Long i = 0;

	//이름을 찾는다.(노드의 위치를 찾음)
	LinearSearchDuplicate(&businessCardBinder->businessCards, name, &nodes, count,
		sizeof(BusinessCard), CompareNames);

	//찾은 명함의 위치를 옮겨적는다.
	*indexes = (BusinessCard*(*))calloc(businessCardBinder->length, sizeof(BusinessCard*));
	while (i < *count) {

		(*indexes)[i] = (BusinessCard*)(nodes[i] + 1);
		i++;
	}

	if (nodes != NULL) {
		free(nodes);
	}
}

BusinessCard *FindByCompanyName(BusinessCardBinder *businessCardBinder,
	char(*companyName)) {

	BusinessCard *index = NULL;
	Node *node;

	node = LinearSearchUnique(&businessCardBinder->businessCards, companyName,
		sizeof(BusinessCard), CompareCompanyNames);

	//찾았으면 명함철에 있는 명함의 위치를 구한다.
	if (node != NULL) {
		index = (BusinessCard*)(node + 1);
	}

	return index;
}

BusinessCard TakeOut(BusinessCardBinder *businessCardBinder, BusinessCard *index) {

	Node *node;
	BusinessCard businessCard;

	//노드를 구한다
	node = LinearSearchUnique(&businessCardBinder->businessCards,
		index, sizeof(BusinessCard*), CompareIndexes);

	//객체(명함)를 꺼낸다
	GetAt(&businessCardBinder->businessCards, node, &businessCard, sizeof(BusinessCard));

	//객체(명함)를 삭제한다.
	Delete(&businessCardBinder->businessCards, node);

	node = businessCardBinder->businessCards.current;

	//명함철에서 현재위치를 저장한다.
	if (node != NULL) {

		businessCardBinder->current = (BusinessCard*)(node + 1);
	}
	else {

		businessCardBinder->current = NULL;
	}
	businessCardBinder->length--;

	return businessCard;
}

BusinessCard *BusinessCardBinder_First(BusinessCardBinder *businessCardBinder) {

	Node *node;

	node = First(&businessCardBinder->businessCards);

	businessCardBinder->current = (BusinessCard*)(node + 1);

	return businessCardBinder->current;
}

BusinessCard *BusinessCardBinder_Previous(BusinessCardBinder *businessCardBinder) {

	Node *node;

	node = Previous(&businessCardBinder->businessCards);

	businessCardBinder->current = (BusinessCard*)(node + 1);

	return businessCardBinder->current;
}

BusinessCard *BusinessCardBinder_Next(BusinessCardBinder *businessCardBinder) {

	Node *node;

	node = Next(&businessCardBinder->businessCards);

	businessCardBinder->current = (BusinessCard*)(node + 1);

	return businessCardBinder->current;
}

BusinessCard *BusinessCardBinder_Last(BusinessCardBinder *businessCardBinder) {

	Node *node;

	node = Last(&businessCardBinder->businessCards);

	businessCardBinder->current = (BusinessCard*)(node + 1);

	return businessCardBinder->current;
}

BusinessCard *BusinessCardBinder_Move(BusinessCardBinder *businessCardBinder,
	BusinessCard *index) {

	Node *node;
	
	node = LinearSearchUnique(&businessCardBinder->businessCards,
		index, sizeof(BusinessCard*), CompareIndexes);

	businessCardBinder->current = (BusinessCard*)(node + 1);

	return businessCardBinder->current;
}

Long Save(BusinessCardBinder *businessCardBinder) {

	BusinessCard businessCard;
	Long index;
	Company company;
	Node *node;
	Node *previous = NULL;
	FILE *personalsFile;
	FILE *companiesFile;
	size_t flag;

	personalsFile = fopen("Personals.dat", "wb");
	companiesFile = fopen("Companies.dat", "wb+");

	if (personalsFile != NULL && companiesFile != NULL) {

		node = First(&businessCardBinder->businessCards);
		while (node != previous) {

			index = 1;
			//회사 파일의 첫 번째 위치
			fseek(companiesFile, 0L, SEEK_SET);

			//같은 상호가 있는지 찾는다.
			GetAt(&businessCardBinder->businessCards, node, &businessCard, sizeof(BusinessCard));
			flag = fread(&company, sizeof(Company), 1, companiesFile);
			while (!feof(companiesFile) && flag != 0 &&
				strcmp(businessCard.company.name, company.name) != 0) {

				index++;
				flag = fread(&company, sizeof(Company), 1, companiesFile);
			}

			//같은 회사가 없으면 회사 파일에 적는다.
			if (flag == 0) {

				fwrite(&businessCard.company, sizeof(Company), 1, companiesFile);
			}

			//개인 파일에 개인을 적는다.
			fwrite(&index, sizeof(Long), 1, personalsFile);
			fwrite(&businessCard.personal, sizeof(Personal), 1, personalsFile);

			previous = node;
			node = Next(&businessCardBinder->businessCards);
		}
		fclose(personalsFile);
		fclose(companiesFile);
	}
	return businessCardBinder->length;
}

void BusinessCardBinder_Destroy(BusinessCardBinder *businessCardBinder) {

	Destroy(&businessCardBinder->businessCards);
}
