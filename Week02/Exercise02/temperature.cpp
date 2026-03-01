#include "temperature.h"

void Temperature::fromCelsius(double C) {
	this->C = C;
	F = (C * 1.8) + 32;
	K = C + 273.15;
}

void Temperature::fromFahrenheit(double F) {
	fromCelsius((F - 32) / 1.8);
}

void Temperature::fromKelvin(double K) {
	fromCelsius(K - 273.15);
}

Temperature Temperature::Sum(const Temperature& other) {
	Temperature t;
	t.fromCelsius(this->C + other.C);
	return t;
}
