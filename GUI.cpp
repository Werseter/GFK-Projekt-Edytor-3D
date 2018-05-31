#include "GUI.h"
#include <vector>

MyFrame::MyFrame(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style) : wxFrame(parent, id, title, pos, size, style) {
	this -> SetSizeHints(wxSize(600, 400), wxDefaultSize);

	wxBoxSizer*  bSizer1;
	wxBoxSizer*  bSizer2;
	wxGridSizer* gSizer1;


	bSizer1 = new wxBoxSizer(wxHORIZONTAL);
	bSizer2 = new wxBoxSizer(wxHORIZONTAL);
	gSizer1 = new wxGridSizer(2, 2, 0, 0);

	m_panel1  = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
	m_panel1 -> SetBackgroundColour(wxColour(255, 255, 255));

	m_panel2  = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
	m_panel2 -> SetBackgroundColour(wxColour(255, 255, 255));

	m_panel3  = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
	m_panel3 -> SetBackgroundColour(wxColour(255, 255, 255));

	m_panel4  = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
	m_panel4 -> SetBackgroundColour(wxColour(255, 255, 255));

	gSizer1 -> Add(m_panel1, 1, wxBOTTOM | wxEXPAND | wxRIGHT, 1);
	gSizer1 -> Add(m_panel2, 1, wxBOTTOM | wxEXPAND | wxLEFT,  1);
	gSizer1 -> Add(m_panel3, 1, wxEXPAND | wxRIGHT  | wxTOP,   1);
	gSizer1 -> Add(m_panel4, 1, wxEXPAND | wxLEFT   | wxTOP,   1);

	bSizer2 -> Add(gSizer1, 1, wxEXPAND, 5);
	bSizer1 -> Add(bSizer2, 1, wxEXPAND, 5);

	wxBoxSizer* bSizer3;
	bSizer3  = new wxBoxSizer(wxVERTICAL);
	bSizer3 -> SetMinSize(wxSize(200, 350));
	
	m_textCtrlObjList       = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_RICH | wxTE_READONLY | wxTE_MULTILINE | wxTE_WORDWRAP);
	m_textCtrlConsoleOutput = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_RICH | wxTE_READONLY | wxTE_MULTILINE | wxTE_WORDWRAP);
	m_textCtrlConsoleInput  = new wxTextCtrl(this, ID_WXTEXTCTRLCONSOLE, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);

	bSizer3 -> Add(m_textCtrlObjList,       3, wxEXPAND | wxALL,            5);
	bSizer3 -> Add(m_textCtrlConsoleOutput, 1, wxEXPAND | wxLEFT | wxRIGHT, 5);
	bSizer3 -> Add(m_textCtrlConsoleInput,  0, wxEXPAND | wxALL,            5);


	bSizer1 -> Add(bSizer3, 0, wxEXPAND, 5);

	this -> SetSizer(bSizer1);
	this -> Layout();
	this -> Centre(wxBOTH);

	Bind(wxEVT_TEXT_ENTER, &MyFrame::ProcessConsoleInput, this, ID_WXTEXTCTRLCONSOLE);
	Bind(wxEVT_UPDATE_UI,  &MyFrame::Form_Update, this);
}

MyFrame::~MyFrame() {
	delete m_panel1;
	delete m_panel2;
	delete m_panel3;
	delete m_panel4;
	delete m_textCtrlObjList;
	delete m_textCtrlConsoleInput;
	delete m_textCtrlConsoleOutput;
}

void MyFrame::ProcessConsoleInput(wxCommandEvent& WXUNUSED(e)) {
	wxStreamToTextRedirector redirect(m_textCtrlConsoleOutput);
	std::cout << m_textCtrlConsoleInput -> GetLineText(0) << std::endl;
	m_textCtrlConsoleInput -> Clear();
}

void MyFrame::Draw() {
	std::vector<wxPanel*> panels = { m_panel1, m_panel2, m_panel3, m_panel4 };
	wxBitmap buffer = wxBitmap(m_panel1 -> GetSize());
	for (wxPanel* panel : panels) {
		wxClientDC _MyDC(panel);
		wxBufferedDC MyDC(&_MyDC, buffer);
		//MyDC.DrawBitmap(jakastambitmapazestuffemzrenderowanym, 0, 0);
	}
}

void MyFrame::Form_Update(wxUpdateUIEvent& WXUNUSED(e)) {
	Draw();
}
