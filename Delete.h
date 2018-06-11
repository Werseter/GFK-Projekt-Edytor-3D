#pragma once

#include "BaseCommand.h"

// delete command deleting an object of a given id
class Delete : public BaseCommand {
	public:
		// Initializing delete command
		Delete(MyFrame* app) : BaseCommand("delete", 1, app) {}

		// Overridden Execute method, deletes an object
		bool Execute(std::vector<std::string> args) {
			unsigned int id = atoi(args[1].c_str());
			std::vector<BaseObject*>::iterator objIt = std::find_if(app -> geoObjects.begin(), app -> geoObjects.end(), [&id](BaseObject* obj) { if (obj) return obj -> GetId() == id; else return false; });

			if (objIt != app -> geoObjects.end()) {
				delete (*objIt);
				(*objIt) = nullptr;
			}

			else {
				std::cout << "delete: Id not found" << std::endl;
			}

			app->UpdateObjList();
			return true;
		}

		// Overridden documentation methods
		std::string Args() const { return "id"; }
		std::string Help() const { return "Deletes an object with a given id"; }
};
