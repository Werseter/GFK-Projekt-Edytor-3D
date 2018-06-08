#pragma once

#include "BaseCommand.h"
#include "../Objects3D/Box.h"

// box command creating a box based on given arguments
class CreateBox : public BaseCommand {
	public:
		// Initializing box
		CreateBox(MyFrame* app) : BaseCommand("box", 6, app) {}

		// Overridden execute method
		bool Execute(std::vector<std::string> args) {
			// First we get starting coordinates
			Data3D start(3);
			start[0] = atof(args[1].c_str());
			start[1] = atof(args[2].c_str());
			start[2] = atof(args[3].c_str());

			// And then ending coordinates
			Data3D end(3);
			end[0] = atof(args[4].c_str());
			end[1] = atof(args[5].c_str());
			end[2] = atof(args[5].c_str());
			
			// Then we create a new box object
			Box* box = new Box(start, end);
			app -> geoObjects.push_back(box);

			// Then we can update the object list
			app -> UpdateObjList(box);
			return true;
		}

		// Overridden documentation methods
		std::string Args() const { return "(x1, y1, z1), (x2, y2, z2)"; }
		std::string Help() const { return "Creates box object using two sets of coordinates: (x1, y1, z1) and (x2, y2, z2)."; }
};
