#ifndef _STRING
#define _STRING

#include <ostream>

class String {
	char* str;
	unsigned length;

	void free();
	void copyFrom(const String& other);

public:
	String();
	~String();
	String(const String& other);
	String& operator=(const String& other);

	String(String&& other);
	String& operator=(String&& other);

	// Помощни член-функции, за да тестваме String
	String(const char* str);
	friend std::ostream& operator<<(std::ostream& ostr, const String& string);

	// Каза ни са кои оператори трябва да бъдат имплементирани,
	// но както помощни функции, можем да си имплементираме и други
	// оператори
	String& operator+=(const String& other);

    char operator[](unsigned index) const;

	const char* te() const {
		return str;
	}

	struct IndexRange {
		unsigned start;
		unsigned end;

		IndexRange(unsigned index);
		IndexRange& operator,(const IndexRange& rhs);
	};
	String operator[](IndexRange range) const;

	// Алтернативно, може да създадем селектори
	// GetStr който връща str указателя и GetLength,
	// и тези функции няма да е нужно да са приятелски
	friend bool operator==(const String& lhs, const String& rhs);
	friend bool operator!=(const String& lhs, const String& rhs);
	friend bool operator<(const String& lhs, const String& rhs);
	friend bool operator<=(const String& lhs, const String& rhs);
	friend bool operator>(const String& lhs, const String& rhs);
	friend bool operator>=(const String& lhs, const String& rhs);
	friend bool operator<<(const String& lhs, const String& rhs);
	friend bool operator>>(const String& lhs, const String& rhs);
};

String operator+(const String& lhs, const String& rhs);

#endif /* _STRING */
