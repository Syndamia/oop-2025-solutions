#include "Person.h"
#include <iostream>

Person::Person(const String& firstName, const String& middleName, const String& lastName, unsigned long long phoneNumber, const String& email, unsigned short birthYear, unsigned long long PN) {
	this->firstName = firstName;
	this->middleName = middleName;
	this->lastName = lastName;
	this->phoneNumber = phoneNumber;
	this->email = email;
	this->birthYear = birthYear;
	this->PN = PN;
}

const String& Person::GetFirstName() const {
	return firstName;
}

const String& Person::GetMiddleName() const {
	return middleName;
}

const String& Person::GetLastName() const {
	return lastName;
}

unsigned long long Person::GetPhoneNumber() const {
	return phoneNumber;
}

const String& Person::GetEmail() const {
	return email;
}

unsigned short Person::GetBirthYear() const {
	return birthYear;
}

unsigned long long Person::GetPN() const {
	return PN;
}
