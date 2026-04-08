#include "Hangar.h"
#include "RocketStage.h"

void Hangar::free() {
	delete[] rockets;
	delete[] stages;
}

void Hangar::copyFrom(const Hangar& other) {
	rocketsCount = other.rocketsCount;
	rocketsAlloc = other.rocketsAlloc;

	rockets = new Rocket[rocketsAlloc];
	for (unsigned i = 0; i < rocketsCount; ++i)
		rockets[i] = other.rockets[i];
}

void Hangar::resizeRockets() {
	rocketsAlloc = rocketsAlloc == 0 ? 8 : rocketsAlloc * 2;
	Rocket* rocketsResized = new Rocket[rocketsAlloc];

	for (unsigned i = 0; i < rocketsCount; ++i)
		rocketsResized[i] = rockets[i];

	delete[] rockets;
	rockets = rocketsResized;
}

void Hangar::resizeStages() {
	stagesAlloc = stagesAlloc == 0 ? 8 : stagesAlloc * 2;
	RocketStage* stagesResized = new RocketStage[stagesAlloc];

	for (unsigned i = 0; i < stagesCount; ++i)
stagesResized[i] = stages[i];

	delete[] stages;
	stages = stagesResized;
}

Hangar::Hangar() {
	rockets = nullptr;
	stages = nullptr;
	rocketsCount = rocketsAlloc = stagesCount = stagesAlloc = 0;
}

Hangar::~Hangar() {
	free();
}

Hangar::Hangar(const Hangar& other) {
	copyFrom(other);
}

Hangar& Hangar::operator=(const Hangar& other) {
	if (this != &other) {
		free();
		copyFrom(other);
	}
	return *this;
}

Hangar::Hangar(Hangar&& other) {
	rockets = other.rockets;
	rocketsCount = other.rocketsCount;
	rocketsAlloc = other.rocketsAlloc;

	stages = other.stages;
	stagesCount = other.stagesCount;
	stagesAlloc = other.stagesAlloc;

	other.rockets = nullptr;
	other.rocketsCount = other.rocketsAlloc = 0;
	other.stages = nullptr;
	other.stagesCount = other.stagesAlloc = 0;
}

Hangar& Hangar::operator=(Hangar&& other) {
	if (this != &other) {
		free();

		rockets = other.rockets;
		rocketsCount = other.rocketsCount;
		rocketsAlloc = other.rocketsAlloc;

		stages = other.stages;
		stagesCount = other.stagesCount;
		stagesAlloc = other.stagesAlloc;

		other.rockets = nullptr;
		other.rocketsCount = other.rocketsAlloc = 0;
		other.stages = nullptr;
		other.stagesCount = other.stagesAlloc = 0;
	}
	return *this;
}

unsigned Hangar::AddStage(const RocketStage& stage) {
	if (stagesCount >= stagesAlloc)
		resizeStages();
	stages[stagesCount] = stage;
	return stagesCount++;
}

RocketStage Hangar::RemoveStage(unsigned stageIndex) {
	if (stageIndex >= stagesCount)
		return RocketStage();

	RocketStage rs = stages[stageIndex];

	stagesCount--;
	for (unsigned i = stageIndex; i < stagesCount; ++i)
		stages[i] = stages[i + 1];

	return rs;
}

unsigned Hangar::AddRocket(const Rocket& rocket) {
	if (rocketsCount >= rocketsAlloc)
		resizeRockets();
	rockets[rocketsCount] = rocket;
	return rocketsCount++;
}

const Rocket* Hangar::GetRocket(unsigned rocketIndex) const {
	if (rocketIndex >= rocketsCount)
		return nullptr;
	return &rockets[rocketIndex];
}

void Hangar::MoveStageToRocket(unsigned rocketIndex, unsigned stageIndex) {
	if (rocketIndex >= rocketsCount || stageIndex >= stagesCount)
		return;

	rockets[rocketIndex].AddStage(RemoveStage(stageIndex));
}

void Hangar::Export(std::ofstream& outFile) const {
	outFile.write((const char*)&rocketsCount, sizeof(rocketsCount));
	outFile.write((const char*)&rocketsAlloc, sizeof(rocketsAlloc));
	for (unsigned i = 0; i < rocketsCount; ++i)
		rockets[i].Export(outFile);

	outFile.write((const char*)&stagesCount, sizeof(stagesCount));
	outFile.write((const char*)&stagesAlloc, sizeof(stagesAlloc));
	for (unsigned i = 0; i < stagesCount; ++i)
		outFile.write((const char*)&stages[i], sizeof(stages[i]));
}

void Hangar::Import(std::ifstream& inFile) {
	free();

	inFile.read((char*)&rocketsCount, sizeof(rocketsCount));
	inFile.read((char*)&rocketsAlloc, sizeof(rocketsAlloc));

	rockets = new Rocket[rocketsAlloc];
	for (unsigned i = 0; i < rocketsCount; ++i)
		inFile.read((char*)&rockets[i], sizeof(rockets[i]));

	inFile.read((char*)&stagesCount, sizeof(stagesCount));
	inFile.read((char*)&stagesAlloc, sizeof(stagesAlloc));

	stages = new RocketStage[stagesAlloc];
	for (unsigned i = 0; i < stagesCount; ++i)
		inFile.read((char*)&stages[i], sizeof(stages[i]));
}
