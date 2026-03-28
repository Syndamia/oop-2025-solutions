#include "String.h"
#include <cstring>

void String::free() {
	delete[] str;
}

void String::copyFrom(const String& other) {
	length = other.length;

	// Не забравяме за терминиращата нула
	str = new char[length + 1];
	strncpy(str, other.str, length + 1);
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

String::String(const char* str) {
	length = strlen(str);
	this->str = new char[length + 1];
	strncpy(this->str, str, length + 1);
}

bool String::IsTheSameAs(const String& other) const {
	return strcmp(str, other.str) == 0;
}

const char* String::GetStr() const {
	return str;
}
