#include "stringHelpers.h"

char* newString(unsigned length) {
	return new char[length + 1];
}

// Тази функция е локална: не можем да я използваме в друг файл!
unsigned stringLength(const char* string) {
	if (string == nullptr)
		return 0;

	unsigned length = 0;

	while (*string != '\0') {
		++length;
		++string;
	}

	return length;
}

char* newString(const char* string) {
	if (string == nullptr)
		return nullptr;

	unsigned length = stringLength(string);

	char* str = newString(length);

	// Правим <= length, за да пренесем и терминиращата нула
	for (unsigned i = 0; i <= length; ++i) {
		str[i] = string[i];
	}

	return str;
}

char* concatStrings(const char* first, const char* second, const char* separator) {
	unsigned length = stringLength(first) + stringLength(separator) + stringLength(second);

	char* str = newString(length);
	unsigned i = 0;

	if (first != nullptr) {
		while (*first != '\0' && i < length) {
			str[i] = *first;
			++first;
			++i;
		}
	}

	if (separator != nullptr) {
		while (*separator != '\0' && i < length) {
			str[i] = *separator;
			++separator;
			++i;
		}
	}

	if (second != nullptr) {
		while (*second != '\0' && i < length) {
			str[i] = *second;
			++second;
			++i;
		}
	}

	return str;
}

void deleteString(char*& string) {
	delete[] string;
	string = nullptr;
}
