#ifndef _SPACE_AGENCY
#define _SPACE_AGENCY

#include "Hangar.h"
#include "LaunchSite.h"

class SpaceAgency {
	Hangar* hangars;
	unsigned hangarsCount;
	unsigned hangarsAlloc;

	LaunchSite* sites;
	unsigned sitesCount;
	unsigned sitesAlloc;

	void free();
	void copyFrom(const SpaceAgency& other);

	void resizeHangars();
	void resizeSites();

public:
	SpaceAgency();
	~SpaceAgency();
	SpaceAgency(const SpaceAgency& other);
	SpaceAgency& operator=(const SpaceAgency& other);
	SpaceAgency(SpaceAgency&& other);
	SpaceAgency& operator=(SpaceAgency&& other);

	void AddHangar(const Hangar& hangar);
	Hangar* GetHangar(unsigned hangarIndex);
	const Hangar* GetHangar(unsigned hangarIndex) const;

	void AddLaunchSite(const LaunchSite& site);
	LaunchSite* GetLaunchSite(unsigned launchSiteIndex);
	const LaunchSite* GetLaunchSite(unsigned launchSiteIndex) const;

	void AddRocketStage(const RocketStage& stage, unsigned hangarIndex);

	unsigned AddRocket(const Rocket& rocket, unsigned hangarIndex);
	void MoveRocketStageToRocket(unsigned stageHangar, unsigned stageIndex, unsigned rocketHangar, unsigned rocketIndex);

	bool CanLaunch(unsigned siteIndex, unsigned hangarIndex, unsigned rocketIndex) const;
};

#endif /* _SPACE_AGENCY */
