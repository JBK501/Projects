#include "Date.h"
#include <time.h>
#include <iostream>

using namespace std;

#pragma warning (disable : 4996)

Date::Date() {

	this->year = 1900;
	this->month = JAN;
	this->day = 1;
	this->weekDay = MON;
}

Date::Date(int year, int month, int day) {	//날짜를 입력 받을 때의 생성자

	struct tm date = { 0, };

	date.tm_year = year - 1900;
	date.tm_mon = month - 1;
	date.tm_mday = day;

	mktime(&date);

	this->year = date.tm_year + 1900;
	this->month = static_cast<Month>(date.tm_mon + 1);
	this->day = date.tm_mday;
	this->weekDay = static_cast<WeekDay>(date.tm_wday);

}

Date::Date(char(*date)) {	//문자열 형태의 날짜를 입력받을 때 생성자 ex>20220504

	struct tm dateTime;
	int year;
	int month;
	int day;

	sscanf(date, "%4d%2d%2d", &year, &month, &day);

	dateTime.tm_year = year - 1900;
	dateTime.tm_mon = month - 1;
	dateTime.tm_mday = day;

	mktime(&dateTime);

	this->year = dateTime.tm_year + 1900;
	this->month = static_cast<Month>(dateTime.tm_mon + 1);
	this->day = dateTime.tm_mday;
	this->weekDay = static_cast<WeekDay>(dateTime.tm_wday);
}

Date::Date(const Date &source) {

	this->year = source.year;
	this->month = source.month;
	this->day = source.day;
	this->weekDay = source.weekDay;
}

Date::~Date(){
}

Date Date::Today() {

	time_t timer;
	struct tm* today;
	Date today_;

	//오늘 날짜를 구한다.
	time(&timer);
	today = localtime(&timer);

	//오늘 날짜를 저장한다.
	today_.year = today->tm_year + 1900;
	today_.month = static_cast<Month>(today->tm_mon + 1);
	today_.day = today->tm_mday;
	today_.weekDay = static_cast<WeekDay>(today->tm_wday);

	return today_;
}

Date Date::Yesterday() {

	struct tm yesterday = { 0, };
	Date yesterday_;

	yesterday.tm_year = this->year - 1900;
	yesterday.tm_mon = this->month - 1;
	yesterday.tm_mday = this->day - 1;	//하루 전 이므로 -1을 한다.

	//어제 시간을 구한다.
	mktime(&yesterday);

	yesterday_.year = yesterday.tm_year + 1900;
	yesterday_.month = static_cast<Month>(yesterday.tm_mon + 1);
	yesterday_.day = yesterday.tm_mday;
	yesterday_.weekDay = static_cast<WeekDay>(yesterday.tm_wday);

	return yesterday_;
}

Date Date::Tomorrow() {

	struct tm tomorrow = { 0, };
	Date tomorrow_;

	tomorrow.tm_year = this->year - 1900;
	tomorrow.tm_mon = this->month - 1;
	tomorrow.tm_mday = this->day + 1;	//내일 시간을 구하므로 1을 더한다.

	//내일 시간을 구한다.
	mktime(&tomorrow);
	
	tomorrow_.year = tomorrow.tm_year + 1900;
	tomorrow_.month = static_cast<Month>(tomorrow.tm_mon + 1);
	tomorrow_.day = tomorrow.tm_mday;
	tomorrow_.weekDay = static_cast<WeekDay>(tomorrow.tm_wday);

	return tomorrow_;
}

Date Date::PreviousDate(int days) {

	struct  tm previousDate = { 0, };
	Date previousDate_;

	previousDate.tm_year = this->year - 1900;
	previousDate.tm_mon = this->month - 1;
	previousDate.tm_mday = this->day - days;	//days전 날짜 구하기

	mktime(&previousDate);

	previousDate_.year = previousDate.tm_year + 1900;
	previousDate_.month = static_cast<Month>(previousDate.tm_mon + 1);
	previousDate_.day = previousDate.tm_mday;
	previousDate_.weekDay = static_cast<WeekDay>(previousDate.tm_wday);

	return previousDate_;
}

