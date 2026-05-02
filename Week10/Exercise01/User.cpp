#include "User.h"
#include <cstring>

bool User::LogIn(const char* name, const char* password) {
	return strcmp(this->name, name) == 0 && strcmp(this->password, password) == 0;
}
