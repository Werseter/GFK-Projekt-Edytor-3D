#pragma once

#include "BaseCommand.h"
#include <wx/filedlg.h>


// load command loading object from a file
class Load : public BaseCommand {
	public:
		// Initializing load command
		Load(MyFrame* app) : BaseCommand("load", 2, app) {}

		// Overridden Execute method, loads object from file
		bool Execute(std::vector<std::string> args) {
			// Open dialog window for loading a file
			wxFileDialog WxOpenFileDialog(this, wxT("Choose a file"), wxT(""), wxT(""), wxT("Geometry file (*.geo)|*.geo"), wxFD_OPEN | wxFD_FILE_MUST_EXIST);

			return true;
		}

		// Overridden documentation methods
		std::string Args() const { return "type file_name"; }
		std::string Help() const { return "Loads object of a given type from file of name file_name"; }
};
