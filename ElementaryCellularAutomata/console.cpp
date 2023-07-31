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
	std::cout << "help     - Display this message.\n";
	std::cout << "setrule  - Set the automaton [0, 255].\n";
	std::cout << "getrule  - Print the current automaton.\n";
	std::cout << "setstate - Set the initial generation state (left, right, center, random).\n";
	std::cout << "reset    - Clear screen and reset state.\n";
	std::cout << "clear    - Clear console history.\n";
	std::cout << "wrap     - Enable / disable wrapping\n\n";
	std::cout << "Available shortcuts:\n";
	std::cout << "CTRL - Run / pause\n";
	std::cout << "R    - Reset\n\n";
	std::cout << "Interesting rules: 30, 73, 90, 110, 184\n\n";
}

void Console::ParseInput(const std::string& text)
{
	auto tokens = Tokenize(text);
	if (tokens.empty())
		return;

	tokens.size() > 1 ? IdentifyCommand(tokens[0], tokens[1]) :
						IdentifyCommand(tokens[0]);
}

void Console::IdentifyCommand(const std::string& command, const std::string& argument)
{
	if (command == "setstate")
	{
		try { SetAutomatonState(argument); }
		catch (std::exception err) { std::cout << err.what(); }
	}
	else if (command == "setrule")
	{
		try { SetAutomatonRule(argument); }
		catch (std::exception err) { std::cout << err.what(); }
	}
	else
		std::cout << "Invalid command: '" << command + " " + argument << 
					 "'. Type 'help' for a list of commands.\n\n";
}

void Console::IdentifyCommand(const std::string& command)
{
	if (command == "help")
		PrintHelpText();
	else if (command == "getrule")
		std::cout << "Current rule: " << automaton->GetRule() << "\n\n";
	else if (command == "reset")
		automaton->Reset();
	else if (command == "clear")
		pge->ConsoleClear();
	else if (command == "wrap")
		automaton->ToggleWrap();
	else
		std::cout << "Invalid command: '" + command + "'. Type 'help' for a list of commands.\n\n";
}

void Console::SetAutomatonState(const std::string& state)
{
	const std::string err = "Invalid state: '" + state + "'. Valid states: left, right, center, random.\n\n";
	if (state == "center")
		automaton->SetState(States::CENTER);
	else if (state == "left")
		automaton->SetState(States::LEFT);
	else if (state == "right")
		automaton->SetState(States::RIGHT);
	else if (state == "random")
		automaton->SetState(States::RANDOM);
	else
		throw new std::exception(err.c_str());
	
	std::cout << "State set.\n\n";
}

void Console::SetAutomatonRule(const std::string& argument)
{
	const std::string err = "Invalid rule: '" + argument + "'. Value must be in range [0, 255].\n\n";
	int rule = 0;
	for (const char& c : argument)
		if (!isdigit(c))
			throw new std::exception(err.c_str());
	
	rule = std::stoi(argument);
	if (rule < 0 || rule > 255)
		throw new std::exception(err.c_str());

	std::cout << "Rule set to " << rule << ".\n\n";
	automaton->SetRule(rule);
}
