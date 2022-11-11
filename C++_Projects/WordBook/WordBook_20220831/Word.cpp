#include "Word.h"

Word::Word() :spelling(""), meaning(""), wordClass(""), exampleSentence("") {
}

Word::Word(string spelling, string meaning, string wordClass, string exampleSentence)
	: spelling(spelling), meaning(meaning), wordClass(wordClass), exampleSentence(exampleSentence) {
}

Word::Word(Word & source)
	: spelling(source.spelling), meaning(source.meaning), 
	wordClass(source.wordClass), exampleSentence(source.exampleSentence) {

}

Word::~Word(){}

bool Word::IsEqual(const Word & other) {

	bool ret = false;

	if (this->spelling.compare(other.spelling) == 0 && this->meaning.compare(other.meaning) == 0 &&
		this->wordClass.compare(other.wordClass) == 0 && 
		this->exampleSentence.compare(other.exampleSentence) == 0) {
		ret = true;
	}
	return ret;
}

bool Word::IsNotEqual(const Word & other) {

	bool ret = false;
	
	if (this->spelling.compare(other.spelling) != 0 || this->meaning.compare(other.meaning) != 0 ||
		this->wordClass.compare(other.wordClass) != 0 || 
		this->exampleSentence.compare(other.exampleSentence) != 0) {
		ret = true;
	}
	return ret;
}

Word & Word::operator=(const Word & source) {
	
	this->spelling = source.spelling;
	this->meaning = source.meaning;
	this->wordClass = source.wordClass;
	this->exampleSentence = source.exampleSentence;

	return *this;
}

bool Word::operator==(const Word & other) {

	bool ret = false;

	if (this->spelling.compare(other.spelling) == 0 && this->meaning.compare(other.meaning) == 0 &&
		this->wordClass.compare(other.wordClass) == 0 &&
		this->exampleSentence.compare(other.exampleSentence) == 0) {
		ret = true;
	}
	return ret;
}

bool Word::operator!=(const Word & other) {

	bool ret = false;

	if (this->spelling.compare(other.spelling) != 0 || this->meaning.compare(other.meaning) != 0 ||
		this->wordClass.compare(other.wordClass) != 0 ||
		this->exampleSentence.compare(other.exampleSentence) != 0) {
		ret = true;
	}
	return ret;
}