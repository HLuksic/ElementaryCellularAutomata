#pragma once

#include "olcPixelGameEngine.h"
#include <bitset>

class Automaton
{
public:
	Automaton(olc::PixelGameEngine* pge, unsigned int screenHeight);
	void Run();
	void SetRule(unsigned int rule);
	void SetSpecificStartingState(unsigned int state);
	void SetRandomStartingState();
	void Reset();
	unsigned int GetRule();
	bool run;
	
private:
	struct Private;
	olc::PixelGameEngine* pge;
	std::bitset<256> currentGeneration;
	std::bitset<256> nextGeneration;
	unsigned int numGenerations;
	unsigned int row;
	unsigned int rule;
};