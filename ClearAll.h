#pragma once

#include "BaseCommand.h"

// clear_all command clearing everything in the console
class ClearAll : public BaseCommand {
	public:
		// Initializing clear_all command
		ClearAll(MyFrame* app) : BaseCommand("clear_all", 0, app) {}

		// Overridden Execute method, clears everything in the console
		bool Execute(std::vector<std::string> args) { app -> m_textCtrlConsoleOutput -> Clear(); return false; }

		// Overridden Args() method returning an empty string -- clear_all takes 0 arguments
		std::string Args() const { return ""; }

		// Overridden documentation method
		std::string Help() const { return "Clears the console"; }
};
