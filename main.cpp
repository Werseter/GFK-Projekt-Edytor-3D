#include <wx/wx.h>
#include "GUI.h"

class MyApp : public wxApp {
	public:
		virtual bool OnInit() {
			MyFrame *frame = new MyFrame(NULL, wxID_ANY, "GFK Projekt 45 2018", wxDefaultPosition, wxSize(1116, 577));
			frame -> Show(true);
			SetTopWindow(frame);
			return true;
		}
};

IMPLEMENT_APP(MyApp);
//wxIMPLEMENT_APP_CONSOLE(MyApp);
