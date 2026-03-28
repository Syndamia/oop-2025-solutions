#include <iostream>
#include <fstream>

struct Smartphone {
	short OSVersion;
	unsigned long long serialNumber;
	float SAR;
	char hardwareRevision;
};

int main() {
	unsigned N;
	std::cin >> N;

	std::ofstream outFile("smartphones.dat", std::ios::binary | std::ios::trunc);

	if (!outFile.is_open()) {
		std::cout << "Couldn't open file!" << std::endl;
	}
	else {
		for (unsigned i = 0; i < N; ++i) {
			Smartphone buffer;
			std::cin >> buffer.OSVersion >> buffer.serialNumber >> buffer.SAR >> buffer.hardwareRevision;
			// Мислим за този char* не като низ ами като byte*
			outFile.write((const char*)&buffer, sizeof(buffer));
		}
	}

	return 0;
}
