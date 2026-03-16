#ifndef _STRING
#define _STRING

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

	String(const char* str);

	unsigned GetLength();
	const char* GetStr();

	String Substring(unsigned startIndex, unsigned endIndex);
	String Concat(const String& rightHalf);
};

#endif /* _STRING */
