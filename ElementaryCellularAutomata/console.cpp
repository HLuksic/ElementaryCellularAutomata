#include "console.h"
#include <iostream>

Console::Console(Automaton* automaton)
{
	this->automaton = automaton;
}

static bool IsEmptyOrWhitespace(const std::string& text)
{
	return text.empty() || std::all_of(text.begin(), text.end(), isspace);
}

static auto Tokenize(const std::string& text)
{
	std::vector<std::string> tokens;
	std::istringstream iss(text);
	std::copy(std::istream_iterator<std::string>(iss), std::istream_iterator<std::string>(), std::back_inserter(tokens));
	return tokens;
}

static void PrintHelpText()
{
	std::cout << "Available commands:\n";
	std::cout << "help         - Displays this message.\n";
	std::cout << "run          - Runs the simulation (shortcut CTRL).\n";
	std::cout << "setrule      - Sets the automaton [0, 255].\n";
	std::cout << "getrule      - Prints the current automaton.\n";
	std::cout << "setstate     - Sets the initial generation state (left, right, center, random).\n";
	std::cout << "clear        - Clear screen (shortcut C).\n";
	std::cout << "clearconsole - Clear console history.\n\n";
}

void Console::ParseCommand(olc::PixelGameEngine* pge, const std::string& text)
{
	if (IsEmptyOrWhitespace(text))
	{
		pge->ConsoleClear();
		return;
	}

	auto tokens = Tokenize(text);
	bool NoArguments = tokens.size() == 1;

	if (NoArguments)
	{
		if (tokens[0] == "help")
			PrintHelpText();
		else if (tokens[0] == "run")
			automaton->ClearAndRun();
		else if (tokens[0] == "getrule")
			std::cout << "Current rule: " << automaton->GetRule() << "\n\n";
		else if (tokens[0] == "clear")
			automaton->Clear();
		else if (tokens[0] == "clearconsole")
			pge->ConsoleClear();
		else
			std::cout << "Invalid command: '" << text << "'. Type 'help' for a list of commands.\n\n";
		
		return;
	}

	if (tokens[0] == "setstate")
		SetAutomatonState(tokens[1]);
	else if (tokens[0] == "setrule")
		SetAutomatonRule(tokens[1]);
	else
		std::cout << "Invalid command: '" << text << "'. Type 'help' for a list of commands.\n\n";
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
		std::cout << "Invalid state: '" << state << "'. Valid states: left, right, center, random.\n\n";
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
		std::cout << "Invalid rule: '" << rule << "'. Value must be in range [0, 255].\n\n";
		return;
	}

	automaton->SetRule(rule);
}
