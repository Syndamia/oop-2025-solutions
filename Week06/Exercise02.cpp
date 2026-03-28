#include <iostream>
#include <fstream>

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
		while (inFile.peek() != EOF) {
			std::cout.put(inFile.get());
		}
		std::cout.flush();
	}

	return 0;
}
