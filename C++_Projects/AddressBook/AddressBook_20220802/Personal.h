#ifndef _PERSONAL_H
#define _PERSONAL_H

#include <string>
using namespace std;

class Personal{

	public:
		Personal();
		Personal(string name, string address, string telephoneNumber, string eMailAddress);
		Personal(const Personal & source);
		~Personal();
		
		bool IsEqual(const Personal & other);
		bool IsNotEqual(const Personal & other);
		
		Personal & operator=(const Personal & source);
		bool operator ==(const Personal & other);
		bool operator !=(const Personal & other);

		string & GetName() const;
		string & GetAddress() const;
		string & GetTelephoneNumber() const;
		string & GetEMailAddress() const;

	private:
		string name;
		string address;
		string telephoneNumber;
		string eMailAddress;
};

inline string & Personal::GetName() const {
	return const_cast<string&>(this->name);
}

inline string & Personal::GetAddress() const {
	return const_cast<string&>(this->address);
}

inline string & Personal::GetTelephoneNumber() const {
	return const_cast<string&>(this->telephoneNumber);
}

inline string & Personal::GetEMailAddress() const {
	return const_cast<string&>(this->eMailAddress);
}

#endif // !_PERSONAL_H
