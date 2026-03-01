#include <iostream>
#include "time.h"

// По условие не ни е поискана логика за главната функция,
// но все пак е добра идея да се провери имплементацията
int main() {
	Time first = { 13, 4, 15 }, second = { 1, 59, 45 };
	first.Advance(second);

	std::cout << first.hour << ' ' << first.minutes << ' ' << first.seconds << std::endl;

	return 0;
}
