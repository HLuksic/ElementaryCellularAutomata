#pragma once

#include "olcPixelGameEngine.h"

class Automaton
{
public:
	Automaton(olc::PixelGameEngine* pge);
	void Run();
	void SetRule(unsigned int rule);
	void SetState(unsigned int state);
	void Reset();
	unsigned int GetRule();
	unsigned int GetWidth();
	
private:
	bool GetNextState(bool left, bool center, bool right);
	void SetSpecificStartingState(unsigned int state);
	void SetRandomStartingState();
	void DrawCurrentGeneration();
	void GenerateNextGeneration();
	void Clear();
	olc::PixelGameEngine* pge;
	std::vector<bool> currentGeneration;
	std::vector<bool> nextGeneration;
	unsigned int state;
	unsigned int row;
	unsigned int rule;
	unsigned int width;
};