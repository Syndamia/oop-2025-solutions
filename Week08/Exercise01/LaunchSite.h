#ifndef _LAUNCH_SITE
#define _LAUNCH_SITE

class LaunchSite {
	char name[251];
	double maxWeight;
	unsigned maxHeight;

public:
	const char* GetName() const;
	void SetName(const char* name);

	double GetMaxWeight() const;
	void SetMaxWeight(double weight);

	unsigned GetMaxHeight() const;
	void SetMaxHeight(unsigned height);
};

#endif /* _LAUNCH_SITE */
