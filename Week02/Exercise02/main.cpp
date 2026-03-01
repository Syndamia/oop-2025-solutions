#include <iostream>
#include "temperature.h"

Temperature readTemperature() {
	double degrees;
	std::cin >> degrees;
	char scale;
	std::cin >> scale;

	Temperature t;
	switch (scale) {
		case 'C': t.fromCelsius(degrees); break;
		case 'F': t.fromFahrenheit(degrees); break;
		case 'K': t.fromKelvin(degrees); break;
	}

	return t;
}

void printTemperature(const Temperature& t) {
	std::cout << t.C << " C " << t.F << " F " << t.K << " K" << std::endl;
}

int main() {
	Temperature first = readTemperature(), second = readTemperature();

	printTemperature(first.Sum(second));

	return 0;
}