Date Date::NextDate(int days) {

	struct tm nextDate = { 0, };
	Date nextDate_;

	nextDate.tm_year = this->year - 1900;
	nextDate.tm_mon = this->month - 1;
	nextDate.tm_mday = this->day + days;//days후 날짜 구하기

	mktime(&nextDate);

	nextDate_.year = nextDate.tm_year + 1900;
	nextDate_.month = static_cast<Month>(nextDate.tm_mon + 1);
	nextDate_.day = nextDate.tm_mday;
	nextDate_.weekDay = static_cast<WeekDay>(nextDate.tm_wday);

	return nextDate_;
}

bool Date::IsLessThan(const Date &other) {

	bool ret = false;

	if (this->year < other.year) {
		ret = true;
	}
	else if (this->year == other.year && this->month < other.month) {
		ret = true;
	}
	else if (this->year == other.year && this->month == other.month && this->day < other.day) {
		ret = true;
	}

	return ret;
}

bool Date::IsGreateThan(const Date &other) {

	bool ret = false;

	if (this->year > other.year) {
		ret = true;
	}
	else if (this->year == other.year && this->month > other.month) {
		ret = true;
	}
	else if (this->year == other.year && this->month == other.month && this->day > other.day) {
		ret = true;
	}

	return ret;
}

bool Date::IsEqual(const Date &other) {

	bool ret = false;

	if (this->year == other.year && this->month == other.month&&this->day == other.day) {
		ret = true;
	}

	return ret;
}

bool Date::IsNotEqual(const Date &other) {

	bool ret = false;

	if (this->year != other.year || this->month != other.month || this->day != other.day) {
		ret = true;
	}

	return ret;
}

Date::operator char*() {	//형변환 함수

	static char buffer[9];
	sprintf(buffer, "%4d%0d%0d", this->year, this->month, this->day);

	return buffer;
}

Date & Date::operator--() {

	struct tm yesterday = { 0, };

	yesterday.tm_year = this->year - 1900;
	yesterday.tm_mon = this->month - 1;
	yesterday.tm_mday = this->day - 1;

	mktime(&yesterday);

	this->year = yesterday.tm_year + 1900;
	this->month = static_cast<Month>(yesterday.tm_mon + 1);
	this->day = yesterday.tm_mday;
	this->weekDay = static_cast<WeekDay>(yesterday.tm_wday);

	return *this;
}

Date Date::operator--(int) {

	struct tm yesterday = { 0, };
	Date yesterday_(*this);

	yesterday.tm_year = this->year - 1900;
	yesterday.tm_mon = this->month - 1;
	yesterday.tm_mday = this->day - 1;

	mktime(&yesterday);

	this->year = yesterday.tm_year + 1900;
	this->month = static_cast<Month>(yesterday.tm_mon + 1);
	this->day = yesterday.tm_mday;
	this->weekDay = static_cast<WeekDay>(yesterday.tm_wday);

	return yesterday_;
}

Date & Date::operator++() {

	struct tm yesterday = { 0, };

	yesterday.tm_year = this->year - 1900;
	yesterday.tm_mon = this->month - 1;
	yesterday.tm_mday = this->day + 1;

	mktime(&yesterday);

	this->year = yesterday.tm_year + 1900;
	this->month = static_cast<Month>(yesterday.tm_mon + 1);
	this->day = yesterday.tm_mday;
	this->weekDay = static_cast<WeekDay>(yesterday.tm_wday);

	return *this;
}

Date Date::operator++(int) {

	struct tm yesterday = { 0, };
	Date yesterday_(*this);

	yesterday.tm_year = this->year - 1900;
	yesterday.tm_mon = this->month - 1;
	yesterday.tm_mday = this->day + 1;

	mktime(&yesterday);

	this->year = yesterday.tm_year + 1900;
	this->month = static_cast<Month>(yesterday.tm_mon + 1);
	this->day = yesterday.tm_mday;
	this->weekDay = static_cast<WeekDay>(yesterday.tm_wday);

	return yesterday_;
}

