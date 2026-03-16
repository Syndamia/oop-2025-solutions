#include "IntArray.h"

int IntArray::At(unsigned index) {
	if (index < capacity)
		return elems[index];
	return 0;
}

void IntArray::Resize(unsigned capacity) {
	int* newElems = new int[capacity];

	unsigned copyCount = this->capacity < capacity ? this->capacity : capacity;
	for (unsigned i = 0; i < copyCount; ++i)
		newElems[i] = elems[i];

	delete[] elems;
	elems = newElems;
	this->capacity = capacity;
}

void IntArray::Concat(const IntArray& endElements) {
	unsigned oldCapacity = capacity;
	Resize(capacity + endElements.capacity);

	for (unsigned i = oldCapacity; i < capacity; ++i)
		elems[i] = endElements.elems[i - oldCapacity];
}
