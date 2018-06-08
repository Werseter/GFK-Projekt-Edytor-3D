#pragma once

#include "BaseCommand.h"

// set_line_color setting pen color for drawing
class SetLineColor : public BaseCommand {
	public:
		// Initializing set_line_color command
		SetLineColor(MyFrame* app) : BaseCommand("set_line_color", 3, app) {}

		// Overridden Execute method, sets pen color
		bool Execute(std::vector<std::string> args) {
			// Get r g b numbers
			std::vector<int> rgb(3);
			rgb[0] = atoi(args[1].c_str());
			rgb[1] = atoi(args[2].c_str());
			rgb[2] = atoi(args[3].c_str());

			app->drawingColor.Set(rgb[0], rgb[1], rgb[2]);

			return true;
		}

		// Overridden documentation methods
		std::string Args() const { return "r g b"; }
		std::string Help() const { return "Sets pen color"; }
};
