#include "LaunchSite.h"
#include <cstring>

const char* LaunchSite::GetName() const {
	return name;
}

void LaunchSite::SetName(const char* name) {
	strncpy(this->name, name, 250);
	this->name[250] = '\0';
}

double LaunchSite::GetMaxWeight() const {
	return maxWeight;
}
void LaunchSite::SetMaxWeight(double weight) {
	this->maxWeight = weight;
}

unsigned LaunchSite::GetMaxHeight() const {
	return maxHeight;
}

void LaunchSite::SetMaxHeight(unsigned height) {
	this->maxHeight = height;
}
