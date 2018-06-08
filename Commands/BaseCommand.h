#pragma once

#include "../GUI.h"
#include <vector>

// Base class for various commands
class BaseCommand {
	protected:
		// Commands have names and arguments, here we have name and number of arguments
		std::string name;
		unsigned int nArguments;
		MyFrame* app;

	public:
		// Constructor initializing a command
		BaseCommand(std::string name, int nArguments, MyFrame* app) : name(name), nArguments(nArguments), app(app) {}

		// Getters for name and number of arguments of the commans
		std::string GetName() const { return name; }
		int GetArgumentsCount() const { return nArguments; }

		// Virtual functions to override: executing, printing expected arguments and printing help
		virtual bool Execute(std::vector<std::string> args) = 0;
		virtual std::string Args() const = 0;
		virtual std::string Help() const = 0;
};
