#include "Rover.h"
#include <cmath>

// Използваме полярни координати, за да опишем посоките.
// С други думи, използваме ъгъл, такъв че (1,0) е на 0 градуса (радиана),
// (0,1) е на 90 градуса, (-1,0) е на 180 градуса и (0,-1) е на 270 градуса.
// Така ако знаем посоката напред, посоката на ляво е на 90 градуса обратно
// на часовниковата стрелка от ъгъла, който описва посоката "напред".
// Аналогично, посоката на ляво е на 90 градуса по часовниковата стрелка от
// ъгъла, който описва посоката "напред".

void Rover::moveDistByAngle(double dist, double angle) {
	// https://en.wikipedia.org/wiki/Polar_coordinate_system#Converting_between_polar_and_Cartesian_coordinates
	this->x += dist * cos(angle);
	this->y += dist * sin(angle);
}

Rover::Rover() {
	x = y = 0;
	forward = M_PI_2;
}

Rover& operator<(double dist, Rover& rover) {
	rover.moveDistByAngle(dist, rover.forward + M_PI_2);
	return rover;
}

Rover& Rover::operator>(double dist) {
	this->moveDistByAngle(dist, this->forward - M_PI_2);
	return *this;
}

Rover& Rover::operator^(double dist) {
	this->moveDistByAngle(dist, this->forward);
	return *this;
}

Rover& operator<<(double degrees, Rover& rover) {
	rover.forward += degrees / 180.0 * M_PI;
	return rover;
}

Rover& Rover::operator>>(double degrees) {
	this->forward -= degrees / 180.0 * M_PI;
	return *this;
}

std::ostream& operator<<(std::ostream& ostr, const Rover& rover) {
	double forwardUnitX = cos(rover.forward), forwardUnitY = sin(rover.forward);
	ostr << "Rover at (" << rover.x << ',' << rover.y
		<< "), looking direction (" << forwardUnitX << ',' << forwardUnitY << ')'
		<< std::endl;
	return ostr;
}

std::istream& operator>>(std::istream& istr, Rover& rover) {
	// Очакваме координат, който описва посоката "напред"
	// Например (0,1)
	double forwardUnitX, forwardUnitY;
	istr >> rover.x >> rover.y >> forwardUnitX >> forwardUnitY;
	// https://en.wikipedia.org/wiki/Polar_coordinate_system#Converting_between_polar_and_Cartesian_coordinates
	rover.forward = atan2(forwardUnitY, forwardUnitX);
	return istr;
}
