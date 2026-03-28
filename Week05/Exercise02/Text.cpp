#include "Text.h"

void Text::free() {
	delete[] lines;
}

void Text::copyFrom(const Text& other) {
	lineCount = other.lineCount;

	lines = new String[lineCount];
	for (unsigned i = 0; i < lineCount; ++i)
		lines[i] = other.lines[i];
}

Text::Text() {
	lines = nullptr;
	lineCount = 0;
}

Text::~Text() {
	free();
}

Text::Text(const Text& other) {
	copyFrom(other);
}

Text& Text::operator=(const Text& other) {
	if (this != &other) {
		free();
		copyFrom(other);
	}
	return *this;
}

Text::Text(Text&& other) {
	lines = other.lines;
	lineCount = other.lineCount;

	other.lines = nullptr;
	other.lineCount = 0;
}

unsigned Text::LineCount() const {
	return lineCount;
}

unsigned Text::WordCount() const {
	unsigned totalCount = 0;

	for (unsigned i = 0; i < lineCount; ++i)
		totalCount += lines[i].CountWords();

	return totalCount;
}

Text Text::SubText(unsigned startLine, unsigned startCol, unsigned endLine, unsigned endCol) const {
	Text result;
	result.lineCount = endLine - startLine + 1;
	result.lines = new String[lineCount];

	for (unsigned i = 0; i < result.lineCount; ++i) {
		result.lines[i] = lines[i + startLine].Substring(startCol, endCol - startCol + 1);
	}

	return result;
}
