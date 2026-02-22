#include <iostream>
#include "matrix.h"

int main() {
	unsigned rowsA, colsA;
	std::cin >> rowsA >> colsA;

	int** matA = newMatrix(rowsA, colsA);

	for (unsigned row = 0; row < rowsA; ++row)
		for (unsigned col = 0; col < colsA; ++col)
			std::cin >> matA[row][col];

	unsigned rowsB, colsB;
	std::cin >> rowsB >> colsB;

	int** matB = newMatrix(rowsB, colsB);

	for (unsigned row = 0; row < rowsB; ++row)
		for (unsigned col = 0; col < colsB; ++col)
			std::cin >> matB[row][col];

	std::cout << (sumMatrix((const int**)matA, rowsA, colsA) - sumMatrix((const int**)matB, rowsB, colsB)) << std::endl;

	deleteMatrix(matA, rowsA);
	deleteMatrix(matB, rowsB);

	return 0;
}
