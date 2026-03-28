#include <iostream>
#include <fstream>

int main() {
	char fileName[1024];
	std::cin.getline(fileName, sizeof(fileName) / sizeof(*fileName));

	std::ifstream inFile(fileName, std::ios::binary);

	if (!inFile.is_open()) {
		std::cout << "Couldn't open file!" << std::endl;
	}
	else {
		inFile.seekg(0, std::ios::end);
		// Като сме отишли в края на файла с горния seekg,
		// ако вземем tellg, ще получим общия размер на файла
		// в байтове. Помним че файла се представя все едно е
		// един голям масив и g/p са индекси.
		unsigned N = inFile.tellg() / sizeof(double);
		inFile.seekg(0, std::ios::beg);

		for (unsigned i = 0; i < N; ++i) {
			double buffer;
			// Мислим за този char* не като низ ами като byte*
			inFile.read((char*)&buffer, sizeof(buffer));
			std::cout << buffer << ' ';
		}
		std::cout << std::endl;
	}

	return 0;
}
