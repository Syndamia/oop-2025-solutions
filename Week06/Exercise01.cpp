#include <iostream>
#include <fstream>

int main() {
	std::ofstream outFile("HelloWorld.txt", std::ios::trunc);

	if (!outFile.is_open()) {
		std::cout << "Couldn't open file!" << std::endl;
	}
	else {
		const char HELLO_WORLD[] = "Hello World!";
		outFile.write(HELLO_WORLD, sizeof(HELLO_WORLD) / sizeof(*HELLO_WORLD));
	}

	return 0;
}
