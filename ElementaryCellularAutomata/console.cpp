#include "console.h"
#include <iostream>

Console::Console(Automaton* automaton)
{
	this->automaton = automaton;
}

void Console::PrintHelpText()
{
	std::cout << "Available commands:\n";
	std::cout << "help         - Displays this message.\n";
	std::cout << "run          - Runs the simulation.\n";
	std::cout << "setrule      - Sets the automaton. [0, 255]\n";
	std::cout << "getrule      - Prints the current automaton.\n";
	std::cout << "setstate     - Sets the initial generation state. (left, right, center, random)\n";
	std::cout << "reset        - Resets the simulation.\n";
	std::cout << "clear        - Clear screen.\n";
	std::cout << "clearconsole - Clear console history.\n" << std::endl;
}

void Console::SetAutomatonState(const std::string& state)
{
	if (state == "left")
	{
		automaton->SetSpecificStartingState(0);
	}
	else if (state == "right")
	{
		automaton->SetSpecificStartingState(SCREEN_WIDTH - 1);
	}
	else if (state == "center")
	{
		automaton->SetSpecificStartingState(SCREEN_WIDTH / 2);
	}
	else if (state == "random")
	{
		automaton->SetRandomStartingState();
	}
	else
	{
		std::cout << "Invalid state: '" << state << "'. Valid states: left, right, center, random.\n" << std::endl;
		return;
	}

	automaton->Clear();
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

std::string Console::Trim(const std::string& text)
{
	std::string leftTrimmed = text.substr(text.find_first_not_of(" "));
	return leftTrimmed.substr(0, leftTrimmed.find_last_not_of(" ") + 1);
}

void Console::ParseCommand(olc::PixelGameEngine* pge, const std::string& text)
{
	std::string trimmedText = Trim(text);
	// first letter until space
	std::string command = trimmedText.substr(0, trimmedText.find(" "));
	// last space + 1 until end
	std::string argument = trimmedText.substr(trimmedText.find_last_of(" ") + 1);

	// command == argument means there is no arguments
	if (command == "help" && command == argument)
	{
		PrintHelpText();
	}
	else if (command == "run" && command == argument)
	{
		automaton->ClearAndRun();
	}
	else if (command == "getrule" && command == argument)
	{
		std::cout << "Current rule: " << automaton->GetRule() << "\n" << std::endl;
	}
	else if (command == "clear" && command == argument)
	{
		automaton->Clear();
	}
	else if (command == "clearconsole" && command == argument)
	{
		pge->ConsoleClear();
	}
	else if (command == "setstate")
	{
		SetAutomatonState(argument);
	}
	else if (command == "setrule")
	{
		SetAutomatonRule(argument);
	}
	else
	{
		std::cout << "Command not found: '" << trimmedText << "'. Type 'help' for a list of commands.\n" << std::endl;
	}
}
