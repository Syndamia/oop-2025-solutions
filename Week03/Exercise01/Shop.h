#ifndef _SHOP
#define _SHOP

#include "User.h"
#include "Product.h"

struct Shop {
	UserArray users;
	ProductArray products;
	User* loggedInUser;

	void runCommand(char command);
};

Shop newShop();
void deleteShop(Shop& shop);

#endif
