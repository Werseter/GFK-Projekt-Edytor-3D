#pragma once

#include "BaseCommand.h"
#include <wx/filedlg.h>
#include <wx/log.h>

// save command saving object to a file
class Save : public BaseCommand {
	public:
		// Initializing save command
		Save(MyFrame* app) : BaseCommand("save", 2, app) {}

		// Overridden Execute method, saves object to file
		bool Execute(std::vector<std::string> args) {
			// Open dialog window for saving a file
			wxFileDialog saveFileDialog(this, wxT("Save XYZ file"), wxT(""), wxT(""), wxT("Geometry file (*.geo)|*.geo"), wxFD_SAVE|wxFD_OVERWRITE_PROMPT);

			// If user changes their mind and chooses cancel
			if (saveFileDialog.ShowModal() == wxID_CANCEL)
        return false;

			// Prepare an output stream to write points there
			wxFileOutputStream output_stream(saveFileDialog.GetPath());

			// Get id of an object from arguments
			unsigned int id = atoi(args[1].c_str());
			std::vector<BaseObject*>::iterator objIt = std::find_if(app -> geoObjects.begin(), app -> geoObjects.end(), [&id](BaseObject* obj) { if (obj) return obj -> GetId() == id; else return false; });

			if (objIt != app -> geoObjects.end()) {
				const DataVector* data = (*objIt)->GetData();

			}

      if (!output_stream.IsOk()) {
				wxLogError("Cannot save current contents in file '%s'.", saveFileDialog.GetPath());
				return false;
     }
		 return true;
		}

		// Overridden documentation methods
		std::string Args() const { return "id file_name"; }
		std::string Help() const { return "Saves object of given id to file of name file_name"; }
};
