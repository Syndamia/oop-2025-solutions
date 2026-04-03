#ifndef _STRING
#define _STRING

class String {
	char* str;
	unsigned length;
	unsigned allocated;

	void free();
	void copyFrom(const String& other);

	void resize();

public:
	String();
	~String();
	String(const String& other);
	String& operator=(const String& other);
	String(String&& other);
	String& operator=(String&& other);

	String(const char* str);
	void Clear();

	void AppendChar(char c);

	bool EqualTo(const String& other) const;

	const char* GetStr() const;
	unsigned GetLength() const;
};

#endif /* _STRING */
