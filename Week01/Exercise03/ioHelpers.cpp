#include <iostream>
#include "ioHelpers.h"
#include "stringHelpers.h"

int readInteger(const char* prompt, int min, int max) {
	std::cout << prompt;

	int value;
	std::cin >> value;

	while (value < min || max < value) {
		std::cout << "Value must in range [" << min << ", " << max << "]! Try again... " << std::endl;
		std::cin >> value;
	}

	return value;
}

double readDouble(const char* prompt, double min, double max) {
	std::cout << prompt;

	double value;
	std::cin >> value;

	while (value < min || max < value) {
		std::cout << "Value must in range [" << min << ", " << max << "]! Try again... " << std::endl;
		std::cin >> value;
	}

	return value;
}

char* readString(const char* prompt) {
	std::cout << prompt;

	const unsigned BUFFER_SIZE = 1024;
	char buffer[BUFFER_SIZE];

	// Когато правим "std::cin >> x", std::cin чете само нужния брой знаци за x,
	// докато std::cin.getline чете от последната позиция нататък.
	// Тоест, ако направим например "std::cin >> integerValue" и след това
	// "std::cin.getline(...)" и входа ни е "5 ABC", тогава първото std::cin
	// ще прочете само 5-цата и getline ще запише " ABC".
	// Когато обаче имаме нов ред, тоест еквивалентно на "5\nABC", тогава
	// getline ще почне да чете от "\nABC", ще види това "\n" и ще запише
	// празния низ "".
	// std::cin.peek() връща текущата буква, без да премества напред четенето,
	// std::cin.ignore() игнорира една буква (т.е. четенето продължава след нея).
	// Общо взето, това долу игнорира знак за нов ред, ако сме срещнали такъв.
	// Това оправя ситуацията, когато получаваме "First name: Last name: ".
	if (std::cin.peek() == '\n')
		std::cin.ignore();

	std::cin.getline(buffer, BUFFER_SIZE);

	return newString(buffer);
}
