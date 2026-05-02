#ifndef _UNIQUEPOINTER
#define _UNIQUEPOINTER

template<class T>
class UniquePointer {
	T* value;

public:
	UniquePointer(T* value);

	UniquePointer();
	~UniquePointer();

	UniquePointer(UniquePointer&& other);
	UniquePointer& operator=(UniquePointer&& other);

	T& operator*();
	const T& operator*() const;
	T* operator->();
	const T* operator->() const;
};

template<class T>
UniquePointer<T>::UniquePointer(T* value) : value(value)
{ }

template<class T>
UniquePointer<T>::UniquePointer() : value()
{ }

template<class T>
UniquePointer<T>::~UniquePointer() {
	delete value;
}

template<class T>
UniquePointer<T>::UniquePointer(UniquePointer&& other) {
	value = other.value;

	other.value = nullptr;
}

template<class T>
UniquePointer<T>& UniquePointer<T>::operator=(UniquePointer&& other) {
	if (this != &other) {
		delete value;

		value = other.value;

		other.value = nullptr;
	}
	return *this;
}

template<class T>
T& UniquePointer<T>::operator*() {
	return *value;
}

template<class T>
const T& UniquePointer<T>::operator*() const {
	return *value;
}

template<class T>
T* UniquePointer<T>::operator->() {
	return value;
}

template<class T>
const T* UniquePointer<T>::operator->() const {
	return value;
}

#endif /* _UNIQUEPOINTER */
