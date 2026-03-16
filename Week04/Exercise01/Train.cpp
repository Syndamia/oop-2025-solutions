#include "Train.h"
#include <iostream>

void Train::ArriveAtStation(unsigned passengersGettingOff, unsigned passengersGettingOn) {
	if (passengersGettingOff > passengersOnBoard)
		passengersOnBoard = 0;
	else
		passengersOnBoard -= passengersGettingOff;

	passengersOnBoard += passengersGettingOn;
	earnings += passengersGettingOn * ticketPrice;

	passedStops++;
	upcomingStops--;
}

void Train::Print() {
	std::cout << "Carriages: " << carriages << ' '
		<< "Seats: " << passengersOnBoard << '/' << seatsAvailable << ' '
		<< "Stops: " << passedStops << " < " << upcomingStops << ' '
		<< "Ticket: " << ticketPrice << ' '
		<< "Earnings: " << earnings
		<< std::endl;
}
