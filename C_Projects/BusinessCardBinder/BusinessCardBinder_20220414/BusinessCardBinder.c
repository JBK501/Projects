#include "BusinessCardBinder.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable:4996)


#if 0
int main(int argc, char *argv[]) {

	BusinessCardBinder businessCardBinder;
	BusinessCard *index;
	BusinessCard businessCard1 = { {"홍길동","대리","01012345678","hong@naver.com"},
	{"삼성","수원시 영통구","021234567","0501123456","www.samsung.com"},NULL };
	BusinessCard businessCard2 = { {"김길동","주임","01022345678","kim@naver.com"},
	{"네이버","성남시 분당구","022345678","0501433458","www.naver.com"},NULL };
	BusinessCard businessCard3 = { {"홍길동","사원","01042345878","hong@google.com"},
	{"LG","서울시 영등포구","024345688","0501432158","www.lg.com"},NULL };
	BusinessCard businessCard4 = { {"이길동","과장","01045309878","lee@google.com"},
	{"LG","서울시 영등포구","024345688","0501432158","www.lg.com"},NULL };
	BusinessCard *(*indexes);
	Long count;
	BusinessCard businessCard;
	BusinessCard *previous;
	Long i;

	Create(&businessCardBinder);

	printf("적재하기\n");
	Load(&businessCardBinder);
	previous = NULL;
	index = First(&businessCardBinder);
	while (previous != index) {

		printf("%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n", index->personal.name,
			index->personal.position, index->personal.cellphoneNumber,
			index->personal.eMailAddress, index->company.name,
			index->company.address, index->company.telephoneNumber,
			index->company.paxNumber, index->company.url);
		previous = index;
		index = Next(&businessCardBinder);
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

	printf("\n\n상호로 찾기\n");
	index = FindByCompanyName(&businessCardBinder, "네이버");
	if (index != NULL) {
		printf("%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n", index->personal.name,
			index->personal.position, index->personal.cellphoneNumber,
			index->personal.eMailAddress, index->company.name,
			index->company.address, index->company.telephoneNumber,
			index->company.paxNumber, index->company.url);
	}

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

	printf("\n\n첫 번째 명함으로 이동\n");
	index = First(&businessCardBinder);
	printf("%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n", index->personal.name,
		index->personal.position, index->personal.cellphoneNumber,
		index->personal.eMailAddress, index->company.name,
		index->company.address, index->company.telephoneNumber,
		index->company.paxNumber, index->company.url);

	printf("\n\n다음 명함으로 이동\n");
	index = Next(&businessCardBinder);
	printf("%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n", index->personal.name,
		index->personal.position, index->personal.cellphoneNumber,
		index->personal.eMailAddress, index->company.name,
		index->company.address, index->company.telephoneNumber,
		index->company.paxNumber, index->company.url);

	printf("\n\n이전 명함으로 이동\n");
	index = Previous(&businessCardBinder);
	printf("%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n", index->personal.name,
		index->personal.position, index->personal.cellphoneNumber,
		index->personal.eMailAddress, index->company.name,
		index->company.address, index->company.telephoneNumber,
		index->company.paxNumber, index->company.url);

	printf("\n\n정리하기\n");
	Arrange(&businessCardBinder);
	previous = NULL;
	index = First(&businessCardBinder);
	while (previous != index) {

		printf("%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n", index->personal.name,
			index->personal.position, index->personal.cellphoneNumber,
			index->personal.eMailAddress, index->company.name,
			index->company.address, index->company.telephoneNumber,
			index->company.paxNumber, index->company.url);
		previous = index;
		index = Next(&businessCardBinder);
	}

	printf("\n\n마지막 명함으로 이동\n");
	index = Last(&businessCardBinder);
	printf("%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n", index->personal.name,
		index->personal.position, index->personal.cellphoneNumber,
		index->personal.eMailAddress, index->company.name,
		index->company.address, index->company.telephoneNumber,
		index->company.paxNumber, index->company.url);

	printf("\n\n마지막 이전 명함 꺼내기\n");
	index = Previous(&businessCardBinder);
	businessCard = TakeOut(&businessCardBinder, index);
	printf("%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n", businessCard.personal.name,
		businessCard.personal.position, businessCard.personal.cellphoneNumber,
		businessCard.personal.eMailAddress, businessCard.company.name,
		businessCard.company.address, businessCard.company.telephoneNumber,
		businessCard.company.paxNumber, businessCard.company.url);

	printf("\n\n이동하기(첫 번째명함으로)\n");
	index = Move(&businessCardBinder, businessCardBinder.first);
	printf("%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n", index->personal.name,
		index->personal.position, index->personal.cellphoneNumber,
		index->personal.eMailAddress, index->company.name,
		index->company.address, index->company.telephoneNumber,
		index->company.paxNumber, index->company.url);

	Save(&businessCardBinder);

	Destroy(&businessCardBinder);

	return 0;
}
#endif

void Create(BusinessCardBinder *businessCardBinder) {

	businessCardBinder->first = NULL;
	businessCardBinder->length = 0;
	businessCardBinder->current = NULL;
}

Long Load(BusinessCardBinder *businessCardBinder) {

	Personal personal;
	Company company;
	BusinessCard businessCard;
	Long index;
	BusinessCard *previous=NULL;
	Long i;
	FILE *personalsFile;
	FILE *companiesFile;
	size_t flag;

	personalsFile = fopen("Personals.dat", "rb");
	companiesFile = fopen("Companies.dat", "rb");

	if (personalsFile != NULL && companiesFile != NULL) {

		fread(&index, sizeof(Long), 1, personalsFile);
		flag = fread(&personal, sizeof(Personal), 1, personalsFile);
		while (!feof(personalsFile) && flag != 0) {

			i = 1;
			//회사 파일의 처음부터
			fseek(companiesFile, 0L, SEEK_SET);

			//개인 파일에서 받아온 위치에 해당하는 회사를 가져온다.
			flag = fread(&company, sizeof(Company), 1, companiesFile);
			while (!feof(companiesFile) && flag != 0 && i < index) {

				i++;
				flag = fread(&company, sizeof(Company), 1, companiesFile);
			}

			//명함을 만든다.
			businessCard.personal = personal;
			businessCard.company = company;
			businessCard.next = NULL;

			businessCardBinder->current = (BusinessCard*)malloc(sizeof(BusinessCard));
			*businessCardBinder->current = businessCard;

			//명함철에 넣는다.
			if (previous != NULL) {

				previous->next = businessCardBinder->current;
			}
			else {
				businessCardBinder->first = businessCardBinder->current;
			}
			businessCardBinder->length++;

			previous = businessCardBinder->current;

			fread(&index, sizeof(Long), 1, personalsFile);
			flag = fread(&personal, sizeof(Personal), 1, personalsFile);
		}
		fclose(personalsFile);
		fclose(companiesFile);
	}
	return businessCardBinder->length;
}

BusinessCard *TakeIn(BusinessCardBinder *businessCardBinder,
	BusinessCard businessCard) {

	BusinessCard *previous = NULL;
	BusinessCard *it;

	//명함을 넣을 위치를 찾는다.
	it = businessCardBinder->first;
	while (it != NULL) {	

		previous = it;
		it = it->next;
	}

	// 명함을 넣는다.
	businessCardBinder->current = (BusinessCard*)malloc(sizeof(BusinessCard));
	*businessCardBinder->current = businessCard;

	if (previous != NULL) {	//첫 번째 명함이 아닐 때

		previous->next = businessCardBinder->current;
	}
	else {	//첫 번째 명함일 때

		businessCardBinder->first = businessCardBinder->current;
	}
	businessCardBinder->length++;

	//가리키고 있는 명함의 위치를 출력한다.
	return businessCardBinder->current;
}

void Find(BusinessCardBinder *businessCardBinder, char(*name),
	BusinessCard* *(*indexes), Long *count) {

	BusinessCard *it;
	Long i = 0;
	*count = 0;

	//위치를 저장할 배열을 할당한다.
	*indexes = (BusinessCard*(*))calloc(businessCardBinder->length, 
		sizeof(BusinessCard*));

	// 명함철에서 찾는다.
	it = businessCardBinder->first;
	while (it != NULL) {

		if (strcmp(it->personal.name, name) == 0) {

			(*indexes)[i] = it;
			i++;
			(*count)++;
		}
		it = it->next;
	}
}

BusinessCard *FindByCompanyName(BusinessCardBinder *businessCardBinder,
	char(*companyName)) {

	BusinessCard *index = NULL;
	BusinessCard *it;

	//명함철에서 상호를 찾는다.
	it = businessCardBinder->first;
	while (it != NULL && strcmp(it->company.name, companyName) != 0) {
		it = it->next;
	}
	
	if (it != NULL) {
		index = it;
	}
	return index;
}

BusinessCard TakeOut(BusinessCardBinder *businessCardBinder,
	BusinessCard *index) {

	BusinessCard businessCard;
	BusinessCard *previous = NULL;
	BusinessCard *it;

	//꺼낼 명함의 위치로 이동한다.
	it = businessCardBinder->first;
	while (it != index) {

		previous = it;
		it = it->next;
	}

	//꺼낼 명함에 연결된 이전 명함이 있다면 
	if (previous != NULL) {

		//이전 명함은 꺼낼 명함의 다음 명함을 가리킨다.
		previous->next = index->next;
	}
	//꺼낼 명함이 첫 번째 명함이라면
	else {

		businessCardBinder->first = it->next;
	}

	//다음 명함이 있으면 다음 명함을 가리킨다.
	if (index->next != NULL) {

		businessCardBinder->current = index->next;
	}
	//다음 명함이 없으면 이전 명함을 가리킨다.
	else {
		businessCardBinder->current = previous;
	}

	//명함을 꺼낸다.
	businessCard = *index;
	businessCard.next = NULL;
	if (index != NULL) {

		free(index);
		index = NULL;
	}
	businessCardBinder->length--;

	return businessCard;
}

void Arrange(BusinessCardBinder *businessCardBinder) {

	BusinessCard *previous;
	BusinessCard *current;
	BusinessCard *next;
	Long i;
	Long j;

	i = businessCardBinder->length;
	while (i > 1) {

		previous = NULL;
		current = businessCardBinder->first;
		next = current->next;

		j = 1;
		while (j < i) {
			
			//앞 명함의 이름이 더 크다면
			if (strcmp(current->personal.name, next->personal.name) > 0) {

				//첫 번째 명함을 교환하는 것이 아니라면
				if (businessCardBinder->first != current) {

					previous->next = next;
				}
				//첫 번째 명함을 교환하는 것이라면
				else{
					businessCardBinder->first = next;
				}
				current->next = next->next;
				next->next = current;
				previous = next;
				next = current->next;
			}
			//앞 명함의 이름이 더 작거나 같다면
			else {

				previous = current;
				current = next;
				next = next->next;
			}
			j++;
		}
		i--;
	}
}

BusinessCard *First(BusinessCardBinder *businessCardBinder) {

	businessCardBinder->current = businessCardBinder->first;
	return businessCardBinder->current;
}

BusinessCard *Previous(BusinessCardBinder *businessCardBinder) {

	BusinessCard *previous=NULL;
	BusinessCard *it;

	//이전 명함으로 이동한다.
	it = businessCardBinder->first;
	while (it != businessCardBinder->current) {

		previous = it;
		it = it->next;
	}

	//이전 명함이 있으면 이전 명함을 가리킨다.
	if (previous != NULL) {

		businessCardBinder->current = previous;
	}
	return businessCardBinder->current;
}

BusinessCard *Next(BusinessCardBinder *businessCardBinder) {

	BusinessCard *previous;

	previous = businessCardBinder->current;
	//다음 명함으로 이동한다.
	businessCardBinder->current = businessCardBinder->current->next;

	//마지막 명함이었으면 원위치로 이동한다.
	if (businessCardBinder->current == NULL) {

		businessCardBinder->current = previous;
	}
	return businessCardBinder->current;
}

BusinessCard *Last(BusinessCardBinder *businessCardBinder) {

	BusinessCard *previous=NULL;
	BusinessCard *it;

	//현재 가리키는 명함부터 시작해서 마지막 명함을 찾는다.
	it = businessCardBinder->current;
	while (it != NULL) {

		previous = it;
		it = it->next;
	}
	businessCardBinder->current = previous;
	
	return businessCardBinder->current;
}

BusinessCard *Move(BusinessCardBinder *businessCardBinder, BusinessCard *index) {

	//입력 받은 위치로 이동한다.
	businessCardBinder->current = index;

	return businessCardBinder->current;
}

Long Save(BusinessCardBinder *businessCardBinder) {

	Long index;
	Company company;
	BusinessCard *current;

	FILE *personalsFile;
	FILE *companiesFile;
	size_t flag;

	personalsFile = fopen("Personals.dat", "wb");
	companiesFile = fopen("Companies.dat", "wb+");

	if (personalsFile != NULL && companiesFile != NULL) {

		current = businessCardBinder->first;
		while (current != NULL) {

			index = 1;
			
			//회사 파일의 첫 번째 위치
			fseek(companiesFile, 0L, SEEK_SET);

			//같은 상호가 있는지 찾는다.
			flag = fread(&company, sizeof(Company), 1, companiesFile);
			while (!feof(companiesFile) && flag != 0 && 
				strcmp(current->company.name, company.name) != 0) {

				index++;
				flag = fread(&company, sizeof(Company), 1, companiesFile);
			}
			
			//같은 회사가 없으면 회사 파일에 적는다.
			if (flag == 0) {

				fwrite(&current->company, sizeof(Company), 1, companiesFile);
			}
			//개인 파일에 개인을 적는다.
			fwrite(&index, sizeof(Long), 1, personalsFile);
			fwrite(&current->personal, sizeof(Personal), 1, personalsFile);

			current = current->next;
		}
		fclose(personalsFile);
		fclose(companiesFile);
	}
	return businessCardBinder->length;
}

void Destroy(BusinessCardBinder *businessCardBinder) {

	businessCardBinder->current = businessCardBinder->first;
	
	while (businessCardBinder->current != NULL) {

		businessCardBinder->first = businessCardBinder->current->next;

		if (businessCardBinder->current != NULL) {
			free(businessCardBinder->current);
		}

		businessCardBinder->current = businessCardBinder->first;
	}
}