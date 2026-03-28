#ifndef _TEXT
#define _TEXT

#include "String.h"

class Text {
	String* lines;
	unsigned lineCount;

	void free();
	void copyFrom(const Text& other);

public:
	Text();
	~Text();
	Text(const Text& other);
	Text& operator=(const Text& other);

	Text(Text&& other);
	Text& operator=(Text&& other);

	unsigned LineCount() const;
	unsigned WordCount() const;
	Text SubText(unsigned startLine, unsigned startCol, unsigned endLine, unsigned endCol) const;
};

#endif /* _TEXT */
