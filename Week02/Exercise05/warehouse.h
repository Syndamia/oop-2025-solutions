#ifndef _WAREHOUSE
#define _WAREHOUSE

#include "package.h"

struct Warehouse {
	char ID;
	Package* packages;
	unsigned storedPackages;
	unsigned packageCapacity;

	bool storePackage(const Package& p);
};

#endif
