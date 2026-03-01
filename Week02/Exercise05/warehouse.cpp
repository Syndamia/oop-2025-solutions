#include "warehouse.h"

bool Warehouse::storePackage(const Package& p) {
	if (storedPackages >= packageCapacity)
		return false;

	packages[storedPackages++] = p;
	return true;
}
