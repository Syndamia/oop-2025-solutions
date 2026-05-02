#ifndef _DOUBLEVECTOR
#define _DOUBLEVECTOR

#include "Pair.hpp"

template<class T, class U>
class DoubleVector {
	T* first;
	unsigned firstCount;
	unsigned firstAlloc;

	T* second;
	unsigned secondCount;
	unsigned secondAlloc;

	void free();
	void copyFrom(const DoubleVector& other);

	void firstResize();
	void secondResize();

public:
	DoubleVector();
	~DoubleVector();
	DoubleVector(const DoubleVector& other);
	DoubleVector& operator=(const DoubleVector& other);

	DoubleVector(DoubleVector&& other);
	DoubleVector& operator=(DoubleVector&& other);

	Pair<unsigned, unsigned> Count() const;

	void FirstPushBack(const T& object);
	void SecondPushBack(const U& object);

	Pair<T&, U&> operator[](unsigned index);
	const Pair<T&, U&> operator[](unsigned index) const;

	DoubleVector& operator+=(const DoubleVector& rhs);
};

template<class T, class U>
DoubleVector<T, U> operator+(const DoubleVector<T, U>& lhs, const DoubleVector<T, U>& rhs);

template<class T, class U>
void DoubleVector<T, U>::free() {
	delete[] first;
	delete[] second;
}

template<class T, class U>
void DoubleVector<T, U>::copyFrom(const DoubleVector& other) {
	firstCount = other.firstCount;
	firstAlloc = other.firstAlloc;

	first = new T[firstAlloc];
	for (unsigned i = 0; i < firstCount; ++i)
		first[i] = other.first[i];

	secondCount = other.secondCount;
	secondAlloc = other.secondAlloc;

	second = new T[secondAlloc];
	for (unsigned i = 0; i < secondCount; ++i)
		second[i] = other.second[i];
}

template<class T, class U>
void DoubleVector<T, U>::firstResize() {
	firstAlloc = firstAlloc == 0 ? 8 : firstAlloc * 2;
	T* firstLarger = new T[firstAlloc];

	for (unsigned i = 0; i < firstCount; ++i)
		firstLarger[i] = first[i];

	delete[] first;
	first = firstLarger;
}

template<class T, class U>
void DoubleVector<T, U>::secondResize() {
	secondAlloc = secondAlloc == 0 ? 8 : secondAlloc * 2;
	U* secondLarger = new U[secondAlloc];

	for (unsigned i = 0; i < secondCount; ++i)
		secondLarger[i] = second[i];

	delete[] second;
	second = secondLarger;
}

template<class T, class U>
DoubleVector<T, U>::DoubleVector()
	: first(), firstAlloc(), firstCount(),
	  second(), secondAlloc(), secondCount()
{ }

template<class T, class U>
DoubleVector<T, U>::~DoubleVector() {
	free();
}

template<class T, class U>
DoubleVector<T, U>::DoubleVector(const DoubleVector& other) {
	copyFrom(other);
}

template<class T, class U>
DoubleVector<T, U>& DoubleVector<T, U>::operator=(const DoubleVector& other) {
	if (this != &other) {
		free();
		copyFrom(other);
	}
	return *this;
}

template<class T, class U>
DoubleVector<T, U>::DoubleVector(DoubleVector&& other) {
	first = other.first;
	firstCount = other.firstCount;
	firstAlloc = other.firstAlloc;

	second = other.second;
	secondCount = other.secondCount;
	secondAlloc = other.secondAlloc;

	other.first = nullptr;
	other.firstCount = other.firstAlloc = 0;

	other.second = nullptr;
	other.secondCount = other.secondAlloc = 0;
}

template<class T, class U>
DoubleVector<T, U>& DoubleVector<T, U>::operator=(DoubleVector&& other) {
	if (this != &other) {
		free();

		first = other.first;
		firstCount = other.firstCount;
		firstAlloc = other.firstAlloc;

		second = other.second;
		secondCount = other.secondCount;
		secondAlloc = other.secondAlloc;

		other.first = nullptr;
		other.firstCount = other.firstAlloc = 0;

		other.second = nullptr;
		other.secondCount = other.secondAlloc = 0;
	}
	return *this;
}

template<class T, class U>
Pair<unsigned, unsigned> DoubleVector<T, U>::Count() const {
	return Pair(firstCount, secondCount);
}

template<class T, class U>
void DoubleVector<T, U>::FirstPushBack(const T& object) {
	if (firstCount >= firstAlloc)
		firstResize();
	first[firstCount++] = object;
}

template<class T, class U>
void DoubleVector<T, U>::SecondPushBack(const U& object) {
	if (secondCount >= secondAlloc)
		secondResize();
	second[secondCount++] = object;
}

template<class T, class U>
Pair<T&, U&> DoubleVector<T, U>::operator[](unsigned index) {
	return Pair(first[index], second[index]);
}

template<class T, class U>
const Pair<T&, U&> DoubleVector<T, U>::operator[](unsigned index) const {
	return Pair(first[index], second[index]);
}

template<class T, class U>
DoubleVector<T, U>& DoubleVector<T, U>::operator+=(const DoubleVector& rhs) {
	for (unsigned i = 0; i < rhs.firstCount; ++i)
		FirstPushBack(rhs.first[i]);
	for (unsigned i = 0; i < rhs.secondCount; ++i)
		SecondPushBack(rhs.second[i]);
	return *this;
}

template<class T, class U>
DoubleVector<T, U> operator+(const DoubleVector<T, U>& lhs, const DoubleVector<T, U>& rhs) {
	DoubleVector val(lhs);
	val += rhs;
	return val;
}

#endif /* _DOUBLEVECTOR */
