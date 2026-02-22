#include "arrmath.h"

int sum(const int* elements, unsigned length) {
	if (elements == nullptr || length == 0)
		return 0;

	int sum = 0;

	for (unsigned i = 0; i < length; ++i)
		sum += elements[i];

	return sum;
}

double average(const int* elements, unsigned length) {
	if (elements == nullptr || length == 0)
		return 0.0;

	return (double)sum(elements, length) / length;
}

int largest(const int* elements, unsigned length) {
	if (elements == nullptr || length == 0)
		return 0;

	int largest = elements[0];
	for (unsigned i = 1; i < length; ++i)
		if (elements[i] > largest)
			largest = elements[i];

	return largest;
}

int smallest(const int* elements, unsigned length) {
	if (elements == nullptr || length == 0)
		return 0;

	int smallest = elements[0];
	for (unsigned i = 1; i < length; ++i)
		if (elements[i] < smallest)
			smallest = elements[i];

	return smallest;
}

unsigned findIndex(const int* elements, unsigned length, int elementToSearch) {
	if (elements == nullptr || length == 0)
		return length;

	for (unsigned i = 0; i < length; ++i)
		if (elements[i] == elementToSearch)
			return i;

	// Коректно е да връщаме length вместо 0, защото
	// 0 може да е валиден индекс в масива с елементи
	return length;
}
