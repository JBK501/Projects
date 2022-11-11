#include "Personal.h"

Personal::Personal() :name(""), address(""), telephoneNumber(""), eMailAddress("") {
}

Personal::Personal(string name, string address, string telephoneNumber, string eMailAddress)
	: name(name), address(address), telephoneNumber(telephoneNumber), eMailAddress(eMailAddress) {

}

Personal::Personal(const Personal &source)
	: name(source.name), address(source.address), telephoneNumber(source.telephoneNumber),
	eMailAddress(source.eMailAddress) {

}

Personal::~Personal(){
}

bool Personal::IsEqual(const Personal & other) {
	
	bool ret = false;

	if (this->name.compare(other.name) == 0 && this->address.compare(other.address) == 0 &&
		this->telephoneNumber.compare(other.telephoneNumber) == 0 &&
		this->eMailAddress.compare(other.eMailAddress) == 0) {
		ret = true;
	}
	return ret;
}

bool Personal::IsNotEqual(const Personal & other) {

	bool ret = false;

	if (this->name.compare(other.name) != 0 || this->address.compare(other.address) != 0 ||
		this->telephoneNumber.compare(other.telephoneNumber) != 0 ||
		this->eMailAddress.compare(other.eMailAddress) != 0) {
		ret = true;
	}
	return ret;
}

Personal & Personal::operator=(const Personal & source) {

	this->name = source.name;
	this->address = source.address;
	this->telephoneNumber = source.telephoneNumber;
	this->eMailAddress = source.eMailAddress;

	return *this;
}

bool Personal::operator==(const Personal & other) {

	bool ret = false;

	if (this->name.compare(other.name) == 0 && this->address.compare(other.address) == 0 &&
		this->telephoneNumber.compare(other.telephoneNumber) == 0 &&
		this->eMailAddress.compare(other.eMailAddress) == 0) {
		ret = true;
	}
	return ret;
}

bool Personal::operator!=(const Personal & other) {

	bool ret = false;

	if (this->name.compare(other.name) != 0 || this->address.compare(other.address) != 0 ||
		this->telephoneNumber.compare(other.telephoneNumber) != 0 ||
		this->eMailAddress.compare(other.eMailAddress) != 0) {
		ret = true;
	}
	return ret;
}


#if 0

#include <iostream>
using namespace std;

int main(int argc, char* argv[]) {

	Personal one("홍길동","서울시 마포구","01012345678","hong@naver.com");
	cout << one.GetName() << "\t" << one.GetAddress() << "\t" <<
		one.GetTelephoneNumber() << "\t" << one.GetEMailAddress() << endl;

	Personal other("김길동", "서울시 용산구", "01088873033", "kim@naver.com");
	cout << other.GetName() << "\t" << other.GetAddress() << "\t" <<
		other.GetTelephoneNumber() << "\t" << other.GetEMailAddress() << endl;

	Personal one_(one);
	cout << one_.GetName() << "\t" << one_.GetAddress() << "\t" <<
		one_.GetTelephoneNumber() << "\t" << one_.GetEMailAddress() << endl;

	Personal other_ = other;
	cout << other_.GetName() << "\t" << other_.GetAddress() << "\t" <<
		other_.GetTelephoneNumber() << "\t" << other_.GetEMailAddress() << endl;


	bool ret = one.IsEqual(one_);
	if (ret == true) {
		cout << "같다." << endl;
	}
	
	ret = one.IsNotEqual(other);
	if (ret == true) {
		cout << "다르다." << endl;
	}

	if (other == other_) {
		cout << "같다." << endl;
	}

	if (one != other) {
		cout << "다르다." << endl;
	}

	return 0;
}

#endif