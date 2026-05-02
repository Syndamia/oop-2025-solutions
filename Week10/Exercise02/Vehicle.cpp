#include "Vehicle.h"
#include <cstring>

Vehicle::Vehicle() : model(), yearOfManufacture(), mileage(), ecoCategory(), weight(), horsePower() {
	type = 0;
}

const char* Vehicle::GetModel() const {
	return model;
}

void Vehicle::SetModel(char model[MODEL_LENGTH]) {
	strcpy(this->model, model);
}

unsigned Vehicle::GetYearOfManufacture() const {
	return yearOfManufacture;
}

void Vehicle::SetYearOfManufacture(unsigned yearOfManufacture) {
	this->yearOfManufacture = yearOfManufacture;
}

double Vehicle::GetMileage() const {
return mileage;
}

void Vehicle::SetMileage(double mileage) {
	this->mileage = mileage;
}

unsigned short Vehicle::GetEcoCategory() const {
	return ecoCategory;
}

void Vehicle::SetEcoCategory(unsigned short ecoCategory) {
	this->ecoCategory = ecoCategory;
}

double Vehicle::GetWeight() const {
	return weight;
}

void Vehicle::SetWeight(double weight) {
	this->weight = weight;
}

double Vehicle::GetHorsePower() const {
	return horsePower;
}

void Vehicle::SetHorsePower(double horsePower) {
	this->horsePower = horsePower;
}

std::ostream& operator<<(std::ostream& ostr, const Vehicle& vehicle) {
	ostr << vehicle.model << std::endl
		<< "Manufactured: " << vehicle.yearOfManufacture << std::endl
		<< "Mileage: " << vehicle.mileage << std::endl
		<< "Eco category: " << vehicle.ecoCategory << std::endl
		<< "Weight: " << vehicle.weight << std::endl
		<< "Horse power: " << vehicle.horsePower << std::endl;
	return ostr;
}

std::istream& operator>>(std::istream& istr, Vehicle& vehicle) {
	istr.getline(vehicle.model, MODEL_LENGTH);
	istr >> vehicle.yearOfManufacture
		>> vehicle.mileage
		>> vehicle.ecoCategory
		>> vehicle.weight
		>> vehicle.horsePower;
	return istr;
}
