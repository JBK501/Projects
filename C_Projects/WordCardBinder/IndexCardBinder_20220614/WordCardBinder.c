#include "WordCardBinder.h"
#include "IndexCard.h"
#include "IndexCardBinder.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#pragma warning (disable : 4996)

#if 0
int main(int argc, char* argv[]) {

	WordCardBinder wordCardBinder;
	WordCard wordCard1 = { {"eye","눈","명사","Open your eyes."}};
	WordCard wordCard2 = { {"pretty","예쁜","형용사","She is pretty"}};
	WordCard wordCard3 = { {"snow","눈","명사","The first show of winter!"}};
	WordCard wordCard4 = { {"park","주차하다","동사","You can't park here"}};
	WordCard wordCard5 = { {"eat","먹다","동사","I want to eat some pizza."} };
	WordCard *wordCardIndex;
	Long count;
	WordCard wordCard;
	IndexCardBinder indexCardBinder;
	IndexCard *indexCardIndex;
	IndexCard(*indexCards);
	Long i;
	Long j;
	Long index;
	
	WordCardBinder_Create(&wordCardBinder);
	IndexCardBinder_Create(&indexCardBinder);

	printf("\n\n끼우기\n");
	wordCardIndex = TakeIn(&wordCardBinder, wordCard1);
	indexCardIndex = IndexCardBinder_TakeIn(&indexCardBinder, wordCardIndex);
	printf("\n알파벳 : %c\n", indexCardIndex->alphabat);
	i = 0;
	while (i < indexCardIndex->length) {
		
		wordCardIndex = IndexCard_GetAt(indexCardIndex, i);
		printf("%s\t%s\t%s\t%s\n", wordCardIndex->word.spelling, wordCardIndex->word.meaning,
			wordCardIndex->word.wordClass, wordCardIndex->word.exampleSentence);
		i++;
	}
	wordCardIndex = TakeIn(&wordCardBinder, wordCard2);
	indexCardIndex = IndexCardBinder_TakeIn(&indexCardBinder, wordCardIndex);
	printf("\n알파벳 : %c\n", indexCardIndex->alphabat);
	i = 0;
	while (i < indexCardIndex->length) {

		wordCardIndex = IndexCard_GetAt(indexCardIndex, i);
		printf("%s\t%s\t%s\t%s\n", wordCardIndex->word.spelling, wordCardIndex->word.meaning,
			wordCardIndex->word.wordClass, wordCardIndex->word.exampleSentence);
		i++;
	}
	wordCardIndex = TakeIn(&wordCardBinder, wordCard3);
	indexCardIndex = IndexCardBinder_TakeIn(&indexCardBinder, wordCardIndex);
	printf("\n알파벳 : %c\n", indexCardIndex->alphabat);
	i = 0;
	while (i < indexCardIndex->length) {

		wordCardIndex = IndexCard_GetAt(indexCardIndex, i);
		printf("%s\t%s\t%s\t%s\n", wordCardIndex->word.spelling, wordCardIndex->word.meaning,
			wordCardIndex->word.wordClass, wordCardIndex->word.exampleSentence);
		i++;
	}
	wordCardIndex = TakeIn(&wordCardBinder, wordCard4);
	indexCardIndex = IndexCardBinder_TakeIn(&indexCardBinder, wordCardIndex);
	printf("\n알파벳 : %c\n", indexCardIndex->alphabat);
	i = 0;
	while (i < indexCardIndex->length) {

		wordCardIndex = IndexCard_GetAt(indexCardIndex, i);
		printf("%s\t%s\t%s\t%s\n", wordCardIndex->word.spelling, wordCardIndex->word.meaning,
			wordCardIndex->word.wordClass, wordCardIndex->word.exampleSentence);
		i++;
	}

	wordCardIndex = TakeIn(&wordCardBinder, wordCard5);
	indexCardIndex = IndexCardBinder_TakeIn(&indexCardBinder, wordCardIndex);
	printf("\n알파벳 : %c\n", indexCardIndex->alphabat);
	i = 0;
	while (i < indexCardIndex->length) {

		wordCardIndex = IndexCard_GetAt(indexCardIndex, i);
		printf("%s\t%s\t%s\t%s\n", wordCardIndex->word.spelling, wordCardIndex->word.meaning,
			wordCardIndex->word.wordClass, wordCardIndex->word.exampleSentence);
		i++;
	}
	
	printf("\n\n알파벳으로 찾기\n");
	indexCardIndex = IndexCardBinder_Find(&indexCardBinder, 'p');
	printf("\n알파벳 : %c\n", indexCardIndex->alphabat);
	i = 0;
	while (i < indexCardIndex->length) {

		wordCardIndex = IndexCard_GetAt(indexCardIndex, i);
		printf("%s\t%s\t%s\t%s\n", wordCardIndex->word.spelling, wordCardIndex->word.meaning,
			wordCardIndex->word.wordClass, wordCardIndex->word.exampleSentence);
		i++;
	}

	printf("\n\n첫 번째 카드 꺼내기\n");
	wordCardIndex = WordCardBinder_First(&wordCardBinder);

	wordCard = TakeOut(&wordCardBinder, wordCardIndex);
	indexCardIndex = IndexCardBinder_TakeOut(&indexCardBinder, wordCardIndex,
		wordCard.word.spelling[0]);

	if (indexCardIndex != NULL) {
		
		indexCardIndex = IndexCardBinder_Find(&indexCardBinder,wordCard.word.spelling[0]);
		printf("\n알파벳 : %c\n", indexCardIndex->alphabat);
		i = 0;
		while (i < indexCardIndex->length) {

			wordCardIndex = IndexCard_GetAt(indexCardIndex, i);
			printf("%s\t%s\t%s\t%s\n", wordCardIndex->word.spelling, wordCardIndex->word.meaning,
				wordCardIndex->word.wordClass, wordCardIndex->word.exampleSentence);
			i++;
		}
	}

	printf("\n\n리스트 만들기\n");
	IndexCardBinder_MakeList(&indexCardBinder, &indexCards, &count);
	i = 0;
	while (i < count) {
		
		printf("\n알파벳 : %c\n", indexCards[i].alphabat);
		j = 0;
		while (j < indexCards[i].length) {

			wordCardIndex = IndexCard_GetAt(indexCards+i, j);
			printf("%s\t%s\t%s\t%s\n", wordCardIndex->word.spelling, wordCardIndex->word.meaning,
				wordCardIndex->word.wordClass, wordCardIndex->word.exampleSentence);
			j++;
		}
		i++;
	}
	if (indexCards != NULL) {
		free(indexCards);
	}

	printf("\n\n정리하기\n");
	IndexCardBinder_Arrange(&indexCardBinder);
	IndexCardBinder_MakeList(&indexCardBinder, &indexCards, &count);
	i = 0;
	while (i < count) {

		printf("\n알파벳 : %c\n", indexCards[i].alphabat);
		j = 0;
		while (j < indexCards[i].length) {

			wordCardIndex = IndexCard_GetAt(indexCards + i, j);
			printf("%s\t%s\t%s\t%s\n", wordCardIndex->word.spelling, wordCardIndex->word.meaning,
				wordCardIndex->word.wordClass, wordCardIndex->word.exampleSentence);
			j++;
		}
		i++;
	}
	if (indexCards != NULL) {
		free(indexCards);
	}

	printf("\n\n뜻과 품사로 찾기\n");
	indexCardIndex = IndexCardBinder_Find(&indexCardBinder, 'p');
	index = FindByWordCardMembers(indexCardIndex, "pretty", "형용사");
	printf("\n위치 : %d", index);

	printf("\n\n철자로 찾기");
	indexCardIndex = IndexCardBinder_Find(&indexCardBinder, 'p');
	index = IndexCard_FindBySpellings(indexCardIndex, "pretty");
	printf("\n위치 : %d", index);
	


	WordCardBinder_Destroy(&wordCardBinder);
	IndexCardBinder_Destroy(&indexCardBinder);

	return 0;
}
#endif

