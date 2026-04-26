#include "String.h"
#include <iostream>

int main() {
	String a = "Hello";
	String b = "World";

	String c = a + " " + b;

	std::cout << c << std::endl;
	std::cout << (c << b) << ' ' << (a >> c) << std::endl;
	std::cout << c[String::IndexRange(2), 7] << std::endl;

	return 0;
}
