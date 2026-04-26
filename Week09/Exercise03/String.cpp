#include "String.h"
#include <cstring>

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

		str = nullptr;
		length = 0;
	}
	return *this;
}

String::String(const char* str) {
	this->length = strlen(str);
	this->str = new char[this->length + 1];
	strcpy(this->str, str);
}

std::ostream& operator<<(std::ostream& ostr, const String& string) {
	if (string.str == nullptr)
		return ostr << "";
	return ostr << string.str;
}

String& String::operator+=(const String& other) {
	char* largerStr = new char[length + other.length + 1];
	strcpy(largerStr, str);
	strcat(largerStr, other.str);

	delete[] str;
	str = largerStr;
	length += other.length;

	return *this;
}

char String::operator[](unsigned index) const {
	return str[index];
}

String::IndexRange::IndexRange(unsigned index) {
	start = end = index;
}

String::IndexRange& String::IndexRange::operator,(const IndexRange& rhs) {
	if (rhs.start < this->start)
		this->start = rhs.start;
	if (this->end < rhs.end)
		this->end = rhs.end;
	return *this;
}

String String::operator[](IndexRange range) const {
	if (range.end >= length)
		range.end = length - 1;
	if (range.start > range.end)
		return String();
	if (range.start == 0 && range.end == length - 1)
		return *this;

	String substr;
	substr.length = range.end - range.start + 1;
	substr.str = new char[substr.length + 1];

	strncpy(substr.str, str + range.start, substr.length);
	substr.str[substr.length] = '\0';

	return substr;
}

bool operator==(const String& lhs, const String& rhs) {
	return strcmp(lhs.str, rhs.str) == 0;
}

bool operator!=(const String& lhs, const String& rhs) {
	return !(lhs == rhs);
}

bool operator<(const String& lhs, const String& rhs) {
	return strcmp(lhs.str, rhs.str) < 0;
}

bool operator<=(const String& lhs, const String& rhs) {
	return strcmp(lhs.str, rhs.str) <= 0;
}

bool operator>(const String& lhs, const String& rhs) {
	return strcmp(lhs.str, rhs.str) > 0;
}

bool operator>=(const String& lhs, const String& rhs) {
	return strcmp(lhs.str, rhs.str) >= 0;
}

bool operator<<(const String& lhs, const String& rhs) {
	if (rhs.length > lhs.length)
		return false;
	return strcmp(lhs.str + (lhs.length - rhs.length), rhs.str) == 0;
}

bool operator>>(const String& lhs, const String& rhs) {
	if (lhs.length > rhs.length)
		return false;
	return strncmp(lhs.str, rhs.str, lhs.length) == 0;
}

String operator+(const String& lhs, const String& rhs) {
	return String(lhs) += rhs;
}
