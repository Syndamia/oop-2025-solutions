#include "SharedPointer.hpp"
#include <iostream>

void inc(SharedPointer<int> val) {
	(*val)++;
}

int main() {
	SharedPointer<int> x(new int);
	SharedPointer<int> y = x;
	*x = 5;
	std::cout << *x << ' ' << *y << std::endl;
	inc(y);
	std::cout << *x << ' ' << *y << std::endl;

	return 0;
}
