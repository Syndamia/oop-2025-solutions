#ifndef _TIME
#define _TIME

struct Time {
	unsigned hour;
	unsigned minutes;
	unsigned seconds;

	void Advance(const Time& other);
};

Time millisecondsToTime(unsigned milliseconds);

#endif
