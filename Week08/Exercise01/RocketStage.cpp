#include "RocketStage.h"
#include <cstring>

const char* RocketStage::GetName() const {
	return name;
}

void RocketStage::SetName(const char* name) {
	strncpy(this->name, name, 100);
	this->name[100] = '\0';
}

unsigned RocketStage::GetHeight() const {
	return height;
}

void RocketStage::SetHeight(unsigned height) {
	this->height = height;
}

double RocketStage::GetWeight() const {
	return weight;
}

void RocketStage::SetWeight(double weight) {
	this->weight = weight;
}

double RocketStage::GetLiftForce() const {
	return liftForce;
}

void RocketStage::SetLiftForce(double liftForce) {
	this->liftForce = liftForce;
}

unsigned RocketStage::GetBurnTime() const {
	return burnTime;
}

void RocketStage::SetBurnTime(unsigned burnTime) {
	this->burnTime = burnTime;
}

double RocketStage::acceleration(double payloadWeight) const {
	return liftForce / (weight + payloadWeight);
}

double RocketStage::Speed(double payloadWeight) const {
	return burnTime * acceleration(payloadWeight);
}

double RocketStage::DistanceTravel(double payloadWeight) const {
	return (acceleration(payloadWeight) * burnTime * burnTime) / 2.0;
}
