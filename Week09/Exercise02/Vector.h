#ifndef _VECTOR
#define _VECTOR

class Vector {
	double* numbers;
	unsigned numbersCount;
	unsigned numbersAlloc;

	void free();
	void copyFrom(const Vector& other);

public:
	Vector();
	~Vector();
	Vector(const Vector& other);
	Vector& operator=(const Vector& other);

	Vector(Vector&& other);
	Vector& operator=(Vector&& other);

	unsigned GetCount() const;
	const double* GetNumbers() const;

	// Добра конвенция при бинарни (двуаргументни) оператори е да
	// дефинираме като член-функции съответните _= оператори (+=, -=, ...)
	// и след това да дефинираме _ опеарторите (+, -, ...) като нормални
	// функции, които вътрешно използват _=

	Vector& operator+=(const Vector& other);
	Vector& operator-=(const Vector& other);
	Vector& operator*=(double scalar);
	double operator*=(const Vector& other);
	Vector& operator^=(const Vector& other);

	double operator&() const;

	// Понеже предефинираме &, не можем да направим &vector, за да
	// вземем указател от референция към обект. За нашите цели е нужно,
	// затова си правим помощни методи които "реимплементират" същата логика.
	Vector* ptr();
	const Vector* ptr() const;
};

Vector operator+(const Vector& lhs, const Vector& rhs);
Vector operator-(const Vector& lhs, const Vector& rhs);

// Понеже лявия и десния аргумент се различават по тип,
// така поддържаме комутативност
Vector operator*(const Vector& lhs, double scalar);
Vector operator*(double scalar, const Vector& rhs);

double operator*(const Vector& lhs, const Vector& rhs);
Vector operator^(const Vector& lhs, const Vector& rhs);

bool operator||(const Vector& lhs, const Vector& rhs);
bool operator==(const Vector& lhs, const Vector& rhs);
bool operator!=(const Vector& lhs, const Vector& rhs);

#endif /* _VECTOR */
