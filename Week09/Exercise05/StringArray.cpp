#include "StringArray.h"

/* StringArray клас */

void StringArray::free() {
	delete[] strings;
}

void StringArray::copyFrom(const StringArray& other) {
	stringsCount = other.stringsCount;
	stringsAlloc = other.stringsAlloc;
	stringsAssigned = other.stringsAssigned;

	strings = new String[stringsAlloc];
	for (unsigned i = 0; i < stringsCount; ++i)
		strings[i] = other.strings[i];
}

void StringArray::resize() {
	stringsAlloc = stringsAlloc == 0 ? 8 : stringsAlloc * 2;
	String* stringsLarger = new String[stringsAlloc];

	for (unsigned i = 0; i < stringsCount; ++i)
		stringsLarger[i] = strings[i];

	delete[] strings;
	strings = stringsLarger;
}

StringArray::StringArray() {
	strings = nullptr;
	stringsCount = stringsAlloc = stringsAssigned = 0;
}

StringArray::~StringArray() {
	free();
}

StringArray::StringArray(const StringArray& other) {
	copyFrom(other);
}

StringArray& StringArray::operator=(const StringArray& other) {
	if (this != &other) {
		free();
		copyFrom(other);
	}
	return *this;
}

StringArray::StringArray(StringArray&& other) {
	strings = other.strings;
	stringsCount = other.stringsCount;
	stringsAlloc = other.stringsAlloc;
	stringsAssigned = other.stringsAssigned;

	other.strings = nullptr;
	other.stringsCount = other.stringsAlloc = other.stringsAssigned = 0;
}

StringArray& StringArray::operator=(StringArray&& other) {
	if (this != &other) {
		free();

		strings = other.strings;
		stringsCount = other.stringsCount;
		stringsAlloc = other.stringsAlloc;
		stringsAssigned = other.stringsAssigned;

		other.strings = nullptr;
		other.stringsCount = other.stringsAlloc = other.stringsAssigned = 0;
	}
	return *this;
}

void StringArray::PushLength(unsigned length) {
	if (stringsCount >= stringsAlloc)
		resize();
	strings[stringsCount++] = String(length);
}

void StringArray::PushString(const char* str) {
	if (stringsAssigned >= stringsAlloc)
		resize();
	strings[stringsAssigned++].Copy(str);

	if (stringsAssigned > stringsCount)
		stringsCount = stringsAssigned;
}

StringArray& StringArray::operator[](const Z& expectedNumbers) {
	for (unsigned i = 0; i < expectedNumbers.numbersCount; ++i) {
		PushLength(expectedNumbers.numbers[i]);
	}
	return *this;
}

StringArray& StringArray::operator()(const StringArray& strings) {
	for (unsigned i = 0; i < strings.stringsAssigned; ++i) {
		PushString(strings.strings[i].GetStr());
	}
	return *this;
}

StringArray& StringArray::operator()(const char* str) {
	PushString(str);
	return *this;
}

StringArray::StringArray(const char* str) : StringArray() {
	PushString(str);
}

StringArray& StringArray::operator|(const char* str) {
	PushString(str);
	return *this;
}

// Това не е нужно по условие, но ще ни е
// полезно за тестване.
std::ostream& operator<<(std::ostream& ostr, const StringArray& sa) {
	for (unsigned i = 0; i < sa.stringsAssigned; ++i)
		ostr << sa.strings[i].GetStr() << std::endl;
	return ostr;
}

/* Z клас (помощен) */

void Z::free() {
	delete[] numbers;
}

void Z::copyFrom(const Z& other) {
	numbersCount = other.numbersCount;
	numbersAlloc = other.numbersAlloc;

	numbers = new unsigned[numbersAlloc];
	for (unsigned i = 0; i < numbersCount; ++i)
		numbers[i] = other.numbers[i];
}

void Z::resize() {
	numbersAlloc = numbersAlloc == 0 ? 8 : numbersAlloc * 2;
	unsigned* numbersLarger = new unsigned[numbersAlloc];

	for (unsigned i = 0; i < numbersCount; ++i)
		numbersLarger[i] = numbers[i];

	delete[] numbers;
	numbers = numbersLarger;
}

Z::Z() {
	numbers = nullptr;
	numbersCount = numbersAlloc = 0;
}

Z::~Z() {
	free();
}

Z::Z(const Z& other) {
	copyFrom(other);
}

Z& Z::operator=(const Z& other) {
	if (this != &other) {
		free();
		copyFrom(other);
	}
	return *this;
}

Z::Z(Z&& other) {
	numbers = other.numbers;
	numbersAlloc = other.numbersAlloc;
	numbersCount = other.numbersCount;

	other.numbers = nullptr;
	other.numbersCount = other.numbersAlloc = 0;
}

Z& Z::operator=(Z&& other) {
	if (this != &other) {
		free();

		numbers = other.numbers;
		numbersAlloc = other.numbersAlloc;
		numbersCount = other.numbersCount;

		other.numbers = nullptr;
		other.numbersCount = other.numbersAlloc = 0;
	}
	return *this;
}

Z::Z(unsigned number) {
	numbersAlloc = 8;
	numbersCount = 1;
	numbers = new unsigned[numbersAlloc];
	numbers[0] = number;
}

// Това е един метод да имплементираме operator++ и operator+,
// където с ++ все едно подсказваме че ще добавяме елемент и с
// + се добавя елемента.
// Валидно е и ++ да не върши нищо и цялата логика да е в +.
// Но така задължаваме употребата на "+++".

Z& Z::operator++(int) {
	if (numbersCount + 1 >= numbersAlloc)
		resize();
	return *this;
}

Z& Z::operator+(const Z& rhs) {
	for (unsigned i = 0; i < rhs.numbersCount && numbersCount < numbersAlloc; ++i)
		numbers[numbersCount++] = rhs.numbers[i];
	return *this;
}
