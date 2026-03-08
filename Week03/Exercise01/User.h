#ifndef _USER
#define _USER

struct User {
	char name[256];
	char password[256];
	bool isAdmin;
};

struct UserArray {
	User* users;
	unsigned count;
	unsigned allocated;

	void add(const User& user);
	User* find(char* username);
};

UserArray newUserArray(unsigned allocatedSize);
void deleteUserArray(UserArray& ua);

#endif
