#include <iostream>
#include <cstring>
#include "Shop.h"

int main() {
	Shop shop = newShop();

	User admin;
	strcpy(admin.name, "admin");
	strcpy(admin.password, "admin");
	admin.isAdmin = true;

	shop.users.add(admin);

	char command;
	while (true) {
		std::cin >> command;
		std::cin.ignore();
		shop.runCommand(command);
	}

	deleteShop(shop);

	return 0;
}
