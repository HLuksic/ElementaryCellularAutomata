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
    DrawGeneration(currentGeneration, row);
}

void Automaton::DrawGeneration(const std::vector<bool>& generation, unsigned int row)
{
    for (int i = 0; i < width; ++i)
        generation[i] ? pge->Draw(i, row, olc::DARK_GREY) : pge->Draw(i, row, olc::VERY_DARK_GREY);
}

bool Automaton::GetNextState(bool left, bool center, bool right, unsigned int rule)
{
    unsigned int ruleIndex = (left ? 4 : 0) + (center ? 2 : 0) + (right ? 1 : 0);
    return (rule >> ruleIndex) & 1;
}

void Automaton::GenerateNextGeneration(const std::vector<bool>& currentGeneration, std::vector<bool>& nextGeneration, unsigned int rule)
{
    for (int i = 0; i < width; ++i)
    {
        // wraps around the edges of the simulation
        bool left = currentGeneration[(i + (width - 1)) % width];
        bool right = currentGeneration[(i + 1) % width];
        bool center = currentGeneration[i];
        
        nextGeneration[i] = GetNextState(left, center, right, rule);
    }
}

void Automaton::Run()
{
    if (run)
    {
        DrawGeneration(currentGeneration, row);
        GenerateNextGeneration(currentGeneration, nextGeneration, rule);
        currentGeneration = nextGeneration;
        row++;
        
        if (row == pge->ScreenHeight())
            run = false;
    }
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
    DrawGeneration(currentGeneration, row);
    row = 0;
    run = false;
}

void Automaton::ClearAndRun()
{
    Clear();
    run = true;
}
