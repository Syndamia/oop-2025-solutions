#include "Locomotive.h"
#include <cstring>

unsigned Locomotive::GetID() const {
	return ID;
}

void Locomotive::SetID(unsigned ID) {
	this->ID = ID;
}

const char* Locomotive::GetManufacturer() const {
	return manufacturer;
}

void Locomotive::SetManufacturer(const char manufacturer[MAX_LEN]) {
	strncpy(this->manufacturer, manufacturer, MAX_LEN);
}

const char* Locomotive::GetModel() const {
	return model;
}

void Locomotive::SetModel(const char model[MAX_LEN]) {
	strncpy(this->model, model, MAX_LEN);
}

int Locomotive::GetYearOfManufacture() const {
	return yearOfManufacture;
}

void Locomotive::SetYearOfManufacture(int yearOfManufacture) {
	this->yearOfManufacture = yearOfManufacture;
}

double Locomotive::GetLength() const {
	return length;
}

void Locomotive::SetLength(double length) {
	this->length = length;
}

unsigned short Locomotive::GetCyllinders() const {
	return cyllinders;
}

void Locomotive::SetCyllinders(unsigned short cyllinders) {
	this->cyllinders = cyllinders;
}

bool Locomotive::GetSupportsMultipleWorking() const {
	return supportsMultipleWorking;
}

void Locomotive::SetSupportsMultipleWorking(bool supportsMultipleWorking) {
	this->supportsMultipleWorking = supportsMultipleWorking;
}

// Тази функция не е нужно да бъде приятелска, можеше просто да използваме
// константните селектори.
std::ofstream& operator<<(std::ofstream& ostr, const Locomotive& loc) {
	ostr << "Train #" << loc.ID << std::endl
		<< "+ Model: " << loc.model << std::endl
		<< "+ Manufacturer: " << loc.manufacturer << std::endl
		<< "+ Year of manufacture: " << loc.yearOfManufacture << std::endl
		<< "- Length: " << loc.length << std::endl
		<< "- Engine cyllinders: " << loc.cyllinders << std::endl
		<< "- Multiple working: " << (loc.supportsMultipleWorking ? "Yes" : "No") << std::endl;
	return ostr;
}

// Тазу функция не е нужно да бъде приятелска, можеше просто да използваме
// мутаторите.
std::ifstream& operator>>(std::ifstream& istr, Locomotive& loc) {
	istr >> loc.ID;
	istr.getline(loc.model, MAX_LEN);
	istr.getline(loc.manufacturer, MAX_LEN);
	istr >> loc.yearOfManufacture >> loc.length >> loc.cyllinders >> loc.supportsMultipleWorking;
	return istr;
}
