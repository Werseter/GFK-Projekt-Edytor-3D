#include "GUI.h"
#include "Commands.h"
#include <vector>

MyFrame::MyFrame(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style) : wxFrame(parent, id, title, pos, size, style) {
	this -> SetSizeHints(wxSize(600, 400), wxDefaultSize);

	wxBoxSizer*  bSizer1;
	wxBoxSizer*  bSizer2;
	wxGridSizer* gSizer1;


	bSizer1 = new wxBoxSizer(wxHORIZONTAL);
	bSizer2 = new wxBoxSizer(wxHORIZONTAL);
	gSizer1 = new wxGridSizer(2, 2, 0, 0);

	for(int i = 0; i < 4; ++i) {
		m_panels.push_back(new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL));
		m_panels.back() -> SetBackgroundColour(wxColour(255, 255, 255));
		gSizer1 -> Add(m_panels.back(), 1, wxBOTTOM | wxEXPAND | wxRIGHT, 1);
	}

	bSizer2 -> Add(gSizer1, 1, wxEXPAND, 5);
	bSizer1 -> Add(bSizer2, 1, wxEXPAND, 5);

	wxBoxSizer* bSizer3;
	bSizer3  = new wxBoxSizer(wxVERTICAL);
	bSizer3 -> SetMinSize(wxSize(350, 350));

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

	GenerateDefaultPanelCasters();

	commands.push_back(new PrintHelp(this));

	commands.push_back(new SetLineColor(this));

	commands.push_back(new CreateLine(this));
	commands.push_back(new CreateBox(this));
	commands.push_back(new CreateSphere(this));
	commands.push_back(new CreateCone(this));
	commands.push_back(new CreateCylinder(this));

	commands.push_back(new Delete(this));
	commands.push_back(new ClearAll(this));
	commands.push_back(new MoveObj(this));
	commands.push_back(new Rotate(this));
	commands.push_back(new Save(this));
	commands.push_back(new Load(this));
}

MyFrame::~MyFrame() {
	std::for_each(m_panels.begin(), m_panels.end(), [](wxPanel* x) { delete x; });
	m_panels.clear();
	panelCasters.clear();
	std::for_each(commands.begin(), commands.end(), [](BaseCommand* x) { delete x; });
	commands.clear();
	std::for_each(geoObjects.begin(), geoObjects.end(), [](BaseObject* x) { delete x; });
	geoObjects.clear();
	delete m_textCtrlObjList;
	delete m_textCtrlConsoleInput;
	delete m_textCtrlConsoleOutput;
}

void MyFrame::GenerateDefaultPanelCasters() {
	for (int i = 0; i < 1; ++i) {

		Matrix4 transform1;
		transform1.data[0][0] = 1;
		transform1.data[1][1] = 1;
		transform1.data[2][2] = 1;
		transform1.data[2][3] = -2;

		Matrix4 transform2;
		transform2.data[0][(0+i)%3] = 1;
		transform2.data[1][(1+i)%3] = 1;
		transform2.data[3][(2+i)%3] = 1.0 / -2;

		Matrix4 transform3;
		wxSize panelSize = m_panels[i] -> GetSize();
		transform3.data[0][0] =  panelSize.GetWidth () / 2;
		transform3.data[1][1] = -panelSize.GetHeight() / 2;
		transform3.data[0][3] =  transform3.data[0][0];
		transform3.data[1][3] = -transform3.data[1][1];

		panelCasters.push_back(transform3 * transform2 * transform1);
	}
}

bool MyFrame::isNumber(const std::string& s) {
    try { std::stod(s); }
    catch(...) { return false; }
    return true;
}

bool MyFrame::CheckArgumentsIfIntOrDouble(std::vector<std::string> args) {
	for (unsigned int i=1; i<args.size(); ++i) {
		if (!isNumber(args[i]))
			return false;
	}
	return true;
}

