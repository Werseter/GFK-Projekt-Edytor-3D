#pragma once

#include "BaseCommand.h"

// sphere command creating a cone based on given arguments
class CreateCone : public BaseCommand {
	public:
    // Initializing cone
		CreateCone(MyFrame* app) : BaseCommand("cone", 9, app) {}

    // Overrided execute method
		bool Execute(std::vector<std::string> args) {
      // First we get starting coordinates
			std::vector<float> start(3);
			start[0] = atof(args[1].c_str());
			start[1] = atof(args[2].c_str());
			start[2] = atof(args[3].c_str());

      // And then ending coordinates
      std::vector<float> end(3);
			end[0] = atof(args[5].c_str());
			end[1] = atof(args[6].c_str());
			end[2] = atof(args[7].c_str());

      // Then we create a new cone object
			app->geoObjects.push_back(new Cone(start, end, atof(args[4].c_str()), atoi(args[8].c_str()), atoi(args[9].c_str())));

      // Then we can update the object list
			app->UpdateObjList();

			return true;
		}

    // Overrided documentation methods
		std::string Args() const { return "(x1, y1, z1), radius1, (x2, y2, z2), radius1, nTetragons"; }
		std::string Help() const { return "Creates cone object using two sets of coordinates for bases: (x1, y1, z1) - with radius 1 - and (x2, y2, z2) - with radius2. The cone will be divided into given number of tetragons"; }
};
