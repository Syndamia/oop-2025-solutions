#ifndef _ROCKET
#define _ROCKET

#include "RocketStage.h"
#include <fstream>

class Rocket {
	char name[512];
	RocketStage* stages;
	unsigned stagesCount;
	unsigned stagesAlloc;

	void free();
	void copyFrom(const Rocket& other);

	void resize();

public:
	Rocket();
	~Rocket();
	Rocket(const Rocket& other);
	Rocket& operator=(const Rocket& other);
	Rocket(Rocket&& other);
	Rocket& operator=(Rocket&& other);

	void SetName(const char* name);
	void AddStage(const RocketStage& stage);

	double TotalWeight() const;
	unsigned TotalHeight() const;
	double FinalStageSpeed() const;
	double TotalDistanceTravel() const;
	unsigned TotalBurnTime() const;

	void Export(std::ofstream& outFile) const;
	void Import(std::ifstream& inFile);
};

#endif /* _ROCKET */
