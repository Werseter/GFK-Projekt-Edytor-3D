#pragma once

#include "BaseCommand.h"

// move an object of a given id by a given vector
class Move : public BaseCommand {
	public:
    // Initializing move command
		Move(MyFrame* app) : BaseCommand("move", 4, app) {}

    // Overrided Execute method, loads object from file
		bool Execute(std::vector<std::string> args) {
      // First we get the vector
      std::vector<float> vec(3);
      vec[0] = atof(args[2].c_str());
      vec[1] = atof(args[3].c_str());
      vec[2] = atof(args[4].c_str());

      // And then the id
      unsigned int id = atoi(args[1].c_str());
    }

    // Overrided documentation methods
		std::string Args() const { return "id, (x, y, z)"; }
		std::string Help() const { return "Moves an object of given id by a vector (x, y, z)"; }
};
