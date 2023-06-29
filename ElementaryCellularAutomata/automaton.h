#pragma once

#include "olcPixelGameEngine.h"
#include <bitset>

constexpr unsigned int SCREEN_WIDTH = 760;

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
	std::bitset<SCREEN_WIDTH> currentGeneration;
	std::bitset<SCREEN_WIDTH> nextGeneration;
	unsigned int numGenerations;
	unsigned int row;
	unsigned int rule;
};