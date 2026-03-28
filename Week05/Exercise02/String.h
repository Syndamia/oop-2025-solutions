#ifndef _STRING
#define _STRING

class String {
	char* str;
	// Не е нужно да пазим и дължината като атрибут,
	// можем винаги да си я смятаме с strlen, но
	// е по-културно така
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

	String(const char* str);
	String Substring(unsigned startIndex, unsigned length) const;
	void Concat(const String& end);

	/* Помощна функция */

	unsigned CountWords() const;
};

#endif /* _STRING */
