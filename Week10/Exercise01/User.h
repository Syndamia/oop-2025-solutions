#ifndef _USER
#define _USER

class User {
	unsigned ID;
	char name[1024];
	char password[128];
	unsigned yearRegistered;

public:
	bool LogIn(const char* name, const char* password);
};

#endif /* _USER */
