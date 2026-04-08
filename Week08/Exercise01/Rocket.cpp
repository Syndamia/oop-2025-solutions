#include "Rocket.h"
#include <cstring>

void Rocket::free() {
	delete[] stages;
}

void Rocket::copyFrom(const Rocket& other) {
	strncpy(name, other.name, sizeof(name) / sizeof(*name));

	stagesAlloc = other.stagesAlloc;
	stagesCount = other.stagesCount;

	stages = new RocketStage[stagesAlloc];
	for (unsigned i = 0; i < stagesCount; ++i)
		stages[i] = other.stages[i];
}

void Rocket::resize() {
	stagesAlloc = stagesAlloc == 0 ? 8 : stagesAlloc * 2;
	RocketStage* stagesResized = new RocketStage[stagesAlloc];

	for (unsigned i = 0; i < stagesCount; ++i)
		stagesResized[i] = stages[i];

	delete[] stages;
	stages = stagesResized;
}

Rocket::Rocket() {
	name[0] = '\0';
	stages = nullptr;
	stagesCount = stagesAlloc = 0;
}

Rocket::~Rocket() {
	free();
}

Rocket::Rocket(const Rocket& other) {
	copyFrom(other);
}

Rocket& Rocket::operator=(const Rocket& other) {
	if (this != &other) {
		free();
		copyFrom(other);
	}
	return *this;
}

Rocket::Rocket(Rocket&& other) {
	strncpy(name, other.name, sizeof(other.name) / sizeof(*other.name));
	stages = other.stages;
	stagesCount = other.stagesCount;
	stagesAlloc = other.stagesAlloc;

	other.name[0] = '\0';
	other.stages = nullptr;
	other.stagesCount = other.stagesAlloc = 0;
}

Rocket& Rocket::operator=(Rocket&& other) {
	if (this != &other) {
		free();

		strncpy(name, other.name, sizeof(other.name) / sizeof(*other.name));
		stages = other.stages;
		stagesCount = other.stagesCount;
		stagesAlloc = other.stagesAlloc;

		other.name[0] = '\0';
		other.stages = nullptr;
		other.stagesCount = other.stagesAlloc = 0;
	}
	return *this;
}

void Rocket::SetName(const char* name) {
	strncpy(this->name, name, sizeof(this->name) / sizeof(*this->name));
}

void Rocket::AddStage(const RocketStage& stage) {
	if (stagesCount >= stagesAlloc)
		resize();
	stages[stagesCount++] = stage;
}

double Rocket::TotalWeight() const {
	double weight = 0.0;
	for (unsigned i = 0; i < stagesCount; ++i)
		weight += stages[i].GetWeight();
	return weight;
}

unsigned Rocket::TotalHeight() const {
	unsigned height = 0;
	for (unsigned i = 0; i < stagesCount; ++i)
		height += stages[i].GetHeight();
	return height;
}

double Rocket::FinalStageSpeed() const {
	double speed = 0.0;
	unsigned weight = TotalWeight();

	for (unsigned i = 0; i < stagesCount; ++i) {
		weight -= stages[i].GetWeight();
		speed += stages[i].Speed(weight);
	}

	return speed;
}

double Rocket::TotalDistanceTravel() const {
	unsigned weight = TotalWeight();
	double x = 0.0;
	double v0 = 0.0;

	for (unsigned i = 0; i < stagesCount; ++i) {
		weight -= stages[i].GetWeight();
		x += v0 * stages[i].GetBurnTime() + stages[i].DistanceTravel(weight);
		v0 = stages[i].Speed(weight);
	}

	return x;
}

unsigned Rocket::TotalBurnTime() const {
	unsigned burnTime = 0;
	for (unsigned i = 0; i < stagesCount; ++i)
		burnTime += stages[i].GetBurnTime();
	return burnTime;
}

void Rocket::Export(std::ofstream& outFile) const {
	outFile.write(name, sizeof(name) / sizeof(*name));
	outFile.write((const char*)&stagesCount, sizeof(stagesCount));
	outFile.write((const char*)&stagesAlloc, sizeof(stagesAlloc));
	for (unsigned i = 0; i < stagesCount; ++i)
		outFile.write((const char*)&stages[i], sizeof(stages[i]));
}

void Rocket::Import(std::ifstream& inFile) {
	free();

	inFile.read(name, sizeof(name) / sizeof(*name));
	inFile.read((char*)&stagesCount, sizeof(stagesCount));
	inFile.read((char*)&stagesAlloc, sizeof(stagesAlloc));

	stages = new RocketStage[stagesAlloc];
	for (unsigned i = 0; i < stagesCount; ++i)
		inFile.read((char*)&stages[i], sizeof(stages[i]));
}
