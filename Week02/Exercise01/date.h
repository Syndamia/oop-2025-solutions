#ifndef _DATE
#define _DATE

struct Date {
	unsigned day;
	unsigned month;
	unsigned year;
};

void printDate(const Date& d);
Date readDate();

#endif
