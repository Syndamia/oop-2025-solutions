#ifndef _TRAIN
#define _TRAIN

class Train {
	unsigned carriages;
	unsigned seatsAvailable;
	unsigned passengersOnBoard;
	unsigned passedStops;
	unsigned upcomingStops;
	double ticketPrice;
	double earnings;

	// Излишно, но е добре да следваме "шаблона"
	void free() {}
	void copyFrom(const Train& other) {
		carriages = other.carriages;
		seatsAvailable = other.seatsAvailable;
		passengersOnBoard = other.passengersOnBoard;
		passedStops = other.passedStops;
		upcomingStops = other.upcomingStops;
		ticketPrice = other.ticketPrice;
		earnings = other.earnings;
	}

public:
	// "Шаблон" за голямата четворка
	Train() {
		carriages = seatsAvailable = passengersOnBoard = passedStops = upcomingStops = ticketPrice = earnings = 0;
	}
	~Train() {
		free();
	}
	Train(const Train& other) {
		copyFrom(other);
	}
	Train& operator=(const Train& other) {
		if (this != &other) {
			free();
			copyFrom(other);
		}
		return *this;
	}

	Train(unsigned carriages, unsigned seatsAvailable, unsigned upcomingStops, double ticketPrice) {
		this->carriages = carriages;
		this->seatsAvailable = seatsAvailable;
		this->passengersOnBoard = 0;
		this->passedStops = 0.0;
		this->upcomingStops = upcomingStops;
		this->ticketPrice = ticketPrice;
		this->earnings = 0.0;
	}

	void ArriveAtStation(unsigned passengersGettingOff, unsigned passengersGettingOn);
	void Print();

	unsigned GetCarriages() {
		return carriages;
	}
	void SetCarriages(unsigned carriages) {
		this->carriages = carriages;
	}

	unsigned GetSeatsAvailable() {
		return seatsAvailable;
	}
	void SetSeatsAvailable(unsigned seatsAvailable) {
		this->seatsAvailable = seatsAvailable;
	}

	unsigned GetPassengersOnBoard() {
		return passengersOnBoard;
	}
	void SetPassengersOnBoard(unsigned passengersOnBoard) {
		this->passengersOnBoard = passengersOnBoard;
	}

	unsigned GetPassedStops() {
		return passedStops;
	}
	void SetPassedStops(unsigned passedStops) {
		this->passedStops = passedStops;
	}

	unsigned GetUpcomingStops() {
		return upcomingStops;
	}
	void SetUpcomingStops(unsigned upcomingStops) {
		this->upcomingStops = upcomingStops;
	}

	double GetTicketPrice() {
		return ticketPrice;
	}
	void SetTicketPrice(double ticketPrice) {
		this->ticketPrice = ticketPrice;
	}

	double GetEarnings() {
		return earnings;
	}
	void SetEarnings(double earnings) {
		this->earnings = earnings;
	}
};

#endif /* _TRAIN */
