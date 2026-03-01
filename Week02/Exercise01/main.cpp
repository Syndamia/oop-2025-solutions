#include <iostream>
#include "date.h"

int main() {
	for (unsigned i = 0; i < 3; ++i) {
		printDate(readDate());
		std::cout << ' ';
	}
	std::cout << std::endl;

	return 0;
}
