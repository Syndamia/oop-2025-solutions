#include <cstring>
#include <iostream>

#include "SpaceAgency.h"

int main() {
	char command[1024];
	SpaceAgency sa;

	while (true) {
		std::cin.getline(command, sizeof(command) / sizeof(*command));
		if (strcmp(command, "exit") == 0) {
			break;
		}
		else if (strcmp(command, "new_hangar") == 0) {
			sa.AddHangar(Hangar());
		}
		else if (strcmp(command, "new_launch_site") == 0) {
			char nameBuffer[251];
			std::cout << "Name: ";
			std::cin.getline(nameBuffer, sizeof(nameBuffer) / sizeof(*nameBuffer));

			double maxWeight;
			std::cout << "Max weight: ";
			std::cin >> maxWeight;

			unsigned maxHeight;
			std::cout << "Max height: ";
			std::cin >> maxHeight;

			std::cin.ignore();

			LaunchSite ls;
			ls.SetName(nameBuffer);
			ls.SetMaxWeight(maxWeight);
			ls.SetMaxHeight(maxHeight);

			sa.AddLaunchSite(ls);
		}
		else if (strcmp(command, "new_rocket_stage") == 0) {
			char name[101];
			std::cout << "Name: ";
			std::cin.getline(name, sizeof(name) / sizeof(*name));

			unsigned height;
			std::cout << "Height: ";
			std::cin >> height;

			double weight;
			std::cout << "Weight: ";
			std::cin >> weight;

			double liftForce;
			std::cout << "Lift force: ";
			std::cin >> liftForce;

			unsigned burnTime;
			std::cout << "Burn time: ";
			std::cin >> burnTime;

			RocketStage rs;
			rs.SetName(name);
			rs.SetHeight(height);
			rs.SetWeight(weight);
			rs.SetLiftForce(liftForce);
			rs.SetBurnTime(burnTime);

			unsigned hangarIndex;
			std::cout << "Hangar index: ";
			std::cin >> hangarIndex;

			std::cin.ignore();

			sa.AddRocketStage(rs, hangarIndex);
		}
		else if (strcmp(command, "new_rocket") == 0) {
			unsigned rocketHangarIndex;
			std::cout << "Rocket hangar index: ";
			std::cin >> rocketHangarIndex;

			std::cin.ignore();

			char name[512];
			std::cout << "Name: ";
			std::cin.getline(name, sizeof(name) / sizeof(*name));

			Rocket r;
			r.SetName(name);
			unsigned rocketIndex = sa.AddRocket(r, rocketHangarIndex);

			unsigned stages;
			std::cout << "Stages: ";
			std::cin >> stages;

			for (unsigned i = 0; i < stages; ++i) {
				unsigned stageHangar, stageIndex;

				std::cout << "Stage hangar index: ";
				std::cin >> stageHangar;
				std::cout << "Stage index: ";
				std::cin >> stageIndex;

				sa.MoveRocketStageToRocket(stageHangar, stageIndex, rocketHangarIndex, rocketIndex);
			}
			std::cin.ignore();
		}
		else if (strcmp(command, "can_launch") == 0) {
			unsigned siteIndex;
			std::cout << "Site index: ";
			std::cin >> siteIndex;

			unsigned hangarIndex;
			std::cout << "Rocket hangar index: ";
			std::cin >> hangarIndex;

			unsigned rocketIndex;
			std::cout << "Rocket index: ";
			std::cin >> rocketIndex;

			std::cin.ignore();

			if (sa.CanLaunch(siteIndex, hangarIndex, rocketIndex)) {
				std::cout << "Can be launched!" << std::endl;
			}
			else {
				std::cout << "Cannot be launched!" << std::endl;
			}
		}
		else {
			std::cout << "Invalid command!" << std::endl;
		}
	}

	return 0;
}
