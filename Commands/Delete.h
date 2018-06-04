#pragma once

#include "BaseCommand.h"

// delete command deleting an object of a given id
class Delete : public BaseCommand {
	public:
    // Initializing delete command
		Delete(MyFrame* app) : BaseCommand("delete", 1, app) {}

    // Overrided Execute method, deletes an object
		bool Execute(std::vector<std::string> args) { }

    // Overrided documentation methods
		std::string Args() const { return "id"; }
		std::string Help() const { return "Deletes an object of a given id"; }
};
