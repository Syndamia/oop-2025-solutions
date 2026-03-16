#ifndef _INTARRAY
#define _INTARRAY

class IntArray {
	int* elems;
	unsigned capacity;

	/* Как трябва да изглежда голяма четворка: */

	void free() {
		delete[] elems;
	}
	void copyFrom(const IntArray& other) {
		capacity = other.capacity;

		elems = new int[capacity];
		for (unsigned i = 0; i < capacity; ++i)
			elems[i] = other.elems[i];
	}
public:
	IntArray() {
		elems = nullptr;
		capacity = 0;
	}
	~IntArray() {
		free();
	}
	IntArray(const IntArray& other) {
		copyFrom(other);
	}
	IntArray& operator=(const IntArray& other) {
		if (this != &other) {
			free();
			copyFrom(other);
		}
		return *this;
	}

	int At(unsigned index);
	void Resize(unsigned capacity);
	void Concat(const IntArray& endElements);
};

#endif /* _INTARRAY */
