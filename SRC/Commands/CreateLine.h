#pragma once

#include "BaseCommand.h"
#include "Line.h"

// line command creating a line based on given arguments
class CreateLine : public BaseCommand {
	public:
		// Initializing line
		CreateLine(MyFrame* app) : BaseCommand("line", 6, app) {}

		// Overriden execute method
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
			end[2] = atof(args[6].c_str());

			// Then we create a new line object
			Line* line = new Line(start, end);
			app -> geoObjects.push_back(line);

			// Then we can update the object list
			app -> UpdateObjList(line);

			return true;
		}

		// Overridden documentation methods
		std::string Args() const { return "x1 y1 z1 x2 y2 z2"; }
		std::string Help() const { return "Creates line object using coordinates for starting point - (x1, y1, z1) and ending point - (x2, y2, z2)."; }
};
