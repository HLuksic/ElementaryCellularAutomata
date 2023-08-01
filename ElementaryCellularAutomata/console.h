#pragma once

#include "olcPixelGameEngine.h"
#include "automaton.h"

typedef std::unordered_map<std::string, std::function<void(void)>> CmdNoArgMap;
typedef std::unordered_map<std::string, std::function<void(const std::string&)>> CmdArgMap;
typedef CmdNoArgMap::const_iterator CmdNoArgMapIt;
typedef CmdArgMap::const_iterator CmdArgMapIt;


class Console
{
public:
	Console(olc::PixelGameEngine* pge, Automaton* automaton);
	void ParseInput(const std::string& text);

private:
	void IdentifyCommand(const std::string& command, const std::string& argument);
	void SetAutomatonState(const std::string& state);
	void SetAutomatonRule(const std::string& rule);
	olc::PixelGameEngine* pge;
	CmdNoArgMap commandsNoArg;
	CmdArgMap commandsWithArg;
	Automaton* automaton;
};