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

void String::resize() {
	allocated = allocated == 0 ? 8 : allocated * 2;
	char* strLarger = new char[allocated];

	memcpy(strLarger, str, length);
	strLarger[length] = '\0';

	delete[] str;
	str = strLarger;
}

String::String() {
	str = nullptr;
	allocated = length = 0;
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

void String::Clear() {
	free();
	str = nullptr;
	length = allocated = 0;
}

void String::AppendChar(char c) {
	if (length + 1 >= allocated)
		resize();
	str[length++] = c;
	str[length] = '\0';
}

bool String::EqualTo(const String& other) const {
	return strcmp(str, other.str) == 0;
}

const char* String::GetStr() const {
	return str;
}

unsigned String::GetLength() const {
	return length;
}
