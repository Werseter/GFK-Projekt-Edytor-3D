#pragma once

#include <wx/string.h>
#include <wx/font.h>
#include <wx/textctrl.h>
#include <wx/sizer.h>
#include <wx/panel.h>
#include <wx/frame.h>
#include <wx/dcbuffer.h>

class MyFrame : public wxFrame {
	private:
		void ProcessConsoleInput(wxCommandEvent&  e);

		void Draw();
		void Form_Update(wxUpdateUIEvent& e);

		enum {
			ID_WXTEXTCTRLCONSOLE = 1001,
		};
		
		wxPanel*    m_panel1;
		wxPanel*    m_panel2;
		wxPanel*    m_panel3;
		wxPanel*    m_panel4;
		wxTextCtrl* m_textCtrlObjList;
		wxTextCtrl* m_textCtrlConsoleInput;
		wxTextCtrl* m_textCtrlConsoleOutput;


	public:
		MyFrame (wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(600, 400), long style = wxDEFAULT_FRAME_STYLE | wxTAB_TRAVERSAL);
		~MyFrame();
};