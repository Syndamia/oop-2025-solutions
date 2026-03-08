#include <iostream>
#include <cstring>
#include "User.h"

void UserArray::add(const User& user) {
	if (count >= allocated) {
		std::cout << "No more users are allowed!" << std::endl;
		return;
	}

	users[count++] = user;
}

User* UserArray::find(char* username) {
	for (unsigned i = 0; i < count; ++i)
		if (strcmp(username, users[i].name) == 0)
			return &users[i];
	return nullptr;
}

UserArray newUserArray(unsigned allocatedSize) {
	UserArray ua;
	ua.users = new User[allocatedSize];
	ua.count = 0;
	ua.allocated = allocatedSize;
	return ua;
}

void deleteUserArray(UserArray& ua) {
	delete[] ua.users;
	ua.users = nullptr;
	ua.count = ua.allocated = 0;
}
