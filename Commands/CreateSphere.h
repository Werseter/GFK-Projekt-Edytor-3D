#pragma once

#include "BaseCommand.h"

// sphere command creating a sphere based on given arguments
class CreateSphere : public BaseCommand {
	public:
    // Initializing sphere
		CreateSphere(MyFrame* app) : BaseCommand("sphere", 6, app) {}

    // Overrided execute method
		bool Execute(std::vector<std::string> args) {
      // First we get x,y,z coordinates
			std::vector<float> coordinates(3);
			coordinates[0] = atof(args[1].c_str());
			coordinates[1] = atof(args[2].c_str());
			coordinates[2] = atof(args[3].c_str());

      // And then, using also the rest of arguments, we create a new sphere object
			app->geoObjects.push_back(new Sphere(coordinates, atof(args[4].c_str()), atoi(args[5].c_str()), atoi(args[6].c_str())));

      // Then we can update the object list
			app->UpdateObjList();

			return true;
		}

    // Overrided documentation methods
		std::string Args() const { return "(x, y, z), radius, (meridians, parallels)"; }
		std::string Help() const { return "Creates sphere object with a middle of coordinates (x, y, z) and a given radius. The sphere will be divided into given meridians and parallels"; }
};
