#include "console.h"
#include <iostream>

Console::Console(olc::PixelGameEngine* pge, Automaton* automaton)
{
	this->pge = pge;
	this->automaton = automaton;
}

static auto Tokenize(const std::string& text)
{
	std::vector<std::string> tokens;
	std::istringstream iss(text);
	std::copy(std::istream_iterator<std::string>(iss),
			  std::istream_iterator<std::string>(), 
			  std::back_inserter(tokens));
	
	return tokens;
}

static void PrintHelpText()
{
	std::cout << "Available commands:\n";
	std::cout << "help     - Displays this message.\n";
	std::cout << "setrule  - Sets the automaton [0, 255].\n";
	std::cout << "getrule  - Prints the current automaton.\n";
	std::cout << "setstate - Sets the initial generation state (left, right, center, random).\n";
	std::cout << "reset    - Clear screen and reset state.\n";
	std::cout << "clear    - Clear console history.\n\n";
	std::cout << "Available shortcuts:\n";
	std::cout << "CTRL - Pause / unpause\n";
	std::cout << "R    - Reset\n\n";
	std::cout << "Interesting rules: 30, 73, 90, 110, 184\n\n";
}

void Console::ParseInput(const std::string& text)
{
	std::vector<std::string> tokens = Tokenize(text);

	if (tokens.empty())
		return;
	
	IdentifyCommand(tokens[0], tokens[1]);
}

void Console::IdentifyCommand(const std::string& command, const std::string& argument)
{
	if (command == "help")
		PrintHelpText();
	else if (command == "getrule")
		std::cout << "Current rule: " << automaton->GetRule() << "\n\n";
	else if (command == "reset")
		automaton->Reset();
	else if (command == "clear")
		pge->ConsoleClear();
	else if (command == "setstate")
		SetAutomatonState(argument);
	else if (command == "setrule")
		SetAutomatonRule(argument);
	else
		std::cout << "Invalid command: '" << command + " " + argument 
				  << "'. Type 'help' for a list of commands.\n\n";
}

void Console::SetAutomatonState(const std::string& state)
{
	if (state == "center")
		automaton->SetState(0);
	else if (state == "left")
		automaton->SetState(1);
	else if (state == "right")
		automaton->SetState(2);
	else if (state == "random")
		automaton->SetState(3);
	else
	{
		std::cout << "Invalid state: '" << state << "'. Valid states: left, right, center, random.\n\n";
		return;
	}

	automaton->Reset();
}

void Console::SetAutomatonRule(const std::string& argument)
{
	int rule = 0;

	try
	{
		rule = std::stoi(argument);
	}
	catch (...)
	{
		std::cout << "Invalid rule: '" << argument << "'. Value must be in range [0, 255].\n\n";
		return;
	}
	
	if (rule < 0 || rule > 255)
	{
		std::cout << "Invalid rule: '" << argument << "'. Value must be in range [0, 255].\n\n";
		return;
	}

	automaton->SetRule(rule);
}
