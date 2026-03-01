#ifndef _PACKAGE
#define _PACKAGE

struct Package {
	char ID[11]; // 10 букви за кода и още една за терминираща нула
	double weight;
};

Package readPackage();

#endif
