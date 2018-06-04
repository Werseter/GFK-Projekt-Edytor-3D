#pragma once

#include "BaseCommand.h"

// set_line_color setting pen color for drawing
class SetLineColor : public BaseCommand {
	public:
    // Initializing set_line_color command
		SetLineColor(MyFrame* app) : BaseCommand("set_line_color", 1, app) {}

    // Overrided Execute method, sets pen color
		bool Execute(std::vector<std::string> args) { }

    // Overrided documentation methods
		std::string Args() const { return "color"; }
		std::string Help() const { return "Sets pen color"; }
};
