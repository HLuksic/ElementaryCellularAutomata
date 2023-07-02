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
	void Clear();
	void ClearAndRun();
	unsigned int GetRule();
	
private:
	bool GetNextState(bool left, bool center, bool right, unsigned int rule);
	void DrawGeneration(std::vector<bool>& generation, unsigned int row);
	void GenerateNextGeneration(std::vector<bool>& currentGeneration, std::vector<bool>& nextGeneration, unsigned int rule);
	void ShowNewInitialState();
	olc::PixelGameEngine* pge;
	std::vector<bool> currentGeneration;
	std::vector<bool> nextGeneration;
	unsigned int row;
	unsigned int rule;
	int width;
	bool run;
};