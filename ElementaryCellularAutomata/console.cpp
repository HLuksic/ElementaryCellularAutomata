#include "console.h"
#include <iostream>

struct Console::Private
{
	static void ParseCommand(const std::string& text)
	{
		if (text == "help")
		{
			PrintHelpText();
		}
		else if (text == "reset")
		{
			std::cout << "Resetting simulation..." << std::endl;
		}
		else if (text == "setstate")
		{
			std::cout << "Setting initial state..." << std::endl;
		}
		else if (text == "start")
		{
			std::cout << "Starting simulation..." << std::endl;
		}
		/*else if (command == "setrule")
		{
			std::string rule = text.substr(text.find(' ') + 1);
			try
			{
				self->automaton->SetRule(std::stoi(rule));
	}

	static void PrintHelpText()
	{
		std::cout << "Available commands:" << std::endl;
		std::cout << "help - Displays this message." << std::endl;
		std::cout << "reset - Resets the simulation." << std::endl;
		std::cout << "setstate (left, right, center, random) - Sets the initial generation state." << std::endl;
		std::cout << "setrule (0 - 255) - Sets the automaton." << std::endl;
		std::cout << "start - Starts the simulation." << std::endl;
	}
};

void Console::OpenConsole(olc::PixelGameEngine* pge)
{
	if (pge->GetKey(olc::Key::TAB).bPressed)
	{
		pge->ConsoleShow(olc::Key::TAB, true);
	}
}

void Console::CheckInput(const std::string& text)
{
	if (std::find(std::begin(commands), std::end(commands), text) == std::end(commands))
	{
		std::cout << "Command not found: " << text << ".Type 'help' for a list of commands." << std::endl;
		return;
	}
	
	Private::ParseCommand(text);
}


