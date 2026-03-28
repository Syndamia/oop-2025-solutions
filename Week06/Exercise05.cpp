#include <iostream>
#include <fstream>

int main() {
	char fileName[1024];
	std::cin.getline(fileName, sizeof(fileName) / sizeof(*fileName));

	unsigned N;
	std::cin >> N;

	double* numbers = new double[N];
	for (unsigned i = 0; i < N; ++i)
		std::cin >> numbers[i];

	std::ofstream outFile(fileName, std::ios::binary | std::ios::trunc);

	if (!outFile.is_open()) {
		std::cout << "Couldn't open file!" << std::endl;
	}
	else {
		for (unsigned i = 0; i < N; ++i) {
			// На практика, << конвертира подадената стойност до низ и след
			// това я подава на write.
			// Като говорим за двоични файлове, не говорим за низове и низови
			// репрезентации, т.е. искаме да запишем байтовете в паметта
			// които съставят числата (double е 64-битов, т.е. 8 байтов).
			// Припомняме си, че char типа също е 8 бита, 1 байт, тоест тук
			// трябва да мислим за char* като все едно byte*, не като низ.
			outFile.write((const char*)(numbers + i), sizeof(*numbers));
		}
	}

	delete[] numbers;
	return 0;
}
