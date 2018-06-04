#pragma once

#include "BaseCommand.h"

// help command printing help for functions
class PrintHelp : public BaseCommand {
	public:
    // Initializing help command
		PrintHelp(MyFrame* app) : BaseCommand("help", -1, app) {}

    // Overrided Execute method
		bool Execute(std::vector<std::string> args) {
			wxStreamToTextRedirector redirect(app -> m_textCtrlConsoleOutput);

			if (args.size() - 1 == 0) {
				for (BaseCommand* cmd : app->commands)
					std::cout << cmd->GetName() << " " << cmd->Args() << std::endl << cmd->Help() << std::endl << (cmd != (app->commands.back()) ? "\n" : "");
			}

			else {
				std::vector<BaseCommand*>::iterator cmdIt = std::find_if(app->commands.begin(), app -> commands.end(), [&args](BaseCommand* cmd) { return cmd->GetName() == args[1]; });

				if (cmdIt != app->commands.end()) {
					std::cout << args[1] << " " << (*cmdIt) -> Args() << std::endl << (*cmdIt) -> Help() << std::endl;
				}

				else std::cout << "Nieznana funkcja \"" << args[1] << "\"" << std::endl;
			}

			return false;
		}

    // // Overrided Args() method and documentation method
		std::string Args() const { return "function name"; }
		std::string Help() const { return "Prints help"; }
};
