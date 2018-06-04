#pragma once

#include "GUI.h"
#include "GeoObject.h"
#include <vector>

class BaseCommand {
	protected:
		std::string name;
		int nArguments;
		MyFrame* app;
	public:
		BaseCommand(std::string _name, int n, MyFrame* _app) : name(_name), nArguments(n), app(_app) {}
		std::string GetName() const { return name; }
		int GetNArguments() const { return nArguments; }
		virtual bool Execute(std::vector<std::string> args) = 0;
		virtual std::string Args() const = 0;
		virtual std::string Help() const = 0;
};

class CmdCls : public BaseCommand {
	public:
		CmdCls(MyFrame* app) : BaseCommand("cls", 0, app) {}
		bool Execute(std::vector<std::string> args) { app -> m_textCtrlConsoleOutput -> Clear(); return false; }
		std::string Args() const { return ""; }
		std::string Help() const { return "Czysci konsole"; }
};

class CmdHelp : public BaseCommand {
	public:
		CmdHelp(MyFrame* app) : BaseCommand("help", -1, app) {}
		bool Execute(std::vector<std::string> args) {
			wxStreamToTextRedirector redirect(app -> m_textCtrlConsoleOutput);
			if (args.size() - 1 == 0) {
				for (BaseCommand* cmd : app -> commands) {
					std::cout << cmd -> GetName() << " " << cmd -> Args() << std::endl << cmd -> Help() << std::endl << (cmd != (app -> commands.back()) ? "\n" : "");
				}
			}
			else {
				std::vector<BaseCommand*>::iterator cmdIt = std::find_if(app -> commands.begin(), app -> commands.end(), [&args](BaseCommand* cmd) { return cmd -> GetName() == args[1]; });
				if (cmdIt != app -> commands.end()) {
					std::cout << args[1] << " " << (*cmdIt) -> Args() << std::endl << (*cmdIt) -> Help() << std::endl;
				}
				else {
					std::cout << "Nieznana funkcja \"" << args[1] << "\"" << std::endl;
				}

			}
			return false;
		}
		std::string Args() const { return "polecenie"; }
		std::string Help() const { return "Wyswietla pomoc"; }
};

class CmdSphere : public BaseCommand {
	public:
		CmdSphere(MyFrame* app) : BaseCommand("sphere", 6, app) {}
		bool Execute(std::vector<std::string> args) { 
			std::vector<float> temp(3);
			temp[0] = atof(args[1].c_str());
			temp[1] = atof(args[2].c_str());
			temp[2] = atof(args[3].c_str());
			app -> geoObjects.push_back(new Sphere(temp, atof(args[4].c_str()), atoi(args[5].c_str()), atoi(args[6].c_str())));
			app -> UpdateObjList();
			return true;
		}
		std::string Args() const { return "(x, y, z), r, (n, m)"; }
		std::string Help() const { return "Rysuje sfere o srodku w punkcie (x, y, z) i promieniu r, gdzie (n, m) oznacza na ile \"poludnikow\" i \"rownoleznikow\" ma byc podzielona kula."; }
};