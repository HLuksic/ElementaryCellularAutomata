#pragma once

#include "olcPixelGameEngine.h"
#include "automaton.h"

class Console
{
public:
	Console(olc::PixelGameEngine* pge, Automaton* automaton);
	void ParseInput(const std::string& text);

private:
	void IdentifyCommand(const std::string& command);
	void IdentifyCommand(const std::string& command, const std::string& argument);
	void SetAutomatonState(const std::string& state);
	void SetAutomatonRule(const std::string& rule);
	Automaton* automaton;
	olc::PixelGameEngine* pge;
};