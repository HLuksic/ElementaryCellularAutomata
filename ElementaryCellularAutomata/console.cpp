#include "console.h"
#include <iostream>

void Console::PrintHelpText()
{
	std::cout << "Available commands:\n";
	std::cout << "help		   - Displays this message.\n";
	std::cout << "run		   - Runs the simulation.\n";
	std::cout << "setrule	   - Sets the automaton. [0, 255]\n";
	std::cout << "getrule	   - Prints the current automaton.\n";
	std::cout << "setstate	   - Sets the initial generation state. (left, right, center, random)\n";
	std::cout << "reset        - Resets the simulation.\n";
	std::cout << "clear        - Clear screen.\n" << std::endl;
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
	}
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

Console::Console(Automaton* automaton)
{
	this->automaton = automaton;
}

void Console::ParseCommand(olc::PixelGameEngine* pge, const std::string& text)
{
	std::string command = text.substr(0, text.find(' '));
	std::string argument = text.substr(text.find(' ') + 1);

	if (command == "help")
	{
		PrintHelpText();
	}
	else if (command == "run")
	{
		automaton->ClearAndRun();
	}
	else if (command == "getrule")
	{
		std::cout << "Current rule: " << automaton->GetRule() << "\n" << std::endl;
	}
	else if (command == "setstate")
	{
		automaton->Clear();
		SetAutomatonState(argument);
	}
	else if (command == "setrule")
	{
		SetAutomatonRule(argument);
	}
	else if (command == "clear")
	{
		automaton->Clear();
	}
	else if (command == "clearconsole")
	{
		pge->ConsoleClear();
	}
	else
	{
		std::cout << "Command not found: '" << command << "'. Type 'help' for a list of commands.\n" << std::endl;
	}
}
