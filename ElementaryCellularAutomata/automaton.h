#pragma once

#include "olcPixelGameEngine.h"

const olc::Pixel LIVE_COLOR = olc::VERY_DARK_GREY;
const olc::Pixel DEAD_COLOR = olc::DARK_GREY;

namespace States
{
	enum State
	{
		CENTER = 0,
		LEFT = 1,
		RIGHT = 2,
		RANDOM = 3
	};
}

class Automaton
{
public:
	Automaton(olc::PixelGameEngine* pge);
	void Run();
	void SetRule(unsigned int rule);
	void SetState(unsigned int state);
	void ToggleWrap();
	void Reset();
	unsigned int GetRule();
	unsigned int GetWidth();
	
private:
	bool GetNextState(bool left, bool center, bool right);
	void SetSpecificStartingState(unsigned int state);
	void SetRandomStartingState();
	void DrawCurrentGeneration();
	void GenerateNextGeneration();
	olc::PixelGameEngine* pge;
	std::vector<bool> currentGeneration;
	std::vector<bool> nextGeneration;
	unsigned int state;
	unsigned int row;
	unsigned int rule;
	unsigned int width;
	bool wrap;
};