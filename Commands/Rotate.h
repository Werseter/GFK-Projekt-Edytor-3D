#pragma once

#include "BaseCommand.h"

// rotate an object of a given id around a point of given coordinates using given angles
class Rotate : public BaseCommand {
	public:
		// Initializing rotate command
		Rotate(MyFrame* app) : BaseCommand("rotate", 7, app) {}

		// Overridden Execute method, rotates an object
		bool Execute(std::vector<std::string> args) {
			// First we get the point's coordinates
			std::vector<float> coordinates(3);
			coordinates[0] = atof(args[2].c_str());
			coordinates[1] = atof(args[3].c_str());
			coordinates[2] = atof(args[4].c_str());

			// Then angles
			std::vector<float> angles(3);
			angles[0] = atof(args[5].c_str());
			angles[1] = atof(args[6].c_str());
			angles[2] = atof(args[7].c_str());

			// And then the id
			unsigned int id = atoi(args[1].c_str());

			return true;
		}

		// Overridden documentation methods
		std::string Args() const { return "id, (x, y, z), (a, b, c)"; }
		std::string Help() const { return "Rotates an object of a given id around a point of given coordinates using given angles"; }
};
