#include "BusinessCardBinder.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable:4996)


#if 0
int main(int argc, char *argv[]) {

	BusinessCardBinder businessCardBinder;
	BusinessCard *index;
	BusinessCard businessCard1 = { {"ȫ�浿","�븮","01012345678","hong@naver.com"},
	{"�Ｚ","������ ���뱸","021234567","0501123456","www.samsung.com"},NULL };
	BusinessCard businessCard2 = { {"��浿","����","01022345678","kim@naver.com"},
	{"���̹�","������ �д籸","022345678","0501433458","www.naver.com"},NULL };
	BusinessCard businessCard3 = { {"ȫ�浿","���","01042345878","hong@google.com"},
	{"LG","����� ��������","024345688","0501432158","www.lg.com"},NULL };
	BusinessCard businessCard4 = { {"�̱浿","����","01045309878","lee@google.com"},
	{"LG","����� ��������","024345688","0501432158","www.lg.com"},NULL };
	BusinessCard *(*indexes);
	Long count;
	BusinessCard businessCard;
	BusinessCard *previous;
	Long i;

	Create(&businessCardBinder);

	printf("�����ϱ�\n");
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

	printf("\n\n�����ϱ�\n");
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

	printf("\n\n��ȣ�� ã��\n");
	index = FindByCompanyName(&businessCardBinder, "���̹�");
	if (index != NULL) {
		printf("%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n", index->personal.name,
			index->personal.position, index->personal.cellphoneNumber,
			index->personal.eMailAddress, index->company.name,
			index->company.address, index->company.telephoneNumber,
			index->company.paxNumber, index->company.url);
	}

	printf("\n\nã��\n");
	Find(&businessCardBinder, "ȫ�浿", &indexes, &count);
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

	printf("\n\nù ��° �������� �̵�\n");
	index = First(&businessCardBinder);
	printf("%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n", index->personal.name,
		index->personal.position, index->personal.cellphoneNumber,
		index->personal.eMailAddress, index->company.name,
		index->company.address, index->company.telephoneNumber,
		index->company.paxNumber, index->company.url);

	printf("\n\n���� �������� �̵�\n");
	index = Next(&businessCardBinder);
	printf("%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n", index->personal.name,
		index->personal.position, index->personal.cellphoneNumber,
		index->personal.eMailAddress, index->company.name,
		index->company.address, index->company.telephoneNumber,
		index->company.paxNumber, index->company.url);

	printf("\n\n���� �������� �̵�\n");
	index = Previous(&businessCardBinder);
	printf("%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n", index->personal.name,
		index->personal.position, index->personal.cellphoneNumber,
		index->personal.eMailAddress, index->company.name,
		index->company.address, index->company.telephoneNumber,
		index->company.paxNumber, index->company.url);

	printf("\n\n�����ϱ�\n");
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

	printf("\n\n������ �������� �̵�\n");
	index = Last(&businessCardBinder);
	printf("%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n", index->personal.name,
		index->personal.position, index->personal.cellphoneNumber,
		index->personal.eMailAddress, index->company.name,
		index->company.address, index->company.telephoneNumber,
		index->company.paxNumber, index->company.url);

	printf("\n\n������ ���� ���� ������\n");
	index = Previous(&businessCardBinder);
	businessCard = TakeOut(&businessCardBinder, index);
	printf("%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n", businessCard.personal.name,
		businessCard.personal.position, businessCard.personal.cellphoneNumber,
		businessCard.personal.eMailAddress, businessCard.company.name,
		businessCard.company.address, businessCard.company.telephoneNumber,
		businessCard.company.paxNumber, businessCard.company.url);

	printf("\n\n�̵��ϱ�(ù ��°��������)\n");
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
			//ȸ�� ������ ó������
			fseek(companiesFile, 0L, SEEK_SET);

			//���� ���Ͽ��� �޾ƿ� ��ġ�� �ش��ϴ� ȸ�縦 �����´�.
			flag = fread(&company, sizeof(Company), 1, companiesFile);
			while (!feof(companiesFile) && flag != 0 && i < index) {

				i++;
				flag = fread(&company, sizeof(Company), 1, companiesFile);
			}

			//������ �����.
			businessCard.personal = personal;
			businessCard.company = company;
			businessCard.next = NULL;

			businessCardBinder->current = (BusinessCard*)malloc(sizeof(BusinessCard));
			*businessCardBinder->current = businessCard;

			//����ö�� �ִ´�.
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

	//������ ���� ��ġ�� ã�´�.
	it = businessCardBinder->first;
	while (it != NULL) {	

		previous = it;
		it = it->next;
	}

	// ������ �ִ´�.
	businessCardBinder->current = (BusinessCard*)malloc(sizeof(BusinessCard));
	*businessCardBinder->current = businessCard;

	if (previous != NULL) {	//ù ��° ������ �ƴ� ��

		previous->next = businessCardBinder->current;
	}
	else {	//ù ��° ������ ��

		businessCardBinder->first = businessCardBinder->current;
	}
	businessCardBinder->length++;

	//����Ű�� �ִ� ������ ��ġ�� ����Ѵ�.
	return businessCardBinder->current;
}

