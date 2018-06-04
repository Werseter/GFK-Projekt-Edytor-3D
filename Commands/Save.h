#pragma once

#include "BaseCommand.h"

// save command saving object to a file
class Save : public BaseCommand {
	public:
		// Initializing save command
		Save(MyFrame* app) : BaseCommand("save", 1, app) {}

		// Overridden Execute method, saves object to file
		bool Execute(std::vector<std::string> args) { return true; }

		// Overridden documentation methods
		std::string Args() const { return "file_name"; }
		std::string Help() const { return "Saves object to file of name file_name"; }
};
