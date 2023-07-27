#include "automaton.h"
#include <random>

Automaton::Automaton(olc::PixelGameEngine* engine, unsigned int screenHeight)
{
    pge = engine;
    width = pge->ScreenWidth();
    currentGeneration.resize(width);
    nextGeneration.resize(width);
    currentGeneration[width / 2] = true;
    row = 0;
    rule = 30;
    run = false;
    DrawCurrentGeneration();
}

void Automaton::Run()
{
    if (run)
    {
        DrawCurrentGeneration();
        GenerateNextGeneration();
        currentGeneration = nextGeneration;
        row++;

        if (row == pge->ScreenHeight())
            run = false;
    }
}

void Automaton::GenerateNextGeneration()
{
    for (int i = 0; i < width; ++i)
    {
        // wraps around the edges of the simulation
        bool left = currentGeneration[(i + (width - 1)) % width];
        bool right = currentGeneration[(i + 1) % width];
        bool center = currentGeneration[i];
        
        nextGeneration[i] = GetNextState(left, center, right);
    }
}

bool Automaton::GetNextState(bool left, bool center, bool right)
{
    unsigned int ruleIndex = (left ? 4 : 0) + (center ? 2 : 0) + (right ? 1 : 0);
    return (rule >> ruleIndex) & 1;
}

void Automaton::DrawCurrentGeneration()
{
    for (int i = 0; i < width; ++i)
        currentGeneration[i] ? pge->Draw(i, row, olc::DARK_GREY) : pge->Draw(i, row, olc::VERY_DARK_GREY);
}

unsigned int Automaton::GetRule()
{
    return rule;
}

unsigned int Automaton::GetWidth()
{
    return width;
}

void Automaton::SetRule(unsigned int rule)
{
    this->rule = rule;
}

void Automaton::SetSpecificStartingState(unsigned int index)
{
    std::fill(currentGeneration.begin(), currentGeneration.end(), 0);
    currentGeneration[index] = true;
    Clear();
}

void Automaton::SetRandomStartingState()
{
    srand(unsigned int(time(NULL)));
    
	for (auto cell : currentGeneration)
		cell = rand() % 2;

    Clear();
}

void Automaton::Clear()
{
    pge->Clear(olc::VERY_DARK_GREY);
    row = 0;
    run = false;
    DrawCurrentGeneration();
}

void Automaton::ClearAndRun()
{
    Clear();
    run = true;
}
