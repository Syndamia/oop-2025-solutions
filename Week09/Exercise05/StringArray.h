#ifndef _STRINGARRAY
#define _STRINGARRAY

#include "String.h"
#include <ostream>

// Декларация на класа, за да може в StringArray
// да си го използваме преди пълната дефиниция
class Z;

class StringArray {
	String* strings;
	unsigned stringsCount;
	unsigned stringsAlloc;

	unsigned stringsAssigned;

	void free();
	void copyFrom(const StringArray& other);
	void resize();

public:
	StringArray();
	~StringArray();
	StringArray(const StringArray& other);
	StringArray& operator=(const StringArray& other);

	StringArray(StringArray&& other);
	StringArray& operator=(StringArray&& other);

	void PushLength(unsigned length);
	void PushString(const char* str);

	StringArray& operator[](const Z& expectedNumbers);

	// Можем да създадем помощен клас "PassedStrings".
	// Обаче нямаме ограничение което задължава StringArray и
	// PassedStrings да са различни класове.
	// Можем и просто да се възползваме от StringArray,
	// и да си спестим писане на код.
	StringArray& operator()(const StringArray& strings);
	StringArray& operator()(const char* str);
	StringArray(const char* str);

	// Оператор "|" е ляво асоциативен
	StringArray& operator|(const char* str);

	// Това не е нужно по условие, но ще ни е
	// полезно за тестване.
	friend std::ostream& operator<<(std::ostream& ostr, const StringArray& sa);
};

class Z {
	unsigned* numbers;
	unsigned numbersCount;
	unsigned numbersAlloc;

	void free();
	void copyFrom(const Z& other);
	void resize();

public:
	Z();
	~Z();
	Z(const Z& other);
	Z& operator=(const Z& other);

	Z(Z&& other);
	Z& operator=(Z&& other);

	Z(unsigned num);

	Z& operator++(int);
	Z& operator+(const Z& rhs);

	friend StringArray;
};


#endif /* _STRINGARRAY */
