#include <iostream>
#include "package.h"
#include "warehouse.h"

int main() {
	unsigned warehouseCount;
	std::cin >> warehouseCount;

	Warehouse* warehouses = new Warehouse[warehouseCount];

	for (unsigned i = 0; i < warehouseCount; ++i) {
		std::cin >> warehouses[i].ID >> warehouses[i].packageCapacity;
		warehouses[i].packages = new Package[warehouses[i].packageCapacity];
	}

	unsigned packagesCount;
	std::cin >> packagesCount;
	std::cin.ignore();

	for (unsigned i = 0; i < packagesCount; ++i) {
		Package p = readPackage();


		char warehouse;
		std::cin >> warehouse;
		std::cin.ignore();

		for (unsigned i = 0; i < warehouseCount; ++i) {
			if (warehouses[i].ID == warehouse) {
				warehouses[i].storePackage(p);
				break;
			}
		}
	}

	for (unsigned i = 0; i < warehouseCount; ++i) {
		std::cout << warehouses[i].ID << ' ' << warehouses[i].storedPackages << '/' << warehouses[i].packageCapacity << std::endl;
		for (unsigned j = 0; j < warehouses[i].storedPackages; ++j) {
			std::cout << warehouses[i].packages[j].ID << std::endl;
		}
	}

	for (unsigned i = 0; i < warehouseCount; ++i) {
		delete[] warehouses[i].packages;
	}
	delete[] warehouses;

	return 0;
}
