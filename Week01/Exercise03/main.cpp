#include <iostream>
#include "ioHelpers.h"
#include "stringHelpers.h"

int main() {
	// Нямаме ограничение на броя студенти, затова просто ще сложим максимума
	// да е най-голямата стойност за 32-битов signed integer: 2^31 - 1
	// По-коректно е да се ползват специални константи, които пазят максималната
	// стойност на отделните типове данни, защото на стар компютър, int може да
	// не е 32 бита.
	unsigned numStudents = readInteger("Number of students: ", 0, 2147483647);

	double* grades = new double[numStudents];
	char** names = new char*[numStudents];

	for (unsigned i = 0; i < numStudents; ++i) {
		char* firstName = readString("First name: ");
		char* lastName = readString("Last name: ");

		names[i] = concatStrings(firstName, lastName, " ");

		deleteString(firstName);
		deleteString(lastName);

		double grade = readDouble("Grade: ", 2.0, 6.0);

		grades[i] = grade;
	}

	for (unsigned i = 0; i < numStudents; ++i) {
		std::cout << names[i] << " has grade " << grades[i] << std::endl;
	}

	delete[] grades;
	for (unsigned i = 0; i < numStudents; ++i)
		deleteString(names[i]);
	delete[] names;

	return 0;
}
