#pragma once

#include "olcPixelGameEngine.h"
#include <bitset>

class Automaton
{
public:
	Automaton(unsigned int screenHeight);
	void Run(olc::PixelGameEngine* pge);
	unsigned int rule;

private:
	struct Private;
	std::bitset<256> currentGeneration;
	std::bitset<256> nextGeneration;
	unsigned int numGenerations;
	unsigned int row;
};