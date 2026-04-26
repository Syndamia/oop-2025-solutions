#include "String.h"
#include <cstring>
#include <iostream>

void String::free() {
	delete[] str;
}

void String::copyFrom(const String& other) {
	length = other.length;
	// Не забравяме за терминиращата нула
	str = new char[length + 1];
	strcpy(str, other.str);
}

String::String() {
	str = nullptr;
	length = 0;
}

String::~String() {
	free();
}

String::String(const String& other) {
	copyFrom(other);
}

String& String::operator=(const String& other) {
	if (this != &other) {
		free();
		copyFrom(other);
	}
	return *this;
}

String::String(String&& other) {
	str = other.str;
	length = other.length;

	other.str = nullptr;
	other.length = 0;
}

String& String::operator=(String&& other) {
	if (this != &other) {
		free();

		str = other.str;
		length = other.length;

		other.str = nullptr;
		other.length = 0;
	}
	return *this;
}

String::String(unsigned length) {
	this->length = length;
	this->str = new char[length + 1];
	this->str[length] = '\0';
}

void String::Copy(const char* str) {
	if (this->str == nullptr) {
		length = strlen(str);
		this->str = new char[length + 1];
	}
	strncpy(this->str, str, length);
	this->str[length] = '\0';
}

const char* String::GetStr() const {
	return str;
}
