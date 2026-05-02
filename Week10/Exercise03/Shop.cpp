#include "Shop.h"
#include <cstring>
#include <utility>

void Shop::free() {
	delete[] sales;
}

void Shop::copyFrom(const Shop& other) {
	salesAlloc = other.salesAlloc;
	salesCount = other.salesCount;

	sales = new Sale[salesAlloc];
	for (unsigned i = 0; i < salesCount; ++i)
		sales[i] = other.sales[i];
}

void Shop::resize() {
	salesAlloc = salesAlloc == 0 ? 8 : salesAlloc * 2;
	Sale* salesLarger = new Sale[salesAlloc];

	for (unsigned i = 0; i < salesCount; ++i)
		salesLarger[i] = sales[i];

	delete[] sales;
	sales = salesLarger;
}

Shop::Shop() : Inventory(), sales(), salesCount(), salesAlloc()
{ }

Shop::~Shop() {
	free();
}

Shop::Shop(const Shop& other) : Inventory(other) {
	copyFrom(other);
}

Shop& Shop::operator=(const Shop& other) {
	if (this != &other) {
		Inventory::operator=(other);
		free();
		copyFrom(other);
	}
	return *this;
}

Shop::Shop(Shop&& other) : Inventory(std::move(other)) {
	sales = other.sales;
	salesCount = other.salesCount;
	salesAlloc = other.salesAlloc;

	other.sales = nullptr;
	other.salesAlloc = other.salesCount = 0;
}

Shop& Shop::operator=(Shop&& other) {
	if (this != &other) {
		Shop::operator=(std::move(other));

		free();

		sales = other.sales;
		salesCount = other.salesCount;
		salesAlloc = other.salesAlloc;

		other.sales = nullptr;
		other.salesAlloc = other.salesCount = 0;
	}
	return *this;
}

bool Shop::Purchase(const Sale& sale) {
	unsigned productIndex = 0;
	while (productIndex < productsCount &&
	       strcmp(sale.productName, products[productIndex].name) != 0)
	{
		++productIndex;
	}

	if (productIndex == productsCount || products[productIndex].quantity >= sale.quantity)
		return false;

	if (salesCount >= salesAlloc)
		resize();
	sales[salesCount++] = sale;

	products[productIndex].quantity -= sale.quantity;
	return true;
}
