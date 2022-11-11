#include "WordBook.h"

WordBook::WordBook(Long capacity) :words(capacity) {

	this->capacity = capacity;
	this->length = 0;
}

WordBook::WordBook(const WordBook & source):words(source.words) {

	this->capacity = source.capacity;
	this->length = source.length;
}

WordBook::~WordBook(){}

Long WordBook::Record(string spelling, string meaning, string wordClass, string exampleSentence) {

	Word word(spelling, meaning, wordClass, exampleSentence);
	Long index;

	if (this->length < this->capacity) {
		index = this->words.Store(this->length, word);
	}
	else {

		index = this->words.AppendFromRear(word);
		this->capacity++;
	}
	this->length++;

	return index;
}

void WordBook::FindBySpelling(string spelling, Long*(*indexes), Long *count) {
	this->words.LinearSearchDuplicate(&spelling, indexes, count, CompareSpellings);
}

void WordBook::FindByMeaning(string meaning, Long*(*indexes), Long *count) {
	this->words.LinearSearchDuplicate(&meaning, indexes, count, CompareMeanings);
}

Long WordBook::Correct(Long index, string meaning, string wordClass, string exampleSentence) {

	Word tempWord = this->words.GetAt(index);
	Word word(tempWord.GetSpelling(), meaning, wordClass, exampleSentence);

	index = this->words.Modify(index, word);

	return index;
}

Long WordBook::Erase(Long index) {

	index = this->words.Delete(index);
	this->capacity--;
	this->length--;

	return index;
}

void WordBook::Arrange() {
	this->words.SelectionSort(CompareWords);
}

Word & WordBook::GetAt(Long index) {
	return this->words.GetAt(index);
}

WordBook & WordBook::operator=(const WordBook & source) {

	this->words = source.words;
	this->capacity = source.capacity;
	this->length = source.length;

	return *this;
}

Word & WordBook::operator[](Long index) {
	return this->words[index];
}
Word * WordBook::operator+(Long index) {
	return this->words + index;
}


int CompareSpellings(void *one, void *other){
	return static_cast<Word*>(one)->GetSpelling().compare((*static_cast<string *>(other)));
}

int CompareMeanings(void *one, void *other) {
	return static_cast<Word*>(one)->GetMeaning().compare((*static_cast<string *>(other)));
}

int CompareWords(void *one, void *other) {
	return static_cast<Word*>(one)->GetSpelling().compare(static_cast<Word*>(other)->GetSpelling());
}

#include <iostream>
using namespace std;

int main(int argc, char*argv[]) {

	WordBook wordBook(3);
	Long index;
	Word word;
	Long(*indexes);
	Long count;
	Long i;


	cout << "�����ϱ�" << endl;
	index = wordBook.Record("free", "����", "���", "I am free.");
	word = wordBook.GetAt(index);
	cout << word.GetSpelling() << " " << word.GetMeaning() << " " << 
		word.GetWordClass() << " " << word.GetExampleSentence() << endl;

	index = wordBook.Record("eye", "��", "���", "Open your eyes.");
	word = wordBook.GetAt(index);
	cout << word.GetSpelling() << " " << word.GetMeaning() << " " <<
		word.GetWordClass() << " " << word.GetExampleSentence() << endl;

	index = wordBook.Record("snow", "��", "���", "The first snow of winter.");
	word = wordBook.GetAt(index);
	cout << word.GetSpelling() << " " << word.GetMeaning() << " " <<
		word.GetWordClass() << " " << word.GetExampleSentence() << endl;

	index = wordBook.Record("free", "��¥", "���", "It's free.");
	word = wordBook.GetAt(index);
	cout << word.GetSpelling() << " " << word.GetMeaning() << " " <<
		word.GetWordClass() << " " << word.GetExampleSentence() << endl;

	cout << endl;
	cout << "ö�� ã��" << endl;
	wordBook.FindBySpelling("free", &indexes, &count);
	i = 0;
	while (i < count) {

		word = wordBook.GetAt(indexes[i]);
		cout << word.GetSpelling() << " " << word.GetMeaning() << " " <<
			word.GetWordClass() << " " << word.GetExampleSentence() << endl;

		i++;
	}
	if (indexes != 0) {
		delete[] indexes;
	}

	cout << endl;
	cout << "�ǹ� ã��" << endl;
	wordBook.FindByMeaning("��", &indexes, &count);
	i = 0;
	while (i < count) {

		word = wordBook.GetAt(indexes[i]);
		cout << word.GetSpelling() << " " << word.GetMeaning() << " " <<
			word.GetWordClass() << " " << word.GetExampleSentence() << endl;

		i++;
	}
	if (indexes != 0) {
		delete[] indexes;
	}

	cout << endl;
	cout << "��ġ��" << endl;
	index = wordBook.Correct(2, "���� ������.", "����", "It's snowing.");
	word = wordBook.GetAt(index);
	cout << word.GetSpelling() << " " << word.GetMeaning() << " " <<
		word.GetWordClass() << " " << word.GetExampleSentence() << endl;

	cout << endl;
	cout << "�����" << endl;
	index = wordBook.Erase(0);
	if (index == -1) {
		cout << "���������ϴ�." << endl;
	}

	cout << endl;
	cout << "�����ϱ�" << endl;
	wordBook.Arrange();
	i = 0;
	while (i < wordBook.GetLength()) {

		word = wordBook[i];
		cout << word.GetSpelling() << " " << word.GetMeaning() << " " <<
			word.GetWordClass() << " " << word.GetExampleSentence() << endl;

		i++;
	}


	cout << endl;
	cout << "ġȯ������" << endl;
	WordBook secondWordBook = wordBook;
	i = 0;
	while (i < secondWordBook.GetLength()) {

		word = secondWordBook[i];
		cout << word.GetSpelling() << " " << word.GetMeaning() << " " <<
			word.GetWordClass() << " " << word.GetExampleSentence() << endl;

		i++;
	}

	cout << endl;
	cout << "���������" << endl;
	WordBook thirdWordBook(wordBook);
	i = 0;
	while (i < thirdWordBook.GetLength()) {

		word = thirdWordBook[i];
		cout << word.GetSpelling() << " " << word.GetMeaning() << " " <<
			word.GetWordClass() << " " << word.GetExampleSentence() << endl;

		i++;
	}

	cout << endl;
	cout << "������ ��� ������" << endl;
	Word *wordIndex = wordBook + 1;
	word = *wordIndex;
	cout << word.GetSpelling() << " " << word.GetMeaning() << " " <<
		word.GetWordClass() << " " << word.GetExampleSentence() << endl;

	return 0;
}