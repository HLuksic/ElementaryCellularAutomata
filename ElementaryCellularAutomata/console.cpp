#include "console.h"
#include <iostream>

struct Console::Private
{
	static void ParseCommand(Console* self, const std::string& text)
	{
		std::string command = text.substr(0, text.find(' '));
		std::string argument = text.substr(text.find(' ') + 1);
		
		if (command == "help")
		{
			PrintHelpText();
		}
		else if (command == "run")
		{
			self->automaton->run = true;
			self->automaton->Reset();
		}
		else if (command == "getrule")
		{
			std::cout << "Current rule: " << self->automaton->GetRule() << std::endl;
		}
		else if (command == "setstate")
		{
			SetAutomatonState(self, argument);
		}
		else if (command == "setrule")
		{
			SetAutomatonRule(self, argument);
		}
		else if (command == "reset")
		{
			self->automaton->Reset();
		}
		else if (command == "clear")
		{
			self->pge->ConsoleClear();
		}
		else
		{
			std::cout << "Command not found: '" << command << "'. Type 'help' for a list of commands." << std::endl;
		}
	}

	static void PrintHelpText()
	{
		std::cout << "Available commands:\n";
		std::cout << "help     - Displays this message.\n";
		std::cout << "run      - Runs the simulation.\n";
		std::cout << "setrule  - Sets the automaton. [0, 255]\n";
		std::cout << "getrule  - Prints the current automaton.\n";
		std::cout << "setstate - Sets the initial generation state. (left, right, center, random)\n";
		std::cout << "reset    - Resets the simulation.\n";
		std::cout << "clear    - Clear console history.\n" << std::endl;
	}

	static void SetAutomatonState(Console* self, const std::string& state)
	{
		if (state == "left")
		{
			self->automaton->SetSpecificStartingState(0);
		}
		else if (state == "right")
		{
			self->automaton->SetSpecificStartingState(255);
		}
		else if (state == "center")
		{
			self->automaton->SetSpecificStartingState(127);
		}
		else if (state == "random")
		{
			self->automaton->SetRandomStartingState();
		}
		else
		{
			std::cout << "Invalid state: '" << state << "'. Valid states: left, right, center, random.\n" << std::endl;
		}
	}

	static void SetAutomatonRule(Console* self, const std::string& argument)
	{
		int rule = std::stoi(argument);
		
		if (rule < 0 || rule > 255)
		{
			std::cout << "Invalid rule: '" << rule << "'. Value must be in range [0, 255].\n" << std::endl;
			return;
		}

		self->automaton->SetRule(rule);
	}
};

Console::Console(olc::PixelGameEngine* engine, Automaton* automaton)
{
	this->pge = engine;
	this->automaton = automaton;
}

void Console::OpenConsole()
{
	if (pge->GetKey(olc::Key::TAB).bPressed)
	{
		pge->ConsoleShow(olc::Key::TAB, true);
	}
}

void Console::CheckInput(const std::string& text)
{
	if (pge->GetKey(olc::Key::A).bPressed)
	{
		automaton->run = true;
		automaton->Reset();
	}

	Private::ParseCommand(this, text);
}


