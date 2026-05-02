#include "Warehouse.h"
#include <cstring>
#include <utility>

void Warehouse::free() {
	delete[] deliveries;
}

void Warehouse::copyFrom(const Warehouse& other) {
	deliveriesAlloc = other.deliveriesAlloc;
	deliveriesCount = other.deliveriesCount;

	deliveries = new Delivery[deliveriesAlloc];
	for (unsigned i = 0; i < deliveriesCount; ++i)
		deliveries[i] = other.deliveries[i];
}

void Warehouse::resize() {
	deliveriesAlloc = deliveriesAlloc == 0 ? 8 : deliveriesAlloc * 2;
	Delivery* deliveriesLarger = new Delivery[deliveriesAlloc];

	for (unsigned i = 0; i < deliveriesCount; ++i)
		deliveriesLarger[i] = deliveries[i];

	delete[] deliveries;
	deliveries = deliveriesLarger;
}

Warehouse::Warehouse() : Inventory(), deliveries(), deliveriesCount(), deliveriesAlloc()
{ }

Warehouse::~Warehouse() {
	free();
}

Warehouse::Warehouse(const Warehouse& other) : Inventory(other) {
	copyFrom(other);
}

Warehouse& Warehouse::operator=(const Warehouse& other) {
	if (this != &other) {
		Inventory::operator=(other);
		free();
		copyFrom(other);
	}
	return *this;
}

Warehouse::Warehouse(Warehouse&& other) : Inventory(std::move(other)) {
	deliveries = other.deliveries;
	deliveriesCount = other.deliveriesCount;
	deliveriesAlloc = other.deliveriesAlloc;

	other.deliveries = nullptr;
	other.deliveriesCount = other.deliveriesAlloc = 0;
}

Warehouse& Warehouse::operator=(Warehouse&& other) {
	if (this != &other) {
		Warehouse::operator=(std::move(other));

		free();

		deliveries = other.deliveries;
		deliveriesCount = other.deliveriesCount;
		deliveriesAlloc = other.deliveriesAlloc;

		other.deliveries = nullptr;
		other.deliveriesCount = other.deliveriesAlloc = 0;
	}
	return *this;
}

bool Warehouse::Receive(const Delivery& delivery) {
	for (unsigned i = 0; i < delivery.productsCount; ++i) {
		unsigned productIndex = 0;
		while (productIndex < productsCount &&
			   strcmp(delivery.products[i].name, products[productIndex].name) != 0)
		{
			++productIndex;
		}

		if (productIndex == productsCount)
			AddProduct(delivery.products[i]);
		else
			products[i].quantity += delivery.products[i].quantity;
	}

	if (deliveriesCount >= deliveriesAlloc)
		resize();
	deliveries[deliveriesCount++] = delivery;

	return true;
}
