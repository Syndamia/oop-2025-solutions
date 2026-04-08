#ifndef _HANGAR
#define _HANGAR

#include "RocketStage.h"
#include "Rocket.h"

class Hangar {
	Rocket* rockets;
	unsigned rocketsCount;
	unsigned rocketsAlloc;

	RocketStage* stages;
	unsigned stagesCount;
	unsigned stagesAlloc;

	void free();
	void copyFrom(const Hangar& other);

	void resizeRockets();
	void resizeStages();

public:
	Hangar();
	~Hangar();
	Hangar(const Hangar& other);
	Hangar& operator=(const Hangar& other);
	Hangar(Hangar&& other);
	Hangar& operator=(Hangar&& other);

	unsigned AddStage(const RocketStage& stage);
	RocketStage RemoveStage(unsigned stageIndex);

	unsigned AddRocket(const Rocket& rocket);
	const Rocket* GetRocket(unsigned rocketIndex) const;
	void MoveStageToRocket(unsigned rocketIndex, unsigned stageIndex);

	void Export(std::ofstream& outFile) const;
	void Import(std::ifstream& inFile);
};

#endif /* _HANGAR */
