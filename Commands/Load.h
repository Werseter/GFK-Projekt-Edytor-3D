#pragma once

#include "BaseCommand.h"

// load command loading object from a file
class Load : public BaseCommand {
	public:
		// Initializing load command
		Load(MyFrame* app) : BaseCommand("load", 1, app) {}

		// Overridden Execute method, loads object from file
		bool Execute(std::vector<std::string> args) { return true; }

		// Overridden documentation methods
		std::string Args() const { return "file_name"; }
		std::string Help() const { return "Loads object from file of name file_name"; }
};
