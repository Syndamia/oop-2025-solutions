#ifndef _STUDENT
#define _STUDENT

#include "User.h"

class Student : public User {
	bool graduated;
	unsigned yearEnrolled;

public:
	void Graduate();
};

#endif /* _STUDENT */
