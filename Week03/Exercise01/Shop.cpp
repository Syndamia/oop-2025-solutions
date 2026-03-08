#include <iostream>
#include <cstring>
#include "Shop.h"

void readUsername(char* str, unsigned length) {
	std::cout << "Username: ";
	std::cin.getline(str, length);
}

void readPassword(char* str, unsigned length) {
	std::cout << "Password: ";
	std::cin.getline(str, length);
}

void readName(char* str, unsigned length) {
	std::cout << "Name: ";
	std::cin.getline(str, length);
}

void Shop::runCommand(char command) {
	switch (command) {
		case 'l':
			if (loggedInUser == nullptr) {
				User temp;
				readUsername(temp.name, sizeof(temp.name) / sizeof(*temp.name));

				User* registeredUser = users.find(temp.name);

				if (registeredUser == nullptr) {
					std::cout << "User '" << temp.name << "' does not exist!" << std::endl;
					return;
				}

				readPassword(temp.password, sizeof(temp.password) / sizeof(*temp.password));

				if (strcmp(registeredUser->password, temp.password) != 0) {
					std::cout << "Incorrect password!" << std::endl;
					return;
				}

				loggedInUser = registeredUser;
				std::cout << "Successfull login!" << std::endl;
			}
			break;

		case 'r':
			if (loggedInUser == nullptr) {
				User temp;
				temp.isAdmin = false;
				readUsername(temp.name, sizeof(temp.name) / sizeof(*temp.name));

				User* registeredUser = users.find(temp.name);

				if (registeredUser != nullptr) {
					std::cout << "User '" << temp.name << "' is already registered!" << std::endl;
					return;
				}

				readPassword(temp.password, sizeof(temp.password) / sizeof(*temp.password));

				users.add(temp);
				std::cout << "Successfully registered user '" << temp.name << "'!" << std::endl;
			}
			break;

		case 'p':
			if (products.count > 0) {
				for (unsigned i = 0; i < products.count; ++i)
					std::cout << products.products[i].name << ' '
					          << products.products[i].count << ' '
					          << products.products[i].price << std::endl;
			}
			else {
				std::cout << "No products!" << std::endl;
			}
			break;

		case 'e':
			if (loggedInUser != nullptr) {
				loggedInUser = nullptr;
				std::cout << "Logged out!" << std::endl;
			}
			break;

		case 'b':
			if (loggedInUser != nullptr) {
				unsigned N;

				std::cout << "Number of products: ";
				std::cin >> N;
				std::cin.ignore();

				Product** shoppingCartProducts = new Product*[N];
				unsigned* shoppingCartCounts = new unsigned[N];
				unsigned cartItems = 0;

				for (unsigned i = 0; i < N; ++i) {
					Product temp;

					readName(temp.name, sizeof(temp.name) / sizeof(*temp.name));

					Product* storedProduct = products.find(temp.name);
					if (storedProduct == nullptr) {
						std::cout << "Invalid product name!" << std::endl;
						delete[] shoppingCartProducts;
						delete[] shoppingCartCounts;
						return;
					}

					std::cout << "Quantity: ";
					std::cin >> temp.count;
					std::cin.ignore();

					if (temp.count > storedProduct->count) {
						std::cout << "Invalid quantity!" << std::endl;
						delete[] shoppingCartProducts;
						delete[] shoppingCartCounts;
						return;
					}

					shoppingCartProducts[cartItems] = storedProduct;
					shoppingCartCounts[cartItems++] = temp.count;
				}

				double total = 0.0;
				for (unsigned i = 0; i < N; ++i) {
					total += shoppingCartProducts[i]->price * shoppingCartCounts[i];
					shoppingCartProducts[i]->count -= shoppingCartCounts[i];
				}

				std::cout << "Purchase successful! Total cost: " << total << std::endl;

				delete[] shoppingCartProducts;
				delete[] shoppingCartCounts;
			}
			break;

		case 'a':
			if (loggedInUser != nullptr) {
				if (!loggedInUser->isAdmin) {
					std::cout << "No permissions!" << std::endl;
					return;
				}

				User temp;

				readUsername(temp.name, sizeof(temp.name) / sizeof(*temp.name));

				User* registeredUser = users.find(temp.name);

				if (registeredUser == nullptr) {
					std::cout << "User '" << temp.name << "' does not exist!" << std::endl;
					return;
				}

				registeredUser->isAdmin = !registeredUser->isAdmin;
				if (registeredUser->isAdmin) {
					std::cout << "Made user '" << registeredUser->name << "' into an administrator." << std::endl;
				}
				else {
					std::cout << "Made administrator '" << registeredUser->name << "' into a user." << std::endl;
				}
			}
			break;

		case 's':
			if (loggedInUser != nullptr) {
				if (!loggedInUser->isAdmin) {
					std::cout << "No permissions!" << std::endl;
					return;
				}

				Product temp;

				readName(temp.name, sizeof(temp.name) / sizeof(*temp.name));

				std::cout << "Quantity: ";
				std::cin >> temp.count;

				std::cout << "Price: ";
				std::cin >> temp.price;
				std::cin.ignore();

				Product* storedProduct = products.find(temp.name);

				if (storedProduct == nullptr) {
					products.add(temp);
				}
				else {
					storedProduct->count += temp.count;
					storedProduct->price = temp.price;
				}
			}
			break;

		default:
			std::cout << "Invalid command '" << command << "'!" << std::endl;
	}
}

Shop newShop() {
	Shop s;
	s.users = newUserArray(64);
	s.products = newProductArray(64);
	s.loggedInUser = nullptr;
	return s;
}

void deleteShop(Shop& shop) {
	deleteUserArray(shop.users);
	deleteProductArray(shop.products);
	shop.loggedInUser = nullptr;
}
