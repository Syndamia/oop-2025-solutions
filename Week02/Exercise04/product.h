#ifndef _PRODUCT
#define _PRODUCT

static const unsigned MAX_NAME_LENGTH = 256;

struct Product {
	unsigned ID;
	char name[MAX_NAME_LENGTH];
	unsigned stockSize;
};

#endif
