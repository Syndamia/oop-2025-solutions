#ifndef _TEACHER
#define _TEACHER

#include "User.h"

class Teacher : public User {
	char subject[1024];
	unsigned teachingStudentsCount;

public:
	void ChangeStudents(unsigned teachingStudentsCount);
};

#endif /* _TEACHER */
