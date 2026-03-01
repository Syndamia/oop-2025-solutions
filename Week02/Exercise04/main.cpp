#include <iostream>
#include "product.h"

int main() {
	unsigned productsCount;
	std::cin >> productsCount;

	Product* products = new Product[productsCount];

	for (unsigned i = 0; i < productsCount; ++i) {
		std::cin >> products[i].ID;
		std::cin.ignore();
		std::cin.getline(products[i].name, MAX_NAME_LENGTH);
	}

	for (unsigned i = 0; i < productsCount; ++i) {
		unsigned ID, stockSize;
		std::cin >> ID >> stockSize;

		for (unsigned i = 0; i < productsCount; ++i) {
			if (products[i].ID == ID) {
				products[i].stockSize = stockSize;
				break;
			}
		}
	}

	for (unsigned i = 0; i < productsCount; ++i) {
		std::cout << products[i].name << ": " << products[i].stockSize << std::endl;
	}

	delete[] products;

	return 0;
}
