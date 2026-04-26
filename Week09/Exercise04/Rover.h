#ifndef _ROVER
#define _ROVER

#include <ostream>
#include <istream>

class Rover {
	double x;
	double y;
	double forward;

	void moveDistByAngle(double dist, double angle);

public:
	Rover();

	friend Rover& operator<(double dist, Rover& rover);
	Rover& operator>(double dist);
	Rover& operator^(double dist);
	friend Rover& operator<<(double degrees, Rover& rover);
	Rover& operator>>(double degrees);

	friend std::ostream& operator<<(std::ostream& ostr, const Rover& rover);
	friend std::istream& operator>>(std::istream& istr, Rover& rover);
};

#endif /* _ROVER */
