#pragma once

#include "olcPixelGameEngine.h"

class Automaton
{
public:
	Automaton(olc::PixelGameEngine* pge, unsigned int screenHeight);
	void Run();
	void SetRule(unsigned int rule);
	void SetSpecificStartingState(unsigned int state);
	void SetRandomStartingState();
	void Clear();
	void ClearAndRun();
	unsigned int GetRule();
	unsigned int GetWidth();
	
private:
	bool GetNextState(bool left, bool center, bool right);
	void DrawCurrentGeneration();
	void GenerateNextGeneration();
	olc::PixelGameEngine* pge;
	std::vector<bool> currentGeneration;
	std::vector<bool> nextGeneration;
	unsigned int row;
	unsigned int rule;
	int width;
	bool run;
};