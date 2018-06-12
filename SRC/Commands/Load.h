#pragma once

#include "BaseCommand.h"
#include <wx/filedlg.h>
#include <fstream>


// load command loading object from a file
class Load : public BaseCommand {
	public:
		// Initializing load command
		Load(MyFrame* app) : BaseCommand("load", 1, app) {}

		// Overridden Execute method, loads object from file
		bool Execute(std::vector<std::string> args) {
			wxStreamToTextRedirector redirect(app->m_textCtrlConsoleOutput);
			// Open dialog window for loading a file
			wxFileDialog loadFileDialog(app, wxT("Choose a file"), wxT(""), args[1] + ".geo", wxT("Geometry file (*.geo)|*.geo"), wxFD_OPEN | wxFD_FILE_MUST_EXIST);

			// If user changes their mind and chooses cancel
			if (loadFileDialog.ShowModal() == wxID_CANCEL) {
				std::cout << "Aborted file saving operation" << std::endl;
				return false;
			}
			// Prepare an output stream to read points from
			std::ifstream in(loadFileDialog.GetPath().c_str().AsChar());

			std::string line, line2;
			//Load all objects' data from file
			while (std::getline(in, line)) {
				std::vector<BaseObject*>::iterator objIt = std::find_if(app -> basicGeoObjects.begin(), app -> basicGeoObjects.end(), [&line](BaseObject* obj) { if (obj) return obj -> GetType() == line; else return false; });

				if (objIt != app -> basicGeoObjects.end()) {
					BaseObject* obj = (*objIt) -> Copy();
					std::getline(in, line);
					std::getline(in, line2);
					obj -> SetData(line, line2);
					app -> geoObjects.push_back(obj);
					app -> UpdateObjList(obj);
				}
				else {
					std::cout << "Encountered an unknown object type, skipping" << std::endl;
					std::getline(in, line2);
					std::getline(in, line2);
				}
			}

			return true;
		}

		// Overridden documentation methods
		std::string Args() const { return "file_name"; }
		std::string Help() const { return "Loads objects from file provided in file_name"; }
};
