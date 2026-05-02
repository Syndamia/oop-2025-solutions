#include "Inventory.h"

void Inventory::free() {
	delete[] products;
}

void Inventory::copyFrom(const Inventory& other) {
	productsCount = other.productsCount;
	productsAlloc = other.productsAlloc;

	products = new Product[productsAlloc];
	for (unsigned i = 0; i < productsCount; ++i)
		products[i] = other.products[i];
}

void Inventory::resize() {
	productsAlloc = productsAlloc == 0 ? 8 : productsAlloc * 2;
	Product* productsLarger = new Product[productsAlloc];

	for (unsigned i = 0; i < productsCount; ++i)
		productsLarger[i] = products[i];

	delete[] products;
	products = productsLarger;
}

Inventory::Inventory() : products(), productsCount(), productsAlloc()
{ }

Inventory::~Inventory() {
	free();
}

Inventory::Inventory(const Inventory& other) {
	copyFrom(other);
}

Inventory& Inventory::operator=(const Inventory& other) {
	if (this != &other) {
		free();
		copyFrom(other);
	}
	return *this;
}

Inventory::Inventory(Inventory&& other) {
	products = other.products;
	productsCount = other.productsCount;
	productsAlloc = other.productsAlloc;

	other.products = nullptr;
	other.productsAlloc = other.productsCount = 0;
}

Inventory& Inventory::operator=(Inventory&& other) {
	if (this != &other) {
		free();

		products = other.products;
		productsCount = other.productsCount;
		productsAlloc = other.productsAlloc;

		other.products = nullptr;
		other.productsAlloc = other.productsCount = 0;
	}
	return *this;
}

void Inventory::AddProduct(const Product& product) {
	if (productsCount >= productsAlloc)
		resize();
	products[productsCount++] = product;
}
