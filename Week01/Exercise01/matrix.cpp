#include "matrix.h"

int** newMatrix(unsigned rows, unsigned cols) {
	int** mat = new int*[rows];

	for (unsigned i = 0; i < rows; ++i)
		mat[i] = new int[cols];

	return mat;
}

void deleteMatrix(int**& matrix, unsigned rows) {
	for (unsigned i = 0; i < rows; ++i)
		delete[] matrix[i];
	delete[] matrix;

	matrix = nullptr;
}

int sumMatrix(const int** matrix, unsigned rows, unsigned cols) {
	int sum = 0;

	for (unsigned row = 0; row < rows; ++row)
		for (unsigned col = 0; col < cols; ++col)
			sum += matrix[row][col];

	return sum;
}
