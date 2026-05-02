#ifndef _ELECTRICVEHICLE
#define _ELECTRICVEHICLE

#include "Vehicle.h"
#include <istream>
#include <ostream>

class ElectricVehicle : public Vehicle {
	double batteryCapacity;
	double range;
	double chargingCapacity;

public:
	ElectricVehicle();

	double GetBatteryCapacity() const;
	void SetBatteryCapacity(double batteryCapacity);

	double GetRange() const;
	void SetRange(double range);

	double GetCharingCapacity() const;
	void SetChargingCapacity(double chargingCapacity);

	friend std::ostream& operator<<(std::ostream& ostr, const ElectricVehicle& vehicle);
	friend std::istream& operator>>(std::istream& istr, ElectricVehicle& vehicle);

	static bool IsElectricVehicle(const Vehicle& vehicle);
};

#endif /* _ELECTRICVEHICLE */
