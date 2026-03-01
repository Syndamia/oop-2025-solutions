#ifndef _INTARRAY
#define _INTARRAY

struct IntArray {
	unsigned size;
	int* elems;

	void deleteSelf();
	int sum();
};

IntArray newIntArray(unsigned size);
void deleteIntArray(IntArray& arr);

#endif
