#pragma once

#include "olcPixelGameEngine.h"
#include "automaton.h"

class Console
{
public:
	Console(Automaton* automaton);
	void ParseCommand(olc::PixelGameEngine* pge, const std::string& text);

private:
	void PrintHelpText();
	void SetAutomatonState(const std::string& state);
	void SetAutomatonRule(const std::string& argument);
	Automaton* automaton;
};