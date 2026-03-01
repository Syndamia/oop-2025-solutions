#include "time.h"

unsigned timeToMilliseconds(const Time& t) {
	return (t.hour * 60 * 60 + t.minutes * 60 + t.seconds) * 1000;
}

void Time::Advance(const Time& other) {
	// По-простия вариант е с експлицитни сметки, но помислете защо това работи
	*this = millisecondsToTime(timeToMilliseconds(*this) + timeToMilliseconds(other));
}

Time millisecondsToTime(unsigned int milliseconds) {
	Time t;
	t.hour    = (milliseconds / 1000 / 60 / 60) % 24;
	t.minutes = (milliseconds / 1000 / 60) % 60;
	t.seconds = (milliseconds / 1000) % 60;

	return t;
}
