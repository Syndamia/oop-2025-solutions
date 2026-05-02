#ifndef _INVENTORY
#define _INVENTORY

const unsigned PRODUCT_NAME_LENGTH = 1024;

struct Product {
	char name[PRODUCT_NAME_LENGTH];
	unsigned quantity;
};

class Inventory {
protected:
	Product* products;
	unsigned productsCount;
	unsigned productsAlloc;

private:
	void free();
	void copyFrom(const Inventory& other);

	void resize();

public:
	Inventory();
	~Inventory();
	Inventory(const Inventory& other);
	Inventory& operator=(const Inventory& other);

	Inventory(Inventory&& other);
	Inventory& operator=(Inventory&& other);

protected:
	void AddProduct(const Product& product);
};

#endif /* _INVENTORY */
