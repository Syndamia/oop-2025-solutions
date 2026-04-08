#include "SpaceAgency.h"

void SpaceAgency::free() {
	delete[] hangars;
	delete[] sites;
}

void SpaceAgency::copyFrom(const SpaceAgency& other) {
	hangarsCount = other.hangarsCount;
	hangarsAlloc = other.hangarsAlloc;

	hangars = new Hangar[hangarsAlloc];
	for (unsigned i = 0; i < hangarsCount; ++i)
		hangars[i] = other.hangars[i];

	sitesCount = other.sitesCount;
	sitesAlloc = other.sitesAlloc;

	sites = new LaunchSite[sitesAlloc];
	for (unsigned i = 0; i < sitesCount; ++i)
		sites[i] = other.sites[i];
}

void SpaceAgency::resizeHangars() {
	hangarsAlloc = hangarsAlloc == 0 ? 8 : hangarsAlloc * 2;
	Hangar* hangarsResized = new Hangar[hangarsAlloc];

	for (unsigned i = 0; i < hangarsCount; ++i)
		hangarsResized[i] = hangars[i];

	delete[] hangars;
	hangars = hangarsResized;
}

void SpaceAgency::resizeSites() {
	sitesAlloc = sitesAlloc == 0 ? 8 : sitesAlloc * 2;
	LaunchSite* sitesResized = new LaunchSite[sitesAlloc];

	for (unsigned i = 0; i < sitesCount; ++i)
		sitesResized[i] = sites[i];

	delete[] sites;
	sites = sitesResized;
}

SpaceAgency::SpaceAgency() {
	hangars = nullptr;
	sites = nullptr;
	hangarsCount = hangarsAlloc = sitesCount = sitesAlloc = 0;
}

SpaceAgency::~SpaceAgency() {
	free();
}

SpaceAgency::SpaceAgency(const SpaceAgency& other) {
	copyFrom(other);
}

SpaceAgency& SpaceAgency::operator=(const SpaceAgency& other) {
	if (this != &other) {
		free();
		copyFrom(other);
	}
	return *this;
}

SpaceAgency::SpaceAgency(SpaceAgency&& other) {
	hangars = other.hangars;
	hangarsAlloc = other.hangarsAlloc;
	hangarsCount = other.hangarsCount;

	sites = other.sites;
	sitesAlloc = other.sitesAlloc;
	sitesCount = other.sitesCount;

	other.hangars = nullptr;
	other.hangarsAlloc = other.hangarsCount = 0;
	other.sites = nullptr;
	other.sitesAlloc = other.sitesCount = 0;
}

SpaceAgency& SpaceAgency::operator=(SpaceAgency&& other) {
	if (this != &other) {
		free();

		hangars = other.hangars;
		hangarsAlloc = other.hangarsAlloc;
		hangarsCount = other.hangarsCount;

		sites = other.sites;
		sitesAlloc = other.sitesAlloc;
		sitesCount = other.sitesCount;

		other.hangars = nullptr;
		other.hangarsAlloc = other.hangarsCount = 0;
		other.sites = nullptr;
		other.sitesAlloc = other.sitesCount = 0;
	}
	return *this;
}

void SpaceAgency::AddHangar(const Hangar& hangar) {
	if (hangarsCount >= hangarsAlloc)
		resizeHangars();
	hangars[hangarsCount++] = hangar;
}

Hangar* SpaceAgency::GetHangar(unsigned hangarIndex) {
	if (hangarIndex >= hangarsCount)
		return nullptr;
	return &hangars[hangarIndex];
}

const Hangar* SpaceAgency::GetHangar(unsigned hangarIndex) const {
	if (hangarIndex >= hangarsCount)
		return nullptr;
	return &hangars[hangarIndex];
}

void SpaceAgency::AddLaunchSite(const LaunchSite& site) {
	if (sitesCount >= sitesAlloc)
		resizeSites();
	sites[sitesCount++] = site;
}

LaunchSite* SpaceAgency::GetLaunchSite(unsigned launchSiteIndex) {
	if (launchSiteIndex >= sitesCount)
		return nullptr;
	return &sites[launchSiteIndex];
}
const LaunchSite* SpaceAgency::GetLaunchSite(unsigned launchSiteIndex) const {
	if (launchSiteIndex >= sitesCount)
		return nullptr;
	return &sites[launchSiteIndex];
}

void SpaceAgency::AddRocketStage(const RocketStage& stage, unsigned hangarIndex) {
	if (hangarIndex >= hangarsCount)
		return;
	hangars[hangarIndex].AddStage(stage);
}

unsigned SpaceAgency::AddRocket(const Rocket& rocket, unsigned hangarIndex) {
	if (hangarIndex >= hangarsCount)
		return -1; // Заради 2s complement това е само единици битове и резултата е най-голямото unsigned число
	return hangars[hangarIndex].AddRocket(rocket);
}

void SpaceAgency::MoveRocketStageToRocket(unsigned stageHangar, unsigned stageIndex, unsigned rocketHangar, unsigned rocketIndex) {
	if (stageHangar >= hangarsCount || rocketHangar >= hangarsCount)
		return;

	if (stageHangar != rocketHangar) {
		stageIndex = hangars[rocketIndex].AddStage(hangars[stageIndex].RemoveStage(stageIndex));
	}

	hangars[rocketIndex].MoveStageToRocket(rocketIndex, stageIndex);
}

bool SpaceAgency::CanLaunch(unsigned siteIndex, unsigned hangarIndex, unsigned rocketIndex) const {
	if (siteIndex >= sitesCount || hangarIndex >= hangarsCount)
		return false;

	const Rocket* rock = hangars[hangarIndex].GetRocket(rocketIndex);
	if (rock == nullptr)
		return false;

	return rock->TotalHeight() <= sites[siteIndex].GetMaxHeight() && rock->TotalWeight() <= sites[siteIndex].GetMaxWeight();
}
