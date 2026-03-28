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

	String(String&& other);
	String& operator=(String&& other);

	String(const char* str);

	bool IsTheSameAs(const String& other) const;
	const char* GetStr() const;
};

#endif /* _STRING */
