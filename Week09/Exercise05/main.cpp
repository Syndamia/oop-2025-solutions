#include "StringArray.h"
#include <iostream>

int main() {
	StringArray s;

	// Защо за числата трябва да конвертираме всички, а при | конвертираме само първия?
	s[ Z(7) +++ Z(4) +++ Z(3) ] ("") (StringArray("Hello")|"World") [ Z(4) +++ Z(5) +++ Z(1) ] ("!") [ Z(2) ] (StringArray("Code")|"A"|"B");

	std::cout << s;
	return 0;
}
