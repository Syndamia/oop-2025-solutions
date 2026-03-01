#include <iostream>
#include "intarray.h"

int main() {
	unsigned N;
	std::cin >> N;

	IntArray ia = newIntArray(N);
	for (unsigned i = 0; i < ia.size; ++i)
		std::cin >> ia.elems[i];

	std::cout << ((double)ia.sum() / ia.size) << std::endl;

	deleteIntArray(ia);

	return 0;
}
