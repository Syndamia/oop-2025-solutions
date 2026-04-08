#ifndef _ROCKET_STAGE
#define _ROCKET_STAGE

class RocketStage {
	char name[101];
	unsigned height; // Метри
	double weight; // Килограми
	double liftForce; // Нютони
	unsigned burnTime; // Секунди

	double acceleration(double payloadWeight) const;

public:
	const char* GetName() const;
	void SetName(const char* name);

	unsigned GetHeight() const;
	void SetHeight(unsigned height);

	double GetWeight() const;
	void SetWeight(double weight);

	double GetLiftForce() const;
	void SetLiftForce(double liftForce);

	unsigned GetBurnTime() const;
	void SetBurnTime(unsigned burnTime);

	double Speed(double payloadWeight) const;
	double DistanceTravel(double payloadWeight) const;
};

#endif /* _ROCKET_STAGE */
