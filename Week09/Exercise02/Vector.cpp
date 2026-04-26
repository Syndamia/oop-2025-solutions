#include "Vector.h"
#include <cmath>
#include <cstring>

void Vector::free() {
	delete[] numbers;
}

void Vector::copyFrom(const Vector& other) {
	numbersCount = other.numbersCount;
	numbersAlloc = other.numbersAlloc;

	numbers = new double[numbersAlloc];
	for (unsigned i = 0; i < numbersCount; ++i)
		numbers[i] = other.numbers[i];
}

Vector::Vector() {
	numbers = nullptr;
	numbersCount = numbersAlloc = 0;
}

Vector::~Vector() {
	free();
}

Vector::Vector(const Vector& other) {
	copyFrom(other);
}

Vector& Vector::operator=(const Vector& other) {
	if (this != other.ptr()) {
		free();
		copyFrom(other);
	}
	return *this;
}

Vector::Vector(Vector&& other) {
	numbers = other.numbers;
	numbersCount = other.numbersCount;
	numbersAlloc = other.numbersAlloc;

	other.numbers = nullptr;
	other.numbersCount = other.numbersAlloc = 0;
}

Vector& Vector::operator=(Vector&& other) {
	if (this != other.ptr()) {
		free();

		numbers = other.numbers;
		numbersCount = other.numbersCount;
		numbersAlloc = other.numbersAlloc;

		other.numbers = nullptr;
		other.numbersCount = other.numbersAlloc = 0;
	}
	return *this;
}

unsigned Vector::GetCount() const {
	return numbersCount;
}

const double* Vector::GetNumbers() const {
	return numbers;
}

Vector& Vector::operator+=(const Vector& other) {
	unsigned minLen = numbersCount < other.numbersCount ? numbersCount : other.numbersCount;
	for (unsigned i = 0; i < minLen; ++i)
		numbers[i] += other.numbers[i];

	return *this;
}

Vector& Vector::operator-=(const Vector& other) {
	unsigned minLen = numbersCount < other.numbersCount ? numbersCount : other.numbersCount;
	for (unsigned i = 0; i < minLen; ++i)
		numbers[i] -= other.numbers[i];

	return *this;
}


Vector& Vector::operator*=(double scalar) {
	for (unsigned i = 0; i < numbersCount; ++i)
		numbers[i] *= scalar;

	return *this;
}

double Vector::operator*=(const Vector& other) {
	double dotProduct = 0.0;
	unsigned minLen = numbersCount < other.numbersCount ? numbersCount : other.numbersCount;

	for (unsigned i = 0; i < minLen; ++i)
		dotProduct += numbers[i] * other.numbers[i];

	return dotProduct;
}

Vector& Vector::operator^=(const Vector& other) {
	// Припомняме си, че векторното умножение работи само върху
	// триизмерни вектори
	if (numbersCount != 3 || other.numbersCount != 3)
		return *this;

	double s[3];
	double *a = numbers, *b = other.numbers;

	s[0] = a[1] * b[2] - a[2] * b[1];
	s[1] = a[2] * b[0] - a[0] * b[2];
	s[2] = a[0] * b[1] - a[1] * b[0];

	memcpy(a, s, sizeof(double) * 3);

	return *this;
}

double Vector::operator&() const {
	double sum = 0.0;
	for (unsigned i = 0; i < numbersCount; ++i)
		sum += numbers[i] * numbers[i];
	return sqrt(sum);
}

Vector* Vector::ptr() {
	return this;
}

const Vector* Vector::ptr() const {
	return this;
}

Vector operator+(const Vector& lhs, const Vector& rhs) {
	Vector ret(lhs);
	ret += rhs;
	return ret;
}

Vector operator-(const Vector& lhs, const Vector& rhs) {
	// Не трябва да е нужно да обясняваме защо това
	// е напълно същото като логиката при operator+
	return Vector(lhs) -= rhs;
}

Vector operator*(const Vector& lhs, double scalar) {
	return Vector(lhs) *= scalar;
}

Vector operator*(double scalar, const Vector& rhs) {
	return rhs * scalar;
}

double operator*(const Vector& lhs, const Vector& rhs) {
	return Vector(lhs) *= rhs;
}

Vector operator^(const Vector& lhs, const Vector& rhs) {
	return Vector(lhs) ^= rhs;
}

bool operator||(const Vector& lhs, const Vector& rhs) {
	unsigned minLen = lhs.GetCount() < rhs.GetCount() ? lhs.GetCount() : rhs.GetCount();

	// Под "паралелни" вектори говорим повече за "колинеарни" вектори.
	// Или с други думи, считаме дали правите, образувани от центъра 0 и
	// един вектор съвпада с правата, образувана от центъра 0 и другия вектор.
	// Щом лежат на една права, можем да скалираме единия вектор,
	// така че той да стане равен на другия.
	// С други думи, за вектори x и y, и скалар s, имаме че
	// x || y тогава и само тогава когато съществува s: x = s*y,
	// тстк същ. s: за всяко i: x[i] = s * y[i]
	// тстк същ. s: вс. i: x[i] / y[i] = s
	// тстк x[0] / y[0] = x[1] / y[1] = x[2] / y[2] = ...
	//
	// Алтернативно можем да вземем точковото умножение на вектори x и y,
	// и чрез него да намерим ъгъла между двата вектора.
	// Те ще лежат на една права ако ъгъла е 0 или 180 градуса.
	// С други думи, ако arccos((x * y) / (&x * &y)) е 0 или PI
	for (unsigned i = 0; i < minLen - 1; ++i) {
		// Това коректно ли е? Възможно ли е да имаме проблеми с такова директно сравнение?
		if (lhs.GetNumbers()[i] / rhs.GetNumbers()[i] != lhs.GetNumbers()[i+1] / rhs.GetNumbers()[i+1])
			return false;
	}
	return true;
}

bool operator==(const Vector& lhs, const Vector& rhs) {
	if (lhs.GetCount() != rhs.GetCount())
		return false;

	for (unsigned i = 0; i < lhs.GetCount(); ++i)
		if (lhs.GetNumbers()[i] != rhs.GetNumbers()[i])
			return false;
	return true;
}

bool operator!=(const Vector& lhs, const Vector& rhs) {
	return !(lhs == rhs);
}
