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

	String(unsigned length);
	void Copy(const char* other);

	const char* GetStr() const;
};

#endif /* _STRING */
