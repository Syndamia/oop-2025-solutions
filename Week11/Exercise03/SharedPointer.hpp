#ifndef _SHAREDPOINTER
#define _SHAREDPOINTER

template<class T>
class SharedPointer {
	T* value;
	unsigned* instances;

	void free();
	void copyFrom(const SharedPointer& other);

public:
	SharedPointer(T* value);

	SharedPointer();
	~SharedPointer();
	SharedPointer(const SharedPointer& other);
	SharedPointer& operator=(const SharedPointer& other);

	SharedPointer(SharedPointer&& other);
	SharedPointer& operator=(SharedPointer&& other);

	T& operator*();
	const T& operator*() const;
	T* operator->();
	const T* operator->() const;

	unsigned RefCount() const;
};

template <class T>
void SharedPointer<T>::free() {
	if (instances == nullptr)
		return;

	--*instances;
	if (*instances == 0) {
		delete instances;
		delete value;
	}
}

template <class T>
void SharedPointer<T>::copyFrom(const SharedPointer& other) {
	this->instances = other.instances;
	this->value = other.value;
	++*instances;
}

template <class T>
SharedPointer<T>::SharedPointer(T* value) : instances(new unsigned), value(value)
{
	*instances = 1;
}

template <class T>
SharedPointer<T>::SharedPointer() : instances(), value()
{ }

template <class T>
SharedPointer<T>::~SharedPointer() {
	free();
}

template <class T>
SharedPointer<T>::SharedPointer(const SharedPointer& other) {
	copyFrom(other);
}

template <class T>
SharedPointer<T>& SharedPointer<T>::operator=(const SharedPointer& other) {
	if (this != &other) {
		free();
		copyFrom(other);
	}
	return *this;
}

template <class T>
SharedPointer<T>::SharedPointer(SharedPointer&& other) {
	instances = other.instances;
	value = other.value;

	other.instances = nullptr;
	other.value = nullptr;
}

template <class T>
SharedPointer<T>& SharedPointer<T>::operator=(SharedPointer&& other) {
	if (this != &other) {
		free();

		instances = other.instances;
		value = other.value;

		other.instances = nullptr;
		other.value = nullptr;
	}
	return *this;
}

template <class T>
T& SharedPointer<T>::operator*() {
	return *value;
}

template <class T>
const T& SharedPointer<T>::operator*() const {
	return *value;
}

template <class T>
T* SharedPointer<T>::operator->() {
	return value;
}

template <class T>
const T* SharedPointer<T>::operator->() const {
	return value;
}

template <class T>
unsigned SharedPointer<T>::RefCount() const {
	if (instances == nullptr)
		return 0;
	return *instances;
}

#endif /* _SHAREDPOINTER */
