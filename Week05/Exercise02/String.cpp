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

String String::Substring(unsigned startIndex, unsigned length) const {
	String result;
	if (startIndex >= this->length) {
		return result;
	}

	if (startIndex + length >= this->length) {
		length = this->length - startIndex;
	}

	result.length = length;
	result.str = new char[length + 1];
	strncpy(result.str, str, length);
	result.str[length + 1] = '\0';

	return result;
}

void String::Concat(const String& end) {
	char* newStr = new char[length + end.length + 1];
	strncpy(newStr, str, length);
	strncpy(newStr + length, end.str, end.length + 1);

	delete[] str;
	str = newStr;
	length += end.length;
}

unsigned String::CountWords() const {
	unsigned words = 0;
	bool prevBlank = true;

	for (const char* s = str; *s != '\0'; ++s) {
		if (prevBlank && *s != ' ')
			++words;
		prevBlank = *s == ' ';
	}

	return words;
}
