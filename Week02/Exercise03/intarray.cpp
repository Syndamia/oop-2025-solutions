#include "intarray.h"

void IntArray::deleteSelf() {
	delete[] elems;

	size = 0;
	elems = nullptr;
}

int IntArray::sum() {
	int totalSum = 0;
	for (unsigned i = 0; i < size; ++i)
		totalSum += elems[i];
	return totalSum;
}

IntArray newIntArray(unsigned size) {
	IntArray ia;
	ia.size = size;
	ia.elems = new int[size];

	return ia;
}

void deleteIntArray(IntArray& arr) {
	arr.deleteSelf();
}
