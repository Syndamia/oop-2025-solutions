#include "String.h"
#include "string.h"

void String::free() {
	delete[] str;
}
void String::copyFrom(const String& other) {
	length = other.length;

	// Не забравяме за терминиращата нула!
	str = new char[length + 1];
	for (unsigned i = 0; i <= length; ++i)
		str[i] = other.str[i];
}

String::String() {
	length = 0;
	str = new char[1];
	str[0] = '\0';
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

String::String(const char* str) {
	length = strlen(str);

	this->str = new char[length + 1];
	for (unsigned i = 0; i <= length; ++i)
		this->str[i] = str[i];
}

unsigned String::GetLength() {
	return length;
}

const char* String::GetStr() {
	return str;
}

String String::Substring(unsigned startIndex, unsigned endIndex) {
	if (endIndex >= length)
		endIndex = length - 1;

	String ret;
	// Не забравяме за терминиращата нула!
	ret.length = endIndex - startIndex + 2;

	ret.str = new char[ret.length];
	for (unsigned i = 0; i <= ret.length; ++i)
		ret.str[i] = this->str[i + startIndex];

	return ret;
}

String String::Concat(const String& rightHalf) {
	String ret;
	// Не забравяме за терминиращата нула!
	ret.length = length + rightHalf.length + 1;

	ret.str = new char[ret.length];
	for (unsigned i = 0; i < length; ++i)
		ret.str[i] = this->str[i];
	for (unsigned i = 0; i <= rightHalf.length; ++i)
		ret.str[i + length] = this->str[i];

	return ret;
}
