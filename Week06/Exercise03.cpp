#include <iostream>
#include <fstream>

int main() {
	// Във файловите системи, имената на файлове са с ограничена дължина,
	// така че и ние да работим с ограничена дължина е коректно
	char fileName[1024];
	std::cin.getline(fileName, sizeof(fileName) / sizeof(*fileName));

	std::ofstream outFile(fileName);

	if (!outFile.is_open()) {
		std::cout << "Couldn't open file!" << std::endl;
	}
	else {
		for (char curr = std::cin.get(); curr != '@'; curr = std::cin.get()) {
			outFile.put(curr);
		}
	}

	return 0;
}
