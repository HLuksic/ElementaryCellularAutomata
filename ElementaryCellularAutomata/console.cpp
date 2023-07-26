#include "console.h"
#include <iostream>

Console::Console(Automaton* automaton)
{
	this->automaton = automaton;
}


void Console::SetAutomatonState(const std::string& state)
{
	if (state == "left")
		automaton->SetSpecificStartingState(0);
	else if (state == "right")
		automaton->SetSpecificStartingState(automaton->GetWidth() - 1);
	else if (state == "center")
		automaton->SetSpecificStartingState(automaton->GetWidth() / 2);
	else if (state == "random")
		automaton->SetRandomStartingState();
	else
		std::cout << "Invalid state: '" << state << "'. Valid states: left, right, center, random.\n" << std::endl;
}

void Console::SetAutomatonRule(const std::string& argument)
{
	int rule = std::stoi(argument);
		
	if (rule < 0 || rule > 255)
	{
		std::cout << "Invalid rule: '" << rule << "'. Value must be in range [0, 255].\n" << std::endl;
		return;
	}

	automaton->SetRule(rule);
}

auto PrintHelpText = []()
{
	std::cout << "Available commands:\n";
	std::cout << "help         - Displays this message.\n";
	std::cout << "run          - Runs the simulation (shortcut CTRL).\n";
	std::cout << "setrule      - Sets the automaton [0, 255].\n";
	std::cout << "getrule      - Prints the current automaton.\n";
	std::cout << "setstate     - Sets the initial generation state (left, right, center, random).\n";
	std::cout << "clear        - Clear screen (shortcut C).\n";
	std::cout << "clearconsole - Clear console history.\n" << std::endl;
};

auto IsEmptyOrWhitespace = [](const std::string& text) -> bool
{
	return text.empty() || std::all_of(text.begin(), text.end(), isspace);
};

auto Trim = [](const std::string& text) -> std::string
{
	std::string leftTrimmed = text.substr(text.find_first_not_of(" "));
	return leftTrimmed.substr(0, leftTrimmed.find_last_not_of(" ") + 1);
};

void Console::ParseCommand(olc::PixelGameEngine* pge, const std::string& text)
{
	if (IsEmptyOrWhitespace(text))
	{
		pge->ConsoleClear();
		return;
	}
	
	std::string trimmedText = Trim(text);
	std::string command = trimmedText.substr(0, trimmedText.find(" "));
	std::string argument = Trim(trimmedText.substr(trimmedText.find_first_of(" ")));
	bool NoArguments = command == argument;

	if (command == "help" && NoArguments)
		PrintHelpText();
	else if (command == "run" && NoArguments)
		automaton->ClearAndRun();
	else if (command == "getrule" && NoArguments)
		std::cout << "Current rule: " << automaton->GetRule() << "\n" << std::endl;
	else if (command == "clear" && NoArguments)
		automaton->Clear();
	else if (command == "clearconsole" && NoArguments)
		pge->ConsoleClear();
	else if (command == "setstate")
		SetAutomatonState(argument);
	else if (command == "setrule")
		SetAutomatonRule(argument);
	else
		std::cout << "Command not found: '" << trimmedText << "'. Type 'help' for a list of commands.\n" << std::endl;
}
