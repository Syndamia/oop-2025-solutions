#include "NumSeries.h"
#include <cmath>

void NumSeries::free() {
	delete[] numbers;
}

void NumSeries::copyFrom(const NumSeries& other) {
	allocated = other.allocated;
	size = other.size;

	numbers = new double[allocated];
	for (unsigned i = 0; i < size; ++i)
		numbers[i] = other.numbers[i];
}

void NumSeries::resize() {
	allocated *= 2;

	double* newNumbers = new double[allocated];
	for (unsigned i = 0; i < size; ++i)
		newNumbers[i] = numbers[i];

	delete[] numbers;
	numbers = newNumbers;
}

NumSeries::NumSeries() {
	numbers = nullptr;
	allocated = size = 0;
}

NumSeries::~NumSeries() {
	free();
}

NumSeries::NumSeries(const NumSeries& other) {
	copyFrom(other);
}

NumSeries& NumSeries::operator=(const NumSeries& other) {
	if (this != &other) {
		free();
		copyFrom(other);
	}
	return *this;
}

NumSeries::NumSeries(NumSeries&& other) {
	numbers = other.numbers;
	allocated = other.allocated;
	size = other.size;

	other.numbers = nullptr;
	other.allocated = 0;
	other.size = 0;
}

NumSeries& NumSeries::operator=(NumSeries&& other) {
	if (this != &other) {
		free();

		numbers = other.numbers;
		allocated = other.allocated;
		size = other.size;

		other.numbers = nullptr;
		other.allocated = 0;
		other.size = 0;
	}
	return *this;
}

void NumSeries::Push(double element) {
	if (size >= allocated)
		resize();
	numbers[size++] = element;
}

double NumSeries::At(unsigned index) const {
	if (index >= size)
		return NAN;
	return numbers[index];
}

unsigned NumSeries::Length() const {
	return size;
}
