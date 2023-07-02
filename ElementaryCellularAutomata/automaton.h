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
	void Clear();
	void ClearAndRun();
	unsigned int GetRule();
	bool run;
	
private:
	bool GetNextState(bool left, bool center, bool right, unsigned int rule);
	void DrawGeneration(Automaton* self, const std::bitset<SCREEN_WIDTH>& generation, unsigned int row);
	void GenerateNextGeneration(std::bitset<SCREEN_WIDTH>& currentGeneration, std::bitset<SCREEN_WIDTH>& nextGeneration, unsigned int numGenerations, unsigned int rule);
	void ShowNewInitialState(Automaton* self);
	olc::PixelGameEngine* pge;
	std::bitset<SCREEN_WIDTH> currentGeneration;
	std::bitset<SCREEN_WIDTH> nextGeneration;
	unsigned int numGenerations;
	unsigned int row;
	unsigned int rule;
};