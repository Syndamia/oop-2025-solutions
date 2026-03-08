#ifndef _PRODUCT
#define _PRODUCT

struct Product {
	char name[256];
	unsigned count;
	double price;
};

struct ProductArray {
	Product* products;
	unsigned count;
	unsigned allocated;

	void add(const Product& product);
	Product* find(char* name);
};

ProductArray newProductArray(unsigned allocatedSize);
void deleteProductArray(ProductArray& ua);

#endif