Date Date::operator-(int days) {

	struct tm previousDate = { 0, };
	Date previousDate_;

	previousDate.tm_year = this->year - 1900;
	previousDate.tm_mon = this->month - 1;
	previousDate.tm_mday = this->day - days;

	mktime(&previousDate);

	previousDate_.year = previousDate.tm_year + 1900;
	previousDate_.month = static_cast<Month> (previousDate.tm_mon + 1);
	previousDate_.day = previousDate.tm_mday;
	previousDate_.weekDay = static_cast<WeekDay>(previousDate.tm_wday);

	return previousDate_;
}

Date Date::operator+(int days) {

	struct tm nextDate = { 0, };
	Date nextDate_;

	nextDate.tm_year = this->year - 1900;
	nextDate.tm_mon = this->month - 1;
	nextDate.tm_mday = this->day + days;

	mktime(&nextDate);

	nextDate_.year = nextDate.tm_year + 1900;
	nextDate_.month = static_cast<Month> (nextDate.tm_mon + 1);
	nextDate_.day = nextDate.tm_mday;
	nextDate_.weekDay = static_cast<WeekDay>(nextDate.tm_wday);

	return nextDate_;
}

bool Date::operator<(const Date &other) {

	bool ret = false;

	if (this->year < other.year) {
		ret = true;
	}
	else if (this->year == other.year && this->month < other.month) {
		ret = true;
	}
	else if (this->year == other.year && this->month == other.month && this->day < other.day) {
		ret = true;
	}
	return ret;
}

bool Date::operator<=(const Date &other) {
	
	bool ret = false;

	if (this->year < other.year) {
		ret = true;
	}
	else if (this->year == other.year && this->month < other.month) {
		ret = true;
	}
	else if (this->year == other.year && this->month == other.month && this->day <= other.day) {
		ret = true;
	}
	return ret;
}

bool Date::operator>(const Date &other) {

	bool ret = false;
	if (this->year > other.year) {
		ret = true;
	}
	else if (this->year == other.year && this->month > other.month) {
		ret = true;
	}
	else if (this->year == other.year && this->month == other.month && this->day > other.day) {
		ret = true;
	}
	return ret;
}

bool Date::operator>=(const Date &other) {

	bool ret = false;
	if (this->year > other.year) {
		ret = true;
	}
	else if (this->year == other.year && this->month > other.month) {
		ret = true;
	}
	else if (this->year == other.year && this->month == other.month && this->day >= other.day) {
		ret = true;
	}
	return ret;
}

bool Date::operator==(const Date &other) {

	bool ret = false;

	if (this->year == other.year && this->month == other.month && this->day == other.day) {
		ret = true;
	}
	return ret;
}
bool Date::operator!=(const Date &other) {

	bool ret = false;

	if (this->year != other.year || this->month != other.month || this->day != other.day) {
		ret = true;
	}
	return ret;
}

Date& Date::operator=(const Date &source) {

	this->year = source.year;
	this->month = source.month;
	this->day = source.day;
	this->weekDay = source.weekDay;

	return *this;
}

