#ifndef ARRMATH
#define ARRMATH

// Сума на стойностите в elements
int sum(const int* elements, unsigned length);
// Средно аритметично на стойностите в elements
double average(const int* elements, unsigned length);
// Най-голямата стойност в elements
int largest(const int* elements, unsigned length);
// Най-малката стойност в elements
int smallest(const int* elements, unsigned length);
// Връща индекса на първото срещане на elementToSearch
unsigned findIndex(const int* elements, unsigned length, int elementToSearch);

#endif