void Find(BusinessCardBinder *businessCardBinder, char(*name),
	BusinessCard* *(*indexes), Long *count) {

	BusinessCard *it;
	Long i = 0;
	*count = 0;

	//��ġ�� ������ �迭�� �Ҵ��Ѵ�.
	*indexes = (BusinessCard*(*))calloc(businessCardBinder->length, 
		sizeof(BusinessCard*));

	// ����ö���� ã�´�.
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

	//����ö���� ��ȣ�� ã�´�.
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

	//���� ������ ��ġ�� �̵��Ѵ�.
	it = businessCardBinder->first;
	while (it != index) {

		previous = it;
		it = it->next;
	}

	//���� ���Կ� ����� ���� ������ �ִٸ� 
	if (previous != NULL) {

		//���� ������ ���� ������ ���� ������ ����Ų��.
		previous->next = index->next;
	}
	//���� ������ ù ��° �����̶��
	else {

		businessCardBinder->first = it->next;
	}

	//���� ������ ������ ���� ������ ����Ų��.
	if (index->next != NULL) {

		businessCardBinder->current = index->next;
	}
	//���� ������ ������ ���� ������ ����Ų��.
	else {
		businessCardBinder->current = previous;
	}

	//������ ������.
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
			
			//�� ������ �̸��� �� ũ�ٸ�
			if (strcmp(current->personal.name, next->personal.name) > 0) {

				//ù ��° ������ ��ȯ�ϴ� ���� �ƴ϶��
				if (businessCardBinder->first != current) {

					previous->next = next;
				}
				//ù ��° ������ ��ȯ�ϴ� ���̶��
				else{
					businessCardBinder->first = next;
				}
				current->next = next->next;
				next->next = current;
				previous = next;
				next = current->next;
			}
			//�� ������ �̸��� �� �۰ų� ���ٸ�
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

	//���� �������� �̵��Ѵ�.
	it = businessCardBinder->first;
	while (it != businessCardBinder->current) {

		previous = it;
		it = it->next;
	}

	//���� ������ ������ ���� ������ ����Ų��.
	if (previous != NULL) {

		businessCardBinder->current = previous;
	}
	return businessCardBinder->current;
}

BusinessCard *Next(BusinessCardBinder *businessCardBinder) {

	BusinessCard *previous;

	previous = businessCardBinder->current;
	//���� �������� �̵��Ѵ�.
	businessCardBinder->current = businessCardBinder->current->next;

	//������ �����̾����� ����ġ�� �̵��Ѵ�.
	if (businessCardBinder->current == NULL) {

		businessCardBinder->current = previous;
	}
	return businessCardBinder->current;
}

BusinessCard *Last(BusinessCardBinder *businessCardBinder) {

	BusinessCard *previous=NULL;
	BusinessCard *it;

	//���� ����Ű�� ���Ժ��� �����ؼ� ������ ������ ã�´�.
	it = businessCardBinder->current;
	while (it != NULL) {

		previous = it;
		it = it->next;
	}
	businessCardBinder->current = previous;
	
	return businessCardBinder->current;
}

BusinessCard *Move(BusinessCardBinder *businessCardBinder, BusinessCard *index) {

	//�Է� ���� ��ġ�� �̵��Ѵ�.
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
			
			//ȸ�� ������ ù ��° ��ġ
			fseek(companiesFile, 0L, SEEK_SET);

			//���� ��ȣ�� �ִ��� ã�´�.
			flag = fread(&company, sizeof(Company), 1, companiesFile);
			while (!feof(companiesFile) && flag != 0 && 
				strcmp(current->company.name, company.name) != 0) {

				index++;
				flag = fread(&company, sizeof(Company), 1, companiesFile);
			}
			
			//���� ȸ�簡 ������ ȸ�� ���Ͽ� ���´�.
			if (flag == 0) {

				fwrite(&current->company, sizeof(Company), 1, companiesFile);
			}
			//���� ���Ͽ� ������ ���´�.
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