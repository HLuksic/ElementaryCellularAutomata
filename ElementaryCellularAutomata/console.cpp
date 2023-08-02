#include "console.h"
#include <iostream>
#include <cstdarg>

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

Console::Console(olc::PixelGameEngine* pge, Automaton* automaton)
{
	this->pge = pge;
	this->automaton = automaton;
	commandsNoArg["help"] = PrintHelpText;
	commandsNoArg["getrule"] = [&]() { std::cout << "Current rule: " << this->automaton->GetRule() << "\n\n"; };
	commandsNoArg["reset"] = [&]() { this->automaton->Reset(); };
	commandsNoArg["clear"] = [&]() { this->pge->ConsoleClear(); };
	commandsNoArg["wrap"] = [&]() { this->automaton->ToggleWrap(); };
	commandsWithArg["setstate"] = [&](CStringRef arg) { this->SetAutomatonState(arg); };
	commandsWithArg["setrule"] = [&](CStringRef arg) { this->SetAutomatonRule(arg); };
}

static auto Tokenize(CStringRef text)
{
	std::vector<std::string> tokens;
	std::istringstream iss(text);
	std::copy(std::istream_iterator<std::string>(iss),
              std::istream_iterator<std::string>(), 
              std::back_inserter(tokens));
	return tokens;
}

void Console::ParseInput(CStringRef text)
{
	auto tokens = Tokenize(text);
	if (tokens.empty())
		return;

	tokens.size() > 1 ? IdentifyCommand(tokens[0], tokens[1]) :
						IdentifyCommand(tokens[0], " ");
}

void Console::IdentifyCommand(CStringRef command, CStringRef argument)
{
	CmdNoArgMapIt noArgIt = commandsNoArg.find(command);
	CmdArgMapIt argIt = commandsWithArg.find(command);

	if (noArgIt != commandsNoArg.end())
	{
		noArgIt->second();
		return;
	}
	if (argIt != commandsWithArg.end())
	{
		argIt->second(argument);
		return;
	}
	std::cout << "Invalid command: '" << command << "'. Type 'help' for a list of commands.\n\n";
}

void Console::SetAutomatonState(CStringRef state)
{
	if (state == "center")
		automaton->SetState(States::CENTER);
	else if (state == "left")
		automaton->SetState(States::LEFT);
	else if (state == "right")
		automaton->SetState(States::RIGHT);
	else if (state == "random")
		automaton->SetState(States::RANDOM);
	else
	{
		std::cout << "Invalid state: '" + state + "'. Valid states: left, right, center, random.\n\n";
		return;
	}
	std::cout << "State set.\n\n";
}

void Console::SetAutomatonRule(CStringRef argument)
{
	for (const char& c : argument)
	{
		if (!isdigit(c))
		{
			std::cout << "Invalid rule: '" + argument + "'. Value must be in range [0, 255].\n\n"; 
			return;
		}
	}
	int rule = std::stoi(argument);
	if (rule < 0 || rule > 255)
	{
		std::cout << "Invalid rule: '" + argument + "'. Value must be in range [0, 255].\n\n";
		return;
	}
	std::cout << "Rule set to " << rule << ".\n\n";
	automaton->SetRule(rule);
}
