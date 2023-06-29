#pragma once

#include "olcPixelGameEngine.h"
#include "automaton.h"

class Console
{
public:
	Console(olc::PixelGameEngine* pge, Automaton* automaton);
	void OpenConsole();
	void CheckInput(const std::string& text);

private:
	struct Private;
	olc::PixelGameEngine* pge;
	const std::string commands[6] = { "help", "setstate", "setrule", "getrule", "run", "clear"};
	Automaton* automaton;
};