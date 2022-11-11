#ifndef _DATE_H
#define _DATE_H

enum Month {
	JAN = 1, FEB = 2, MAR = 3, APR = 4, MAY = 5, JUN = 6,
	JUL = 7, AUG = 8, SEP = 9, OCT = 10, NON = 11, DEC = 12
};

enum WeekDay { SUN = 0, MON = 1, TUE = 2, WED = 3, THU = 4, FRI = 5, SAT = 6 };

class Date{
	
	private:
		int year;
		Month month;
		int day;
		WeekDay weekDay;

	public:
		Date();
		Date(int year, int month, int day);
		Date(char(*date));
		Date(const Date &source);	//���� ������
		~Date();

		static	Date Today();	//static����
		Date Yesterday();
		Date Tomorrow();
		Date PreviousDate(int days);
		Date NextDate(int days);
		bool IsLessThan(const Date &other);
		bool IsGreateThan(const Date &other);
		bool IsEqual(const Date &other);
		bool IsNotEqual(const Date &other);

		int GetYear() const;
		Month GetMonth() const;
		int GetDay() const;
		WeekDay GetWeekDay() const;

		operator char*();	//�� ��ȯ �Լ�

		Date& operator--();	//������ �����ε�
		Date operator--(int);
		Date& operator++();
		Date operator++(int);
		Date operator-(int days);
		Date operator+(int days);
		bool operator<(const Date &other);
		bool operator<=(const Date &other);
		bool operator>(const Date &other);
		bool operator>=(const Date &other);
		bool operator==(const Date &other);
		bool operator!=(const Date &other);
		Date& operator=(const Date &source);
};

inline int Date::GetYear() const {
	return this->year;
}

inline  Month Date::GetMonth() const {
	return this->month;
}

inline int Date::GetDay() const {
	return this->day;
}

inline WeekDay Date::GetWeekDay() const {
	return this->weekDay;
}

#endif // !_DATE_H
