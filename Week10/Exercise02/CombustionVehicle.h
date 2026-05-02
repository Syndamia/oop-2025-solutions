#ifndef _COMBUSTIONVEHICLE
#define _COMBUSTIONVEHICLE

#include "Vehicle.h"
#include <istream>
#include <ostream>

class CombustionVehicle : public Vehicle {
	unsigned cyllindersCount;
	double engineVolume;

public:
	CombustionVehicle();

	unsigned GetCyllindersCount() const;
	void SetCyllindersCount(unsigned cyllindersCount);

	double GetEngineVolume() const;
	void SetEngineVolume(double engineVolume);

	friend std::ostream& operator<<(std::ostream& ostr, const CombustionVehicle& vehicle);
	friend std::istream& operator>>(std::istream& istr, CombustionVehicle& vehicle);

	static bool IsCombustionVehicle(const Vehicle& vehicle);
};

#endif /* _COMBUSTIONVEHICLE */