#if 0
int main(int argc, char *argv) {

	Date today;
	Date yesterday;
	Date tomorrow;
	Date previousDate;
	Date nextDate;
	bool ret;

	today = Date::Today();
	cout << today.GetYear() << "-" << today.GetMonth() << "-" << today.GetDay() << endl;

	yesterday = today.Yesterday();
	cout << yesterday.GetYear() << "-" << yesterday.GetMonth() << "-" << yesterday.GetDay() << endl;

	tomorrow = today.Tomorrow();
	cout << tomorrow.GetYear() << "-" << tomorrow.GetMonth() << "-" << tomorrow.GetDay() << endl;
	
	previousDate = today.PreviousDate(1);
	cout << previousDate.GetYear() << "-" << previousDate.GetMonth() << "-" << previousDate.GetDay() << endl;

	nextDate = today.NextDate(5);
	cout << nextDate.GetYear() << "-" << nextDate.GetMonth() << "-" << nextDate.GetDay() << endl;

	cout << endl;

	ret = today.IsLessThan(nextDate);
	if (ret = true) {
		cout << "오늘은 5일 후 보다 작다." << endl;
	}

	ret = tomorrow.IsGreateThan(yesterday);
	if (ret = true) {
		cout << "내일은 어제보다 크다." << endl;
	}

	ret = yesterday.IsEqual(previousDate);
	if (ret == true) {
		cout << "어제와 1일전은 같다." << endl;
	}

	ret = tomorrow.IsNotEqual(nextDate);
	if (ret == true) {
		cout << "내일과 5일 후는 다르다." << endl;
	}

	cout << endl;
	Date birthDay(2000, MAY, 1);
	cout << birthDay.GetYear() << "-" << birthDay.GetMonth() << "-" << birthDay.GetDay() << endl;

	Date christmas((char*)"20221225");
	cout << static_cast<char*>(christmas) << endl;

	cout << endl;
	cout << "전위감소" << endl;
	Date preOrderYesterday;
	preOrderYesterday = --today;

	cout << preOrderYesterday.GetYear() << "-" << preOrderYesterday.GetMonth() << "-" <<
		preOrderYesterday.GetDay() << endl;
	cout << today.GetYear() << "-" << today.GetMonth() << "-" << today.GetDay() << endl;

	cout << endl;
	cout << "후위감소" << endl;
	Date postOrderYesterday;
	postOrderYesterday = today--;

	cout << postOrderYesterday.GetYear() << "-" << postOrderYesterday.GetMonth() << "-" 
		<< postOrderYesterday.GetDay() << endl;
	cout << today.GetYear() << "-" << today.GetMonth() << "-" << today.GetDay() << endl;

	cout << endl;
	cout << "전위증가" << endl;
	Date preOrderTomorrow;
	preOrderTomorrow = ++today;

	cout << preOrderTomorrow.GetYear() << "-" << preOrderTomorrow.GetMonth() << "-" <<
		preOrderTomorrow.GetDay() << endl;
	cout << today.GetYear() << "-" << today.GetMonth() << "-" << today.GetDay() << endl;

	cout << endl;
	cout << "후위증가" << endl;
	Date postOrderTomorrow;
	postOrderTomorrow = today++;

	cout << postOrderTomorrow.GetYear() << "-" << postOrderTomorrow.GetMonth() << "-"
		<< postOrderTomorrow.GetDay() << endl;
	cout << today.GetYear() << "-" << today.GetMonth() << "-" << today.GetDay() << endl;


	cout << endl;
	cout << "이전 날짜" << endl;
	Date opPreviousDate;
	opPreviousDate = today - 1;
	cout << opPreviousDate.GetYear() << "-" << opPreviousDate.GetMonth() << "-"
		<< opPreviousDate.GetDay() << endl;

	cout << endl;
	cout << "다음 날짜" << endl;
	Date opNextDate;
	opNextDate = today + 5;
	cout << opNextDate.GetYear() << "-" << opNextDate.GetMonth() << "-"
		<< opNextDate.GetDay() << endl;

	cout << endl;
	if (today < opNextDate) {
		cout << "오늘은 5일 후 보다 작다." << endl;
	}

	if (today <= tomorrow) {
		cout << "오늘은 내일보다 작거나 같다."<<endl;
	}
	if (today > yesterday) {
		cout << "오늘은 어제보다 크다." << endl;
	}
	if (today >= previousDate) {
		cout << "오늘은 하루 전보다 크거나 같다."<<endl;
	}
	if (yesterday >= previousDate) {
		cout << "어제는 하루 전보다 크거나 같다." << endl;
	}
	if (yesterday == previousDate) {
		cout << "오늘과 하루 전은 같다" << endl;
	}
	if (tomorrow != nextDate) {
		cout << "내일과 5일 후는 다르다." << endl;
	}

	cout << endl;
	cout << "복사생성자 테스트" << endl;
	Date afterFiveDate(nextDate);
	cout << afterFiveDate.GetYear() << "-" << afterFiveDate.GetMonth() << "-" << afterFiveDate.GetDay() << endl;

	cout << endl;
	cout << "치환연산자 테스트" << endl;
	previousDate = birthDay;
	cout << previousDate.GetYear() << "-" << previousDate.GetMonth() << "-" << previousDate.GetDay() << endl;

	return 0;
}
#endif