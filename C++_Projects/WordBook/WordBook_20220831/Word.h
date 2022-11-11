#ifndef WORD_H
#define WORD_H

#include <string>
using namespace std;

class Word {

public:
	Word();
	Word(string spelling, string meaning, string wordClass, string exampleSentence);
	Word(Word & source);
	~Word();

	bool IsEqual(const Word & other);
	bool IsNotEqual(const Word & other);

	Word & operator=(const Word & source);
	bool operator==(const Word & other);
	bool operator!=(const Word & other);

	string & GetSpelling() const;
	string & GetMeaning() const;
	string & GetWordClass() const;
	string & GetExampleSentence() const;

private:
	string spelling;
	string meaning;
	string wordClass;
	string exampleSentence;
};

inline string & Word::GetSpelling() const {
	return const_cast<string &>(this->spelling);
}

inline string & Word::GetMeaning() const {
	return const_cast<string &>(this->meaning);
}

inline string & Word::GetWordClass() const {
	return const_cast<string &>(this->wordClass);
}

inline string & Word::GetExampleSentence() const {
	return const_cast<string &>(this->exampleSentence);
}

#endif // !WORD_H
