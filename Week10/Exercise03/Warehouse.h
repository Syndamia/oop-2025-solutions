#ifndef _WAREHOUSE
#define _WAREHOUSE

#include "Inventory.h"
#include "Date.h"

struct Delivery {
	Product products[8];
	unsigned productsCount;
	Date date;
	unsigned trackingNumber;
};

class Warehouse : public Inventory {
	Delivery* deliveries;
	unsigned deliveriesCount;
	unsigned deliveriesAlloc;

	void free();
	void copyFrom(const Warehouse& other);

	void resize();

public:
	Warehouse();
	~Warehouse();
	Warehouse(const Warehouse& other);
	Warehouse& operator=(const Warehouse& other);

	Warehouse(Warehouse&& other);
	Warehouse& operator=(Warehouse&& other);

	bool Receive(const Delivery& delivery);
};

#endif /* _WAREHOUSE */
