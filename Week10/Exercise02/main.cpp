#include "Vehicle.h"
#include "CombustionVehicle.h"
#include "ElectricVehicle.h"
#include <iostream>

int main() {
	unsigned N;
	std::cin >> N;

	Vehicle** vehicles = new Vehicle*[N];
	for (unsigned i = 0; i < N; ++i) {
		char type;
		std::cin >> type;
		std::cin.ignore();

		if (type == 'c') {
			CombustionVehicle* vehicle = new CombustionVehicle;
			std::cin >> *vehicle;
			vehicles[i] = vehicle;
		}
		else if (type == 'e') {
			ElectricVehicle* vehicle = new ElectricVehicle;
			std::cin >> *vehicle;
			vehicles[i] = vehicle;
		}
		else {
			vehicles[i] = nullptr;
		}
	}

	for (unsigned i = 0; i < N; ++i) {
		if (vehicles[i] != nullptr)
			std::cout << *vehicles[i];
	}

	for (unsigned i = 0; i < N; ++i) {
		if (vehicles[i] == nullptr) {
			continue;
		}
		// Това го правим, защото delete само вижда че обекта е "Vehicle",
		// не вижда допълнителната памет, която се заделя за допълнителните
		// член-данни, които запазваме при Combustion и Electric.

		else if (CombustionVehicle::IsCombustionVehicle(*vehicles[i])) {
			delete (CombustionVehicle*)vehicles[i];
		}
		else if (ElectricVehicle::IsElectricVehicle(*vehicles[i])) {
			delete (ElectricVehicle*)vehicles[i];
		}
		else {
			delete vehicles[i];
		}
	}
	delete[] vehicles;

	return 0;
}