int CompareSpellings(void *one, void *other) {

	WordCard *one_ = (WordCard*)one;
	char(*other_) = (char(*))other;

	return strcmp(one_->word.spelling, other_);
}


int CompareMeanings(void *one, void *other) {

	WordCard *one_ = (WordCard*)one;
	char(*other_) = (char(*))other;
	char(*meaning);
	char subMeaning[32] = "";
	Long meaningLength;
	
	//입력받은 문자열이 있는지 확인한다.
	meaning = strstr(one_->word.meaning, other_);
	
	if (meaning != NULL) {	//입력받은 문자열이 있다면
		
		//입력받은 문자열의 길이를 구한다.
		meaningLength = strlen(other_);
		
		//입력받은 문자열의 길이만큼 추출한다.
		strncpy(subMeaning, meaning, meaningLength);
	}

	return strcmp(other_, subMeaning);
}

int CompareIndexes(void *one, void *other) {

	Long ret;

	if (one == other) {
		ret = 0;
	}
	else {
		ret = -1;
	}
	return ret;
}

void WordCardBinder_Create(WordCardBinder *wordCardBinder) {

	Create(&wordCardBinder->wordCards);
	wordCardBinder->length = 0;
	wordCardBinder->current = NULL;
}

Long Load(WordCardBinder *wordCardBinder) {

	WordCard wordCard;
	Node *node;
	
	FILE *file;
	size_t flag;

	file = fopen("Words.dat", "rb");
	if (file != NULL) {

		flag = fread(&wordCard, sizeof(WordCard), 1, file);
		while (!feof(file), flag != 0) {

			node = AppendFromTail(&wordCardBinder->wordCards, &wordCard, sizeof(WordCard));

			wordCardBinder->current = (WordCard*)(node + 1);
			wordCardBinder->length++;

			flag = fread(&wordCard, sizeof(WordCard), 1, file);
		}
		fclose(file);
	}
	return wordCardBinder->length;
}


