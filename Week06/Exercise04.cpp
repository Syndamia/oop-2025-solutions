#include <iostream>
#include <fstream>

void printFileBetweenPositions(std::ifstream& inFile, int start, int end) {
	if (start >= end)
		return;

	int original = inFile.tellg();
	inFile.seekg(start, std::ios::beg);

	while (inFile.tellg() <= end) {
		std::cout.put(inFile.get());
	}

	inFile.seekg(original, std::ios::beg);
}

int main() {
	// Във файловите системи, имената на файлове са с ограничена дължина,
	// така че и ние да работим с ограничена дължина е коректно
	char fileName[1024];
	std::cin.getline(fileName, sizeof(fileName) / sizeof(*fileName));

	std::ifstream inFile(fileName);

	if (!inFile.is_open()) {
		std::cout << "Couldn't open file!" << std::endl;
	}
	else {
		int beg = inFile.tellg();

		// seekg(0, std::ios::end) ще ни заведе в края на файла,
		// след последния байт, все едно сме отишли при терминиращата
		// нула в низ. Затова трябва да отидем с една позиция назад,
		// за да стигнем последния (съществуващ) байт във файла.
		inFile.seekg(-1, std::ios::end);
		int endOfLine = inFile.tellg();

		while (inFile.tellg() != beg) {
			if (inFile.peek() == '\n') {
				printFileBetweenPositions(inFile, (int)inFile.tellg() + 1, endOfLine);
				endOfLine = inFile.tellg();
			}
			inFile.seekg(-1, std::ios::cur);
		}

		printFileBetweenPositions(inFile, inFile.tellg(), endOfLine);
		std::cout.flush();
	}

	return 0;
}
