#pragma once

#include <wx/string.h>
#include <wx/font.h>
#include <wx/textctrl.h>
#include <wx/sizer.h>
#include <wx/panel.h>
#include <wx/frame.h>
#include <wx/dcbuffer.h>
#include <wx/gdicmn.h>
#include <algorithm>
#include <vector>
#include "BaseObject.h"
#include "vecmat.h"

class BaseCommand;

class MyFrame : public wxFrame {
	public:
		// Functions maintaing what is written on a console
		// Updates the whole list (used in delete)
		void UpdateObjList();
		// Pushes back new object
		void UpdateObjList(BaseObject* obj);

		void GenerateDefaultPanelCasters();

		// PARSER
		// Main function processing responsible for processing input
		void ProcessConsoleInput(wxCommandEvent&  e);
	  // Helper function checking if argument given as a string is integer or double
	  bool isNumber(const std::string& s);
	  // Function using isNumber to determine whether given arguments were correct
	  bool CheckArgumentsIfIntOrDouble(std::vector<std::string> args);

		void Draw();
		void Form_Update(wxUpdateUIEvent& e);

		enum {
			ID_WXTEXTCTRLCONSOLE = 1001,
		};

		wxTextCtrl* m_textCtrlObjList;
		wxTextCtrl* m_textCtrlConsoleInput;
		wxTextCtrl* m_textCtrlConsoleOutput;

		std::vector<wxPanel*> m_panels;
		std::vector<Matrix4>  panelCasters;

		std::vector<BaseCommand*> commands;
		std::vector<BaseObject*>  geoObjects;

		wxColor drawingColor = wxColor(*wxGREEN);
		std::vector<const DataVector*> drawingData;

		MyFrame (wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(600, 400), long style = wxDEFAULT_FRAME_STYLE | wxTAB_TRAVERSAL);
		~MyFrame();
};