void MyFrame::ProcessConsoleInput(wxCommandEvent& WXUNUSED(e)) {
	// Prepare vector for arguments
	std::vector<std::string> args;

	// Take all arguments form the input console and store them in string
	std::string input = std::string((m_textCtrlConsoleInput -> GetLineText(0)).c_str());

	// Split them into words, first argument is function name
	while (input.size()) {
	 int index = input.find(" ");
	 if (index != std::string::npos) {
		 if (input[0] != ' ') {
			 args.push_back(input.substr(0, index));
			 input = input.substr(index + 1);
		 }
		 else {
			 input = input.substr(1);
		 }
	 }
	 else {
		 args.push_back(input);
		 input = "";
	 }
 }

	// Redirect all outputs to output console
	wxStreamToTextRedirector redirect(m_textCtrlConsoleOutput);

	// Create an iterator in order to find the right command in commands
	std::vector<BaseCommand*>::iterator cmdIt = std::find_if(commands.begin(), commands.end(), [&args](BaseCommand* cmd) { return cmd -> GetName() == args[0]; });

	// This if indicates that function was found
	if (cmdIt != commands.end()) {

		// Check if enough aguments were given
		if (args.size() - 1 == (*cmdIt) -> GetArgumentsCount() || -1 == (*cmdIt) -> GetArgumentsCount()) {

			// Check arguments' format
			if (CheckArgumentsIfIntOrDouble(args)) {

				// If all checks went fine then execute function
				if ((*cmdIt) -> Execute(args)) {
					for (std::string& arg : args) std::cout << arg << " ";
					std::cout << std::endl;
				}

			}

			// If arguments had bad format tell user about the right format and print given arguments
			else {
				std::cout << "Arguments need to be either integer or double (given arguments:";
				for (unsigned int i=1; i<args.size(); ++i)
					std::cout << " " << args[i];
				std::cout << ")" << std::endl;
			}

		}
		// If not enough arguments were given thell user about this and print how many arguments were given
		else  std::cout << "Function \"" << args[0] << "\" takes " << (*cmdIt) -> GetArgumentsCount() << " arguments (" << args.size() - 1 << " given)" << std::endl;
	}
	// If the function wasn't found tell the user about it
	else std::cout << "Unknown function \"" << args[0] << "\"" << std::endl;

	// Clear input console
	m_textCtrlConsoleInput -> Clear();
}

void MyFrame::UpdateObjList() {
	m_textCtrlObjList -> Clear();
	drawingData.clear();

	for (BaseObject* obj : geoObjects) {
		if (obj != nullptr) {
			m_textCtrlObjList -> AppendText(obj -> Repr());
			m_textCtrlObjList -> AppendText("\n");
			drawingData.push_back(obj -> GetData());
		}
	}
}

void MyFrame::UpdateObjList(BaseObject* obj) {
	m_textCtrlObjList -> AppendText(obj -> Repr());
	m_textCtrlObjList -> AppendText("\n");
	drawingData.push_back(obj -> GetData());
}


void MyFrame::Draw() {
	Vector4 pt1, pt2;
	for (wxPanel* panel : m_panels) {
		if (panel -> GetSize().x > 0 && panel -> GetSize().y > 0 && drawingData.size() > 0) {
			wxBitmap buffer = wxBitmap(panel -> GetSize());
			wxClientDC _MyDC(panel);
			wxBufferedDC MyDC(&_MyDC, buffer);
			MyDC.SetBackground(*wxBLACK_BRUSH);
			MyDC.Clear();
			MyDC.SetPen(wxPen(drawingColor));
			for (const DataVector* data : drawingData) {
				for (Data3D points : *data) {
					pt1.Set(points[0], points[1], points[2]);
					pt2.Set(points[3], points[4], points[5]);
					pt1 = (panelCasters[0] * pt1).Normalize();
					pt2 = (panelCasters[0] * pt2).Normalize();
					MyDC.DrawLine(pt1.GetX(), pt1.GetY(), pt2.GetX(), pt2.GetY());
				}
			}
			break;
		}
	}
}

void MyFrame::Form_Update(wxUpdateUIEvent& WXUNUSED(e)) {
	Draw();
}
