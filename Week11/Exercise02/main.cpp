#include "Option.hpp"
#include <cmath>
#include <iostream>

Option<double> trySqrt(double x) {
	if (x < 0.0)
		return Option<double>::None();
	return Option<double>::Some(sqrt(x));
}

int main() {
	double num;
	std::cin >> num;

	Option<double> numRoot = trySqrt(num);

	if (numRoot.IsSome()) {
		std::cout << numRoot.Unwrap() << std::endl;
	}
	else {
		std::cout << "Couldn't find square root!" << std::endl;
	}

	return 0;
}
