#ifndef _VECTOR
#define _VECTOR

template<class T>
class Vector {
	T* objects;
	unsigned objectsCount;
	unsigned objectsAlloc;

	void free();
	void copyFrom(const Vector& other);

	void resize();

public:
	Vector();
	~Vector();
	Vector(const Vector& other);
	Vector& operator=(const Vector& other);

	Vector(Vector&& other);
	Vector& operator=(Vector&& other);

	unsigned Count() const;
	void PushBack(const T& object);

	T& operator[](unsigned index);
	const T& operator[](unsigned index) const;

	Vector& operator+=(const Vector& rhs);
};

template<class T>
Vector<T> operator+(const Vector<T>& lhs, const Vector<T>& rhs);

template<class T>
void Vector<T>::free() {
	delete[] objects;
}

template<class T>
void Vector<T>::copyFrom(const Vector& other) {
	objectsCount = other.objectsCount;
	objectsAlloc = other.objectsAlloc;

	objects = new T[objectsAlloc];
	for (unsigned i = 0; i < objectsCount; ++i)
		objects[i] = other.objects[i];
}

template<class T>
void Vector<T>::resize() {
	objectsAlloc = objectsAlloc == 0 ? 8 : objectsAlloc * 2;
	T* objectsLarger = new T[objectsAlloc];

	for (unsigned i = 0; i < objectsCount; ++i)
		objectsLarger[i] = objects[i];

	delete[] objects;
	objects = objectsLarger;
}

template<class T>
Vector<T>::Vector() : objects(), objectsAlloc(), objectsCount()
{ }

template<class T>
Vector<T>::~Vector() {
	free();
}

template<class T>
Vector<T>::Vector(const Vector& other) {
	copyFrom(other);
}

template<class T>
Vector<T>& Vector<T>::operator=(const Vector& other) {
	if (this != &other) {
		free();
		copyFrom(other);
	}
	return *this;
}

template<class T>
Vector<T>::Vector(Vector&& other) {
	objects = other.objects;
	objectsCount = other.objectsCount;
	objectsAlloc = other.objectsAlloc;

	other.objects = nullptr;
	other.objectsCount = other.objectsAlloc = 0;
}

template<class T>
Vector<T>& Vector<T>::operator=(Vector&& other) {
	if (this != &other) {
		free();

		objects = other.objects;
		objectsCount = other.objectsCount;
		objectsAlloc = other.objectsAlloc;

		other.objects = nullptr;
		other.objectsCount = other.objectsAlloc = 0;
	}
	return *this;
}

template<class T>
unsigned Vector<T>::Count() const {
	return objectsCount;
}

template<class T>
void Vector<T>::PushBack(const T& object) {
	if (objectsCount >= objectsAlloc)
		resize();
	objects[objectsCount++] = object;
}

template<class T>
T& Vector<T>::operator[](unsigned index) {
	return objects[index];
}

template<class T>
const T& Vector<T>::operator[](unsigned index) const {
	return objects[index];
}

template<class T>
Vector<T>& Vector<T>::operator+=(const Vector& rhs) {
	for (unsigned i = 0; i < rhs.objectsCount; ++i)
		PushBack(rhs.objects[i]);
	return *this;
}

template<class T>
Vector<T> operator+(const Vector<T>& lhs, const Vector<T>& rhs) {
	Vector val(lhs);
	val += rhs;
	return val;
}

#endif /* _VECTOR */