WordCard *TakeIn(WordCardBinder *wordCardBinder, WordCard wordCard) {

	Node *node;
	
	node = AppendFromTail(&wordCardBinder->wordCards, &wordCard, sizeof(WordCard));

	wordCardBinder->current = (WordCard*)(node + 1);
	wordCardBinder->length++;

	return wordCardBinder->current;
}

void FindBySpelling(WordCardBinder *wordCardBinder, char(*spelling),
	WordCard* *(*indexes), Long *count) {

	Node *(*nodes);
	Long i = 0;

	LinearSearchDuplicate(&wordCardBinder->wordCards, spelling, &nodes, count,
		sizeof(WordCard), CompareSpellings);

	*indexes = (WordCard*(*))calloc(wordCardBinder->length, sizeof(WordCard*));
	while (i < *count) {

		(*indexes)[i] = (WordCard*)(nodes[i] + 1);
		i++;
	}
	if (nodes != NULL) {
		free(nodes);
	}
}

void FindByMeaning(WordCardBinder *wordCardBinder, char(*meaning),
	WordCard* *(*indexes), Long *count) {

	Node *(*nodes);
	Long i = 0;

	LinearSearchDuplicate(&wordCardBinder->wordCards, meaning, &nodes, count,
		sizeof(WordCard), CompareMeanings);

	*indexes = (WordCard*(*))calloc(wordCardBinder->length, sizeof(WordCard*));
	while (i < *count) {

		(*indexes)[i] = (WordCard*)(nodes[i] + 1);
		i++;
	}
	if (nodes != NULL) {
		free(nodes);
	}
}

WordCard TakeOut(WordCardBinder *wordCardBinder, WordCard *index) {

	WordCard wordCard;
	Node *node;

	node = LinearSearchUnique(&wordCardBinder->wordCards, index,
		sizeof(wordCard), CompareIndexes);

	GetAt(&wordCardBinder->wordCards, node, &wordCard, sizeof(WordCard));

	Delete(&wordCardBinder->wordCards, node);

	node = wordCardBinder->wordCards.current;

	if (node != NULL) {
		wordCardBinder->current = (WordCard*)(node + 1);
	}
	else {
		wordCardBinder->current = NULL;
	}
	wordCardBinder->length--;

	return wordCard;
}


WordCard *WordCardBinder_First(WordCardBinder *wordCardBinder) {

	Node *node;

	node = First(&wordCardBinder->wordCards);
	wordCardBinder->current = (WordCard*)(node + 1);

	return wordCardBinder->current;
}

WordCard *WordCardBinder_Previous(WordCardBinder *wordCardBinder) {

	Node *node;

	node = Previous(&wordCardBinder->wordCards);
	wordCardBinder->current = (WordCard*)(node + 1);

	return wordCardBinder->current;
}

WordCard *WordCardBinder_Next(WordCardBinder *wordCardBinder) {

	Node *node;

	node = Next(&wordCardBinder->wordCards);
	wordCardBinder->current = (WordCard*)(node + 1);

	return wordCardBinder->current;
}

WordCard *WordCardBinder_Last(WordCardBinder *wordCardBinder) {

	Node *node;

	node = Last(&wordCardBinder->wordCards);
	wordCardBinder->current = (WordCard*)(node + 1);

	return wordCardBinder->current;
}

WordCard *WordCardBinder_Move(WordCardBinder *wordCardBinder, WordCard *index) {

	Node *node;

	node = LinearSearchUnique(&wordCardBinder->wordCards, index, 
		sizeof(WordCard), CompareIndexes);

	Move(&wordCardBinder->wordCards, node);
	wordCardBinder->current = (WordCard*)(node + 1);

	return wordCardBinder->current;
}

Long Save(WordCardBinder *wordCardBinder) {

	WordCard wordCard;
	Node *node;
	Node *previous = NULL;
	FILE *file;

	file = fopen("Words.dat", "wb");
	if (file != NULL) {

		node = First(&wordCardBinder->wordCards);
		while (node != previous) {

			GetAt(&wordCardBinder->wordCards, node, &wordCard, sizeof(WordCard));

			fwrite(&wordCard, sizeof(WordCard), 1, file);

			previous = node;
			node = Next(&wordCardBinder->wordCards);
		}
		fclose(file);
	}
	return wordCardBinder->length;
}


void WordCardBinder_Destroy(WordCardBinder *wordCardBinder) {

	Destroy(&wordCardBinder->wordCards);
}

