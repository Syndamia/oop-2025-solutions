#ifndef _SHOP
#define _SHOP

#include "Inventory.h"
#include "Date.h"

struct Sale {
	char productName[PRODUCT_NAME_LENGTH];
	unsigned quantity;
	Date date;
};

class Shop : public Inventory {
	Sale* sales;
	unsigned salesCount;
	unsigned salesAlloc;

	void free();
	void copyFrom(const Shop& other);

	void resize();

public:
	Shop();
	~Shop();
	Shop(const Shop& other);
	Shop& operator=(const Shop& other);

	Shop(Shop&& other);
	Shop& operator=(Shop&& other);

	bool Purchase(const Sale& sale);
};

#endif /* _SHOP */
