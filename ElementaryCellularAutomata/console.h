#pragma once

#include "olcPixelGameEngine.h"
#include "automaton.h"

using CStringRef  = const std::string&;
using CmdNoArgMap = std::unordered_map<std::string, std::function<void(void)>>;
using CmdArgMap   = std::unordered_map<std::string, std::function<void(CStringRef)>>;
using CmdNoArgMapIt = CmdNoArgMap::const_iterator;
using CmdArgMapIt   = CmdArgMap::const_iterator;

class Console
{
public:
	Console(olc::PixelGameEngine* pge, Automaton* automaton);
	void ParseInput(CStringRef text);

private:
	void IdentifyCommand(CStringRef command, CStringRef argument);
	void SetAutomatonState(CStringRef state);
	void SetAutomatonRule(CStringRef rule);
	olc::PixelGameEngine* pge;
	CmdNoArgMap commandsNoArg;
	CmdArgMap commandsWithArg;
	Automaton* automaton;
};