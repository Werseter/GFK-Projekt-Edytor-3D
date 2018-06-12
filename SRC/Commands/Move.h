#pragma once

#include "BaseCommand.h"

// move an object of a given id by a given vector
class MoveObj : public BaseCommand {
	public:
		// Initializing move command
		MoveObj(MyFrame* app) : BaseCommand("move", 4, app) {}

		// Overridden Execute method, loads object from file
		bool Execute(std::vector<std::string> args) {
			// First we get the vector
			Data3D vec(3);
			vec[0] = atof(args[2].c_str());
			vec[1] = atof(args[3].c_str());
			vec[2] = atof(args[4].c_str());

			// And then the id
			unsigned int id = atoi(args[1].c_str());

			std::vector<BaseObject*>::iterator objIt = std::find_if(app -> geoObjects.begin(), app -> geoObjects.end(), [&id](BaseObject* obj) { if (obj) return obj -> GetId() == id; else return false; });
			if (objIt != app -> geoObjects.end()) {
				(*objIt) -> Move(vec);
				app -> UpdateObjList();
				return true;
			}
			else {
				wxStreamToTextRedirector redirect(app->m_textCtrlConsoleOutput);
				std::cout << "Object with id \"" << id << "\" has not been found" << std::endl;
				return false;
			}

			return true;
		}

		// Overridden documentation methods
		std::string Args() const { return "id, (x, y, z)"; }
		std::string Help() const { return "Moves an object of given id by a vector (x, y, z)"; }
};
