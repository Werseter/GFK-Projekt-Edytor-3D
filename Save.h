#pragma once

#include "BaseCommand.h"
#include <wx/filedlg.h>
#include <wx/log.h>
#include <fstream>

// save command saving objects to a file
class Save : public BaseCommand {
	public:
		// Initializing save command
		Save(MyFrame* app) : BaseCommand("save", 1, app) {}

		// Overridden Execute method, saves objects to file
		bool Execute(std::vector<std::string> args) {
			wxStreamToTextRedirector redirect(app -> m_textCtrlConsoleOutput);
			// Open dialog window for saving a file
			wxFileDialog saveFileDialog(app, wxT("Save XYZ file"), wxT(""), args[1] + ".geo", wxT("Geometry file (*.geo)|*.geo"), wxFD_SAVE | wxFD_OVERWRITE_PROMPT);

			// If user changes their mind and chooses cancel
			if (saveFileDialog.ShowModal() == wxID_CANCEL) {
				std::cout << "Aborted file saving operation" << std::endl;
				return false;
			}
			// Prepare an output stream to write points there
			std::ofstream out(std::string(saveFileDialog.GetPath()));

			//Save all objects' data to file
			for (BaseObject* obj : app -> geoObjects) {
				if (obj != nullptr) {
					out << obj->GetSaveData();
				}
			}

			return true;
		}

		// Overridden documentation methods
		std::string Args() const { return "file_name"; }
		std::string Help() const { return "Saves all objects to file of name file_name"; }
};
