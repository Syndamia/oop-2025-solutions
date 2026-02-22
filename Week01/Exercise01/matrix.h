#ifndef _MATRIX
#define _MATRIX

// Създава нова динамично-заделена матрица
int** newMatrix(unsigned rows, unsigned cols);
// Изтрива динамично-заделена матрица
void deleteMatrix(int**& matrix, unsigned rows); // Запишете nullptr в matrix!
// Връща сумата на всички елементи в матрицата
int sumMatrix(const int** matrix, unsigned rows, unsigned cols);

#endif
